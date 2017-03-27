#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;
	
int main(int argc, char** argv )
{
	//const int krows1 = 9;
	//const int kcols1 = 9;
	const int krows = 9;
	const int kcols = 9;
	const int rows = 5;
	const int cols = 4;
	//int kernel2[krows][kcols]={0,0,0,0,1,0,0,0,0};
	//double kernel2[krows][kcols]={0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0};
/***********************************Replace this with a code snippet that generates a gaussian matrix*******************************/
	double kernel[krows][kcols]={0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000,
	0.000, 0.000, 0.000, 0.001, 0.002, 0.001, 0.000, 0.000, 0.000,
	0.000, 0.000, 0.003, 0.013, 0.022, 0.013, 0.003, 0.000, 0.000,
	0.000, 0.001, 0.013, 0.059, 0.097, 0.059, 0.013, 0.001, 0.000,
	0.000, 0.002, 0.022, 0.097, 0.159, 0.097, 0.022, 0.002, 0.000,
	0.000, 0.001, 0.013, 0.059, 0.097, 0.059, 0.013, 0.001, 0.000,
	0.000, 0.000, 0.003, 0.013, 0.022, 0.013, 0.003, 0.000, 0.000,
	0.000, 0.000, 0.000, 0.001, 0.002, 0.001, 0.000, 0.000, 0.000,
	0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000};
	//int in[rows][cols]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	Mat in,out,orig;
	
	
	orig = imread(argv[1]);
	int mm,nn,ii,jj;
	int kCenterX = krows/2;
	int kCenterY = kcols/2;
	//int out[rows][cols]={0};
	int i,j,m,n;
	
	
	in =Mat(orig.rows,orig.cols,CV_8UC1);
	cvtColor(orig,in,COLOR_BGR2GRAY);
	out = Mat(in.rows,in.cols,CV_8UC1);

	for(i=0;i<in.rows;i++)//for(i=0;i<rows;i++)
	{
		for(j=0;j<in.cols;j++)//for(j=0;j<cols;j++)
		{
			for(m=0; m < krows; ++m)    
			{	mm = krows - 1 - m;      
				for(n=0; n < kcols; ++n) 
				{
					nn = kcols - 1 - n;  
					ii = i + (m - kCenterY);
					jj = j + (n - kCenterX);
					/*if( ii >= 0 && ii < rows && jj >= 0 && jj < cols )*/if( ii >= 0 && ii < in.rows && jj >= 0 && jj < in.cols)
					/*out[i][j]+=in[ii][jj]*kernel2[mm][nn];*/out.at<uchar>(i,j) += in.at<uchar>(ii,jj) * kernel[mm][nn];
				}
			}
		}
	}
	/*for(i=0;i<rows;i++)
	{
	for(j=0;j<cols;j++){
	cout<<endl;
	cout<<out[i][j];
	}cout<<endl;
	}*/

	namedWindow( "original", WINDOW_AUTOSIZE );// Create a window for display.
	imshow( "original", in );  
	waitKey(0);
	namedWindow( "filter", WINDOW_AUTOSIZE );// Create a window for display.
	imshow( "filter", out);   
	waitKey(0);
	return 0;
}
	

