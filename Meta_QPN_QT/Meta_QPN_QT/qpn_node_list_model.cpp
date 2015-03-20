#include "qpn_node_list_model.h"


qpn_node_list_model::qpn_node_list_model(meta_qpn_controller* controller):qpn(controller)
	{
	nNames = QStringList();
	std::list<std::string> nodeNames= std::list<std::string>();
	controller->getNodeNames(nodeNames);
	for(auto i_nName = nodeNames.begin();i_nName!=nodeNames.cend();i_nName++)
		nNames.push_back(QString::fromStdString(*i_nName));
	}


qpn_node_list_model::~qpn_node_list_model(void)
	{
	}


int qpn_node_list_model::rowCount(const QModelIndex & parent) const
	{
	return 3;
	return qpn->nodesCount();
	}
QVariant qpn_node_list_model::data(const QModelIndex & index, int role) const
	{
	if (role == Qt::DisplayRole)
		{
		return QString("Row%1, Column%2")
			.arg(index.row() + 1);
			
		}
	return QVariant();
	return QVariant(nNames.at(index.row()));
	}

bool qpn_node_list_model::setData(const QModelIndex & index, const QVariant & value, int role)
	{
	std::string nName = value.toString().toLocal8Bit().constData();
	qpn->addNode(nName);
	nNames.push_back(value.toString());
	nNames.replace(0, value.toString());
	emit dataChanged(index, index);
	return true;
	}
Qt::ItemFlags qpn_node_list_model::flags(const QModelIndex & index) const
	{
	return Qt::ItemIsEditable;
	}