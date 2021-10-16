#include "mymodel.h"

//#include <QDebug>

MyModel::MyModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    zipContents = nullptr;
}

void MyModel::setVector(QVector<Archive_info>* vect)
{
    beginResetModel();
    zipContents = vect;
    endResetModel();
}

//-----------------------------------------------------------------
int MyModel::rowCount(const QModelIndex & /*parent*/) const
{
//    qDebug() << "zipContents->size() = " << zipContents->size();
    if (zipContents)
            return zipContents->size();
    return 0;
}

//-----------------------------------------------------------------
int MyModel::columnCount(const QModelIndex & /*parent*/) const
{
    return ccount;
}

//-----------------------------------------------------------------
QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if ( !zipContents || !index.isValid() ||
       ( index.row() >= zipContents->size() ) || (role != Qt::DisplayRole) )
        return QVariant();

    auto iter = zipContents->cbegin();
    iter += index.row();

    if (index.column() == 0)
        return iter->filename;
    if (index.column() == 1)
        return QString("%1").arg(iter->compressed_size);
    if (index.column() == 2)
        return QString("%1").arg(iter->uncompressed_size);

    return QVariant();
}

//-----------------------------------------------------------------
QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString( tr("Полное имя") );
        case 1:
            return QString( tr("Сжатый размер, bytes") );
        case 2:
            return QString( tr("Расжатый размер, bytes") );
        }
    }
    return QVariant();
}
