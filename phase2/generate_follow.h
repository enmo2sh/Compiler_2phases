#ifndef GENERATE_FOLLOW_H
#define GENERATE_FOLLOW_H
#include "parse_grammar.h"
#include <bits/stdc++.h>

class generate_follow
{
    public:
        generate_follow();
        map<string,vector<string>> follow;

        map<string,vector<string>> get_follow(parse_grammar parse);

    protected:

    private:
};

#endif // GENERATE_FOLLOW_H
