/*
 *  SceneXMLBuilder.h
 *  Bunyip
 *
 *  Created by gameover on 26/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#ifndef _H_SCENEXMLBUILDER
#define _H_SCENEXMLBUILDER

#include "IXMLBuilder.h"
#include "AppModel.h"

class SceneXMLBuilder : public IXMLBuilder {
public:
	SceneXMLBuilder(string xmlFile);
	void buildXML();
};

#endif