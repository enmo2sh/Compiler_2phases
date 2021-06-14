#include "parse_grammar.h"
#include <bits/stdc++.h>
#include <string>
parse_grammar::parse_grammar()
{
    //ctor
}

void parse_grammar:: prepare_follow (string LHS ,vector<string> tokens){
    int sz = tokens.size();
    for (int i =0; i < sz-1 ; i++){
        if(tokens[i][0]!='\'' && tokens[i]!="\\L"){
            helper_Follow[tokens[i]].first.push_back({tokens[i+1], LHS});
        }
    }
    if(tokens[sz-1][0]!='\'' && tokens[sz-1]!="\\L"){
        helper_Follow[tokens[sz-1]].second.push_back(LHS);
    }
}

string remove_extra_spaces(string temp){
    while (temp[temp.length()-1]==' ')
            temp.erase(temp.length()-1,1);
    while (temp[0]==' ')
        temp.erase(0,1);
        return temp;
}

vector<string> parse_grammar:: splits(string str, string del){
	vector<string> result;
	int start = 0;
	int end = str.find(del);
	string temp;
	while (end != -1) {
        temp = str.substr(start, end - start);
        temp = remove_extra_spaces(temp);

		result.push_back(temp);
		start = end + del.size();
		end = str.find(del, start);
	}
    temp = str.substr(start, end - start);
    temp = remove_extra_spaces(temp);
	result.push_back(temp);
	return result;
}

string parse_grammar:: extract_from_line(string line){
    cout << " "<<line<<endl;
    vector<string> parts = splits(line," = ");
    ordered_follow.push_back(parts[0]);
    vector<string> productions = splits(parts[1],"|");

    vector <pair<string,string>> temp ;
    for(int i=0;i<productions.size();i++){
        string prod = productions[i];
        vector<string> within_prod = splits(productions[i]," ");

        prepare_follow (parts[0] ,within_prod);
        if(within_prod[0].rfind("'",0)==0){    // terminal
            within_prod[0].erase(0,1);
            within_prod[0].erase(within_prod[0].length()-1,1);
            temp.push_back(make_pair(within_prod[0],prod));
        }
        else if (within_prod[0]=="\\L"){
            temp.push_back(make_pair("\\L",prod));
        }
        else{       //non terminal
            bool has_epsilon = true;
            int counter = 0;
            while(has_epsilon && counter < within_prod.size()){
                has_epsilon = false;
                if(within_prod[counter].rfind("'",0)==0){    // terminal
                    within_prod[counter].erase(0,1);
                    within_prod[counter].erase(within_prod[counter].length()-1,1);
                    temp.push_back(make_pair(within_prod[counter],prod));
                }
                else{
                    for(int p=0;p<First.find(within_prod[counter])->second.size();p++){
                        if(First.find(within_prod[counter])->second.at(p).first == "\\L")
                            has_epsilon = true;
                        else
                            temp.push_back(make_pair(First.find(within_prod[counter])->second.at(p).first,prod));
                    }
                    if(has_epsilon)
                        counter++ ;
                }
            }
            if(counter == within_prod.size())
                temp.push_back(make_pair("\\L",prod));
        }
    }
    First.insert({parts[0],temp});
    return parts[0];
}

map<string,vector<pair<string,string>>> parse_grammar::  get_first (){
    return First;
}

vector <string> parse_grammar:: get_ordered_follow(){
    return ordered_follow;
}

map<string,pair<vector<pair<string,string>>,vector<string>>> parse_grammar:: get_helper_Follow(){
    return helper_Follow;
}


