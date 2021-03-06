#include "pch.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <algorithm>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


using namespace std;
using namespace cv;


int main()
{
	string request;
	CascadeClassifier cascade;
	cout << "What do you want to detect? (Face/Eyes/Profile/Body)" << endl;
	cin >> request;
	if (request == "face" || request == "Face") {
		cout << "Face detection started" << endl;
		cascade.load("C:\\Users\\user\\Documents\\GitHub\\imagemanipulation\\libs\\opencv\\data\\haarcascades_cuda\\haarcascade_frontalface_alt.xml");
	}
	else if (request == "eyes" || request == "Eyes") {
		cout << "Eyes detection started" << endl;
		cascade.load("C:\\Users\\user\\Documents\\GitHub\\imagemanipulation\\libs\\opencv\\data\\haarcascades_cuda\\haarcascade_eye_tree_eyeglasses.xml");
	} 
	else if (request == "profile" || request == "Profile") {
		cout << "Profile face detection started" << endl;
		cascade.load("C:\\Users\\user\\Documents\\GitHub\\imagemanipulation\\libs\\opencv\\data\\haarcascades_cuda\\haarcascade_profileface.xml");
	} else {
		cout << "Body detection started" << endl;
		cascade.load("C:\\Users\\user\\Documents\\GitHub\\imagemanipulation\\libs\\opencv\\data\\haarcascades_cuda\\haarcascade_fullbody.xml");
	}
	VideoCapture capture(0);
	if (!capture.isOpened())
		throw "Error when reading file";
	
	for (;;)
	{
		Mat image;
		capture >> image;
		if (image.empty())
			break;

		// Detect piece
		std::vector<Rect> pieces;
		cascade.detectMultiScale(image, pieces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30), cv::Size(480, 480));

		// Draw circles on the detected pieces
		for (int i = 0; i < pieces.size(); i++)
		{
			Point center(pieces[i].x + pieces[i].width*0.5, pieces[i].y + pieces[i].height*0.5);
			ellipse(image, center, Size(pieces[i].width*0.5, pieces[i].height*0.5), 0, 0, 360, Scalar(0, 255, 0), 2, 8, 0);
		}

		imshow("Detected", image);
		waitKey(1);
	}

	return 0;
}