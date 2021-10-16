#ifndef MYMODEL_H
#define MYMODEL_H

//! [Quoting ModelView Tutorial]
// mymodel.h
#include <QAbstractTableModel>
#include <QString>
#include <QVector>

#include "arch_info.h"

class MyModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    MyModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void setVector(QVector<Archive_info>* vect);

private:
    QVector<Archive_info> *zipContents; // содержимое zip-архива
    const int ccount{3};                // количество столбцов
};
//! [Quoting ModelView Tutorial]
//!
#endif // MYMODEL_H
