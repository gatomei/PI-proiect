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

void calcMagAng(Mat img, Mat& magnitude, Mat &angle) {

	Mat Gx, Gy;

	//setez dx = 1, dy = 0, k_size = 1 
	//k_size=width && height of the filter mask
	Sobel(img, Gx, CV_32F, 1, 0, 1);

	//setez dx = 0, dy = 1, k_size = 1
	Sobel(img, Gy, CV_32F, 0, 1, 1);

	cartToPolar(Gx, Gy, magnitude, angle, true);// setez ca magnitudinea si unghiul sa se masoare in grade(ultimul param)
	
}

Mat HOG(Mat magnitude, Mat angle, int featureDimension) {


	Mat features(1, featureDimension, CV_32F); // CV_32F ->valPixel va apartine [0,1.0]
	features = 0.0;

	float binLen = 360 / float(featureDimension);

	float* limits = new float[featureDimension]; 
	float* medlimits = new float[featureDimension];

	int rows = magnitude.rows;
	int cols = magnitude.cols;

	int indx;//indexul la care vom adauga in vector produsul proportion*magnitude
	int sideIndx;// indexul vecin lui indx

	float difference;
	float proportion;//proportion = 1 - difference / binLen

	float val; // valoarea pe care o voi insera pe poz indx
	float sideVal; //valorea pe care o voi insera pe poz sideIndx

	if ((magnitude.rows != angle.rows) || (magnitude.cols != angle.cols)) {

		cerr << "Dimensiunile matricelor dimension si angle trebuie sa corespunda!\n";
		exit(0);

	}

	limits[0] = binLen / 2;
	medlimits[0] = 0;
	for (int i = 1; i < featureDimension; ++i) {

		limits[i] = limits[i - 1] + binLen;
		medlimits[i] = i * binLen;// medlimits[i] = ( limits[i-1] + limits[i] ) / 2 , i>=1
	}

	for (int i = 0; i < rows; ++i) {

		for (int j = 0; j < cols; ++j) {

			float angleVal = angle.at<float>(i, j);
			float magVal = magnitude.at<float>(i, j);

			
			if (angleVal <= limits[0] || angleVal >= limits[featureDimension - 1]) {

				indx = 0;

				//verific daca angleVal este mai mare decat 0 si mai mic decat prima limita a vectorului limits
				if (angleVal >= medlimits[0] && angleVal <= limits[0]) { 

					difference = angleVal;
					sideIndx = 1;

				}
				else {

					//in acest caz angleVal e mai mic decat 360 de grade si mai mare decat ultima limita a vectorului limits
					difference = abs(angleVal - 360);
					sideIndx = featureDimension - 1;
				}
			}
			else {
				//tratez restul cazurilor
				for (int k = 0; k < featureDimension - 1; k++)
				{
					if (angleVal >= limits[k] && angleVal < limits[k + 1]) {
						
							difference = abs(angleVal - medlimits[k + 1]);
							indx = k + 1;

							if (angleVal >= medlimits[k + 1]) {

								if ((k + 1) == featureDimension - 1)
									sideIndx = 0;
								else
									sideIndx = k + 2;
							}
							else {
								sideIndx = k;
							}

						break;
					}
				}
			}
			proportion = 1 - difference / binLen;

			val = proportion * magVal;
			sideVal = (1.f - proportion) * magVal;

			features.at<float>(0, indx) += val;
			features.at<float>(0, sideIndx) += sideVal;

		}
	}

	return features;

}