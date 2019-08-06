//  HW_5B
#include "Question.h"

#include <iostream>      // Needed for cout
#include <cstdlib>       // Needed for the exit function
using namespace std;

//***********************************************************
// The default constructor.                                 *
//***********************************************************

Question::Question()
{
}

//***********************************************************
// setWidth sets the value of the member variable width.    *
//***********************************************************

void Question::setQuestion(string question)
{
    this->question = question;
}

//***********************************************************
// setLength sets the value of the member variable length.  *
//***********************************************************

void Question::setAnswer(int index, string answer)
{
    this->answers[index] = answer;
}

//***********************************************************
// setLength sets the value of the member variable length.  *
//***********************************************************

void Question::setAnswerKey(string answerKey)
{
    this->answerKey = answerKey;
}

void Question::shuffleAnswers()
{
    for (int i=0; i<SIZE; i++)
    {
        int index = rand() % SIZE;
        
        // swap answers in the array
        string temp = answers[i];
        answers[i]=answers[index];
        answers[index]=temp;
    }
}
