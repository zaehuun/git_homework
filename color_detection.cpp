#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv; //opencv namespace
using namespace std;


int main()
{
	Mat img_color; //rgb 컬러 영상 출력할 이미지 객체
	
	Mat img_hsv; //bgr 영상을 hsv로 변환해서 출력할  이미지 객체

	int threshold = 100; 
	//--------------init red range------------------------------
	Vec3b lower_red1 = Vec3b(170, threshold, threshold); //170, 100 100의 값을 가진 객체 생성, 출력할 빨간색의 hsv를 지정하기 위해 생성
	Vec3b upper_red1 = Vec3b(178, 255, 255); 
	Vec3b lower_red2 = Vec3b(0, threshold, threshold);
	Vec3b upper_red2 = Vec3b(7, 255, 255);
	Vec3b lower_red3 = Vec3b(160, threshold, threshold);
	Vec3b upper_red3 = Vec3b(177, 255, 255);
	//-----------------------------------------------------------

	//--------------init blue range------------------------------
	Vec3b lower_blue1 = Vec3b(110, threshold, threshold); //110, 100 100의 값을 가진 객체 생성, 출력할 파란색의 hsv를 지정하기 위해 생성
	Vec3b upper_blue1 = Vec3b(130, 255, 255);
	Vec3b lower_blue2 = Vec3b(115, threshold, threshold);
	Vec3b upper_blue2 = Vec3b(131, 255, 255);
	Vec3b lower_blue3 = Vec3b(95, threshold, threshold);
	Vec3b upper_blue3 = Vec3b(110, 255, 255);
	//-----------------------------------------------------------

	//VideoCapture cap(0);

	VideoCapture v("test.mp4");
	if (!v.isOpened()) { 
		while(1)
			cout << "카메라를 열 수 없습니다." << endl;
		return -1;
	}


	while (1)
	{
		v.read(img_color);

		cvtColor(img_color, img_hsv, COLOR_BGR2HSV); 
		
		//----------------red check-----------------------------
		Mat img_red1, img_red2, img_red3, img_red; 
		inRange(img_hsv, lower_red1, upper_red1, img_red1); 
		inRange(img_hsv, lower_red2, upper_red2, img_red2); 
		inRange(img_hsv, lower_red3, upper_red3, img_red3);
		
		img_red = img_red1 | img_red2 | img_red3; 
		//--------------------------------------------------------

		//----------------blue check-----------------------------
		Mat img_blue1, img_blue2, img_blue3, img_blue; 
		inRange(img_hsv, lower_blue1, upper_blue1, img_blue1);
		inRange(img_hsv, lower_blue2, upper_blue2, img_blue2);
		inRange(img_hsv, lower_blue3, upper_blue3, img_blue3);
		img_blue = img_blue1 | img_blue2 | img_blue3; 
		//--------------------------------------------------------

		Mat img_tmp = img_red | img_blue; 
		Mat img_result; 
		bitwise_and(img_color, img_color, img_result, img_tmp);

		imshow("img_color", img_color);
		//imshow("img_mask", img_tmp);
		imshow("img_result", img_result); 

		if (waitKey(1) > 0) 
			break;
	}


	return 0;
}
