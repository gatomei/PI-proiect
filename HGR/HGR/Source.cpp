#include "Functii.h"


int main()
{
	string palma = "Images\\palma\\p";
	vector<Mat> palmImg = prepareInputData(palma);
	
	string like = "Images\\like\\l";
	vector<Mat> likeImg = prepareInputData(like);

	Mat palmDescriptors = computeHog(palmImg);
	Mat likeDescriptors = computeHog(likeImg);

	//concatenate descriptors for all types of images into a vector
	vector<Mat> Descriptors;
	Descriptors.push_back(palmDescriptors); 
	Descriptors.push_back(likeDescriptors);
	
	vector<int> labels;
	Mat inputTrain;
	shuffleData(Descriptors, inputTrain, labels);

	Ptr<SVM> svm = trainSvm(inputTrain, labels);

	//test
	string testFilename = "Images\\test\\testPalm.jpg";
	int result = predictGestureType(testFilename, svm);
	interpretateResult(result);

	waitKey(0);
	system("pause");
	return 0;
}