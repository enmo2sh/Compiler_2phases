#ifndef GENERATE_TABLE_H
#define GENERATE_TABLE_H
#include "generate_follow.h"
#include <bits/stdc++.h>
using namespace std;

class generate_table
{
    public:
        generate_table();
        map<string,map<string,string>> Parsing_Table;
        map<string,map<string,string>> get_Parsing_Table(map<string,vector<pair<string,string>>> First, map <string,vector<string>> Follow);

    protected:

    private:
};

#endif // GENERATE_TABLE_H
