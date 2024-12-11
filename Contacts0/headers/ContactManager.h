#ifndef CONTACTMANAGER_H
#define CONTACTMANAGER_H

#include "Contact.h"
#include <algorithm>
#include <vector>
#include <sstream>
class ContactManager {
public:
    void addContact(const Contact& contact);
    void deleteContact(int index);
    void listContacts() const;
    const std::vector<Contact>& getContacts() const;
    Contact& getContact(int index);
    void findContacts(std::string value);
    void sortContacts(std::string field);
    void editContact(int index, std::string valueToChange, std::string value);
private:
    std::vector<Contact> contacts;
};

#endif // CONTACTMANAGER_H
