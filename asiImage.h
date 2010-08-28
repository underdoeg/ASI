/*
 *  asiImage.h
 *  asiExample
 *
 *  Created by Philip Whitfield on 8/26/10.
 *  Copyright 2010 undef.ch. All rights reserved.
 *
 */

#ifndef _CLASS_asiImage_
#define _CLASS_asiImage_
#include "ofMain.h"
#include "asiData.h"

class asiImage{
public:
	asiImage();
	~asiImage();
	void loadImg(string path);
	void bind();
	void unbind();
	ofImage* getImage();
	int getTexScaleW();
	int getTexScaleH();
	
	string name;
	bool imgLoaded;
	
protected:
private:
	ofImage img;
};

#endif