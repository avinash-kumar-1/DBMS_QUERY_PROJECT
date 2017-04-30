#include <iostream>
#include <string>
#include <vector>
#include<bits/stdc++.h>


//project name from Ins;
//project * from Ins;
//project all from Ins;
//project name ID from Ins;

using namespace std;

vector<string> table1(string);
vector<string> split(string, char);
int project(string);
string lower1(string);
vector<string>attribute1(string);
vector<string> table1(string t)
{
    vector<string> table;
    string t1;
    while(t!="\0")
    {
        int l = t.length();
        int comma = t.find_first_of(',');
        if(comma!=-1)
        {
            t1 = t.substr(0,comma);
            t = t.substr(comma+1,l);
        }
        else
        {
            t1 = t.substr(0,l-1);
            t = "\0";
        }
        table.push_back(t1);
    }
    return table;
}


vector<string> split(string str, char delimiter) {
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;

  while(getline(ss, tok, delimiter)) {
    //cout<<tok<<'\t';
    internal.push_back(tok);
  }

  return internal;
}

int project(string s)
{
    //cout<<s;
    int from = s.find("from");
    string attribute_string = s.substr(0,from-1);
    string table_string = s.substr(from+5,s.length());
    vector<string> attribute = attribute1(attribute_string);
    vector<string> table = table1(table_string);

    ifstream fin;
    fin.open(((table[0]+".txt")).c_str());
    string desc_row;
    getline(fin,desc_row);
    desc_row = lower1(desc_row);
    //cout<<desc_row<<endl;
    vector<string> desc;
    desc = split(desc_row,'\t');
    //cout<<desc[0]<<'.'<<desc[1]<<'.'<<desc[2]<<endl;
    //cout<<attribute[0]<<'.'<<attribute[1]<<'.'<<endl;
    int selected[desc.size()];
    for(int i=0;i<desc.size();i++)
        selected[i] = 0;
    //vector<bool> selected;
    for(int j=0;j<desc.size();j++)
    {
        for(int i=0;i<attribute.size();i++)
        {
            //cout<<desc[j]<<'.'<<attribute[i]<<endl;
            if(desc[j]==attribute[i]||attribute[i]=="*"||attribute[i]=="all")
            {
                selected[j] = 1;
                //cout<<"in";
                //break;
            }
            //cout<<selected[j];
        }
    }

    string row;
    vector<string> entries;
    //while(true)
    for(int i=0;i<40;i++)
    {
        getline(fin,row);
        //cout<<row<<endl;
        if(row=="\0")
            break;
        entries = split(row,'\t');
        //cout<<entries[0];
        for(int i=0;i<desc.size();i++)
        {
            if(selected[i])
                cout<<entries[i]<<'\t';
        }
        cout<<endl;
    }
    fin.close();

    return 0;
}


string lower1(string s)
{
    int l = s.length();
    for(int i=0;i<l;i++)
    {
        if(s[i]>=65 && s[i]<=90)
        {
            s[i] = s[i] + 32;
        }
    }
    return s;
}


vector<string>attribute1(string a)
{
    vector<string> attribute;
    string a1;
    //cout<<a<<endl;
    while(a!="\0")
    {
        int l = a.length();
        int comma = a.find_first_of(',');
        if(comma!=-1)
        {
            a1 = a.substr(0,comma);
            a = a.substr(comma+1,l);
        }
        else
        {
            a1 = a.substr(0,l);
            a = "\0";
        }
        attribute.push_back(a1);
    }
    return attribute;
}



int main()
{
    string s;
    getline(cin,s);
    //cout<<s;
    s = lower1(s);
    string comd = s.substr(0,s.find_first_of(' '));
    //cout<<command;
    if(comd == "project")
    {
        int result = project(s.substr(s.find_first_of(' ')+1,s.length()));
        if(result == 1)
            cout<<"Error";
    }
    //else if(command == "project")
        //project(s.substr(s.find_first_of(' '),s.length()));
    return 0;
}

