#include "Video.h"
#include <stdio.h>  
#include <time.h>  
#include "Serial.h"
#include <opencv2/opencv.hpp>  
//#include <opencv/cv.h>  
#include <iostream> 
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/ml/ml.hpp>  
#include <io.h> //查找文件相关函数


using namespace std;
using namespace cv;
using namespace ml;
Mat yangben_gray, yangben_thresh,src, ou1,ou2,outt, edge;
void shibie(Mat dealimage);
VideoCapture cam;
Ptr<SVM>SVM_params;
std::vector<std::vector<Point>> contours;
std::vector<Vec4i> hireachy;
Rect rect;
//Mat img(Size(200,200), CV_8UC3);
Mat roi1;
char buf[20];

void distance(Mat in);
HANDLE hCom;//串口句柄
int main()
{
	cam.open(1);
	serial_connect(hCom, (wchar_t*)L"\\\\.\\COM4", CBR_115200);//连接到COM10，波特率115200
	//加载XML文件
	//SVM_params = SVM::load("C:/Users/shen/Desktop/shibie/x64/Debug/svm.xml");
	while (1) {
		cam >> src;

		videoCalibration(&src, src);
		cvtColor(src, yangben_gray, COLOR_BGR2HSV);
		inRange(yangben_gray, Scalar(160, 60, 60), Scalar(180, 255, 255), ou1);
		
		inRange(yangben_gray, Scalar(0, 60, 60), Scalar(10, 255, 255), ou2);
		outt = ou1 + ou2;
		findContours(outt, contours, hireachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
		if (contours.size() >= 1)
		{
			double maxArea = 50.00;
			for (int i = 0; i < contours.size(); i++)
			{
				double area = contourArea(contours[static_cast<int>(i)]);
				if (area > maxArea)
				{
					maxArea = area;
					rect = boundingRect(contours[static_cast<int>(i)]);
					//minEnclosingCircle(contours[static_cast<int>(i)], center, radius);
				}
			}
		}
		rectangle(src, rect, Scalar(0, 0, 255), 2);
		//blur(outt, edge, Size(2, 2));
		//threshold(edge, yangben_thresh, 100, 150, THRESH_OTSU);
		roi1 = outt(Rect(Point(rect.tl()),Size(rect.size())));
		imshow("2", src);
		distance(roi1);
		//shibie(roi1);
		//shibie(outt);
		waitKey(30);
	}
	return 0;

}



void shibie(Mat dealimage)
{
	//imshow("原图像", dealimage);
	//输入图像取特征点
	Mat trainTempImg = Mat::zeros(Size(128, 128), CV_8UC1);
	resize(dealimage, trainTempImg, trainTempImg.size());
	imshow("1", trainTempImg);
	HOGDescriptor *hog = new HOGDescriptor(Size(128, 128), Size(16, 16), Size(8, 8), Size(8, 8), 9);
	vector<float>descriptors;//结果数组         
	hog->compute(trainTempImg, descriptors, Size(1, 1), Size(0, 0));
	//cout << "HOG描述子向量维数    " << descriptors.size() << endl;
	Mat SVMtrainMat = Mat(1, descriptors.size(), CV_32FC1);

	int  number1 = descriptors.size();
	//将计算好的HOG描述子复制到样本特征矩阵SVMtrainMat  
	for (int i = 0; i < number1; i++)
	{
		//把一幅图像的HOG描述子向量依次存入data_mat矩阵的同一列
		//因为输入图像只有一个，即SVMtrainMat只有一列，则为0
		SVMtrainMat.at<float>(0, i) = descriptors[i];  									  //  n++;
	}

	SVMtrainMat.convertTo(SVMtrainMat, CV_32FC1);//更改图片数据的类型，必要，不然会出错
	int ret = (int)SVM_params->predict(SVMtrainMat);//检测结果  
	cout << "识别的数字为：" << ret << "\n";

}

void distance(Mat in) {
	imshow("3", in);
	float weight, dis, pix,F;
	float D;
	pix = in.cols;
	weight = 105;//25
	dis = 300;
	F = (pix*dis) / weight;
	//dis=
	D = (weight * 340)/pix;
	//cout << F << endl;
	cout << D/10  << "厘米" << endl;
	sprintf_s(buf,"%.2f",D/10);
	Write(hCom, buf, sizeof(buf));//发送
}
