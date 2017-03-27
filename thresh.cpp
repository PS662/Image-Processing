#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include<string>
#include <stdlib.h>
 
using namespace cv;
using namespace std;

int thresh(Mat im,int tl)
{
	int i,j;
	Mat t_im;
	
	cvtColor(im,t_im,COLOR_BGR2GRAY);
	
	for(i=0;i<t_im.rows;i++)
	{
		for(j=0;j<t_im.cols;j++)
		{
			if(t_im.at<uchar>(i,j)>tl)
				t_im.at<uchar>(i,j)=255;
			else
				t_im.at<uchar>(i,j)=0;//t_im.at<uchar>(i,j);
		}
	}
	
	namedWindow("Thresh",CV_WINDOW_AUTOSIZE);
	imshow("Thresh",t_im);
	waitKey(0);
	return 0;
}

int main(int arg, char** argv)
{
 int tl = 40;
 Mat im;
 im = imread(argv[1]);
 thresh(im,tl);
 return 0;
}
