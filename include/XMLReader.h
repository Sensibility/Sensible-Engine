#ifndef _XML_READER_H_
#define _XML_READER_H_
#include "../lib/tinyxml2/tinyxml2.h"

class XMLReader
{
public:
	XMLReader(char* pFile)
	{
		doc_.LoadFile(pFile);
		if (doc_.Error())
			return;
		/*
		printf("%s\n", doc.FirstChildElement("COLLADA")->
			FirstChildElement("asset")->
			FirstChildElement("contributor")->
			FirstChildElement("author")->
			GetText());
	*/
	}
private:
	tinyxml2::XMLDocument doc_;
};

#endif _XML_READER_H_
