#include "FileHandler.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

bool FileHandler::saveToFile(const std::vector<Contact>& contacts, const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        qWarning() << "Не удалось открыть файл для записи:" << file.errorString();
        return false;
    }

    QTextStream out(&file);
    for (const auto& contact : contacts) {
        out << QString::fromStdString(contact.getFirstName()) << "`"
            << QString::fromStdString(contact.getLastName()) << "`"
            << QString::fromStdString(contact.getMiddleName()) << "`"
            << QString::fromStdString(contact.getAddress()) << "`"
            << QString::fromStdString(contact.getBirthDate()) << "`"
            << QString::fromStdString(contact.getEmail());

        for (const auto& phone : contact.getPhoneNumbers()) {
            out << "`" << QString::fromStdString(phone);
        }
        out << "\n";
    }

    file.close();
    return true;
}

std::vector<Contact> FileHandler::loadFromFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Не удалось открыть файл для чтения:" << file.errorString();
        return {};
    }

    std::vector<Contact> contacts;
    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split('`');
        if (fields.size() < 6) {
            qWarning() << "Некорректная строка в файле:" << line;
            continue;
        }

        QString firstName = fields[0];
        QString lastName = fields[1];
        QString middleName = fields[2];
        QString address = fields[3];
        QString birthDate = fields[4];
        QString email = fields[5];

        std::vector<std::string> phoneNumbers;
        for (int i = 6; i < fields.size(); ++i) {
            phoneNumbers.push_back(fields[i].toStdString());
        }
        Contact contact(firstName.toStdString(), lastName.toStdString(), middleName.toStdString(),
                        address.toStdString(), birthDate.toStdString(), email.toStdString(), phoneNumbers);

        if (contact.validate() && contact.isValidDate()) {
            contacts.push_back(contact);
        } else {
            qWarning() << "Некорректные данные контакта, пропускаем:" << line;
        }
    }

    file.close();
    return contacts;
}

void FileHandler::LoadContactsToTable(const std::vector<Contact>& contacts, QTableWidget *table)
{
    for (const auto& contact : contacts) {
        int row = table->rowCount();
        table->insertRow(row);

        table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(contact.getFirstName())));
        table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(contact.getLastName())));
        table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(contact.getMiddleName())));
        table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(contact.getAddress())));
        table->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(contact.getBirthDate())));
        table->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(contact.getEmail())));

        QStringList phoneNumbersList;
        for (const auto &phone : contact.getPhoneNumbers()) {
            phoneNumbersList.append(QString::fromStdString(phone));
        }
        table->setItem(row, 6, new QTableWidgetItem(phoneNumbersList.join(", ")));
    }
}

