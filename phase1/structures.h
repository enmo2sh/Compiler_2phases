#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <bits/stdc++.h>
using namespace std;

struct Transition{
    struct state* next ;
    string input_symbol;
};

struct  copied_state{
    state * related ;
};
// transition. first ---- transitions.next
// transition . second  ---- transitions.input_symbol

struct state{
    int id = 0;
    copied_state cpd;
    bool accepted = false;
    string accepted_language = "";
    int priority = 0;
    vector<Transition> transitions ;
};

struct automata{
    state* start = new state;
    state* end_  = new state;
};

class structures
{
    public:
        structures();


    protected:

    private:
};

#endif // STRUCTURES_H
