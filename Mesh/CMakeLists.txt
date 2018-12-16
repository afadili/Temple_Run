include_directories(include)
file(GLOB_RECURSE SRC_FILES *.cpp *.hpp)
add_library(Mesh ${SRC_FILES})