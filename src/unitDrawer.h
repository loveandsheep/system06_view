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

class unitDrawer{

public:
	unitDrawer();
	
	void set(int row, int column);
	void draw();
	
	int curRow, curColumn;
	int frame;
	
	vector<ofVec2f> circle;
};

#endif /* unitDrawer_hpp */
