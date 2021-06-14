#ifndef CHECK_H
#define CHECK_H
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

vector<string> Split_Word(string str);
void Parser_Handle(map<string,map<string,string>> Parsing_Table,stack<string>* Main_Stack,string One_Token);

#endif
