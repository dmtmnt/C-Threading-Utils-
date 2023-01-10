cmake_minimum_required(VERSION 3.21)
project (TestCode)

 if (POLICY CMP0025)
    cmake_policy(SET CMP0025 NEW)
  endif ()
  
set(CMAKE_CXX_STANDARD 14)
set(CLANG_CXX_LANGUAGE_STANDARD C++14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(TARGET_NAME test_code)


file(GLOB_RECURSE DEMO_HEADERS include/*.h)
file(GLOB_RECURSE DEMO_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

add_executable(${TARGET_NAME} ${DEMO_HEADERS} ${DEMO_SOURCES} )

target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

