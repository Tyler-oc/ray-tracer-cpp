cmake_minimum_required(VERSION 3.10)
project(Ray-Tracer VERSION 1.0 LANGUAGES CXX)

add_executable(Ray-Tracer main.cc)
set_target_properties(Ray-Tracer PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)