#ifndef ILISTING_H
#define ILISTING_H

#include "IVehicle.h"

// ============================================================
// ABSTRACTION: IListing is an abstract base class (interface).
// It defines the contract for any entity that can manage
// vehicle listings (e.g., a Seller).
// ============================================================
class IListing
{
public:
    // Pure virtual — add a vehicle to listings
    virtual void addListing(IVehicle *v) = 0;

    // Pure virtual — remove a listing by vehicle ID
    virtual void removeListing(int vehicleID) = 0;

    // Pure virtual — display all current listings
    virtual void showListings() const = 0;

    // Virtual destructor
    virtual ~IListing() {}
};

#endif
