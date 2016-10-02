//Jonathan Wapman

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

typedef map<char, short> Values;
typedef map<string, int> Combs;


class Word
{
  string word; //Stores the word
  
  int value; //Point value of the word
  
public:
  
  void setWord(const string& wor)
  {
    word = wor;
  } //setWord()
  
  void setValue(const int val)
  {
    value = val;
  } //setValue
  
  bool operator < (const Word rhs) const;
  
  
  string getWord() const
  {
    return word;
  } //getWord()
  
  int returnVal() const
  {
    return value;
  } //returnVal()
  
  friend bool operator == (const Word& lhs, const Word& rhs)
  {
    if (lhs.word == rhs.word && lhs.value == rhs.value)
    {
      return true;
    } //If the words are equal
    else //If not equal
    {
      return false;
    } //if not equal
  } // ==
  
}; //Word

bool Word::operator < (const Word rhs) const
{
  return (word.compare(rhs.word) < 0);
} // <


void initializeValues(Values& values)
{
  values.insert(Values::value_type('a', 1));
  values.insert(Values::value_type('b', 3));
  values.insert(Values::value_type('c', 3));
  values.insert(Values::value_type('d', 2));
  values.insert(Values::value_type('e', 1));
  values.insert(Values::value_type('f', 4));
  values.insert(Values::value_type('g', 2));
  values.insert(Values::value_type('h', 4));
  values.insert(Values::value_type('i', 2));
  values.insert(Values::value_type('j', 8));
  values.insert(Values::value_type('k', 5));
  values.insert(Values::value_type('l', 1));
  values.insert(Values::value_type('m', 3));
  values.insert(Values::value_type('n', 1));
  values.insert(Values::value_type('o', 1));
  values.insert(Values::value_type('p', 3));
  values.insert(Values::value_type('q', 10));
  values.insert(Values::value_type('r', 1));
  values.insert(Values::value_type('s', 1));
  values.insert(Values::value_type('t', 1));
  values.insert(Values::value_type('u', 1));
  values.insert(Values::value_type('v', 4));
  values.insert(Values::value_type('w', 4));
  values.insert(Values::value_type('x', 8));
  values.insert(Values::value_type('y', 4));
  values.insert(Values::value_type('z', 10));
  values.insert(Values::value_type(' ', 0));
} //initializeValues

int getValue(string& tempWord, Values& values)
{
  string::iterator itr; //Loops through string
  Values::iterator vitr;
  int wordValue = 0;
  
  for (itr = tempWord.begin(); itr != tempWord.end(); ++itr)
  {
    vitr = values.find(*itr); //Gets value of key
    wordValue += vitr->second; //Gets word value
  } //Gets values for each letter
  
  return wordValue;
  
} //getValues()

void readWords(set<Word>& words, Values& values)
{
  ifstream inf("words.txt"); //Opens file
  string tempWord; //Stores line from file
  string::iterator itr;
  bool shouldBreak = false;
  Word insertWord;
  
  while (getline(inf, tempWord))
  {
    if (tempWord.length() > 7)
      continue;
    
    for (itr = tempWord.begin(); itr != tempWord.end(); ++itr)
    {
      if (isupper(*itr) || isalpha(*itr) == false)
      {
        shouldBreak = true;
        break;
      } //Checks if letter is uppercase
    } //Checks if string has an uppercase letter
    
    if (shouldBreak == true)
    {
      shouldBreak = false;
      continue;
    } //Breaks out of loop

    insertWord.setWord(tempWord);
    insertWord.setValue(getValue(tempWord, values));
    
    words.insert(insertWord);
  } //Loops through lines
  
  inf.close(); //Closes file
} //readWords()

void clean(set<Word>& foundWords)
{
  int maxVal = 0;
  set<Word>::iterator itr;
  
  for (itr = foundWords.begin(); itr != foundWords.end(); ++itr)
  {
    if (itr->Word::returnVal() > maxVal)
    {
      maxVal = itr->Word::returnVal();
    } //Updates max val
  } //Finds max value
  
  for (itr = foundWords.begin(); itr != foundWords.end(); itr = itr)
  {
    if (itr->Word::returnVal() < maxVal)
    {
      foundWords.erase(itr);
      itr = foundWords.begin();
      continue;
    } //Erases too-small words
    
    ++itr;
  } //Cleans words
} //clean()

void print(set<Word>& foundWords, string userString)
{
  set<Word>::iterator itr = foundWords.begin();
  cout << setw(2) << right << itr->Word::returnVal() << " ";
  cout << userString << ":";
  
  if (foundWords.size() == 0)
  {
    cout << " No words found.\n";
    return;
  } //If no words found
  
  for (itr = foundWords.begin(); itr != foundWords.end(); itr++)
  {
    cout << " " << itr->Word::getWord();
  } //Prints words
  
  cout << endl;
} //Print

void replaceSpaces2(string& tempString, int spacePos, Combs& combs,
                    string& combString, Values& values)
{
  combs.insert(Combs::value_type(combString.replace(spacePos, 1, "n"),
                                 getValue(tempString, values)));
  combs.insert(Combs::value_type(combString.replace(spacePos, 1, "o"),
                                 getValue(tempString, values)));
  combs.insert(Combs::value_type(combString.replace(spacePos, 1, "p"),
                                 getValue(tempString, values)));
  combs.insert(Combs::value_type(combString.replace(spacePos, 1, "q"),
                                 getValue(tempString, values)));
  combs.insert(Combs::value_type(combString.replace(spacePos, 1, "r"),
                                 getValue(tempString, values)));
  combs.insert(Combs::value_type(combString.replace(spacePos, 1, "s"),
                                 getValue(tempString, values)));
  combs.insert(Combs::value_type(combString.replace(spacePos, 1, "t"),
                                 getValue(tempString, values)));
  combs.insert(Combs::value_type(combString.replace(spacePos, 1, "u"),
                                 getValue(tempString, values)));
  combs.insert(Combs::value_type(combString.replace(spacePos, 1, "v"),
                                 getValue(tempString, values)));
  combs.insert(Combs::value_type(combString.replace(spacePos, 1, "w"),
                                 getValue(tempString, values)));
  combs.insert(Combs::value_type(combString.replace(spacePos, 1, "x"),
                                 getValue(tempString, values)));
  combs.insert(Combs::value_type(combString.replace(spacePos, 1, "y"),
                                 getValue(tempString, values)));
  combs.insert(Combs::value_type(combString.replace(spacePos, 1, "z"),
                                 getValue(tempString, values)));
} //replaceSpaces2()

void replaceSpaces(string& combString, Combs& combs, Values& values)
{
  string origString = combString; //Saves original string
  int spacePos = (int)combString.find(' ');
  set<string>::iterator itr;
  string tempString = combString; //Stores the replacement strings
  combs.insert(Combs::value_type(combString.replace(spacePos, 1, "a"),
                                 getValue(tempString, values)));
  combs.insert(Combs::value_type(combString.replace(spacePos, 1, "b"),
                                 getValue(tempString, values)));
  combs.insert(Combs::value_type(combString.replace(spacePos, 1, "c"),
                                 getValue(tempString, values)));
  combs.insert(Combs::value_type(combString.replace(spacePos, 1, "d"),
                                 getValue(tempString, values)));
  combs.insert(Combs::value_type(combString.replace(spacePos, 1, "e"),
                                 getValue(tempString, values)));
  combs.insert(Combs::value_type(combString.replace(spacePos, 1, "f"),
                                 getValue(tempString, values)));
  combs.insert(Combs::value_type(combString.replace(spacePos, 1, "g"),
                                 getValue(tempString, values)));
  combs.insert(Combs::value_type(combString.replace(spacePos, 1, "h"),
                                 getValue(tempString, values)));
  combs.insert(Combs::value_type(combString.replace(spacePos, 1, "i"),
                                 getValue(tempString, values)));
  combs.insert(Combs::value_type(combString.replace(spacePos, 1, "j"),
                                 getValue(tempString, values)));
  combs.insert(Combs::value_type(combString.replace(spacePos, 1, "k"),
                                 getValue(tempString, values)));
  combs.insert(Combs::value_type(combString.replace(spacePos, 1, "l"),
                                 getValue(tempString, values)));
  combs.insert(Combs::value_type(combString.replace(spacePos, 1, "m"),
                                 getValue(tempString, values)));

  replaceSpaces2(tempString, spacePos, combs, combString, values);
  combString = origString; //resets combination string
} //replaceSpaces

void permute(string& userString, map<string, int>& combs, Values& values)
{
  string::iterator stitr;
  string combString;
  
  if (userString.length() > 7)
  {
    combs.insert(map<string, int>::value_type(combString, 0));
    return;
  } //If the user's string is longer than 7 chars
  
  while (next_permutation(userString.begin(), userString.end()))
  {
    for (stitr = userString.begin(); stitr != userString.end(); ++stitr)
    {
      combString.push_back(*stitr); //Gets the user's string
      
      if ((int)combString.find(' ') != -1)
      {
        replaceSpaces(combString, combs, values);
        continue;
      } //if a space is found
      
      combs.insert(map<string, int>::value_type(combString,
                                                getValue(combString, values)));
    } //Gets combinations
    
    combString.erase();
  } //Gets all permutations of the string
} //permute()

void findWords(set<Word>& words, Values& values, ifstream& inf)
{
  string combString, userString, origString;
  string::iterator stitr;
  
  while(getline(inf, userString)) //While still reading in lines from file
  {
    set<Word>::iterator sitr; //Loops through set
    Word combWord; //temporary word
    map<string, int> combs;
    set<Word> foundWords;
    set<string>::iterator combitr;
    map<string, int>::iterator mitr;
    origString = userString;
    sort(userString.begin(), userString.end()); //Sorts the string initially
    permute(userString, combs, values);
    
    for (sitr = words.begin(); sitr != words.end(); ++sitr)
    {
      mitr = combs.find(sitr->Word::getWord());
      
      if (mitr != combs.end())
      {
        combWord.setWord(mitr->first); //Sets word
        combWord.setValue(mitr->second);
        
        if (combWord.returnVal() != 0)
          foundWords.insert(combWord);
      } //Finds the word
    } //loops through all words
    
    clean(foundWords);
    print(foundWords, origString);
  } //While still reading in lines from file
  
  inf.close(); //Closes file
} //findWords()

int main(int argc, const char** argv)
{
  ifstream wordFile(argv[1]);
  Values values; //Stores word values, sorted highest to lowest value
  set<Word> words; //Stores the words
  
  initializeValues(values); //initializes values
  
  readWords(words, values); //reads words from file

  findWords(words, values, wordFile); //Finds the words from the set of words
  
  return 0;
} //main()
