#include "hgr.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	

	QApplication a(argc, argv);
	HGR w;
	w.setWindowTitle("Hand Gesture Recognition");
	w.show();
	return a.exec();
	
}
