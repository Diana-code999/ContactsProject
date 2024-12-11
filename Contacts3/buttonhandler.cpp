#include "buttonhandler.h"
#include <QString>

ButtonHandler::ButtonHandler(ContactManager &manager, QTableWidget *table, const QList<QLineEdit *> &fields, QObject *parent)
    : QObject(parent), manager(manager), table(table), fields(fields){
}

ButtonHandler::~ButtonHandler() = default;

void ButtonHandler::AddUser()
{

    QStringList rowData;
    for (auto *field : fields) {
        rowData.append(field->text());
    }
    QString phoneNumbersStr = fields[6]->text();
    std::vector<std::string> phoneNumbers;
    for (const auto &phone : phoneNumbersStr.split(',')) {
        phoneNumbers.push_back(phone.trimmed().toStdString());
    }
    Contact contact(rowData[0].toStdString(), rowData[1].toStdString(), rowData[2].toStdString(),
                    rowData[3].toStdString(), rowData[4].toStdString(), rowData[5].toStdString(),
                    phoneNumbers);

    if(contact.validate() && contact.isValidDate()) {
        manager.addContact(contact);

    int row = table->rowCount();
    table->insertRow(row);

    for (int i = 0; i < rowData.size(); ++i) {
        table->setItem(row, i, new QTableWidgetItem(rowData[i]));
    }

    for (auto *field : fields) {
        field->clear();
    }
    }
}

void ButtonHandler::onCellChanged(int row, int column) {
    if (row < 0 || static_cast<size_t>(row) >= manager.getContacts().size()) return;

    Contact contact = manager.getContacts()[row];

    QString newValue = table->item(row, column)->text();

    switch (column) {
    case 0: contact.setFirstName(newValue.toStdString()); break;
    case 1: contact.setLastName(newValue.toStdString()); break;
    case 2: contact.setMiddleName(newValue.toStdString()); break;
    case 3: contact.setAddress(newValue.toStdString()); break;
    case 4: contact.setBirthDate(newValue.toStdString()); break;
    case 5: contact.setEmail(newValue.toStdString()); break;
    case 6: {
        QStringList phones = newValue.split(',');
        std::vector<std::string> phoneNumbers;
        for (const QString& phone : phones) {
            phoneNumbers.push_back(phone.toStdString());
        }
        contact.setPhoneNumbers(phoneNumbers);
        break;
    }
    }
    manager.setContact(row, contact);
}

void ButtonHandler::onSearch(QString query) {
    table->clearContents();
    table->setRowCount(0);

    for (const auto& contact : manager.getContacts()) {
        if (QString::fromStdString(contact.getFirstName()).contains(query, Qt::CaseInsensitive) ||
            QString::fromStdString(contact.getLastName()).contains(query, Qt::CaseInsensitive) ||
            QString::fromStdString(contact.getEmail()).contains(query, Qt::CaseInsensitive)) {

            int row = table->rowCount();
            table->insertRow(row);

            table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(contact.getFirstName())));
            table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(contact.getLastName())));
            table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(contact.getMiddleName())));
            table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(contact.getAddress())));
            table->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(contact.getBirthDate())));
            table->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(contact.getEmail())));

            QStringList phones;
            for (const auto& phone : contact.getPhoneNumbers()) {
                phones.append(QString::fromStdString(phone));
            }
            table->setItem(row, 6, new QTableWidgetItem(phones.join(", ")));
        }
    }
}

void ButtonHandler::sortTableByColumn(QString columnName) {

    int columnIndex = -1;

    if (columnName == "firstName") columnIndex = 0;
    else if (columnName == "lastName") columnIndex = 1;
    else if (columnName == "middleName") columnIndex = 2;
    else if (columnName == "address") columnIndex = 3;
    else if (columnName == "birthDate") columnIndex = 4;
    else if (columnName == "email") columnIndex = 5;
    else if (columnName == "phoneNumbers") columnIndex = 6;

    if (columnIndex == -1) {
        return;
    }

    table->sortItems(columnIndex);
}



void ButtonHandler::DeleteUser(){
    table->removeRow(id);
    manager.deleteContact(id);
}

void ButtonHandler::setId(int id){
    this->id = id;
}
