/*
 *  asiUtils.cpp
 *  asiExample
 *
 *  Created by Philip Whitfield on 8/26/10.
 *  Copyright 2010 undef.ch. All rights reserved.
 *
 */

#include "asiTypes.h"
#include "asiObject.h"

ofxVec3f asiBounds::get(int i){
	ofxVec3f ret = points[i];
	if(obj != NULL){
		ret *= obj->scale;
	}
	return ret;
};

asiObjectContainer::asiObjectContainer():asiObjectBase(){
	
};

asiObjectContainer::~asiObjectContainer(){
	
};

void asiObjectContainer::addObject(asiObjectBase* obj){
	asiData::addObject(obj);
	obj->scene = scene;
	objNames.push_back(obj->name);
}

void asiObjectContainer::drawObjects(){
	for (int i=0; i<objNames.size(); i++) {
		asiData::getObject(objNames[i])->draw();
	}
}

void asiObjectContainer::resetObjects(){
	for (int i=0; i<objNames.size(); i++) {
		asiData::getObject(objNames[i])->reset();
	}
}

void asiObjectContainer::updateObjects(){
	
}