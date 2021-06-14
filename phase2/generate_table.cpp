#include "generate_table.h"

generate_table::generate_table()
{
}

map<string,map<string,string>> generate_table:: get_Parsing_Table(map<string,vector<pair<string,string>>> First, map <string,vector<string>> Follow){
    generate_follow gf;
    map<string,vector< pair<string,string>>>::iterator itr;
    for (itr = First.begin(); itr != First.end(); ++itr) {
        map<string,string> temp;
        bool flag = false;
        for(int j=0;j<itr->second.size();j++){
            if(itr->second[j].first != "\\L"){
                if(temp.find(itr->second[j].first) != temp.end()){
                    cout <<endl<< " NOT LL(1) GRAMMAR !!";
                    exit(0);
                }
                temp.insert({itr->second[j].first,itr->second[j].second});
            }
            else{
                flag = true;
            }
        }
        vector<string> follow = Follow.at(itr->first);
        for(int i=0;i<follow.size();i++){
            if(flag){
                if(temp.find(follow[i])!= temp.end()){
                     cout <<itr->first <<"     "<<follow[i]<<endl;
                     cout <<endl<< " NOT LL(1) GRAMMAR !!";
                     exit(0);
                }
                temp.insert({follow[i],"\\L"});
            }
            else
                if(temp.find(follow[i])== temp.end())
                    temp.insert({follow[i],"synch"});
        }
        Parsing_Table.insert({itr->first,temp});
    }

    return Parsing_Table;
}
