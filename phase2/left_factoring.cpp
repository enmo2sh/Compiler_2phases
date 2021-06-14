#include "left_factoring.h"

Left_Factoring::Left_Factoring()
{
    //ctor
}

bool visited [1000];
vector <vector<int>>  Left_Factoring::common_prefix(vector<string> productions, parse_grammar parse){
    vector <vector<int>> common ;
    for(int i=0;i<productions.size();i++){
        vector<int> vec;
        if (!visited[i]){
            visited[i] = 1;
            vec.push_back(i);
            vector<string> prod1 = parse.splits(productions[i]," ");
            for(int j=i+1; j<productions.size(); j++){
                if (!visited[j]){
                    vector<string> prod2 = parse.splits(productions[j]," ");
                    if (prod1[0] == prod2[0]){
                        visited[j] = 1;
                        vec.push_back(j);
                    }
                }
            }

            common.push_back(vec);
        }

    }
    memset(visited, 0, sizeof visited);
    return common;
}
string Left_Factoring:: longest_common_prefix (vector<int> group, vector<string> productions){
        for (int i = 0; i < productions[group[0]].length(); ++i) {
            for (int j = 1; j < group.size(); j++) {
                if (i >= (productions[group[j]]).length() || productions[group[j]][i] != productions[group[0]][i]) {
                    string prefix = productions[group[0]].substr(0, i);
                    if (prefix[prefix.length()-1]==' ')
                        prefix = prefix.substr(0, prefix.length()-1);
                    return prefix;
                }
            }
        }
    return productions[group[0]];
}
bool Left_Factoring:: check_left_fact(vector <vector<int>> common){
    for (auto vec : common)
        if (vec.size()>1)
            return true;
    return false;
}

bool Left_Factoring:: left_factoring(string line, parse_grammar parse){
    line.erase(0,2);    // to remove "# " from the start of line
    vector <string> parts = parse.splits(line," = ");
    vector <string> productions = parse.splits(parts[1],"|");
    vector <vector<int>> common = common_prefix(productions, parse);
    if (!check_left_fact(common))
        return false;
    vector <string> lines; string line_help;
    line = "# " + parts[0] + " = ";
    for (int i =0; i < common.size(); i++){

        string prefix = longest_common_prefix (common[i], productions);
        string dash ="";
        if (common[i].size() > 1)
            dash = " " + parts[0] + to_string(i+1) ;
        string  new_prod = prefix + dash;
        line += new_prod;
        if (i != common.size()-1)
            line += " | ";

        if (common[i].size() > 1){
            dash = parts[0] + to_string(i+1);
            line_help ="# " +  dash + " = ";
            for (int j =0; j < common[i].size(); j++){
                if (productions[common[i][j]] == prefix)
                    productions[common[i][j]] = "\\L";
                else{
                    productions[common[i][j]] = productions[common[i][j]].substr(prefix.length()+1, productions[common[i][j]].length()-prefix.length());
                }

                line_help += productions[common[i][j]];

                if (j != common[i].size()-1)
                    line_help += " | ";

            }
            lines.push_back(line_help);
            new_production [dash]= line_help;

        }

    }

    new_production [parts[0]] = line;
    for (auto l: lines){
        left_factoring(l, parse);
    }

    return true;
}

map <string, string> Left_Factoring:: get_new_production(){
    return new_production;
}
