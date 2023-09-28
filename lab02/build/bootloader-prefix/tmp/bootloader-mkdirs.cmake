# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/hieun/esp/esp-idf/components/bootloader/subproject"
  "D:/Semester_231/Embeded_System/Lab/lab02/build/bootloader"
  "D:/Semester_231/Embeded_System/Lab/lab02/build/bootloader-prefix"
  "D:/Semester_231/Embeded_System/Lab/lab02/build/bootloader-prefix/tmp"
  "D:/Semester_231/Embeded_System/Lab/lab02/build/bootloader-prefix/src/bootloader-stamp"
  "D:/Semester_231/Embeded_System/Lab/lab02/build/bootloader-prefix/src"
  "D:/Semester_231/Embeded_System/Lab/lab02/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Semester_231/Embeded_System/Lab/lab02/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/Semester_231/Embeded_System/Lab/lab02/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
