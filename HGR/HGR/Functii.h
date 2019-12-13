#pragma once
#include <iostream>
#include <math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/ml/ml.hpp>
#include <vector>
#include <string>

using namespace cv;
using namespace std;
using namespace cv::ml;

Mat binarize(cv::Mat image);

vector<Mat> prepareInputData(string filename);
Mat computeHog(vector<Mat> inputData);
void shuffleData(vector<Mat> input, Mat &inputTrain, vector<int> &labels);
Ptr<SVM> trainSvm(Mat inputTrain, vector<int> labels);
int predictGestureType(string filename, Ptr<SVM> trainedSvm);
void interpretateResult(int result);