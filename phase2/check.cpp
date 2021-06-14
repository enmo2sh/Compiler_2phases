#include "check.h"

vector<string> Split_Word(string str)
{
    vector<string> v;
    istringstream ss(str);
    string word; // for storing each word
    while (ss >> word)
    {
        if(word[0]=='\'')
            word.erase(remove(word.begin(), word.end(), '\''), word.end());
        v.push_back(word);
        //cout << word << "\n";
    }
    return v;
}

int get_space(stack<string> main){
    int c = 0;
    while(main.size()>0){
        c = c + (main.top()).size() + 1;
        main.pop();
    }
    return c;
}

void Parser_Handle(map<string,map<string,string>> Parsing_Table,stack<string>* Main_Stack,string One_Token)
{
    bool flag =true;
    bool accept = true;
    while(flag)
    {
        stack<string> temp = *Main_Stack;
        //print the stack
        while(temp.size()>0){
            temp.pop();
        }

        string Top =(*Main_Stack).top();
        //stack & tokens are empty
        if(One_Token == "$" && (Top == "$" )){
            if(accept)
                cout<<" accept\n";
            else
                cout<<" not accept\n";
            return;
        }

        //check if TOP is terminal or not
        auto it = Parsing_Table.find(Top);
        if ( it != Parsing_Table.end() ) {
            // exists in parsing_table, Non terminal
            auto search_terminal = Parsing_Table[Top].find(One_Token);
            //there is entry in the parsing table for this non-terminal
            if (search_terminal != Parsing_Table[Top].end()){
                string Production = Parsing_Table[Top][One_Token];
                if(Production=="synch"){
                    (*Main_Stack).pop();
                    cout<<" Ignore Error:(illegal "<<Top<<")"<<endl;
                }
                else{

                    cout<<" "<<Top << " --> "<<Production<<endl; //output.
                    //replace the non-terminal with corresponding production

                    (*Main_Stack).pop();
                    vector<string> Words_Vector=Split_Word(Production);
                    int i=Words_Vector.size();
                    while(i--){
                        if(Words_Vector[i] != "\\L")
                            (*Main_Stack).push(Words_Vector[i]);
                    }
                }
            }
            //the entry is empty
             else{
                 cout<<" Error:(illegal "<<Top<<") - discard "<<One_Token<<endl; //discard token and take another one.
                 flag = false;
             }

        }
        else {
           // terminal
            if(Top == One_Token){
                cout<<" "<<Top << " match!" << "\n"; //element Matched.
                //take next Token .
                flag = false;
            }
            else{
                cout<<" Error: missing "<<Top<<", inserted"<<endl; //Report Error.
                if(One_Token != "$")
                    accept = false;
            }
            //take next Token.
            (*Main_Stack).pop();
        }
    }
}
