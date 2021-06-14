#include <iostream>
#include <fstream>
#include "parse_grammar.h"
#include "left_factoring.h"
#include "generate_follow.h"
#include "generate_table.h"
#include "check.h"
#include "../phase1/input_rules.h"
#include <bits/stdc++.h>

using namespace std;
using std::ifstream;
parse_grammar parse2;
generate_follow follower;
Left_Factoring left_fact;
generate_table gtable;

input_rules ip;

void print(map<string,vector< pair<string,string>>> First){
    map<string,vector< pair<string,string>>>::iterator itr;
    for (itr = First.begin(); itr != First.end(); ++itr) {
        for(int i=0;i<itr->second.size();i++){
            cout << " "<<itr->first << '\t' ;
            cout << itr->second[i].first << '\t' << itr->second[i].second <<'\n';
        }
        cout<<'\n'<<"-------------------------------------------------------"<<'\n';
    }
}

vector<string> Left_Recursion(string line){
    line.erase(0,2);
    vector<string> result;
    vector<string> parts = parse2.splits(line," = ");
    vector<string> productions = parse2.splits(parts[1],"|");
    int has_left_recursion = -1;
    for(int i=0;i<productions.size();i++){
        vector<string> temp = parse2.splits(productions[i]," ");
        if(temp[0]==parts[0]){
            has_left_recursion = i;
            break;
        }
    }
    if(has_left_recursion == -1){       // no left recursion in this production
        result.push_back(line);
        return result;
    }
    string new_nonTerminal = parts[0] + "~";
    productions[has_left_recursion].erase(0,parts[0].length()+1);
    string new_line = new_nonTerminal + " = " + productions[has_left_recursion] + " " + new_nonTerminal + " | \\L";
    string old_line = parts[0] + " = ";
    for(int j=0;j<productions.size();j++){
        if(j != has_left_recursion){
            old_line += productions[j] + " " + new_nonTerminal ;
            old_line += " | ";
        }
    }
    old_line.erase(old_line.length()-3,3);      // to remove last or
    result.push_back(new_line);
    result.push_back(old_line);
    return result;
}

string fix_left_recursion (string line){
    vector <string> lines = Left_Recursion(line);
        string grammar;
        for(int i=0;i<lines.size();i++){
            grammar = parse2.extract_from_line(lines.at(i));
        }
    return grammar;
}

void fix_left_factoring (){
    map <string, string> my_m =left_fact.get_new_production();
    for (auto itr = my_m.rbegin(); itr != my_m.rend(); ++itr)
        fix_left_recursion(itr->second);
}

string readFile(char *fileName){
    string start_grammar = "";
    char c;
    string line ;
    ifstream myFile(fileName,std::ios::ate);
    std::streampos size = myFile.tellg();
    for(int i=1;i<=size;i++){
        myFile.seekg(-i,std::ios::end);
        myFile.get(c);
        if(c=='\n'){
            if(line[0]=='#'){
                if (left_fact.left_factoring(line, parse2)){
                    fix_left_factoring();           //fix left_factoring then fix left_recursion
                }else{
                    fix_left_recursion (line);
                }
                line = "";
            }
        }
        else
            line = c + line;
    }

     if (left_fact.left_factoring(line, parse2)){
        fix_left_factoring();                      //fix left_factoring then fix left_recursion
    }else{
        start_grammar = fix_left_recursion (line);
    }
    return start_grammar;
}

void print_follow (map<string,vector<string>> follow){
    for (auto m: follow ){
       cout <<" "<< m.first<< "                      ";
       for (auto v: m.second){
            cout << v <<" ";
       }
        cout << endl;
   }
}

void print_table (map<string, map<string,string>> Parsing_Table){
   cout<<endl<<" ***************************"<<endl;
   cout<<"     Parsing Table is:" <<endl;
   cout<<" ***************************"<<endl<<endl;
   map<string, map<string, string>>::iterator i;
   map<string, string>::iterator itr;
   for(i = Parsing_Table.begin(); i != Parsing_Table.end(); ++i){
        cout << " "<<i-> first << '\n';
        cout <<" ----------------------- "<<endl;
        cout <<'\t' << "Terminal" <<'\t' <<"Derivation"<<endl;
        for (itr = i->second.begin(); itr != i->second.end(); ++itr) {
            cout << '\t' << itr->first<< '\t'<<'\t' << itr->second << '\n';
        }
    }
}

void generate_final_output(string start_grammar, map<string,map<string,string>> Parsing_Table ){
    cout<<endl<<"************************ Output ****************************\n";
    //check the tokens:
    stack<string> Main_stack;
    Main_stack.push("$");
    Main_stack.push(start_grammar);

    string token = ip.get_next_token() ;
    while(token != "$"){
       Parser_Handle(Parsing_Table, &Main_stack, token);
       token = ip.get_next_token();
    }
    Parser_Handle(Parsing_Table, &Main_stack, "$");
}

int main(){
   string start_grammar = readFile("grammar.txt");
   cout <<"--------------------------------------------------------------------"<<endl;
   map<string,vector<pair<string,string>>> first = parse2.get_first();
   //print(first);

   map<string,vector<string>> follow = follower.get_follow(parse2);
  // print_follow(follow);

   map<string,map<string,string>> Parsing_Table = gtable.get_Parsing_Table(first,follow);
   print_table(Parsing_Table);

   ip.generate_automatas();

   generate_final_output(start_grammar, Parsing_Table);


   return 0;
}
