#include "Functii.h"
using namespace cv;
Mat binarize(Mat image)
{
	double min, max;
	minMaxIdx(image, &min, &max);
	Mat binarized;
	int threshVal = (int)(min + max) / 2;//i-am facut cast sa scap de warningu de loss of data 

	do {


		double m1 = 0;
		long int counter1 = 0;

		double m2 = 0;
		long int counter2 = 0;

		for (int x = 0; x <image.rows; x++) {

			for (int y = 0; y < image.cols; y++) {

				// Accesssing values of each pixel
				if (image.at<uchar>(x, y) >= threshVal) {

					m1 += image.at<uchar>(x, y);
					++counter1;

				}
				else if (image.at<uchar>(x, y) < threshVal) {

					m2 += image.at<uchar>(x, y);
					++counter2;
				}
			}
		}

		m1 /= counter1;
		m2 /= counter2;

		int threshold1 = (int)(m1 + m2) / 2;

		if (threshVal == threshold1)
			break;
		threshVal = threshold1;
	} while (1);

	
	threshold(image, binarized, threshVal, 255, THRESH_BINARY_INV);
	return binarized;

}