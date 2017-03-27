#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include<string>
#include <stdlib.h> 

using namespace std;
using namespace cv;

//***********************Method to subtract the frames********************************
int sub(String argv)
{
	Mat frame,edges,save_frame,save_frame_edge,inter_edge;
	int i,j;
	VideoCapture cap(argv);
	
	cap>>save_frame;
	
	if(!cap.isOpened())
	{
		return -1;
	} 
	
	cvtColor(save_frame,save_frame_edge,COLOR_BGR2GRAY);
	imwrite("data1/backsub.jpg",save_frame_edge);
	inter_edge = Mat(save_frame_edge.rows,save_frame_edge.cols,CV_8UC1);
	
	for(;;)
	{
		 cap>>frame;
		 cvtColor(frame, edges, COLOR_BGR2GRAY);
		if(!cap.isOpened())
		{
			return -1;
		}
	
		//namedWindow("edges",CV_WINDOW_AUTOSIZE);
		//imshow("edges", edges);
		//waitKey(0);
	
		for(i=0;i<edges.rows;i++)
		{
			for(j=0;j<edges.cols;j++)
			{ 
				inter_edge.at<uchar>(i,j)=abs(save_frame_edge.at<uchar>(i,j)-edges.at<uchar>(i,j));
			}
		}
	
		imwrite("data1/inter.png",inter_edge);
		namedWindow("inter_edge",CV_WINDOW_AUTOSIZE);
		imshow("inter_edge",inter_edge);
	
		//waitKey(0);
	
		if(waitKey(30) >= 0) 
			break;
	}
	return 0;
}

//***************************MAIN FUNTION*******************************************

int main(int agr, char** argv)
{
	String param;
	param = "lib/Test123.avi";
	sub(param);
	return 0;
}
