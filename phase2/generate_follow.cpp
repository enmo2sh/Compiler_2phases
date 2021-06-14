#include "generate_follow.h"

generate_follow::generate_follow()
{
    //ctor
}

bool contain_epslion(vector<pair<string,string>> vec){
    for (auto v : vec){
        if ( v.first == "\\L")
            return true;
    }
    return false;
}
void remove_duplicates (vector<string>* vec){
    set<string> s( vec->begin(), vec->end());
    vec->assign( s.begin(), s.end() );
}
void remove_eps_emptyStr (vector<string>* vec){
    for (auto v : *vec){
        if ( v == "\\L" || v == "")
            vec->erase(remove(vec->begin(), vec->end(), v), vec->end());
    }
}
string first( const pair<string, string> &p ) {
    return p.first;
}
map<string,vector<string>> generate_follow:: get_follow(parse_grammar parse){
    vector <string> ordered_follow = parse.get_ordered_follow();
    map<string,vector<pair<string,string>>> First = parse.get_first();
    map<string,pair<vector<pair<string,string>>,vector<string>>> helper_Follow = parse.get_helper_Follow();

    reverse(ordered_follow.begin(), ordered_follow.end());
    follow[ordered_follow[0]] = {"$"};
    for (int i = 0; i < ordered_follow.size(); i++){

        for (auto follower : helper_Follow[ordered_follow[i]].first){
            vector<string> termianl_follow;
            if (follower.first[0]=='\'')
                follow[ordered_follow[i]].push_back(follower.first.substr(1,follower.first.length()-2));
            else{
                transform(First [follower.first].begin(), First [follower.first].end(),back_inserter(termianl_follow), first);
                follow[ordered_follow[i]].insert(follow[ordered_follow[i]].end(), termianl_follow.begin(), termianl_follow.end());

                if (contain_epslion(First [follower.first])){
                    follow[ordered_follow[i]].insert(follow[ordered_follow[i]].end(), follow[follower.second].begin(), follow[follower.second].end());
                }
            }
        }

        for (auto LHS : helper_Follow[ordered_follow[i]].second){
            follow[ordered_follow[i]].insert(follow[ordered_follow[i]].end(), follow[LHS].begin(), follow[LHS].end());
        }
        remove_duplicates (&follow[ordered_follow[i]]);
        remove_eps_emptyStr(&follow[ordered_follow[i]]);
    }
    return follow;
}
