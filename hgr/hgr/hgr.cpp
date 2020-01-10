#include "hgr.h"
#include "ui_hgr.h"

HGR::HGR(QWidget *parent)
	: QMainWindow(parent),
	ui(new Ui::HGR())
{
	string palma = "Images\\palma\\p";
	vector<Mat> palmImg = prepareInputData(palma);

	string like = "Images\\like\\l";
	vector<Mat> likeImg = prepareInputData(like);
	
	string pumn = "Images\\pumn\\pu";
	vector<Mat> pumnImg = prepareInputData(pumn);

	string peace = "Images\\peace\\pe";
	vector<Mat> peaceImg = prepareInputData(peace);

	Mat palmDescriptors = computeHog(palmImg);
	Mat likeDescriptors = computeHog(likeImg);
	Mat pumnDescriptors = computeHog(pumnImg);
	Mat peaceDescriptors = computeHog(peaceImg);

	//concatenate descriptors for all types of images into a vector
	vector<Mat> Descriptors;
	Descriptors.push_back(palmDescriptors);
	Descriptors.push_back(likeDescriptors);
	Descriptors.push_back(pumnDescriptors);
	Descriptors.push_back(peaceDescriptors);

	vector<int> labels;
	Mat inputTrain;
	shuffleData(Descriptors, inputTrain, labels);

	svm = trainSvm(inputTrain, labels);
	getAccuracyData(this->succes_nr, this->failure_nr);

	
	ui->setupUi(this);
	QDir path("Images/test");
	QStringList files = path.entryList(QDir::Files);
	ui->ImageCmbBox->addItems(files);
	scene = new QGraphicsScene();
	QPixmap pixmap = QPixmap("Images/test/a1.jpg").scaled(400, 300, Qt::KeepAspectRatio);
	scene->addPixmap(pixmap);
	ui->graphicsView->setScene(scene);
	ui->graphicsView->setMinimumSize(400, 300);
	ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->graphicsView->viewport()->resize(pixmap.size());

	ui->graphicsView->show();

}


HGR::~HGR()
{
	delete ui;
}


void HGR::on_pushButton_clicked()
{
	//TO DO ->run the app
	string testFilename = "Images\\test\\"+ui->ImageCmbBox->currentText().toStdString();
	this->on_label_2_linkActivated(" ");
	_sleep(5);
	int result = predictGestureType(testFilename,this->svm);
	interpretateResult(result);

}




void HGR::on_ImageCmbBox_editTextChanged(const QString &arg1)
{
	delete this->scene;
	this->scene = nullptr;
	this->scene = new QGraphicsScene();
	QPixmap pixmap = QPixmap("Images/test/" + arg1).scaled(400, 300, Qt::KeepAspectRatio);
	scene->addPixmap(pixmap);
	ui->graphicsView->setScene(scene);
	ui->graphicsView->viewport()->resize(pixmap.size());

	ui->graphicsView->show();


}

void HGR::on_label_2_linkActivated(const QString &link)
{
	ui->prediction_lbl->setText(link);
	
}

void HGR::on_ImageCmbBox_currentTextChanged(const QString &arg1)
{
	delete this->scene;
	this->scene = nullptr;
	this->scene = new QGraphicsScene();
	this->on_label_2_linkActivated(" ");
	QPixmap pixmap = QPixmap("Images/test/" + arg1).scaled(400, 300, Qt::KeepAspectRatio);
	scene->addPixmap(pixmap);
	ui->graphicsView->setScene(scene);
	ui->graphicsView->viewport()->resize(pixmap.size());

	ui->graphicsView->show();
}
void HGR::interpretateResult(int result)
{

	switch (result)
	{
	case 0:
		this->on_label_2_linkActivated("Palma");
		break;
	case 1:
		this->on_label_2_linkActivated("Like");
		break;
	case 2:
		this->on_label_2_linkActivated("Pumn");
		break;
	case 3:
		this->on_label_2_linkActivated("Peace");
		break;


	}
}
void HGR::on_succes_clicked()
{
	this->succes_nr++;
	computeAccuracy();
	saveAccuracyData(succes_nr, failure_nr);
}

void HGR::on_failure_clicked()
{
	this->failure_nr++;
	computeAccuracy();
	saveAccuracyData(succes_nr, failure_nr);
}

void  HGR::computeAccuracy() {

	double acc = (double(succes_nr) / (succes_nr + failure_nr));
	ui->accuracy->setText(QString::number(acc*100)+"%");
}
