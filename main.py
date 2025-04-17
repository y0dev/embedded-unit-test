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


    

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate subdir.mk and optionally dummy test data.")
    parser.add_argument('--source', type=str, default='src', help='Source directory to scan for .c files')
    parser.add_argument('--target', type=str, default='.', help='Target directory to write subdir.mk to')
    parser.add_argument('--obj-root', type=str, default='obj', help='Root directory where object files should be placed')
    parser.add_argument('--generate-data', action='store_true', help='Generate dummy data arrays')

    args = parser.parse_args()
    config_json = None
    with open('config.json', 'r') as json_file:
        config_json = json.load(json_file)

    tester = EmbeddedTestAutomation(config_json)
    tester.generate_subdir_mk(target_dir=args.target, source_dir=args.source, obj_root=args.obj_root)

    if args.generate_data:
        uint_array = DummyDataGenerator.generate_unsigned_int_array(5)
        ushort_array = DummyDataGenerator.generate_unsigned_short_array(5)
        char_array = DummyDataGenerator.generate_char_array(10)
        byte_array = DummyDataGenerator.generate_byte_array(10)

        print("Unsigned Int Array:", uint_array)
        print("Unsigned Short Array:", ushort_array)
        print("Char Array:", char_array)
        print("Byte Array:", byte_array)

    print("Relative test paths:", get_relative_file_paths("unit_tests"))