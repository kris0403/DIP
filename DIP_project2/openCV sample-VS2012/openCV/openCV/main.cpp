#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <highgui.h>
#include <complex>
#include <cmath>
#include "cv.h"
using namespace std;
using namespace cv;
complex<double> temp[1000][1000];
complex<double> tempflash[1000][1000];
int main(){
	double pi=3.1415;
	Mat SrcImg = imread("Q4.tif", CV_LOAD_IMAGE_GRAYSCALE);
	Mat DstImg=Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);//output space
	
	for(int v = 0;v <SrcImg.cols;v++)	
	{
		for(int u=0;u<SrcImg.rows;u++)
		{
			temp[u][v]=(0,0);
			for(int i=0;i<SrcImg.rows;i++)
			{
					complex<double> newtemp((double)SrcImg.at<uchar>(i,v),0);
					temp[u][v] += newtemp / complex<double>(cos(pi*2*i*u/SrcImg.rows), sin(pi*2*i*u/SrcImg.rows));
			}
		}
	}

	for(int u=0;u<SrcImg.rows;u++)
	{
		complex<double> srcrow (SrcImg.rows,0);

		for(int v = 0;v <SrcImg.cols;v++)
		{
			
			for(int j=0;j<SrcImg.cols;j++)
			{
				
				complex<double> newtemp1=temp[u][j];
				tempflash[u][v] += newtemp1 / complex<double> (cos(pi*2*j*v/SrcImg.cols), sin(pi*2*j*v/SrcImg.cols));
			}
			tempflash[u][v] /= (SrcImg.rows/2);
			//cout<<temp[u][v].real()<<" r"<<temp[u][v].imag()<<" i";
			double s = sqrt(pow(tempflash[u][v].real(),2)+pow(tempflash[u][v].imag(),2));
			if(s>255)s=255;
			DstImg.at<uchar>(u,v) = (uchar)(s);	
		}
		

	}

	 int cx =  DstImg.cols/2;
    int cy =  DstImg.rows/2;

    Mat q0( DstImg, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    Mat q1( DstImg, Rect(cx, 0, cx, cy));  // Top-Right
    Mat q2( DstImg, Rect(0, cy, cx, cy));  // Bottom-Left
    Mat q3( DstImg, Rect(cx, cy, cx, cy)); // Bottom-Right

    Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);

	//normalize( DstImg,  DstImg, 0, 255, CV_MINMAX);
	// Show images
	imshow("Input Image", SrcImg);	
	imshow("Output", DstImg);

	// Write output images
	imwrite("Q4_output.tif", DstImg);
	waitKey(0);
	return 0;
}

