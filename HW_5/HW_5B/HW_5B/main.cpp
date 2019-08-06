//  HW_5B

#include <iostream>
#include <fstream>
#include "Question.h"

using namespace std;

Question *readQuestions(string filename, int &n);
void randomizeQuestions(Question * ptrQuestion, int n);
void randomizeAnswers(Question * ptrQuestion, int n);
void swapQuestions(Question * ptrQuestion, int index1, int index2);
void playTriviaGame(Question * ptrQuestion, int n, string player1, string player2);
int getValidNum(int low, int high);

int main(int argc, const char * argv[]) {
    int n = 0;
    string player1;
    string player2;
    
    Question *ptrQuestion = readQuestions("TriviaQuestions.txt", n);
    
    // Prompt the user to enter the names of the next two players
    cout << "Please enter first name of player1" << endl;
    cin >> player1;
    cout << "Please enter first name of player2" << endl;
    cin >> player2;

    while (player1 != "#" && player2 != "#")
    {
        // Randomize questions and ansers before playing the game
        randomizeQuestions(ptrQuestion, n);
        randomizeAnswers(ptrQuestion, n);
        
        // Play trivia game
        playTriviaGame(ptrQuestion, n, player1, player2);
        
        // Prompt the user to enter the names of the next two players
        cout << "Please enter first name of player1" << endl;
        cin >> player1;
        cout << "Please enter first name of player2" << endl;
        cin >> player2;
    }

    //release memory
    delete [] ptrQuestion;

    return 0;
}

/***************************************************************
 This function reads data from an input file into a dynamically
 allocated array
 filename - the name of the input file
 n - the array size (an output parameter)
 Return - the dynamically allocated array
 */
Question *readQuestions(string filename, int &n)
{
    ifstream inputFile;
    int idx = 0;
    Question *ptrQuestion = nullptr;
    string question;
    string answer;
    string tmp;
    
    // open the input file
    inputFile.open(filename.c_str());
    
    if (inputFile.fail())
    {
        cout << "\n\tPlease check the name of the input file and"
             << "\n\ttry again later!\n";
        exit(EXIT_FAILURE);
    }
    else
    {
        // read number of students that were surveyed
        getline(inputFile, tmp);
        n = atoi(tmp.c_str());
        cout << "There are " << n << " questions in the input file" << endl;
        
        // allocate memory for array with size n
        ptrQuestion = new Question[n];
        
        // read data from the input file into arrays
        for (idx = 0; idx < n; idx++)
        {
            // getline for the question
            getline(inputFile, question);
            ptrQuestion[idx].setQuestion(question);

            // getline for each answer
            for (int i = 0; i < 4; i++)
            {
                getline(inputFile, answer);
                ptrQuestion[idx].setAnswer(i, answer);
                
                if (i == 0) {
                    // set correct answer as the first answer
                    ptrQuestion[idx].setAnswerKey(answer);
                }
            }

            // read the empty line between each question
            getline(inputFile, tmp);
        }

        // close the input file
        inputFile.close();
    }
    return ptrQuestion;
}

/***************************************************************
 This function randomizes questions before playing game
 
 ptrQuestion - the pointer of the question array
 n - the array size
 */
void randomizeQuestions(Question * ptrQuestion, int n)
{
    for (int i = 0; i < n; i++)
    {
        // Generate a random number in range [0, n-1]
        int randIndex = rand() % n;
        while (randIndex == i)
        {
            randIndex = rand() % n;
        }
        // Swap the two questions in index i and randIndex
        swapQuestions(ptrQuestion, i, randIndex);
    }
}

/***************************************************************
 This function swaps the two questions in index1 and index2
 
 ptrQuestion - the pointer of the question array
 index1 - the first index to swap
 index2 - the second index to swap
 */
void swapQuestions(Question * ptrQuestion, int index1, int index2)
{
    Question tmp;

    tmp = ptrQuestion[index1];
    ptrQuestion[index1] = ptrQuestion[index2];
    ptrQuestion[index2] = tmp;
}

/***************************************************************
 This function randomizes answers before playing game
 
 ptrQuestion - the pointer of the question array
 n - the array size
 */
void randomizeAnswers(Question * ptrQuestion, int n)
{
    string tmp;

    for (int i = 0; i < n; i++)
    {
        ptrQuestion[i].shuffleAnswers();
    }
}

/***************************************************************
 This function plays trivia game with two players
 
 ptrQuestion - the pointer of the question array
 n - the array size
 player1 - first name of player 1
 player2 - first name of player 2
 */
void playTriviaGame(Question * ptrQuestion, int n, string player1, string player2)
{
    int answerIndex1;
    int answerIndex2;
    string answer1;
    string answer2;
    int count1 = 0;
    int count2 = 0;

    // Display 6 questions for two players
    for (int i = 0; i < 6; i++) {
        // Print the question
        cout << ptrQuestion[i].getQuestion() << endl;
        
        // Print the 4 answers
        for (int j = 0; j < 4; j++) {
            cout << "\t" << j+1 << ". " << ptrQuestion[i].getAnswer(j) << endl;
        }
        
        // Collect anwser from player 1
        if (i % 2 == 0) {
            cout << "Player 1, " << player1 << ", please select your answer:" << endl;
            answerIndex1 = getValidNum(1, 4);
            answer1 = ptrQuestion[i].getAnswer(answerIndex1-1);
            
            if (answer1 == ptrQuestion[i].getAnswerKey()) {
                cout << "Congratulations." << endl;
                count1++;
            }
            else {
                cout << "Sorry. The correct answer is: "
                     << ptrQuestion[i].getAnswerKey() << endl;
            }
        }
        // Collect anwser from player 2
        else {
            cout << "Player 2, " << player2 << ", please select your answer:" << endl;
            answerIndex2 = getValidNum(1, 4);
            answer2 = ptrQuestion[i].getAnswer(answerIndex2-1);

            if (answer2 == ptrQuestion[i].getAnswerKey()) {
                cout << "Congratulations" << endl;
                count2++;
            }
            else {
                cout << "Sorry. The correct answer is: "
                     << ptrQuestion[i].getAnswerKey()<< endl;
            }
        }
        cout << endl;
    }
    
    // Print the results for each player and the final winner of this game
    cout << "Player 1, " << player1 << ", eraned " << count1 << " point(s)." << endl;
    cout << "Player 2, " << player2 << ", eraned " << count2 << " point(s)." << endl;
    if (count1 > count2) {
        cout << "Player 1, " << player1 << ", is the winner." << endl;
    }
    else if (count1 < count2) {
        cout << "Player 2, " << player2 << ", is the winner." << endl;
    }
    else {
        cout << "The game is equalized." << endl;
    }
    cout << endl;
}

int getValidNum(int low, int high)
{
    int num;
    
    do
    {
        cout << "\tPlease enter a number (" << low << " to " << high << "): ";
        cin >> num;
        cin.clear();          // to clear the error flag
        cin.ignore(80, '\n'); // to discard the unwanted input from the input buffer
    } while (cin.fail() || num < low || num > high);
    
    return num;
}

/***************************************************************
 Save the OUTPUT below
 There are 14 questions in the input file
 Please enter first name of player1
 Huimei1
 Please enter first name of player2
 Huimei2
 A constructor that requires no arguments is called
 1. None of the above
 2. A null constructor
 3. An overloaded constructor
 4. A default constructor
 Player 1, Huimei1, please select your answer:
 Please enter a number (1 to 4): 4
 Congratulations.
 
 Data hiding refers to an object’s ability to
 1. Hide its data from code that is inside the object
 2. Hide its data
 3. Hide its procedures
 4. Hide its data from code that is outside the object
 Player 2, Huimei2, please select your answer:
 Please enter a number (1 to 4): 1
 Sorry. The correct answer is: Hide its data from code that is outside the object
 
 The operator that identifies the function as a member of a class is
 1. ->
 2. .
 3. :
 4. ::
 Player 1, Huimei1, please select your answer:
 Please enter a number (1 to 4): 3
 Sorry. The correct answer is: ::
 
 The complete name of the operator that identifies the function as a member of a class is
 1. Scope operator
 2. Identification operator
 3. Scope identification operator
 4. Scope resolution operator
 Player 2, Huimei2, please select your answer:
 Please enter a number (1 to 4): 4
 Congratulations
 
 A class is not an object, but it is
 1. A description of an object
 2. Code that specifies the attributes that a particular type of object may have
 3. An instance of an object
 4. Code that specifies the functions that a particular type of object may have
 Player 1, Huimei1, please select your answer:
 Please enter a number (1 to 4): 1
 Congratulations.
 
 An object is not a class, but it is
 1. Code that specifies the attributes that a class may have
 2. An instance of a class
 3. Code that specifies the functions that a class may have
 4. A description of a class
 Player 2, Huimei2, please select your answer:
 Please enter a number (1 to 4): 1
 Sorry. The correct answer is: An instance of a class
 
 Player 1, Huimei1, eraned 2 point(s).
 Player 2, Huimei2, eraned 1 point(s).
 Player 1, Huimei1, is the winner.
 
 Please enter first name of player1
 #
 Please enter first name of player2
 #
 Program ended with exit code: 0
 
 */

