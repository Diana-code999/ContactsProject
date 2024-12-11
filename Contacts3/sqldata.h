#ifndef SQLDATA_H
#define SQLDATA_H

#include "Contact.h"
#include <vector>
#include <QString>
#include <QSqlDatabase>

class SQLData {
public:
    SQLData(const QString& dbPath);
    ~SQLData();

    bool saveContactsToDB(const std::vector<Contact>& contacts);
    std::vector<Contact> loadContactsFromDB();

private:
    QSqlDatabase db;
    bool createTable();
};

#endif // SQLDATA_H
