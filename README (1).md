# A2-25K-0013 — PakWheels Marketplace
**OOP Assignment 02 | Roll No: 25K-0013 | Section: BAI-2C**

---

## Overview

This project implements a **PakWheels-inspired car marketplace** in C++ demonstrating five core OOP concepts: Inheritance, Polymorphism, Abstraction, Operator Overloading, and Friend Functions. The system supports three user roles — Admin, Seller, and Buyer — interacting through a console menu.

---

## Repository Structure

```
A2-25K-0013/
├── main.cpp          # Full source code (all classes + main)
├── IUser.h           # Abstract interface for users
├── IVehicle.h        # Abstract interface for vehicles
├── IListing.h        # Abstract interface for listings
├── IMessenger.h      # Abstract interface for messaging
└── README.md         # This documentation file
```

---

## OOP Concepts Demonstrated

### 1. Inheritance

Eight inheritance relationships are used throughout the project:

| Derived Class  | Base Class(es)         | Purpose                          |
|----------------|------------------------|----------------------------------|
| `vehicle`      | `IVehicle`             | Base for all vehicle types       |
| `car`          | `vehicle`              | Car-specific attributes          |
| `bike`         | `vehicle`              | Bike-specific attributes         |
| `message`      | `IMessenger`           | Chat messages between users      |
| `User`         | `IUser`, `IMessenger`  | Base for all user roles          |
| `seller`       | `User`, `IListing`     | Seller with listing management   |
| `buyer`        | `User`                 | Buyer with search & favorites    |
| `adminPanel`   | `User`                 | Admin with approval controls     |

**Example — `car` inheriting from `vehicle`:**

```cpp
class car : public vehicle {
    string color, type;
    int    doors;
    bool   has_AC;
public:
    car(string b, string m, int y, double p, int mil,
        location loc, engine eng,
        string col, string body, int d, bool ac)
        : vehicle(b, m, y, p, mil, loc, eng) {
        color  = col;
        type   = body;
        doors  = d;
        has_AC = ac;
    }
    void display() const override { ... }
};
```

---

### 2. Polymorphism

Virtual functions allow runtime dispatch across all user and vehicle types.

| Virtual Function | Base Class   | Overridden In                        |
|------------------|--------------|--------------------------------------|
| `display()`      | `vehicle`    | `car`, `bike`                        |
| `displayInfo()`  | `User`       | `seller`, `buyer`, `adminPanel`      |
| `getRole()`      | `User`       | `seller`, `buyer`, `adminPanel`      |
| `login()`        | `IUser`      | `adminPanel`                         |

**Example — polymorphic dispatch via base pointer:**

```cpp
User *activeUser = &sellerObj;
activeUser->displayInfo("Seller Profile");
// Calls seller::displayInfo() at runtime, not User::displayInfo()
```

**Example — `car::display()` overriding `vehicle::display()`:**

```cpp
void display() const override {
    vehicle::display();   // calls base first
    cout << "Color: " << color << " | Type: " << type
         << " | Doors: " << doors
         << " | AC: " << (has_AC ? "Yes" : "No") << endl;
}
```

---

### 3. Abstraction

Four abstract interfaces (`pure virtual` classes) define contracts enforced in concrete classes:

| Interface     | Pure Virtual Methods                        | Implemented By          |
|---------------|---------------------------------------------|-------------------------|
| `IVehicle`    | `display()`, `getID()`, `getBrand()`, etc.  | `vehicle`               |
| `IUser`       | `displayInfo()`, `getRole()`, `login()`     | `User` and subclasses   |
| `IListing`    | `addListing()`, `removeListing()`, etc.     | `seller`                |
| `IMessenger`  | `sendMessage()`                             | `User`, `message`       |

**Example — `IListing` interface (IListing.h):**

```cpp
class IListing {
public:
    virtual void addListing(IVehicle *v)      = 0;
    virtual void removeListing(int vehicleID) = 0;
    virtual void showListings() const         = 0;
    virtual ~IListing() {}
};
```

---

### 4. Operator Overloading

Three operators are overloaded across `vehicle` and `message`:

| Operator | Class     | Purpose                                               |
|----------|-----------|-------------------------------------------------------|
| `+`      | `vehicle` | Bundle two vehicles into a combined deal listing      |
| `==`     | `vehicle` | Check if two vehicle listings represent the same car  |
| `<<`     | `message` | Stream output for clean `cout << msg` printing        |

**Example — `vehicle::operator+` (bundle deal):**

```cpp
vehicle vehicle::operator+(const vehicle &other) const {
    string combinedBrand = brand + " & " + other.brand;
    double combinedPrice = price + other.price;
    int    combinedYear  = (year < other.year) ? year : other.year;  // manual min
    vehicle bundle(combinedBrand, combinedModel, combinedYear,
                   combinedPrice, combinedMileage, l, e);
    bundle.setIsApproved(isApproved && other.isApproved);
    return bundle;
}
```

**Example — `operator<<` for message:**

```cpp
friend ostream &operator<<(ostream &out, const message &msg);

ostream &operator<<(ostream &out, const message &msg) {
    out << "Message[" << msg.msgID << "] "
        << msg.sender << " -> " << msg.receiver << ": " << msg.text;
    return out;
}
```

---

### 5. Friend Functions

Five friend functions are declared to allow controlled access to private members:

| Friend Function      | Class     | Private Member Accessed | Purpose                                 |
|----------------------|-----------|-------------------------|-----------------------------------------|
| `compareByPrice`     | `vehicle` | `price`                 | External price-based sorting/comparison |
| `compareMileage`     | `vehicle` | `mileage`               | External mileage-based comparison       |
| `operator<<`         | `message` | `msgID`, `sender`, etc. | Stream output for message objects       |
| `compareUserName`    | `User`    | `name`                  | Compare two users by name externally    |
| `compareBudget`      | `buyer`   | `budget`                | Sort/compare buyers by budget           |

**Example — `compareByPrice` accessing private `price`:**

```cpp
// Declared inside vehicle class:
friend bool compareByPrice(const vehicle &a, const vehicle &b);

// Definition:
bool compareByPrice(const vehicle &a, const vehicle &b) {
    return a.price < b.price;  // accesses private member directly
}
```

---

## Class Hierarchy

```
IVehicle (abstract)
  └── vehicle
        ├── car
        └── bike

IUser (abstract)
IMessenger (abstract)
  └── User
        ├── seller  [also implements IListing]
        ├── buyer
        └── adminPanel

IMessenger (abstract)
  └── message

marketplace  (aggregates vehicle*, seller*, buyer*)
```

---

## How to Compile & Run

```bash
g++ -o pakwheels main.cpp -std=c++11
./pakwheels
```

**Default Admin Credentials:**
- Admin ID: `25k-0013`
- Password: `Admin123`

---

## Sample Workflow

1. **Login as Admin** → approve listings
2. **Continue as Seller** → register, add car/bike listings
3. **Continue as Buyer** → search vehicles, save favorites, message seller

---

## Key Design Decisions

- **No `<algorithm>` header used** — `std::min`/`std::max` replaced with ternary operators in `operator+`.
- **Static arrays instead of vectors** — avoids STL containers per assignment constraints.
- **Global storage arrays** (`carStorage[]`, `bikeStorage[]`) — prevents dangling pointers when stack-allocated vehicles go out of scope inside menu functions.
- **`static` menu-local objects** — `sellerObj`, `buyerObj`, `admin` declared `static` inside menu functions to persist across menu loops.

---

*Submitted by: Roll No 25K-0013 | BAI-2C | FAST-NUCES Karachi*
