#define _VIDEO_H_
#ifdef _VIDEO_H_
#include <opencv2/opencv.hpp>
#include <iostream>
//using namespace cv;
using namespace std;

void videoCalibration(cv::Mat *frameCalibration, cv::Mat frame);
//void VideoCut(cv::Mat img, cv::Mat *out, float a);
//cv::Mat comMatR(Mat Matrix1, Mat Matrix2, Mat &MatrixCom);
//void xuanzhuan(Mat src, Mat *out, int z);
#endif