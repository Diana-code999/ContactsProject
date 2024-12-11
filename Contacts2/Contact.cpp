#include "Contact.h"
#include <regex>

Contact::Contact(const std::string& firstName, const std::string& lastName, const std::string& middleName,
                 const std::string& address, const std::string& birthDate, const std::string& email,
                 const std::vector<std::string>& phoneNumbers)
    : firstName(firstName), lastName(lastName), middleName(middleName), address(address),
      birthDate(birthDate), email(email), phoneNumbers(phoneNumbers) {}

bool Contact::validate() const {
    std::regex nameRegex(R"(^[A-Za-zА-Яа-яЁё][A-Za-zА-Яа-яЁё\s\-]*[A-Za-zА-Яа-яЁё]$)");
    std::regex emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    std::regex phoneRegex(R"(^\+?[0-9\- ]+$)");

    if (!std::regex_match(firstName, nameRegex) ||
        !std::regex_match(lastName, nameRegex) ||
        !std::regex_match(middleName, nameRegex)) {
        return false;
    }

    if (!std::regex_match(email, emailRegex)) {
        return false;
    }

    for (const auto& phone : phoneNumbers) {
        if (!std::regex_match(phone, phoneRegex)) {
            return false;
        }
    }

    return true;
}

bool Contact::isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool Contact::isValidDate() {
    int day, month, year;
    std::string date = birthDate;

    char delimiter;
    std::istringstream stream(date);
    if (!(stream >> year >> delimiter >> month >> delimiter >> day) || delimiter != '-') {
        return false;
    }

    if (month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int maxDays = daysInMonth[month - 1];
    if (month == 2 && isLeapYear(year)) {
        maxDays = 29;
    }
    if (day > maxDays) {
        return false;
    }

    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    if (year > (now->tm_year + 1900)) return false;
    if (year == (now->tm_year + 1900) && month > (now->tm_mon + 1)) return false;
    if (year == (now->tm_year + 1900) && month == (now->tm_mon + 1) && day > now->tm_mday) {
        return false;
    }

    return true;
}

std::string Contact::getFirstName() const { return firstName; }
std::string Contact::getLastName() const { return lastName; }
std::string Contact::getMiddleName() const { return middleName; }
std::string Contact::getAddress() const { return address; }
std::string Contact::getBirthDate() const { return birthDate; }
std::string Contact::getEmail() const { return email; }
std::vector<std::string> Contact::getPhoneNumbers() const { return phoneNumbers; }

void Contact::setFirstName(const std::string& firstName) { this->firstName = firstName; }
void Contact::setLastName(const std::string& lastName) { this->lastName = lastName; }
void Contact::setMiddleName(const std::string& middleName) { this->middleName = middleName; }
void Contact::setAddress(const std::string& address) { this->address = address; }
void Contact::setBirthDate(const std::string& birthDate) { this->birthDate = birthDate; }
void Contact::setEmail(const std::string& email) { this->email = email; }
void Contact::setPhoneNumbers(const std::vector<std::string>& phoneNumbers) { this->phoneNumbers = phoneNumbers; }
