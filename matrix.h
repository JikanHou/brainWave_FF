#ifndef MATRIX_H
#define MATRIX_H
#include <QVector>

class Matrix{    
private:
    QVector<QVector<double>> mat;
    bool CheckValidate(int row, int col);

public:
    Matrix();
    int Rown();
    void PushBack(const QVector<double> &t);
    bool SetVal(int row, int col, double val);
    double GetVal(int row, int col);

    const QVector<double> GetRow(int row) const;
    void clear();
};

#endif // MATRIX_H
