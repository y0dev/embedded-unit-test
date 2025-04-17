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
        :return: bytearray with random values (0–255)
        """
        return bytearray(random.getrandbits(8) for _ in range(size))
    
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
    def to_c_char_array_string(char_string, var_name):
        """
        Formats a C-style null-terminated char array using string literals.
        """
        escaped = char_string.encode('unicode_escape').decode('utf-8')
        return f'const char {var_name}[{len(char_string) + 1}] = "{escaped}";\n'
