cmake_minimum_required(VERSION 3.28.0)
project(Algebra VERSION 0.1.0 LANGUAGES CXX)

set(HDRS headers)
set(SRCS sources)

set(ARCH architecture)
set(DABA database)
set(LIBS libraries)

include_directories(${HDRS}/${ARCH})
include_directories(${HDRS}/${DABA})
include_directories(${HDRS}/${LIBS})

set(PARS ${HDRS}/${LIBS}/parsing.hpp ${SRCS}/${LIBS}/parsing.cpp)
set(INPR ${HDRS}/${ARCH}/interpreter.hpp ${SRCS}/${ARCH}/interpreter.cpp)
set(VRBL ${HDRS}/${DABA}/variables.hpp ${SRCS}/${DABA}/variables.cpp)

add_library(LIB_PARS STATIC ${PARS})
add_library(LIB_INPR STATIC ${INPR})
add_library(LIB_VRBL STATIC ${VRBL})

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE LIB_PARS LIB_INPR LIB_VRBL)
target_link_libraries(LIB_INPR PUBLIC LIB_PARS)