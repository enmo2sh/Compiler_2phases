#include "parse_rules.h"
#include <bits/stdc++.h>

parse_rules::parse_rules()
{

}

bool is_closure(char c){
    if(c=='+' || c=='*' || c=='.')
        return true;
    return false;
}

bool is_AndOr(char c){
    if(c=='|' || c==' ')
        return true;
    return false;
}

bool split_space (int i, string str){
     if (i==0 || i == str.length()-1) return 0;
     return isalpha(str[i-1]) && isalpha(str[i+1]);
}

string parse_rules::removeSpaces(string str){
	string new_str="";
	for (int i = 0; i<str.length(); i++) {
		if (str.at(i) != ' ' || (str.at(i) == ' ' && split_space(i, str)))
			new_str.push_back(str.at(i));
	}
	new_str.push_back ('\0');
	return new_str;
}

string parse_rules::removeExtraSpaces(string str){
	string new_str="";
	for (int i = 0; i<str.length(); i++) {
		if (str.at(i) != ' ' )
			new_str.push_back(str.at(i));
        else{
            if(i>0 && (i < str.length()-1)){
                if(str.at(i-1)==')' || ((str.at(i-1)=='E' || str.at(i-1)=='L')&&!is_AndOr(str.at(i+1)))
                || (str.at(i+1)=='(' && str.at(i-1)!='=' && str.at(i-1)!=':') ||(is_closure(str.at(i-1))&& !is_AndOr(str.at(i+1))) || split_space(i,str) )
                    new_str.push_back(str.at(i));
            }
        }
	}
	return new_str;
}

vector<string> parse_rules::splits(string str, string del){
	vector<string> result;
	int start = 0;
	int end = str.find(del);
	while (end != -1) {
		result.push_back(str.substr(start, end - start));
		start = end + del.size();
		end = str.find(del, start);
	}
	result.push_back(str.substr(start, end - start));
	return result;
}


