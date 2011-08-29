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

#include "ofxShader.h"

class SceneView : public BaseView {
	
public:
	
	SceneView(float width, float height);
	//~SceneView();
	
	void update();
	
private:
	
	ofxShader				_shaders[3];
	ofTexture _shader1Tex, _shader2Tex;
	ofxFbo _shader1FBO, _shader2FBO;
};

#endif