#ifndef CALC_RGX_H
#define CALC_RGX_H
#include "structures.h"
#include "NFA.h"

class calc_rgx
{
    public:
        calc_rgx();
    NFA nfa;
    int find_language(string lang,vector<pair<string,automata> > Languages);
    bool is_operator(char c);
    int priority(char op);
    automata applyOp(automata* a, automata* b, char op, state* start, state* ed);
    automata language_NFA (string rgx,vector<pair<string,automata> > Languages);
    void  dfs(state* st, state* cpd,  state* helper);
    automata  start_copy(automata n);
    automata combine (vector <pair<string,automata>> patterns,state* s);
    protected:

    private:
};

#endif // CALC_RGX_H
