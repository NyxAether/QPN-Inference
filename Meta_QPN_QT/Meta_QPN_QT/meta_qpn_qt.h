#ifndef META_QPN_QT_H
#define META_QPN_QT_H

#include <QInputDialog>
#include <QMessageBox>
#include <QtWidgets/QMainWindow>
#include "ui_meta_qpn_qt.h"
#include <iostream>

class Meta_QPN_QT : public QMainWindow
{
	Q_OBJECT

public:
	Meta_QPN_QT(QWidget *parent = 0);
	~Meta_QPN_QT();

	public slots:
	void addNode();

private:
	Ui::Meta_QPN_QTClass ui;
};

#endif // META_QPN_QT_H
 