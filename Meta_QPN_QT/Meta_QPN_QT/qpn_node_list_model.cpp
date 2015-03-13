#include "qpn_node_list_model.h"


qpn_node_list_model::qpn_node_list_model(meta_qpn_controller* controller):qpn(controller)
	{
	}


qpn_node_list_model::~qpn_node_list_model(void)
	{
	}


int qpn_node_list_model::rowCount(const QModelIndex & parent) const
	{
	return qpn->nodesCount();
	}
QVariant qpn_node_list_model::data(const QModelIndex & index, int role) const
	{
	qpn_node<bool>* node = qpn->getNode(index.row());
	return QVariant(QString::fromStdString(node->getName()));
	}

bool qpn_node_list_model::setData(const QModelIndex & index, const QVariant & value, int role)
	{
	std::string nName = value.toString().toLocal8Bit().constData();
	qpn->addNode(nName);
	emit dataChanged(index, index);
	return true;
	}
Qt::ItemFlags qpn_node_list_model::flags(const QModelIndex & index) const
	{
	return Qt::NoItemFlags;
	}