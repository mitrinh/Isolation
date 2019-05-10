Prerequisites: MINGW installed, mingw/bin directory added to system path variables (WIN10), .zip file extracted to directory
1) Open command line.
2) go to directory where my src files are located in.
3) Check g++ version using "g++ --version" command:
    a) if program doesn't compile change g++ version to my tested version.
    b) my g++ version is "(MinGW.org GCC-6.3.0-1) 6.3.0".
4) Compile my program using command: "g++ main.cpp game.h board.h queen.h misc.h -o isolation" ("isolation" is name of executable).
5) Execute program using command: "isolation.exe" (or whatever name you gave to the attribute after -o in previous command).
    a) This can be executed as many times as you want without compiling program again.
6) The game should be running now and can be played by typing in the appropriate user input when prompted.
    a) make sure user input is appropriate and not in lowercase as it can crash the program or cause side effects (e.g. '-20','o','b5').
