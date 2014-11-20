#include"xutils.h"
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

namespace xutils {

bool parse_line(const string &line,const char* spliter,vector<string> &storage)
{
    if(line.size() <= 0 )
        return true;
    size_t pos = 0;
    int quit = 0;
    while (!quit)
    {
        size_t next_pos = line.find_first_of(*spliter,pos);
        if( next_pos == string::npos )
        {
            next_pos = line.size();
            quit = 1;
        }
        size_t space_pos = line.find_first_not_of(" ",pos);
        size_t last_space_pos = line.find_last_not_of(" ",next_pos-1);
        string sec = line.substr(space_pos,last_space_pos-space_pos+1);
        storage.push_back(sec);
        pos = next_pos + 1;
    }
    return true;
}

bool parse_line(const string &line,const char* spliter,vector<int> &storage)
{
    vector<string> vec;
    if( true != parse_line(line,spliter,vec) )
        return false;
    vector<string>::iterator it = vec.begin();
    for(;it!=vec.end();it++)
    {
        storage.push_back(strtoul((*it).c_str(),NULL,10));
    }
    return true;

}

bool parse_line(const string &line,const char* spliter,set<string> &storage)
{
    vector<string> vec;
    if( true != parse_line(line,spliter,vec) )
        return false;
    vector<string>::iterator it = vec.begin();
    for(;it!=vec.end();it++)
    {
        storage.insert(*it);
    }
    return true;
}

bool parse_line(const string &line,const char* spliter,set<int> &storage)
{
    vector<string> vec;
    if( true != parse_line(line,spliter,vec) )
        return false;
    vector<string>::iterator it = vec.begin();
    for(;it!=vec.end();it++)
    {
        storage.insert(strtoul((*it).c_str(),NULL,10));
    }
    return true;

}

bool parse_line(const string &line,const char* spliter,map<string,string> &kvs)
{
    vector<string> vec;
    if( true != parse_line(line,spliter,vec) )
        return false;
    vector<string>::iterator it = vec.begin();
    vector<string> kv;
    for(;it!=vec.end();it++)
    {
        if (true != parse_line(*it,"=",kv))
            return false;
        if(kv.size()<2)
            kvs[kv[0]]="";
        else
            kvs[kv[0]]=kv[1];
        kv.clear();
    }
    return true;
}

string str_ltrim(const string &str,const string &trim_chars)
{
    size_t pos = str.find_first_not_of(trim_chars);
    if( string::npos == pos )
        return str;
    else
        return str.substr(pos);
}

string str_rtrim(const string &str,const string &trim_chars)
{
    size_t pos = str.find_first_not_of(trim_chars,str.size()-1);
    if( string::npos == pos )
        return str;
    else
        return str.substr(0,pos+1);
}

string str_trim(const string &str,const string &trim_chars)
{
   string new_str = str_ltrim(str,trim_chars);
   new_str = str_rtrim(new_str,trim_chars);
   return new_str;
}


}

#if 0 
//测试

using namespace xutils;
int main(int argc,char** argv)
{
    string line1("abc#def#ghi#jkl#mno#pqr#stu#vwx");
    string line2("123#456#789#111#222#333#444#555");
    string line3("a=100#b=200#c=300#d=400#e=500");
    vector<string> vecstr;
    vector<int> vecint;
    set<string> setstr;
    set<int> setint;
    map<string,string> mapstr;
    // test vector<string>
    if( parse_line(line3,"#",vecstr) == true )
    {
        std::cout<<"\nparse_line to vector<string> success \n"<<std::endl;
        vector<string>::iterator vecit=vecstr.begin();
        for(;vecit != vecstr.end();vecit++)
        {
            std::cout<<(*vecit).c_str()<<"\t"<<std::endl;
        }
    }
    else
    {
        std::cout<<"parse_line to vector<string> failed \n"<<std::endl;
    }
    
    // test vector<int>
    if( parse_line(line2,"#",vecint) == true )
    {
        std::cout<<"\nparse_line to vector<int> success \n"<<std::endl;
        vector<int>::iterator vecit=vecint.begin();
        for(;vecit != vecint.end();vecit++)
        {
            std::cout<<(*vecit)<<"\t"<<std::endl;
        }
    }
    else
    {
        std::cout<<"parse_line to vector<int> failed \n"<<std::endl;
    }

    // test set<string>
    if( parse_line(line1,"#",setstr) == true )
    {
        std::cout<<"\nparse_line to set<string> success \n"<<std::endl;
        set<string>::iterator setit=setstr.begin();
        for(;setit != setstr.end();setit++)
        {
            std::cout<<(*setit).c_str()<<"\t"<<std::endl;
        }
    }
    else
    {
        std::cout<<"parse_line to set<string> failed \n"<<std::endl;
    }

    // test set<int>
    if( parse_line(line2,"#",setint) == true )
    {
        std::cout<<"\nparse_line to set<int> success \n"<<std::endl;
        set<int>::iterator setit=setint.begin();
        for(;setit != setint.end();setit++)
        {
            std::cout<<(*setit)<<"\t"<<std::endl;
        }
    }
    else
    {
        std::cout<<"parse_line to set<int> failed \n"<<std::endl;
    }

    // test map<string,string>
    if( parse_line(line3,"#",mapstr) == true )
    {
        std::cout<<"\nparse_line to map<string,string> success \n"<<std::endl;
        map<string,string>::iterator mapit = mapstr.begin();
        for(;mapit != mapstr.end();mapit++)
        {
            std::cout<<"key="<<(*mapit).first<<" value="<<(*mapit).second<<"\t"<<std::endl;
        }
    }
    else
    {
        std::cout<<"parse_line to map<string,string> failed \n"<<std::endl;
    }
    return 0;
}


#endif
