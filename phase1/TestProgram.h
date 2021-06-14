#include <iostream>
#include <vector>
#include <map>
#include "minimization.h"
#include <bits/stdc++.h>
#ifndef TESTPROGRAM_H
#define TESTPROGRAM_H
using namespace std;
class TestProgram
{
    public :
        TestProgram();
        void split (int line_num, string program, vector <char> punctuation, vector <string> keyWords, vector<pair<string,int>>* words);
        void validation(int line_num, map<int, DFA_Graph> graph, string word,vector <char> punctuation, vector <string> keyWords,vector<string>*Result_Tokens);
        vector<string> Parse(int line_num, map<int, DFA_Graph> graph, vector <char> punctuation, vector <string> keyWords, string splitted );
    protected:
    private:
};
#endif
