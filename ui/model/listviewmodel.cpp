#include "listviewmodel.h"

ListViewModel::ListViewModel(QObject *parent)
{

}

int ListViewModel::rowCount(const QModelIndex &parent) const{
    return listData.count();
}

QVariant ListViewModel::data(const QModelIndex &index, int role) const{
    if (role == Qt::DisplayRole){
        return listData.at(index.row());
    }

    return QVariant();
}

void ListViewModel::refrushModel(){
    this->beginResetModel();
    this->endResetModel();
}

//pubic slots
