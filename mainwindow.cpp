#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include <QFile>
// #include <QTextCodec>
#include <QFileDialog>
#include <QProgressDialog>
#include <QMessageBox>
#include <windows.h>
#include "qcustomplot.h"

MainWindow:: MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui -> setupUi(this);
    ui -> actionAnalyse -> setCheckable(false);
    ui -> actionImport -> setCheckable(false);

    currentInfo = nullptr;
    initSettings();
    // connect(ui -> actionImport, &QAction::triggered, this, &MainWindow:: ActionImportClicked);
    // loadFromFile("C:\\Users\\houji\\Desktop\\test.txt");
}

MainWindow:: ~MainWindow(){
    delete ui;
    if (currentInfo != nullptr){
        delete currentInfo;
    }
}

void MainWindow:: initSettings(){
    QSettings settings("BrainWave");
    int windowSize = settings.value("windowSize", 10).toInt();
    int picHeight = settings.value("picHeight", 1200).toInt();
    int picWidth = settings.value("picWidth", 2000).toInt();
    bool showTopPoint = settings.value("showTopPoint", true).toBool();
    bool showBottomPoint = settings.value("showBottomPoint", true).toBool();
    bool showBaseline = settings.value("showBaseline", true).toBool();
    settings.setValue("windowSize", windowSize);
    settings.setValue("picHeight", picHeight);
    settings.setValue("picWidth", picWidth);
    settings.setValue("showTopPoint", showTopPoint);
    settings.setValue("showBottomPoint", showBottomPoint);
    settings.setValue("showBaseline", showBaseline);
}

PatientInfo MainWindow:: LoadFromFile(const QString &filepath){
    PatientInfo ret;
    Matrix mat;
    QFile file(filepath);
    if (!file.open(QIODevice:: ReadOnly | QIODevice:: Text)){
        qDebug() << "文件打开失败！";
        file.close();
        return ret;
    }
    //QTextCodec *codec = QTextCodec::codecForName("UTF-16LE");
    QTextStream in(&file);
    in.setEncoding(QStringConverter:: Utf16LE);
    bool s = true;
    while (!in.atEnd()){
        QString line = in.readLine();
        // QString line = QString::fromUtf16(reinterpret_cast<const char16_t*>(file.readLine().constData()));
        if (line.startsWith(QString("已中和的数据(µV)<960>="))){
            if (s){
                s = false;
            }
            else{
                s = true;
                continue;
            }
            QVector<double> row;
            line.replace("已中和的数据(µV)<960>=", "");
            line.replace("\n", "");
            while (line.endsWith("/") && !in.atEnd()){
                line.replace("/", ",");
                line.append(in.readLine());
            }
            line.replace(',', ' ');
            QTextStream in1(&line);
            while (!in1.atEnd()){
                double d; in1 >> d;
                row.append(d);
            }
            mat.PushBack(row);
        }
        else if (line.startsWith(QString("姓氏"))){
            ret.SetName(line.mid(3));
        }
        else if (line.startsWith(QString("就诊日期"))){
            ret.SetDate(line.mid(5));
        }
        else if (line.startsWith(QString("患者标识"))){
            ret.SetID(line.mid(5));
        }
    }
    file.close();
    ret.SetBrainWave(mat);
    return ret;
}

void MainWindow:: ShowInfo(const PatientInfo &info){
    ui -> edit_name -> setText(info.GetName());
    ui -> edit_id -> setText(info.GetID());
    ui -> edit_cnt -> setText(QString::number(info.GetBrainWave().Rown()));
    ui -> edit_date -> setText(info.GetDate());
}


void MainWindow::on_actionImport_triggered(){
    QString filePath = QFileDialog:: getOpenFileName(this, QString("请选择文件"), QString(), QString("文本文档 *txt"));
    if (filePath.isEmpty()){
        return;
    }
    QString fileName = filePath.split('/').last().split('.').first();
    PatientInfo info = LoadFromFile(filePath);
    ShowInfo(info);
    if (currentInfo != nullptr){
        delete currentInfo;
    }
    currentInfo = new PatientInfo(info);
}


void MainWindow::on_actionAnalyse_triggered(){
    if (currentInfo == nullptr){
        QMessageBox msgBox;
        msgBox.setText("请先导入文件！");
        msgBox.setWindowTitle("导入失败");
        msgBox.setWindowIcon(QIcon(":/Icons/favicon.ico"));
        msgBox.setIcon(QMessageBox:: Warning);
        msgBox.exec();
        return;
    }
    int bwCnt = currentInfo -> GetBrainWave().Rown();
    QProgressDialog progress("正在分析……", "中止分析", 0, bwCnt, this);
    progress.setWindowTitle("脑电波分析");
    progress.setWindowModality(Qt:: WindowModal);
    progress.setMinimumDuration(2000);
    //progress.exec();

    QSettings settings("BrainWave");
    int windowSize = settings.value("windowSize", 10).toInt();
    //windowSize = 10;
    bool cancelled = false;
    for (int i = 0; i < bwCnt; i ++){
        progress.setValue(i);
        if (progress.wasCanceled()){
            cancelled = true;
            break;
        }
        // 分析每一个文件
        QVector<double> bw = currentInfo -> GetRow(i);
        int length = bw.length();
        double sum = 0;
        QVector<double> window, res;
        for (int i = 0; i < windowSize && i < length; i ++){
            window.append(bw[i]);
            sum += bw[i];
        }
        res.append(sum / window.size());
        for (int i = windowSize; i < length; i ++){
            sum -= window.front();
            window.pop_front();
            window.append(bw[i]);
            sum += bw[i];
            res.append(sum / window.size());
        }
        //qDebug() << res;
        QString filename = currentInfo -> GetName();
        QString fileDate = currentInfo -> GetDate();
        fileDate.replace("/", "_").replace(":", "_");
        filename += fileDate + QString("_") + QString::number(i + 1);
        AnalyseBw(filename + ".png", res);
    }
    progress.setValue(bwCnt);
    if (!cancelled){
        QMessageBox msgBox;
        msgBox.setWindowTitle("分析完成");
        msgBox.setWindowIcon(QIcon(":/Icons/favicon.ico"));
        msgBox.setText("分析完毕，结果已保存至文件");
        msgBox.exec();
    }
}

void MainWindow:: AnalyseBw(QString filename, QVector<double> bw){
    QSettings settings("BrainWave");
    QCustomPlot *plot = new QCustomPlot(this);
    QVector<double> x, y = bw;
    double yMax = -10000, yMin = 100000;
    int maxX = 0, minX = 0;
    for (int i = 0; i < y.size(); i ++){
        x.append(i);
        if (y[i] < y[minX]){
            minX = i;
        }
        if (y[i] > y[maxX]){
            maxX = i;
        }
    }
    QPen funcPen;
    funcPen.setColor(Qt:: black);
    QCPGraph *funcGraph = plot -> addGraph();
    funcGraph -> setPen(funcPen);
    funcGraph -> setData(x, y);
    funcGraph -> setName("脑电图");

    yMax = y[maxX];
    yMin = y[minX];
    yMax = std:: ceil(yMax) + 1;
    yMin = std:: floor(yMin) - 1;



    bool showTopPoint = settings.value("showTopPoint").toBool();
    bool showBottomPoint = settings.value("showBottomPoint").toBool();
    if (showTopPoint){
        QCPItemTracer *maxPoint = new QCPItemTracer(plot);
        maxPoint -> setGraph(funcGraph);
        maxPoint -> setGraphKey(maxX);
        maxPoint -> setStyle(QCPItemTracer::tsCircle);
        maxPoint -> setPen(QPen(Qt::red));
        maxPoint -> setBrush(Qt::red);
        maxPoint -> setSize(15);

        QCPItemStraightLine *maxLine = new QCPItemStraightLine(plot);
        maxLine -> setPen(QPen(Qt::red, 3, Qt:: DotLine));
        maxLine -> point1 -> setCoords(maxX, -10);
        maxLine -> point2 -> setCoords(maxX, -30);

        QCPItemText *maxPointText = new QCPItemText(plot);
        maxPointText -> setPositionAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        maxPointText -> setText(QString("(%1, %2)").arg(maxX).arg(round(y[maxX] * 100) / 100.0));
        maxPointText -> position -> setCoords(maxX + 10, y[maxX]);
        maxPointText -> setFont(QFont(font().family(), 30));
    }
    if (showBottomPoint){
        QCPItemTracer *minPoint = new QCPItemTracer(plot);
        minPoint -> setGraph(funcGraph);
        minPoint -> setGraphKey(minX);
        minPoint -> setStyle(QCPItemTracer::tsCircle);
        minPoint -> setPen(QPen(Qt::red));
        minPoint -> setBrush(Qt::red);
        minPoint -> setSize(15);

        QCPItemStraightLine *minLine = new QCPItemStraightLine(plot);
        minLine -> setPen(QPen(Qt::red, 3, Qt:: DotLine));
        minLine -> point1 -> setCoords(minX, -10);
        minLine -> point2 -> setCoords(minX, -30);

        QCPItemText *minPointText = new QCPItemText(plot);
        minPointText -> setPositionAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        minPointText -> setText(QString("(%1, %2)").arg(minX).arg(round(y[minX] * 100) / 100.0));
        minPointText -> position -> setCoords(minX + 10, y[minX]);
        minPointText -> setFont(QFont(font().family(), 30));
    }
    plot -> xAxis -> setRange(0, x.size() + 50);
    plot -> yAxis -> setRange(yMin, yMax);
    plot -> xAxis -> setLabel("时间");
    plot -> xAxis -> setLabelFont(QFont(font().family(), 20));
    plot -> yAxis -> setLabel("电位");
    plot -> yAxis -> setRangeReversed(true);
    plot -> yAxis -> setLabelFont(QFont(font().family(), 20));

    std:: sort(y.begin(), y.end());
    double sum = 0;
    for (int i = y.size() / 3; i <= y.size() * 2 / 3; i ++){
        sum += y[i];
    }
    sum /= y.size() * 2 / 3 - y.size() / 3 + 1;

    bool showBaseline = settings.value("showBaseline").toBool();
    if (showBaseline){
        QPen dotPen;
        dotPen.setStyle(Qt:: PenStyle:: DashLine);
        dotPen.setColor(Qt:: blue);
        QCPGraph *lineGraph = plot -> addGraph();
        lineGraph -> setPen(dotPen);
        QVector<double> y2;
        for (int i = 0; i < y.size(); i ++){
            y2.append(sum);
        }
        lineGraph -> setData(x, y2);
        lineGraph -> setName(QString("基线：%1").arg(QString:: number(sum)));
        plot -> legend -> setVisible(true);
    }

    int width = settings.value("picWidth").toInt();
    int height = settings.value("picHeight").toInt();
    qDebug() << plot -> saveJpg(filename, width, height);
}

void MainWindow::on_actionSettings_triggered(){
    SettingsWindow *settingsWindow = new SettingsWindow;
    settingsWindow -> setWindowModality(Qt:: WindowModal);
    settingsWindow -> show();
}

