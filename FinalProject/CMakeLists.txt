####################################################
# CMake is a build file generator.
# It does not compile your software, but
# rather uses the CMake Language to 
# figure out how to generate another file
# for which you can then use to build projects.
# CMake is a specification language for build tools.
####################################################

############### INSTALLATION #######################
# Installation on Mac
# 'brew install cmake'
#
# Installation on Linux
# 'sudo apt-get install cmake'
#
# Installation on Windows
# See download page and download
####################################################

############## How to use CMake ####################
# I recommend you create a separate directory for
# your CMake generated files. This is a clean way
# to separate out all of your binary files generated
# from the source code. An example on Linux is
# the following:
#
# mkdir bin	# Make a directory
# cd bin	# navigate to that directory
# cmake .. 	# Then execute the CMakeLists.txt
#		# file found one directory up.
####################################################

####################################################
# Writing a CMake file involves writing one 
# cmake command per line.

# The minimum required version of CMake to use
cmake_minimum_required(VERSION 3.10)

# Set the project name to your project name
# Additionally, we specify the languages we need
# to use with our project 'App' which happen
# to be 'C++' (CXX), and 'C' is also included
# just in case we mix C in our C++ code
project(
    App             # Name of our application
    VERSION 1.0     # Version of our software
    LANGUAGES CXX)  # Language that we are using

# We can additionally set the langauge standard for
# C++
set(CMAKE_CXX_STANDARD 17)
ADD_COMPILE_OPTIONS(-Wall -Wextra -Wno-unused)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

#Find OpenGL package
find_package(OpenGL REQUIRED)

# Where are the include directories (sample for linux)
#link_directories("/usr/lib/x86_64-linux-gnu/")

# Where are the include directories (sample for Windows)
#include_directories("C:/Users/ojast/Personal/MASTERS/MSD/SFML-2.5.1/include") #Ojas use this line comment the rest
#include_directories("C:/Users/vishw/Desktop/Foundations of SE/SFML-2.5.1/include") #Vishwas use this, comment the rest
include_directories("C:/Users/Urvak/Documents/FSE/SFML-2.5.1/include") #Urvaksh use this comment the rest


include_directories("./include/")
include_directories("./include/Commands")
include_directories("include/Controllers")
include_directories("include/Ext")
include_directories("include/Types")
include_directories("include/Utils")
include_directories( ${OPENGL_INCLUDE_DIRS})

# Where are the libraries (sample for Windows)
#link_directories("C:/Users/ojast/Personal/MASTERS/MSD/SFML-2.5.1/lib") # Ojas
#link_directories("C:/Users/vishw/Desktop/Foundations of SE/SFML-2.5.1/lib") # Vishwas
link_directories("C:/Users/urvak/Documents/FSE/SFML-2.5.1/lib") # Urvaksh


# Add the source code files to a specific project
# We can indeed have multiple executables generated from
# one CMakeLists.txt file.
# For example, we might have test files that we want
# to generate.
#
# Here is an example below adding multiple files


add_executable(App ./src/App.cpp ./src/Commands/Brush.cpp ./src/Commands/BrushUndo.cpp ./src/Commands/Draw_Canvas.cpp src/Utils/Command.cpp ./src/main.cpp src/Controllers/UDPNetworkServer.cpp src/Controllers/UDPNetworkClient.cpp src/Utils/CommandFactory.cpp) # example with more files
add_executable(AppClient1 ./src/App.cpp ./src/Commands/Brush.cpp ./src/Commands/BrushUndo.cpp ./src/Commands/Draw_Canvas.cpp src/Utils/Command.cpp ./src/main.cpp src/Controllers/UDPNetworkServer.cpp src/Controllers/UDPNetworkClient.cpp src/Utils/CommandFactory.cpp) # example with more files
add_executable(AppClient2 ./src/App.cpp ./src/Commands/Brush.cpp ./src/Commands/BrushUndo.cpp ./src/Commands/Draw_Canvas.cpp src/Utils/Command.cpp ./src/main.cpp src/Controllers/UDPNetworkServer.cpp src/Controllers/UDPNetworkClient.cpp src/Utils/CommandFactory.cpp) # example with more files
add_executable(AppClient3 ./src/App.cpp ./src/Commands/Brush.cpp ./src/Commands/BrushUndo.cpp ./src/Commands/Draw_Canvas.cpp src/Utils/Command.cpp ./src/main.cpp src/Controllers/UDPNetworkServer.cpp src/Controllers/UDPNetworkClient.cpp src/Utils/CommandFactory.cpp) # example with more files
add_executable(App_Test ./src/App.cpp ./src/Commands/Brush.cpp ./src/Commands/BrushUndo.cpp ./src/Commands/Draw_Canvas.cpp src/Utils/Command.cpp ./tests/main_test.cpp src/Controllers/UDPNetworkServer.cpp src/Controllers/UDPNetworkClient.cpp src/Utils/CommandFactory.cpp)


# Add any libraries
# On linux, you can use the handy 'apt-file' tool to find
# where exactly header files exist. See example below:
# 	sudo apt install apt-file
#   	sudo apt-file update
# 	apt-file find Texture.hpp


target_link_libraries(App sfml-graphics sfml-window sfml-system sfml-network ${OPENGL_LIBRARIES})
target_link_libraries(AppClient1 sfml-graphics sfml-window sfml-system sfml-network ${OPENGL_LIBRARIES})
target_link_libraries(AppClient2 sfml-graphics sfml-window sfml-system sfml-network ${OPENGL_LIBRARIES})
target_link_libraries(AppClient3 sfml-graphics sfml-window sfml-system sfml-network ${OPENGL_LIBRARIES})
target_link_libraries(App_Test sfml-graphics sfml-window sfml-system sfml-network ${OPENGL_LIBRARIES})

