#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

//	ud.set(ofRandom(1, 4), ofRandom(1, 7));
	ud.set(3,6);
	ofSetFrameRate(30);
}

//--------------------------------------------------------------
void ofApp::update()
{
	ofHideCursor();
	ud.update();
	
	if (ofGetFrameNum() % 3000 == 0)
	{
		ud.set(ofRandom(1, 4), ofRandom(1, 7));
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	ofSetColor(50);
//	ofDrawLine(0, ofGetHeight() / 2.0, ofGetWidth(), ofGetHeight() / 2.0);
//	ofDrawLine(ofGetWidth() / 2.0, 0, ofGetWidth() / 2.0, ofGetHeight());

	ud.draw();
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'c') ud.clear();
	if (key == 's') ud.set(ofRandom(1, 4), ofRandom(1, 7));
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
