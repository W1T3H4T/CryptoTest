#!/usr/bin/bash

# Function to compute SHA-224 or SHA-384 hash of a file using OpenSSL
compute_hash() {
    local file_path=$1
    local algorithm=$2
    openssl dgst -"$algorithm" "$file_path" | awk '{print $2}'
}

# Paths to the applications
random_data_gen_path="../CPP/Windows-binaries/RandomDataGen.exe"
check_entropy_path="../CPP/Windows-binaries/CheckEntropy.exe"

# Compute and display SHA-384 hash for RandomDataGen.exe
random_data_gen_hash_384=$(compute_hash "$random_data_gen_path" "sha384")
echo "RandomDataGen.exe SHA-384 hash: $random_data_gen_hash_384"

# Compute and display SHA-384 hash for CheckEntropy.exe
check_entropy_hash_384=$(compute_hash "$check_entropy_path" "sha384")
echo "CheckEntropy.exe SHA-384 hash: $check_entropy_hash_384"

