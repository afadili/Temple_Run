cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

#name of the project 
project(Temple_Run)

# compilation flags (but should be avoided)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")

# specify the system
message("CMAKE_VERSION          : " ${CMAKE_VERSION})
message("CMAKE_SYSTEM           : " ${CMAKE_SYSTEM})
message("CMAKE_SYSTEM_PROCESSOR : " ${CMAKE_SYSTEM_PROCESSOR})

# use at least c++ 11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# add a "output" directory in the project binary directory
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/output)

# put the binary files in this directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# find packages
find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# To manage a bug on some pc, delete on personal machine
# set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)

# lib include path
include_directories(${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} glimac/include third-party/include)
include_directories(dependencies/jsoncpp/include Error/include Render/include Game/include Element/include Mesh/include)

set(ALL_LIBRARIES jsoncpp glimac Error Render Game Element Mesh ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

add_subdirectory(dependencies/jsoncpp)
add_subdirectory(glimac)
add_subdirectory(Error)
add_subdirectory(Render)
add_subdirectory(Game)
add_subdirectory(Element)
add_subdirectory(Mesh)

file(GLOB GAME_DIRECTORIES "TEMPLE_RUN")

foreach(GAME ${GAME_DIRECTORIES})
    add_subdirectory(${GAME})
endforeach()


#copy shaders and assets
file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY levels DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY assets.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY config.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


# call the CMakeLists.txt to make the documentation (Doxygen)
# > 'make html' to generate the documentation
# > the documentation is located in : [CMAKE ROOT]/build/doc/doc-doxygen/html
add_subdirectory(doc)
