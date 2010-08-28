/*
 *  asiCamera.h
 *  asiExample
 *
 *  Created by Philip Whitfield on 8/26/10.
 *  Copyright 2010 undef.ch. All rights reserved.
 *
 */

#ifndef _CLASS_asiCamera_
#define _CLASS_asiCamera_

#include "asiTypes.h"
#include "ofx3DUtils.h"

class asiCamera: public asiObjectBase{
public:
      asiCamera();
      ~asiCamera();      
	void place();
	float clipStart;
	float clipEnd;
	float lensAngle;
	int imgWidth;
	int imgHeight;
protected:
	ofxCamera cam;
	ofPoint lookDir;
private:
};

#endif