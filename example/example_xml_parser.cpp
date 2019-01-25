#include "printf.h"
#include "xml_parser.h"
using namespace tinyxml2;
#include <iostream>
using namespace std;

template <typename T1, typename T2, typename T3>
void PRINTF_MAP(map<T1, T2> &record, T3 &it)
{
	it = record.begin();
	while (it != record.end())
	{
		cout << it->first << ":" << it->second << endl;
		it++;
	}
}

int main(int argc, char *argv[])
{	
	XMLDocument doc;
	if (get_conf(doc, "/home/zcp_tool/conf/server.xml") != 0)
	{
		PRINTF_ERROR("get_conf error");
	}
	map<string, XMLElement*> record;
	get_node(record, doc);
	map<string, XMLElement*>::iterator it = record.begin();
	while (it != record.end())
	{
		cout << it->first << endl;
		map<string, XMLElement*> record_1;
		get_node(record_1, it->second);
		map<string, XMLElement*>::iterator it_1 = record_1.begin();
		while (it_1 != record_1.end())
		{
			cout << it_1->first << endl;
			if (it_1->first == "cgi-bin")
			{
				map<string, XMLElement*> record_2;
				get_node(record_2, it_1->second);
				map<string, XMLElement*>::iterator it_2 = record_2.begin();
				while (it_2 != record_2.end())
				{
					cout << it_2->first << endl;
					map<string, string> record_3;
					get_attri(record_3, it_2->second);
					map<string, string>::iterator it_3;
					PRINTF_MAP(record_3, it_3);
					it_2++;
				}
			}
			it_1++;
		}
		it++;
	}
	return 0;
}