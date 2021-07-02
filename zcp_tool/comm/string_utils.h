#ifndef __STRING_UTILS_H__
#define __STRING_UTILS_H__

#include <map>
#include <string>
#include <vector>
using namespace std;

// void string_trim(string& str);
void string_replace(string& data, const string& src, const string& dst);
void string_lower(string& str);
void string_upper(string& str);

typedef vector<string> vector_t;
void str2vec(const string& buf, const char& field, vector_t& vec);
void str2vec(const string& buf, const string& field, vector_t& vec);

typedef map<string, string> record_t;
void map2str(string& buf, const record_t& record, bool encode = true);
void str2map(record_t& record, const string& buf, bool decode = true);

bool va_function(const char* format, ...);
// bool va_function(const char* format, args...);

#endif