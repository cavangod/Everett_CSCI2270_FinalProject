#include "Gallows.h"

#include <iostream>
#include <string>

Difficulty getDifficulty()
{
    // let the user choose their desired difficulty
    // this setting impacts the number of lives they start with
    std::cout << "Please choose your difficulty (easy/medium/hard): ";

    std::string response;
    std::getline(std::cin, response);

    while (response != "easy" && response != "medium" && response != "hard") {
        std::cout << "Please enter 'easy', 'medium', or 'hard' to select your desired difficulty." << std::endl;
        std::getline(std::cin, response);
    }

    Difficulty difficulty;
    if (response == "easy") {
        difficulty = Difficulty::EASY;
    }
    else if (response == "medium") {
        difficulty = Difficulty::MEDIUM;
    }
    else {
        difficulty = Difficulty::HARD;
    }

    return difficulty;
}

Subject getSubject()
{
    // let the user choose their desired subject
    // this setting impacts the word bank from which their word is chosen
    std::cout << "Now choose your desired subject matter (animals/locations/television/books/movies): ";

    std::string response;
    std::getline(std::cin, response);

    while (response != "animals" && response != "locations" && response != "television" && response != "books" && response != "movies") {
        std::cout << "Please enter 'animals', 'locations', 'television', 'books', or 'movies' to select your desired subject area." << std::endl;
        std::getline(std::cin, response);
    }

    Subject subject;
    if (response == "animals") {
        subject = Subject::ANIMALS;
    }
    else if (response == "locations") {
        subject = Subject::LOCATIONS;
    }
    else if (response == "television") {
        subject = Subject::TELEVISION;
    }
    else if (response == "books") {
        subject = Subject::BOOKS;
    }
    else {
        subject = Subject::MOVIES;
    }

    return subject;
}

void playGame()
{
    // play an actual game
    // this is put into a function to allow multiple plays

    Difficulty difficulty = getDifficulty();
    Subject subject = getSubject();

    Gallows gallows = Gallows(difficulty, subject);
    std::cout << "-------------------------------------------------------" << std::endl << "Let's begin! Your word has " << gallows.getCharacters() << " characters and is from the subject '" << gallows.getSubject() << "'. You have " << gallows.getLives() << " lives remaining." << std::endl;


    std::string input = "";
    while (true) {
        gallows.displayProgress();
        std::cout << "Your guess (or 'quit'/'reset'/'info'): ";
        std::getline(std::cin, input);

        if (input == "quit") {
            break;
        }
        else if (input == "reset") {
            std::cout << "-------------------------------------------------------" << std::endl;
            playGame();
            return;
        }
        else if (input == "info") {
            gallows.displayInfo();
        }
        else if (input.length() > 1) {
            std::cout << "Your guess should only be one character. Please try again." << std::endl;
        }
        else {
            gallows.guessCharacter(input[0]);

            if (gallows.hasDied()) {
                // user has lost. ask them if they want to play again.
                std::cout << "Would you like to try again? (y/n): ";
                std::getline(std::cin, input);

                while (input != "y" && input != "n") {
                    std::cout << "Please enter 'y' or 'n': ";
                    std::cin >> input;
                }

                if (input == "n")
                    break;
                else {
                    std::cout << "-------------------------------------------------------" << std::endl;
                    playGame();
                    return;
                }
            }
        }

        if (gallows.hasWon()) {
            // user has won. ask them if they want to play again.
            gallows.displayVictory();
            std::cout << "Would you like to play again? (y/n): ";
            std::getline(std::cin, input);

            while (input != "y" && input != "n") {
                std::cout << "Please enter 'y' or 'n': ";
                std::cin >> input;
            }

            if (input == "n")
                break;
            else {
                std::cout << "-------------------------------------------------------" << std::endl;
                playGame();
                return;
            }
        }
    }

    // end of program
    std::cout << "Bye! Thanks for playing." << std::endl;
}

int main()
{
    std::cout << "Hello! Welcome to the gallows. Let's play some hangman!" << std::endl << "-------------------------------------------------------" << std::endl;

    // begin with single play
    playGame();
}
