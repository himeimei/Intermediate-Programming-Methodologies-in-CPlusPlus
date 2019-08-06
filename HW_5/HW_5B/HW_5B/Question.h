//  HW_5B
//
//  Created by Huimei Wu on 11/10/17.
//

#ifndef Question_h
#define Question_h

#include <string>

using namespace std;

const int SIZE = 4;

class Question
{
private:
    string question;
    string answers[SIZE];
    string answerKey;
public:
    Question();
    void setQuestion(string question);
    void setAnswer(int index, string answer);
    void setAnswerKey(string);
    void shuffleAnswers();
    
    
    string getQuestion() const
    { return question; }
    
    string getAnswer(int index) const
    { return answers[index]; }
    
    string getAnswerKey() const
    { return answerKey; }
};

#endif /* Question_h */



