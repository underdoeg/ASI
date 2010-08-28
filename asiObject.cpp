/*
 *  asiObject.cpp
 *  asiExample
 *
 *  Created by Philip Whitfield on 8/26/10.
 *  Copyright 2010 undef.ch. All rights reserved.
 *
 */

#include "asiObject.h"


asiObject::asiObject(){
	parent = NULL;
};

asiObject::~asiObject(){

};

void asiObject::addVert(asiVert v){
	verts.push_back(v);
}

void asiObject::addFace(asiFace f){
	faces.push_back(f);
}

void asiObject::draw(){
	ofFill();
	ofSetColor(255, 255, 255);
	ofPushMatrix();

	ofTranslate(x, y, z);

	ofRotateX(RAD_TO_DEG*rotation.x);
	ofRotateY(RAD_TO_DEG*rotation.y);
	ofRotateZ(RAD_TO_DEG*rotation.z);
	ofPushMatrix();
	
	if(scale.x != 0 && scale.y != 0 && scale.z != 0)
		ofScale(scale.x, scale.y, scale.z);
	ofEnableAlphaBlending();
	for(int i=0;i<faces.size();i++){
		float tW = 1;
		float tH = 1;
		if(!faces[i].img.empty()){
			asiImage* img = asiData::getImage(faces[i].img);
			img->bind();
			tW = img->getTexScaleW();
			tH = img->getTexScaleH();
		}
		glBegin(GL_POLYGON);
		for(int j=0;j<faces[i].indexes.size();j++){
			asiVert v = verts[faces[i].indexes[j]];
			if(faces[i].uv.size()>=j)
				glTexCoord2f ((faces[i].uv[j].x)*tW, (1-faces[i].uv[j].y)*tH);
			glVertex3f(v.x, v.y, v.z);
		}
		
		glEnd();
		if(!faces[i].img.empty()){
			asiImage* img = asiData::getImage(faces[i].img);
			img->unbind();
		}
	}
	ofPopMatrix();
	ofDisableAlphaBlending();
	drawObjects();
	ofPopMatrix();
}