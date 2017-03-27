
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include<string>
#include <sstream>

using namespace cv;
using namespace std;

//*************************METHOD TO PROCESS VIDEO FRAMES***********************
int load(String argv)
{

	VideoCapture cap(argv);
	if(!cap.isOpened())
	{
	return -1;
	}
	int framenum=1;
	string Result;
	Mat edges;
	int i,j,k;
	ostringstream convert;
	Mat frame;
	double computemean=0.0;
	int totalpixel = 0;
	int sum = 0;
	long long int thatpixel[100000];
	namedWindow("edges",CV_WINDOW_AUTOSIZE);

	for(;;)
	{
		Result="0";
		cap>>frame;
		cvtColor(frame, edges, COLOR_BGR2GRAY);

		
		framenum++;
		convert<<framenum;
		Result = convert.str();
		sum=0;
		
		cout<<Result<<endl;
		//waitKey(0);
		
		for(i=0;i<edges.rows;i++)
		{
			k=0;
			for(j=0;j<edges.cols;j++)
			{
				totalpixel=0;
				thatpixel[k]=edges.at<uchar>(i,j);//cout<<thatpixel[k];
				sum+=thatpixel[k];
				k++;
			}
		}

		//String font = "FONT_HERSHEY_SIMPLEX";
		//ostringstream s;
		//s << framenum;
		//string converted(s.str());
		//string str = "Frame"+s;
		//putText(edges,str,Point(40,40), FONT_HERSHEY_PLAIN, 4,Scalar(255,255,255),2,8,false);

		totalpixel = edges.rows*edges.cols;
		computemean = (float)sum/totalpixel;
	
		cout<<computemean<<endl;
		//framenum;

		imwrite( "data/frame"+Result+".jpg", edges );
		imshow("edges", edges);	
		if(waitKey(30) >= 0) 
			break;
	}

	cout<<totalpixel<<endl;
	return 0;
}

int main(int arg,char** argv)
{
	String param;
	param = "lib/Test123.avi";
	load(param);
	//namedWindow( "vid", CV_WINDOW_AUTOSIZE );
	//imshow( "vid", cap );
	return 0;
}
