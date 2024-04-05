##  ==========================================================================================
##  Program Name        :   CryptoTest.py
##  Program Description :   This program generates cryptographic data and saves it to two files.
##  Developer:              David Means <w1t3h4t@gmail.com>
##  ===========================================================================================

import sys
import os
import struct
import random
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.backends import default_backend

def generate_random_numbers(data_size):
    return os.urandom(data_size)

def save_data_to_file(filename, data, hex_format=False):
    with open(filename, 'wb') as file:
        if hex_format:
            file.write(data.hex().encode())
        else:
            file.write(data)

def generate_and_save_data(data_size, generate_hex):
    if generate_hex:
        random_numbers = generate_random_numbers(data_size)
        save_data_to_file("random_data.txt", random_numbers, hex_format=True)
    else:
        cryptographic_data = generate_random_numbers(data_size)
        save_data_to_file("random_data.bin", cryptographic_data)
       

def main():
    data_size = 0
    generate_hex = False

    args = sys.argv[1:]
    for i, arg in enumerate(args):
        if arg == "--hex":
            generate_hex = True
        elif arg == "--count" and i + 1 < len(args):
            data_size = int(args[i + 1]) * 1024 * 1024  # Convert megabytes to bytes
            break

    if data_size == 0:
        print("Usage:", sys.argv[0], "[--hex] --count <megabytes>")
        sys.exit(1)

    generate_and_save_data(data_size, generate_hex)

if __name__ == "__main__":
    main()
