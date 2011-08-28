/*
 *  SceneXMLParser.h
 *  Bunyip
 *
 *  Created by gameover on 26/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#ifndef _H_SCENEXMLPARSER
#define _H_SCENEXMLPARSER

#include "IXMLParser.h"
#include "AppModel.h"

class SceneXMLParser : public IXMLParser {
public:
	SceneXMLParser(string xmlFile);
	void parseXML();
};

#endif