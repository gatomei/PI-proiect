#ifndef HGR_H
#define HGR_H

#include <QMainWindow>
#include <QDir>
#include <QComboBox>
#include <QPixmap>
#include <QGraphicsScene>

#include "AppLogic.H"

QT_BEGIN_NAMESPACE
namespace Ui { class HGR; }
QT_END_NAMESPACE



class HGR : public QMainWindow
{
	Q_OBJECT

public:
	HGR(QWidget *parent = nullptr);
	~HGR();

private slots:
	void on_pushButton_clicked();

	void on_ImageCmbBox_editTextChanged(const QString &arg1);

	void on_label_2_linkActivated(const QString &link);

	void on_ImageCmbBox_currentTextChanged(const QString &arg1);
	void interpretateResult(int result);

	void on_failure_clicked();

	void on_succes_clicked();
	void computeAccuracy();

private:
	Ui::HGR *ui;
	QGraphicsScene *scene = nullptr;
	Ptr<SVM> svm;

	int succes_nr = 0;
	int failure_nr = 0;
};
#endif // HGR_H
