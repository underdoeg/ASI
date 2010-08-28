/*
 *  asiUtils.h
 *  asiExample
 *
 *  Created by Philip Whitfield on 8/26/10.
 *  Copyright 2010 undef.ch. All rights reserved.
 *
 */
#ifndef ASI_SETTINGS
#define ASI_SETTINGS
#include "ofMain.h"
#include "ofxVectorMath.h"
#include "asiData.h"
#include "asiGeomTypes.h"
#include "asiAnimator.h"

struct asiSettings{
	asiSettings(){
		play = true;
		loop = true;
		doCamera = true;
		autoResize = true;
	}
	bool play;
	bool loop;
	bool doCamera;
	bool autoResize;
};

enum ASI_DIR {
	ASI_TOPLEFTFRONT, ASI_TOPLEFTBACK, ASI_TOPRIGHTFRONT, ASI_BOTTOMLEFTFRONT, ASI_BOTTOMLEFTBACK, ASI_TOPRIGHTBACK, ASI_BOTTOMRIGHTFRONT, ASI_BOTTOMRIGHTBACK
};

#define ASI_TOPLEFT ASI_TOPLEFTFRONT
#define ASI_BOTTOMLEFT ASI_BOTTOMLEFTFRONT
#define ASI_TOPRIGHT ASI_TOPRIGHTFRONT
#define ASI_BOTTOMRIGHT ASI_BOTTOMRIGHTFRONT

class asiBounds{
public:
	asiBounds(){
		
	}
	
	void set(int pos, float x, float y, float z){
		points[pos].set(x,y,z);
	}
	
	void set(int pos, ofxVec3f v){
		points[pos]=v;
	}
	
	ofxVec3f operator[](int i){
		return points[i]; 
	}
	ofxVec3f points[8];
};

class asiObjectBase: public ofxVec3f{
public:
	string name;
	ofxVec3f scale;
	ofxVec3f rotation;
	
	ofxVec3f origScale;
	ofxVec3f origRotation;
	ofxVec3f origPos;
	
	asiScene* scene;
	
	asiBounds bounds;
	
	void setOriginal(){
		origScale.set(scale);
		origRotation.set(rotation);
		origPos.set(this->x, this->y, this->z);
	}
	
	void readOriginal(){
		scale.set(origScale);
		rotation.set(origRotation);
		this->set(origPos);
	}
	
	void reset(){
		readOriginal();
	}
	
	virtual void draw(){
		
	}
	
	virtual void update(){
		
	}
	
	bool linkTween(asiTween* t){
		bool done = false;
		if(t->path.compare("location")==0){
			if(t->index == 0){
				t->val = &x;
				done = true;
			}
			if(t->index == 1){
				t->val = &y;
				done = true;
			}
			if(t->index == 2){
				t->val = &z;
				done = true;
			}
		}else if(t->path.compare("rotation_euler")==0){
			if(t->index == 0){
				t->val = &rotation.x;
				done = true;
			}
			if(t->index == 1){
				t->val = &rotation.y;
				done = true;
			}
			if(t->index == 2){
				t->val = &rotation.z;
				done = true;
			}
		}else if(t->path.compare("scale")==0){
			if(t->index == 0){
				t->val = &scale.x;
				done = true;
			}
			if(t->index == 1){
				t->val = &scale.y;
				done = true;
			}
			if(t->index == 2){
				t->val = &scale.z;
				done = true;
			}
		}
		
		bool doneSpecial = linkTweenSpecial(t);
		
		if(doneSpecial)
			return doneSpecial;
		else
			return done;
	}
	
	virtual bool linkTweenSpecial(asiTween* t){return false;};
};

class asiObjectContainer: public asiObjectBase{
public:
	asiObjectContainer();
	~asiObjectContainer();
	void addObject(asiObjectBase* obj);
	void drawObjects();
	void updateObjects();
	void resetObjects();
	
	std::vector<string> objNames;
protected:
private:
};

#endif