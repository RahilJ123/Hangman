#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRIES 6
#define WORDS_COUNT 20
#define MAX_WORD_GUESSES 3

const char* words[WORDS_COUNT] = {
    "apple","banana","cherry","grape","kiwi","snorkel","enclave","quagmire","azure","xylophone",
    "jovial","fjord","zephyr","galvanize","blackjack","quixotic","crypt","embezzle","ocelot","fluffiness"
};

const char* chooseRandomWord() {
    int randomIndex = rand() % WORDS_COUNT;
    return words[randomIndex];
}

void displayHangman(int incorrectGuesses) {
    const char* hangmanFigures[MAX_TRIES + 1] = {
        "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========",
    };

    printf("%s\n", hangmanFigures[incorrectGuesses]);
}

void displayWord(const char* word, const char* guessed) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (strchr(guessed, word[i]) != NULL) {
            printf("%c ", word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

int main() {
    srand(time(NULL));
    const char* wordToGuess = chooseRandomWord();
    char guessedLetters[26] = {0};
    int tries = 0;
    int correctGuesses = 0;
    int incorrectGuesses = 0;
    int incorrectWordGuesses = 0;

    printf("Welcome to Hangman!\n");

    while (1) {
        printf("\n");
        displayHangman(incorrectGuesses);
        displayWord(wordToGuess, guessedLetters);
        printf("Tries left: %d\n", MAX_TRIES - incorrectGuesses);

        if (correctGuesses == strlen(wordToGuess)) {
            printf("Congratulations! You guessed the word: %s\n", wordToGuess);
            break;
        }

        if (incorrectGuesses >= MAX_TRIES) {
            printf("Sorry, you ran out of tries. The word was: %s\n", wordToGuess);
            break;
        }

        if (incorrectWordGuesses >= MAX_WORD_GUESSES) {
            printf("Sorry, you ran out of word guess attempts.\n");
            break;
        }

        printf("Guessed letters: ");
        for (int i = 0; i < 26; i++) {
            if (guessedLetters[i] != 0) {
                printf("%c ", guessedLetters[i]);
            }
        }
        printf("\n");

        printf("Guess a letter or enter the word (type '0' to guess the whole word): ");
        char guess[27];  // 26 letters plus null-terminator
        scanf("%s", guess);

        if (strcmp(guess, "0") == 0) {  // User wants to guess the whole word
            printf("Enter your word guess: ");
            char wordGuess[50];  // Adjust this size as needed
            scanf("%s", wordGuess);

            if (strcmp(wordGuess, wordToGuess) == 0) {
                printf("Congratulations! You guessed the word: %s\n", wordToGuess);
                break;
            } else {
                printf("Incorrect guess for the word.\n");
                incorrectWordGuesses++;
            }
        } else if (strlen(guess) == 1) {  // User guessed a single letter
            char letterGuess = guess[0];
            if (strchr(guessedLetters, letterGuess) != NULL) {
                printf("You already guessed that letter.\n");
            } else {
                guessedLetters[tries] = letterGuess;
                if (strchr(wordToGuess, letterGuess) != NULL) {
                    printf("Correct guess!\n");
                    correctGuesses++;
                } else {
                    printf("Incorrect guess.\n");
                    incorrectGuesses++;
                }
                tries++;
            }
        }
    }

    return 0;
}
