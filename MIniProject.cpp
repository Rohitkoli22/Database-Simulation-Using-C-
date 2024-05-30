#include<iostream>
#include<string.h>
#include<string>
#include<stdio.h>
#include<conio.h>
#include<vector>
#include <bits/stdc++.h> 
#include <map>
#include<fstream>
#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <direct.h>

using namespace std;
struct TableCol {

    std::string Col_name;
    std::vector<std::string> data;

};
class Table {

    public: 
        std::vector<TableCol> columns;
        std::map<int, size_t> index;
        vector<string> datatype;
       
    public:
        void validCommand(string command)
        {
            int n=command.size();
            int Ocount=0,Ecount=0;
            if(command[n] != ';')
            {
                for(int i=0;i<n-1;i++)
                {
                    if(command[i]=='(')
                    {
                        Ocount++;
                    }
                    else if(command[i]==')')
                    {
                        Ecount++;
                    }
                }
            }
            else{
                cout<<"\nSyntax Error!;";
                exit(0);
            }
            if(Ocount==Ecount)
            {
                //valid command;
            }
            else
            {
                cout<<"\nSyntax Error!()";
                exit(0);
            }
        }
        std::vector<string> tokenize(std::string str)
        {
            vector<string> result; 
            string str1="";
            for(size_t i=0;i<str.size();i++)
            {
                if(str[i] == ',' || str[i] == ')')
                {
                     if(str1=="")
                    {
                        str1.clear();
                    }
                    else{
                    datatype.push_back(str1);
                    str1="";
                    }

                }
                else if(str[i] == '\t' || str[i]== ' ' || str[i]== '\0' ||  str[i]== ';' || str[i] == '(' )
                {
                    if(str1=="")
                    {
                        str1.clear();
                    }
                    else{
                    result.push_back(str1);
                    str1="";
                    }
                }
                else{
                    str1+=str[i];
                }
            }
            result.push_back(str1);
            return result;
        }
        std::vector<string> tokenized(std::string str)
        {
            vector<string> result; 
            string str1="";
            for(size_t i=0;i<str.size();i++)
            {
               
                if(str[i] == '\t' || str[i]== ' ' || str[i]== '\0' ||  str[i]== ';' || str[i] == '(' || str[i] == ')' || str[i] == ',' )
                {
                    if(str1=="")
                    {
                        str1.clear();
                    }
                    else{
                    result.push_back(str1);
                    str1="";
                    }
                }
                else{
                    str1+=str[i];
                }
            }
            result.push_back(str1);
            return result;
        }
        void DatabaseInfo(const string& filename)
        {
        
        ofstream outFile;
        outFile.open("database.txt", ios::app);
        outFile<<filename;
        outFile<<endl;
        outFile.close();
        }
        void TableInfo(const string& filename)
        {
        
        ofstream outFile;
        outFile.open("tables.txt", ios::app);
        outFile<<filename;
        outFile<<endl;
        outFile.close();
        }
        vector<string> getColumnNames(const string& filename)
        {
            ifstream inFile;
            inFile.open(filename, ios::in);

            if (!inFile.is_open()) {
                cout << "File not found or unable to open!" << std::endl;
                exit(0);
            }

            std::string line;
            int i=0;
            while(i<1)
            {
            getline(inFile,line);
            i++;
            }
            std::vector<string> res=tokenized(line);
            inFile.close();
            return res;
        }
        vector<string> getDatatypes(const string& filename)
        {
            ifstream inFile;
            inFile.open(filename, ios::in);

            if (!inFile.is_open()) {
                cout << "File not found or unable to open!" << std::endl;
                exit(0);
            }

            std::string line;
            int i=0;
            while(i<=1)
            {
            line="";
            getline(inFile,line);
            i++;
            }
            std::vector<string> res=tokenized(line);
            inFile.close();
            return res;
        }
        void SelectSep(vector<string> Data)
        {
            int flag;
            vector<string> colnames;
            vector<string> tablename;
            vector<string> condition;
            for(size_t i=0;i<Data.size();i++)
            {
                if(Data[i] == "SELECT")
                {
                    flag=0;
                }
                else if(Data[i] == "FROM")
                {
                    flag=1;
                }
                else if(Data[i] == "WHERE")
                {
                    flag=2;
                }
                else if(flag == 0)
                {
                    colnames.push_back(Data[i]);
                }
                 else if(flag==1)
                {
                    tablename.push_back(Data[i]);
                }
                 else if(flag==2)
                {
                    condition.push_back(Data[i]);
                }
                else if(Data[i] == ",")
                {
                    continue;
                }
            }
            for(size_t i=0;i<tablename.size();i++)
            {
                int index;
                vector<string> Columns=getColumnNames(tablename[i]);
                for(size_t j=0;j<Columns.size();j++)
                {
                    if(Columns[j] == condition[0])
                    {
                        index=j;
                    }
                }
                string file=tablename[i] + "Desc";
                vector<string> datatypes=getDatatypes(file);
                if(datatypes[index] == "INT")
                {
                    ifstream inFile;
                    inFile.open(tablename[i],ios::in);
                    if (!inFile.is_open()) {
                    cout << "File not found or unable to open!add" << std::endl;
                    exit(0);
                    return ;
                    }
                    std::string line;
                    getline(inFile, line);
                    cout<<line<<endl;
                    while(getline(inFile,line))
                    {
                        vector<string> Data=tokenized(line);
                        int val=stoi(Data[index]);
                        int val2=stoi(condition[2]);
                        if(condition[1] == "=")
                        {
                            if(val==val2)
                            {
                                cout<<line<<endl;
                            }
                        }
                        else if(condition[1] == "!=")
                        {
                            if(val != val2)
                            {
                                cout<<line<<endl;
                            }
                        }
                        else if(condition[1] == ">")
                        {
                            if(val > val2)
                            {
                                cout<<line<<endl;
                            }
                        }
                        else if(condition[1] == "<")
                        {
                            if(val < val2)
                            {
                                cout<<line<<endl;
                            }
                        }
                        else if(condition[1] == ">=")
                        {
                            if(val >= val2)
                            {
                                cout<<line<<endl;
                            }
                        }
                        else if(condition[1] == "<=")
                        {
                            if(val <= val2)
                            {
                                cout<<line<<endl;
                            }
                        }

                                            
                    }
                    inFile.close();

                }
                else if(datatypes[index] == "VARCHAR[30]")
                {
                    ifstream inFile;
                    inFile.open(tablename[i],ios::in);
                    if (!inFile.is_open()) {
                    cout << "File not found or unable to open!add" << std::endl;
                    exit(0);
                    return ;
                    }
                    std::string line;
                    getline(inFile, line);
                    cout<<line<<endl;
                    while(getline(inFile,line))
                    {
                        vector<string> Data=tokenized(line);
                        
                        if(condition[1] == "=")
                        {
                            if(Data[index]==condition[2])
                            {
                                cout<<line<<endl;
                            }
                        }
                        else if(condition[1] == "!=")
                        {
                            if(Data[index] != condition[2])
                            {
                                cout<<line<<endl;
                            }
                        }
                   
                    }
                    inFile.close();

                }
                else if(datatypes[index] == "FLOAT")
                {
                    ifstream inFile;
                    inFile.open(tablename[i],ios::in);
                    if (!inFile.is_open()) {
                    cout << "File not found or unable to open!add" << std::endl;
                    exit(0);
                    return ;
                    }
                    std::string line;
                    getline(inFile, line);
                    cout<<line<<endl;
                    while(getline(inFile,line))
                    {
                        vector<string> Data=tokenized(line);
                        int val=stof(Data[index]);
                        int val2=stof(condition[2]);
                        if(condition[1] == "=")
                        {
                            if(val==val2)
                            {
                                cout<<line<<endl;
                            }
                        }
                        else if(condition[1] == "!=")
                        {
                            if(val != val2)
                            {
                                cout<<line<<endl;
                            }
                        }
                        else if(condition[1] == ">")
                        {
                            if(val > val2)
                            {
                                cout<<line<<endl;
                            }
                        }
                        else if(condition[1] == "<")
                        {
                            if(val < val2)
                            {
                                cout<<line<<endl;
                            }
                        }
                        else if(condition[1] == ">=")
                        {
                            if(val >= val2)
                            {
                                cout<<line<<endl;
                            }
                        }
                        else if(condition[1] == "<=")
                        {
                            if(val <= val2)
                            {
                                cout<<line<<endl;
                            }
                        }

                                            
                    }
                    inFile.close();
                }

            }
            
        }
        void DeleteData(vector<string> Data)
        {
            int flag;
            vector<string> colnames;
            vector<string> tablename;
            vector<string> condition;
            for(size_t i=0;i<Data.size();i++)
            {
                if(Data[i] == "DELETE")
                {
                    flag=0;
                }
                else if(Data[i] == "FROM")
                {
                    flag=1;
                }
                else if(Data[i] == "WHERE")
                {
                    flag=2;
                }
                else if(flag == 0)
                {
                    colnames.push_back(Data[i]);
                }
                 else if(flag==1)
                {
                    tablename.push_back(Data[i]);
                }
                 else if(flag==2)
                {
                    condition.push_back(Data[i]);
                }
                else if(Data[i] == ",")
                {
                    continue;
                }
            }
            for(size_t i=0;i<tablename.size();i++)
            {
                int index;
                vector<string> Columns=getColumnNames(tablename[i]);
                for(size_t j=0;j<Columns.size();j++)
                {
                    if(Columns[j] == condition[0])
                    {
                        index=j;
                    }
                }
                string file=tablename[i] + "Desc";
                vector<string> datatypes=getDatatypes(file);
                if(datatypes[index] == "INT")
                {
                    ifstream inFile;
                    inFile.open(tablename[i],ios::in);
                    ofstream outFile("temp.txt");
                    if (!inFile.is_open()) {
                    cout << "File not found or unable to open!add" << std::endl;
                    exit(0);
                    return ;
                    }
                    std::string line;
                    getline(inFile, line);
                    outFile<<line<<endl;
                    line="";
                    while(getline(inFile,line))
                    {
                        vector<string> Data=tokenized(line);
                        int val=stoi(Data[index]);
                        int val2=stoi(condition[2]);
                        if(condition[1] == "=")
                        {
                            if(val==val2)
                            {
                                cout<<line<<"Deleted"<<endl;
                            }
                            else{
                                outFile<<line<<endl;
                            }
                        }
                        else if(condition[1] == "!=")
                        {
                            if(val != val2)
                            {
                                cout<<line<<"Deleted"<<endl;
                            }
                            else{
                                outFile<<line<<endl;
                            }
                        }
                        else if(condition[1] == ">")
                        {
                            if(val > val2)
                            {
                                cout<<line<<"Deleted"<<endl;
                            }
                            else{
                                outFile<<line<<endl;
                            }
                        }
                        else if(condition[1] == "<")
                        {
                            if(val < val2)
                            {
                                cout<<line<<"Deleted"<<endl;
                            }
                            else{
                                outFile<<line<<endl;
                            }
                        }
                        else if(condition[1] == ">=")
                        {
                            if(val >= val2)
                            {
                                cout<<line<<"Deleted"<<endl;
                            }
                            else{
                                outFile<<line<<endl;
                            }
                        }
                        else if(condition[1] == "<=")
                        {
                            if(val <= val2)
                            {
                                cout<<line<<"Deleted"<<endl;
                            }
                            else{
                                outFile<<line<<endl;
                            }
                        }

                                            
                    }
                     inFile.close();
                    outFile.close();
                    string filename=tablename[i];
                    std::remove(filename.c_str());
                    std::rename("temp.txt", filename.c_str());

                }
                else if(datatypes[index] == "VARCHAR[30]")
                {
                    ifstream inFile;
                    inFile.open(tablename[i],ios::in);
                    ofstream outFile("temp.txt");
                    if (!inFile.is_open()) {
                    cout << "File not found or unable to open!add" << std::endl;
                    exit(0);
                    return ;
                    }
                    std::string line;
                    getline(inFile, line);
                    outFile<<line<<endl;
                    line="";
                    while(getline(inFile,line))
                    {
                        vector<string> Data=tokenized(line);
                        
                        if(condition[1] == "=")
                        {
                            if(Data[index]==condition[2])
                            {
                                cout<<line<<"Deleted"<<endl;
                            }
                            else{
                                outFile<<line<<endl;
                            }

                        }
                        else if(condition[1] == "!=")
                        {
                            if(Data[index] != condition[2])
                            {
                                cout<<line<<"Deleted"<<endl;
                            }
                            else{
                                outFile<<line<<endl;
                            }
                        }
                   
                    }
                     inFile.close();
                    outFile.close();
                    string filename=tablename[i];
                    std::remove(filename.c_str());
                    std::rename("temp.txt", filename.c_str());

                }
                else if(datatypes[index] == "FLOAT")
                {
                    ifstream inFile;
                    inFile.open(tablename[i],ios::in);
                    ofstream outFile("temp.txt");
                    if (!inFile.is_open()) {
                    cout << "File not found or unable to open!add" << std::endl;
                    exit(0);
                    return ;
                    }
                    std::string line;
                    getline(inFile, line);
                    outFile<<line<<endl;
                    line="";
                    while(getline(inFile,line))
                    {
                        vector<string> Data=tokenized(line);
                        int val=stof(Data[index]);
                        int val2=stof(condition[2]);
                        if(condition[1] == "=")
                        {
                            if(val==val2)
                            {
                                cout<<line<<"Deleted"<<endl;
                            }
                            else{
                                outFile<<line<<endl;
                            }
                        }
                        else if(condition[1] == "!=")
                        {
                            if(val != val2)
                            {
                                cout<<line<<"Deleted"<<endl;
                            }
                            else{
                                outFile<<line<<endl;
                            }
                        }
                        else if(condition[1] == ">")
                        {
                            if(val > val2)
                            {
                                cout<<line<<"Deleted"<<endl;
                            }
                            else{
                                outFile<<line<<endl;
                            }
                        }
                        else if(condition[1] == "<")
                        {
                            if(val < val2)
                            {
                                cout<<line<<"Deleted"<<endl;
                            }
                            else{
                                outFile<<line<<endl;
                            }
                        }
                        else if(condition[1] == ">=")
                        {
                            if(val >= val2)
                            {
                                cout<<line<<"Deleted"<<endl;
                            }
                            else{
                                outFile<<line<<endl;
                            }
                        }
                        else if(condition[1] == "<=")
                        {
                            if(val <= val2)
                            {
                                cout<<line<<"Deleted"<<endl;
                            }
                            else{
                                outFile<<line<<endl;
                            }
                        }

                                            
                    }
                     inFile.close();
                    outFile.close();
                    string filename=tablename[i];
                    std::remove(filename.c_str());
                    std::rename("temp.txt", filename.c_str());

                }

            }
            
        }



        void UpdateData(vector<string> Data)
        {
            int flag;
            vector<string> colnames;
            vector<string> values;
            vector<string> tablename;
            vector<string> condition;
            for(size_t i=0;i<Data.size();i++)
            {
                if(Data[i] == "UPDATE")
                {
                    flag=0;
                }
                else if(Data[i] == "TABLE")
                {
                    flag=0;
                }
                else if(Data[i] == "SET")
                {
                    flag=1;
                }
                else if(Data[i] == "=" && flag != 3)
                {
                    flag=2;
                }
                else if(Data[i] == "WHERE")
                {
                    flag=3;
                }
                else if(flag == 0)
                {
                    tablename.push_back(Data[i]);
            
                }
                 else if(flag==1)
                {
                    colnames.push_back(Data[i]);
                }
                 else if(flag==2)
                {
                    values.push_back(Data[i]);
                }
                 else if(flag==3)
                {
                    condition.push_back(Data[i]);
                }
                else if(Data[i] == ",")
                {
                    continue;
                }
            }
            for(size_t i=0;i<tablename.size();i++)
            {
                int index;
                vector<string> Columns=getColumnNames(tablename[i]);
                for(size_t j=0;j<Columns.size();j++)
                {
                    if(Columns[j] == condition[0])
                    {
                        index=j;
                    }
                }
                string file=tablename[i] + "Desc";
                vector<string> datatypes=getDatatypes(file);
                if(datatypes[index] == "INT")
                {
                    ifstream inFile;
                    inFile.open(tablename[i],ios::in);
                    ofstream outFile("temp.txt");
                    if (!inFile.is_open()) {
                        cout<<"hi from int"<<endl;
                    cout << "File not found or unable to open!add" << std::endl;
                    exit(0);
                    return ;
                    }
                    std::string line;
                    getline(inFile, line);
                    outFile<<line<<endl;
                    line="";
                    while(getline(inFile,line))
                    {
                        vector<string> Data=tokenized(line);
                        int val=stoi(Data[index]);
                        int val2=stoi(condition[2]);
                        if(condition[1] == "=")
                        {
                            if(val==val2)
                            {
                                vector<string> lineValues=tokenized(line);
                                for(int q=0;q<colnames.size();q++)
                                {
                                    for(int p=0;p<Columns.size();p++)
                                    {
                                        if(colnames[q]==Columns[p])
                                        {
                                            lineValues[p]=values[q];
                                        }
                                    }
                                }
                                string updatedline;
                                for(int x=0;x<lineValues.size();x++)
                                {
                                    updatedline.append(lineValues[x]);
                                    updatedline.append("\t");

                                }
                                outFile<<updatedline<<endl;
                            }
                            else{
                                outFile<<line<<endl;
                            }
                        }
                        else if(condition[1] == "!=")
                        {
                            if(val != val2)
                            {
                                vector<string> lineValues=tokenize(line);
                                for(int q=0;q<colnames.size();q++)
                                {
                                    for(int p=0;p<Columns.size();p++)
                                    {
                                        if(colnames[q]==Columns[p])
                                        {
                                            lineValues[p]=values[q];
                                        }
                                    }
                                }
                                string updatedline;
                                for(int x=0;x<lineValues.size();x++)
                                {
                                    updatedline.append(lineValues[x]);
                                    updatedline.append("\t");

                                }
                                outFile<<updatedline<<endl;
                            }
                            else{
                                outFile<<line<<endl;
                            }
                        }
                        else if(condition[1] == ">")
                        {
                            if(val > val2)
                            {
                               vector<string> lineValues=tokenize(line);
                                for(int q=0;q<colnames.size();q++)
                                {
                                    for(int p=0;p<Columns.size();p++)
                                    {
                                        if(colnames[q]==Columns[p])
                                        {
                                            lineValues[p]=values[q];
                                        }
                                    }
                                }
                                string updatedline;
                                for(int x=0;x<lineValues.size();x++)
                                {
                                    updatedline.append(lineValues[x]);
                                    updatedline.append("\t");

                                }
                                outFile<<updatedline<<endl;
                            }
                            else{
                                outFile<<line<<endl;
                            }
                        }
                        else if(condition[1] == "<")
                        {
                            if(val < val2)
                            {
                                vector<string> lineValues=tokenize(line);
                                for(int q=0;q<colnames.size();q++)
                                {
                                    for(int p=0;p<Columns.size();p++)
                                    {
                                        if(colnames[q]==Columns[p])
                                        {
                                            lineValues[p]=values[q];
                                        }
                                    }
                                }
                                string updatedline;
                                for(int x=0;x<lineValues.size();x++)
                                {
                                    updatedline.append(lineValues[x]);
                                    updatedline.append("\t");

                                }
                                outFile<<updatedline<<endl;
                            }
                            else{
                                outFile<<line<<endl;
                            }
                        }
                        else if(condition[1] == ">=")
                        {
                            if(val >= val2)
                            {
                                vector<string> lineValues=tokenize(line);
                                for(int q=0;q<colnames.size();q++)
                                {
                                    for(int p=0;p<Columns.size();p++)
                                    {
                                        if(colnames[q]==Columns[p])
                                        {
                                            lineValues[p]=values[q];
                                        }
                                    }
                                }
                                string updatedline;
                                for(int x=0;x<lineValues.size();x++)
                                {
                                    updatedline.append(lineValues[x]);
                                    updatedline.append("\t");

                                }
                                outFile<<updatedline<<endl;
                            }
                            else{
                                outFile<<line<<endl;
                            }
                        }
                        else if(condition[1] == "<=")
                        {
                            if(val <= val2)
                            {
                                vector<string> lineValues=tokenize(line);
                                for(int q=0;q<colnames.size();q++)
                                {
                                    for(int p=0;p<Columns.size();p++)
                                    {
                                        if(colnames[q]==Columns[p])
                                        {
                                            lineValues[p]=values[q];
                                        }
                                    }
                                }
                                string updatedline;
                                for(int x=0;x<lineValues.size();x++)
                                {
                                    updatedline.append(lineValues[x]);
                                    updatedline.append("\t");

                                }
                                outFile<<updatedline<<endl;
                            }
                            else{
                                outFile<<line<<endl;
                            }
                        }

                                            
                    }
                     inFile.close();
                    outFile.close();
                    string filename=tablename[i];
                    std::remove(filename.c_str());
                    std::rename("temp.txt", filename.c_str());

                }
                else if(datatypes[index] == "VARCHAR[30]")
                {
                    ifstream inFile;
                    inFile.open(tablename[i],ios::in);
                    ofstream outFile("temp.txt");
                    if (!inFile.is_open()) {
                    cout << "File not found or unable to open!add" << std::endl;
                    exit(0);
                    return ;
                    }
                    std::string line;
                    getline(inFile, line);
                    outFile<<line<<endl;
                    line="";
                    while(getline(inFile,line))
                    {
                        vector<string> Data=tokenized(line);
                        
                        if(condition[1] == "=")
                        {
                            if(Data[index]==condition[2])
                            {
                                vector<string> lineValues=tokenize(line);
                                for(int q=0;q<colnames.size();q++)
                                {
                                    for(int p=0;p<Columns.size();p++)
                                    {
                                        if(colnames[q]==Columns[p])
                                        {
                                            lineValues[p]=values[q];
                                        }
                                    }
                                }
                                string updatedline;
                                for(int x=0;x<lineValues.size();x++)
                                {
                                    updatedline.append(lineValues[x]);
                                    updatedline.append("\t");

                                }
                                outFile<<updatedline<<endl;
                            }
                            else{
                                outFile<<line<<endl;
                            }

                        }
                        else if(condition[1] == "!=")
                        {
                            if(Data[index] != condition[2])
                            {
                               vector<string> lineValues=tokenize(line);
                                for(int q=0;q<colnames.size();q++)
                                {
                                    for(int p=0;p<Columns.size();p++)
                                    {
                                        if(colnames[q]==Columns[p])
                                        {
                                            lineValues[p]=values[q];
                                        }
                                    }
                                }
                                string updatedline;
                                for(int x=0;x<lineValues.size();x++)
                                {
                                    updatedline.append(lineValues[x]);
                                    updatedline.append("\t");

                                }
                                outFile<<updatedline<<endl;
                            }
                            else{
                                outFile<<line<<endl;
                            }
                        }
                   
                    }
                     inFile.close();
                    outFile.close();
                    string filename=tablename[i];
                    std::remove(filename.c_str());
                    std::rename("temp.txt", filename.c_str());

                }
                else if(datatypes[index] == "FLOAT")
                {
                    ifstream inFile;
                    inFile.open(tablename[i],ios::in);
                    ofstream outFile("temp.txt");
                    if (!inFile.is_open()) {
                    cout << "File not found or unable to open!add" << std::endl;
                    exit(0);
                    return ;
                    }
                    std::string line;
                    getline(inFile, line);
                    outFile<<line<<endl;
                    line="";
                    while(getline(inFile,line))
                    {
                        vector<string> Data=tokenized(line);
                        int val=stof(Data[index]);
                        int val2=stof(condition[2]);
                        if(condition[1] == "=")
                        {
                            if(val==val2)
                            {
                                vector<string> lineValues=tokenize(line);
                                for(int q=0;q<colnames.size();q++)
                                {
                                    for(int p=0;p<Columns.size();p++)
                                    {
                                        if(colnames[q]==Columns[p])
                                        {
                                            lineValues[p]=values[q];
                                        }
                                    }
                                }
                                string updatedline;
                                for(int x=0;x<lineValues.size();x++)
                                {
                                    updatedline.append(lineValues[x]);
                                    updatedline.append("\t");

                                }
                                outFile<<updatedline<<endl;
                            }
                            else{
                                outFile<<line<<endl;
                            }
                        }
                        else if(condition[1] == "!=")
                        {
                            if(val != val2)
                            {
                               vector<string> lineValues=tokenize(line);
                                for(int q=0;q<colnames.size();q++)
                                {
                                    for(int p=0;p<Columns.size();p++)
                                    {
                                        if(colnames[q]==Columns[p])
                                        {
                                            lineValues[p]=values[q];
                                        }
                                    }
                                }
                                string updatedline;
                                for(int x=0;x<lineValues.size();x++)
                                {
                                    updatedline.append(lineValues[x]);
                                    updatedline.append("\t");

                                }
                                outFile<<updatedline<<endl;
                            }
                            else{
                                outFile<<line<<endl;
                            }
                        }
                        else if(condition[1] == ">")
                        {
                            if(val > val2)
                            {
                                vector<string> lineValues=tokenize(line);
                                for(int q=0;q<colnames.size();q++)
                                {
                                    for(int p=0;p<Columns.size();p++)
                                    {
                                        if(colnames[q]==Columns[p])
                                        {
                                            lineValues[p]=values[q];
                                        }
                                    }
                                }
                                string updatedline;
                                for(int x=0;x<lineValues.size();x++)
                                {
                                    updatedline.append(lineValues[x]);
                                    updatedline.append("\t");

                                }
                                outFile<<updatedline<<endl;
                            }
                            else{
                                outFile<<line<<endl;
                            }
                        }
                        else if(condition[1] == "<")
                        {
                            if(val < val2)
                            {
                                vector<string> lineValues=tokenize(line);
                                for(int q=0;q<colnames.size();q++)
                                {
                                    for(int p=0;p<Columns.size();p++)
                                    {
                                        if(colnames[q]==Columns[p])
                                        {
                                            lineValues[p]=values[q];
                                        }
                                    }
                                }
                                string updatedline;
                                for(int x=0;x<lineValues.size();x++)
                                {
                                    updatedline.append(lineValues[x]);
                                    updatedline.append("\t");

                                }
                                outFile<<updatedline<<endl;
                            }
                            else{
                                outFile<<line<<endl;
                            }
                        }
                        else if(condition[1] == ">=")
                        {
                            if(val >= val2)
                            {
                                vector<string> lineValues=tokenize(line);
                                for(int q=0;q<colnames.size();q++)
                                {
                                    for(int p=0;p<Columns.size();p++)
                                    {
                                        if(colnames[q]==Columns[p])
                                        {
                                            lineValues[p]=values[q];
                                        }
                                    }
                                }
                                string updatedline;
                                for(int x=0;x<lineValues.size();x++)
                                {
                                    updatedline.append(lineValues[x]);
                                    updatedline.append("\t");

                                }
                                outFile<<updatedline<<endl;
                            }
                            else{
                                outFile<<line<<endl;
                            }
                        }
                        else if(condition[1] == "<=")
                        {
                            if(val <= val2)
                            {
                                vector<string> lineValues=tokenize(line);
                                for(int q=0;q<colnames.size();q++)
                                {
                                    for(int p=0;p<Columns.size();p++)
                                    {
                                        if(colnames[q]==Columns[p])
                                        {
                                            lineValues[p]=values[q];
                                        }
                                    }
                                }
                                string updatedline;
                                for(int x=0;x<lineValues.size();x++)
                                {
                                    updatedline.append(lineValues[x]);
                                    updatedline.append("\t");

                                }
                                outFile<<updatedline<<endl;
                            }
                            else{
                                outFile<<line<<endl;
                            }
                        }

                                            
                    }
                     inFile.close();
                    outFile.close();
                    string filename=tablename[i];
                    std::remove(filename.c_str());
                    std::rename("temp.txt", filename.c_str());

                }

            }
            
        }



        size_t getColumns(const string& filename)
        {
            ifstream inFile;
            inFile.open(filename, ios::in);

            if (!inFile.is_open()) {
                cout << "File not found or unable to open!" << std::endl;
                exit(0);
                return 0;
            }

            std::string line;

            getline(inFile,line);
        
            std::vector<string> res=tokenize(line);
            inFile.close();
           
            return (res.size());
        }
        void CreateCol(std::string name)
        {
            TableCol newcol;
            newcol.Col_name=name;
            columns.push_back(newcol);
            
        }
        void insertRowData(std::vector<std::string> Rowdata,string filename)
        {
            size_t colsize;
            colsize=getColumns(filename);
            if(Rowdata.size() != colsize)
            {
                std::cout<<"\nRow does not match the columns number!\n";
                return exit(0);
            }
            for(size_t i=0;i<(colsize-1);i++)
            {
                columns[0].data.push_back(Rowdata[i]);
            }

        }
        void selectData(string tableName)
        {
            
            ifstream inFile;
            inFile.open(tableName,ios::in);
            if (!inFile.is_open()) {
                cout << "File not found or unable to open!add" << std::endl;
                exit(0);
                return ;
            }
            std::string line;
                while(getline(inFile,line))
                {
                    cout<<"\n"<<line;
                }
            inFile.close();
        }

         void SaveinFile(const string& filename)
        {
            ofstream outFile(filename);
            for(const auto& col : columns)
            {
                outFile<<col.Col_name<<"\t";
            }
            outFile<<endl;
             

            outFile.close();
    } 
    void InsertData(const string& filename,vector<string> Data)
    {
        size_t size;
        string line;
        size=getColumns(filename);
        ofstream outFile;
        outFile.open(filename, ios::app);
         for(size_t i=0;i<size;i++)
            {
            line.append(Data[i]);
            line.append("\t");
            }
        outFile<<line;
        outFile << std::endl;

        outFile.close();


    }
    void description(const string& filename,vector<string> Data)
    {
        string line;
        
        ofstream outFile;
        outFile.open(filename, ios::app);
         for(size_t i=0;i<Data.size();i++)
            {
            line.append(Data[i]);
            line.append("\t");
            }
        outFile<<line;
        outFile << std::endl;

        outFile.close();
    }
    void createTable(const string& tableName, const std::vector<std::string>& columnNames) {
        for(size_t i=0;i<columnNames.size();i++)
        {
            CreateCol(columnNames[i]);
        }
        SaveinFile(tableName);
    }

    void executeCommand(const string& command) {
        
        validCommand(command);
        vector<string> tokens = tokenize(command);
        vector<string> token = tokenized(command);
        if (tokens.empty()) {
            cout << "Invalid command!" <<endl;
            return;
        }
        if (token.empty()) {
            cout << "Invalid command!" <<endl;
            return;
        }

        string& operation = tokens[0];
        string& operation1 = token[0];

        if (operation == "CREATE") {
            // Handle CREATE TABLE command
            // Example: CREATE TABLE tablename (column1, column2, ...)
            // ... (Parse command and create table)
            if(tokens[1]=="DATABASE")
            {
                if(mkdir(tokens[2].data()) == -1)
                {
                     cerr << "Error :  " << strerror(errno) << endl;
                }
                else{
                    cout << "Database created";
                }
            }
            else if(tokens[1]!="TABLE")
            {
                cout<<"\nSyntax Error!";
                exit(0);
            }
            vector<string> columnNames;
            columns.clear();
            DatabaseInfo(tokens[2]);
            string str2=tokens[2];
            string str3="Desc";
            string file= str2 + str3;
            // cout<<file;
            // SaveinFile(file);
            // for(size_t i=0;i<datatype.size();i++)
            // {
            //     cout<<"\n"<<datatype[i];
            // }
            
            for(size_t i=3;i<tokens.size();i++)
            {
                if(tokens[i]=="PRIMARY" && tokens[i+1]=="KEY")
                {
                       
                        createTable(file,columnNames);
                        string primarycol=datatype[datatype.size()-1];
                        datatype.pop_back();
                        description(file,datatype);
                        vector<string> coldata=getColumnNames(file);
                        
                        
                        cout<<"Primary COL NAME: "<<tokens[i+2]<<endl;
                        int primarypos=0;
                        for(int k=0;k<coldata.size();k++)
                        {
                            if(coldata[k]==primarycol)
                            {
                                 cout<<"Primary COL: "<<k<<endl;
                                primarypos=k;
                            }
                        }
                        size_t size;
                        string line1;
                        size=getColumns(file);
                        ofstream outFile;
                        outFile.open(file, ios::app);
                        for(int i=0;i<coldata.size();i++)
                            {
                                if(i==primarypos)
                                {
                                     cout<<"Primary key"<<endl;
                                    line1.append("PRIMARY KEY");
                                    line1.append("\t");
                                }
                                else{
                                    line1.append("\t");
                                }
                                
                            }
                        
                        outFile<<line1;
                        outFile << std::endl;
                        outFile.close();
                        columns.clear();
                        break;
                }
                else{
                    columnNames.push_back(tokens[i]);
                }
                
            }
            createTable(tokens[2],columnNames);
            TableInfo(tokens[2]);
            
            
            datatype.clear();
            columnNames.clear();

        } else if (operation1 == "INSERT") {
            // Handle INSERT command
            // Example: INSERT INTO tablename VALUES (value1, value2, ...)
            // ... (Parse command and insert row)
            
            vector<string> Data;
             if(token[1]!="INTO")
            {
                cout<<"\nSyntax Error!";
                exit(0);
            }
            CreateCol(token[2]);
            
            for(size_t i=3;i<token.size();i++)
            {
                Data.push_back(token[i]);
            }
            insertRowData(Data,token[2]);
            InsertData(token[2],Data);
            Data.clear();
        } else if (operation1 == "SELECT") {
            // Handle SELECT command
            // Example: SELECT * FROM tablename
            // ... (Parse command and execute select query)
            if(token[1] == "*")
            {
                selectData(token[3]);
                return ;
            }
            else{

                SelectSep(token);

            }

        }
        else if(operation1 == "DELETE"){

            DeleteData(token);
        }
        else if(operation1 == "DROP"){

            int res = remove(token[1].c_str());
                    if(res==0)
                    {
                        cout<<"\nTable is Deleted";
                    }
        }
        else if(operation1 == "QUIT"){

            exit(0);
        }
        else if(operation1 == "USE")
        {
            string DataBaseFolder="E:/ROHIT/Mini--Project 123/output/"+tokens[1];
            if (chdir(DataBaseFolder.c_str()) != 0) 
            {
                perror("chdir() to / failed"); 
            }
    
 
        }
        else if(operation1 == "UPDATE")
        {
            UpdateData(token);
        }
        else if(operation1 == "HELP"){

            cout<<"\nCREATE TABLE TABLE_NAME(COL1,COL2,.....COLN);";
            cout<<"\nDROP TABLE TABLE_NAME;";
            cout<<"\nINSERT INTO TABLE_NAME(VAL1,VAL2,....VALN);";
            cout<<"\nSELECT";
            cout<<"\nUPDATE";
            cout<<"\nDELETE";
        }
         else {
            cout << "Command not recognized!" <<endl;
        }
        
    }


};
int main()
{

    Table newtable;
    string tableName;
    string colname,data;
    vector<string> columnNames;
    vector<string> Data;
    string command;
    while(1)
    {
    cout<<"\n>>";
    getline(cin, command);
    newtable.executeCommand(command);
    }


    return 0;
}