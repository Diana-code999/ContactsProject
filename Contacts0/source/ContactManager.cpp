#include "../headers/ContactManager.h"
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
        std::cout << i + 1 << ". " << contact.getFirstName() << " " << contact.getLastName() << " (" << contact.getEmail() << ") " 
        << contact.getPhoneNumbers()[0] << "\n";
    }
}

void ContactManager::findContacts(std::string value){
    for (size_t i = 0; i < contacts.size(); ++i) {
        const auto& contact = contacts[i];
        if(contact.getFirstName() == value || contact.getLastName() == value || contact.getEmail() == value){
        std::cout << i + 1 << ". " << contact.getFirstName() << " " << contact.getLastName()
                  << " (" << contact.getEmail() << ")\n";
        }
    }
}

void ContactManager::sortContacts(std::string field) {
    if (field == "firstName") {
        std::sort(contacts.begin(), contacts.end(), [](const Contact& a, const Contact& b) {
            return a.getFirstName() < b.getFirstName();
        });
    } else if (field == "lastName") {
        std::sort(contacts.begin(), contacts.end(), [](const Contact& a, const Contact& b) {
            return a.getLastName() < b.getLastName();
        });
    } else if (field == "email") {
        std::sort(contacts.begin(), contacts.end(), [](const Contact& a, const Contact& b) {
            return a.getEmail() < b.getEmail();
        });
    } else {
        std::cerr << "Unknown field for sorting: " << field << std::endl;
    }
}

void ContactManager::editContact(int index, std::string valueToChange, std::string value){
    Contact contact = contacts[index];
    if(valueToChange == "firstName") contacts[index].setFirstName(value);
    else if(valueToChange == "lastName") contacts[index].setLastName(value);
    else if(valueToChange == "middleName") contacts[index].setMiddleName(value);
    else if(valueToChange == "birthDate") contacts[index].setBirthDate(value);
    else if(valueToChange == "email") contacts[index].setEmail(value);
    else if(valueToChange == "address") contacts[index].setAddress(value);
    else if(valueToChange == "phoneNumbers"){
        std::istringstream stream(value);
        std::string number;
        std::vector<std::string> numbers;
        while (stream >> number) {
            numbers.push_back(number);
        }
        contacts[index].setPhoneNumbers(numbers);
    } 
    else std::cout<< "Unknown field to edit: " << std::endl;
    if(!contacts[index].isValidDate() || !contacts[index].validate()){
        contacts[index] = contact;
        std::cout<<"Contacts are not valid!"<<std::endl;
    }
    else std::cout<< "Contacts are successfully edited!"<<std::endl;
}



Contact& ContactManager::getContact(int index){
    return contacts[index];
}

const std::vector<Contact>& ContactManager::getContacts() const {
    return contacts;
}
