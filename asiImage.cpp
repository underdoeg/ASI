/*
 *  asiImage.cpp
 *  asiExample
 *
 *  Created by Philip Whitfield on 8/26/10.
 *  Copyright 2010 undef.ch. All rights reserved.
 *
 */

#include "asiImage.h"

asiImage::asiImage(){
	imgLoaded = false;
};

asiImage::~asiImage(){
	
};

ofImage* asiImage::getImage(){
	return &img;
}

void asiImage::loadImg(string path){
	imgLoaded = img.loadImage(asiData::toPath(path));
	if(!imgLoaded)
		cout << "could not load " << path;
}

void asiImage::bind(){
	if(!imgLoaded)
		return;
	img.getTextureReference().bind();
}

void asiImage::unbind(){
	if(!imgLoaded)
		return;
	img.getTextureReference().unbind();
}

int asiImage::getTexScaleW(){
	if(!imgLoaded)
		return 1;
	return img.getTextureReference().texData.tex_w;
}
int asiImage::getTexScaleH(){
	if(!imgLoaded)
		return 1;
	return img.getTextureReference().texData.tex_h;
}