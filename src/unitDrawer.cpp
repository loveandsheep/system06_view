//
//  unitDrawer.cpp
//  system06_view
//
//  Created by Ovis aries on 2016/10/12.
//
//

#include "unitDrawer.h"

unitDrawer::unitDrawer()
{
	circle.push_back(ofVec2f(0, 0));
	for (int i = 0;i <= 360;i+=3)
	{
		circle.push_back(ofVec2f(sin(ofDegToRad(i)), cos(ofDegToRad(i))));
	}
	
}

void unitDrawer::set(int row, int column)
{
	frame = 0;
	isClear = false;
	
	if (row > column) swap(row, column);
	
	curRow = row;
	curColumn = column;
	
	units.resize(row * column, simUnit());
	for (int i = 0;i < row;i++)
	{
		for (int j = 0;j < column;j++)
		{
			int idx = i * column + j;
			units[idx].rId = i;
			units[idx].cId = j;
			units[idx].flip(true);
		}
	}
	
}

void unitDrawer::update()
{
	for (int i = 0;i < curRow; i++)
	{
		for (int j = 0;j < curColumn;j++)
		{
			int idx = i * curColumn + j;
			units[idx].animFrame++;
		}
	}
	
	if (!isClear)
	{
		if (frame > 30)
		{
			static int step2 = 3;
			if (ofGetFrameNum() % step2 == 0)
			{
				step2 = ofRandom(10, 50);
				int idx = int(ofRandom(100)) % units.size();
				if (!units[idx].ballStat)
				{
					units[idx].flip(true);
				}
			}
			
			static int step = 3;
			if (ofGetFrameNum() % step == 0)
			{
				step = ofRandom(10, 100);
				simUnit *targ = NULL;
				for (int i = 0;i < curRow;i++)
				{
					for (int j = 0;j < curColumn;j++)
					{
						int idx = i * curColumn + j;
						
						if (!units[idx].ballStat) continue;
						
						if (targ == NULL)
						{
							targ = &units[idx];
						}else{
							if (targ->ballStat && units[idx].ballStat)
							{
								if (targ->animFrame < units[idx].animFrame)
								{
									targ = &units[idx];
								}
							}
						}
					}
				}
				
				if (targ) targ->flip(false);
			}

		}
	}
}

void unitDrawer::clear()
{
	isClear = true;
	clearFrame = 0;
	
	for (int i = 0;i < curRow;i++)
	{
		for (int j = 0;j < curColumn;j++)
		{
			int idx = i * curColumn + j;
			units[idx].rId = i;
			units[idx].cId = j;
			units[idx].flip(false);
		}
	}
}

void unitDrawer::draw()
{
	float margine = 200;
	float tgs = margine * 0.25;
	
	frame++;
	if (isClear) clearFrame++;
	
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2.0 - (curColumn - 1) * margine / 2.0,
				ofGetHeight() / 2.0 - (curRow - 1) * margine / 2.0);
	
	ofSetColor(255);
	for (int i = 0;i < curRow; i++)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, &circle[0]);
		for (int j = 0;j < curColumn;j++)
		{
			int idx = i * curColumn + j;

			ofPushMatrix();
			ofTranslate(margine*j, margine*i);
			
			float ns = ofNoise(i * 934.23, j * 523.32);
			float rad;
			
			if (units[idx].ballStat)
				rad = ofxeasing::map_clamp(units[idx].animFrame, 20, 50 + ns * 40, 0.0, tgs, ofxeasing::elastic::easeOut);
			else
				rad = ofxeasing::map_clamp(units[idx].animFrame, 0, 5 + ns * 5, tgs, 0.0, ofxeasing::quad::easeOut);
				
			float ring = ofxeasing::map_clamp(frame, 0, 15 + ns * 5, 0.0, 1.0, ofxeasing::quad::easeInOut);
			
			if (isClear)
			{
				ring = ofxeasing::map_clamp(clearFrame, 30, 55 + ns * 5, 1.0, 0.0, ofxeasing::quad::easeInOut);
			}
			
			ofPushMatrix();
			glScalef(tgs, tgs, 1.0);
			ofRotateZ(ns * 500 - ofxeasing::map_clamp(frame, 0, 15, 0.0, 400, ofxeasing::quad::easeInOut));
			glLineWidth(2.0);
			glDrawArrays(GL_LINE_STRIP, 1, (circle.size() - 1) * ring);
			ofPopMatrix();

			ofPushMatrix();
			glScalef(rad, rad, 1.0);
			glDrawArrays(GL_TRIANGLE_FAN, 0, circle.size());
			ofPopMatrix();
			
			ofPopMatrix();
		}
		
		glDisableClientState(GL_VERTEX_ARRAY);
		
	}
	ofPopMatrix();
	
	float line = ofxeasing::map_clamp(frame, 0, 20, 0.0, 1.0, ofxeasing::quad::easeInOut);
	
//	ofPushMatrix();
//	ofTranslate(ofGetWidth() / 2.0 - (curColumn - 1) * margine / 2.0,
//				ofGetHeight() / 2.0 - (curRow - 1) * margine / 2.0);

//	ofSetColor(50);
//	ofEnableBlendMode(OF_BLENDMODE_ADD);
//	for (int i = 0;i < curRow;i++)
//	{
//		ofDrawLine(-2000 * line, margine * i, 2000 * line, margine * i);
//	}
//	for (int i = 0;i < curColumn;i++)
//	{
//		ofDrawLine(margine * i, -1000 * line, margine * i, 1000 * line);
//	}
//	ofPopMatrix();
//	
//	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	
//	ofPushMatrix();
//	ofSetColor(100);
//	ofTranslate(ofGetWidth() / 2.0, ofGetHeight() / 2.0);
//	ofDrawLine(-ofGetWidth() / 2.0 * line, (curRow - 1) * margine / 2.0 + margine * 0.75,
//			   ofGetWidth() / 2.0 * line , (curRow - 1) * margine / 2.0 + margine * 0.75);
//	ofDrawLine(-ofGetWidth() / 2.0 * line, -(curRow - 1) * margine / 2.0 - margine * 0.75,
//			   ofGetWidth() / 2.0 * line , -(curRow - 1) * margine / 2.0 - margine * 0.75);
//	
//	ofDrawLine((curColumn - 1) * margine / 2.0 + margine * 0.75, -ofGetHeight() / 2.0 * line,
//			   (curColumn - 1) * margine / 2.0 + margine * 0.75, ofGetHeight() / 2.0 * line);
//	ofDrawLine(-(curColumn - 1) * margine / 2.0 - margine * 0.75, -ofGetHeight() / 2.0 * line,
//			   -(curColumn - 1) * margine / 2.0 - margine * 0.75, ofGetHeight() / 2.0 * line);
//	ofPopMatrix();

}
