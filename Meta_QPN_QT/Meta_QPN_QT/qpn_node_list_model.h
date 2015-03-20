#pragma once
#include <QAbstractListModel>
#include <QVariant>
#include <QModelIndex>
#include <QString>
#include <QStringList>

#include "../../Meta_QPN/Meta_QPN/meta_qpn_controller.h"

class qpn_node_list_model :
	public QAbstractListModel
	{
	public:
		qpn_node_list_model(meta_qpn_controller* controller);
		~qpn_node_list_model(void);

		int rowCount(const QModelIndex & parent = QModelIndex()) const;
		QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

		bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
			Qt::ItemFlags flags(const QModelIndex & index) const;

	private:
		meta_qpn_controller* qpn;
		QStringList nNames;
	};

