// Collaborated with: Valerie Wong, Kira Hammond, zyBooks, cplusplus.com

/* Compile command:
   g++ WordLadder.cpp main.cpp -Wall -Werror -Wuninitialized -o a.out
*/

#include "WordLadder.h"

// TODO: We can't add data members or public member functions,
// but can we defined this global constant?
const int correctNumberOfLetters = 5;

/* Passes in the name of a file that contains a dictionary of 5-letter words.
   Fills the list (dict) with the words within this file. 
   If the file does not open for any reason or if any word within the file
   does not have exactly 5 characters, this function should output an
   error message and return.
*/
WordLadder::WordLadder(const string &file) {
  ifstream fin; 
  string word; 

  fin.open(file);

  if (!fin.is_open()) {
    cout << "Error opening " << file << endl; 
    return; // return with error code
  }

  while (fin >> word) {
    if (word.size() != 5) {
      cout << "Word does not have exactly 5 characters" << endl; 
      return; 
    }
    
    dict.push_back(word);
  }
  
}

ostream &operator<<(ostream &out, stack<string> wordLadder) {
  if (wordLadder.size() == 1) {
    out << wordLadder.top();
    return out;
  }

  // a b c d e f

  // scope 0
  // topWord = f
  // now wordLadder = a b c d e

  // scope 1
  // wordLadder = a b c d e
  // topWord = e
  // now wordLadder = a b c d

  // scope 2
  // wordLadder = a b c d
  // topWord = d
  // now wordLadder = a b c
  
  // scope 3
  // wordLadder = a b c
  // topWord = c
  // now wordLadder = a b
  
  // scope 4
  // wordLadder = a b
  // topWord = b
  // now wordLadder = a
  
  // scope 5
  // a
  // outputs a

  // output: a b c d e f
  
  string topWord;
  topWord = wordLadder.top();
  wordLadder.pop();
  out << wordLadder;
  out << " " << topWord;
  return out;
}

// makes sure the start and end word are in the dictionary
bool WordLadder::verifyWordsInDictionary(const string &start, const string &end) {
  // TODO: Any more efficient way to do this?
  bool startFound, endFound;
  
  startFound = false;
  endFound = false;

  for (string wordFromDict : dict) {
    if (start == wordFromDict) {
      startFound = true;
    }
    if (end == wordFromDict) {
      endFound = true;
    }
  }
  if (!startFound) {
    cout << "Start word \"" << start << "\" not found in dictionary." << endl;
    return false;
  } else if (!endFound) {
    cout << "End word \"" << end << "\" not found in dictionary." << endl;
    return false;
  } else {
    return true;
  }
}

// if strings are same length: return number of letters different between the 2 strings
// else return -1 as error code
int WordLadder::findHammingDistance(const string &firstString, const string &secondString) {
  char char1;
  char char2; 
  int counter = 0;

  if (firstString.size() != secondString.size()) {
    return -1;
  }

  for (unsigned i = 0; i < firstString.size(); ++i) {
    char1 = firstString.at(i);
    char2 = secondString.at(i);
    // cout << "char1: " << char1 << endl;
    // cout << "char2: " << char2 << endl;
    if (char1 != char2) {
      ++counter;
      // cout << "counter: " << counter << endl; 
    }
  }

  return counter;
}

// implement WordLadder algorithm 
bool WordLadder::findAWordLadder(const string &start, const string &end, stack<string> &wordLadder) {
  queue<stack<string>> queueOfStacks;
  stack<string> frontStack;
  stack<string> newStack;
  list<string> copyOfDict; 
  int distance;

  newStack.push(start);
  if (start == end) {
    wordLadder = newStack;
    return true;
  }

  queueOfStacks.push(newStack);

  while (!queueOfStacks.empty()) {
    frontStack = queueOfStacks.front(); 

    copyOfDict = dict;
    for (string word : copyOfDict) {
      distance = findHammingDistance(frontStack.top(), word);

      if (distance == 1) {
        newStack = frontStack;
        newStack.push(word);

        if (word != end) {
          queueOfStacks.push(newStack);
          dict.remove(word);
        }
        else {
          wordLadder = newStack;
          return true; 
        }
      }
    }
    queueOfStacks.pop();
  }
  
  return false; 
}

/* Passes in two 5-letter words and the name of an output file.
   Outputs to this file a word ladder that starts from the first word passed in
   and ends with the second word passed in.
   If either word passed in does not exist in the dictionary (dict),
   this function should output an error message and return.
   Otherwise, this function outputs to the file the word ladder it finds or outputs
   to the file, the message, "No Word Ladder Found."
*/
void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile) {
  ofstream ladderFile;
  stack<string> wordLadder;
  bool ladderFound;
  
  if (!verifyWordsInDictionary(start, end)) {
    exit(1);
  }

  ladderFile.open(outputFile);
  if (!ladderFile.is_open()) {
    cout << "The file could not be opened." << endl;
    exit(1);
  }
  
  ladderFound = findAWordLadder(start, end, wordLadder);
  
  if (!ladderFound) {
    ladderFile << "No Word Ladder Found." << endl;
  } else {
    ladderFile << wordLadder << endl;
  }
  
  ladderFile.close();
}
