/**
 CIS 22B: Homework 4C
 
 Structures and Strings
 Project: Text Analyzer: Word Count
 
 NAME: Huimei Wu
 */
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

#define SIZE 100

/* Define a struct named Word with the following fields:
 
 1. word, a string
 2. count, an integer
 
 */
struct Word
{
    string word;
    int count;
};

/* Define a struct named WordStats with the following fields:
 
 1. list, an array of SIZE Word structures defined above
 2. noWords, an integer, for the number of distinct words
 3. maxLength, an integer, for the length of the longest word
 4. highFreq, an integer, for the highest frequency
 
 */
struct WordStats
{
    Word list[SIZE];
    int noWords;
    int maxLength;
    int highFreq;
};


// Function prototypes
void buildList(string inFilename, WordStats *data);
string processString(string input);
int  binarySearch( Word ary[], int size, string neword);
void insertOne(Word ary[], int &size, string neword);
void printHigestFreq( const WordStats *data);
void writeFile( string outFilename, const WordStats *data);

int main()
{
    string inFilename; // = "song_row.txt";
    string outFilename;

    WordStats data;
    // use the following for testing printprintHigestFreq and writeFile
    /*
    WordStats data =
    {
        { {"a", 9},  {"boat", 21}, {"dream", 125}, {"merrily", 44}, {"row", 125}, {"stream", 5}} ,
        6,
        7,
        125
    };
     */
    
    cout << "Please enter the name of the input file: \n";
    cin >> inFilename;

    // get the name of the input file from the user
    buildList(inFilename, &data);
    printHigestFreq(&data);
    
    // Build output file name based on input file name
    int index = (int) inFilename.find('.', 0);
    outFilename = inFilename;
    outFilename.insert(index, "_OUT");
    
    writeFile(outFilename, &data);
    
    return 0;
}

/**************************************************
 This function builds word count list from input file
 */
void buildList(string inFilename, WordStats *data)
{
    ifstream inputFile;
    string tmp;

    // open the input file
    inputFile.open(inFilename.c_str());
    
    if (inputFile.fail())
    {
        cout << "\n\tPlease check the name of the input file"
        << "and \n\ttry again later!\n";
        exit(EXIT_FAILURE);
    }
    else
    {
        while (inputFile >> tmp)
        {
            // Process the string read from input file
            tmp = processString(tmp);

            // Binary search input string in current list
            int pos = binarySearch(data->list, data->noWords, tmp);
            
            // If input string is in current list, we need update
            // its occurrence
            if (pos != -1) {
                data->list[pos].count++;
                
                if (data->list[pos].count > data->highFreq) {
                    data->highFreq = data->list[pos].count;
                }
            }
            // If input string is NOT in current list, insert it to list
            else {
                insertOne(data->list, data->noWords, tmp);
                if (tmp.size() > data->maxLength) {
                    data->maxLength = (int) tmp.size();
                }
            }
        }
        // close the input file
        inputFile.close();
    }
}

/**************************************************
 This function processes input string:
     1. Change upper case to lower case
     2. Remove non alpha character
 */
string processString(string input)
{
    int index = 0;
    char tmp [input.size()];
    for (; index < input.size(); index++)
    {
        char c = input.at(index);
        if (c >= 'A' && c <= 'Z')
        {
            tmp[index] = c - 'A' + 'a';
        }
        else if (c >= 'a' && c <= 'z') {
            tmp[index] = c;
        }
        else {
            tmp[index] = '\0';
            break;
        }
    }
    
    return string(tmp, index);
}

/**************************************************
This function binary search input new word in the list
 */
int  binarySearch( Word ary[], int size, string neword)
{
    int first = 0,
    last = size - 1,
    middle,
    position = -1;
    bool found = false;
    
    while (!found && first <= last)
    {
        middle = (first + last) / 2;
        if(ary[middle].word == neword)
        {
            found = true;
            position = middle;
        }
        else if(ary[middle].word > neword)
            last = middle - 1;
        else
            first = middle + 1;
    }
    return position;
}

/**************************************************
This function inserts input new word to the list
 */
void insertOne(Word ary[], int &size, string neword)
{
    int index;
    for (index = size; index > 0; index--)
    {
        // If current position (index-1) is smaller than new word
        // we insert the new word to next position (index)
        if (ary[index-1].word < neword) {
            ary[index].word = neword;
            ary[index].count = 1;
            break;
        }
        // Otherwise, move current word one position back
        else {
            ary[index] = ary[index-1];
        }
    }

    // If input word is smaller than all words in the list
    // put it in the beginning of the list
    if (index == 0) {
        ary[index].word = neword;
        ary[index].count = 1;
    }
    
    // Update current size of the word list
    size++;
}

/**************************************************
This functions prints number of words, the max length,
the highest frequence, and sorted words
 */
void printHigestFreq( const WordStats *data)
{
    cout << data->noWords << " words" << endl;
    cout << "Maximum length: " << data->maxLength << endl;
    cout << "Highest frequency: " << data->highFreq << endl;
    
    for (int i = 0; i < data->noWords; i++)
    {
        cout << setw(3) << data->list[i].count
            << " " << data->list[i].word << endl;
    }
}

/**************************************************
This function writes data to output file based on required format.
 */
void writeFile( string outFilename, const WordStats *data)
{
    cout << "This is the writeFile function" << endl;
    ofstream outputFile;
    outputFile.open(outFilename.c_str());
    
    outputFile << data->noWords << " words" << endl;
    outputFile << "Maximum length: " << data->maxLength << endl;
    outputFile << "Highest frequency: " << data->highFreq << endl << endl;
    
    for (int i = 0; i < data->noWords; i++)
    {
        outputFile << setw(3) << data->list[i].count
                   << " " << data->list[i].word << endl;
    }

    outputFile.close();
}

/***************************************************************
 Save the OUTPUT below
 1.
 Please enter the name of the input file:
 song_row.txt
 13 words
 Maximum length: 7
 Highest frequency: 4
 1 a
 1 boat
 1 but
 1 down
 1 dream
 1 gently
 1 is
 1 life
 4 merrily
 3 row
 1 stream
 1 the
 1 your
 This is the writeFile function
 Program ended with exit code: 0
 
 2.
 Please enter the name of the input file:
 song_ten.txt
 18 words
 Maximum length: 12
 Highest frequency: 4
 1 accidentally
 1 and
 1 be
 1 bottle
 3 bottles
 1 fall
 4 green
 3 hanging
 1 if
 1 nine
 3 on
 1 one
 1 should
 2 ten
 3 the
 1 there
 3 wall
 1 will
 This is the writeFile function
 Program ended with exit code: 0
 
 3.
 Please enter the name of the input file: 
 test.txt
 7 words
 Maximum length: 5
 Highest frequency: 7
 1 end
 5 one
 2 step
 2 the
 7 three
 7 two
 7 waltz
 This is the writeFile function
 Program ended with exit code: 0
 */



