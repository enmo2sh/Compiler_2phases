#ifndef LEFT_FACTORING_H
#define LEFT_FACTORING_H
#include "parse_grammar.h"
#include <bits/stdc++.h>
using namespace std;

class Left_Factoring
{
    public:
        Left_Factoring();
        map <string, string> new_production;


        map <string, string> get_new_production();
        bool check_left_fact(vector <vector<int>> common);
        bool left_factoring(string line, parse_grammar parse);
        string longest_common_prefix (vector<int> group, vector<string> productions);
        vector <vector<int>> common_prefix(vector<string> productions, parse_grammar parse);

    protected:

    private:
};

#endif // LEFT_FACTORING_H
