/*  =====================================================================================
 *  Program Name        :   RandomDataGen.cpp
 *  Program Description :   This program generates cryptographic data and saves it.
 *	Why					: 	Demonstrate randomness in cryptographic provider
 *  =====================================================================================
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

#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <Wincrypt.h>
#include "version.h"

//  =====================================================================================
//  Function Name       :   lowEntropyNumbers
//  Function Description:   This function generates low entropy numbers
//  Inputs              :   DWORD dataSize, BYTE* buffer
//  Returns             :   void
// ======================================================================================
void lowEntropyNumbers(DWORD dataSize, BYTE* buffer) {
    BYTE patternDigit = 0;

    for (DWORD i = 0; i < dataSize; ++i)
        buffer[i] = static_cast<BYTE>(std::rand() % 5);
}


//  =====================================================================================
//  Function Name       :   generateRandomNumbers
//  Function Description:   This function generates random numbers using the Windows 
//                      :   Cryptographic API.
//  Inputs              :   DWORD dataSize, BYTE* buffer
//  Returns             :   void
// ======================================================================================
void generateRandomNumbers(DWORD dataSize, BYTE* buffer) {
    HCRYPTPROV hCryptProv;
    CryptAcquireContext(&hCryptProv, nullptr, nullptr, PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
    CryptGenRandom(hCryptProv, dataSize, buffer);
    CryptReleaseContext(hCryptProv, 0);
}

//  =====================================================================================
//  Function Name       :   saveDataToFile
//  Function Description:   This function saves the data to a file in either hexadecimal 
//                      :   or binary format.
//  Inputs              :   const char* filename, DWORD dataSize, BYTE* data, bool hexFormat
//  Returns             :   void
//  ======================================================================================
void saveDataToFile(const char* filename, DWORD dataSize, BYTE* data, bool hexFormat) {
    std::ofstream file(filename, std::ios::binary);
    std::cout << "Saving data to file: " << filename << std::endl;

    if (hexFormat) {
        for (DWORD i = 0; i < dataSize; ++i) {
            file << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(1);
        }
    }
    else {
        file.write(reinterpret_cast<const char*>(data), dataSize);
    }
    file.close();
}

//  =====================================================================================
//  Function Name       :   generateAndSaveLowData
//  Function Description:   This function generates low entropy numbers and saves them to a file.
//  Inputs              :   DWORD dataSize, bool generateHex
//  Returns             :   void
//  =====================================================================================
void generateAndSaveLowData(DWORD dataSize, bool generateHex) {

    BYTE* noEntropyData = new BYTE[dataSize];
    lowEntropyNumbers(dataSize, noEntropyData);

    if (generateHex)
		saveDataToFile("low_entropy_data.txt", dataSize, noEntropyData, true); // Save as hexadecimal
	
    else
        saveDataToFile("low_entropy_data.bin", dataSize, noEntropyData, false); // Save as binary
    
    delete[] noEntropyData;
}
//  =====================================================================================
//  Function Name       :   generateAndSaveData
//  Function Description:   This function generates random numbers or cryptographic 
//                      :   data and saves it to a file.
//  Inputs              :   DWORD dataSize, bool generateHex
//  Returns             :   void
//  =====================================================================================
void generateAndSaveData(DWORD dataSize, bool generateHex) {
    
    BYTE* randomNumbers = new BYTE[dataSize];
    generateRandomNumbers(dataSize, randomNumbers);

    if (generateHex)
        saveDataToFile("random_data.txt", dataSize, randomNumbers, true); // Save as hexadecimal
    
    else
        saveDataToFile("random_data.bin", dataSize, randomNumbers, false); // Save as binary
   
    delete[] randomNumbers;

}

//  =====================================================================================
//  Function Name       :   basename
//  Function Description:   This function extracts the base name of a file path.
//  Inputs              :   const std::string& path
//  Returns             :   std::string
//  =====================================================================================
std::string basename(const std::string& path) {
    // Find the last occurrence of '/' or '\\'
    size_t pos = path.find_last_of("/\\");

    if (pos != std::string::npos) {
        return path.substr(pos + 1);
    }
    return path;
}

//  =====================================================================================
//  Function Name       :   main
//  Function Description:   Entry point of the program. Generates random numbers or cryptographic 
//                      :   data and saves it to a file.
//  Inputs              :   int argc, char* argv[]
//  Returns             :   int
//  =====================================================================================
int main(int argc, char* argv[])
{
    DWORD dataSize = 0;
    bool hasTestFlag = false;
    bool generateHex = false;
    std::cout 
        << std::endl 
        << "Version: " << PROJECT_VERSION_MAJOR << "." 
        << PROJECT_VERSION_MINOR << "." 
        << PROJECT_VERSION_PATCH << "." 
        << PROJECT_VERSION_BUILD 
        << std::endl;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--hex") == 0) {
            generateHex = true;
        }
        
        else if (strcmp(argv[i], "--test") == 0) {
            hasTestFlag = true;
        }

        else if (strcmp(argv[i], "--megabytes") == 0 && i + 1 < argc && dataSize == 0) {
            dataSize = std::stoi(argv[i + 1]) * 1024 * 1024; // Convert megabytes to bytes using std::stoi
            ++i; // Move to the next argument
        }

        else if (strcmp(argv[i], "--bytes") == 0 && i + 1 < argc && dataSize == 0) {
            dataSize = std::stoi(argv[i + 1]);
            ++i; // Move to the next argument
        }
        
        else {
            std::cerr << "Invalid argument: " << argv[i] << std::endl;
            return 1; // Exit the program with an error code
        }
    }

    if (dataSize == 0 ) {
        std::cerr << std::endl;
        std::cerr << "Usage: " << basename(argv[0]) << " [--hex]  [--test] | --megabytes <mb-size> | --bytes <bytes>" << std::endl;
        std::cerr << std::endl;
        return 1;
    }
    

    if ( hasTestFlag ) {
		std::cout << "Generating low entropy data" << std::endl;
        generateAndSaveLowData(dataSize, generateHex);
	}
    else {
		std::cout << "Generating random numbers" << std::endl;
        generateAndSaveData(dataSize, generateHex);
    }

    return 0;
}


