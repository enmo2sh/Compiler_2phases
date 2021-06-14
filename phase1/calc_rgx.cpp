#include "calc_rgx.h"
#include <bits/stdc++.h>
#include "structures.h"
using namespace std;
calc_rgx::calc_rgx()
{
}
bool vis[1000];
void display_ (state st){
    vis[st.id] = 1;
    for (auto edg: st.transitions){
           cout << std::left;
           cout << std::setw(4) << st.id <<"    "<< (edg.next)->id <<"     " << edg.input_symbol  <<endl;
        if (!vis[edg.next->id]){
            display_ (*(edg.next));
        }
    }
}

void display_NFA(automata automata){
    cout <<"        ..... "<<endl;
    cout <<"        |NFA| "<<endl;
    cout <<"        ..... "<<endl;
    printf("FROM    TO    INPUT\n" );
    display_(*automata.start);
    memset(vis, 0, sizeof(vis));
    cout <<"-----------------------------\n"<<endl;
}
int calc_rgx::find_language(string lang,vector<pair<string,automata> > Languages){
    for(int x=0;x<Languages.size();x++){
        if(Languages[x].first == lang)
            return x;
    }
    return -1;
}

bool calc_rgx::is_operator(char c){
    if(c=='|' || c==' ' || c=='+' || c=='*' || c=='(' || c==')')
        return true;
    return false;
}

int calc_rgx::priority(char op){
    if(op == '|')
        return 1;
    if(op == ' ')
        return 2;
    if(op == '*'||op == '+')
        return 3;
    return 0;
}

bool v [1000];
void calc_rgx:: dfs(state* st, state* cpd, state* helper_end){
    v[st->id] = 1;
    st->cpd.related = new state;
    for (auto trs: st->transitions){
        state* help = new state;
        st->cpd.related = cpd;
        if (trs.next->transitions.size()==0){
            if (!v[trs.next->id]){
                help->id = nfa.cnt++;
                *(helper_end) = *(help);
            }
            cpd->transitions.push_back({helper_end, trs.input_symbol});
            v[trs.next->id] = 1;
            continue;
        }
        if (!v[trs.next->id]){
            help->id = nfa.cnt++;
            cpd->transitions.push_back({help, trs.input_symbol});
            dfs(trs.next, help, helper_end);
        }else {
            cpd->transitions.push_back({(trs.next->cpd).related, trs.input_symbol});
        }
    }

}

automata calc_rgx:: start_copy(automata n){
    state * cp =  new state;
    state *helper_end = new state;
    cp->id = nfa.cnt++;
    dfs(n.start, cp, helper_end);
    memset(v, 0, sizeof(v));
    automata cpd;
    cpd.start = cp;
    cpd.end_ = helper_end;
    return cpd;
}

automata calc_rgx::applyOp(automata* a, automata* b,char op, state* s, state* e){
    switch(op){
        case ' ': return nfa.and_NFA (a, b);
        case '|': return nfa.or_NFA (a, b, s, e);
        case '*': return nfa.Closure(a, s, e, op);
        case '+': return nfa.Closure(a, s, e, op);
    }
}

automata calc_rgx::language_NFA (string rgx,vector<pair<string,automata> > Languages){
    stack <automata> automatas;
    stack <char> ops;
    int i;
    for(i=0;i<rgx.length();i++){
        if(rgx[i] == '('){
            ops.push(rgx[i]);
        }
        else if (!is_operator(rgx[i]) ||(is_operator(rgx[i]) && rgx[i-1]=='\\')){
            string  name = "";
            bool flag = false;
            int indx_of_slash = 0;
            while(i < rgx.length() && (!is_operator(rgx[i]) ||(is_operator(rgx[i]) && rgx[i-1]=='\\'))){
                if(rgx[i]!='\\' )
                    name.push_back (rgx[i]);
                else{
                    if(rgx[i+1]=='L')
                        name.push_back (rgx[i]);
                    else{
                        flag = true;
                        indx_of_slash = name.length();
                    }
                }
                i++;
            }
            int temp = find_language(name,Languages);
            automata  n;
            if(temp == -1){
                if(!flag || name.length()==1){
                    automata base;
                    n = nfa.basic_NFA(name, base);
                }
                else{
                    automata base1,base2,n1,n2;
                    n1 = nfa.basic_NFA(name.substr(0,indx_of_slash),base1);
                    n2 = nfa.basic_NFA(name.substr(indx_of_slash,name.length()-1),base2);
                    n = nfa.and_NFA(&n1,&n2);
                }

            }else{
                n =Languages[temp].second;
                n = start_copy(n);
            }
            automatas.push(n);
            i--;

        }
        else if(rgx[i] == ')'){
            while(!ops.empty() && ops.top() != '('){
                automata auto1;
                automata auto2;
                state *s = new state;
                state *e = new state;
                if(ops.top()==' ' || ops.top()=='|'){
                    auto2 = automatas.top();
                    automatas.pop();
                }

                auto1 = automatas.top();
                automatas.pop();

                char op = ops.top();
                ops.pop();
                automata res = applyOp(&auto1, &auto2, op, s, e);
                automatas.push(res);
            }
            // pop opening brace.
            if(!ops.empty())
               ops.pop();
        }
        else{
            while(!ops.empty() && priority(ops.top())>= priority(rgx[i])){
                automata auto1;
                automata auto2;
                state *s = new state;
                state *e = new state;
                if(ops.top()==' ' || ops.top()=='|'){
                    auto2 = automatas.top();
                    automatas.pop();
                }

                auto1 = automatas.top();
                automatas.pop();
                char op = ops.top();
                ops.pop();

                automata res = applyOp(&auto1, &auto2, op, s, e);
                automatas.push(res);
            }
            ops.push(rgx[i]);
        }

    }
    while(!ops.empty()){
        automata auto1, auto2;
        state *s = new state;
        state *e = new state;
        if(ops.top()==' ' || ops.top()=='|'){
                auto2 = automatas.top();

                automatas.pop();
        }

        auto1 = automatas.top();
        automatas.pop();

        char op = ops.top();
        ops.pop();

        automata res = applyOp(&auto1, &auto2, op, s, e);

        automatas.push(res);
    }
    return automatas.top();
}

automata calc_rgx::combine (vector <pair<string,automata>> patterns,state* s){
    return nfa.combined_NFA(patterns,s);
}
