/*  ==========================================================================================
 *  Program Name        :   CryptoTest.cpp
 *  Program Description :   This program generates cryptographic data and saves it to two files.
 *	Why					: 	Demonstrate randomness in cryptographic provider
 *  Developer:              David Means <w1t3h4t@gmail.com>
 *  Date                :   04-APR-2024
 *  ===========================================================================================
 */
#include "CryptoTest.h"

void generateRandomNumbers(DWORD dataSize, BYTE* buffer) {
    HCRYPTPROV hCryptProv;
    CryptAcquireContext(&hCryptProv, nullptr, nullptr, PROV_RSA_AES, CRYPT_VERIFYCONTEXT);

    CryptGenRandom(hCryptProv, dataSize, buffer);

    CryptReleaseContext(hCryptProv, 0);
}

void saveDataToFile(const char* filename, DWORD dataSize, BYTE* data, bool hexFormat) {
    std::ofstream file(filename, std::ios::binary);
    if (hexFormat) {
        for (DWORD i = 0; i < dataSize; ++i) {
            file << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);
        }
    }
    else {
        file.write(reinterpret_cast<const char*>(data), dataSize);
    }
    file.close();
}

void generateAndSaveData(DWORD dataSize, bool generateHex) {
    if (generateHex) {
        BYTE* randomNumbers = new BYTE[dataSize];
        generateRandomNumbers(dataSize, randomNumbers);
        saveDataToFile("random_numbers.txt", dataSize, randomNumbers, true); // Save as hexadecimal
        delete[] randomNumbers;
        std::cout << "Random numbers generation and file saving completed in hexadecimal format." << std::endl;
    }
    else {
        BYTE* cryptographicData = new BYTE[dataSize];
        generateRandomNumbers(dataSize, cryptographicData);
        saveDataToFile("cryptographic_data_file.bin", dataSize, cryptographicData, false); // Save as binary
        delete[] cryptographicData;
        std::cout << "Cryptographic data generation and file saving completed in binary format." << std::endl;
    }
}

int main(int argc, char* argv[]) {
    DWORD dataSize = 0;
    bool generateHex = false;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--hex") == 0) {
            generateHex = true;
        }
        else if (strcmp(argv[i], "--count") == 0 && i + 1 < argc) {
            dataSize = std::stoi(argv[i + 1]) * 1024 * 1024; // Convert megabytes to bytes using std::stoi
            ++i; // Move to the next argument
        }
    }

    if (dataSize == 0) {
        std::cerr << "Usage: " << argv[0] << " [--hex] --count <megabytes>" << std::endl;
        return 1;
    }

    generateAndSaveData(dataSize, generateHex);

    return 0;
}



