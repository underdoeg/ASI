/*
 *  asiCamera.cpp
 *  asiExample
 *
 *  Created by Philip Whitfield on 8/26/10.
 *  Copyright 2010 undef.ch. All rights reserved.
 *
 */

#include "asiCamera.h"


asiCamera::asiCamera(){
	cam.up(0, 1, 0);
	//cam.perspective();
	cam.setOrigin(OF_ORIGIN_ZERO);
	lookDir.set(0, 0, -3);
};

asiCamera::~asiCamera(){

};

void asiCamera::place(){
	cam.position(x,y,z);
	cam.perspective(RAD_TO_DEG*lensAngle*.585, imgWidth/(float)imgHeight, clipStart, clipEnd);
	cam.eye(x+lookDir.x, y+lookDir.y, z+lookDir.z);
	cam.rotate(ofxVec3f(1,0,0), RAD_TO_DEG*rotation.x);
	cam.rotate(ofxVec3f(0,1,0), RAD_TO_DEG*rotation.y);
	cam.rotate(ofxVec3f(0,0,1), RAD_TO_DEG*rotation.z);
	cam.place();
}