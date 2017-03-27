
#include<list>
#include<iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv; 

/*struct pointxy{
px;
py;
};*/

//pointxy p1;
 
Point p;
list<Point> listp;
list<list<Point> > listll;

//listxy xy;
//list<listxy> listll;

int comp = 255;
int counter =0;
int tl = 32;
Mat t_im,t_imc,in;

//**********************UTILITY METHOD FOR THRESHOLDING******************
void thresh(Mat in,int tl)
{
	//cout<<"Hellothresh";
	int i,j;
	 cvtColor(in,t_im,COLOR_BGR2GRAY);
	 for(i=t_im.rows;i>0;i--)
	 {
		for(j=t_im.cols;j>0;j--)
		{
			 if(t_im.at<uchar>(i,j)>tl)
			 	t_im.at<uchar>(i,j)=255;
			 else
			 	t_im.at<uchar>(i,j)=0;
			counter++;//t_im.at<uchar>(i,j);
		}
	}
	//cout<<"returnthresh"<<endl;
}
 
//*******************WHERE THE MAGIC HAPPENS*************************

void flood(Mat t_im, int x, int y, int val)
{
	if (x < 0 || x >= t_imc.rows || y < 0 || y >= t_imc.cols)
	    return;
	if (t_imc.at<uchar>(x,y) != comp)
	    return;
	//cout<<"helloflood"<<endl;

	p.x=x;
	p.y=y;
	listp.push_front(p);   
	//xy.int_listx.push_front(x);
	// xy.int_listy.push_front(y);
	t_imc.at<uchar>(x,y) = 0;
	counter++;

	cout<<"\nWhitex:"<<x<<"\nWhitey:"<<y<<endl;
	//cout<<"returnflood";
	//namedWindow("Threshmain",CV_WINDOW_AUTOSIZE);
	//imshow("Threshmain",t_imc);
	//waitKey(0);
	
	flood(t_imc, x+1, y, val);
	flood(t_imc, x-1, y, val);
	flood(t_imc, x, y+1, val);
	flood(t_imc, x, y-1, val);
}
 
//********************FLOODFILL HELPER METHOD***************************

void floodFill(Mat in, int x, int y)
{
	//cout<<"hellofloodfill";   
	int val = in.at<uchar>(x,y);
	//namedWindow("Thresh",CV_WINDOW_AUTOSIZE);
	//imshow("Thresh",t_im);
	//waitKey(0);
	//cout<<"returnfloodfill";
	flood(t_im, x, y, val);
}
 
//***************************DRAWS RECTANGLE***************************
void drawrec(Mat im)
{
	Point p,p1,p2;
	//list<Point> listp;
	//Mat im;
	int max_x=0,max_y=0,min_x=in.rows,min_y=in.cols;	
	
/*	p.x = 100;
	p.y = 249;
	listp.push_front(p);
	p.x = 122;
	p.y = 341;
	listp.push_front(p);
	p.x = 130;
	p.y = 130;
	listp.push_front(p);
	p.x = 120;
	p.y = 140;
	listp.push_front(p);
	p.x = 130;
	p.y = 340;
	listp.push_front(p);	   
*/
	list<Point>::iterator iter;
	for(iter = listp.begin() ; iter!= listp.end() ; ++iter)
	{	
		if(max_x<iter->x)
			max_x=iter->x;
		if(min_x>iter->x)
			min_x=iter->x;
		if(max_y<iter->y)
			max_y=iter->y;
		if(min_y>iter->y)
			min_y=iter->y;
	}
	cout<<"max_x:"<<max_x;			
	cout<<"max_y"<<max_y;
	cout<<"min_x"<<min_x;
	cout<<"min_y"<<min_y;
	cout<<endl;
	p1.y=min_x;
	p1.x=min_y;
	p2.y=max_x;
	p2.x=max_y;			
//	Rect rectangle;
	rectangle(im, p1, p2, Scalar(255,255,255));
	//namedWindow("LOL",CV_WINDOW_AUTOSIZE);
	//imshow("LOL",im);
	//waitKey(0);
}

//****************************METHOD TO CALCULATE COM OF IMAGE***********
void calcom(Mat im)
{
	
}

//************************MAIN FUNCTION**********************************

int main(int arg, char** argv)
{
//	int x ,y;
	int i,j;
	/*int in[M][N] = {{1, 1, 1, 1, 1, 1, 1, 1},
		             {1, 1, 1, 1, 1, 1, 0, 0},
				      {1, 0, 0, 1, 1, 0, 1, 1},
				      {1, 2, 2, 2, 2, 0, 1, 0},
				      {1, 1, 1, 2, 2, 0, 1, 0},
				      {1, 1, 1, 2, 2, 2, 2, 0},
				      {1, 1, 1, 1, 1, 2, 1, 1},
				      {1, 1, 1, 1, 1, 2, 2, 1},
		             };*/
	in = imread(argv[1]);
	thresh(in,tl);
	//cout<<"Hellomain";
	//cout<<endl;

	t_imc = t_im.clone();

	//waitKey(0);
	for(i=0;i<t_imc.rows;i++)
	{   
		for(j=0;j<t_imc.cols;j++)
		{listp.clear();
			if(t_imc.at<uchar>(i,j)==comp)
			{
				//x = i;
				//y = j;
				floodFill(t_im, i, j);
				listll.push_front(listp);
				drawrec(in);
			}
			continue;
		}
		continue;
	}


	//cout<<x<<","<<y;
	//if(t_im.at<uchar>(x,y)==comp)
	//{    

	//}
	/*for (std::list<int>::iterator it=int_list.begin(); it != int_list.end(); ++it)
		{std::cout << ' ' << *it;
	  }//cout<<endl;}
	 cout<<endl;
		for (int i=0; i<M; i++)
		{
		    for (int j=0; j<N; j++)
		       cout << in[i][j] << " ";
		    cout << endl;
		}
	*/

//	cout<<"AT I,J"<<in.at<uchar>(i,j);	
	namedWindow("Input",CV_WINDOW_AUTOSIZE);
	imshow("Input",in);
	waitKey(0);
	namedWindow("Threshmain",CV_WINDOW_AUTOSIZE);
	imshow("Threshmain",t_im);
	waitKey(0);
//	namedWindow("rec",CV_WINDOW_AUTOSIZE);
//	imshow("rec",t_im);
	namedWindow("Threshcopy",CV_WINDOW_AUTOSIZE);
	imshow("Threshcopy",t_imc);
	waitKey(0);

	cout<<"\nRecursion times"<<counter;

	return 0;
}
