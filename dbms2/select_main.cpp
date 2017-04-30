#include <iostream>
#include <string>
#include <vector>
#include<bits/stdc++.h>



using namespace std;

vector<string> table1(string);
vector<string> split(string, char);
string select(string);
string lowercase_letter(string);
vector<string>attribute1(string);
vector<string> clauses(string a);
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
    int selected[desc.size()];
    for(int i=0;i<desc.size();i++)
        selected[i] = 0;
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
string select(string s)
{
    //cout<<"@"<<s<<endl;
    string output = s+".txt";
    //cin>>s>>endl;
//cout<<"@"<<output<<endl;
    bool notdelete = false;
    //cout<<s<<endl;
    int from = s.find("from");
// select ID=5 from ins1

    string result = s.substr(from+5,s.length()); cout<<"<"<<result<<endl;
    if(result.find("project")==0)
       result = project(result.substr(8,result.length()));
    else if(result.find("select")==0)
        result = select(result.substr(7,result.length()));
    else if(result == "Error")
        return "Error";
    else
    {
        notdelete = true;
        //result = result+"output.txt";
        result = result+".txt";
        //cout<<endl<<result;
    }
    //cout<<result<<endl;
    ifstream fin;
    ofstream fout;
    //fout.open(output.c_str());
    fin.open(result.c_str());
    //fin.open("ins1.txt");
    if(!fin)
    {
        cout<<"File not found"<<endl;
        return "Error";
    }
    string des_row;
    getline(fin,des_row);
    //fout<<des_row<<endl;
    cout<<des_row<<endl;
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
    vector<string> clause= clauses(condition_string);
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
    string row;
    while(getline(fin,row))
    {
        row = lowercase_letter(row);
        //cout<<row<<endl;
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
        //cout<<f_ans;

        if(f_ans)
        {
            for(int i=0;i<des.size()-1;i++)
            {
                cout<<entry_string[i]<<'\t';
            }
        }
    }
    fin.close();
    return output;
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
    s = lowercase_letter(s);
    string comd = s.substr(0,s.find_first_of(' '));
    //cout<<command;
    if(comd == "select")
    {
        //cout<<s.substr(s.find_first_of(' '),s.length());
        string result = select(s.substr(s.find_first_of(' ')+1,s.length()));
        //if(result != "all")
            //cout<<"Error";
    }
    /*if(comd == "project")
    {
        int result = project(s.substr(s.find_first_of(' ')+1,s.length()));
        if(result == 1)
            cout<<"Error";
    }*/

    return 0;
}

