#ifndef PARSE_GRAMMAR_H
#define PARSE_GRAMMAR_H
#include <bits/stdc++.h>
using namespace std;
class parse_grammar
{
    public:
        parse_grammar();
        static parse_grammar* getInstance();
        vector <string> ordered_follow;
        map<string,vector<pair<string,string>>> First;
        map<string,pair<vector<pair<string,string>>,vector<string>>> helper_Follow;

        string extract_from_line(string line);
        vector <string> get_ordered_follow();
        vector<string> splits(string str, string del);
        map<string,vector<pair<string,string>>> get_first();
        void prepare_follow (string LHS ,vector<string> tokens);
        map<string,pair<vector<pair<string,string>>,vector<string>>> get_helper_Follow();

    protected:

    private:
};

#endif // PARSE_GRAMMAR_H
