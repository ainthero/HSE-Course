#include "biginteger.h"

BigInteger BigInteger::sub(const BigInteger &_this, const BigInteger &number,
                           int sign) {//не учитывает знаки и считает что первое число больше второго
    BigInteger res;
    int digit = 0;
    for (int i = 0; i < _this._data.size(); i++) {
        if (_this._at(i) - digit >= number._at(i)) {
            res._data.push_back(_this._at(i) - number._at(i) - digit);
            digit = 0;
        } else {
            res._data.push_back(_this._at(i) - number._at(i) + base - digit);
            digit = 1;
        }
    }
    res.sign = sign;
    while (!res._data.empty() && res._data.back() == 0) res._data.pop_back();
    if (res._data.empty()) res._data.push_back(0), res.sign = 1;
    return res;
}

std::pair<BigInteger, int> BigInteger::div(const BigInteger &_this, int number) {//pair<quotient, remainder>
    int remainder = 0;
    BigInteger res = _this;
    int number_sign = number < 0 ? -1 : 1;
    res.sign = res.sign * number_sign;
    number = abs(number);
    for (auto num_ptr = res._data.rbegin(); num_ptr != res._data.rend(); num_ptr++) {
        uint64_t cur = *num_ptr + (uint64_t) remainder * base;
        *num_ptr = int(cur / number);
        remainder = int(cur % number);
    }
    while (!res._data.empty() && res._data.back() == 0) res._data.pop_back();
    if (res._data.empty()) res._data.push_back(0), res.sign = 1;
    return {res, remainder};
}

BigInteger::BigInteger(int number) {
    sign = number < 0 ? -1 : 1;
    number = abs(number);
    if (number == 0) {
        _data.push_back(0);
        return;
    }
    while (number > 0) {
        _data.push_back(number % base);
        number /= base;
    }
}

BigInteger::BigInteger(std::string number) {
    if (number.front() == '-') {
        sign = -1;
        number.erase(number.begin());
    } else {
        sign = 1;
    }
    for (int i = number.length(); i > 0; i -= 9)
        if (i < 9)
            _data.push_back(std::stoi(number.substr(0, i)));
        else
            _data.push_back(std::stoi(number.substr(i - 9, 9)));
    while (_data.size() > 1 && _data.back() == 0) {
        _data.pop_back();
    }
}

BigInteger::BigInteger(const BigInteger &number) {
    *this = number;
}

BigInteger &BigInteger::operator=(int number) {
    *this = BigInteger(number);
    return *this;
}

BigInteger BigInteger::operator-() {
    BigInteger res = *this;
    res.sign += res.sign * (-2);
    return res;
}

BigInteger BigInteger::operator+(const BigInteger &number) const {
    BigInteger res = *this;
    return res += number;

}

BigInteger &BigInteger::operator+=(const BigInteger &number) {
    BigInteger res;
    int digit = 0;
    if (sign == number.sign) {
        res.sign = sign;
        for (int i = 0; i < std::max(_data.size(), number._data.size()); i++) {
            res._data.push_back((_at(i) + number._at(i) + digit) % base);
            digit = (_at(i) + number._at(i) + digit) / base;
        }
        if (digit) res._data.push_back(digit);
        return *this = res;
    } else {
        BigInteger nosign_number1 = *this;
        nosign_number1.sign = 1;
        BigInteger nosign_number2 = number;
        nosign_number2.sign = 1;
        if (sign == 1) {
            if (nosign_number1 >= nosign_number2) {
                return *this = sub(nosign_number1, nosign_number2, 1);
            } else {
                return *this = sub(nosign_number2, nosign_number1, -1);
            }
        } else {
            if (nosign_number1 >= nosign_number2) {
                return *this = sub(nosign_number1, nosign_number2, -1);
            } else {
                return *this = sub(nosign_number2, nosign_number1, 1);
            }
        }
    }
}

BigInteger &BigInteger::operator-=(const BigInteger &number) {
    BigInteger revsign_number = number;
    revsign_number.sign += number.sign * (-2);
    return *this += revsign_number;
}

BigInteger BigInteger::operator-(const BigInteger &number) const {
    BigInteger res = *this;
    return res -= number;
}

BigInteger BigInteger::operator*(int number) const {
    if (number == 0 || *this == BigInteger(0)) return BigInteger(0);
    int digit = 0;
    BigInteger res;
    int number_sign = number < 0 ? -1 : 1;
    res.sign = sign * number_sign;
    for (auto num : _data) {
        res._data.push_back(((uint64_t) num * number + digit) % base);
        digit = (int) (((uint64_t) num * number + digit) / base);
    }
    if (digit) res._data.push_back(digit);
    return res;
}

BigInteger BigInteger::operator*(const BigInteger &number) const {
    if (*this == BigInteger(0) || number == BigInteger(0)) return BigInteger(0);
    BigInteger res;
    BigInteger tmp = 0;
    BigInteger nosign_this = *this;
    nosign_this.sign = 1;
    for (int i = 0; i < number._data.size(); i++) {
        tmp = nosign_this * number._at(i);
        for (int j = 0; j < i; j++) {
            tmp = tmp * base;
        }
        res += tmp;
    }
    res.sign = sign * number.sign;
    return res;
}

BigInteger &BigInteger::operator*=(const BigInteger &number) {
    *this = *this * number;
    return *this;
}

BigInteger BigInteger::operator%(int number) const {
    return div(*this, number).second;
}

BigInteger &BigInteger::operator%=(int number) {
    *this = *this % number;
    return *this;
}

BigInteger BigInteger::operator/(int number) const {
    return div(*this, number).first;
}

BigInteger &BigInteger::operator/=(int number) {
    *this = *this / number;
    return *this;
}

BigInteger &BigInteger::operator++() {//prefix
    if (sign == 1 && _data[0] + 1 < base) _data[0]++;
    else if (sign == -1 && _data[0] - 1 >= 0) _data[0]--;
    else *this += 1;
    return *this;
}

BigInteger BigInteger::operator++(int) {//postfix
    BigInteger tmp = *this;
    *this += 1;
    return tmp;
}

BigInteger &BigInteger::operator--() {//prefix
    if (sign == 1 && _data[0] - 1 >= 0) _data[0]--;
    else if (sign == -1 && _data[0] + 1 < base) _data[0]++;
    else *this -= 1;
    return *this;
}

BigInteger BigInteger::operator--(int) {//postfix
    BigInteger tmp = *this;
    *this -= 1;
    return tmp;
}

bool BigInteger::operator>(const BigInteger &number) const {
    if (sign != number.sign) return sign == 1;
    if (_data.size() > number._data.size()) {
        return true;
    }
    if (_data.size() < number._data.size()) {
        return false;
    }
    for (int i = (int) number._data.size() - 1; i >= 0; i--) {
        if (_at(i) < number._at(i)) {
            return sign != 1;
        }
        if (_at(i) > number._at(i)) {
            return sign == 1;
        }
    }
    return false;
}

bool BigInteger::operator>=(const BigInteger &number) const {
    return (*this == number) || (*this > number);
}

bool BigInteger::operator==(const BigInteger &number) const {
    if (sign != number.sign) return false;
    if (_data.size() != number._data.size()) return false;
    for (int i = (int) number._data.size() - 1; i >= 0; i--) {
        if (_at(i) != number._at(i)) return false;
    }
    return true;
}

bool BigInteger::operator!=(const BigInteger &number) const {
    return !(*this == number);
}

bool BigInteger::operator<(const BigInteger &number) const {
    return !(*this >= number);
}

bool BigInteger::operator<=(const BigInteger &number) const {
    return !(*this > number);
}

std::string BigInteger::toString() const {
    std::string ans;
    if (sign == -1) ans.push_back('-');
    if (!_data.empty()) ans += std::to_string(_data.back());
    for (int i = (int) _data.size() - 2; i >= 0; i--) {
        int tmp_base = base;
        while (tmp_base > 1) {
            ans.push_back('0' + (_data[i] / (tmp_base / 10) % 10));
            tmp_base /= 10;
        }
    }
    return ans;
}

BigInteger::operator bool() const {
    return !(_data.size() == 1 && _at(0) == 0);
}

std::ostream &operator<<(std::ostream &out, const BigInteger &number) {
    out << number.toString();
    return out;
}

std::istream &operator>>(std::istream &in, BigInteger &number) {
    std::string tmp;
    in >> tmp;
    number = BigInteger(tmp);
    return in;
}
