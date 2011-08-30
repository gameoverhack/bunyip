/*
 *  VideoView.h
 *  Bunyip
 *
 *  Created by gameover on 29/08/11.
 *  Copyright 2011 trace media. All rights reserved.
 *
 */

#ifndef _H_VIDEOVIEW
#define _H_VIDEOVIEW

#include "BaseView.h"
#include "goThreadedVideo.h"

class VideoView : public BaseView {
	
public:
	
	VideoView(float width, float height, int layerIndex, string videoPath = "", ViewPort* viewPort = NULL);
	~VideoView();
	
	void update();
	
	string					getVideoPath() {return _videoPath;};
	goThreadedVideo*		getVideo() {return _video;};
	
	void loadMovie(string videoPath = "");
	
private:
	
	goThreadedVideo*		_video;
	int						_layerIndex;
	
	string					_videoPath;
	
};

#endif