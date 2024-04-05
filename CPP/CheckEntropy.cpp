/*  =====================================================================================
 *  Program Name        :   CheckEntropy.cpp
 *  Program Description :   This program calculates the entropy of data from a file and
 *                          determines the level of randomness.
 *	Why					: 	Demonstrate randomness in cryptographic provider
 *  =====================================================================================
 */

/*  =====================================================================================
    MIT License

    Copyright (c) 2024 David Means <W1T3H4T@gmail.com>

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE. 

    =====================================================================================
    */


#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <openssl/sha.h>
#include <sstream>
#include "version.h"

enum class EntropyLevel {
    High,
    Moderate,
    Low
};

//  ==========================================================================================
//  Function Name       :   calculate_entropy
//  Function Description:   This function calculates the entropy of the input data and 
//                      :   determines the level of randomness.
//  Developer           :   David Means
//  Inputs              :   const std::vector<unsigned char>& data
//  Returns             :   std::pair<double, EntropyLevel>
// ===========================================================================================
std::pair<double, EntropyLevel> calculate_entropy(const std::vector<unsigned char>& data) {

    std::vector<int> byte_counts(256, 0);
    std::vector<double> probabilities(256, 0.0);
    double entropy = 0.0;
    EntropyLevel level;

    // If data is empty, return 0.0 and low entropy
    if (data.empty()) {
        return { 0.0, EntropyLevel::Low };
    }

    // Count occurrences of each byte value in the data
    for (unsigned char byte : data) {
        byte_counts[byte]++;
    }

    // Calculate probability of each byte value
    for (int i = 0; i < 256; i++) {
        probabilities[i] = static_cast<double>(byte_counts[i]) / data.size();
    }

    // Calculate entropy using Shannon entropy formula
    for (double prob : probabilities) {
        if (prob > 0) {
            entropy -= prob * log2(prob);
        }
    }

    // Determine the level of entropy
    if (entropy < 3.5) {
        level = EntropyLevel::Low;
    }
    else if (entropy < 4.5) {
        level = EntropyLevel::Moderate;
    }
    else {
        level = EntropyLevel::High;
    }

    return { entropy, level };
}

//  ==========================================================================================
//  Function Name       :   compute_sha256_hash
//  Function Description:   This function computes the SHA-256 hash of the input data.
//  Developer           :   David Means
//  Inputs              :   const std::vector<unsigned char>& data
//  Returns             :   std::string
// ===========================================================================================
std::string compute_sha256_hash(const std::vector<unsigned char>& data) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(data.data(), data.size(), hash);

    std::stringstream ss;
    for (unsigned char byte : hash) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }

    return ss.str();
}

//  ==========================================================================================
//  Function Name       :   basename
//  Function Description:   This function extracts the base name of a file path.
//  Developer           :   David Means
//  Inputs              :   const std::string& path
//  Returns             :   std::string
// ===========================================================================================
std::string basename(const std::string& path) {
    // Find the last occurrence of '/' or '\\'
    size_t pos = path.find_last_of("/\\");

    if (pos != std::string::npos) {
        return path.substr(pos + 1);
    }
    return path;
}

//  ==========================================================================================
//  Function Name       :   main
//  Function Description:   Entry point of the program. Reads data from a file, calculates
//                      :   entropy, and determines the level of randomness.
//  Developer           :   David Means
//  Inputs              :   int argc, char* argv[]
//  Returns             :   int
// ===========================================================================================
int main(int argc, char* argv[]) {

    std::cout
        << std::endl
        << "Version: " << PROJECT_VERSION_MAJOR << "."
        << PROJECT_VERSION_MINOR << "."
        << PROJECT_VERSION_PATCH << "."
        << PROJECT_VERSION_BUILD
        << std::endl;

    if (argc != 3 || std::string(argv[1]) != "--file") {
        std::cerr << std::endl;
        std::cerr << "Usage: " << basename(argv[0]) << " --file <file_path>" << std::endl;
        std::cerr << std::endl;
        return 1;
    }

    const char* file_path = argv[2];
    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file " << file_path << std::endl;
        return 1;
    }

    // Read file data into a vector
    std::vector<unsigned char> data(std::istreambuf_iterator<char>(file), {});

    file.close();

    // Calculate entropy and determine the level
    auto [entropy, level] = calculate_entropy(data);

    // Output the results
    std::cout << "Entropy is " << entropy << ", or ";
    switch (level) {
    case EntropyLevel::Low:
        std::cout << "Low (highly predictable)." << std::endl;
        break;
    case EntropyLevel::Moderate:
        std::cout << "Moderate (some predictability)." << std::endl;
        break;
    case EntropyLevel::High:
        std::cout << "High (unpredictable)." << std::endl;
        break;
    }

    return 0;
}

