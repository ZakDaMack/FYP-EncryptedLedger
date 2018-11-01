# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zak/Code/FYP-EncryptedLedger/TFHE/tfhe-tfhe-1bedf38/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build

# Include any dependencies generated for this target.
include libtfhe/CMakeFiles/tfhe-nayuki-portable.dir/depend.make

# Include the progress variables for this target.
include libtfhe/CMakeFiles/tfhe-nayuki-portable.dir/progress.make

# Include the compile flags for this target's objects.
include libtfhe/CMakeFiles/tfhe-nayuki-portable.dir/flags.make

# Object files for target tfhe-nayuki-portable
tfhe__nayuki__portable_OBJECTS =

# External object files for target tfhe-nayuki-portable
tfhe__nayuki__portable_EXTERNAL_OBJECTS = \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/CMakeFiles/tfhe-core.dir/autogenerated.cpp.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/CMakeFiles/tfhe-core.dir/lwebootstrappingkey.cpp.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/CMakeFiles/tfhe-core.dir/lwe.cpp.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/CMakeFiles/tfhe-core.dir/lwe-functions.cpp.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/CMakeFiles/tfhe-core.dir/lwekey.cpp.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/CMakeFiles/tfhe-core.dir/lwekeyswitch.cpp.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/CMakeFiles/tfhe-core.dir/lweparams.cpp.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/CMakeFiles/tfhe-core.dir/lwesamples.cpp.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/CMakeFiles/tfhe-core.dir/multiplication.cpp.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/CMakeFiles/tfhe-core.dir/numeric-functions.cpp.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/CMakeFiles/tfhe-core.dir/polynomials.cpp.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/CMakeFiles/tfhe-core.dir/tgsw.cpp.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/CMakeFiles/tfhe-core.dir/tlwe.cpp.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/CMakeFiles/tfhe-core.dir/tlwe-functions.cpp.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/CMakeFiles/tfhe-core.dir/tgsw-functions.cpp.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/CMakeFiles/tfhe-core.dir/tlwe-fft-operations.cpp.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/CMakeFiles/tfhe-core.dir/tgsw-fft-operations.cpp.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/CMakeFiles/tfhe-core.dir/toruspolynomial-functions.cpp.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/CMakeFiles/tfhe-core.dir/boot-gates.cpp.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/CMakeFiles/tfhe-core.dir/lwe-keyswitch-functions.cpp.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/CMakeFiles/tfhe-core.dir/lwe-bootstrapping-functions.cpp.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/CMakeFiles/tfhe-core.dir/lwe-bootstrapping-functions-fft.cpp.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/CMakeFiles/tfhe-core.dir/tfhe_io.cpp.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/CMakeFiles/tfhe-core.dir/tfhe_generic_streams.cpp.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/CMakeFiles/tfhe-core.dir/tfhe_garbage_collector.cpp.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/CMakeFiles/tfhe-core.dir/tfhe_gate_bootstrapping.cpp.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/CMakeFiles/tfhe-core.dir/tfhe_gate_bootstrapping_structures.cpp.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/fft_processors/nayuki/CMakeFiles/tfhe-fft-nayuki-portable.dir/fft-x8664-avx-aux.c.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/fft_processors/nayuki/CMakeFiles/tfhe-fft-nayuki-portable.dir/fft-model-of-x8664-avx.c.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/fft_processors/nayuki/CMakeFiles/tfhe-fft-nayuki-portable.dir/fft_processor_nayuki.cpp.o" \
"/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/fft_processors/nayuki/CMakeFiles/tfhe-fft-nayuki-portable.dir/lagrangehalfc_impl.cpp.o"

libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-core.dir/autogenerated.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-core.dir/lwebootstrappingkey.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-core.dir/lwe.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-core.dir/lwe-functions.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-core.dir/lwekey.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-core.dir/lwekeyswitch.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-core.dir/lweparams.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-core.dir/lwesamples.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-core.dir/multiplication.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-core.dir/numeric-functions.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-core.dir/polynomials.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-core.dir/tgsw.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-core.dir/tlwe.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-core.dir/tlwe-functions.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-core.dir/tgsw-functions.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-core.dir/tlwe-fft-operations.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-core.dir/tgsw-fft-operations.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-core.dir/toruspolynomial-functions.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-core.dir/boot-gates.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-core.dir/lwe-keyswitch-functions.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-core.dir/lwe-bootstrapping-functions.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-core.dir/lwe-bootstrapping-functions-fft.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-core.dir/tfhe_io.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-core.dir/tfhe_generic_streams.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-core.dir/tfhe_garbage_collector.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-core.dir/tfhe_gate_bootstrapping.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-core.dir/tfhe_gate_bootstrapping_structures.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/fft_processors/nayuki/CMakeFiles/tfhe-fft-nayuki-portable.dir/fft-x8664-avx-aux.c.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/fft_processors/nayuki/CMakeFiles/tfhe-fft-nayuki-portable.dir/fft-model-of-x8664-avx.c.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/fft_processors/nayuki/CMakeFiles/tfhe-fft-nayuki-portable.dir/fft_processor_nayuki.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/fft_processors/nayuki/CMakeFiles/tfhe-fft-nayuki-portable.dir/lagrangehalfc_impl.cpp.o
libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-nayuki-portable.dir/build.make
libtfhe/libtfhe-nayuki-portable.so: libtfhe/CMakeFiles/tfhe-nayuki-portable.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Linking CXX shared library libtfhe-nayuki-portable.so"
	cd /home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tfhe-nayuki-portable.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libtfhe/CMakeFiles/tfhe-nayuki-portable.dir/build: libtfhe/libtfhe-nayuki-portable.so

.PHONY : libtfhe/CMakeFiles/tfhe-nayuki-portable.dir/build

libtfhe/CMakeFiles/tfhe-nayuki-portable.dir/requires:

.PHONY : libtfhe/CMakeFiles/tfhe-nayuki-portable.dir/requires

libtfhe/CMakeFiles/tfhe-nayuki-portable.dir/clean:
	cd /home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe && $(CMAKE_COMMAND) -P CMakeFiles/tfhe-nayuki-portable.dir/cmake_clean.cmake
.PHONY : libtfhe/CMakeFiles/tfhe-nayuki-portable.dir/clean

libtfhe/CMakeFiles/tfhe-nayuki-portable.dir/depend:
	cd /home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zak/Code/FYP-EncryptedLedger/TFHE/tfhe-tfhe-1bedf38/src /home/zak/Code/FYP-EncryptedLedger/TFHE/tfhe-tfhe-1bedf38/src/libtfhe /home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build /home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe /home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/CMakeFiles/tfhe-nayuki-portable.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libtfhe/CMakeFiles/tfhe-nayuki-portable.dir/depend

