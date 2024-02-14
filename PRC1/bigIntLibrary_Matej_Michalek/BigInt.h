#ifndef BIGINTLIBRARY_BIGINT_H
#define BIGINTLIBRARY_BIGINT_H

#include "iostream"


class BigInt {
    std::string value;
    char sign;

public:
    //Constructors
    BigInt();
    BigInt(const BigInt&);
    BigInt(const long long&);
    BigInt(const std::string&);

    //Assignment operator overload
    BigInt& operator=(const BigInt&);
    BigInt& operator=(const long long&);
    BigInt& operator=(const std::string&);

    friend std::ostream& operator<<(std::ostream&, const BigInt&);

    //Binary operator overload
    BigInt operator+() const;
    BigInt operator-() const;
    BigInt operator+(const BigInt&) const;
    BigInt operator-(const BigInt&) const;
    BigInt operator*(const BigInt&) const;
    BigInt operator/(const BigInt&) const;
    BigInt operator%(const BigInt&) const;
    BigInt operator+(const long long&) const;
    BigInt operator-(const long long&) const;
    BigInt operator*(const long long&) const;
    BigInt operator/(const long long&) const;
    BigInt operator%(const long long&) const;
    BigInt operator+(const std::string&) const;
    BigInt operator-(const std::string&) const;
    BigInt operator*(const std::string&) const;
    BigInt operator/(const std::string&) const;
    BigInt operator%(const std::string&) const;

    std::string to_string() const;
};


#endif //BIGINTLIBRARY_BIGINT_H
