#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include<time.h>

using namespace std;


//global variables
bool bGameOver;
string HiddenWord;
int Lives;
vector<string> WordList;


//function headers
void OnInput(const string &Input);
void setupGame();
void processGuess(const string &Guess);
bool isIsogram(const string &Word);
vector<string> getValidWords(const vector<string> &WordList);
void getRedBlue(const string &Guess, int &RedCount, int &BlueCount);
vector<string> readWordFile();


int main()
{
    int i;
    string input;

    vector<string> WordList = readWordFile();
    WordList = getValidWords(WordList);

    while(true){          //infinite loop
        system("cls");
        setupGame();


        while(!bGameOver){  //play the game
           cout << endl << "Enter word: ";
           cin >> input;
           processGuess(input);
        }



        cout << "Enter 1 to try again. Press any key to exit." << endl;
        cin >> i;
        if(i == 1){
            continue;
        }
        else{
            break;
        }
    }


    return 0;
}



void setupGame(){
    srand(time(0));
    int randomIndex;
    randomIndex = rand() % WordList.size();

    cout << "Welcome to Red and Blue, a fun guessing game!" << endl;
    cout << "Type in your guess. For every letter in its correct place in the word you will receive a Red coin. For every letter present but in the wrong place, you will receive a Blue coin." << endl;
    cout << endl << endl;

    HiddenWord = WordList.at(randomIndex);
    Lives = HiddenWord.length();
    bGameOver = false;

    cout << "Enter the " << HiddenWord.length() << " letter word!" << endl;
    cout << "You have " << Lives << " lives left." << endl;
    cout << "Type in your guess and press Enter to continue..." << endl;
    //cout << "The word is " << HiddenWord << endl;

}



void processGuess(const string &Guess){

    if(Guess == HiddenWord){
            cout << "You have won!" << endl;
            bGameOver = true;
            return;
    }

    if(!isIsogram(Guess)){
        cout << "No repeating letters! Try again." << endl;
        return;
    }

    if(Guess.length() != HiddenWord.length()){
        cout << "The hidden word is" << HiddenWord.length() << " letters long!" << endl;
        cout << "Lost a life! You have" << (Lives - 1) << " lives left. Try again." << endl;
        return;
    }

    cout  << "Lost a life." << endl;
    Lives -= 1;

    if(Lives <= 0){
        system("cls");
        cout << "You have no lives left." << endl;
        cout << "The hidden word was: " << HiddenWord << endl;
        bGameOver = true;
        return;
    }

    int Red, Blue;
    getRedBlue(Guess, Red, Blue);
    cout << "You have " << Red << " red coins and " << Blue << " blue coins." << endl;
    cout << "Wrong answer! You have " << Lives << " lives left. Try again." << endl;

}

bool isIsogram(const string& Word){
    for (int Index = 0; Index < Word.length(); Index++){

        for (int Comparison = Index + 1; Comparison < Word.length(); Comparison++){

            if(Word.at(Index) == Word.at(Comparison)){
                return false;
            }

        }

    }

    return true;
}

vector<string> getValidWords(const vector<string> &WordList){
    vector<string> ValidWords;

    for(string Word : WordList){

        if(Word.length() >= 4 && Word.length() <= 8){
            if(isIsogram(Word)){
                ValidWords.push_back(Word);
            }
        }

    }

    return ValidWords;
}


void getRedBlue(const string &Guess, int &RedCount, int &BlueCount){
    RedCount = 0;
    BlueCount = 0;

    for(int GuessIndex = 0; GuessIndex < Guess.length(); GuessIndex++){

        if(Guess.at(GuessIndex) == HiddenWord.at(GuessIndex)){
            RedCount++;
            continue;
        }

        for(int HiddenIndex = 0; HiddenIndex < HiddenWord.length(); HiddenIndex++){

            if(Guess.at(GuessIndex) == HiddenWord.at(HiddenIndex)){
                BlueCount++;
            }

        }
    }
}


vector<string> readWordFile(){

    string word;
    ifstream WordFile;
    WordFile.open("Words.txt");

    if(WordFile.is_open()){
        while(!WordFile.eof()){
            getline(WordFile, word);
            WordList.push_back(word);
        }
        WordFile.close();
    }
    else{
        cout << "Could not open file" << endl;
    }


    return WordList;
}






