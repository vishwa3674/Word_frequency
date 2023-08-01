#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100

// Structure to store word frequency data
struct WordFrequency {
    char word[MAX_WORD_LENGTH];
    int frequency;
};

// Function to convert a string to lowercase (for case-insensitive word comparison)
void toLowercase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Function to insert a word into the hash table
void insertWord(struct WordFrequency* wordArray, int* numWords, char* word) {
    // Convert word to lowercase for case-insensitive comparison
    toLowercase(word);

    // Check if the word already exists in the wordArray
    for (int i = 0; i < *numWords; i++) {
        if (strcmp(wordArray[i].word, word) == 0) {
            // Word found, increase the frequency count
            wordArray[i].frequency++;
            return;
        }
    }

    // Word not found, create a new entry in the wordArray
    strcpy(wordArray[*numWords].word, word);
    wordArray[*numWords].frequency = 1;
    (*numWords)++;
}

// Function to compare two word frequencies for sorting
int compareWordFrequencies(const void* a, const void* b) {
    return strcmp(((struct WordFrequency*)a)->word, ((struct WordFrequency*)b)->word);
}

// Function to display the words and their frequencies in alphabetical order
void displayWordFrequency(struct WordFrequency* wordArray, int numWords) {
    printf("Word Frequency\n");
    printf("--------------\n");

    // Sort the wordArray based on words in alphabetical order
    qsort(wordArray, numWords, sizeof(struct WordFrequency), compareWordFrequencies);

    // Display the words and their frequencies in alphabetical order
    for (int i = 0; i < numWords; i++) {
        printf("%-10s %d\n", wordArray[i].word, wordArray[i].frequency);
    }
}

int main() {
    FILE* inputFile;
    char word[MAX_WORD_LENGTH];
    struct WordFrequency wordArray[MAX_WORD_LENGTH]; // Assuming the maximum number of words in the file is limited
    int numWords = 0;

    // Open the input file in read mode
    inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error: Cannot open input file.\n");
        return 1;
    }

    // Read each word from the file and insert it into the wordArray
    while (fscanf(inputFile, "%s", word) == 1) {
        insertWord(wordArray, &numWords, word);
    }

    // Close the input file
    fclose(inputFile);

    // Display the word frequencies in alphabetical order
    displayWordFrequency(wordArray, numWords);

    return 0;
}
