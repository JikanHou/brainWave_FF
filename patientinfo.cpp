#include "patientinfo.h"

PatientInfo::PatientInfo(){

}
void PatientInfo:: SetName(const QString &name){
    this -> name = name;
}

QString PatientInfo:: GetName() const{
    return name;
}

Matrix PatientInfo:: GetBrainWave() const{
    return this -> brainWave;
}

void PatientInfo:: SetBrainWave(const Matrix& bw){
    this -> brainWave = bw;
}

QString PatientInfo:: GetDate() const{
    return date;
}

void PatientInfo:: SetDate(const QString &date){
    this -> date = date;
}

QString PatientInfo:: GetID() const{
    return id;
}

void PatientInfo:: SetID(const QString &id){
    this -> id = id;
}

const QVector<double> PatientInfo:: GetRow(int row) const{
    return brainWave.GetRow(row);
}
