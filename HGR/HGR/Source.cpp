#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
int main()
{
	Mat image, greyimg;
	char *imagename = (char*)"gesture.jpg";
	image = imread(imagename, CV_LOAD_IMAGE_COLOR);   // Read the file

	if (!image.data)                              // Check for invalid input
	{
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	cvtColor(image, greyimg, COLOR_BGR2GRAY);

	namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
	//imshow("Display window", image);   // Show our image inside it.
	imshow("Display window", greyimg);
	waitKey(0);                                          // Wait for a keystroke in the window
	return 0;
}