#include "parse_rules.h"
#include "TestProgram.h"
#include "structures.h"
#include "calc_rgx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#ifndef INPUT_RULES_H
#define INPUT_RULES_H


class input_rules
{
    public:
        input_rules();
        parse_rules parse;
        calc_rgx cal;
        TestProgram tp;
        vector<pair<string,automata> > Languages;
        vector <pair<string,automata> > patterns;
        vector <string> keyWords;
        vector <char> punctuation;
        vector <pair<string,int>> words;
        vector <string> main_tokens;
        map<int, DFA_Graph> Final_Graph;
        void extract(string line);
        void generate_automatas();
        string get_next_token();

    protected:

    private:
};

#endif // INPUT_RULES_H

