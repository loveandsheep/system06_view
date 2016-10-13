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
	
	if (ofGetFrameNum() % 60 == 0)
	{
		if (lastBangId == -1)
		{
			lastBangId = 0;
			units[lastBangId].flip(false);
		}
		else
		{
			for (int i = 0;i < row;i++)
			{
				for (int j = 0;j < column;j++)
				{
					int idx = i * column + j;
					int lb_r = lastBangId / curColumn;
					int lb_c = lastBangId % curColumn;
					
					//評価を計測
					units[idx].tmp_Score = 0;
					
					if ((abs(lb_r - units[idx].rId) < 2) &&//隣り合う
						(abs(lb_c - units[idx].cId) < 2))
					{
						units[idx].tmp_Score += 50;
					}
					
//					if (
				}
			}
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
	float tgs = margine * 0.20;
	
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
				rad = ofxeasing::map_clamp(units[idx].animFrame, 0, 20 + ns * 20, tgs, 0.0, ofxeasing::quad::easeInOut);
				
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
}
