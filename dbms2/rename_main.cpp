#include <iostream>
#include <string>
#include <vector>
#include<bits/stdc++.h>

using namespace std;

vector<string> table1(string);
vector<string> split(string, char);
int project(string);
string lowercase_letter(string);
string Rename(string s);
vector<string>attribute1(string);
vector<string> clauses(string a)
{
    vector<string> clause;
    string a1;
    //cout<<a<<endl;
    while(a!="\0")
    {
        int l = a.length();
        int space = a.find_first_of(' ');
        if(space!=-1)
        {
            a1 = a.substr(0,space);
            a = a.substr(space+1,l);
        }
        else
        {
            a1 = a.substr(0,l);
            a = "\0";
        }
        clause.push_back(a1);
    }
    return clause;
}

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
    desc_row = lowercase_letter(desc_row);
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


string lowercase_letter(string s)
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
string select(string s)
{
    string output = s+".txt";
    //cin>>s>>endl;
    bool notdelete = false;
    //cout<<s<<endl;
    int from = s.find("from");


    string result = s.substr(from+5,s.length());
    if(result.find("project")==0)
       result = project(result.substr(8,result.length()));
    else if(result.find("select")==0)
        result = select(result.substr(8,result.length()));
    else if(result == "Error")
        return "Error";
    else
    {
        notdelete = true;
        result = result+".txt";
    }
    //cout<<result<<endl;
    ifstream fin;
    ofstream fout;
    fout.open(output.c_str());
    fin.open(result.c_str());
    if(!fin)
    {
        //cout<<"File not found"<<endl;
        return "Error";
    }
    string des_row;
    getline(fin,des_row);
    fout<<des_row<<endl;
    des_row = lowercase_letter(des_row);
    //cout<<desc_row<<endl;
    vector<string> des;
    des = split(des_row,'\t');
    map<string,int> columns;
    for(int i=0;i<des.size();i++)
    {
        columns[des[i]] = i;
        //cout<<desc[i]<<columns[desc[i]]<<endl;
    }
    string condition_string = lowercase_letter(s.substr(0,from-1));
    //cout<<condition_string<<endl;
    vector<string> clause=clauses(condition_string);
    //cout<<clause[0];
    vector<string> con;
    vector<string> cond;
    for(int i=0;i<clause.size();i++)
    {
        if(i%2==1)
            con.push_back(clause[i]);
        else
            cond.push_back(clause[i]);
    }
    //cout<<connector[0];
    //cout<<condition[0]<<condition[1]<<endl;
    string row;
    while(getline(fin,row))
    {
        row = lowercase_letter(row);
        //cout<<row<<endl;
        vector<bool> ans(cond.size(), false);
        vector<string> entry_string = split(row,'\t');
        for(int i=0;i<cond.size();i++)
        {
            if((entry_string[columns[cond[i].substr(0,cond[i].find_first_of('='))]]) ==
               (cond[i].substr(cond[i].find_first_of('=')+1,cond[i].length())))
                ans[i] = true;

        }
        bool f_ans = ans[0];
        for(int i=0;i<con.size();i++)
        {
            f_ans = (con[i]=="and") ? (f_ans && ans[i+1]) : (f_ans);
            f_ans = (con[i]=="or") ? (f_ans || ans[i+1]) : (f_ans);
        }

        if(f_ans)
        {
            for(int i=0;i<des.size()-1;i++)
            {
                fout<<entry_string[i]<<'\t';
                //cout<<entry_string[i]<<'\t';
            }
            fout<<entry_string[des.size()-1]<<endl;
        }
    }
    //cout<<"OUT";
    fout.close();
    //cout<<"OUT";
    fin.close();
    //cout<<"OUT";
    //if(!do_not_delete)
    //    remove(result.c_str());
    return output;
}

string Rename(string s)
{
    cout<<s<<endl;
    string output = s+".txt";
    bool notdelete = false;
    int space = s.find_first_of(' ');
    string result = s.substr(space+1,s.length());//no semicolon needed now
    //vector<string> table = tables(table_string);
    //cout<<result<<endl<<attribute_string;
    if(result.find("project")==0)
        result = project(result.substr(8,result.length()));
    else if(result.find("select")==0)
        result = select(result.substr(7,result.length()));
    else if(result.find("rename")==0)
        result = Rename(result.substr(7,result.length()));
    else if(result == "ERROR")
        return "ERROR";
    else
    {
        notdelete = true;
        result = result+".txt";
    }
    //cout<<result<<endl;
    ifstream fin;
    ofstream fout;
    //fout.open(output.c_str());
    fin.open(result.c_str());
    if(!fin)
    {
        cout<<"File not found"<<endl;
        return "ERROR";
    }
    string des_row;
    getline(fin,des_row);
    des_row = lowercase_letter(des_row);
    //cout<<desc_row<<endl;
    vector<string> des;
    //cout<<desc_row<<endl;
    des = split(des_row,'\t');
    string alt_string = s.substr(0,space);
    //cout<<alt_string<<endl;
    //vector<string> alt = split(alt_string,',');
    vector<string> alt = attribute1(alt_string);
    //cout<<alt[0]<<alt[1]<<alt[2]<<endl;
    if(alt.size()!=des.size())
    {
        cout<<"Unequal columns"<<endl;
        return "ERROR";
    }
    for(int i=0;i<alt.size()-1;i++)
    {
        cout<<alt[i]<<'\t';
    }
    cout<<alt[alt.size()-1]<<endl;
    string row;
    while(getline(fin,row))
    {
        cout<<row<<endl;
    }
    fin.close();
    //fout.close();
    if(!notdelete)
        remove(result.c_str());
    return output;
}



//int select(string s);
//string lower(string s);
int main()
{
    string s;
    getline(cin,s);
    //cout<<s;
    s = lowercase_letter(s);
    string comd = s.substr(0,s.find_first_of(' '));
    //cout<<command;
    if(comd == "rename")
    {
        string result = Rename(s.substr(s.find_first_of(' ')+1,s.length()));
        //if(result == "OR")
           // cout<<"Error";
    }
    //else if(command == "project")
        //project(s.substr(s.find_first_of(' '),s.length()));
    return 0;
}

