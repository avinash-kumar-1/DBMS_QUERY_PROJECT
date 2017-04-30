#include <iostream>
#include <string>
#include <vector>
#include<bits/stdc++.h>

using namespace std;
//select_query ID=5 OR name=Avinash from ins1

vector<string> dbmstable(string);
vector<string> breaks(string, char);
string select_query(string );
string lowercase_letter(string);
string rename_query(string s);
int project_query(string);
vector<string>dbmsfunction(string);
vector<string> forms(string s);
/*/************************************TABLE**********************************************************
This function searches comma in whole input string if comma is found in string then
call in main function and work in two parts: before comma and after comma in string
//******************************************************************************************************/
vector<string> dbmstable(string s)
{
    vector<string> table;
    string s1;
    while(s!="\0")
    {
        int l = s.length();
        int comma = s.find(',');
        if(comma!=-1)
        {
            s1 = s.substr(0,comma);s = s.substr(comma+1,l);
        }
        else
        {
            s1 = s.substr(0,l-1);s = "\0";
        }
        table.push_back(s1);
    }
    return table;
}
/*/********************************************************breaks*****************************************************
 This breaks function is used for breaking the input string in many part
 in sub string and also in char
//*******************************************************************************************************************/
vector<string> breaks(string str, char stream) {
  vector<string> in;
  stringstream ss(str); // Turn the string into a stream.
  string s;

  while(getline(ss, s, stream)) in.push_back(s);

  return in;
}
/*/**************************************************************project_query******************************************************
//********************************************************************************************************************************/
int project_query(string s)
{
    int from = s.find("from");
    string attstring = s.substr(0,from-1);
    string table_string = s.substr(from+5,s.length());

    vector<string> arrange = dbmsfunction(attstring);
    vector<string> table = dbmstable(table_string);

    ifstream fin;
    fin.open(((table[0]+".txt")).c_str());
    string drow;
    getline(fin,drow);
    drow = lowercase_letter(drow);
    vector<string> sec;
    sec = breaks(drow,'\t');
    int select_queryed[sec.size()];
    for(int i=0;i<sec.size();i++)
        select_queryed[i] = 0;
    for(int j=0;j<sec.size();j++)
    {
        for(int i=0;i<arrange.size();i++)
        {
            if(sec[j]==arrange[i]||arrange[i]=="*"||arrange[i]=="all")
            {
                select_queryed[j] = 1;
            }
        }
    }

    string row;
    vector<string> entries;
    for(int i=0;i<40;i++)
    {
        getline(fin,row);
        if(row=="\0")
            break;
        entries = breaks(row,'\t');
        for(int i=0;i<sec.size();i++)
        {
            if(select_queryed[i])
                cout<<entries[i]<<'\t';
        }
        cout<<endl;
    }
    fin.close();

    return 0;
}
/*/********************************************************select_query********************************************************
//****************************************************************************************************************************/
string select_query(string s)
{
    string output = s+".txt";
    bool notdelete = false;
    int from = s.find("from");
// select_query ID=5 from ins1

    string ans = s.substr(from+5,s.length());
    if(ans.find("select")==0)
        ans = select_query(ans.substr(8,ans.length()));
    else if(ans == "Error")
        return "Error";
    else
    {
        notdelete = true;
        ans = ans+".txt";
    }
    ifstream fin;
    fin.open(ans.c_str());
    if(!fin)
    {
        //cout<<"File not found"<<endl;
        return "Error";
    }
    string des_row;
    getline(fin,des_row);
    cout<<des_row<<endl;
    des_row = lowercase_letter(des_row);
    vector<string> des;
    des = breaks(des_row,'\t');
    map<string,int> columns;
    for(int i=0;i<des.size();i++)
    {
        columns[des[i]] = i;
    }
    string string_case = lowercase_letter(s.substr(0,from-1));
    vector<string> form= forms(string_case);
    vector<string> con;
    vector<string> cond;
    for(int i=0;i<form.size();i++)
    {
        if(i%2==1)
            con.push_back(form[i]);
        else
            cond.push_back(form[i]);
    }
    string row;
    while(getline(fin,row))
    {
        row = lowercase_letter(row);
        vector<bool> ans(cond.size(), false);
        vector<string> f_string = breaks(row,'\t');
        for(int i=0;i<cond.size();i++)
        {
            if((f_string[columns[cond[i].substr(0,cond[i].find('='))]]) ==
               (cond[i].substr(cond[i].find('=')+1,cond[i].length())))
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
                cout<<f_string[i]<<'\t';
            }
        }
    }
    fin.close();
    return output;
}
/*/***********************************************************rename_query************************************************************
//********************************************************************************************************************************/
 string rename_query(string s)
{
     string answer = s+".txt";
     bool notdelete = false;
     int space = s.find(' ');
     string ans = s.substr(space+1,s.length());
     if(ans.find("rename")==0)
        ans = rename_query(ans.substr(7,ans.length()));
     else if(ans == "Error")
        return "Error";
     else
     {
        notdelete = true;
        ans = ans+".txt";
     }
     ifstream fin;
    fin.open(ans.c_str());
    if(!fin)
    {
        cout<<"File not found"<<endl;
        return "Error";
    }
    string des_row;
    getline(fin,des_row);
    des_row = lowercase_letter(des_row);
    vector<string> des;
    des = breaks(des_row,'\t');
    string alt_string = s.substr(0,space);
    vector<string> alt = dbmsfunction(alt_string);
    if(alt.size()!=des.size())
    {
        cout<<"Unequal"<<endl;
        return "Error";
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
    if(!notdelete)
        remove(ans.c_str());
    return answer;
}
/*/********************************************************LOWER_FUCTION*************************************************
 This lowercase function is used if input string is in uppercase letter
 then convert into lowercase letter of each char of input string
//****************************************************************************************************************************/
string lowercase_letter(string s)
{
    int l = s.length();
    for(int i=0;i<l;i++)
    {
        if(s[i]>=65 && s[i]<=90) s[i] = s[i] + 32;
    }
    return s;
}
/*/***************************************************FORMS_FUCTION********************************************************
This function is used for space in input string
//*****************************************************************************************************************************/
vector<string> forms(string s)
{
    vector<string> form;
    string s1;
    while(s!="\0")
    {
        int l = s.length();
        int space = s.find(' ');
        if(space!=-1){ s1 = s.substr(0,space);s = s.substr(space+1,l);}
        else{s1 = s.substr(0,l);s = "\0";}
        form.push_back(s1);
    }
    return form;
}
/*/*****************************************************arrangeS********************************************************************
This function is used for comma in arrange in input string
//************************************************************************************************************************************/
vector<string>dbmsfunction(string s)
{
    vector<string> att;
    string s1;
    while(s!="\0")
    {
        int l = s.length();
        int comma = s.find(',');
        if(comma!=-1){s1 = s.substr(0,comma);s = s.substr(comma+1,l);}
        else{s1 = s.substr(0,l);s = "\0";}
        att.push_back(s1);
    }
    return att;
}
/*/*********************************************************MAIN_FUCTION***********************************************************
This main fuction of all fuctions and in main fuction withought any fuction union and intersect and cartesion aare work
//******************************************************************************************************************************************/
int main()
{
    string s;
    getline(cin,s);
    s = lowercase_letter(s);
    string comd = s.substr(0,s.find(' '));//this is first word. must be command, like select_query,project_query,rename_query.
    int u = s.find("union");
    int v = s.find("intersect");
    int w = s.find("cartesion");
/*/********************************************************UNION***************************************************************
In this area union query is work
This query work if two of select_query or project_query query use output of two query is
//*************************************************************************************************************************************/
    if(u < s.length())
    {
        //UNION

        string s1 = s.substr(0,u-1);
        string s2 = s.substr(u+6,s.length());
        if((s1.find("select")==0) && (s2.find("select")==0))
  {
        int from1 = s1.find("from");
        int from2 = s2.find("from");

        string ans1 = s1.substr(from1+5,s1.length()) + ".txt";
        string ans2 = s2.substr(from2+5,s2.length()) + ".txt";

      //select in s1 and s2 both
      ifstream fin1,fin2;
      fin1.open(ans1.c_str());
      fin2.open(ans2.c_str());
      if(!fin1 || !fin2)
      {
          cout<<"nahi mila"<<endl;
          return -1;
      }
        string row1;
        getline(fin1,row1);
        string row2;
        getline(fin2,row2);
        if(row1!=row2)
            return -1;
        vector<string> v = breaks(row1,'\t');
    map<string,int> columns;
    for(int i=0;i<v.size();i++)
    {
        columns[v[i]] = i;
    }
    string string_case;
    vector<string> form;
    vector<string> con;
    vector<string> cond;
    string row;
    set<string> rows;

    string_case = lowercase_letter(s1.substr(7,from1-8));
    form = forms(string_case);
    for(int i=0;i<form.size();i++)
    {
        if(i%2==1)
            con.push_back(form[i]);
        else
            cond.push_back(form[i]);
    }
    while(getline(fin1,row))
    {
        row = lowercase_letter(row);
        vector<bool> ans(cond.size(), false);
        vector<string> f_string = breaks(row,'\t');
        for(int i=0;i<cond.size();i++)
        {
            if((f_string[columns[cond[i].substr(0,cond[i].find('='))]]) ==
               (cond[i].substr(cond[i].find('=')+1,cond[i].length())))
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
            if(rows.insert(row).second)
                cout<<row<<endl;
        }
    }

    //now s2
    string string_case2;
    vector<string> form2;
    vector<string> con2;
    vector<string> cond2;
    string_case2 = lowercase_letter(s2.substr(7,from2-8));

    form2 = forms(string_case2);
    for(int i=0;i<form2.size();i++)
    {
        if(i%2==1)
            con2.push_back(form2[i]);
        else
            cond2.push_back(form2[i]);
    }
    while(getline(fin2,row))
    {
        row = lowercase_letter(row);
        vector<bool> ans(cond2.size(), false);
        vector<string> f_string = breaks(row,'\t');
        for(int i=0;i<cond2.size();i++)
        {
            if((f_string[columns[cond2[i].substr(0,cond2[i].find('='))]]) ==
               (cond2[i].substr(cond2[i].find('=')+1,cond2[i].length())))
                ans[i] = true;

        }
        bool f_ans = ans[0];
        for(int i=0;i<con2.size();i++)
        {
            f_ans = (con2[i]=="and") ? (f_ans && ans[i+1]) : (f_ans);
            f_ans = (con2[i]=="or") ? (f_ans || ans[i+1]) : (f_ans);
        }
        if(f_ans)
        {
            //cout<<row<<endl;
            if(rows.insert(row).second)
                cout<<row<<endl;
        }
    }//while reading end
  }//if both select_query end
  }//union end
/*/******************************************************INTERSECTION****************************************************************
In this area intersect query is work
//****************************************************************************************************************************************/
     else if(v<s.length())
     {
         //Intersect
      string s1 = s.substr(0,v-1);
        string s2 = s.substr(v+10,s.length());
        if((s1.find("select")==0) && (s2.find("select")==0))
  {
        int from1 = s1.find("from");
        int from2 = s2.find("from");

        string ans1 = s1.substr(from1+5,s1.length()) + ".txt";
        string ans2 = s2.substr(from2+5,s2.length()) + ".txt";
        //cout<<"1"<<ans1<<endl;
       // cout<<"2"<<ans2<<endl;

      //select in s1 and s2 both
      ifstream fin1,fin2;
      fin1.open(ans1.c_str());
      fin2.open(ans2.c_str());
      if(!fin1 || !fin2)
      {
          cout<<"not found"<<endl;
          return -1;
      }
        string row1;
        getline(fin1,row1);
        string row2;
        getline(fin2,row2);
        if(row1!=row2)
            return -1;
        vector<string> v = breaks(row1,'\t');
    map<string,int> columns;
    for(int i=0;i<v.size();i++)
    {
        columns[v[i]] = i;
    }
    string string_case;
    vector<string> form;
    vector<string> con;
    vector<string> cond;
    string row;
    set<string> rows;

    string_case = lowercase_letter(s1.substr(7,from1-8));
    form = forms(string_case);
    for(int i=0;i<form.size();i++)
    {
        if(i%2==1)
            con.push_back(form[i]);
        else
            cond.push_back(form[i]);
    }
    while(getline(fin1,row))
    {
        row = lowercase_letter(row);
        vector<bool> ans(cond.size(), false);
        vector<string> f_string = breaks(row,'\t');
        for(int i=0;i<cond.size();i++)
        {
            if((f_string[columns[cond[i].substr(0,cond[i].find('='))]]) ==
               (cond[i].substr(cond[i].find('=')+1,cond[i].length())))
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
            if(!rows.insert(row).second)
                cout<<row<<endl;
        }
    }

    //now s2
    string string_case2;
    vector<string> form2;
    vector<string> con2;
    vector<string> cond2;
    string_case2 = lowercase_letter(s2.substr(7,from2-8));
    form2 = forms(string_case2);
    for(int i=0;i<form2.size();i++)
    {
        if(i%2==1)
            con2.push_back(form2[i]);
        else
            cond2.push_back(form2[i]);
    }
    while(getline(fin2,row))
    {
        row = lowercase_letter(row);
        vector<bool> ans(cond2.size(), false);
        vector<string> f_string = breaks(row,'\t');
        for(int i=0;i<cond2.size();i++)
        {
            if((f_string[columns[cond2[i].substr(0,cond2[i].find('='))]]) ==
               (cond2[i].substr(cond2[i].find('=')+1,cond2[i].length())))
                ans[i] = true;

        }
        bool f_ans = ans[0];
        for(int i=0;i<con2.size();i++)
        {
            f_ans = (con2[i]=="and") ? (f_ans && ans[i+1]) : (f_ans);
            f_ans = (con2[i]=="or") ? (f_ans || ans[i+1]) : (f_ans);
        }
        if(f_ans)
        {
            if(!rows.insert(row).second)
                cout<<row<<endl;
        }
    }//while reading end
  }//if b
    }
/*/******************************************************************************END_INTERSECT********************************************
//******************************************************************CARTESION*************************************************************
In this area cartesion product query is work
//************************************************************************************************************************************************/
  else if(w<s.length())
  {
      string s1 = s.substr(0,w-1);
        string s2 = s.substr(w+10,s.length());
        if((s1.find("select")==0) && (s2.find("select")==0))
  {
        bool notdelete1 = false;
        bool notdelete2 = false;
        int from1 = s1.find("from");
        int from2 = s2.find("from");

        string ans1 = s1.substr(from1+5,s1.length()) + ".txt";
        string ans2 = s2.substr(from2+5,s2.length()) + ".txt";

      //select in s1 and s2 both
      ifstream fin1,fin2;
      fin1.open(ans1.c_str());
      fin2.open(ans2.c_str());
      if(!fin1 || !fin2)
      {
          cout<<"nahi mila"<<endl;
          return -1;
      }
        string row1;
        getline(fin1,row1);
        string row2;
        getline(fin2,row2);
        if(row1!=row2)
            return -1;
        vector<string> v = breaks(row1,'\t');
    map<string,int> columns;
    for(int i=0;i<v.size();i++)
    {
        columns[v[i]] = i;
    }
    string string_case;
    vector<string> form;
    vector<string> con;
    vector<string> cond;
    string row;
    set<string> rows;

    string_case = lowercase_letter(s1.substr(7,from1-8));
    form = forms(string_case);
    for(int i=0;i<form.size();i++)
    {
        if(i%2==1)
            con.push_back(form[i]);
        else
            cond.push_back(form[i]);
    }
    while(getline(fin1,row))
    {
        row = lowercase_letter(row);
        vector<bool> ans(cond.size(), false);
        vector<string> f_string = breaks(row,'\t');
        for(int i=0;i<cond.size();i++)
        {
            if((f_string[columns[cond[i].substr(0,cond[i].find('='))]]) ==
               (cond[i].substr(cond[i].find('=')+1,cond[i].length())))
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
            if(rows.insert(row).second)
                cout<<row<<endl;
        }
    }

    //now s2
    string string_case2;
    vector<string> form2;
    vector<string> con2;
    vector<string> cond2;
    string_case2 = lowercase_letter(s2.substr(7,from2-8));
    form2 = forms(string_case2);
    for(int i=0;i<form2.size();i++)
    {
        if(i%2==1)
            con2.push_back(form2[i]);
        else
            cond2.push_back(form2[i]);
    }
    while(getline(fin2,row))
    {
        row = lowercase_letter(row);
        vector<bool> ans(cond2.size(), false);
        vector<string> f_string = breaks(row,'\t');
        for(int i=0;i<cond2.size();i++)
        {
            if((f_string[columns[cond2[i].substr(0,cond2[i].find('='))]]) ==
               (cond2[i].substr(cond2[i].find('=')+1,cond2[i].length())))
                ans[i] = true;

        }
        bool f_ans = ans[0];
        for(int i=0;i<con2.size();i++)
        {
            f_ans = (con2[i]=="and") ? (f_ans && ans[i+1]) : (f_ans);
            f_ans = (con2[i]=="or") ? (f_ans || ans[i+1]) : (f_ans);
        }
        if(f_ans)
        {
            //cout<<row<<endl;
            if(rows.insert(row).second)
                cout<<row<<endl;
        }
    }//while reading end
  }//if
  }
/*/*****************************************************************************************************************************************
In this area fucction of query select_query project_query rename_query are works in main fuction
//************************************************************************************************************************************************/
    if(comd == "select")
    {//select_query
        string ans = select_query(s.substr(s.find(' ')+1,s.length()));

    }
    else if(comd == "project")
    {//project_query
        int ans = project_query(s.substr(s.find(' ')+1,s.length()));
        if(ans == 1)
            cout<<"Error";
    }
    else if(comd == "rename")
    {//rename_query
        string ans = rename_query(s.substr(s.find(' ')+1,s.length()));
    }
    return 0;
}

