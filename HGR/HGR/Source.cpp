#include "Functii.h"

using namespace cv;
int main()
{
	Mat image, greyimg,binarized;
	char *imagename = (char*)"Images\\fist.jpg";


	image = imread(imagename, cv::IMREAD_COLOR);   // Read the file

	if (!image.data)                              // Check for invalid input
	{
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	cvtColor(image, greyimg, COLOR_BGR2GRAY); //conv from color to grayscale image

	imshow("Grey", greyimg);

	binarized = binarize(greyimg);

	imshow("Binary",binarized);

	waitKey(0);                                          // Wait for a keystroke in the window

	return 0;
}