#include "qpn_node_list_model.h"


qpn_node_list_model::qpn_node_list_model(meta_qpn_controller* controller):qpn(controller)
	{
	}


qpn_node_list_model::~qpn_node_list_model(void)
	{
	}


int qpn_node_list_model::rowCount(const QModelIndex & parent) const
	{
	return 0;
	}
QVariant qpn_node_list_model::data(const QModelIndex & index, int role) const
	{
	return QVariant();
	}

bool qpn_node_list_model::setData(const QModelIndex & index, const QVariant & value, int role)
	{
	return false;
	}
Qt::ItemFlags qpn_node_list_model::flags(const QModelIndex & index) const
	{
	return Qt::NoItemFlags;
	}