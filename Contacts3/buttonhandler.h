#ifndef BUTTONHANDLER_H
#define BUTTONHANDLER_H

#include <QObject>
#include <QPushButton>
#include <QTableWidget>
#include <QLineEdit>
#include "Contact.h"
#include "ContactManager.h"
#include "FileHandler.h"

class ButtonHandler : public QObject
{
    Q_OBJECT

public:
    ButtonHandler(ContactManager &manager, QTableWidget *table, const QList<QLineEdit *> &fields, QObject *parent = nullptr);
    void AddUser();
    void DeleteUser();
    void setId(int id);
    ~ButtonHandler();
    void onCellChanged(int row, int column);
    void onSearch(QString query);
    void sortTableByColumn(QString columnName);
private:
    ContactManager &manager;
    QTableWidget *table;
    QList<QLineEdit *> fields;
    int id;
};

#endif // BUTTONHANDLER_H
