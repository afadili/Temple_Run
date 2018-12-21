include_directories(include)
file(GLOB_RECURSE SRC_FILES *.cpp *.hpp)
add_library(Render ${SRC_FILES})
target_link_libraries(Render glimac)