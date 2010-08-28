/*
 *  asiObject.h
 *  asiExample
 *
 *  Created by Philip Whitfield on 8/26/10.
 *  Copyright 2010 undef.ch. All rights reserved.
 *
 */

#ifndef _CLASS_asiObject_
#define _CLASS_asiObject_

#include "ofMain.h"
#include "ofxVectorMath.h"
#include "asiTypes.h"
#include "asiImage.h"
#include "asiAnimator.h"

class asiObject: public asiObjectContainer{
public:
	asiObject();
	~asiObject();
	void addVert(asiVert v);
	void addFace(asiFace f);
	void draw();
	
	asiObjectContainer* parent;
	std::vector<asiVert> verts;
	std::vector<asiFace> faces;
protected:
private:
};

#endif