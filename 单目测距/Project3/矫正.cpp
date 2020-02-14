#include"Video.h"


//#include <opencv2/opencv.hpp>
//#include <iostream>
using namespace cv;
//using namespace std;


void videoCalibration(Mat* frameCalibration,Mat frame){
	Mat cameraMatrix = Mat::eye(3, 3, CV_64F);		
	cameraMatrix.at<double>(0, 0) = 1.1113630602933533e+03;
	cameraMatrix.at<double>(0, 1) = 0;
	//cameraMatrix.at<double>(0, 2) = frame.cols;
	cameraMatrix.at<double>(0, 2) = 320;
	cameraMatrix.at<double>(1, 0) = 0;
	cameraMatrix.at<double>(1, 1) = 1.1113630602933533e+03;
	//cameraMatrix.at<double>(1, 2) = frame.rows;
	cameraMatrix.at<double>(1, 2) = 240;
	cameraMatrix.at<double>(2, 0) = 0;
	cameraMatrix.at<double>(2, 1) = 0;
	cameraMatrix.at<double>(2, 2) = 1;

	Mat distCoeffs = Mat::zeros(5, 1, CV_64F);
	distCoeffs.at<double>(0, 0) = -4.8335587165302130e-01;
	distCoeffs.at<double>(1, 0) = 3.2504303260890022e-01;
	distCoeffs.at<double>(2, 0) = 0;
	distCoeffs.at<double>(3, 0) = 0;
	distCoeffs.at<double>(4, 0) = -1.4446407869320901e-01;

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



Mat comMatR(Mat Matrix1, Mat Matrix2, Mat &MatrixCom)//图像拼接
{

	//CV_Assert(Matrix1.rows == Matrix2.rows);//行数不相等，出现错误中断    
	MatrixCom.create(Matrix1.rows, Matrix1.cols + Matrix2.cols, Matrix1.type());
	Mat temp = MatrixCom.colRange(0, Matrix1.cols);
	Matrix1.copyTo(temp);
	Mat temp1 = MatrixCom.colRange(Matrix1.cols, Matrix1.cols + Matrix2.cols);
	Matrix2.copyTo(temp1);
	return MatrixCom;
}
void xuanzhuan(Mat src, Mat *out,int z) {//图像旋转
	Mat temp, dst;
	transpose(src, temp);
	flip(temp, *out, z);
	//imshow("1", dst);
}