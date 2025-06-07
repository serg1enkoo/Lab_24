#include <iostream>
#include <string>
#include <numeric>
#include <cmath>
#include <stdexcept>
#include <limits>

using namespace std;

class Fraction {
private:
    long long numerator;
    long long denominator;

    void reduce() {
        if (denominator == 0) return;
        if (numerator == 0) {
            denominator = 1;
            return;
        }
        long long common_divisor = std::gcd(std::abs(numerator), std::abs(denominator));
        if (common_divisor != 0) {
             numerator /= common_divisor;
             denominator /= common_divisor;
        }
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    Fraction(long long num = 0, long long den = 1) : numerator(num), denominator(den) {
        if (den == 0) {
            throw std::invalid_argument("Знаменник нуль? Ти серйозно?!");
        }
        reduce();
    }

    string toString() const {
        if (denominator == 1) return to_string(numerator);
        if (numerator == 0) return "0";

        string sign = "";
        long long num_abs = numerator;
        if (numerator < 0) {
            sign = "-";
            num_abs = -num_abs;
        }

        long long whole_part = num_abs / denominator;
        long long fraction_part = num_abs % denominator;

        string result = sign;
        if (whole_part > 0) {
            result += to_string(whole_part);
            if (fraction_part > 0) {
                result += " " + to_string(fraction_part) + "/" + to_string(denominator);
            }
        } else if (fraction_part > 0) {
             result += to_string(fraction_part) + "/" + to_string(denominator);
        }
        return result;
    }

    double toDouble() const {
        return static_cast<double>(numerator) / denominator;
    }

    string getRawString() const {
         return std::to_string(numerator) + "/" + std::to_string(denominator);
     }

    Fraction plus(const Fraction& that) const {
        long long new_num = numerator * that.denominator + that.numerator * denominator;
        long long new_den = denominator * that.denominator;
        return Fraction(new_num, new_den);
    }

    Fraction minus(const Fraction& that) const {
        long long new_num = numerator * that.denominator - that.numerator * denominator;
        long long new_den = denominator * that.denominator;
        return Fraction(new_num, new_den);
    }

    Fraction times(const Fraction& that) const {
        long long new_num = numerator * that.numerator;
        long long new_den = denominator * that.denominator;
        return Fraction(new_num, new_den);
    }

    Fraction by(const Fraction& that) const {
        if (that.numerator == 0) {
            throw std::invalid_argument("Ділити на нуль?! Геть звідси!");
        }
        long long new_num = numerator * that.denominator;
        long long new_den = denominator * that.numerator;
        return Fraction(new_num, new_den);
    }

    bool isGreaterThan(const Fraction& that) const {
        return static_cast<long long>(this->numerator) * that.denominator > static_cast<long long>(that.numerator) * this->denominator;
    }

    bool isLessThan(const Fraction& that) const {
        return static_cast<long long>(this->numerator) * that.denominator < static_cast<long long>(that.numerator) * this->denominator;
    }

    bool isEqual(const Fraction& that) const {
        return this->numerator == that.numerator && this->denominator == that.denominator;
    }

};

int main() {
    long long num1, den1, num2, den2;
    char slash;

    cout << "Введи перший дріб (типу 3/4): ";
    cin >> num1 >> slash >> den1;

    cout << "Тепер другий дріб (типу 1/3): ";
    cin >> num2 >> slash >> den2;

    Fraction f1(num1, den1);
    Fraction f2(num2, den2);

    cout << "\nПорівнюємо " << f1.getRawString() << " та " << f2.getRawString() << "...\n" << endl;

    if (f1.isGreaterThan(f2)) {
        cout << f1.getRawString() << " > " << f2.getRawString() << endl;
    } else if (f1.isLessThan(f2)) {
        cout << f1.getRawString() << " < " << f2.getRawString() << endl;
    } else {
        cout << f1.getRawString() << " = " << f2.getRawString() << endl;
    }

    return 0;
}
