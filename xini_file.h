#ifndef __INI_FILE_H__
#define __INI_FILE_H__

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "xutils.h"
using namespace std;

class xini_file {
public:
	typedef std::map<std::string, std::string> KeyType;
	typedef std::map<std::string, KeyType> SectionType;

public:
	xini_file() {}
	~xini_file() {}

	inline bool init(const std::string &file);

	std::string get(const std::string &section, const std::string &key, std::string value) {
		SectionType::iterator sit = _data.find(section);
		if (sit != _data.end()) {
			KeyType::iterator kit = sit->second.find(key);
		if (kit != sit->second.end())
			value = kit->second;
		}
		return value;
	}

	int get(const std::string &section, const std::string &key, int value) {
		std::string str_value = get(section, key, "");
		if (str_value != "") {
			value = strtoul(str_value.c_str(), NULL, 10);
		}
		
		return value;
	}

	double get(const std::string &section, const std::string &key, double value) {
		std::string str_value = get(section, key, "");
		if (str_value != "") {
			value = strtod(str_value.c_str(), NULL);
		}

		return value;
	}

private:
	SectionType _data; // < section, <key, value> >
};

bool xini_file::init(const std::string &file)
{
	std::ifstream in(file.c_str());
	if (!in) {
		return false;
	}
	char c;
	std::string line, section, key, value;

	while (getline(in, line)) {
		if (line.empty() || line[0] == '\n' || line[0] == '#' || line[0] == ';') {
			continue;
		}
        //std::cout<<"before trim size="<<line.size()<<std::endl;
		line = xutils::str_trim(line, " \r\t\n");
        //std::cout<<"after trim size="<<line.size()<<std::endl;
		if (line.empty() || line[0] == '\n' || line[0] == '#' || line[0] == ';') {
			continue;
		}

		if (line[0] == '[' && line[line.size()-1] == ']') {
			section = xutils::str_trim(line.substr(1, line.size()-2), " \t");
			continue;
		} else if (line[0] == '[') {
			return false;
		}

		size_t pos = line.find_first_of('=', 0);
		if (pos == string::npos) {
			printf("it can not find equalifier for line [%s]\n", line.c_str());
			return false;
		}
		if (section.empty()) {
			printf("section is empty\n");
			return false;
		}
		string key = xutils::str_trim(line.substr(0, pos), " \t ");
		string val = xutils::str_trim(line.substr(pos+1, line.size() - pos), " \t ");
		_data[section][key] = val;
	}

	return true;
}

#endif // __INI_FILE_H__
