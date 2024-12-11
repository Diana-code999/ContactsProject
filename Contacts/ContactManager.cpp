#include "ContactManager.h"
#include <iostream>

void ContactManager::addContact(const Contact& contact) {
    contacts.push_back(contact);
}

void ContactManager::deleteContact(int index) {
    if (index >= 0 && index < contacts.size()) {
        contacts.erase(contacts.begin() + index);
    }
}

void ContactManager::listContacts() const {
    if (contacts.empty()) {
        std::cout << "List of contacts is empty.\n";
        return;
    }

    for (size_t i = 0; i < contacts.size(); ++i) {
        const auto& contact = contacts[i];
        std::cout << i + 1 << ". " << contact.getFirstName() << " " << contact.getLastName()
                  << " (" << contact.getEmail() << ")\n";
    }
}

void ContactManager::setContact(int index, const Contact& contact) {
    if (index >= 0 && static_cast<size_t>(index) < contacts.size()) {
        contacts[index] = contact;
    }
}

const std::vector<Contact>& ContactManager::getContacts() const {
    return contacts;
}
