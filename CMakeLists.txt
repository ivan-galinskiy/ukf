cmake_minimum_required(VERSION 3.16)
project(ukf LANGUAGES CXX)

include(ExternalProject)
include(CheckCXXCompilerFlag)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-register -Wno-ignored-attributes")

# Set default ExternalProject root directory
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX .)

# Add Eigen dependency
ExternalProject_Add(
eigen3
URL https://gitlab.com/libeigen/eigen/-/archive/5.0.0/eigen-5.0.0.tar.gz
TIMEOUT 30
DOWNLOAD_EXTRACT_TIMESTAMP TRUE
CMAKE_ARGS -DCMAKE_POLICY_VERSION_MINIMUM=3.5
# Disable install step
INSTALL_COMMAND ""
# Wrap download, configure and build steps in a script to log output
LOG_DOWNLOAD ON
LOG_CONFIGURE ON
LOG_BUILD ON)

ExternalProject_Get_Property(eigen3 source_dir)
SET(eigen_dir ${source_dir})

INCLUDE_DIRECTORIES(${eigen_dir})

GET_DIRECTORY_PROPERTY(hasParent PARENT_DIRECTORY)
IF(hasParent)
    SET(eigen_dir ${eigen_dir} PARENT_SCOPE)
ENDIF()

ENABLE_TESTING()

ADD_SUBDIRECTORY(test EXCLUDE_FROM_ALL)
ADD_SUBDIRECTORY(benchmark EXCLUDE_FROM_ALL)
ADD_SUBDIRECTORY(examples EXCLUDE_FROM_ALL)
