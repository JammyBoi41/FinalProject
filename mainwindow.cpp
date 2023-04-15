
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <sstream>
#include "HashTable.h"
#include <string>
#include "QFile"
#include <map>

HashTable table;

string mode;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_radioHashTable_clicked()
{
    table.clearHashTable();

    mode = "HashTable";

    int added = 0;

    int total = 539382;

    float progress = (float(added) / float(total)) * 100;

    std::ifstream inputFile;
    inputFile.open("C:\\Users\\gavin\\Documents\\QtProjects\\COP3530FinalProjectGUI\\airlines_delay.csv");

    std::string line = "";
    getline(inputFile, line); // x throw away header line
    line = "";

    while (getline(inputFile, line)) {

        int id;
        int departTime;
        int flightDuration;
        std::string airline;
        std::string origin;
        std::string destination;
        int day;
        int delayed;
        int delayDuration;

        std::string temp = "";

        std::stringstream inputString(line);

        getline(inputString, temp, ',');
        id = atoi(temp.c_str());

        getline(inputString, temp, ',');
        departTime = atoi(temp.c_str());

        getline(inputString, temp, ',');
        flightDuration = atoi(temp.c_str());

        getline(inputString, airline, ',');
        getline(inputString, origin, ',');
        getline(inputString, destination, ',');

        getline(inputString, temp, ',');
        day = atoi(temp.c_str());

        getline(inputString, temp, ',');
        delayed = atoi(temp.c_str());

        getline(inputString, temp, ',');
        delayDuration = atoi(temp.c_str());

        Flight flight(id, departTime, flightDuration, airline, origin,
                      destination, day, delayed, delayDuration);

        table.insert(flight);

        added++;

        line = "";

    }

    std::cout << "Hash table loaded" << std::endl;

}


void MainWindow::on_radioGraph_clicked()
{

    mode = "Graph";

    table.clearHashTable();



    std::cout << "Graph loaded" << std::endl;

}


void MainWindow::on_howManyDelaysInput_clicked()
{
    std::map<std::string, int> weekdays;

    weekdays["Sunday"] = 1;
    weekdays["Monday"] = 2;
    weekdays["Tuesday"] = 3;
    weekdays["Wednesday"] = 4;
    weekdays["Thursday"] = 5;
    weekdays["Friday"] = 6;
    weekdays["Saturday"] = 7;

    if (mode == "HashTable") {

        QString origin = ui->origin->text();
        QString destination = ui->destination->text();
        QString day = ui->dayBox->currentText();
        QString delayed = QString::number(table.findDelays(origin.toStdString(), destination.toStdString(), weekdays[day.toStdString()]));
        QString total = QString::number(table.numOfFlights(origin.toStdString(), destination.toStdString(), weekdays[day.toStdString()]));

        if (delayed.toInt() == -1) {

            ui->howManyDelaysOutput->setText(day + " flights from " + origin + " to " + destination + " couldn't be found");

        }

        else {

            ui->howManyDelaysOutput->setText(day + " flights from " + origin + " to " + destination + " have been delayed " + delayed + " out of " + total + " times");

        }

    }

    else {

    }

}


void MainWindow::on_avgDelayTimeInput_clicked()
{
    std::map<std::string, int> weekdays;

    weekdays["Sunday"] = 1;
    weekdays["Monday"] = 2;
    weekdays["Tuesday"] = 3;
    weekdays["Wednesday"] = 4;
    weekdays["Thursday"] = 5;
    weekdays["Friday"] = 6;
    weekdays["Saturday"] = 7;

    if (mode == "HashTable") {

        QString origin = ui->origin->text();
        QString destination = ui->destination->text();
        QString day = ui->dayBox->currentText();
        QString avg = QString::number(table.findAvgDelay(origin.toStdString(), destination.toStdString(), weekdays[day.toStdString()]));

        if (avg.toFloat() == -1) {

            ui->avgDelayTimeOutput->setText(day + " flights from " + origin + " to " + destination + " couldn't be found");

        }

        else {

            ui->avgDelayTimeOutput->setText(day + " flights from " + origin + " to " + destination + " have an average delay time of " + avg + " minutes");

        }

    }

    else {

    }

}

