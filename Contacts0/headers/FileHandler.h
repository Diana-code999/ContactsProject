#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "Contact.h"
#include <vector>
#include <string>

class FileHandler {
public:
    static bool saveToFile(const std::string& filePath, const std::vector<Contact>& contacts);
    static std::vector<Contact> loadFromFile(const std::string& filePath);
};

#endif // FILEHANDLER_H
