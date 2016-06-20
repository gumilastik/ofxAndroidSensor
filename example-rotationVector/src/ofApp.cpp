#include "ofApp.h"
#include "HelperFunctions.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofEnableDepthTest();
    ofBackground(255, 255, 255);
    ofSetColor(0, 0, 0);

    sensor = new ofxAndroidSensor(SENSOR_TYPE_ROTATION_VECTOR);
}

//--------------------------------------------------------------
void ofApp::exit()
{
    delete sensor;
}

//--------------------------------------------------------------
void ofApp::update()
{
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofVec3f sensorData = sensor->GetData();

    ofPushMatrix();
    ofPushStyle();

    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

    ofMatrix4x4 mat;
    GetRotationMatrixFromVector(mat.getPtr(), sensorData.getPtr());
    ofVec3f euler = QuatToEuler(mat.getRotate());
    euler.x = -euler.x;
    euler.z = -euler.z;
    mat.setRotate(EulerToQuat(euler));
    ofMultMatrix(mat);

    ofDrawRotationAxes(300, 10, 60);
    ofSetColor(128, 128, 128);
    ofDrawBox(100, 100, 100);

    ofPopStyle();
    ofPopMatrix();

    char buf[100];
    sprintf(buf, "SENSOR_TYPE_ROTATION_VECTOR: %.3f, %.3f, %.3f", sensorData.x, sensorData.y, sensorData.z);
    ofDrawBitmapString("test sensors", 20, 20);
    ofDrawBitmapString(buf, 20, 40);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::touchDown(int x, int y, int id)
{
}

//--------------------------------------------------------------
void ofApp::touchMoved(int x, int y, int id)
{
}

//--------------------------------------------------------------
void ofApp::touchUp(int x, int y, int id)
{
}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(int x, int y, int id)
{
}

//--------------------------------------------------------------
void ofApp::touchCancelled(int x, int y, int id)
{
}

//--------------------------------------------------------------
void ofApp::swipe(ofxAndroidSwipeDir swipeDir, int id)
{
}

//--------------------------------------------------------------
void ofApp::pause()
{
}

//--------------------------------------------------------------
void ofApp::stop()
{
}

//--------------------------------------------------------------
void ofApp::resume()
{
}

//--------------------------------------------------------------
void ofApp::reloadTextures()
{
}

//--------------------------------------------------------------
bool ofApp::backPressed()
{
    return false;
}

//--------------------------------------------------------------
void ofApp::okPressed()
{
}

//--------------------------------------------------------------
void ofApp::cancelPressed()
{
}
