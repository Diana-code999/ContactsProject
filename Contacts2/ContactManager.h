#ifndef CONTACTMANAGER_H
#define CONTACTMANAGER_H

#include "Contact.h"
#include <vector>

class ContactManager {
public:
    void addContact(const Contact& contact);
    void deleteContact(int index);
    void listContacts() const;
    const std::vector<Contact>& getContacts() const;
    void setContact(int index, const Contact& contact);
private:
    std::vector<Contact> contacts;
};

#endif // CONTACTMANAGER_H
