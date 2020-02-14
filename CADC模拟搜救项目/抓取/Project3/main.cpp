#include<opencv2/opencv.hpp>
//#include <opencv2/stitching.hpp>
#include<math.h>
#include"Serial.h"
#include "Video.h"
#define aaa "USB Camera"
#define ppp
using namespace cv;
using namespace std;

int zzz,ooo;
Rect mouse;
char P[8];
char A[22];
char uuu='&';
void jizuobiao(float x, float y, int* p, int* angle);
void on_MouseHandle(int event, int x, int y, int flags, void* param);
void Drawline(Mat img, Point start, Point end);
VideoCapture camera1, camera2;
int connectstate;
HANDLE hCom;//串口句柄
int main(int argc, char** argv) {
	serial_connect(hCom, (wchar_t*)L"\\\\.\\COM17", CBR_115200);//连接到COM11，波特率115200
	Mat frame1, frame2,frame;
	Mat src1,src2;
	Mat cut1,cut2;
	Mat dst1, dst2;
	VideoCapture capture;
	VideoCapture capture1;
	mouse = Rect(-1, -1, 0, 0);
	namedWindow(aaa);
	setMouseCallback(aaa, on_MouseHandle, (void*)& frame);
	capture.open(0);
	capture1.open(1);
	int a=10;
	while (1) {
		capture >> src1;
		capture1 >> src2;

		videoCalibration1(&frame1, src2);
		videoCalibration1(&frame2, src1);
		VideoCut(frame1, &cut1,0.24);
		VideoCut(frame2, &cut2,0.24);
		xuanzhuan(cut1, &dst1);
		xuanzhuan(cut2, &dst2);
		comMatR(dst1, dst2,frame);	
		Drawline(frame, Point(0, (frame.rows) / 2), Point(frame.cols, (frame.rows) / 2));
		Drawline(frame, Point((frame.cols) / 2, 0), Point((frame.cols) / 2, frame.rows));
		imshow(aaa, frame);
		jizuobiao(mouse.x - (frame.cols) / 2, -(mouse.y - (frame.rows) / 2),&zzz,&ooo);
		Read(hCom);//读串口，并将读到的内容显示出来
		if (mouse.x && mouse.y > 0)
		{
			Sleep(20);
			_itoa_s(zzz, P, 10);
			_itoa_s(ooo, A, 10);
			//printf("%s\n", P);
			//printf("%s\n", A);
 #ifdef ppp
			if (connectstate != -1) {
				strcat_s(A, "#");
				strcat_s(A, P);
				strcat_s(A,"$");
				printf("%s\n", A);
				Write(hCom, A, sizeof(A) - 1);//发送			
			}
#endif


			else {
				printf("串口连接失败!\n");
			}			
		}
		waitKey(20);
	}
	return 0;
}

void on_MouseHandle(
	int event,
	int x,
	int y, 
	int flags,
	void* param) {//鼠标回调函数

	Mat& image = *(cv::Mat*) param;
	switch (event) {
	case EVENT_LBUTTONDOWN:
		mouse = Rect(x, y, 0, 0);
		//strcat_s(A, "&");
		break;
	case EVENT_RBUTTONDOWN:
		mouse = Rect(0, 0, 0, 0);
		Write(hCom,&uuu, sizeof (uuu));//发送
		break;
	//case EVENT_MBUTTONDOWN: 
	default: mouse = Rect(0, 0, 0, 0);
	}

}

void Drawline(
	Mat img,
	Point start,
	Point end) {//划线函数

	int thickness = 1;
	int lineType = 8;
	line(img, start, end, Scalar(0, 0, 0), thickness, lineType);

}

void jizuobiao(
	float y,
	float x,
	int *p,
	int *angle) {//直角坐标转极坐标
	float pp;
	*p = (sqrt(x * x + y * y))/3.75*10000;
	pp = sqrt(x * x + y * y);
	//*p = (int)*p;
	if (y > 0) {
		*angle = ((180 * acos(x / pp)) / 3.14)*10000 ;
		//*angle = (int)*angle;
	}
	else if (y < 0) {
		*angle = (360 - (180 * acos(x / pp)) / 3.14)*10000;
		//*angle = (int)*angle;
	}
}
