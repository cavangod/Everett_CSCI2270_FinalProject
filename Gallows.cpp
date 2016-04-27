#include "Gallows.h"

#include <iostream>

const std::string Gallows::animalsWordBank[] = {"BEAR", "PANDA", "KOALA", "ZEBRA", "PENGUIN", "LION", "PANTHER", "IGUANA", "LEOPARD", "LEMUR", "DOG", "CAT", "HIPPO", "GIRAFFE", "SQUIRREL"};

const std::string Gallows::locationsWordBank[] = {"LONDON", "CALIFORNIA", "MADAGASCAR", "DETROIT", "COLORADO", "CHINA", "SINGAPORE", "ANTARCTICA", "EGYPT", "IOWA", "IRAN", "ITALTY", "SYRIA", "PARIS", "JAPAN"};

const std::string Gallows::televisionWordBank[] = {"PSYCH", "LONGMIRE", "ARROW", "DAREDEVIL", "DEXTER", "SPARTACUS", "LOST", "SEINFELD", "SUPERWOMAN", "SCRUBS", "SIMPSONS", "SUPERNATURAL", "ARTHUR", "BARNEY", "TELETUBBIES"};

const std::string Gallows::booksWordBank[] = {"MACBETH", "HAMLET", "DRACULA", "OTHELLO", "NIGHT", "UGLIES", "HOLES", "TWILIGHT", "IT", "MATILDA", "BELOVED", "MOCKINGJAY", "PRETTIES", "TARTUFFE", "ERAGON"};

const std::string Gallows::moviesWordBank[] = {"LOOPER", "CLOVERFIELD", "SAW", "BATMAN", "SUPERMAN", "DEADPOOL", "XMEN", "HULK", "CONSTANTINE", "MUMMY", "WICKERMAN", "HANCOCK", "KICKASS", "THOR", "WOLVERINE"};

Gallows::Gallows(Difficulty difficulty, Subject subject)
    : subject(subject), guessedHead(nullptr)
{
    // set the number of lives based on the desired difficulty
    switch (difficulty) {
        case Difficulty::EASY:
            lives = 12;
            break;
        case Difficulty::MEDIUM:
            lives = 9;
            break;
        case Difficulty::HARD:
            lives = 6;
            break;
    }

    // randomly choose a word from the word bank corresponding
    // to the desired subject
    std::string word;
    srand(time(nullptr));
    int index = rand() % 15;
    switch (subject) {
        case Subject::ANIMALS:
            word = animalsWordBank[index];
            break;
        case Subject::LOCATIONS:
            word = locationsWordBank[index];
            break;
        case Subject::TELEVISION:
            word = televisionWordBank[index];
            break;
        case Subject::BOOKS:
            word = booksWordBank[index];
            break;
        case Subject::MOVIES:
            word = moviesWordBank[index];
            break;
    }
    this->word = word;

    // set progress string to string of equal length consisting of
    // all underscores
    progress = std::string(word.length(), '_');
}

Gallows::~Gallows()
{
    GuessedChar* temp = guessedHead;

    while (temp->next) {
        GuessedChar* temp2 = temp->next;
        delete temp;
        temp = temp2;
    }

    delete temp;
}

void Gallows::guessCharacter(char c)
{
    // convert the character to uppercase
    c = std::toupper(c);

    // check if character is valid
    if (c < 'A' || c > 'Z') {
        std::cout << "That character is not valid. Please try again." << std::endl;
        return;
    }

    // check if character has been guessed previously
    if (guessedHead) {
        GuessedChar* temp = guessedHead;
        while (temp->next) {
            if (temp->c == c) {
                std::cout << "That character has already been guessed. Please try again." << std::endl;
                return;
            }

            temp = temp->next;
        }

        temp->next = new GuessedChar(c);
    }
    else {
        guessedHead = new GuessedChar(c);
    }

    // check for character occurrences in word
    int count = 0;
    for (int i = 0; i < word.length(); i++) {
        if (word[i] == c) {
            progress[i] = c;
            count++;
        }
    }

    // print results
    if (count == 0) {
        std::cout << "The character '" << c << "' was not present in the word/phrase. One life lost." << std::endl;

        lives--;

        if (lives == 0) {
            std::cout << "You have run out of lives. You lose. The word was " << word << "." << std::endl;
        }
    }
    else {
        std::cout << "The character '" << c << "' was found in the word/phrase " << count << " times." << std::endl;
    }
}

bool Gallows::hasWon()
{
    // return true if the player has guessed all the chars
    for (int i = 0; i < progress.length(); i++) {
        if (progress[i] == '_')
            return false;
    }

    return true;
}

bool Gallows::hasDied()
{
    // return true if the player has died
    return lives == 0;
}

void Gallows::displayProgress()
{
    // show guessed characters and underscores elsewhere
    for (int i = 0; i < progress.length(); i++) {
        std::cout << progress[i] << " ";
    }

    std::cout << "(" << lives << " lives remaining)" << std::endl;
}

void Gallows::displayInfo()
{
    // display relevant info
    std::cout << "Your word is from the subject " << getSubject() << " and has " << getCharacters() << " characters. You have " << lives << " lives remaining." << std::endl;
}

void Gallows::displayVictory()
{
    std::cout << "Congratulations! You have won. The word was " << word << "." << std::endl;
}

std::string Gallows::getSubject()
{
    // return string representing subject
    if (subject == Subject::ANIMALS)
        return "animals";
    else if (subject == Subject::LOCATIONS)
        return "locations";
    else if (subject == Subject::TELEVISION)
        return "television";
    else if (subject == Subject::BOOKS)
        return "books";
    else
        return "movies";
}

std::string Gallows::getWord()
{
    return word;
}

int Gallows::getCharacters()
{
    return word.length();
}

int Gallows::getLives()
{
    return lives;
}
