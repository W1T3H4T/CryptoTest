# Entropy Checker and Random Data Generator

## vcpkg
This project uses the [vcpkg](https://vcpkg.io/en/) C++ package manager to install the required libraries.  The following libraries are used: <br>
- OpenSSL
<br>OpenSSL is used to compute the SHA-256 hash of the data.
<br>Including it was necessary step for me to learn how to use vcpkg.  I'm certain there are others ways to compute a hash, but this was a good learning experience.
<br>For more information on vcpkg, see [vcpkg: A C++ Library Manager for Windows, Linux, and MacOS](https://vcpkg.io/en/docs/)



See also [Tutorial: Install and use packages with CMake in Visual Studio](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started-vs?source=recommendations&pivots=shell-powershell)

## Entropy Checker

This C++ program calculates the entropy of a file and determines the level of uncertainty in the data. It uses the Shannon entropy formula to quantify randomness and categorizes the entropy level based on the calculated value.

### Description

The program reads a file specified as a command-line argument, calculates the entropy 
of the data, and categorizes the level of entropy.  It also includes a function to 
compute the SHA-256 hash of the data for additional verification.

### Usage

```bash
./CheckEntropy --file <file_path>
```
Replace ``<file_path>`` with the path of the file to analyze.
<br><br>

### Random Data Generator

This C++ program generates random data and saves it to a file. It can be used to create strong cryptographic data for various purposes.

### Description

The program generates random data using the Windows API and saves it to a file called ``random_data.bin``
in binary format.  When using the ``--hex`` parameter, the data is saved in a file called ``random_data.txt``.<br>


```bash
./RandomDataGen.exe [--hex] [--test] --megabytes <size> | --bytes <size> 
```
The switches ``--megabytes`` and ``--bytes`` are mutually exclusive.<br>
Replace ``<size>`` with number of megabytes or bytes to generate.<br>
The optional ``--test`` switch generates the specified number of low-entropy data for testing purposes.<br>
Use the optional ``--hex`` flag to save the data in hexadecimal format.  Note: when using the ``--hex`` processing time will be longer.

## Hashes
```bash
RandomDataGen.exe SHA-384 hash: 11cc5c16d633077170e3f9d87165d0904187af930201320cc2b7c8d98d4ae9f008fee9aa650799ec8e6c3ea003a25608

CheckEntropy.exe SHA-384 hash: 40ebce9837506c1c286e1a6739f996befcd3e9e009578e9b510c2f04393ee9bb45a38ad7f339fc1877075244c938e2be
```

