#include "meta_qpn_qt.h"

Meta_QPN_QT::Meta_QPN_QT(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//connect(addNode, SIGNAL(clicked()), this, SLOT(addNode()));
	QObject::connect(ui.addEdgeButton, SIGNAL(clicked()), this, SLOT(addNode()));

}

Meta_QPN_QT::~Meta_QPN_QT()
{

}


void Meta_QPN_QT::addNode(){
	 QString pseudo = QInputDialog::getText(this, "Pseudo", "Quel est votre pseudo ?");
	 if(! pseudo.isEmpty())
		ui.nodeNamesListWidget->addItem(pseudo);
	}