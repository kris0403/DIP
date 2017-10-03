#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <highgui.h>
#include "cv.h"
using namespace std;
using namespace cv;
int main(){

	// Read input images
	// Fig3.tif is in openCV\bin\Release
	//Mat SrcImg = imread("Fig3.tif", CV_LOAD_IMAGE_GRAYSCALE);
	Mat SrcImg = imread("Fig01_Slide10.tif", CV_LOAD_IMAGE_GRAYSCALE);
	// Create a grayscale output image matrix
	Mat Dst1Img = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	Mat Dst2Img = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	Mat Dst3Img = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	// Copy each pixel of the source image to the output image
	for (int i = 0; i<SrcImg.rows; ++i)
		for (int j = 0; j<SrcImg.cols; ++j)
		{
			Dst1Img.at<uchar>(i, j) = 255.0*pow((float)SrcImg.at<uchar>(i, j) / 255, 0.6);
			Dst2Img.at<uchar>(i, j) = 255.0*pow((float)SrcImg.at<uchar>(i, j) / 255, 0.4);
			Dst3Img.at<uchar>(i, j) = 255.0*pow((float)SrcImg.at<uchar>(i, j) / 255, 0.3);//皈依劃過了
		}
	// Show images
	imshow("Input Image", SrcImg);
	imshow("Output Image1", Dst1Img);
	imshow("Output Image2", Dst2Img);
	imshow("Output Image3", Dst3Img);

	// Write output images
	imwrite("Fig01_output1.tif", Dst1Img);
	imwrite("Fig01_output2.tif", Dst2Img);
	imwrite("Fig01_output3.tif", Dst3Img);

	waitKey(0);
	return 0;
}