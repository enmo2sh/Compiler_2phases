#ifndef NFA_H
#define NFA_H
#include "structures.h"
#include <bits/stdc++.h>
using namespace std;


class NFA
{
    public:
        NFA();

    int cnt =0;
    automata basic_NFA (string a, automata base);
    automata and_NFA (automata * automata1, automata *automata2);
    automata or_NFA (automata * automata1, automata * automata2, state* new_, state* _end);
    automata Closure(automata * automata1, state* new_, state* _end, char c);
    automata combined_NFA(vector <pair<string,automata>> patterns, state* new_);


};

#endif // NFA_H
