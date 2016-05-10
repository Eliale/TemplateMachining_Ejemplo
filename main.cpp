#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/// Locales
Mat img; Mat templ; Mat result;
const char* image_window = "Imagen Fuente";

int match_method=3;


/// Cabezera
void MatchingMethod( int, void* );

/**
* @function main
*/
int main( int, char** argv )
{
	// Carga de escena y modelo
	img = imread( "pokemones.jpg", 1 );	
	templ = imread( "silueta.jpg", 1 );
	
	/// Creacion ventanas
	namedWindow( image_window, WINDOW_AUTOSIZE );
	MatchingMethod( 3, 0);
	waitKey(0);
	return 0;
}


void MatchingMethod( int, void* )
{
	/// Codigo de imagen
	Mat img_display;
	img.copyTo( img_display );
	
	
	/*Mat templ=image;*/
	
	/// Create the result matrix
	int result_cols =  img.cols - templ.cols + 1;
	int result_rows = img.rows - templ.rows + 1;
	
	result.create( result_rows, result_cols, CV_32FC1 );
	
	/// Reconocimiento
	matchTemplate( img, templ, result, match_method );

	
	double minVal; double maxVal; Point minLoc; Point maxLoc;
	Point matchLoc;
	
	minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
	matchLoc = maxLoc;
	
	rectangle( img_display, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
	
	
	cout << "En x " << result_cols<<endl;
	cout << "En y " << result_rows<<endl;
	
	imshow( image_window, img_display );
	return;
}

