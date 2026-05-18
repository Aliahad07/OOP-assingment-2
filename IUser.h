#ifndef IUSER_H
#define IUSER_H

#include <string>
using namespace std;

// ============================================================
// ABSTRACTION: IUser is an abstract base class (interface).
// It defines common behavior all users must have:
// login, displayInfo, and getRole.
// Concrete classes (seller, buyer, adminPanel) implement these.
// ============================================================
class IUser
{
public:
    // Pure virtual — every user type must implement displayInfo
    virtual void displayInfo() const = 0;

    // Pure virtual — every user type must be able to display
    virtual void display() const = 0;

    // Pure virtual — returns role string ("Buyer", "Seller", "Admin")
    virtual string getRole() const = 0;

    // Pure virtual — login logic differs per user type
    virtual bool login(const string &id, const string &password) = 0;

    // Virtual destructor for safe polymorphic deletion
    virtual ~IUser() {}
};

#endif
