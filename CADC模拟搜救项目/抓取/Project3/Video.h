#define _VIDEO_H_
#ifdef _VIDEO_H_
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;



void videoCalibration(Mat *frameCalibration, Mat frame);
void videoCalibration1(Mat* frameCalibration, Mat frame);
void VideoCut(Mat img, Mat *out, float a);
void Video_init(VideoCapture capture, VideoCapture capture1);
Mat comMatR(Mat Matrix1, Mat Matrix2, Mat &MatrixCom);
void xuanzhuan(Mat src, Mat *out);
#endif