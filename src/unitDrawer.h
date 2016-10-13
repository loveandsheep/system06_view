//
//  unitDrawer.hpp
//  system06_view
//
//  Created by Ovis aries on 2016/10/12.
//
//

#ifndef unitDrawer_hpp
#define unitDrawer_hpp

#include "ofMain.h"
#include "ofxEasing.h"

class simUnit{
public:
	
	int rId;
	int cId;
	bool ballStat = true;
	int animFrame = 0;
	int tmp_Score;
	
	void flip()
	{
		ballStat ^= true; animFrame = 0;
	}
	void flip(bool b)
	{
		ballStat = b;
		animFrame = 0;
	}
};

class unitDrawer{

public:
	unitDrawer();
	
	void set(int row, int column);
	void clear();
	
	void update();
	void draw();
	
	int lastBangId = -1;
	int curRow, curColumn;
	int frame;
	
	bool isClear;
	int clearFrame;
	
	vector<ofVec2f> circle;
	vector<simUnit> units;
};

#endif /* unitDrawer_hpp */
