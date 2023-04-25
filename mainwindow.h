
#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>


QT_BEGIN_NAMESPACE

namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:



    void on_radioHashTable_clicked();

    void on_radioGraph_clicked();

    void on_howManyDelaysInput_clicked();

    void on_avgDelayTimeInput_clicked();

private:
    Ui::MainWindow *ui;

    void getAirports(QStringList& airports);

};



#endif // MAINWINDOW_H
