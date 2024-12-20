#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm> 

using namespace std;

class BigInt {
private:
    std::string value; //by doing this, the number is stored in reverse order
    bool is_negative; // check if a BIgint object is negative

public:
    // Default constructor
    BigInt() 
    {
        is_negative = false;
        value = "0";
    }

    // Constructor from integer
    BigInt(int64_t number) 
    {
        if (number < 0) 
        {
            is_negative = true;
            number = -number;
        } 
        else 
        {
            is_negative = false;
        }
        if (number == 0) {
            value = "0";
            is_negative = false;
            return;
        }
        /* this step turns a number to string by doing %10 and dividing by 10 again and again，
         then add every digit to value*/
        value = "";
        while (number > 0) 
        {
            value += (number % 10) + '0';
            number /= 10;
        }
    }


    // Constructor from string
    BigInt(const string& str) {
        is_negative = false;
        size_t index = 0;
        if (str.empty()) 
            throw std::invalid_argument("Empty Input");
        if (str.size() == 1 && (str[0] == '-' || str[0] == '+')) 
            throw std::invalid_argument("Only sign, no digits.");
        //determine which sign it has
        if (str[0] == '-') 
        {
            is_negative = true;
            index = 1;
        } 
        else if (str[0] == '+') 
        {
            index = 1;
        }

        // parse the digits and store them, reverse later
        value = "";
        for (size_t i = index; i < str.size(); i++) 
        {
            if (str[i] < '0' || str[i] > '9') //which means it is not a digit
                throw std::invalid_argument("There are non-digit characters.");
            value += str[i];
        }
        std::reverse(value.begin(), value.end());
        //delete all the zeros before the digits which are valuable for calculation
        while (value.size() > 1 && value.back() == '0') 
            value.pop_back();
        // If it is still zero, then it's not a negative number.
        if (value.size() == 1 && value[0] == '0') 
        {
            is_negative = false;
        }
    }

    // Addition operator
    BigInt operator+(const BigInt& other) const {
        if (is_negative == other.is_negative) // If they have the same sign, do the regular addition.
        {
            BigInt result;
            result.is_negative = is_negative;
            result.value = ""; // Create an empty string 
            int carry = 0;
            size_t max_size = max(value.size(), other.value.size());
            for (size_t i = 0; i < max_size || carry; ++i) 
            {
                int digit1 = (i < value.size()) ? value[i] - '0' : 0;
                int digit2 = (i < other.value.size()) ? other.value[i] - '0' : 0;
                int sum = digit1 + digit2 + carry;
                result.value += (sum % 10) + '0';
                carry = sum / 10;
            }
            //delete zeros
            while (result.value.size() > 1 && result.value.back() == '0') 
                result.value.pop_back();

            // If the result is still zero
            if (result.value.size() ==1 && result.value[0] == '0') 
            {
                result.is_negative = false;
            }

            return result;
        } 
        else //IF their signs are different, turn to do subtraction
        {
            BigInt temp = other;
            temp.is_negative = !temp.is_negative;
            return *this - temp;
        }
    }

    // += operator
    BigInt& operator+=(const BigInt& other) {
        *this = *this + other;
        return *this;
    }

    // Subtraction operator
    BigInt operator-(const BigInt& other) const {
        if (is_negative != other.is_negative) // If they have different sign, do the addition
        {
            BigInt temp = other;
            temp.is_negative = !temp.is_negative;
            return *this + temp;
        } 
        else 
        {
            BigInt result;
            bool resultNegative = false;
            // find which one has larger lenth
            bool greater = false;
            if (value.size() > other.value.size()) 
            {
                greater = true;
            } 
            else if (value.size() < other.value.size()) 
            {
                greater = false;
            } 
            else 
            {
                //  If they have saame number of digits, compare them digit by digit 
                for (size_t i = value.size(); i-- > 0; )
                {
                    if (value[i] > other.value[i])
                    {
                        greater = true;
                        break;
                    } else if (value[i] < other.value[i]) 
                    {
                        greater = false;
                        break;
                    }
                }
            }
            //After knowing which one is greater, subtract the smaller one from the greater one.
            if (greater) 
            {
                result.value = "";
                resultNegative = is_negative;
                int borrow = 0;
                for (size_t i = 0; i < value.size(); i++) 
                {
                    int digit1 = value[i] - '0';
                    int digit2 = (i < other.value.size()) ? other.value[i] - '0' : 0;
                    int diff = digit1 - digit2 - borrow;
                    if (diff < 0) 
                    {
                        diff += 10;
                        borrow = 1;
                    } 
                    else 
                    {
                        borrow = 0;
                    }
                    result.value += static_cast<char>(diff + '0');
                }
            } 
            else 
            {
    
                result.value = "";
                resultNegative = !is_negative;
                int borrow = 0;
                for (size_t i = 0; i < other.value.size(); i++) 
                {
                    int digit1 = other.value[i] - '0';
                    int digit2 = (i < value.size()) ? value[i] - '0' : 0;
                    int diff = digit1 - digit2 - borrow;
                    if (diff < 0) 
                    {
                        diff += 10;
                        borrow = 1;
                    } 
                    else 
                    {
                        borrow = 0;
                    }
                    result.value += static_cast<char>(diff + '0');
                }
            }
            while (result.value.size() > 1 && result.value.back() == '0') 
                result.value.pop_back();

            if (result.value.size() ==1 && result.value[0] == '0') {
                resultNegative = false;
            }
            result.is_negative = resultNegative;
            return result;
        }
    }

    // -= operator
    BigInt& operator-=(const BigInt& other) {
        *this = *this - other;
        return *this;
    }

    // Multiplication operator
    BigInt operator*(const BigInt& other) const {
        // If one of them is zero, the answer is zero.
        if ((value.size() == 1 && value[0] == '0') || (other.value.size() == 1 && other.value[0] == '0')) 
        {
            return BigInt("0");
        }
        BigInt result;
        result.value = std::string(value.size() + other.value.size(), '0');
        //If one of them is negative, the result is negative.
        result.is_negative = (is_negative != other.is_negative);

        for (size_t i = 0; i < value.size(); i++) 
        {
            int digit1 = value[i] - '0';
            int carry = 0;
            for (size_t j = 0; j < other.value.size() || carry; j++) 
            {
                int digit2 = (j < other.value.size()) ? other.value[j] - '0' : 0;
                int temp = (result.value[i + j] - '0') + digit1 * digit2 + carry;
                result.value[i + j] = static_cast<char>((temp % 10) + '0');
                carry = temp / 10;
            }
        }
        while (result.value.size() > 1 && result.value.back() == '0') 
            result.value.pop_back();
        if (result.value.size() ==1 && result.value[0] == '0') 
        {
            result.is_negative = false;
        }

        return result;
    }

    // *= operator
    BigInt& operator*=(const BigInt& other) {
        *this = *this * other;
        return *this;
    }

    // Unary minus operator
    BigInt operator-() const {
        BigInt result = *this;
        if (value.size() ==1 && value[0] == '0') //If it is zero, it cannot be negative.
        {
            result.is_negative = false;
        } 
        else 
        {
            result.is_negative = !is_negative;
        }
        return result;
    }

    // Pre-increment operator
    BigInt& operator++() { //which equals to x = x + 1
        *this += BigInt(1);
        return *this;
    }

    // Post-increment operator
    BigInt operator++(int) {
        BigInt temp = *this;
        ++(*this);
        return temp;
    }
    // Pre-decrement operator
    BigInt& operator--() { // which equals to x = x - 1
        *this -= BigInt(1);
        return *this;
    }

    // Post-decrement operator
    BigInt operator--(int) {
        BigInt temp = *this;
        --(*this);
        return temp;
    }


    // Comparison operators
    /* For `==` and `!=`, check if they have the same sign and the exact same digits.*/
    bool operator==(const BigInt& other) const { return is_negative == other.is_negative && value == other.value; }
    bool operator!=(const BigInt& other) const { return !(*this == other); }
    /*  For `<` and `>`, first check their signs, 
    cause a negative number is always less than a positive one.
    If they have the same sign, then compare the digits.
     */
    bool operator<(const BigInt& other) const {
        if (is_negative != other.is_negative) 
            return is_negative;
        if (value.size() != other.value.size()) 
        /* If they are positive, the one who has longer length is greater. 
         If they are negative, the situation is reversed.*/
            return is_negative ? value.size() > other.value.size() : value.size() < other.value.size();
        // Compare them digit by digit
        for (size_t i = value.size(); i-- > 0; )
        {
            if (value[i] != other.value[i]) 
            {
                return is_negative ? (value[i] > other.value[i]) : (value[i] < other.value[i]);
            }
        }
        // If all digits are equal, the two numbers are equal.
        return false;
    }
    bool operator>(const BigInt& other) const {
        // If one is negative and the other is not, the non-negative is greater
        if (is_negative != other.is_negative) 
            return other.is_negative; 
        // same logic as part of operator`<`
        if (value.size() != other.value.size())
            return is_negative ? (value.size() < other.value.size()) 
                            : (value.size() > other.value.size());
        for (size_t i = value.size(); i-- > 0; )
        {
            if (value[i] != other.value[i]) {

                return is_negative ? (value[i] < other.value[i]) 
                                : (value[i] > other.value[i]);
            }
        }
        return false;
    }

    bool operator<=(const BigInt& other) const { return !(*this > other); }
    bool operator>=(const BigInt& other) const { return !(*this < other); }

    // Output stream operator
    friend std::ostream& operator<<(std::ostream& os, const BigInt& num) {
        if (num.is_negative) os << '-';
        for (auto it = num.value.rbegin(); it != num.value.rend(); ++it) os << *it;
        return os;
    }
};

