#include "matrix.h"
#include <QDebug>

Matrix::Matrix(int row, int col){
    mat.clear();
    for (int i = 0; i < row; i ++){
        QVector<double> t;
        t.resize(col);
        mat.append(t);
    }
}

void Matrix:: clear(){
    mat.clear();
}

QVector<double> &Matrix:: addRow(){
    mat.append(QVector<double>());
    return mat[row() - 1];
}

void Matrix:: resize(int row, int col){
    *this = Matrix(row, col);
}

int Matrix:: row(){
    return mat.size();
}

int Matrix:: col(){
    if (mat.size() == 0){
        return 0;
    }
    return mat[0].size();
}

QVector<double> &Matrix::operator[](const int x){
    return mat[x];
}

void Matrix:: output(){
    qDebug() << QString("共%1条数据：").arg(mat.size());
    for (auto &vec: mat){
        qDebug() << vec;
    }
}
