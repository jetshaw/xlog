#include"xini_file.h"
#include<iostream>
#include<stdio.h>
using namespace std;

int main(int argc,char **argv)
{
    xini_file file;
    if( argc < 2 )
    {
        printf("no input config file\n");
        return -1;
    }
    file.init(string(argv[1]));
    string val=file.get(string("sec1"),string("key2"),string("failed"));
    std::cout<<"sec1 : key2"<<val.c_str()<<std::endl;
    val=file.get(string("sec1"),string("key1"),string("failed"));
    std::cout<<"sec1 : key1"<<val.c_str()<<std::endl;
    val=file.get(string("sec2"),string("key3"),string("failed"));
    std::cout<<"sec2 : key3"<<val.c_str()<<std::endl;
    val=file.get(string("sec2"),string("key4"),string("failed"));
    std::cout<<"sec2 : key4"<<val.c_str()<<std::endl;
    val=file.get(string("sec2"),string("key5"),string("failed"));
    std::cout<<"sec2 : key5"<<val.c_str()<<std::endl;

    return 0;
}
