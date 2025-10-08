#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <string>
using namespace std;

class Vehicle
{
private:
    string brand;
    string model;
    int year;

public:
    Vehicle() : brand("Unknown"), model("Unknown"), year(0) {}
    Vehicle(string b, string m, int y) : brand(b), model(m), year(y) {}

    string getBrand() const { return brand; }
    string getModel() const { return model; }
    int getYear() const { return year; }

    void setBrand(const string &b) { brand = b; }
    void setModel(const string &m) { model = m; }
    void setYear(int y) { year = y; }

    friend istream &operator>>(istream &in, Vehicle &v)
    {
        cout << "Enter brand: ";
        in >> v.brand;
        cout << "Enter model: ";
        in >> v.model;
        cout << "Enter year: ";
        in >> v.year;
        return in;
    }

    friend ostream &operator<<(ostream &out, const Vehicle &v)
    {
        out << v.brand << " " << v.model << " (" << v.year << ")";
        return out;
    }

    bool operator<(const Vehicle &other) const
    {
        if (brand != other.brand)
            return brand < other.brand;
        if (model != other.model)
            return model < other.model;
        return year < other.year;
    }

    bool operator>(const Vehicle &other) const
    {
        return other < *this;
    }

    bool operator==(const Vehicle &other) const
    {
        return brand == other.brand && model == other.model && year == other.year;
    }

    bool operator!=(const Vehicle &other) const
    {
        return !(*this == other);
    }
};

#endif