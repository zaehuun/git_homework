#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;
RNG rng(12345);

int main()
{
	Mat imgColor;
	imgColor = imread("images (2).jpg");
	imshow("color ", imgColor);

	//-----------defining the Ranege of color-------------
	Vec3b lower_red = Vec3b(170, 100, 100);
	Vec3b upper_red = Vec3b(180, 255, 255);
	Vec3b lower_green = Vec3b(50, 100, 10);
	Vec3b upper_green = Vec3b(80, 255, 255);
	Vec3b lower_yellow = Vec3b(0, 100, 100);
	Vec3b upper_yellow = Vec3b(20, 255, 255);
	//-----------------------------------------------------
	Mat hsv;
	cvtColor(imgColor, hsv, COLOR_BGR2HSV);
	Mat imgRed, imgGreen, imgYellow;
	inRange(hsv, lower_red, upper_red, imgRed);
	inRange(hsv, lower_green, upper_green, imgGreen);
	inRange(hsv, lower_yellow, upper_yellow, imgYellow);
	Mat kernel = Mat::ones(5, 5, CV_8UC1);
	dilate(imgRed, imgRed, kernel);
	dilate(imgGreen, imgGreen, kernel);
	dilate(imgYellow, imgYellow, kernel);

	Mat tmp_color = imgRed | imgGreen | imgYellow;
	Mat red;
	//bitwise_and(imgColor, imgColor, red, imgRed);
	
	erode(tmp_color, tmp_color, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	dilate(tmp_color, tmp_color, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	


	dilate(tmp_color, tmp_color, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	erode(tmp_color, tmp_color, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	//imshow("asd", imgRed);원래있던거
	imshow("asd", tmp_color);
	vector < vector<Point>> contours;
	vector<Vec4i> approx;
	findContours(tmp_color, contours, approx, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE); //원래 처음 거 imgRed였음
	
	
	Mat dstimage = Mat::zeros(imgRed.size(),CV_8UC3);
	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		if (contourArea(contours[i]) > 800){
			drawContours(dstimage, contours, i, color, 2, 8, approx, 0, Point());
		}
	}
	for (int i = 0; i < contours.size(); i++) {
		cout << "countour size : " << contours.size() << '\n';
		/*for (unsigned int j = 0; j < contours[i].size(); j++)
		{
			std::cout << "Point(x,y)=" << contours[i][j] << std::endl;
		}*/
		
		cout << i << " contour size : " << contourArea(contours[i]) << '\n';
	}
	imshow("contour ", dstimage);
	/*erode(tmp_color, tmp_color, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));



	


	findContours(imgRed, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);



	Mat img_result = imgColor.clone();

	for (int i = 0; i < contours.size(); i++) {

	}*/







	waitKey(0);

	return 0;
}
/*void mouse_callback(int event, int x, int y, int flags, void *param)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		Vec3b color_pixel = img_color.at<Vec3b>(y, x);

		Mat bgr_color = Mat(1, 1, CV_8UC3, color_pixel);


		Mat hsv_color;
		cvtColor(bgr_color, hsv_color, COLOR_BGR2HSV);

		int hue = hsv_color.at<Vec3b>(0, 0)[0];
		int saturation = hsv_color.at<Vec3b>(0, 0)[1];
		int value = hsv_color.at<Vec3b>(0, 0)[2];

		cout << "hue = " << hue << endl;
		cout << "saturation = " << saturation << endl;
		cout << "value = " << value << endl;


		if (hue < 10)
		{
			cout << "case 1" << endl;
			lower_blue1 = Vec3b(hue - 10 + 180, threshold1, threshold1);
			upper_blue1 = Vec3b(180, 255, 255);
			lower_blue2 = Vec3b(0, threshold1, threshold1);
			upper_blue2 = Vec3b(hue, 255, 255);
			lower_blue3 = Vec3b(hue, threshold1, threshold1);
			upper_blue3 = Vec3b(hue + 10, 255, 255);
		}
		else if (hue > 170)
		{
			cout << "case 2" << endl;
			lower_blue1 = Vec3b(hue, threshold1, threshold1);
			upper_blue1 = Vec3b(180, 255, 255);
			lower_blue2 = Vec3b(0, threshold1, threshold1);
			upper_blue2 = Vec3b(hue + 10 - 180, 255, 255);
			lower_blue3 = Vec3b(hue - 10, threshold1, threshold1);
			upper_blue3 = Vec3b(hue, 255, 255);
		}
		else
		{
			cout << "case 3" << endl;
			lower_blue1 = Vec3b(hue, threshold1, threshold1);
			upper_blue1 = Vec3b(hue + 10, 255, 255);
			lower_blue2 = Vec3b(hue - 10, threshold1, threshold1);
			upper_blue2 = Vec3b(hue, 255, 255);
			lower_blue3 = Vec3b(hue - 10, threshold1, threshold1);
			upper_blue3 = Vec3b(hue, 255, 255);
		}

		cout << "hue = " << hue << endl;
		cout << "#1 = " << lower_blue1 << "~" << upper_blue1 << endl;
		cout << "#2 = " << lower_blue2 << "~" << upper_blue2 << endl;
		cout << "#3 = " << lower_blue3 << "~" << upper_blue3 << endl;
	}
}*/
