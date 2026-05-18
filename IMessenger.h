#ifndef IMESSENGER_H
#define IMESSENGER_H

#include <string>
using namespace std;

// ============================================================
// ABSTRACTION: IMessenger is an abstract base class (interface).
// It defines the contract for any entity capable of sending
// messages. Both User and message classes implement this.
// ============================================================
class IMessenger
{
public:
    // Pure virtual — every messenger must implement sendMessage
    virtual void sendMessage(const string &receiver, const string &text) = 0;

    // Virtual destructor
    virtual ~IMessenger() {}
};

#endif
