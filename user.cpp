#include <iostream>
#include "user.h"
#include <opencv2/opencv.hpp> //define opencv libraries
#include <iostream>
#include <vector> // define vector + iostream
using namespace std;
using namespace cv; //match syntax





void user::getrate(){
    cout << "What do you want the slow-mo rate to be (1 for default, 200 for very slow): "; //prompt user for camera-speed
    cin >> rate;
    cout << rate << endl;
}


void user::xchoice() {
    string datasetChoice; //prompt user for xml sheet for different object detection sets
    cout << "=== Dataset Menu ===" << endl;
    cout << "1. Cat dataset" << endl; //menu
    cout << "2. Face dataset" << endl;
    cout << "3. Eye dataset" << endl;
    cout << "4. Smile dataset (most false positives)" << endl;
    cout << "====================" << endl;
    cout << "Enter the number corresponding to the dataset you want to use: "; //gather input
    cin >> datasetChoice;

    if (datasetChoice == "1") {
        cout << "You chose the cat dataset." << endl;
        finalxml = "haarcascade_frontalcatface.xml";
    }
    else if (datasetChoice == "2") {
        cout << "You chose the face dataset." << endl; //set value back in class
        finalxml = "haarcascade_frontalface_default.xml";
    }
    else if (datasetChoice == "3") {
        cout << "You chose the eye dataset." << endl;
        finalxml = "haarcascade_eye.xml";
    }
    else if (datasetChoice == "4") {
        cout << "You chose the smile dataset." << endl;
        finalxml = "haarcascade_smile.xml";
    }
    else {
        cout << "Invalid choice." << endl;
    }

    cout << "XML choice: " << finalxml << endl;
}

void user::createprogram() { //initalize opencv program
    Mat img; //image matrix
    int counter = 0; //count for object detect #
    CascadeClassifier face;
    if (!face.load(finalxml)) {
        throw runtime_error("xml datasheet not loading"); //error-handling + throw errors
    }

    VideoCapture video(0); //opencv video capture of camera 1 (as 0)
    if (!video.isOpened()) {
        cout << "video stream bug\n";
        throw runtime_error("vid stream error");
    }

    while (true) { //while camera is on
        video.read(img);
        if (img.empty()) { //error handling
            cout << "image camera capture error\n";
            throw runtime_error("image capt error");
        }

        vector<Rect> faces; //creates vector of reactangles to highlight faces
        face.detectMultiScale(img, faces, 1.1, 5, 0 | CASCADE_SCALE_IMAGE, Size(30, 30)); //main opencv method to detect faces and create elements of faces rect vector 
        //in order: input img, stores rectangles of faces, scalefactor for detection, minNeighbors -> detection method to recogniz many other flagged neighbors there are, helps with false positives, size: minimum size of dectected elements 

        for (size_t i = 0; i < faces.size(); i++) { //iterates through image's vector rects
            rectangle(img, faces[i].tl(), faces[i].br(), Scalar(50, 50, 255), 3); //draws a line from the top-left bounding box to the bottom right corner for rectangle, scalar is for color of rect ring.
            cout << "Face found\n"; //report and add to counter
            counter+=1;
        }

        imshow("Frame", img); //shows frame as window
        if (waitKey(rate) >= 0) break; //error handling -> if rate is less than or equal to 0
    }

    cout << "OpenCV dectected " << counter << " instances of your object!"; //report results
}