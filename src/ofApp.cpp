#include "ofApp.h"

int winWidth = 1600;
int winHeight = 900;
int filmWidth = 0;
int filmHeight = 0;
int centerX = 0;
int centerY = 0;
bool showInfo = true;

void ofApp::loadMovie(string path) {
    currMovie.loadMovie(path);
    if (currMovie.isLoaded()) {
        filmWidth = currMovie.getWidth() * 2;
        filmHeight = currMovie.getHeight() * 2;
        currMovie.setLoopState(OF_LOOP_NONE);
        currMovie.play();
    } else {
        ofSystemAlertDialog("Could not load " + path);
        selectMovie();
    }
}

void ofApp::selectMovie() {
    ofFileDialogResult file = ofSystemLoadDialog("Select a movie to play", false);
    if (file.bSuccess) {
        loadMovie(file.getPath());
    } else {
        selectMovie();
    }
}


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetWindowTitle("DomePlayer");
    ofSetWindowShape(winWidth, winHeight);
    ofBackground(0,0,0);
    ofSetVerticalSync(true);
    selectMovie();
}

//--------------------------------------------------------------
void ofApp::update(){
    ofPoint p = ofGetWindowSize();
    winWidth = p.x;
    winHeight = p.y;
    centerX = round((winWidth - filmWidth) / 2);
    centerY = round((winHeight - filmHeight) / 2);
    currMovie.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (showInfo) {
        ofSetColor(150,0,0);
        ofDrawBitmapString(currMovie.getMoviePath() + " " +
                           " " + ofToString(round(currMovie.getPosition() * 100)) + "%" +
                           " " + ofToString(currMovie.getSpeed()) +
                           " " + ofToString(currMovie.getWidth()) +
                           "x" + ofToString(currMovie.getHeight()) +
                       
                           " " + ofToString(currMovie.getDuration()) +
                           " " + ofToString(round(ofGetFrameRate()))+"fps"
                           , 10, 15);
        ofDrawBitmapString("info: ?, fullscreen: f, pause: space, size: + -, position: arrows"
                           , 10, winHeight - 15);
    }
    ofSetColor(255,255,255);
    currMovie.draw(centerX + offsetX, centerY + offsetY, filmWidth, filmHeight);
    if (currMovie.getIsMovieDone()) {
        currMovie.closeMovie();
        selectMovie();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == '+' || key == '=') {
        filmWidth += round(currMovie.getWidth() * .10);
        filmHeight += round(currMovie.getHeight() * .10);
    } else if (key == '-' || key == '_') {
        filmWidth -= round(currMovie.getWidth() * .10);
        filmHeight -= round(currMovie.getHeight() * .10);
    } else if (key == ' ') {
        currMovie.setPaused(!currMovie.isPaused());
    } else if (key == 'f' || key == 'F') {
        ofToggleFullscreen();
    } else if (key == '?' || key == '/') {
        showInfo = !showInfo;
    } else if (key == OF_KEY_LEFT) {
        offsetX = offsetX - 10;
    } else if (key == OF_KEY_RIGHT) {
        offsetX = offsetX + 10;
    } else if (key == OF_KEY_UP) {
        offsetY = offsetY - 10;
    } else if (key == OF_KEY_DOWN) {
        offsetY = offsetY + 10;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}