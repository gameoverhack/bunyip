/*
 *  SceneView.h
 *  Bunyip
 *
 *  Created by gameover on 26/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#ifndef _H_SCENEVIEW
#define _H_SCENEVIEW

#include "BaseView.h"
#include "AppModel.h"

class SceneView : public BaseView {
	
public:
	
	SceneView(float width, float height);
	//~SceneView();
	
	void update();
	
private:
	
};

#endif