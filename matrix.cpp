#include "matrix.h"
#include <QDebug>

Matrix::Matrix(){
    mat.clear();
}

void Matrix:: clear(){
    mat.clear();
}

int Matrix:: Rown(){
    return mat.size();
}

void Matrix:: PushBack(const QVector<double> &t){
    mat.push_back(t);
}

bool Matrix:: CheckValidate(int row, int col){
    if (row > mat.size()){
        return false;
    }
    if (col > mat[row].size()){
        return false;
    }
    return true;
}

bool Matrix:: SetVal(int row, int col, double val){
    if (!CheckValidate(row, col)){
        return false;
    }
    mat[row][col] = val;
    return true;
}

double Matrix:: GetVal(int row, int col){
    if (!CheckValidate(row, col)){
        return -1;
    }
    return mat[row][col];
}

const QVector<double> Matrix:: GetRow(int row) const{
    return mat[row];
}
