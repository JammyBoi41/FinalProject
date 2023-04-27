#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <QCompleter>
#include <QDesktopServices>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "HashTable.h"
#include "Graph.h"
#include "QFile"

using namespace std;

HashTable table;
Graph graph;
string mode;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //allow clickable link
    ui->airportCodeLinks->setText("<a href=\"https://www.ccra.com/airport-codes/\">(See list here)</a>");
    ui->airportCodeLinks->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->airportCodeLinks->setOpenExternalLinks(true);

    //autocomplete airport names
    QStringList airports;
    getAirports(airports);
    airports.removeDuplicates();

    QCompleter *completer = new QCompleter(airports, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->origin->setCompleter(completer);
    ui->destination->setCompleter(completer);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::getAirports(QStringList& airports)
{
    ifstream inputFile;
    inputFile.open("airlines_delay.csv");

    string line = "";
    getline(inputFile, line); // x throw away header line
    line = "";

    while (getline(inputFile, line)) {

        string origin;
        string destination;
        QString q;

        string temp = "";

        stringstream inputString(line);

        getline(inputString, temp, ',');
        getline(inputString, temp, ',');
        getline(inputString, temp, ',');
        getline(inputString, temp, ',');

        getline(inputString, origin, ',');
        q = origin.c_str();
        airports.push_back(q);

        getline(inputString, destination, ',');
        q = destination.c_str();
        airports.push_back(q);

        getline(inputString, temp, ',');
        getline(inputString, temp, ',');
        getline(inputString, temp, ',');

        line = "";
    }
}


void MainWindow::on_radioHashTable_clicked()
{
    table.clearHashTable();

    mode = "HashTable";

    int added = 0;

    ifstream inputFile;
    inputFile.open("airlines_delay.csv");

    string line = "";
    getline(inputFile, line); // x throw away header line
    line = "";

    while (getline(inputFile, line)) {

        int id;
        int departTime;
        int flightDuration;
        string airline;
        string origin;
        string destination;
        int day;
        int delayed;
        int delayDuration;

        string temp = "";

        stringstream inputString(line);

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
    cout << "Hash table loaded" << endl;
}


void MainWindow::on_radioGraph_clicked()
{
    graph.clearGraph();

    mode = "Graph";

    int added = 0;

    ifstream inputFile;
    inputFile.open("airlines_delay.csv");

    string line = "";
    getline(inputFile, line); // x throw away header line
    line = "";

    while (getline(inputFile, line)) {

        int id;
        int departTime;
        int flightDuration;
        string airline;
        string origin;
        string destination;
        int day;
        int delayed;
        int delayDuration;

        string temp = "";

        stringstream inputString(line);

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

        graph.insertEdge(origin, flight);

        added++;

        line = "";
    }
    cout << "Graph loaded!" << endl;
}


void MainWindow::on_howManyDelaysInput_clicked()
{
    map<string, int> weekdays;

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

    else { //mode == "Graph"
        QString origin = ui->origin->text();
        QString destination = ui->destination->text();
        QString day = ui->dayBox->currentText();
        QString delayed = QString::number(graph.fractionNumerator(origin.toStdString(), destination.toStdString(), weekdays[day.toStdString()]));
        QString total = QString::number(graph.fractionDenominator(origin.toStdString(), destination.toStdString(), weekdays[day.toStdString()]));

        if (delayed.toInt() == 0) {
            ui->howManyDelaysOutput->setText(day + " flights from " + origin + " to " + destination + " couldn't be found");
        }

        else {
            ui->howManyDelaysOutput->setText(day + " flights from " + origin + " to " + destination + " have been delayed " + delayed + " out of " + total + " times");
        }
    }
}


void MainWindow::on_avgDelayTimeInput_clicked()
{
    map<string, int> weekdays;

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
        QString avg = QString::number(table.findAvgDelay(origin.toStdString(), destination.toStdString(), weekdays[day.toStdString()]), 'f', 2);

        if (avg.toFloat() == -1) {
            ui->avgDelayTimeOutput->setText(day + " flights from " + origin + " to " + destination + " couldn't be found");
        }

        else {
            ui->avgDelayTimeOutput->setText(day + " flights from " + origin + " to " + destination + " have an average delay time of " + avg + " minutes");
        }

    }

    else { //mode == "Graph"
        QString origin = ui->origin->text();
        QString destination = ui->destination->text();
        QString day = ui->dayBox->currentText();
        QString avg = QString::number(graph.averageDelay(origin.toStdString(), destination.toStdString(), weekdays[day.toStdString()]), 'f', 2);

        if (avg.toFloat() == 0) {
            ui->avgDelayTimeOutput->setText(day + " flights from " + origin + " to " + destination + " couldn't be found");
        }

        else {
            ui->avgDelayTimeOutput->setText(day + " flights from " + origin + " to " + destination + " have an average delay time of " + avg + " minutes");
        }
    }

}

