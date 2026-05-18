#ifndef IVEHICLE_H
#define IVEHICLE_H

#include <string>
using namespace std;

// ============================================================
// ABSTRACTION: IVehicle is an abstract base class (interface).
// It defines the contract that all vehicle types must follow.
// Pure virtual functions force derived classes to implement
// their own version of display() and getTitle().
// ============================================================
class IVehicle
{
public:
    // Pure virtual function — makes IVehicle abstract
    virtual void display() const = 0;

    // Pure virtual getters — must be implemented by derived classes
    virtual string getBrand() const = 0;
    virtual string getModel() const = 0;
    virtual int getID() const = 0;
    virtual double getPrice() const = 0;
    virtual bool getIsApproved() const = 0;
    virtual void setPrice(double p) = 0;
    virtual void setIsApproved(bool a) = 0;
    virtual string getTitle() const = 0;

    // Virtual destructor — required for safe polymorphic deletion
    virtual ~IVehicle() {}
};

#endif
