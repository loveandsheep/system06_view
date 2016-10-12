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
	
	if (row > column) swap(row, column);
	
	curRow = row;
	curColumn = column;
	
}

void unitDrawer::draw()
{
	float margine = 200;
	float tgs = margine * 0.20;
	frame++;
	
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
			ofPushMatrix();
			ofTranslate(margine*j, margine*i);
			
			float noise = ofNoise(i * 234.23, j * 523.32);
			float rad = ofxeasing::map_clamp(frame, 20, 40 + noise * 40, 0.0, tgs, ofxeasing::elastic::easeOut);
			float ring = ofxeasing::map_clamp(frame, 0, 15 + noise * 5, 0.0, 1.0, ofxeasing::quad::easeInOut);
			
			ofPushMatrix();
			glScalef(tgs, tgs, 1.0);
			ofRotateZ(noise * 500 - ofxeasing::map_clamp(frame, 0, 15, 0.0, 400, ofxeasing::quad::easeInOut));
			glLineWidth(2.0);
			glDrawArrays(GL_LINE_STRIP, 1, (circle.size() - 1) * ring);
			ofPopMatrix();

			glScalef(rad, rad, 1.0);
			glDrawArrays(GL_TRIANGLE_FAN, 0, circle.size());
			
			ofPopMatrix();
		}
	}
	ofPopMatrix();
}
