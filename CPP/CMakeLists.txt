cmake_minimum_required(VERSION 3.8)
set(PYTHON_EXECUTABLE "python.exe" CACHE STRING "Path to Python executable")

# Run Python script to update version number
execute_process(
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/build-version/update-version.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE UPDATE_VERSION_RESULT
)

if (UPDATE_VERSION_RESULT)
    message(FATAL_ERROR "Failed to update version number.")
endif()

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("CryptoTest")

# Add source files for the main program
add_executable(RandomDataGen "RandomDataGen.cpp" "version.h" )

# Add source file for CheckEntropy program
add_executable(CheckEntropy "CheckEntropy.cpp" "version.h" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET RandomDataGen PROPERTY CXX_STANDARD 20)
    set_property(TARGET CheckEntropy PROPERTY CXX_STANDARD 20)
endif()

# Find and link OpenSSL libraries
find_package(OpenSSL REQUIRED)
target_link_libraries(RandomDataGen PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(CheckEntropy PRIVATE OpenSSL::SSL OpenSSL::Crypto)
