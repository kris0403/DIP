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
	Mat SrcImg = imread("Fig02_Slide14.tif", CV_LOAD_IMAGE_GRAYSCALE);
	// Create a grayscale output image matrix
	Mat DstImg[8];
	for(int i=0;i<8;i++)
	{
		DstImg[i] = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	}
	// Copy each pixel of the source image to the output image
	for(int num=0;num<8;num++)
	{
		for(int i=0; i<SrcImg.rows; ++i)
			for(int j=0; j<SrcImg.cols; ++j)
			{
				if((SrcImg.at<uchar>(i,j)>>num)&1 == 1) 
				{
					DstImg[num].at<uchar>(i,j)=255;
				}
				else 
				{
						DstImg[num].at<uchar>(i,j)=0;
				}
			}

	}

	
	// Show images
	imshow("Input Image", SrcImg);
	
	imshow("Output Image1", DstImg[0]);
	imshow("Output Image2", DstImg[1]);
	imshow("Output Image3", DstImg[2]);
	imshow("Output Image4", DstImg[3]);
	imshow("Output Image5", DstImg[4]);
	imshow("Output Image6", DstImg[5]);
	imshow("Output Image7", DstImg[6]);
	imshow("Output Image8", DstImg[7]);

	// Write output images
	imwrite("Fig02_output1.tif", DstImg[0]);
	imwrite("Fig02_output2.tif",  DstImg[1]);
	imwrite("Fig02_output3.tif",  DstImg[2]);
	imwrite("Fig02_output4.tif",  DstImg[3]);
	imwrite("Fig02_output5.tif", DstImg[4]);
	imwrite("Fig02_output6.tif",  DstImg[5]);
	imwrite("Fig02_output7.tif", DstImg[6]);
	imwrite("Fig02_output8.tif",  DstImg[7]);
	waitKey(0);
	return 0;
}