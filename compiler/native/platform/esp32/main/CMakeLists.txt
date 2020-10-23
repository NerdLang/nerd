cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

idf_component_register(SRCS "../esp32.cpp"
                    INCLUDE_DIRS "")