/*
 *  asiGeomTypes.h
 *  asiExample
 *
 *  Created by Philip Whitfield on 8/26/10.
 *  Copyright 2010 undef.ch. All rights reserved.
 *
 */

class asiVert: public ofxVec3f{
	
};

struct asiFace {
	std::vector<int> indexes;
	std::vector<ofxVec2f> uv;
	string img;
};

struct asiTex{
	
};