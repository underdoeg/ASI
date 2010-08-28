/*
 *  asiSequence
 *  asiExample
 *
 *  Created by Philip Whitfield on 8/26/10.
 *  Copyright 2010 undef.ch. All rights reserved.
 *
 */

#include "asiSequence.h"


asiSequence::asiSequence(){
	running = false;
};

asiSequence::~asiSequence(){

};

void asiSequence::update(float frame){
	if(!running){
		if(frame>=startFrame && frame<startFrame+1){
			start();
			running = true;
		}
	}else {
		int t = startFrame+length;
		if(frame>=t && frame<t+1){
			stop();
			running = false;
		}
	}
}