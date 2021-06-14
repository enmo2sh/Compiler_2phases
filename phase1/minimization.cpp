#include <iostream>
#include"minimization.h"
#include <map>
#include <set>

using namespace std;

map<int, DFA_Graph> minimize_graph(map<int, DFA_Graph> graph){
    vector<set<int>> equivalent_states = table_filling(graph);
    map<int, DFA_Graph> new_graph = minimized(graph, equivalent_states);
    return new_graph;
}

vector<set<int>> table_filling(map<int, DFA_Graph> graph){
    int states_no = graph.size();
    //table to do minimization through
    int table[states_no-1][states_no-1];
    memset(table,0,sizeof table);
    //array where indx+1 represents state id
    //& its value represents whether it is an accepting state or not
    int accepting[states_no+1];

    map<int, DFA_Graph>::iterator itr;
    for(itr = graph.begin(); itr !=  graph.end(); ++itr)
        accepting[itr->first] = itr->second.acceptance_state;
    //states from 0 to states_no-2 -> columns -> column + 1 "state id"
    //states from 1 to states_no-1 -> rows -> row+2 "state id"

    //looping through this table only need to check the lower triangular
    //mark all transition between accepting & notaccepting as invalid transitions
    for(int i=0; i<states_no-1; i++){
        for(int j=0; j<=i; j++){
            if(accepting[i+2]!=accepting[j+1])
                table[i][j] = -1;
            else{
                string str1 = get_pointer_id(i+2, graph);
                string str2 = get_pointer_id(j+1, graph);
                if(str1.compare(str2) != 0)
                    table[i][j] = -1;
            }

        }
    }
    //construct the table
    int flag = 1;
    while(flag){
        flag = 0;
        for(int i=0; i<states_no-1; i++){
            for(int j=0; j<=i; j++){
                if(table[i][j]==0){
                    int id1 = i+2;
                    int id2 = j+1;
                    map<string, int> transition1 = graph[id1].next_state;
                    map<string, int> transition2 = graph[id2].next_state;
                    if(transition1.size()!=transition2.size()){
                        table[i][j] = -1;
                        flag = 1;
                    }
                    else{
                        map<string, int>::iterator itr;
                        for(itr =  transition1.begin(); itr !=  transition1.end(); ++itr){
                            string input_symbol = itr->first;
                            int next_state_id1 = itr -> second;
                            if(transition2.count(input_symbol)==0){
                                table[i][j] = -1;
                                flag = 1;
                                break;
                            }
                            else{
                                int next_state_id2 = transition2[input_symbol];
                                int x = max(next_state_id1, next_state_id2)-2;
                                int y = min(next_state_id1, next_state_id2)-1;
                                if(table[x][y] == -1){
                                    table[i][j] = -1;
                                    flag = 1;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    //get equivalent states that has value 0 in the table
    vector<set<int>> equivalent_states;
    for(int i=0; i<states_no-1; i++){
        for(int j=0; j<=i; j++){
            //two states are equivalent
            if(table[i][j] == 0)
                join_states(equivalent_states, i+2, j+1);
        }
    }
    return equivalent_states;
}


void join_states(vector<set<int>> &equivalent_states, int id1, int id2){
    if(equivalent_states.size()==0){
        set<int> s;
        s.insert(id1);
        s.insert(id2);
        equivalent_states.push_back(s);
        return;
    }

    for(int i=0; i < equivalent_states.size(); i++){
        if(equivalent_states[i].count(id1) > 0)
            equivalent_states[i].insert(id2);
        else if(equivalent_states[i].count(id2) > 0)
            equivalent_states[i].insert(id1);
        else{
            set<int> s;
            s.insert(id1);
            s.insert(id2);
            equivalent_states.push_back(s);
        }
    }
}

map<int, DFA_Graph> minimized(map<int, DFA_Graph> graph, vector<set<int>> equivalent_states){
    int basic_id, removed_id;
    for(int i=0; i<equivalent_states.size(); i++){
        int indx = 0;
        for(auto item : equivalent_states[i]){
            if(indx == 0){
                basic_id = item;
                indx++;
            }
            else{
                removed_id = item;
                graph.erase(removed_id);
                map<int, DFA_Graph>::iterator itr1;
                map<string, int>::iterator itr2;
                for(itr1 =  graph.begin(); itr1 !=  graph.end(); ++itr1){
                    for(itr2 = itr1->second.next_state.begin(); itr2 != itr1->second.next_state.end(); ++itr2){
                        if(itr2->second == removed_id)
                            itr2->second = basic_id;
                    }
                }
            }
        }
    }
    return graph;
}


string get_pointer_id(int id, map<int, DFA_Graph> graph){
    map<int, DFA_Graph>::iterator itr1;
    for(itr1 =  graph.begin(); itr1 !=  graph.end(); ++itr1){
        if(itr1->first == id){
            return itr1->second.name;
        }
    }
}

