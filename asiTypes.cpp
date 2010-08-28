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

asiObjectContainer::asiObjectContainer(){
	
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