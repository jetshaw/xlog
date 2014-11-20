#ifndef _x_UTILS_H__
#define _x_UTILS_H__

#include<string>
#include<vector>
#include<set>
#include<map>
using namespace std;

namespace xutils {

bool parse_line(const string &line,const char* splite,vector<string> &storage);
bool parse_line(const string &line,const char* splite,vector<int> &storage);
bool parse_line(const string &line,const char* splite,set<string> &storage);
bool parse_line(const string &line,const char* splite,set<int> &storage);
bool parse_line(const string &line,const char* splite,map<string,string> &kvs);

string str_ltrim(const string &str,const string &trim_chars);
string str_rtrim(const string &str,const string &trim_chars);
string str_trim(const string &str,const string &trim_chars);
#if 0
string to_string(int v);
string to_string(long v);
string to_string(long long v);
string to_string(float v);
string to_string(double v);
string to_string(long double v);
string to_upper(string &str);
#endif
}


#endif //_x_UTILS_H__
