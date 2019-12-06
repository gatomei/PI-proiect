#pragma once
#include <iostream>
#include <math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

Mat binarize(cv::Mat image);
void calcMagAng(Mat img, Mat &magnitude, Mat &angle);
Mat HOG(Mat magnitude, Mat angle, int featureDimension);