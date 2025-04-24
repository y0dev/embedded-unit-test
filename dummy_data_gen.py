import random
import string

class DummyDataGenerator:
    """
    Utility class to generate dummy random data for embedded test cases.
    """

    @staticmethod
    def generate_unsigned_int_array(size):
        """
        Generate a list of random unsigned integers (32-bit).

        :param size: Number of elements in the array
        :return: List of unsigned integers
        """
        return [f"0x{random.randint(0, 0xFFFFFFFF):08X}" for _ in range(size)]
    
    @staticmethod
    def generate_unsigned_int_array_range(size, min_val, max_val):
        """
        Generate a list of random unsigned ints within a given range, in hex format.
        """
        return [f"0x{random.randint(min_val, max_val):08X}" for _ in range(size)]

    @staticmethod
    def generate_unsigned_short_array(size):
        """
        Generate a list of random unsigned shorts (16-bit).

        :param size: Number of elements in the array
        :return: List of unsigned shorts
        """
        return [f"0x{random.randint(0, 0xFFFF):04X}" for _ in range(size)]
    
    @staticmethod
    def generate_unsigned_short_array_range(size, min_val, max_val):
        """
        Generate a list of random unsigned shorts within a given range, in hex format.
        """
        return [f"0x{random.randint(min_val, max_val):04X}" for _ in range(size)]

    @staticmethod
    def generate_char_array(size):
        """
        Generate a list of random characters (ASCII printable).

        :param size: Number of characters in the array
        :return: String of random characters
        """
        return ''.join(random.choices(string.ascii_letters + string.digits, k=size))
    
    @staticmethod
    def generate_char_array_as_hex(size):
        return [f"0x{ord(c):02X}" for c in DummyDataGenerator.generate_char_array(size)]


    @staticmethod
    def generate_byte_array(size):
        """
        Generate a bytearray of random bytes.

        :param size: Number of bytes
        :return: bytearray with random values (0-255)
        """
        return bytearray(random.getrandbits(8) for _ in range(size))
    
    @staticmethod
    def generate_multidimensional_uint16_array(dimensions, min_val=0, max_val=0xFFFF):
        """
        Generate a multidimensional array of unsigned 16-bit integers in hex format.

        :param dimensions: Tuple like (2, 3) for 2x3
        :param min_val: Minimum value
        :param max_val: Maximum value
        :return: Nested list of hex strings
        """
        if len(dimensions) == 1:
            return [f"0x{random.randint(min_val, max_val):04X}" for _ in range(dimensions[0])]
        else:
            return [
                DummyDataGenerator.generate_multidimensional_uint16_array(dimensions[1:], min_val, max_val)
                for _ in range(dimensions[0])
            ]

    @staticmethod
    def to_c_multidimensional_array(array, var_type, var_name):
        """
        Convert a nested Python list into a C-style multidimensional array.

        :param array: Nested list (e.g., 2D or 3D) of hex-formatted strings
        :param var_type: C type (e.g., uint32_t)
        :param var_name: Name of the variable
        :return: String representing a C array definition
        """
        def format_array(arr, indent=1):
            if isinstance(arr[0], list):
                inner = ",\n".join(format_array(x, indent + 1) for x in arr)
                return "    " * indent + "{\n" + inner + "\n" + "    " * indent + "}"
            else:
                line = ", ".join(arr)
                return "    " * indent + "{ " + line + " }"

        dim_str = ''.join(f"[{len(dim)}]" for dim in DummyDataGenerator._get_shape(array))
        return f"const {var_type} {var_name}{dim_str} = {{\n{format_array(array)}\n}};\n"

    @staticmethod
    def _get_shape(array):
        """
        Utility function to get the shape (dimensions) of a nested list.
        """
        shape = []
        while isinstance(array, list):
            shape.append(len(array))
            array = array[0] if array else []
        return shape
    
    @staticmethod
    def generate_unsigned_long_array(size):
        """
        Generate a list of random unsigned long integers (64-bit).

        :param size: Number of elements in the array
        :return: List of unsigned 64-bit integers as hex strings
        """
        return [f"0x{random.randint(0, 0xFFFFFFFFFFFFFFFF):016X}" for _ in range(size)]
    
    @staticmethod
    def generate_unsigned_long_array_range(size, min_val, max_val):
        """
        Generate a list of random unsigned long (64-bit) integers within a given range, in hex format.

        :param size: Number of elements in the array
        :param min_val: Minimum value (inclusive)
        :param max_val: Maximum value (inclusive)
        :return: List of 64-bit unsigned integers in hex string format
        """
        return [f"0x{random.randint(min_val, max_val):016X}" for _ in range(size)]


    @staticmethod
    def generate_multidimensional_uint64_array(dimensions, min_val=0, max_val=0xFFFFFFFFFFFFFFFF):
        """
        Generate a multidimensional array of unsigned 64-bit integers in hex format.

        :param dimensions: Tuple specifying the dimensions (e.g., (3, 4) for a 3x4 array)
        :param min_val: Minimum value for the random integers
        :param max_val: Maximum value for the random integers
        :return: Nested list of hex-formatted 64-bit strings (e.g., [["0xABCDEF...", ...], ...])
        """
        if len(dimensions) == 1:
            return [f"0x{random.randint(min_val, max_val):016X}" for _ in range(dimensions[0])]
        else:
            return [DummyDataGenerator.generate_multidimensional_uint64_array(dimensions[1:], min_val, max_val)
                    for _ in range(dimensions[0])]
    
    @staticmethod
    def generate_multidimensional_uint32_array(dimensions, min_val=0, max_val=0xFFFFFFFF):
        """
        Generate a multidimensional array of unsigned 32-bit integers in hex format.

        :param dimensions: Tuple specifying the dimensions (e.g., (3, 4) for a 3x4 array)
        :param min_val: Minimum value for the random integers
        :param max_val: Maximum value for the random integers
        :return: Nested list of hex-formatted strings (e.g., [["0x12345678", ...], ...])
        """
        if len(dimensions) == 1:
            return [f"0x{random.randint(min_val, max_val):08X}" for _ in range(dimensions[0])]
        else:
            return [DummyDataGenerator.generate_multidimensional_uint32_array(dimensions[1:], min_val, max_val)
                    for _ in range(dimensions[0])]

    @staticmethod
    def to_c_char_array_string(char_string, var_name):
        """
        Formats a C-style null-terminated char array using string literals.
        """
        escaped = char_string.encode('unicode_escape').decode('utf-8')
        return f'const char {var_name}[{len(char_string) + 1}] = "{escaped}";\n'

    @staticmethod
    def to_c_array(array, var_type, var_name):
        """
        Converts a list of values to a C-style array declaration with 16 values per line.
        
        :param array: List of string representations of values (e.g., ["0x01", "0x02", ...]).
        :param var_type: The C type of the array (e.g., "uint32_t").
        :param var_name: The name of the variable.
        :return: A formatted C array as a string.
        """
        values_per_line = 8
        lines = []
        for i in range(0, len(array), values_per_line):
            line = ', '.join(array[i:i + values_per_line])
            lines.append(f"    {line}")
        joined_lines = ",\n".join(lines)
        return f"const {var_type} {var_name}[{len(array)}] = {{\n{joined_lines}\n}};\n"
    
    @staticmethod
    def to_c_multidimensional_array(array, var_type, var_name):
        """
        Converts a nested list (multidimensional array) to a C-style array declaration
        with 16 values per line in the innermost arrays.
        
        :param array: Nested list of values (e.g., [[0x01, 0x02], [0x03, 0x04]])
        :param var_type: C type (e.g., "uint16_t", "uint32_t", "uint64_t")
        :param var_name: Variable name
        :return: C array string
        """
        def format_dimensions(arr):
            dims = []
            while isinstance(arr, list):
                dims.append(str(len(arr)))
                arr = arr[0] if arr else []
            return "[" + "][".join(dims) + "]"

        def format_array(arr, indent=1):
            pad = '    ' * indent
            if isinstance(arr[0], list):
                return "{\n" + ",\n".join(
                    pad + format_array(sub, indent + 1) for sub in arr
                ) + "\n" + ('    ' * (indent - 1)) + "}"
            else:
                lines = []
                values_per_line = 16
                for i in range(0, len(arr), values_per_line):
                    line = ', '.join(arr[i:i+values_per_line])
                    lines.append(pad + line)
                return "{\n" + ",\n".join(lines) + "\n" + ('    ' * (indent - 1)) + "}"

        dims = format_dimensions(array)
        formatted = format_array(array)
        return f"const {var_type} {var_name}{dims} = {formatted};\n"

