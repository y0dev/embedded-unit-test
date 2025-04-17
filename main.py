import os
import json
import argparse
import subprocess
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
        

    def create_directories(self):
        """Create necessary directories for the project."""
        for directory in self.directories:
            if not os.path.exists(directory):
                os.makedirs(directory)
                print(f"Created directory: {directory}")
            else:
                print(f"Directory already exists: {directory}")

    def generate_subdir_mk(self, target_dir, source_dir='src', obj_root='obj'):
        """
        Generate a subdir.mk file listing C source and corresponding object files.
        
        Args:
            target_dir: The directory to place the subdir.mk file in.
            source_dir: The directory to scan for source files.
            obj_root: The base directory where object files should be placed.
        """
        subdir_mk_path = os.path.join(target_dir, 'subdir.mk')
        if not os.path.exists(target_dir):
            os.makedirs(target_dir)

        c_sources = []
        object_files = []

        for root, _, files in os.walk(source_dir):
            for file in files:
                if file.endswith('.c'):
                    src_rel_path = os.path.relpath(os.path.join(root, file), start=os.path.dirname(target_dir))
                    c_sources.append(src_rel_path)

                    rel_from_src = os.path.relpath(os.path.join(root, file), start=source_dir)
                    obj_path = os.path.join(obj_root, source_dir, rel_from_src).replace('.c', '.o')
                    obj_path = obj_path.replace('\\', '/')  # Normalize for Windows paths
                    object_files.append(obj_path)

        with open(subdir_mk_path, 'w') as f:
            f.write("C_SRCS += \\\n")
            for idx, src in enumerate(c_sources):
                if idx < len(c_sources) - 1:
                    f.write(f"\t{src} \\\n")
                else:
                    f.write(f"\t{src} \n")
            f.write("\n\nOBJS += \\\n")
            for idx, obj in enumerate(object_files):
                if idx < len(object_files) - 1:
                    f.write(f"\t{obj} \\\n")
                else:
                    f.write(f"\t{obj} \n")

        print(f"Generated subdir.mk in: {subdir_mk_path}")

    def generate_dummy_data(self, output_path='dummy_data.h'):
        if 'data' not in self.config:
            print("No data section found in config.")
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

            if dtype == 'uint':
                data = DummyDataGenerator.generate_unsigned_int_array_range(size, min_val or 0, max_val or 0xFFFFFFFF)
                lines.append(DummyDataGenerator.to_c_array(data, 'uint32_t', name))
            elif dtype == 'ushort':
                data = DummyDataGenerator.generate_unsigned_short_array_range(size, min_val or 0, max_val or 0xFFFF)
                lines.append(DummyDataGenerator.to_c_array(data, 'uint16_t', name))
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