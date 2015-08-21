# ObjectDetector CMake config file
#
# This file sets the following variables:
# ObjectDetector_FOUND - Always TRUE.
# ObjectDetector_INCLUDE_DIRS - Directories containing the ObjectDetector include files.
# ObjectDetector_IDL_DIRS - Directories containing the ObjectDetector IDL files.
# ObjectDetector_LIBRARIES - Libraries needed to use ObjectDetector.
# ObjectDetector_DEFINITIONS - Compiler flags for ObjectDetector.
# ObjectDetector_VERSION - The version of ObjectDetector found.
# ObjectDetector_VERSION_MAJOR - The major version of ObjectDetector found.
# ObjectDetector_VERSION_MINOR - The minor version of ObjectDetector found.
# ObjectDetector_VERSION_REVISION - The revision version of ObjectDetector found.
# ObjectDetector_VERSION_CANDIDATE - The candidate version of ObjectDetector found.

message(STATUS "Found ObjectDetector-1.0.0")
set(ObjectDetector_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(ObjectDetector_INCLUDE_DIRS
#    "/usr/local/include/objectdetector-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(ObjectDetector_IDL_DIRS
#    "/usr/local/include/objectdetector-1/idl")
set(ObjectDetector_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(ObjectDetector_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(ObjectDetector_LIBRARIES
        "/usr/local/components/lib/libobjectdetector.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(ObjectDetector_LIBRARIES
        "/usr/local/components/lib/libobjectdetector.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(ObjectDetector_DEFINITIONS ${<dependency>_DEFINITIONS})

set(ObjectDetector_VERSION 1.0.0)
set(ObjectDetector_VERSION_MAJOR 1)
set(ObjectDetector_VERSION_MINOR 0)
set(ObjectDetector_VERSION_REVISION 0)
set(ObjectDetector_VERSION_CANDIDATE )

