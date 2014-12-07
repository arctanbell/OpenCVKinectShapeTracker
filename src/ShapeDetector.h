#pragma once

#include "ofMain.h"
#include "ShapeDetector.h"
#include "ofxKinectCommonBridge.h"
#include "ofxCv.h"
#include "ofxUI.h"
#include "ofxImageSegmentation.h"

#define SHAPE_COLOR_COUNT 8
typedef int ShapeColor;

//TODO 
//-- run contours on each segment
//-- show stats of contours, filter by compactness
//-- clean up from old color way
//-- add instructions to interface

//OPTIMIZATIONS
//-- optimize kinect
//-- optimize image segmenter

struct ShapeContour {
	
	//FROM SCAN
	ofPolyline contour;
	
	//FROM CV
	cv::Rect boundingRect;
	cv::RotatedRect fitEllipse;
	cv::RotatedRect fitRect;
	
	ofVec2f circlePosition;
	float circleRadius;
	float rectMaxSide;
	
	//COMPUTED
	float depthPosition; //depth of sensed position
	float coordRadius; //radius of sense cross section

	//shape info
	//ShapeColor color;
	float contourArea;
};

/*
class ColorSlider {
  public:
	ColorSlider(){
		hueRange = 0;
		saturationRange = 0;
		valueRange = 0;
	};

	ofRectangle samplePos;
	ofRectangle hpos;
	ofRectangle spos;
	ofRectangle vpos;
	ofColor color;
	int hueRange;
	int saturationRange;
	int valueRange;
};
*/

class ShapeDetector
{
  public:
	void setup();
	void update();
	void draw();
	void exit();

	void mouseMoved(ofMouseEventArgs& args);
	void mouseDragged(ofMouseEventArgs& args);
	void mousePressed(ofMouseEventArgs& args);
	void mouseReleased(ofMouseEventArgs& args);

	void findShapes();

  protected:

	void drawDebug(bool zoom);

	ofxKinectCommonBridge kinect;
	ofxImageSegmentation imageSegmentation;
	int depthImageWidth;
	int depthImageHeight;

	ofxUISuperCanvas* gui;
	float minScanDistance;
	float maxScanDistance;
	float minArea;
	float maxArea;

	//visualization parameters
	bool showAllContours;
	bool previewColors;
	bool previewEllipseFit;
	bool previewRectFit;
	bool previewCircleFit;
	bool previewStats;

//	int sampleColorIndex;

//	void saveColors();
//	void loadColors();

	void createDepthMasks();
	//void createColorMask(ShapeColor colorIndex);
	//void createColorMasks();

//	cv::Mat hsvImage;
//	cv::Mat tempThresh;
	ofImage depthColors;
	ofImage segmentedDepthColors;
//	ofPixels contourPix;

	ofFbo zoomFbo;
	ofVec2f zoomPoint;

//	vector<bool> sampleConnectors;
//	vector< vector<ColorSlider> > colorSamples;
	vector<ofShortImage> segmentedDepthImages;
	vector<ofImage> segmentedColorImages;
	vector<ShapeContour> contours;
//	vector<ColorSlider> colorSliders;

	string getSettingsFilename();
//	string getColorFilename();
//	string getColorRangeFilename();


};
