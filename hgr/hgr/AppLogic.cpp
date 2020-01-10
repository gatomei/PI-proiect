#include "AppLogic.h"
#include <fstream>

const int nrImgs = 22;
const int noGestures = 4;
enum labels { label_palm, label_like, label_pumn, label_peace };

void saveAccuracyData(int succ, int fail) {

	ofstream f;
	f.open("accuracyData.txt");

	f << succ << " ";
	f << fail;

	f.close();
}

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

		for (int x = 0; x < image.rows; x++) {

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
vector<Mat> prepareInputData(string filename)
{
	vector<Mat> images;
	for (int j = 0; j < nrImgs; ++j)
	{
		string image = filename;
		string no = std::to_string(j + 1).append(".jpg");
		Mat temp_img = imread(image.append(no), cv::IMREAD_COLOR);
		Mat dst;
		resize(temp_img, dst, Size(200, 400));
		Mat grayImg;
		cvtColor(dst, grayImg, COLOR_BGR2GRAY);
	
		Mat distance = preprocessImg(grayImg);

		images.push_back(distance);

	}
	return images;
}

Mat computeHog(vector<Mat> inputData)
{
	HOGDescriptor hog(
		Size(64, 64), //winSize
		Size(8, 8), //blocksize
		Size(8, 8), //blockStride,
		Size(8, 8), //cellSize,
		9, //nbins,
		1, //derivAper,
		-1, //winSigma,
		0, //histogramNormType,
		0.2, //L2HysThresh,
		0,//gammal correction,
		64,//nlevels=64
		1);
	Mat imgDescriptors;
	for (auto iter = inputData.begin(); iter < inputData.end(); ++iter)
	{

		vector< float > descriptors;
		hog.compute(*iter, descriptors, hog.winSize);
		imgDescriptors.push_back(Mat(descriptors).t());

	}
	return imgDescriptors;
}
void shuffleData(vector<Mat> input, Mat &inputTrain, vector<int> &labels)
{
	int p = nrImgs;
	int l = nrImgs;
	int pu = nrImgs;
	int pe = nrImgs;

	int i = 0;

	while (p > 0 || l > 0) {

		if (i % 2 && p > 2&& pe>2 ) {

			p--;
			inputTrain.push_back(input[0].row(p));

			pe--;
			inputTrain.push_back(input[3].row(pe));

			p--;
			inputTrain.push_back(input[0].row(p));
			
			pe--;
			inputTrain.push_back(input[3].row(pe));

			i++;
			labels.push_back(label_palm);
			labels.push_back(label_peace);
			labels.push_back(label_palm);
			labels.push_back(label_peace);

		}
		else if (l > 0)
		{
			l--;
			inputTrain.push_back(input[1].row(l));
			i++;

			pu--;
			inputTrain.push_back(input[2].row(pu));
		
			labels.push_back(label_like);
			labels.push_back(label_pumn);
		}
		if (p > 0 && pe > 0 && l == 0 && pu == 0) 
		{
			--p;
			inputTrain.push_back(input[1].row(p));

			--pe;
			inputTrain.push_back(input[3].row(pe));

			labels.push_back(label_palm);
			labels.push_back(label_peace);

		}

	}
}

Ptr<SVM> trainSvm(Mat inputTrain, vector<int> labels)
{
	Ptr<SVM> svm = SVM::create();
	svm->setType(SVM::C_SVC);
	svm->setKernel(SVM::LINEAR);
	svm->setC(10);
	svm->setTermCriteria(cvTermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 1000, 1e-6));

	svm->train(inputTrain, ROW_SAMPLE, Mat(labels));
	return svm;

}

int predictGestureType(string filename, Ptr<SVM> trainedSvm)
{
	Mat test_Img = imread(filename, cv::IMREAD_COLOR);
	Mat dst;
	resize(test_Img, dst, Size(200, 400));
	Mat grayImg;
	cvtColor(dst, grayImg, COLOR_BGR2GRAY);
	Mat testF;
	Mat distance = preprocessImg(grayImg);
	vector<Mat> input;
	input.push_back(distance);
	testF = computeHog(input);
	int result = trainedSvm->predict(testF);
	return result;

}

Mat preprocessImg(Mat grayImg)
{

	int morph_size = 1;
	int morph_elem = 0;
	Mat binary(grayImg.rows, grayImg.cols, CV_8UC1);
	threshold(grayImg, binary, 128, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU);
	Mat element = getStructuringElement(morph_elem, Size(2 * morph_size + 1,
		2 * morph_size + 1), Point(morph_size, morph_size));
	Mat opened_img(binary.rows, binary.cols, CV_8UC1);
	morphologyEx(binary, opened_img, 2, element);
	Mat closed_img(binary.rows, binary.cols, CV_8UC1);
	morphologyEx(opened_img, closed_img, 3, element);

	return closed_img;
}
void getAccuracyData(int &succ, int &fail)
{
	ifstream f;
	f.open("accuracyData.txt");

	f >> succ;
	f >> fail;

	f.close();
}
