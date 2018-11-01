# Install script for directory: /home/zak/Code/FYP-EncryptedLedger/TFHE/tfhe-tfhe-1bedf38/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "optim")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/tfhe" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "/home/zak/Code/FYP-EncryptedLedger/TFHE/tfhe-tfhe-1bedf38/src/include/lagrangehalfc_arithmetic.h"
    "/home/zak/Code/FYP-EncryptedLedger/TFHE/tfhe-tfhe-1bedf38/src/include/lwe-functions.h"
    "/home/zak/Code/FYP-EncryptedLedger/TFHE/tfhe-tfhe-1bedf38/src/include/lwebootstrappingkey.h"
    "/home/zak/Code/FYP-EncryptedLedger/TFHE/tfhe-tfhe-1bedf38/src/include/lwekey.h"
    "/home/zak/Code/FYP-EncryptedLedger/TFHE/tfhe-tfhe-1bedf38/src/include/lwekeyswitch.h"
    "/home/zak/Code/FYP-EncryptedLedger/TFHE/tfhe-tfhe-1bedf38/src/include/lweparams.h"
    "/home/zak/Code/FYP-EncryptedLedger/TFHE/tfhe-tfhe-1bedf38/src/include/lwesamples.h"
    "/home/zak/Code/FYP-EncryptedLedger/TFHE/tfhe-tfhe-1bedf38/src/include/numeric_functions.h"
    "/home/zak/Code/FYP-EncryptedLedger/TFHE/tfhe-tfhe-1bedf38/src/include/polynomials.h"
    "/home/zak/Code/FYP-EncryptedLedger/TFHE/tfhe-tfhe-1bedf38/src/include/polynomials_arithmetic.h"
    "/home/zak/Code/FYP-EncryptedLedger/TFHE/tfhe-tfhe-1bedf38/src/include/tfhe.h"
    "/home/zak/Code/FYP-EncryptedLedger/TFHE/tfhe-tfhe-1bedf38/src/include/tfhe_core.h"
    "/home/zak/Code/FYP-EncryptedLedger/TFHE/tfhe-tfhe-1bedf38/src/include/tfhe_garbage_collector.h"
    "/home/zak/Code/FYP-EncryptedLedger/TFHE/tfhe-tfhe-1bedf38/src/include/tfhe_gate_bootstrapping_functions.h"
    "/home/zak/Code/FYP-EncryptedLedger/TFHE/tfhe-tfhe-1bedf38/src/include/tfhe_gate_bootstrapping_structures.h"
    "/home/zak/Code/FYP-EncryptedLedger/TFHE/tfhe-tfhe-1bedf38/src/include/tfhe_generic_streams.h"
    "/home/zak/Code/FYP-EncryptedLedger/TFHE/tfhe-tfhe-1bedf38/src/include/tfhe_generic_templates.h"
    "/home/zak/Code/FYP-EncryptedLedger/TFHE/tfhe-tfhe-1bedf38/src/include/tfhe_io.h"
    "/home/zak/Code/FYP-EncryptedLedger/TFHE/tfhe-tfhe-1bedf38/src/include/tgsw.h"
    "/home/zak/Code/FYP-EncryptedLedger/TFHE/tfhe-tfhe-1bedf38/src/include/tgsw_functions.h"
    "/home/zak/Code/FYP-EncryptedLedger/TFHE/tfhe-tfhe-1bedf38/src/include/tlwe.h"
    "/home/zak/Code/FYP-EncryptedLedger/TFHE/tfhe-tfhe-1bedf38/src/include/tlwe_functions.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/libtfhe/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/zak/Code/FYP-EncryptedLedger/TFHE/TFHE-Library-Build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
