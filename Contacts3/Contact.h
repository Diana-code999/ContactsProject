#ifndef CONTACT_H
#define CONTACT_H

#include <string>
#include <vector>
#include <iostream>
class Contact {
public:
    Contact() = default;
    Contact(const std::string& firstName, const std::string& lastName, const std::string& middleName,
            const std::string& address, const std::string& birthDate, const std::string& email,
            const std::vector<std::string>& phoneNumbers);

    Contact(const Contact& other);
    Contact(Contact&& other) noexcept;
    Contact& operator=(const Contact& other);
    Contact& operator=(Contact&& other) noexcept;
    ~Contact() = default;

    void* operator new(size_t size);
    void operator delete(void* ptr);

    bool validate() const;
    bool isValidDate();
    bool isLeapYear(int year);

    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getMiddleName() const;
    std::string getAddress() const;
    std::string getBirthDate() const;
    std::string getEmail() const;
    std::vector<std::string> getPhoneNumbers() const;

    void setFirstName(const std::string& firstName);
    void setLastName(const std::string& lastName);
    void setMiddleName(const std::string& middleName);
    void setAddress(const std::string& address);
    void setBirthDate(const std::string& birthDate);
    void setEmail(const std::string& email);
    void setPhoneNumbers(const std::vector<std::string>& phoneNumbers);

private:
    std::string firstName;
    std::string lastName;
    std::string middleName;
    std::string address;
    std::string birthDate;
    std::string email;
    std::vector<std::string> phoneNumbers;
};

#endif // CONTACT_H
