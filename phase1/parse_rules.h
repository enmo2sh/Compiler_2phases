#ifndef PARSE_RULES_H
#define PARSE_RULES_H
#include <bits/stdc++.h>
using namespace std;
class parse_rules
{
    public:
        parse_rules();


    string removeSpaces(string str);
    string removeExtraSpaces(string str);
    vector<string> splits(string str, string del);
};

#endif // PARSE_RULES_H
