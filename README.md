# CSCI 2270 Final
by Jeffrey Everett

## Project Summary
This project allows users to play a simple game of hangman through their terminal. The driver asks the user for their input and then interfaces with the Gallows class, which contains information such as the number of lives remaining, the hidden word, and the user's guessed characters. The user is allowed to choose a desired difficulty and subject to impact the number of lives they start with and the word bank from which the hidden word is chosen.

## How to Run
Before the program can be run, it must first be compiled. For UNIX-like environments, this can be done using `g++ -std=c++11 Gallows.h Gallows.cpp FinalProject.cpp -o hangman`. This line compiles the program and names the resulting binary `hangman`.

Running the program is very simple because it takes no command-line arguments. Simply instruct the terminal to run the compiled binary. For example, if the source is compiled into a binary called `hangman` in the working directory, you would simply type `./hangman` into the terminal.

After that, simply answer the text prompts provided by the program. It should be fairly intuitive.

## Dependencies
There are no dependencies for this project.

## System Requirements
This program should work on any machine capable of compiling C++11 code and executing the resulting binary.

## Group Members
I worked on this project by myself.

## Contributors
None.

## Open Issues
No issues are known.
