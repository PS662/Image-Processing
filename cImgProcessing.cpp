#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class cImageprocessing{
private:
	 Mat image1;
	 Mat gray_image;

	String param;// = "img4.jpg";
	String dparam; //= "Display";
	String sparam; //= "output.jpg";
public:
	cImageprocessing(String);
	void readheight();
	void readwidth();
	void readpixel(int, int, int);
	void readpixel(int ,int);
	void togray();
	void display(String);
	void save(String);
};
//**************************CONSTRUCTOR*************************
cImageprocessing::cImageprocessing(String param)
{
	try{
		image1=imread(param);
		if(image1.data==NULL)
			throw("error while reading the image");

		}catch(String e){
		std::cout<<e;}
}
//********************CLASS METHODS ****************************

//************DISPLAY METHOD*************************
void cImageprocessing::display(String dparam)
	{
	 namedWindow( dparam, WINDOW_AUTOSIZE );// Create a window for display.
	 imshow( dparam, image1 );  
	waitKey(0); 
}

void cImageprocessing::readheight()
{
	cout << "Height: " <<image1.rows << endl;
}
void cImageprocessing::readwidth()
{
	cout << "Width : " <<image1.cols << endl;
}


void cImageprocessing::readpixel(int row, int col, int channel)
{	int newval[3];

	newval[0] = (int)image1.at<cv::Vec3b>(col,row)[0] ;
	newval[1] = (int)image1.at<cv::Vec3b>(col,row)[1] ;
	newval[2] = (int)image1.at<cv::Vec3b>(col,row)[2] ;

	cout<<"Blue"<<newval[0]<<endl;
	cout<<"Green"<<newval[1]<<endl;
	cout<<"Red"<<newval[2]<<endl;;
}

void cImageprocessing::readpixel(int row, int col)
{
	int value;
	value=(int)image1.at<uchar>(row,col);
	cout<<"Pixel Intensity for grayscale:"<<value<<endl;
}

void cImageprocessing::togray()
{
	gray_image = Mat(image1.rows,image1.cols,CV_8U);
    //cvtColor( image1, gray_image, CV_BGR2GRAY );

	int newval[3];	
	int i,j,avg;

	for(i=0;i<image1.rows;i++)
	{
		for(j=0;j<image1.cols;j++)
		{
			gray_image.at<uchar>(i,j) = (image1.at<cv::Vec3b>(i,j)[0]+image1.at<cv::Vec3b>(i,j)[1]+image1.at<cv::Vec3b>(i,j)[2])/3.0; 
		}
	}

}



void cImageprocessing::save(String sparam)
{ 	
	togray();
	imwrite( sparam, gray_image );
	//namedWindow( imageName, CV_WINDOW_AUTOSIZE );
	namedWindow( sparam, CV_WINDOW_AUTOSIZE );
	imshow( sparam, gray_image );
	waitKey(0);
}

int main( int argc, char** argv )
{
	String dparam= "Display";
	String sparam= "output.jpg";
	String s1 = "photo720x540.jpg";
	cImageprocessing c1(s1);

	c1.readheight();
	c1.readwidth();
	c1.readpixel(16,88);
	c1.readpixel(16,88,3);
	c1.display(dparam);                             // Wait for a keystroke in the window
	c1.togray();
	c1.save(sparam);
	return 0;
}
