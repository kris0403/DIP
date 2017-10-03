#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <highgui.h>
#include "cv.h"
using namespace std;
using namespace cv;

void drawHistImg(const Mat &src, Mat &dst){
    int histSize = 256;
    float histMaxValue = 0;
    for(int i=0; i<histSize; i++){
        float tempValue = src.at<float>(i);
        if(histMaxValue < tempValue){
            histMaxValue = tempValue;
        }
    }

    float scale = (0.9*256)/histMaxValue;
    for(int i=0; i<histSize; i++){
        int intensity = static_cast<int>(src.at<float>(i)*scale);
        line(dst,Point(i,255),Point(i,255-intensity),Scalar(0));
    }
}

int main(){

	// Read input images
	// Fig3.tif is in openCV\bin\Release
	//Mat SrcImg = imread("Fig3.tif", CV_LOAD_IMAGE_GRAYSCALE);
	Mat SrcImg = imread("Fig03_Slide23.tif", CV_LOAD_IMAGE_GRAYSCALE);
	// Create a grayscale output image matrix
	Mat DstImg[8];
	for(int i=0;i<8;i++)
	{
		DstImg[i] = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	}
	for(int i=0; i<SrcImg.rows; ++i)
			for(int j=0; j<SrcImg.cols; ++j)
			{
				DstImg[0].at<uchar>(i,j) = SrcImg.at<uchar>(i,j);
				DstImg[2].at<uchar>(i,j) = SrcImg.at<uchar>(i,j);
			}

	for(int i=0; i<SrcImg.rows; ++i)
		for(int j=0; j<SrcImg.cols; ++j) 
		{			
			DstImg[0].at<uchar>(i,j) = (double)DstImg[0].at<uchar>(i,j)*((double)20/(double)51);//y=(20/51)x  (0.255)->(0.100)
			DstImg[2].at<uchar>(i,j) = (double)DstImg[2].at<uchar>(i,j)*((double)31/(double)51) + 100;//y=(31/51)x+100   (0,255)->(100.255)
		}
		int darktable[256]={0};
	int lighttable[256]={0};
	for(int i=0; i<SrcImg.rows; ++i)
		for(int j=0; j<SrcImg.cols; ++j)
		{	
			darktable[DstImg[0].at<uchar>(i,j)]++;
			lighttable[DstImg[2].at<uchar>(i,j)]++;
		}
		int tempdark=0;
		int templight=0;
		int newdarktable[256] = {0};
		int newlighttable[256] = {0};
		for(int i=0; i<256;i++)
		{
			tempdark += 255.0*( (double)darktable[i]/(double)(SrcImg.rows*SrcImg.cols));
			templight += 255.0* ( (double)lighttable[i]/(double)(SrcImg.rows*SrcImg.cols));
			newdarktable[i] = tempdark;
			newlighttable[i] = templight;

		}
		


	for(int i=0; i<SrcImg.rows; ++i)
		for(int j=0; j<SrcImg.cols; ++j)
		{	
			
			DstImg[4].at<uchar>(i,j) = newdarktable[DstImg[0].at<uchar>(i,j)];
			DstImg[5].at<uchar>(i,j) = newlighttable[DstImg[2].at<uchar>(i,j)];
		}
	 int histSize = 256;
    float range[] = {0, 255} ;
    const float* histRange = {range};
    Mat histImg,histImg2;
    calcHist(&DstImg[4], 1, 0, Mat(), histImg, 1, &histSize, &histRange);
    Mat showHistImg(256,256,CV_8UC1,Scalar(255));  //把直方圖秀在一個256*256大的影像上
    drawHistImg(histImg, showHistImg);
	 calcHist(&DstImg[5], 1, 0, Mat(), histImg2, 1, &histSize, &histRange);
	  Mat showHistImg2(256,256,CV_8UC1,Scalar(255));  //把直方圖秀在一個256*256大的影像上
	 drawHistImg(histImg2, showHistImg2);
	// Copy each pixel of the source image to the output image
	// Show images
	imshow("Input Image", SrcImg);
	
	imshow("dark Output Image1", DstImg[0]);
	imshow("dark equalize Output Image2", DstImg[4]);
	 imshow("window2", showHistImg);

	imshow("lightOutput Image3", DstImg[2]);
	imshow("light equalizeImage4", DstImg[5]);
	 imshow("window3", showHistImg2);

	// Write output images
	imwrite("dark_Output_Fig03_output1.tif", DstImg[0]);
	imwrite("dark_equalize_Fig03_output2.tif",  DstImg[4]);
	imwrite("dark_histogram.tif", showHistImg);
	imwrite("light_Fig03_output3.tif",  DstImg[2]);
	imwrite("light_equalize_Fig03_output4.tif",  DstImg[5]);
	imwrite("light_histogram.tif", showHistImg2);
	waitKey(0);
	return 0;
}