#include "meta_qpn_qt.h"
#include <QtWidgets/QApplication>




int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Meta_QPN_QT w;
	w.show();
	return a.exec();
}
