#include "input_rules.h"
#include "parse_rules.h"
#include "minimization.h"
#include "TestProgram.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

input_rules::input_rules()
{
}

bool visit[1000];
void display (state st){
    visit[st.id] = 1;
    for (auto edg: st.transitions){
        cout << std::setw(4) << st.id <<"       "<< (edg.next)->id<< "       ";
        cout << std::setw(4) << edg.input_symbol << "       "<<(edg.next)->accepted<<"   ";
        cout << std::setw(4) <<(edg.next)->accepted_language <<endl;
        if (!visit[edg.next->id]){
            display (*(edg.next));
        }
    }
}

void display_compined_NFA(automata automata){
    cout <<"        ...................."<<endl;
    cout <<"        |Final Combined NFA|"<<endl;
    cout <<"        ...................."<<endl;
    cout << std::left;
    cout << "FROM       TO       INPUT       Accepted\n" ;
    display(*automata.start);
    memset(visit, 0, sizeof(visit));
    cout <<"-----------------------------\n"<<endl;
}

void input_rules :: extract(string line) {
	vector<string> parts;
	if ((line.find('=') < line.length()) && (line.at(line.find('=')-1) != '\\') && !(line.find(':') < line.length())){
        line = parse.removeExtraSpaces(line);
		parts = parse.splits(line, "=");
		automata a ;
		a = cal.language_NFA(parts[1],Languages);
		Languages.push_back({parts[0],a});
	}else if (line.find(':') < line.length()) {
		line = parse.removeExtraSpaces(line);
		parts = parse.splits(line, ":");
		automata a ;
		a = cal.language_NFA (parts[1],Languages);
		patterns.push_back({parts[0],a});
	}
	else if(line[0]=='{'){
		line.erase(remove(line.begin(), line.end(), '{'), line.end());
		line.erase(remove(line.begin(), line.end(), '}'), line.end());
		parts = parse.splits(line, " ");
		for (int i = 0;i < parts.size(); i++) {
				keyWords.push_back(parts[i]);
		}
	}else if(line[0]=='['){
        line = parse.removeSpaces(line);
		line.erase(remove(line.begin(), line.end(), '['), line.end());
		line.erase(remove(line.begin(), line.end(), ']'), line.end());
		line.erase(remove(line.begin(), line.end(), ' '), line.end());
		for (int i = 0;i < line.size();i++) {
                if (line[i]!='\\' || (line[i]=='\\'  && line[i+1] == '\\' )){
                    punctuation.push_back(line[i]);
                }
		}
	}

}

void input_rules:: generate_automatas(){
	fstream my_file;
	my_file.open("rules.txt", ios::in);

	if (!my_file)
		cout << "No such file";
	else {
		string line;
		while (getline(my_file, line)) { //read data from file object and put it into string.
			extract(line);
		}
	}
	my_file.close();
	state *s=new state ;
	automata final_result = cal.combine(patterns,s);

    Final_Graph = Subset_Construction(final_result.start);
    int line_num = 0;
    my_file.open("test.txt", ios::in);
    if (!my_file)
		cout << "No such file";
    else {
		string line;
		while (getline(my_file, line)){
           line_num++;
           tp.split(line_num, line, punctuation, keyWords,&words);
		}
	}

	my_file.close();

}

string input_rules:: get_next_token(){
    string next_token;
    if(main_tokens.size()>0){
        next_token = main_tokens.at(0);
        main_tokens.erase(main_tokens.begin());
    }
    else{
        if(words.size()>0){
            vector <string> result = tp.Parse(words.at(0).second, Final_Graph,punctuation, keyWords,words.at(0).first);
            words.erase(words.begin());
            main_tokens.insert(main_tokens.end(), result.begin(), result.end());
            next_token = main_tokens.at(0);
            main_tokens.erase(main_tokens.begin());
        }
        else
            next_token = "$";
    }
    if(next_token == "assign")
        return "=" ;
    return next_token;
}
