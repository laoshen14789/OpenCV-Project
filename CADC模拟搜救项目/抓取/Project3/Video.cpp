#include"Video.h"
#define A

//#include <opencv2/opencv.hpp>
//#include <iostream>
//using namespace cv;
//using namespace std;


void videoCalibration(Mat* frameCalibration,Mat frame){

#ifdef A
	Mat cameraMatrix = Mat::eye(3, 3, CV_64F);		//1.8mm镜头
	cameraMatrix.at<double>(0, 0) = 2.9231842160057367e+03;
	cameraMatrix.at<double>(0, 1) = 0;
	//cameraMatrix.at<double>(0, 2) = frame.cols;
	cameraMatrix.at<double>(0, 2) = 320;
	cameraMatrix.at<double>(1, 0) = 0;
	cameraMatrix.at<double>(1, 1) = 2.9231842160057367e+03;
	//cameraMatrix.at<double>(1, 2) = frame.rows;
	cameraMatrix.at<double>(1, 2) = 240;
	cameraMatrix.at<double>(2, 0) = 0;
	cameraMatrix.at<double>(2, 1) = 0;
	cameraMatrix.at<double>(2, 2) = 1;

	Mat distCoeffs = Mat::zeros(5, 1, CV_64F);
	distCoeffs.at<double>(0, 0) = -1.9951435223758395e+01;
	distCoeffs.at<double>(1, 0) = 1.1988016591847629e+02;
	distCoeffs.at<double>(2, 0) = 0;
	distCoeffs.at<double>(3, 0) = 0;
	distCoeffs.at<double>(4, 0) = 1.7637092844188075e+04;
#endif

#ifdef B
	Mat cameraMatrix = Mat::eye(3, 3, CV_64F);     //2.5mm镜头
	cameraMatrix.at<double>(0, 0) = 6.2025512800468068e+03;
	cameraMatrix.at<double>(0, 1) = 0;
	//cameraMatrix.at<double>(0, 2) = frame.cols;
	cameraMatrix.at<double>(0, 2) = 320;
	cameraMatrix.at<double>(1, 0) = 0;
	cameraMatrix.at<double>(1, 1) = 6.2025512800468068e+03;
	//cameraMatrix.at<double>(1, 2) = frame.rows;
	cameraMatrix.at<double>(1, 2) = 240;
	cameraMatrix.at<double>(2, 0) = 0;
	cameraMatrix.at<double>(2, 1) = 0;
	cameraMatrix.at<double>(2, 2) = 1;

	Mat distCoeffs = Mat::zeros(5, 1, CV_64F);
	distCoeffs.at<double>(0, 0) = -7.5444625737700903e+01;
	distCoeffs.at<double>(1, 0) = 7.2948480875347304e+03;
	distCoeffs.at<double>(2, 0) = 0;
	distCoeffs.at<double>(3, 0) = 0;
	distCoeffs.at<double>(4, 0) = 3.8719203809889638e+02;
#endif

	Mat view, rview, map1, map2;
	Size imageSize;
	imageSize = frame.size();
	initUndistortRectifyMap(cameraMatrix, distCoeffs, Mat(),
		getOptimalNewCameraMatrix(cameraMatrix, distCoeffs, imageSize, 1, imageSize, 0),
		imageSize, CV_16SC2, map1, map2);
		remap(frame, *frameCalibration, map1, map2, INTER_LINEAR);


}
void videoCalibration1(Mat* frameCalibration, Mat frame) {

#ifdef A
	Mat cameraMatrix = Mat::eye(3, 3, CV_64F);		//1.8mm镜头
	cameraMatrix.at<double>(0, 0) = 2.4079165012676626e+03;
	cameraMatrix.at<double>(0, 1) = 0;
	//cameraMatrix.at<double>(0, 2) = frame.cols;
	cameraMatrix.at<double>(0, 2) = 320;
	cameraMatrix.at<double>(1, 0) = 0;
	cameraMatrix.at<double>(1, 1) = 2.4079165012676626e+03;
	//cameraMatrix.at<double>(1, 2) = frame.rows;
	cameraMatrix.at<double>(1, 2) = 240;
	cameraMatrix.at<double>(2, 0) = 0;
	cameraMatrix.at<double>(2, 1) = 0;
	cameraMatrix.at<double>(2, 2) = 1;

	Mat distCoeffs = Mat::zeros(5, 1, CV_64F);
	distCoeffs.at<double>(0, 0) = -1.6990854038573470e+01;
	distCoeffs.at<double>(1, 0) = 5.8710367416638007e+02;
	distCoeffs.at<double>(2, 0) = 0;
	distCoeffs.at<double>(3, 0) = 0;
	distCoeffs.at<double>(4, 0) = -2.4398950732321100e+04;
#endif

#ifdef B
	Mat cameraMatrix = Mat::eye(3, 3, CV_64F);     //2.5mm镜头
	cameraMatrix.at<double>(0, 0) = 2.5242033205824423e+03;
	cameraMatrix.at<double>(0, 1) = 0;
	//cameraMatrix.at<double>(0, 2) = frame.cols;
	cameraMatrix.at<double>(0, 2) = 320;
	cameraMatrix.at<double>(1, 0) = 0;
	cameraMatrix.at<double>(1, 1) = 2.5242033205824423e+03;
	//cameraMatrix.at<double>(1, 2) = frame.rows;
	cameraMatrix.at<double>(1, 2) = 240;
	cameraMatrix.at<double>(2, 0) = 0;
	cameraMatrix.at<double>(2, 1) = 0;
	cameraMatrix.at<double>(2, 2) = 1;

	Mat distCoeffs = Mat::zeros(5, 1, CV_64F);
	distCoeffs.at<double>(0, 0) = 8.4096022002468884e-01;
	distCoeffs.at<double>(1, 0) = -1.0277562345116351e+03;
	distCoeffs.at<double>(2, 0) = 0;
	distCoeffs.at<double>(3, 0) = 0;
	distCoeffs.at<double>(4, 0) = 3.7222214920034574e+04;
#endif

	Mat view, rview, map1, map2;
	Size imageSize;
	imageSize = frame.size();
	initUndistortRectifyMap(cameraMatrix, distCoeffs, Mat(),
		getOptimalNewCameraMatrix(cameraMatrix, distCoeffs, imageSize, 1, imageSize, 0),
		imageSize, CV_16SC2, map1, map2);
	remap(frame, *frameCalibration, map1, map2, INTER_LINEAR);


}

void VideoCut(Mat img,Mat *out,float a) {
	float x, y,x1,y1;
	//Mat out;
	x = img.rows*a;
	x1 = img.rows*(1 - a);
	y = img.cols*a;
	y1 = img.cols*(1 - a);
	*out = img(Range(x,x1), Range(y,y1));
	//imshow("Range", out);

}

void Video_init(VideoCapture capture, VideoCapture capture1) {

	capture.open(1);
	capture1.open(2);
	
}


Mat comMatR(Mat Matrix1, Mat Matrix2, Mat &MatrixCom)
{

	//CV_Assert(Matrix1.rows == Matrix2.rows);//行数不相等，出现错误中断    
	MatrixCom.create(Matrix1.rows, Matrix1.cols + Matrix2.cols, Matrix1.type());
	Mat temp = MatrixCom.colRange(0, Matrix1.cols);
	Matrix1.copyTo(temp);
	Mat temp1 = MatrixCom.colRange(Matrix1.cols, Matrix1.cols + Matrix2.cols);
	Matrix2.copyTo(temp1);
	return MatrixCom;
}
void xuanzhuan(Mat src, Mat *out) {
	Mat temp, dst;
	transpose(src, temp);
	flip(temp, *out, 1);
	//imshow("1", dst);
}