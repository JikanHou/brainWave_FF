#ifndef PATIENTINFO_H
#define PATIENTINFO_H

#include <QString>
#include "matrix.h"

class PatientInfo{
public:
    PatientInfo();

    void SetName(const QString &name);
    QString GetName() const;

    Matrix GetBrainWave() const;
    void SetBrainWave(const Matrix& bw);

    QString GetDate() const;
    void SetDate(const QString &date);

    QString GetID() const;
    void SetID(const QString &id);

    const QVector<double> GetRow(int row) const;

private:
    QString name, date, id;
    Matrix brainWave;
};

#endif // PATIENTINFO_H
