cmake_minimum_required(VERSION 3.5)

include("cmake/HunterGate.cmake")

HunterGate(
    URL "https://github.com/de-nik/hunter/archive/v0.19.137.1.tar.gz"
    SHA1 "2291d5651b6999408bdc7597b487f97e151ca2"
)

project(lab12)

set(CMAKE_CXX_STANDARD 11)

hunter_add_package(CURL)
find_package(CURL CONFIG REQUIRED)

set(SOURCE_FILES cget.cpp)
add_executable(lab12 ${SOURCE_FILES})

target_link_libraries(lab12 CURL::libcurl)
