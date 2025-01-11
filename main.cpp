#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;

const int NUM_WORDS = 10;
const int NUM_GUESS = 3;
const string FILE_NAME = "test.txt";


/* WORDLE
choose a random word
    through choosing a random number and iterating through until num
store word in array?
enter loop of guessing and checking (while guess < 5 && win == false)
    check validity of guess (against the ones in the file?)
    display already guessed letters (correct colors?)
    check each letter
        if contained in word
            if in correct spot
                green
            else
                yellow
        else
            grey
    if all are green, exit loop
*/ 

ifstream open_file(){
    ifstream words_file(FILE_NAME);
    if (!(words_file.is_open())){
        cout << "Error opening file." << endl;
        exit(1);
    }
    return words_file;
}

void choose_word(char* word_array, ifstream& words_file){
    string word = "";
    for (int i = 0; i < rand() % NUM_WORDS; i++){
        words_file >> word;
    }
    cout << word << endl;
    strcpy(word_array, word.c_str());
}

void get_guess(char* guess_array, int count){
    bool valid = false;
    string guess = "";
    while(!valid){
        cout << "What is your 5 letter word guess? (" << count << " guesses left): ";
        cin >> guess;
        valid = (guess.length() == 5);
        if(!valid){
            cout << "Error: your guess needs to be exactly 5 letters." << endl;
        }
    }
    strcpy(guess_array, guess.c_str());
}

void guess_check(string* graded_array, char* word_array, char* guess_array, int count){
    int current = NUM_GUESS - count;
    for (int i = 0; i < 5; i++){
        bool contain = false;
        if (word_array[i] == guess_array[i]){
            graded_array[current] += "\033[32m"; //green
        } else {
            for (int j = 0; j < 5; j++){
                if(guess_array[i] == word_array[j]){
                    contain = true;
                }
            }
            if (contain){
                graded_array[current] += "\033[33m"; //yellow
            } else {
                graded_array[current] += "\033[0m"; //grey
            }
        }
        graded_array[current] += guess_array[i];
        graded_array[current] += " ";
    }
    cout << graded_array[current] << "\033[0m \n";
}

int main() {    
    // rand setup
    srand((int) time(0));
    // open word file
    ifstream words_file = open_file();
    // choose random
    char word_array[6]; 
    choose_word(word_array, words_file);

    

    // guess loop
    int count = NUM_GUESS;
    bool correct = false;

    while(count > 0 /*|| !correct*/){
        char guess_array[6]; 
        get_guess(guess_array, count);        

        string graded_array[5];
        guess_check(graded_array, word_array, guess_array, count);
    
        count --;
    }

    return 0;
}


