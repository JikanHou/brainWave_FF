#ifndef MATRIX_H
#define MATRIX_H
#include <QVector>

class Matrix{    
protected:
    QVector<QVector<double>> mat;

public:
    Matrix(int row = 0, int col = 0);
    int row();
    int col();
    QVector<double> &addRow();
    void clear();
    void resize(int row, int col);
    QVector<double> &operator [](const int x);
    void output();
};

#endif // MATRIX_H
