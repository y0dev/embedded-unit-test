import os
import re
import json
import argparse
import subprocess
from datetime import datetime
from dummy_data_gen import DummyDataGenerator

def files_in_dir(dir_path):
    return [f for f in os.listdir(dir_path) if os.path.isfile(os.path.join(dir_path, f))]

def get_relative_file_paths(directory):
    """
    Gets all files in a directory and returns their relative paths.

    Args:
        directory: The path to the directory.

    Returns:
        A list of relative file paths.
    """
    file_paths = []
    for root, _, files in os.walk(directory):
        for file in files:
            absolute_path = os.path.join(root, file)
            relative_path = os.path.relpath(absolute_path, directory)
            file_paths.append(relative_path)
    return file_paths
class EmbeddedTestAutomation:
    def __init__(self, config_json):
        """
        Initialize with the JSON configuration for components to test.
        :param config_json: JSON string or dict specifying which components to test (e.g., gpio, uart).
        """
        if isinstance(config_json, str):
            self.config = json.loads(config_json)
        else:
            self.config = config_json
        
        self.generate_test_subdir_mk()

    def create_directories(self):
        """Create necessary directories for the project."""
        for directory in self.directories:
            if not os.path.exists(directory):
                os.makedirs(directory)
                print(f"Created directory: {directory}")
            else:
                print(f"Directory already exists: {directory}")

    def generate_subdir_mk(self, target_dir, source_dir='src', obj_root='obj', project_root='.', macros=None):
        """
        Generate a subdir.mk file listing C source and corresponding object files,
        and include paths for headers relative to the project root.

        Args:
            target_dir: Directory to place the subdir.mk file in.
            source_dir: Directory to scan for source files.
            obj_root: Base directory where object files are placed.
            project_root: Path where the top-level Makefile resides.
        """
        subdir_mk_path = os.path.join(target_dir, 'subdir.mk')
        if not os.path.exists(target_dir):
            os.makedirs(target_dir)

        c_sources = []
        object_files = []
        header_dirs = set()

        for root, _, files in os.walk(source_dir):
            for file in files:
                full_path = os.path.join(root, file)
                if file.endswith('.c'):
                    src_rel_path = os.path.relpath(full_path, start=project_root)
                    c_sources.append(src_rel_path)

                    rel_from_src = os.path.relpath(full_path, start=source_dir)
                    obj_path = os.path.join(obj_root, source_dir, rel_from_src).replace('.c', '.o')
                    obj_path = obj_path.replace('\\', '/')  # Normalize Windows paths
                    object_files.append(obj_path)

                elif file.endswith('.h'):
                    hdr_rel_path = os.path.relpath(root, start=project_root)
                    header_dirs.add(hdr_rel_path)

        with open(subdir_mk_path, 'w') as f:
            f.write("C_SRCS += \\\n")
            for idx, src in enumerate(c_sources):
                f.write(f"\t{src} {'\\' if idx < len(c_sources) - 1 else ''}\n")

            f.write("\n\nOBJS += \\\n")
            for idx, obj in enumerate(object_files):
                f.write(f"\t{obj} {'\\' if idx < len(object_files) - 1 else ''}\n")

            if header_dirs:
                f.write("\n\nINC_DIR += \\\n")
                for idx, hdr in enumerate(sorted(header_dirs)):
                    f.write(f"\t-I./{hdr} {'\\' if idx < len(header_dirs) - 1 else ''}\n")
                
                f.write("\n\nTEST_DIR += \\\n")
                for idx, hdr in enumerate(sorted(header_dirs)):
                    f.write(f"\t{hdr} {'\\' if idx < len(header_dirs) - 1 else ''}\n")

            if macros:
                f.write("\n\nMACROS += \\\n")
                current_line = "\t"
                for i, macro in enumerate(macros):
                    formatted_macro = f"-D{macro}"
                    # Check if adding the macro would exceed 72 characters
                    if len(current_line) + len(formatted_macro) + 1 > 72:
                        f.write(current_line.rstrip() + " \\\n")
                        current_line = "\t" + formatted_macro + " "
                    else:
                        current_line += formatted_macro + " "
                # Write the last line without trailing backslash
                f.write(current_line.rstrip() + "\n")


        print(f"Generated subdir.mk in: {subdir_mk_path}")
        return subdir_mk_path


    def generate_test_subdir_mk(self):
        if 'tests' not in self.config:
            print("No 'tests' section found in config.")
            return

        test_config = self.config['tests']

        for props in test_config:
            tpath = props.get('path')
            makefile_path = props.get('makefile_path')
            macros = props.get('macros', [])  # <- list of macro flags, like ["DEBUG", "FEATURE_X=1"]
            if not tpath or not makefile_path:
                print(f"Missing 'path' or 'makefile_path' in test config: {props}")
                continue

            if not os.path.exists(tpath):
                os.makedirs(tpath, exist_ok=True)

            subdir_path = self.generate_subdir_mk(tpath, source_dir=tpath, macros=macros)
            full_makefile_path = os.path.join(tpath, makefile_path)

            self.update_makefile_with_subdirs(full_makefile_path, [subdir_path])

    def update_makefile_with_subdirs(self,makefile_path, subdir_paths):
        """
        Adds `-include` lines for each subdir.mk in the given paths to the Makefile.

        :param makefile_path: Path to the Makefile to modify.
        :param subdir_paths: List of directories where subdir.mk files exist.
        """
        include_lines = [f"-include {path}" for path in subdir_paths]
        include_block = "\n".join(include_lines) + "\n"

        # Read existing Makefile content
        with open(makefile_path, 'r') as f:
            lines = f.readlines()

        # Find the index to insert after the flags (after TEST_MAIN_DIR )
        insert_index = None
        for i, line in enumerate(lines):
            if line.strip().startswith("TEST_MAIN_DIR"):
                insert_index = i + 1
                break
        
        if insert_index is None:
            raise RuntimeError("Could not find TEST_MAIN_DIR definition to insert after.")

        # Check if the include block is already there
        if any('-include' in line for line in lines):
            print("Makefile already includes subdir.mk lines. Skipping auto-insertion.")
            return
        
        # Insert include block
        lines.insert(insert_index, "\n# Automatically included subdir.mk files\n" + include_block)

        with open(makefile_path, 'w') as file:
            file.write("\n# Automatically included subdir.mk files\n")
            file.writelines(lines)
            print("Inserted subdir.mk includes into Makefile.")

    def generate_dummy_data(self, output_path='dummy_data.h'):
        if 'data' not in self.config:
            print("No 'data' section found in config.")
            return
        
        output_path = os.path.join('unit_tests', output_path)
        if os.path.exists(output_path):
            confirm = input(f"{output_path} exists. Overwrite? (y/n): ").lower()
            if confirm != 'y':
                print("Aborting.")
                return

        data_config = self.config['data']
        lines = ["#ifndef DUMMY_DATA_H", "#define DUMMY_DATA_H", "\n", "#include <stdint.h>", "\n"]

        for props in data_config:
            name = props.get('name', None)
            size = props.get('size', None)
            dtype = props.get('type', None)
            min_val = props.get("min", None)
            max_val = props.get("max", None)

            print(props)

            if not name or not size or not dtype:
                print(f"Missing a field for {props}")
                continue

            # Detect multidimensional shape
            is_multi = isinstance(size, (list, tuple))

            if dtype == 'uint':
                if is_multi:
                    data = DummyDataGenerator.generate_multidimensional_uint32_array(size, min_val or 0, max_val or 0xFFFFFFFF)
                    lines.append(DummyDataGenerator.to_c_multidimensional_array(data, 'uint32_t', name))
                else:
                    data = DummyDataGenerator.generate_unsigned_int_array_range(size, min_val or 0, max_val or 0xFFFFFFFF)
                    lines.append(DummyDataGenerator.to_c_array(data, 'uint32_t', name))

            elif dtype == 'ushort':
                if is_multi:
                    data = DummyDataGenerator.generate_multidimensional_uint16_array(size, min_val or 0, max_val or 0xFFFF)
                    lines.append(DummyDataGenerator.to_c_multidimensional_array(data, 'uint16_t', name))
                else:
                    data = DummyDataGenerator.generate_unsigned_short_array_range(size, min_val or 0, max_val or 0xFFFF)
                    lines.append(DummyDataGenerator.to_c_array(data, 'uint16_t', name))

            elif dtype == 'ulong':
                if is_multi:
                    data = DummyDataGenerator.generate_multidimensional_uint64_array(size, min_val or 0, max_val or 0xFFFFFFFFFFFFFFFF)
                    lines.append(DummyDataGenerator.to_c_multidimensional_array(data, 'uint64_t', name))
                else:
                    data = DummyDataGenerator.generate_unsigned_long_array_range(size, min_val or 0, max_val or 0xFFFFFFFFFFFFFFFF)
                    lines.append(DummyDataGenerator.to_c_array(data, 'uint64_t', name))

            elif dtype == 'char':
                data = DummyDataGenerator.generate_char_array(size)
                lines.append(DummyDataGenerator.to_c_char_array_string(data, name))

            elif dtype == 'byte':
                data = DummyDataGenerator.generate_char_array_as_hex(size)
                lines.append(DummyDataGenerator.to_c_array(data, 'uint8_t', name))

            else:
                print(f"Unknown data type: {dtype}")
                continue


        lines.append("\n#endif // DUMMY_DATA_H")

        with open(output_path, 'w') as f:
            f.write('\n'.join(lines))

        print(f"Generated dummy data in {output_path}")
    
    def run_makefile_and_log(self, makefile_path, make_target='all'):
        """
        Runs 'make clean' and then 'make <target>' for the given Makefile.
        Logs output to logs/YYYY/MM/DD/mmss_<makefile_name>.txt.
        Ensures obj directory exists before building.

        :param makefile_path: Full path to the Makefile.
        :param make_target: Target to build after clean (default: all).
        """
        if not os.path.exists(makefile_path):
            print(f"Makefile not found: {makefile_path}")
            return

        makefile_path = os.path.abspath(makefile_path)
        makefile_dir = os.path.dirname(makefile_path)
        makefile_name = os.path.basename(makefile_path).replace('.mk', '').replace('Makefile', 'main')

        # Create log path
        now = datetime.now()
        log_dir = os.path.join('logs', now.strftime('%Y'), now.strftime('%m'), now.strftime('%d'))
        os.makedirs(log_dir, exist_ok=True)
        log_file = os.path.join(log_dir, f"{now.strftime('%M%S')}_{makefile_name}.txt")
        
        obj_dirs = []

        # Try to prepare obj directory (if expected path used)
        for root, dirs, files in os.walk(makefile_dir):
            for file in files:
                if file.endswith('.c'):
                    rel_path = os.path.relpath(os.path.join(root, file), makefile_dir)
                    obj_path = os.path.join(makefile_dir, 'obj', os.path.dirname(rel_path))
                    os.makedirs(obj_path, exist_ok=True)

        with open(log_file, 'w') as log:
            def run_step(step):
                print(f"Running: make {step}")
                result = subprocess.run(
                    ['make', '-f', makefile_path, step],
                    cwd=makefile_dir,
                    stdout=subprocess.PIPE,
                    stderr=subprocess.STDOUT,
                    check=False
                )
                output = result.stdout.decode()
                log.write(output)
                return output

            run_step('clean')
            info_output = run_step('info')

            # Parse object directories from info output
            for line in info_output.splitlines():
                if 'Object Dir' in line or 'OBJ_DIR' in line:
                    match = re.search(r'Object Dir\s*:\s*(.*)', line)
                    if match:
                        dir_path = match.group(1).strip()
                        if dir_path:
                            obj_dirs.append(dir_path)
                elif line.startswith('  ') and '.o' in line:
                    for word in line.split():
                        dir_path = os.path.dirname(word)
                        if dir_path:
                            obj_dirs.append(dir_path)

            # Deduplicate and create obj dirs
            for path in set(obj_dirs):
                full_path = os.path.join(makefile_dir, path)
                os.makedirs(full_path, exist_ok=True)
            run_step(make_target)

        print(f"Build steps complete. Output logged to: {log_file}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate dummy data files based on config.")
    parser.add_argument('--config', type=str, required=True, help='Path to the config JSON file')
    parser.add_argument('--output', type=str, default='dummy_data.h', help='Output header file')
    
    args = parser.parse_args()

    with open(args.config, 'r') as f:
        config_data = json.load(f)

    tester = EmbeddedTestAutomation(config_data)
    tester.generate_dummy_data(output_path=args.output)

    # print("Relative test paths:", get_relative_file_paths("unit_tests"))