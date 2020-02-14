#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;
VideoCapture cam;
Mat imageSource;
Mat image;
vector<vector<Point>> contours;
vector<Vec4i> hierarchy;
int main(int argc, char* argv[])
{
	cam.open(1);
	//Mat imageSource = imread("C:/Users/shen/Desktop/资料/Project3/x64/Debug/1.jpg", 0);
	//imshow("原始图像", imageSource);



	findContours(image, contours, hierarchy, RETR_TREE,CHAIN_APPROX_NONE, Point());
	Mat imageContours = Mat::zeros(image.size(), CV_8UC1);
	Mat Contours = Mat::zeros(image.size(), CV_8UC1); //绘制
	while (1) {
		cam >> imageSource;
		GaussianBlur(imageSource, image, Size(3, 3), 0);
		Canny(imageSource, image, 100, 250);
		for (int i = 0; i < contours.size(); i++)
		{
			//contours[i]代表的是第i个轮廓，contours[i].size()代表的是第i个轮廓上所有的像素点数
			for (int j = 0; j < contours[i].size(); j++)
			{
				//绘制出contours向量所有的像素点
				Point P = Point(contours[i][j].x, contours[i][j].y);
				Contours.at<uchar>(P) = 255;
			}

			//输出hierarchy向量内容
			char ch[256];
			sprintf_s(ch, "%d", i);
			string str = ch;
			cout << "向量hierarchy的第" << str << "个元素内容为：" << hierarchy[i] << endl << endl;

			//绘制轮廓
			drawContours(imageContours, contours, i, Scalar(255), 1, 8, hierarchy);
		}
		imshow("Contours Image CV_TRET_TREE", imageContours); //轮廓
		imshow("Point of Contours CV_CHAIN_APPROX_NONE", Contours); //向量contours内保存的所有轮廓点集
		waitKey(1);
	}
	return 0;
}