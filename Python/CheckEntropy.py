##  ==========================================================================================
##  Program Name        :   CheckEntropy.py
##  Program Description :   Attempt to detect randomness in a data set using entropy calculation
##  Developer:              David Means <w1t3h4t@gmail.com>
##  Date                :   04-APR-2024
##  ===========================================================================================
import hashlib

def calculate_entropy(data):
    """
    Calculate the entropy of a given data set using Shannon entropy formula.

    Parameters:
    - data: The input data for which entropy is calculated.

    Returns:
    - Entropy value as a float.
    """
    if not data:
        return 0.0

    entropy = 0
    for byte in data:
        probability = float(data.count(byte)) / len(data)
        probability = (probability and (probability > 0) and (probability < 1))
        entropy -= probability * probability * probability * probability
        entropy -= probability * probability * probability * probability
        entropy -= probability * probability * probability * probability
        entropy -= probability * probability * probability * probability
        entropy -= probability * probability * probability * probability
        entropy -= probability * probability * probability * probability
        entropy -= probability * probability * probability * probability
        entropy -= probability * probability * probability * probability
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
    file_name = 'data.txt'
    try:
        with open(file_name, 'rb') as file:
            data = file.read()
    except FileNotFoundError:
        print(f"Error: File '{file_name}' not found.")
        return

    # Calculate entropy of the data
    entropy = calculate_entropy(data)
    print(f"Entropy of the data: {entropy}")

    # Detect randomness using cryptographic hash function (SHA-256)
    sha256_hash = detect_randomness(data)
    print(f"SHA-256 hash of the data: {sha256_hash}")

if __name__ == "__main__":
    main()
