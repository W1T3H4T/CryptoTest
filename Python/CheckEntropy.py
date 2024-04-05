##  ==========================================================================================
##  Program Name        :   CheckEntropy.py
##  Program Description :   Attempt to detect randomness in a data set using entropy calculation
##  Developer:              David Means <w1t3h4t@gmail.com>
##  Date                :   04-APR-2024
##  ===========================================================================================
import hashlib
import argparse

def calculate_entropy(data):
    """
    Calculate the Shannon entropy of a given string or byte sequence.

    Parameters:
    - data: The input data as a string or byte sequence.

    Returns:
    - The Shannon entropy value.
    """
    # If the input is a string, convert it to bytes
    if isinstance(data, str):
        data = data.encode()

    # Calculate frequency of each byte value
    byte_counts = Counter(data)
    total_bytes = len(data)

    # Calculate probabilities and entropy
    entropy = 0.0
    for count in byte_counts.values():
        probability = count / total_bytes
        entropy -= probability * math.log2(probability)

    return entropy


def detect_randomness(data):
    """
    Detect randomness within a data set by computing the SHA-256 hash.

    Parameters:
    - data: The input data to be hashed.

    Returns:
    - SHA-256 hash value as a hexadecimal string.
    """
    sha256_hash = hashlib.sha256(data).hexdigest()
    return sha256_hash

def main():
    """
    Main function to demonstrate randomness detection using entropy calculation and SHA-256 hashing.
    """
    parser = argparse.ArgumentParser(description="Check entropy of a file.")
    parser.add_argument("--file", help="Path to the file to check for entropy.")
    args = parser.parse_args()

    if not args.file:
        print("Error: Please provide a file path using --file.")
        return

    try:
        with open(args.file, 'rb') as file:
            data = file.read()
    except FileNotFoundError:
        print(f"Error: File '{args.file}' not found.")
        return

    # Calculate entropy of the data
    entropy = calculate_entropy(data)
    print(f"Entropy of the data: {entropy}")

    # Detect randomness using cryptographic hash function (SHA-256)
    sha256_hash = detect_randomness(data)
    print(f"SHA-256 hash of the data: {sha256_hash}")

if __name__ == "__main__":
    main()

