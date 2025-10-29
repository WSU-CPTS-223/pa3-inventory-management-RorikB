#ifndef DATA_H
#define DATA_H

#include <string>

using namespace std;

class Data {
private:
    string productName;
    string category;

public:
    Data() = default;
    Data(const string& prodName, const string& cat) : productName(prodName), category(cat) {}
    ~Data() = default;

    string getProductName() const {
        return productName;
    }
    string getCategory() const {
        return category;
    }

    // Overload the output stream operator for easy printing
    friend ostream& operator<<(ostream& os, const Data& data) {
        os << "Product Name: " << data.productName << ", Category: " << data.category;
        return os;
    }
};

#endif 