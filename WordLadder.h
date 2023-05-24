// Collaborated with: Valerie Wong, Kira Hammond, zyBooks, cplusplus.com

/* Compile command:
   g++ WordLadder.cpp main.cpp -Wall -Werror -Wuninitialized -o a.out
*/

#ifndef WORD_LADDER_H
#define WORLD_LADDER_H

// TODO: Should we keep all these #include statements here?
// Or is it best practice to only have <string> and <stack> here
// and everything else in the implementation file?
#include <string>
#include <stack>

#include <list>
#include <queue>
#include <fstream>
#include <iostream>
using namespace std;


class WordLadder {

  private:
    list<string> dict;        //list of possible words in ladder
    
    // Helper functions:
    friend ostream &operator<<(ostream &out, const stack<string> &wordLadder);
    bool verifyWordsInDictionary(const string &start, const string &end);
    int findHammingDistance(const string &firstString, const string &secondString);
    bool findAWordLadder(const string &start, const string &end, stack<string> &wordLadder);
    
    /* "You may not add any data members or add any public member
       functions to this class. You will most likely want to add
       private helper functions though."
    */

  public:
    /* Passes in the name of a file that contains a dictionary of 5-letter words.
       Fills the list (dict) with the words within this file. 
       If the file does not open for any reason or if any word within the file
       does not have exactly 5 characters, this function should output an
       error message and return.
    */
    WordLadder(const string &);

    /* Passes in two 5-letter words and the name of an output file.
       Outputs to this file a word ladder that starts from the first word passed in
       and ends with the second word passed in.
       If either word passed in does not exist in the dictionary (dict),
       this function should output an error message and return.
       Otherwise, this function outputs to the file the word ladder it finds or outputs
       to the file, the message, "No Word Ladder Found."
    */
    void outputLadder(const string &start, const string &end, const string &outputFile);
};

#endif
