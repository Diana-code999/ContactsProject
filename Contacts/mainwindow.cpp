#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "buttonhandler.h"
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QList<QLineEdit *> fields = {
        ui->Name,
        ui->LastName,
        ui->MiddleName,
        ui->adress,
        ui->birthdate,
        ui->mail,
        ui->phoneNumbers,
    };
    ui->tableWidget->setSortingEnabled(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
    buttonHandler = new ButtonHandler(manager, ui->tableWidget, fields,this);
    connections();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_idOfDelete_editingFinished(){
    buttonHandler->setId(ui->idOfDelete->text().toInt()-1);
    ui->idOfDelete->clear();
}


void MainWindow::connections(){
    connect(ui->AddUser, &QPushButton::clicked, buttonHandler, &ButtonHandler::AddUser);
    connect(ui->DeleteUser, &QPushButton::clicked, buttonHandler, &ButtonHandler::DeleteUser);
    connect(ui->findByRowButton, &QPushButton::clicked, this, [this]() {
        buttonHandler->onSearch(ui->findByRow->text());
    });
    connect(ui->sortFieldLineButton, &QPushButton::clicked, this, [this]() {
        QString field = ui->sortFieldLineEdit->text();
        buttonHandler->sortTableByColumn(field);
    });
    connect(ui->tableWidget, &QTableWidget::cellChanged, buttonHandler, &ButtonHandler::onCellChanged);
    connect(ui->SaveUser, &QPushButton::clicked, this, [this]() {
        FileHandler::saveToFile(manager.getContacts(), ui->filepath->text());
    });
    connect(ui->LoadUsers, &QPushButton::clicked, this, [this]() {
        std::vector<Contact> contacts = FileHandler::loadFromFile(ui->filepathtoload->text());
        for (const auto& contact : contacts) {
            manager.addContact(contact); 
        }
        FileHandler::LoadContactsToTable(contacts, ui->tableWidget);
    });
}

