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
	//Mat imageSource = imread("C:/Users/shen/Desktop/����/Project3/x64/Debug/1.jpg", 0);
	//imshow("ԭʼͼ��", imageSource);



	findContours(image, contours, hierarchy, RETR_TREE,CHAIN_APPROX_NONE, Point());
	Mat imageContours = Mat::zeros(image.size(), CV_8UC1);
	Mat Contours = Mat::zeros(image.size(), CV_8UC1); //����
	while (1) {
		cam >> imageSource;
		GaussianBlur(imageSource, image, Size(3, 3), 0);
		Canny(imageSource, image, 100, 250);
		for (int i = 0; i < contours.size(); i++)
		{
			//contours[i]������ǵ�i��������contours[i].size()������ǵ�i�����������е����ص���
			for (int j = 0; j < contours[i].size(); j++)
			{
				//���Ƴ�contours�������е����ص�
				Point P = Point(contours[i][j].x, contours[i][j].y);
				Contours.at<uchar>(P) = 255;
			}

			//���hierarchy��������
			char ch[256];
			sprintf_s(ch, "%d", i);
			string str = ch;
			cout << "����hierarchy�ĵ�" << str << "��Ԫ������Ϊ��" << hierarchy[i] << endl << endl;

			//��������
			drawContours(imageContours, contours, i, Scalar(255), 1, 8, hierarchy);
		}
		imshow("Contours Image CV_TRET_TREE", imageContours); //����
		imshow("Point of Contours CV_CHAIN_APPROX_NONE", Contours); //����contours�ڱ�������������㼯
		waitKey(1);
	}
	return 0;
}