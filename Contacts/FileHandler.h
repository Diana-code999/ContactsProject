#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "Contact.h"
#include <vector>
#include <QString>
#include <QTableWidget>

class FileHandler {
public:
    static bool saveToFile(const std::vector<Contact>& contacts, const QString &filePath);
    static std::vector<Contact> loadFromFile(const QString &filePath);
    static void LoadContactsToTable(const std::vector<Contact>& contacts, QTableWidget *table);
};

#endif // FILEHANDLER_H
