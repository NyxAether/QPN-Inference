#include "meta_qpn_qt.h"

Meta_QPN_QT::Meta_QPN_QT(QWidget *parent)
	: QMainWindow(parent), qpn(meta_qpn_controller()), node_list(new qpn_node_list_model(&qpn))
{
	ui.setupUi(this);
	//connect(addNode, SIGNAL(clicked()), this, SLOT(addNode()));
	QObject::connect(ui.addEdgeButton, SIGNAL(clicked()), this, SLOT(addNode()));
	ui.nodeView->setModel(node_list);
}

Meta_QPN_QT::~Meta_QPN_QT()
{
delete node_list;
}


void Meta_QPN_QT::addNode(){
	 QString pseudo = QInputDialog::getText(this, "Pseudo", "Quel est votre pseudo ?");
	 if(! pseudo.isEmpty())
		 node_list->setData(QModelIndex(),pseudo);
	}