#include "captionBlur.h"
#include <QApplication>
#include <QSurfaceFormat>
#include <QProcess>
#include <QTextCodec>
#include <QDir>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	captionBlur w(argv);
	w.show();
	return a.exec();

}




