#include <iostream>
#include "../headers/ContactManager.h"
#include "../headers/FileHandler.h"
void saveContactsToFile(ContactManager& manager) {
    std::cout << "Enter the path to the file: ";
    std::string filePath;
    std::cin >> filePath;

    if (FileHandler::saveToFile(filePath, manager.getContacts())) {
        std::cout << "Contacts are successfully saved into file.\n";
    } else {
        std::cout << "The error ocured while data saving.\n";
    }
}

void loadContactsFromFile(ContactManager& manager) {
    std::cout << "Enter the path to the file: ";
    std::string filePath;
    std::cin >> filePath;

    auto contacts = FileHandler::loadFromFile(filePath);
    if (!contacts.empty()) {
        for (const auto& contact : contacts) {
            manager.addContact(contact);
        }
        std::cout << "Contacts are successfully loaded from file.\n";
    } else {
        std::cout << "The error ocured while data loading.\n";
    }
}

int main() {
    ContactManager manager;

    while (true) {
        std::cout << "\n=== Phone Directory ===\n";
        std::cout << "1. Add contact\n";
        std::cout << "2. Delete contact\n";
        std::cout << "3. Show contacts\n";
        std::cout << "4. Save contacts to file\n";
        std::cout << "5. Load contacts from file\n";
        std::cout << "6. Edit contacts\n";
        std::cout << "7. Find Contact\n";
        std::cout << "8. Sort contacts\n";
        std::cout << "9. Quite\n";
        std::cout << "Choose action: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cin.ignore(); 
                Contact contact;
                std::string firstName;
                std::string lastName;
                std::string middleName;
                std::string address;
                std::string birthDate;
                std::string email;
                std::string phoneNumber;
                std::vector<std::string> phoneNumbers;
                std::cout<<"Enter you'r name"<<std::endl;
                std::getline(std::cin, firstName);
                std::cout<<"Enter you'r last name"<<std::endl;
                std::getline(std::cin, lastName);
                std::cout<<"Enter you'r middle name"<<std::endl;
                std::getline(std::cin, middleName);
                std::cout<<"Enter you'r address"<<std::endl;
                std::getline(std::cin, address);
                std::cout<<"Enter you'r birthdate"<<std::endl;
                std::getline(std::cin, birthDate);
                std::cout<<"Enter you'r email"<<std::endl;
                std::getline(std::cin, email);
                std::cout<<"Enter you'r phone numbers, to stop entering phone nimbers just enter: 'end'"<<std::endl;
                while(true){
                    std::getline(std::cin, phoneNumber);
                    if(phoneNumber == "end") break;
                    phoneNumbers.push_back(phoneNumber);
                }
                contact.setFirstName(firstName);
                contact.setLastName(lastName);
                contact.setMiddleName(middleName);
                contact.setAddress(address);
                contact.setBirthDate(birthDate);
                contact.setEmail(email);
                contact.setPhoneNumbers(phoneNumbers);
                if(contact.validate() && contact.isValidDate()) manager.addContact(contact);
                else std::cout<<"You'r data is incorrect please check it again"<<std::endl;
                break;
            }
            case 2:
                manager.listContacts();
                std::cout << "Enter index of contact tp delete: ";
                int index;
                std::cin >> index;
                manager.deleteContact(index - 1);
                break;
            case 3:
                manager.listContacts();
                break;
            case 4:
                saveContactsToFile(manager);
                break;
            case 5:
                loadContactsFromFile(manager);
                break;
            case 6:{
                std::cout << "Enter index of editing contact: ";
                int index;
                std::cin >> index;
                index--;
                if(index >= 0 && index < manager.getContacts().size()){
                std::string valueToChange;
                std::string value;
                std::cin.ignore(); 
                std::cout<<"Enter the value you want to change: "<<std::endl;
                std::getline(std::cin, valueToChange);
                std::cout<<"Enter new value: "<<std::endl;
                std::getline(std::cin, value);
                manager.editContact(index, valueToChange, value);
                }
                else std::cout<<"index is out of range"<<std::endl;
                break;  
            }
            case 7:{
                std::cin.ignore(); 
                std::cout << "Enter contact info (last name, first name or email): ";
                std::string value;
                std::getline(std::cin, value);
                manager.findContacts(value);
                break;  
            }
            case 8:{
                std::cin.ignore(); 
                std::cout << "Enter value wich contacts will be sorted: ";
                std::string value;
                std::getline(std::cin, value);
                manager.sortContacts(value);
                break;  
            }
            case 9:
                std::cout << "Quite.\n";
                return 0;
            default:
                std::cout << "Unsapported action, try again.\n";
        }
    }
}
