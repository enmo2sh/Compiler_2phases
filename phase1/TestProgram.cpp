#include "TestProgram.h"
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <regex>
#include <iterator>

using namespace std;
ofstream file;

TestProgram::TestProgram()
{

}

bool split_spc (int i, string str){
     if (i==0 || i == str.length()-1) return 0;
     return (isdigit(str[i-1]) ||isalpha(str[i-1])) && (isdigit(str[i+1]) ||isalpha(str[i+1]));
}

string removeSpaces(string str){
	string new_str="";
	for (int i = 0; i<str.length(); i++) {
		if (str.at(i) != ' ' || (str.at(i) == ' ' && split_spc(i, str)) )
			new_str.push_back(str.at(i));
	}
	return new_str;
}

pair<bool,string> check_regex(string x, map<string, int> next){
    pair<bool, string> output = {false,""};
    for (auto item : next)
    {
        string y = "["+item.first+"]";
        regex temp (y);
        if (regex_match(x, temp)) // matched
        {
            output.first = true;
            output.second += item.first;
            break;
        }
    }
    return output;
}

void TestProgram :: validation(int line_num, map<int, DFA_Graph> graph, string word,vector <char> punctuation, vector <string> keyWords, vector<string>*Result_Tokens ) {
    int state_id = 1;
    int last_accepted_state = 0; //id of accepted
    int last_state; // last id reached
    bool flag = true;
    int new_start = 0;
    string temp="";
    for (int i = 0; i < word.size(); i++)
    {
        map<string, int> next = graph[state_id].next_state;
        temp="";
        temp+= word[i];

        pair<bool, string> result = check_regex(temp, next);
        if (result.first) //found the char in DFA.
        {
            if (graph[next[result.second]].acceptance_state){
                    last_accepted_state = next[result.second];
                    new_start = i+1 ;
            }

            last_state=next[result.second];
            state_id=next[result.second];
        }
        else
        {
            flag = false;
            if (i == 0){
                if(find(punctuation.begin(), punctuation.end(), temp[0]) != punctuation.end()){
                    (*Result_Tokens).push_back(temp);
                    file << temp << endl;
                }else{
                    temp = "ERROR on line " + line_num;
                    (*Result_Tokens).push_back(temp);
                    file <<"ERROR on line " << line_num<<endl;
                }if (i+1 < word.length()){
                    validation(line_num, graph,  word.substr(i+1),punctuation,keyWords,Result_Tokens);
                    return;
                }else
                    return;
            }else{

                if(find(keyWords.begin(), keyWords.end(), temp) != keyWords.end()){
                    (*Result_Tokens).push_back(temp);
                    file << temp << endl;
                }
                else if (last_accepted_state > 0){
                    temp = graph[last_accepted_state].name;
                    (*Result_Tokens).push_back(temp);
                    file <<temp << endl;
                }
                validation(line_num, graph,  word.substr(new_start ),punctuation,keyWords,Result_Tokens);
                return;
            }
        }
    }
    if (flag&&last_accepted_state==last_state)
    {
        temp = graph[last_accepted_state].name;
        (*Result_Tokens).push_back(temp);
        file <<temp<< endl;
    }
}

vector<string> TestProgram :: Parse(int line_num, map<int, DFA_Graph> graph, vector <char> punctuation, vector <string> keyWords, string splitted ){
    file.open("output.txt", ofstream::app);
    vector<string> result;
    if (count (punctuation.begin(), punctuation.end(), splitted[0])){
        file << splitted << endl;
        result.push_back(splitted);
    }
    else if (count (keyWords.begin(),keyWords.end(), splitted)){
        file << splitted << endl;
        result.push_back(splitted);
    }
    else
        validation(line_num, graph,splitted,punctuation,keyWords,&result);

    file.close();
    return result;
}


void TestProgram :: split(int line_num, string program, vector <char> punctuation, vector <string> keyWords , vector<pair<string,int>>* words) {
    string token;
    for (int i =0; i < program.length(); i++){
        if (program[i] == ' '){
            if(token.size()>0){
                (*words).push_back({token,line_num});
                token = "";
            }
        }else if (count(punctuation.begin(), punctuation.end(), program[i])){
            if(token.size()>0){
                (*words).push_back({token,line_num});
                token = "";
            }

            (*words).push_back({token+program[i],line_num});
            token = "";
        }else{
            token += program[i];
            if ( i == program.length()-1)
                (*words).push_back({token,line_num});
        }
    }
}

