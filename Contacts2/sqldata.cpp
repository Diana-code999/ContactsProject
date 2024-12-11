#include "sqldata.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <iostream>
SQLData::SQLData(const QString& dbPath) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qWarning() << "Не удалось открыть базу данных:" << db.lastError().text();
    } else {
        createTable();
    }
}

SQLData::~SQLData() {
    if (db.isOpen()) {
        db.close();
    }
}

bool SQLData::createTable() {
    QSqlQuery query;
    bool success = query.exec(R"(
        CREATE TABLE IF NOT EXISTS contacts (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            first_name TEXT,
            last_name TEXT,
            middle_name TEXT,
            address TEXT,
            birth_date TEXT,
            email TEXT,
            phone_numbers TEXT
        )
    )");

    if (!success) {
        qWarning() << "Ошибка создания таблицы:" << query.lastError().text();
    }

    return success;
}

bool SQLData::saveContactsToDB(const std::vector<Contact>& contacts) {
    QSqlQuery query;

    query.exec("DELETE FROM contacts");

    for (const auto& contact : contacts) {
        query.prepare(R"(
            INSERT INTO contacts (first_name, last_name, middle_name, address, birth_date, email, phone_numbers)
            VALUES (?, ?, ?, ?, ?, ?, ?)
        )");
        std::string phoneNumbersStr;
        for(int i = 0; i < contact.getPhoneNumbers().size(); i++){
            phoneNumbersStr.append(contact.getPhoneNumbers()[i]);
            if(i!=contact.getPhoneNumbers().size()-1) phoneNumbersStr.append(", ");
        }
        query.addBindValue(QString::fromStdString(contact.getFirstName()));
        query.addBindValue(QString::fromStdString(contact.getLastName()));
        query.addBindValue(QString::fromStdString(contact.getMiddleName()));
        query.addBindValue(QString::fromStdString(contact.getAddress()));
        query.addBindValue(QString::fromStdString(contact.getBirthDate()));
        query.addBindValue(QString::fromStdString(contact.getEmail()));
        query.addBindValue(QString::fromStdString(phoneNumbersStr));

        if (!query.exec()) {
            qWarning() << "Ошибка вставки данных:" << query.lastError().text();
            return false;
        }
    }

    return true;
}

std::vector<Contact> SQLData::loadContactsFromDB() {
    QSqlQuery query("SELECT first_name, last_name, middle_name, address, birth_date, email, phone_numbers FROM contacts");

    std::vector<Contact> contacts;

    while (query.next()) {
        std::vector<std::string> phoneNumbers;
        QStringList phoneList = query.value(6).toString().split(',');

        for (const QString &phone : phoneList) {
            phoneNumbers.push_back(phone.toStdString());
        }

        Contact contact(
            query.value(0).toString().toStdString(),
            query.value(1).toString().toStdString(),
            query.value(2).toString().toStdString(),
            query.value(3).toString().toStdString(),
            query.value(4).toString().toStdString(),
            query.value(5).toString().toStdString(),
            phoneNumbers
            );

        contacts.push_back(contact);
    }

    return contacts;
}
