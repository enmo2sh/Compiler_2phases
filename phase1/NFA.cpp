#include "NFA.h"
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

NFA::NFA()
{
    //ctor
}


automata NFA::basic_NFA (string a, automata base){
    base.start->id = cnt++;
    base.end_->id = cnt++ ;
    base.start->transitions.push_back({(base.end_), a});

    return base;
}

automata NFA::and_NFA (automata* automata1, automata* automata2){
    automata1-> end_->transitions.push_back({(automata2->start),"\\L" });
    automata result;
    result.start =  automata1->start;
    result.end_ = automata2->end_;
    return result;
}


automata NFA::or_NFA (automata* automata1, automata* automata2, state* new_start, state* new_end){
    new_start->id = cnt++;
    new_end->id = cnt++;
    new_start->transitions.push_back({(automata1->start), "\\L"});
    new_start->transitions.push_back({(automata2->start), "\\L"});
    automata1->end_->transitions.push_back({(new_end), "\\L"});
    automata2->end_->transitions.push_back({(new_end), "\\L"});

    automata result;
    result.start = new_start;
    result.end_ = new_end;
    return result;
}

automata NFA::Closure(automata * automata1, state* new_start, state* new_end, char c){
    new_start->id = cnt++;
    new_end->id = cnt++;
    automata result;
    automata1->end_->transitions.push_back({(automata1->start), "\\L"});  //positive & kleene
    new_start->transitions.push_back({(automata1->start), "\\L"});
    automata1->end_->transitions.push_back({new_end, "\\L"});
    if (c == '*')
        new_start->transitions.push_back({new_end, "\\L"});
    result.start = new_start;
    result.end_ = new_end;
    return result;
}

automata NFA::combined_NFA(vector <pair<string,automata>> patterns, state* new_start){
    automata result;
    new_start->id = cnt++;
    for (int p=0;p<patterns.size();p++){
         state *temp = patterns[p].second.end_;
         temp->accepted = true;
         temp->accepted_language = patterns[p].first;
         temp->priority = p+1;
         new_start->transitions.push_back({(patterns[p].second.start), "\\L"});
    }
    result.start = new_start;
    return result;
}
