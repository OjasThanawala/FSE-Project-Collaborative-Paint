# Building Software

- [x] Instructions on how to build your software should be written in this file
	- This is especially important if you have added additional dependencies.
	- Assume someone who has not taken this class (i.e. you on the first day) would have read, build, and run your software from scratch.
- You should have at a minimum in your project
	- [x] A CMakeLists.txt in a root directory
    	- [ ] This should generate a 'release' version of your software
  - [x] Run your code with the latest version of cppcheck before commiting your code (could be a github action)
  - [ ] (Optional) Run your code with the latest version of clang-tidy  (could be a github action)

*Modify this file to include instructions on how to build and run your software. Specify which platform you are running on. Running your software involves launching a server and connecting at least 2 clients to the server.*


Steps to build and use the App:
1. Installing dependencies:
    - Linux: Open the terminal and run the following commands to ensure you  have the necessary dependencies:
        - *sudo apt-get install libsfml-dev* (installs SFML library)
        - *sudo apt -get install g++* (installs cpp)
        - *sudo apt-get install cmake* (install cmake)
    - Windows: use the following link to download SFML and the matching g++ compiler:
        - *https://www.sfml-dev.org/download/sfml/2.5.1/*
2. Navigate to FinalProject and open CMakeLists.txt and edit the lib and sfml paths according to you installation.
3. Navigate to bin and open a terminal at that location
4. Run the following commands to build:
    - cmake ..
    - make 
5. This should command should have built the 5 executable files in the bin folder:
    - App 
    - AppClient1
    - AppClient2
    - AppClient3
    - App_Test (this is you to test if the release you have works as expected)
<br/> There is no difference between App and the AppClient executables, but we name them as such so you cn use them as server and clients.
6. Launching a server must be your fierst step to make the code fucntion, launch App and follow the instructions to start a server
7. You may now launch the clients and connect to the server, and start painting away! Make sure that you use the same server port number for each client in order to be on the same network.
8. The server can hadle more clients, you may relaunch the clients again in seperate windows and they should be able to connect to the same sever.
9. The application has both GUI based and keyboard based interfaces to interact with its features, all keyboard options will be printed on the terminal if you launch your client from there.
10. Once all the clients are disconnected from the server (Press Esc closes a client), the server will automatically shutdown.
    
