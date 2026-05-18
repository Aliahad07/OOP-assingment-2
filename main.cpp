// ============================================================
// PakWheels Marketplace — OOP Assignment 02
// Roll No: 25K-0013 | Section: BAI-2C
//
// CONCEPTS DEMONSTRATED:
//   1. Inheritance       — User->Buyer, Seller, Admin; Vehicle->Car, Bike
//   2. Polymorphism      — virtual display(), displayInfo(), getRole()
//   3. Abstraction       — IVehicle, IUser, IListing, IMessenger (.h files)
//   4. Operator Overload — ==, +, << (vehicle, message); compareByPrice
//   5. Friend Functions  — compareByPrice, compareUserName,
//                          compareBudget, operator<<(message)
// ============================================================

#include <iostream>
#include <string>
#include "IUser.h"
#include "IVehicle.h"
#include "IListing.h"
#include "IMessenger.h"
using namespace std;

// ============================================================
// CLASS: location
// Simple value type — city, province, country
// ============================================================
class location
{
    string city, province, country;

public:
    location()
    {
        city     = "unknown";
        province = "unknown";
        country  = "Pakistan";
    }

    location(string c, string p, string cntry) : city(c), province(p), country(cntry) {}

    location(const location &l)
    {
        city     = l.city;
        province = l.province;
        country  = l.country;
    }

    void setcity(string c)        { city = c; }
    void setProvince(string p)    { province = p; }
    void setcountry(string cntry) { country = cntry; }

    string getcity() const     { return city; }
    string getprovince() const { return province; }
    string getcountry() const  { return country; }

    bool operator==(const location &other) const
    {
        return city == other.city && province == other.province && country == other.country;
    }

    void display() const
    {
        cout << "city: " << city << ", province: " << province << ", country: " << country << endl;
    }

    void updateCity(string newCity) { city = newCity; }
};

// ============================================================
// CLASS: engine
// Simple value type — engine specifications
// ============================================================
class engine
{
    int    cc;
    string fuelType;
    int    horsepower;
    string transmission;
    string driveType;

public:
    engine()
    {
        cc           = 800;
        fuelType     = "petrol";
        horsepower   = 120;
        transmission = "manual";
        driveType    = "All wheel";
    }

    engine(int c, string f, int hp, string t)
    {
        cc           = c;
        fuelType     = f;
        horsepower   = hp;
        transmission = t;
        driveType    = "2WD";
    }

    engine(const engine &e)
    {
        cc           = e.cc;
        fuelType     = e.fuelType;
        horsepower   = e.horsepower;
        transmission = e.transmission;
        driveType    = e.driveType;
    }

    void setCC(int c)              { cc = c; }
    void setFuelType(string f)     { fuelType = f; }
    void setHorsepower(int hp)     { horsepower = hp; }
    void setTransmission(string t) { transmission = t; }

    int    getCC() const           { return cc; }
    string getFuelType() const     { return fuelType; }
    int    getHorsepower() const   { return horsepower; }
    string getTransmission() const { return transmission; }

    bool operator==(const engine &other) const
    {
        return cc == other.cc && fuelType == other.fuelType &&
               horsepower == other.horsepower && transmission == other.transmission;
    }

    void display() const
    {
        cout << "Engine: " << cc << "cc | " << fuelType
             << " | " << horsepower << "hp | " << transmission << endl;
    }
};

// ============================================================
// CLASS: vehicle  (inherits IVehicle — INHERITANCE #1)
// Base class for all vehicle types.
// POLYMORPHISM: display() is virtual — overridden in car/bike.
// ============================================================
class vehicle : public IVehicle
{
protected:
    string brand, model;
    int    year, mileage, id;
    double price;
    bool   isApproved;

    location l;
    engine   e;

    static int totalVehicles;

public:
    static const int baseFee = 500;

    vehicle()
    {
        brand      = "unknown";
        model      = "unknown";
        year       = 2020;
        mileage    = 0;
        price      = 0;
        isApproved = false;
        id         = ++totalVehicles;
    }

    vehicle(string b, string m, int y, double p, int mil, location loc, engine eng)
    {
        id         = ++totalVehicles;
        brand      = b;
        model      = m;
        year       = y;
        price      = p;
        mileage    = mil;
        isApproved = false;
        l          = loc;
        e          = eng;
    }

    vehicle(vehicle &v)
    {
        id         = ++totalVehicles;
        brand      = v.brand;
        model      = v.model;
        year       = v.year;
        price      = v.price;
        mileage    = v.mileage;
        isApproved = v.isApproved;
        l          = v.l;
        e          = v.e;
    }

    void setBrand(string b)    { brand = b; }
    void setModel(string m)    { model = m; }
    void setYear(int y)        { year = y; }
    void setPrice(double p)    { price = p; }
    void setMileage(int m)     { mileage = m; }
    void setIsApproved(bool a) { isApproved = a; }

    int    getID() const            { return id; }
    string getBrand() const         { return brand; }
    string getModel() const         { return model; }
    int    getYear() const          { return year; }
    double getPrice() const         { return price; }
    int    getMileage() const       { return mileage; }
    bool   getIsApproved() const    { return isApproved; }
    location getLocation() const    { return l; }
    engine   getEngine() const      { return e; }

    // --------------------------------------------------------
    // OPERATOR OVERLOADING #1: + (combine two vehicles into bundle)
    // Reason: Allows creating a "bundle deal" listing from two vehicles.
    // Uses manual min/max instead of <algorithm>.
    // --------------------------------------------------------
    vehicle operator+(const vehicle &other) const;

    // --------------------------------------------------------
    // OPERATOR OVERLOADING #2: == (compare two vehicles)
    // Reason: Check if two listings represent the same vehicle.
    // --------------------------------------------------------
    bool operator==(const vehicle &other) const;

    // --------------------------------------------------------
    // FRIEND FUNCTION #1: compareByPrice
    // Reason: Needs access to private `price` member of vehicle.
    // Used for sorting/comparing vehicles by price externally.
    // --------------------------------------------------------
    friend bool compareByPrice(const vehicle &a, const vehicle &b);

    // --------------------------------------------------------
    // FRIEND FUNCTION #2: compareMileage
    // Reason: Needs access to private `mileage` member.
    // Allows external comparison without exposing internals.
    // --------------------------------------------------------
    friend bool compareMileage(const vehicle &a, const vehicle &b);

    // POLYMORPHISM: virtual display() — overridden in car and bike
    virtual void display() const override
    {
        cout << "-----------------------------" << endl;
        cout << "ID: " << id << " | " << year << " " << brand << " " << model << endl;
        cout << "Price: PKR " << price << " | Mileage: " << mileage << " km" << endl;
        cout << "Status: " << (isApproved ? "Approved" : "Pending Approval") << endl;
        l.display();
        e.display();
    }

    static int getTotalVehicles() { return totalVehicles; }

    bool matchSearch(const string &searchBrand, double minP, double maxP) const
    {
        bool demanded_model = (searchBrand == "" || brand == searchBrand);
        bool demand_price   = (price >= minP && price <= maxP);
        return demanded_model && demand_price;
    }

    string getTitle() const
    {
        return to_string(year) + " " + brand + " " + model;
    }
};

int vehicle::totalVehicles = 0;

// --------------------------------------------------------
// OPERATOR OVERLOADING #1 implementation: vehicle +
// Combines two vehicles into a bundle (no <algorithm> needed —
// manual ternary used instead of std::min / std::max).
// --------------------------------------------------------
vehicle vehicle::operator+(const vehicle &other) const
{
    string   combinedBrand    = brand + " & " + other.brand;
    string   combinedModel    = model + " / " + other.model;
    double   combinedPrice    = price + other.price;
    int      combinedYear     = (year < other.year)     ? year     : other.year;   // manual min
    int      combinedMileage  = (mileage > other.mileage) ? mileage : other.mileage; // manual max
    location combinedLocation = l;
    engine   combinedEngine   = e;

    vehicle bundle(combinedBrand, combinedModel, combinedYear,
                   combinedPrice, combinedMileage, combinedLocation, combinedEngine);
    bundle.setIsApproved(isApproved && other.isApproved);
    return bundle;
}

bool vehicle::operator==(const vehicle &other) const
{
    return brand   == other.brand   &&
           model   == other.model   &&
           year    == other.year    &&
           price   == other.price   &&
           mileage == other.mileage;
}

// FRIEND FUNCTION #1: compareByPrice — accesses private price
bool compareByPrice(const vehicle &a, const vehicle &b)
{
    return a.price < b.price;
}

// FRIEND FUNCTION #2: compareMileage — accesses private mileage
bool compareMileage(const vehicle &a, const vehicle &b)
{
    return a.mileage < b.mileage;
}

// ============================================================
// CLASS: car  (inherits vehicle — INHERITANCE #2)
// POLYMORPHISM: overrides display() to add car-specific info.
// ============================================================
class car : public vehicle
{
    string color, type;
    int    doors;
    bool   has_AC;

public:
    car()
    {
        color  = "white";
        type   = "sedan";
        doors  = 4;
        has_AC = false;
    }

    car(string b, string m, int y, double p, int mil,
        location loc, engine eng,
        string col, string body, int d, bool ac)
        : vehicle(b, m, y, p, mil, loc, eng)
    {
        color  = col;
        type   = body;
        doors  = d;
        has_AC = ac;
    }

    void setColor(string c) { color = c; }
    void settype(string b)  { type = b; }
    void setDoors(int d)    { doors = d; }
    void set_HasAC(bool a)  { has_AC = a; }

    string getColor() const { return color; }
    string gettype() const  { return type; }
    int    getDoors() const { return doors; }
    bool   getHasAC() const { return has_AC; }

    // POLYMORPHISM: overrides vehicle::display()
    void display() const override
    {
        vehicle::display();
        cout << "Color: " << color << " | Type: " << type
             << " | Doors: " << doors
             << " | AC: " << (has_AC ? "Yes" : "No") << endl;
    }

    bool isFamilyCar()
    {
        return doors == 4 && has_AC;
    }

    void showCarInfo()
    {
        cout << "Car: " << brand << " " << model
             << " | " << color << " | " << type << endl;
    }

    void applyDiscount(double percent)
    {
        price = price - (price * percent / 100);
        cout << "Discount applied! New price: PKR " << price << endl;
    }
};

// ============================================================
// CLASS: bike  (inherits vehicle — INHERITANCE #3)
// POLYMORPHISM: overrides display() to add bike-specific info.
// ============================================================
class bike : public vehicle
{
    string bType;
    string en_type;
    int    cc;

public:
    bike()
    {
        bType   = "Normal";
        en_type = "petrol";
        cc      = 70;
    }

    bike(string b, string m, int y, double p, int mil,
         location loc, engine eng,
         string bT, string eT, int CC)
        : vehicle(b, m, y, p, mil, loc, eng)
    {
        bType   = bT;
        en_type = eT;
        cc      = CC;
    }

    void setBikeType(string t)   { bType = t; }
    void setEngineType(string e) { en_type = e; }
    void setcc(int c)            { cc = c; }

    string getBikeType() const   { return bType; }
    string getEngineType() const { return en_type; }
    int    getCC() const         { return cc; }

    // POLYMORPHISM: overrides vehicle::display()
    void display() const override
    {
        vehicle::display();
        cout << "Bike Type: " << bType << " | Engine Type: " << en_type
             << " | CC: " << cc << endl;
    }

    void isSports() { bType = "sports bike"; }

    void BikeInfo()
    {
        cout << "Brand: "       << brand   << endl;
        cout << "model: "       << model   << endl;
        cout << "type: "        << bType   << endl;
        cout << "CC : "         << cc      << endl;
        cout << "engine type: " << en_type << endl;
    }

    string category()
    {
        if (cc > 200)
            return "premium bike";
        else
            return "economy bike";
    }
};

// ============================================================
// CLASS: message  (inherits IMessenger — INHERITANCE #4)
// Represents a chat message between users.
// ============================================================
class message : public IMessenger
{
    int    msgID;
    string sender;
    string receiver;
    string text;
    bool   isRead;

    static int totalMessages;

public:
    message()
    {
        msgID    = ++totalMessages;
        sender   = "";
        receiver = "";
        text     = "";
        isRead   = false;
    }

    message(string s, string r, string t)
    {
        msgID    = ++totalMessages;
        sender   = s;
        receiver = r;
        text     = t;
        isRead   = false;
    }

    void setSender(string s)   { sender = s; }
    void setReceiver(string r) { receiver = r; }
    void setText(string t)     { text = t; }
    void setIsRead(bool r)     { isRead = r; }

    int    getMsgID() const    { return msgID; }
    string getSender() const   { return sender; }
    string getReceiver() const { return receiver; }
    string getText() const     { return text; }
    bool   getIsRead() const   { return isRead; }

    void display() const
    {
        cout << "[Message #" << msgID << "]" << endl;
        cout << "From: " << sender << " --> To: " << receiver << endl;
        cout << "Text: " << text << endl;
        cout << "Status: " << (isRead ? "Read" : "Unread") << endl;
    }

    void markRead()
    {
        isRead = true;
        cout << "Message marked as read." << endl;
    }

    bool isFromSender(string name) const { return sender == name; }

    void showPreview() const
    {
        cout << "MSG from " << sender << ": " << text.substr(0, 20) << "..." << endl;
    }

    // IMessenger implementation
    void sendMessage(const string &receiverName, const string &messageText) override
    {
        receiver = receiverName;
        text     = messageText;
        sender   = "System";
        isRead   = false;
    }

    // --------------------------------------------------------
    // OPERATOR OVERLOADING #3: + (combine two messages)
    // Reason: Merge two messages into a single chained message,
    // useful for bundled notifications.
    // --------------------------------------------------------
    message operator+(const message &other) const
    {
        return message(sender, other.receiver, text + " | " + other.text);
    }

    // --------------------------------------------------------
    // FRIEND FUNCTION #3: operator<< for message
    // Reason: Needs access to private msgID, sender, receiver, text.
    // Enables clean stream output: cout << msg;
    // --------------------------------------------------------
    friend ostream &operator<<(ostream &out, const message &msg);

    static int getTotalMessages() { return totalMessages; }
};

int message::totalMessages = 0;

// FRIEND FUNCTION #3 implementation: stream output for message
ostream &operator<<(ostream &out, const message &msg)
{
    out << "Message[" << msg.msgID << "] "
        << msg.sender << " -> " << msg.receiver << ": " << msg.text;
    return out;
}

// ============================================================
// CLASS: User  (inherits IUser and IMessenger — INHERITANCE #5)
// Base class for all user roles. Pure virtuals from IUser are
// implemented here and can be overridden in derived classes.
// ============================================================
class User : public IUser, public IMessenger
{
protected:
    int    userID;
    string name;
    string phone;
    string role;

public:
    User() : userID(0), name("Unknown"), phone("N/A"), role("Guest") {}
    User(int id, string n, string p, string r) : userID(id), name(n), phone(p), role(r) {}

    void setUserID(int id) { userID = id; }
    void setName(string n) { name = n; }
    void setPhone(string p) { phone = p; }
    void setRole(string r)  { role = r; }

    int    getUserID() const { return userID; }
    string getName()   const { return name; }
    string getPhone()  const { return phone; }

    // POLYMORPHISM: virtual — overridden in seller, buyer, adminPanel
    virtual void displayInfo() const override
    {
        cout << "User [" << userID << "] " << name << " (" << role << ")" << endl;
        cout << "Contact: " << phone << endl;
    }

    void display() const override { displayInfo(); }

    // Function overloading — displayInfo with a label parameter
    void displayInfo(const string &label) const
    {
        cout << "--- " << label << " ---" << endl;
        displayInfo();
    }

    // POLYMORPHISM: virtual — overridden in each derived class
    virtual string getRole() const override { return role; }

    bool login(const string &id, const string &password) override { return false; }

    void sendMessage(const string &receiver, const string &text) override
    {
        message msg(name, receiver, text);
        msg.display();
    }

    // --------------------------------------------------------
    // FRIEND FUNCTION #4: compareUserName
    // Reason: Accesses private `name` field of User directly.
    // Allows external code to compare users without a getter call.
    // --------------------------------------------------------
    friend bool compareUserName(const User &a, const User &b);
};

// FRIEND FUNCTION #4 implementation
bool compareUserName(const User &a, const User &b)
{
    return a.name == b.name;
}

// ============================================================
// CLASS: seller  (inherits User and IListing — INHERITANCE #6)
// POLYMORPHISM: overrides displayInfo(), getRole()
// ============================================================
class seller : public User, public IListing
{
    string   email;
    bool     isVerified;
    vehicle *myListings[20];
    int      listingCount;

public:
    seller() : User(0, "Unknown Seller", "N/A", "Seller"), email(""), isVerified(false), listingCount(0)
    {
        for (int i = 0; i < 20; i++) myListings[i] = NULL;
    }

    seller(int id, string n, string p, string e, bool v)
        : User(id, n, p, "Seller"), email(e), isVerified(v), listingCount(0)
    {
        for (int i = 0; i < 20; i++) myListings[i] = NULL;
    }

    void setEmail(string e)     { email = e; }
    void setIsVerified(bool v)  { isVerified = v; }

    int    getSellerID() const    { return getUserID(); }
    string getEmail() const       { return email; }
    bool   getIsVerified() const  { return isVerified; }
    int    getListingCount() const { return listingCount; }

    // POLYMORPHISM: overrides User::displayInfo()
    void displayInfo() const override
    {
        User::displayInfo();
        cout << "Email: " << email << " | Verified: " << (isVerified ? "Yes" : "No") << endl;
    }

    string getRole() const override { return "Seller"; }

    // IListing implementation
    void addListing(IVehicle *v) override
    {
        if (listingCount < 20)
        {
            myListings[listingCount] = static_cast<vehicle *>(v);
            listingCount++;
            cout << "Listing added: "
                 << myListings[listingCount - 1]->getBrand() << " "
                 << myListings[listingCount - 1]->getModel() << endl;
        }
        else
        {
            cout << "Cannot add more listings." << endl;
        }
    }

    void removeListing(int vehicleID) override
    {
        for (int i = 0; i < listingCount; i++)
        {
            if (myListings[i] != NULL && myListings[i]->getID() == vehicleID)
            {
                cout << "Removed listing: "
                     << myListings[i]->getBrand() << " "
                     << myListings[i]->getModel() << endl;
                for (int j = i; j < listingCount - 1; j++)
                    myListings[j] = myListings[j + 1];
                listingCount--;
                return;
            }
        }
        cout << "Listing not found." << endl;
    }

    void updatePrice(int vehicleID, double newPrice)
    {
        for (int i = 0; i < listingCount; i++)
        {
            if (myListings[i] != NULL && myListings[i]->getID() == vehicleID)
            {
                myListings[i]->setPrice(newPrice);
                cout << "Price updated to: PKR " << newPrice << endl;
                return;
            }
        }
        cout << "Vehicle not found." << endl;
    }

    void showListings() const override { showMyListings(); }

    void showMyListings() const
    {
        cout << "\n--- Your Listings ---" << endl;
        if (listingCount == 0)
        {
            cout << "No listings yet." << endl;
            return;
        }
        for (int i = 0; i < listingCount; i++)
        {
            if (myListings[i] != NULL)
                myListings[i]->display();
        }
    }

    void sendMessage(const string &receiverName, const string &text) override
    {
        message msg(getName(), receiverName, text);
        msg.display();
    }
};

// ============================================================
// CLASS: buyer  (inherits User — INHERITANCE #7)
// POLYMORPHISM: overrides displayInfo(), getRole()
// ============================================================
class buyer : public User
{
    double   budget;
    string   city;
    vehicle *favorites[10];
    int      favCount;

public:
    buyer() : User(0, "Unknown Buyer", "N/A", "Buyer"), budget(0), city(""), favCount(0)
    {
        for (int i = 0; i < 10; i++) favorites[i] = NULL;
    }

    buyer(int id, string n, string p, double b, string c)
        : User(id, n, p, "Buyer"), budget(b), city(c), favCount(0)
    {
        for (int i = 0; i < 10; i++) favorites[i] = NULL;
    }

    void setBudget(double b) { budget = b; }
    void setCity(string c)   { city = c; }

    double getBudget() const { return budget; }
    string getCity()   const { return city; }

    // POLYMORPHISM: overrides User::displayInfo()
    void displayInfo() const override
    {
        User::displayInfo();
        cout << "Budget: PKR " << budget << " | City: " << city << endl;
    }

    string getRole() const override { return "Buyer"; }

    void saveFavorite(vehicle *v)
    {
        if (favCount >= 10)
        {
            cout << "Favorites list is full." << endl;
            return;
        }
        favorites[favCount] = v;
        favCount++;
        cout << "Saved to favorites: " << v->getBrand() << " " << v->getModel() << endl;
    }

    void removeFavorite(int vehicleID)
    {
        for (int i = 0; i < favCount; i++)
        {
            if (favorites[i] != NULL && favorites[i]->getID() == vehicleID)
            {
                cout << "Removed from favorites: "
                     << favorites[i]->getBrand() << " "
                     << favorites[i]->getModel() << endl;
                for (int j = i; j < favCount - 1; j++)
                    favorites[j] = favorites[j + 1];
                favCount--;
                return;
            }
        }
        cout << "Not found in favorites." << endl;
    }

    void showFavorites() const
    {
        cout << "\n--- Your Favorites ---" << endl;
        if (favCount == 0)
        {
            cout << "No favorites saved." << endl;
            return;
        }
        for (int i = 0; i < favCount; i++)
        {
            if (favorites[i] != NULL)
                favorites[i]->display();
        }
    }

    void sendMessage(const string &sellerName, const string &msgText) override
    {
        message msg(getName(), sellerName, msgText);
        cout << "Message sent:" << endl;
        msg.display();
    }

    void searchVehicles(vehicle *allVehicles[], int count, string brand, double minP, double maxP)
    {
        cout << "\n--- Search Results ---" << endl;
        bool found = false;
        for (int i = 0; i < count; i++)
        {
            if (allVehicles[i] != NULL &&
                allVehicles[i]->getIsApproved() &&
                allVehicles[i]->matchSearch(brand, minP, maxP))
            {
                allVehicles[i]->display();
                found = true;
            }
        }
        if (!found) cout << "No vehicles found." << endl;
    }

    bool canAfford(vehicle *v) const { return v->getPrice() <= budget; }

    // --------------------------------------------------------
    // FRIEND FUNCTION (bonus): compareBudget
    // Reason: Accesses private `budget` field directly.
    // Useful for sorting buyers or checking budget eligibility
    // without making budget publicly accessible everywhere.
    // --------------------------------------------------------
    friend bool compareBudget(const buyer &a, const buyer &b);
};

// compareBudget friend function definition
bool compareBudget(const buyer &a, const buyer &b)
{
    return a.budget < b.budget;
}

// ============================================================
// CLASS: adminPanel  (inherits User — INHERITANCE #8)
// POLYMORPHISM: overrides displayInfo(), getRole(), login()
// ============================================================
class adminPanel : public User
{
    string       password;
    string       Admin_id;
    const int    adminLevel;
    int          totalApproved;
    int          totalRemoved;

public:
    adminPanel()
        : User(0, "Admin", "000", "Admin"),
          password("Admin123"), Admin_id("25k-0013"),
          adminLevel(1), totalApproved(0), totalRemoved(0) {}

    adminPanel(string pass, string a_id, int level)
        : User(0, "Admin", "000", "Admin"),
          password("Admin123"), Admin_id("25k-0013"),
          adminLevel(level), totalApproved(0), totalRemoved(0)
    {
        if (pass != password || a_id != Admin_id)
            cout << "ID and Password not matched! Access denied." << endl;
        else
            cout << "Admin access granted. Welcome!" << endl;
    }

    bool checkLogin(string pass, string a_id)
    {
        return (pass == password && a_id == Admin_id);
    }

    // POLYMORPHISM: overrides IUser::login()
    bool login(const string &id, const string &passwordAttempt) override
    {
        return (id == Admin_id && passwordAttempt == password);
    }

    // POLYMORPHISM: overrides User::displayInfo()
    void displayInfo() const override
    {
        User::displayInfo();
        cout << "Admin ID: " << Admin_id << " | Level: " << adminLevel << endl;
    }

    string getRole() const override { return "Admin"; }

    void setPassword(string p) { password = p; }
    void setAdminID(string id) { Admin_id = id; }

    string getAdminID() const    { return Admin_id; }
    int    getAdminLevel() const { return adminLevel; }
    int    getTotalApproved() const { return totalApproved; }
    int    getTotalRemoved() const  { return totalRemoved; }

    void approveListing(vehicle *v)
    {
        v->setIsApproved(true);
        totalApproved++;
        cout << "[Admin] Approved: " << v->getBrand() << " " << v->getModel() << endl;
    }

    void removeListing(vehicle *v)
    {
        v->setIsApproved(false);
        totalRemoved++;
        cout << "[Admin] Removed: " << v->getBrand() << " " << v->getModel() << endl;
    }

    void approveAll(vehicle *allVehicles[], int count)
    {
        cout << "\n[Admin] Approving all pending listings..." << endl;
        bool any = false;
        for (int i = 0; i < count; i++)
        {
            if (allVehicles[i] != NULL && !allVehicles[i]->getIsApproved())
            {
                approveListing(allVehicles[i]);
                any = true;
            }
        }
        if (!any) cout << "No pending listings." << endl;
    }

    void showStats() const
    {
        cout << "\n--- Admin Stats ---" << endl;
        cout << "Admin ID: " << Admin_id << " | Level: " << adminLevel << endl;
        cout << "Total Approved: " << totalApproved << endl;
        cout << "Total Removed: "  << totalRemoved  << endl;
    }

    bool hasAuthority(const adminPanel &other) const
    {
        return adminLevel > other.adminLevel;
    }
};

// ============================================================
// CLASS: marketplace
// Holds all vehicles, sellers, and buyers.
// ============================================================
class marketplace
{
    string name;
    string website;
    int    startYear;

    vehicle *allVehicles[100];
    seller  *allSellers[50];
    buyer   *allBuyers[50];

    int vehicleCount;
    int sellerCount;
    int buyerCount;

public:
    marketplace()
    {
        name         = "PakWheels";
        website      = "www.pakwheels.com";
        startYear    = 2003;
        vehicleCount = 0;
        sellerCount  = 0;
        buyerCount   = 0;
        for (int i = 0; i < 100; i++) allVehicles[i] = NULL;
        for (int i = 0; i < 50;  i++) { allSellers[i] = NULL; allBuyers[i] = NULL; }
    }

    marketplace(string n, string web, int year)
    {
        name         = n;
        website      = web;
        startYear    = year;
        vehicleCount = 0;
        sellerCount  = 0;
        buyerCount   = 0;
        for (int i = 0; i < 100; i++) allVehicles[i] = NULL;
        for (int i = 0; i < 50;  i++) { allSellers[i] = NULL; allBuyers[i] = NULL; }
    }

    void setName(string n)    { name = n; }
    void setWebsite(string w) { website = w; }

    string getName()      { return name; }
    string getWebsite()   { return website; }
    int    getStartYear() { return startYear; }
    int    getVehicleCount() { return vehicleCount; }
    int    getSellerCount()  { return sellerCount; }
    int    getBuyerCount()   { return buyerCount; }

    vehicle **getVehicles() { return allVehicles; }

    void addVehicle(vehicle *v)
    {
        if (vehicleCount < 100)
        {
            allVehicles[vehicleCount] = v;
            vehicleCount++;
        }
    }

    void addSeller(seller *s)
    {
        if (sellerCount < 50)
        {
            allSellers[sellerCount] = s;
            sellerCount++;
        }
    }

    void addBuyer(buyer *b)
    {
        if (buyerCount < 50)
        {
            allBuyers[buyerCount] = b;
            buyerCount++;
        }
    }

    seller *getSeller(int index)
    {
        if (index >= 0 && index < sellerCount) return allSellers[index];
        return NULL;
    }

    buyer *getBuyer(int index)
    {
        if (index >= 0 && index < buyerCount) return allBuyers[index];
        return NULL;
    }

    void showAllApproved()
    {
        cout << "\n=============================" << endl;
        cout << "  " << name << " - Active Listings" << endl;
        cout << "=============================" << endl;
        bool found = false;
        for (int i = 0; i < vehicleCount; i++)
        {
            if (allVehicles[i] != NULL && allVehicles[i]->getIsApproved())
            {
                allVehicles[i]->display();   // POLYMORPHISM: car/bike display
                found = true;
            }
        }
        if (!found) cout << "No approved listings." << endl;
    }

    void showAllListings()
    {
        cout << "\n=============================" << endl;
        cout << "  All Listings (Admin View)" << endl;
        cout << "=============================" << endl;
        if (vehicleCount == 0)
        {
            cout << "No listings." << endl;
            return;
        }
        for (int i = 0; i < vehicleCount; i++)
        {
            if (allVehicles[i] != NULL)
                allVehicles[i]->display();   // POLYMORPHISM: car/bike display
        }
    }

    void showSummary()
    {
        cout << "\n=============================" << endl;
        cout << "  " << name << " Summary" << endl;
        cout << "=============================" << endl;
        cout << "Website   : " << website      << endl;
        cout << "Started   : " << startYear    << endl;
        cout << "Listings  : " << vehicleCount << endl;
        cout << "Sellers   : " << sellerCount  << endl;
        cout << "Buyers    : " << buyerCount   << endl;
        cout << "Total Vehicles Ever: " << vehicle::getTotalVehicles()  << endl;
        cout << "Total Messages Sent: " << message::getTotalMessages()  << endl;
    }
};

// ============================================================
// Global storage arrays (no dynamic allocation needed)
// ============================================================
static car  carStorage[100];
static bike bikeStorage[100];
static int  carCount  = 0;
static int  bikeCount = 0;

// ============================================================
// INPUT HELPERS
// ============================================================
vehicle *addCarFromInput(marketplace &market, seller *s)
{
    string b, m, col, body, fuel, trans, city, province;
    int    y, mil, doors, cc, hp, acChoice;
    double p;

    cout << "Enter brand: ";           cin >> b;
    cout << "Enter model: ";           cin >> m;
    cout << "Enter year: ";            cin >> y;
    cout << "Enter price (PKR): ";     cin >> p;
    cout << "Enter mileage (km): ";    cin >> mil;
    cout << "Enter city: ";            cin >> city;
    cout << "Enter province: ";        cin >> province;
    cout << "Enter engine CC: ";       cin >> cc;
    cout << "Enter fuel type (Petrol/Diesel): "; cin >> fuel;
    cout << "Enter horsepower: ";      cin >> hp;
    cout << "Enter transmission (Manual/Automatic): "; cin >> trans;
    cout << "Enter color: ";           cin >> col;
    cout << "Enter body type (Sedan/SUV/Hatchback): "; cin >> body;
    cout << "Enter number of doors: "; cin >> doors;
    cout << "Has AC? (1=Yes / 0=No): "; cin >> acChoice;

    location loc(city, province, "Pakistan");
    engine   eng(cc, fuel, hp, trans);

    carStorage[carCount] = car(b, m, y, p, mil, loc, eng, col, body, doors, acChoice == 1);
    vehicle *vPtr = &carStorage[carCount];
    carCount++;

    market.addVehicle(vPtr);
    if (s != NULL) s->addListing(vPtr);

    cout << "Car listing added successfully!" << endl;
    return vPtr;
}

vehicle *addBikeFromInput(marketplace &market, seller *s)
{
    string b, m, bT, eT, fuel, trans, city, province;
    int    y, mil, cc, hp, bikeCC;
    double p;

    cout << "Enter brand: ";           cin >> b;
    cout << "Enter model: ";           cin >> m;
    cout << "Enter year: ";            cin >> y;
    cout << "Enter price (PKR): ";     cin >> p;
    cout << "Enter mileage (km): ";    cin >> mil;
    cout << "Enter city: ";            cin >> city;
    cout << "Enter province: ";        cin >> province;
    cout << "Enter engine CC: ";       cin >> cc;
    cout << "Enter fuel type (Petrol/Diesel): "; cin >> fuel;
    cout << "Enter horsepower: ";      cin >> hp;
    cout << "Enter transmission (Manual/Automatic): "; cin >> trans;
    cout << "Enter bike type (Sports/Commuter/Normal): "; cin >> bT;
    cout << "Enter engine type (Petrol/Electric): ";       cin >> eT;
    cout << "Enter bike CC: ";         cin >> bikeCC;

    location loc(city, province, "Pakistan");
    engine   eng(cc, fuel, hp, trans);

    bikeStorage[bikeCount] = bike(b, m, y, p, mil, loc, eng, bT, eT, bikeCC);
    vehicle *vPtr = &bikeStorage[bikeCount];
    bikeCount++;

    market.addVehicle(vPtr);
    if (s != NULL) s->addListing(vPtr);

    cout << "Bike listing added successfully!" << endl;
    return vPtr;
}

// ============================================================
// MENU FUNCTIONS
// ============================================================
void sellerMenu(marketplace &market)
{
    string name, phone, email;

    cout << "\n--- Seller Registration ---" << endl;
    cout << "Enter your name: ";  cin >> name;
    cout << "Enter phone: ";      cin >> phone;
    cout << "Enter email: ";      cin >> email;

    static seller sellerObj;
    sellerObj = seller(market.getSellerCount() + 1, name, phone, email, false);
    market.addSeller(&sellerObj);

    // POLYMORPHISM: IUser pointer calls virtual displayInfo
    User *activeUser = &sellerObj;
    activeUser->displayInfo("Seller Profile");

    int choice;
    do
    {
        cout << "\n=============================" << endl;
        cout << "   Seller Menu - " << name      << endl;
        cout << "=============================" << endl;
        cout << "1. Add Car Listing"             << endl;
        cout << "2. Add Bike Listing"            << endl;
        cout << "3. Remove a Listing"            << endl;
        cout << "4. Update Listing Price"        << endl;
        cout << "5. View My Listings"            << endl;
        cout << "6. Send Message to Buyer"       << endl;
        cout << "7. Exit"                        << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
            addCarFromInput(market, &sellerObj);
        else if (choice == 2)
            addBikeFromInput(market, &sellerObj);
        else if (choice == 3)
        {
            sellerObj.showMyListings();
            int vid;
            cout << "Enter Vehicle ID to remove: "; cin >> vid;
            sellerObj.removeListing(vid);
        }
        else if (choice == 4)
        {
            sellerObj.showMyListings();
            int vid; double newPrice;
            cout << "Enter Vehicle ID to update price: "; cin >> vid;
            cout << "Enter new price (PKR): ";             cin >> newPrice;
            sellerObj.updatePrice(vid, newPrice);
        }
        else if (choice == 5)
            sellerObj.showMyListings();
        else if (choice == 6)
        {
            string receiverName, msgText;
            cout << "Enter buyer name: "; cin >> receiverName;
            cin.ignore();
            cout << "Enter message: ";   getline(cin, msgText);
            sellerObj.sendMessage(receiverName, msgText);
        }
        else if (choice == 7)
            cout << "Logging out..." << endl;
        else
            cout << "Invalid choice." << endl;

    } while (choice != 7);
}

void buyerMenu(marketplace &market)
{
    string name, phone, city;
    double budget;

    cout << "\n--- Buyer Registration ---"      << endl;
    cout << "Enter your name: ";               cin >> name;
    cout << "Enter phone: ";                   cin >> phone;
    cout << "Enter your city: ";               cin >> city;
    cout << "Enter your budget (PKR): ";       cin >> budget;

    static buyer buyerObj;
    buyerObj = buyer(market.getBuyerCount() + 1, name, phone, budget, city);
    market.addBuyer(&buyerObj);

    // POLYMORPHISM: IUser pointer calls virtual displayInfo
    User *activeUser = &buyerObj;
    activeUser->displayInfo("Buyer Profile");

    int choice;
    do
    {
        cout << "\n=============================" << endl;
        cout << "   Buyer Menu - " << name       << endl;
        cout << "=============================" << endl;
        cout << "1. View All Listings"            << endl;
        cout << "2. Search Vehicles"              << endl;
        cout << "3. Save to Favorites"            << endl;
        cout << "4. Remove from Favorites"        << endl;
        cout << "5. View Favorites"               << endl;
        cout << "6. Send Message to Seller"       << endl;
        cout << "7. Exit"                         << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
            market.showAllApproved();
        else if (choice == 2)
        {
            string brand; double minP, maxP;
            cout << "Enter brand to search (or 'all' for any): "; cin >> brand;
            if (brand == "all") brand = "";
            cout << "Enter minimum price: "; cin >> minP;
            cout << "Enter maximum price: "; cin >> maxP;
            buyerObj.searchVehicles(market.getVehicles(), market.getVehicleCount(), brand, minP, maxP);
        }
        else if (choice == 3)
        {
            market.showAllApproved();
            int vid;
            cout << "Enter Vehicle ID to save to favorites: "; cin >> vid;
            vehicle **all = market.getVehicles();
            bool found = false;
            for (int i = 0; i < market.getVehicleCount(); i++)
            {
                if (all[i] != NULL && all[i]->getID() == vid)
                {
                    buyerObj.saveFavorite(all[i]);
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Vehicle ID not found." << endl;
        }
        else if (choice == 4)
        {
            buyerObj.showFavorites();
            int vid;
            cout << "Enter Vehicle ID to remove from favorites: "; cin >> vid;
            buyerObj.removeFavorite(vid);
        }
        else if (choice == 5)
            buyerObj.showFavorites();
        else if (choice == 6)
        {
            string sellerName, msgText;
            cout << "Enter seller name: "; cin >> sellerName;
            cin.ignore();
            cout << "Enter your message: "; getline(cin, msgText);
            buyerObj.sendMessage(sellerName, msgText);
        }
        else if (choice == 7)
            cout << "Logging out..." << endl;
        else
            cout << "Invalid choice." << endl;

    } while (choice != 7);
}

void adminMenu(marketplace &market)
{
    string pass, aid;
    cout << "\n--- Admin Login ---" << endl;
    cout << "Enter Admin ID: ";   cin >> aid;
    cout << "Enter Password: ";   cin >> pass;

    static adminPanel admin(pass, aid, 2);

    if (!admin.checkLogin(pass, aid))
    {
        cout << "access denied to main menu!" << endl;
        return;
    }

    // POLYMORPHISM: IUser pointer calls virtual displayInfo
    User *activeUser = &admin;
    activeUser->displayInfo("Admin Profile");

    int choice;
    do
    {
        cout << "\n=============================" << endl;
        cout << "   Admin Menu"                  << endl;
        cout << "=============================" << endl;
        cout << "1. View All Listings"            << endl;
        cout << "2. Approve a Listing"            << endl;
        cout << "3. Remove a Listing"             << endl;
        cout << "4. Approve All Pending"          << endl;
        cout << "5. View Stats"                   << endl;
        cout << "6. View Marketplace Summary"     << endl;
        cout << "7. Exit"                         << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
            market.showAllListings();
        else if (choice == 2)
        {
            market.showAllListings();
            int vid;
            cout << "Enter Vehicle ID to approve: "; cin >> vid;
            vehicle **all = market.getVehicles();
            bool found = false;
            for (int i = 0; i < market.getVehicleCount(); i++)
            {
                if (all[i] != NULL && all[i]->getID() == vid)
                {
                    admin.approveListing(all[i]);
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Vehicle ID not found." << endl;
        }
        else if (choice == 3)
        {
            market.showAllListings();
            int vid;
            cout << "Enter Vehicle ID to remove: "; cin >> vid;
            vehicle **all = market.getVehicles();
            bool found = false;
            for (int i = 0; i < market.getVehicleCount(); i++)
            {
                if (all[i] != NULL && all[i]->getID() == vid)
                {
                    admin.removeListing(all[i]);
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Vehicle ID not found." << endl;
        }
        else if (choice == 4)
            admin.approveAll(market.getVehicles(), market.getVehicleCount());
        else if (choice == 5)
            admin.showStats();
        else if (choice == 6)
            market.showSummary();
        else if (choice == 7)
            cout << "Logging out..." << endl;
        else
            cout << "Invalid choice." << endl;

    } while (choice != 7);
}

// ============================================================
// MAIN
// ============================================================
int main()
{
    marketplace market("PakWheels", "www.pakwheels.com", 2003);

    int roleChoice;
    do
    {
        cout << "\n=============================" << endl;
        cout << "   Welcome to PakWheels"        << endl;
        cout << "=============================" << endl;
        cout << "1. Login as Admin"               << endl;
        cout << "2. Continue as Seller"           << endl;
        cout << "3. Continue as Buyer"            << endl;
        cout << "4. Exit"                         << endl;
        cout << "Enter your role: ";
        cin >> roleChoice;

        if (roleChoice == 1)
            adminMenu(market);
        else if (roleChoice == 2)
            sellerMenu(market);
        else if (roleChoice == 3)
            buyerMenu(market);
        else if (roleChoice == 4)
            cout << "Thank you for using PakWheels. Goodbye!" << endl;
        else
            cout << "Invalid choice. Try again." << endl;

    } while (roleChoice != 4);

    return 0;
}
