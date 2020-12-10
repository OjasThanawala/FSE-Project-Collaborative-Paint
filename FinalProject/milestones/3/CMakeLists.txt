# Your CMakeLists.txt for the main App project
# This time what is new is I have added:
# 1.) another 'add_executable'
# 2.) another 'target_link_libraries'
#
# Observe now you will have two projects setup.
# As they stand, they will be identical.
####################################################
# The minimum required version of CMake to ouse
cmake_minimum_required(VERSION 3.10)

# Set the project name to your project name
project(App)

# Where are the include directories
include_directories("/usr/include/")
include_directories("./include/")

# Where are the libraries
# Hint: On linux you can grep for them: ldconfig -p | grep sfml
link_directories("/usr/lib/x86_64-linux-gnu/")

# Add the source code files to a specific project
# We can indeed have multiple executables generated from
# one CMakeLists.txt file.
# For example, we might have test files that we want
# to generate.
add_executable(App ./src/App.cpp ./src/Command.cpp ./src/Draw.cpp ./src/main.cpp)

add_executable(App_Test ./src/App.cpp ./src/Command.cpp ./src/Draw.cpp ./tests/main_test.cpp)

# Add any libraries
# On linux, you can use the handy 'apt-file' tool to find
# where exactly header files exist. See example below:
# 	sudo apt install apt-file
#   	sudo apt-file update
# 	apt-file find Texture.hpp
target_link_libraries(App sfml-graphics sfml-window sfml-system sfml-network)
target_link_libraries(App_Test sfml-graphics sfml-window sfml-system sfml-network)
