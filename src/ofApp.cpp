#include "ofApp.h"


#include "boxparse.h"
#include <fstream>
#include <string>
#include <streambuf>


static int pts[] = {257,219,257,258,259,274,263,325,266,345,266,352,269,369,276,387,286,415,291,425,302,451,308,462,316,472,321,480,328,488,333,495,339,501,345,505,350,507,365,515,370,519,377,522,382,525,388,527,405,534,426,538,439,539,452,539,468,540,485,540,496,541,607,541,618,539,625,537,641,530,666,513,682,500,710,476,723,463,727,457,729,453,732,450,734,447,738,440,746,423,756,404,772,363,779,343,781,339,784,327,789,301,792,278,794,267,794,257,795,250,795,232,796,222,796,197,797,195,797,188,796,188};
static int nPts  = 61*2;

//--------------------------------------------------------------
void ofApp::setup(){
	std::ifstream stream("data/examplelvl.json");
	std::string json((std::istreambuf_iterator<char>(stream)),
					 std::istreambuf_iterator<char>());
	vector<parse::Polygon> polys = parse::parsePolygons(json, ofGetWidth(), ofGetHeight());
	
	ofSetVerticalSync(true);
	ofBackgroundHex(0x0);
	ofSetLogLevel(OF_LOG_NOTICE);

	box2d.init();
	box2d.setGravity(0, 10);
	box2d.createGround();
	box2d.setFPS(30.0);
	box2d.registerGrabbing();

	// lets add a contour to start
	/*for (int i=0; i<nPts; i+=2) {
		float x = pts[i];
		float y = pts[i+1];
		edgeLine.addVertex(x, y);
	}*/

	// make the shape
	edgeLine.setPhysics(0.0, 0.5, 0.5);
	edgeLine.create(box2d.getWorld());

	for (int i=0; i < polys.size(); ++i)
	{
		/* code */
		parse::Polygon p = polys[i];
		ofPtr<ofxBox2dEdge> edge(new ofxBox2dEdge);
		ofLog() << "numPoints:" << p.size();
		for (int i = 0; i < p.size(); ++i)
		{
			edge->addVertex(p[i].x,p[i].y);
			ofLog() << "Point: " << i << " (" << p[i].x << "," << p[i].y;
		}
		//edge.addVertexes(p);
		edge->setPhysics(0.0, 0.5, 0.5);
		edge->create(box2d.getWorld());
		edgesFromEdge.push_back(edge);
	}
	ofLog() << "edges:" << edgesFromEdge.size();

}

//--------------------------------------------------------------
void ofApp::update(){
	box2d.update();


 	// remove shapes offscreen
    ofRemove(boxes, ofxBox2dBaseShape::shouldRemoveOffScreen);
    ofRemove(circles, ofxBox2dBaseShape::shouldRemoveOffScreen);
}

//--------------------------------------------------------------
void ofApp::draw(){
	//Circles
	for(int i=0; i<circles.size(); i++) {
		ofFill();
		ofSetHexColor(0x90d4e3);
		circles[i].get()->draw();
	}
	//Boxes
	for(int i=0; i<boxes.size(); i++) {
		ofFill();
		ofSetHexColor(0xe63b8b);
		boxes[i].get()->draw();
	}
	//Edges
	ofNoFill();
	ofSetHexColor(0x444342);
	//ofLog() << "edges:" << edgesFromEdge.size();

	for (int i = 0; i < edgesFromEdge.size(); ++i)
	{
		edgesFromEdge[i]->updateShape();
		edgesFromEdge[i]->draw();
	}

	

	//edges
	//edgeLine.updateShape();
	//edgeLine.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == 'c') {
		float r = ofRandom(4, 20);		// a random radius 4px - 20px
		circles.push_back(ofPtr<ofxBox2dCircle>(new ofxBox2dCircle));
		circles.back().get()->setPhysics(3.0, 0.53, 0.1);
		circles.back().get()->setup(box2d.getWorld(), mouseX, mouseY, r);
		
	}

	if(key == 'b') {
		float w = ofRandom(4, 20);	
		float h = ofRandom(4, 20);	
		boxes.push_back(ofPtr<ofxBox2dRect>(new ofxBox2dRect));
		boxes.back().get()->setPhysics(3.0, 0.53, 0.1);
		boxes.back().get()->setup(box2d.getWorld(), mouseX, mouseY, w, h);
	}

	if (key == 'f')
	{
		//fullscreen
		ofToggleFullscreen();
	}

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
