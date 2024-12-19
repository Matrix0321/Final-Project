# CSE 701 final project
## Introduction
## Implementation
### Private
```cpp
    std::string value; 
```
It is used to store every digit of the number in reverse order. 
```cpp
    bool is_negative; 
```
It is used to determine whether the number is negative or not. <br>
### Constructors 
```cpp
    BigInt();
    BigInt(int64_t number);
    BigInt(const string& str); 
```
The ***BigInt*** contains three constructors. <br>
1. `BigInt()` is a default constructor which sets the number to 0 by default.
2. `BigInt(int64_t number)` is a constructor which takes a signed 64-bit integer and converts it to `BigInt`.
3. `BigInt(const string& str)` is a constructor which takes a string of digits (the string version of a large number) and converts it to `BigInt`. It could also check the empty and invalid inputs, check the `+` and `-` signs, delete all the zeros in front of the numbers which are valuable for calculation.

### Arithmetic Functions
```cpp
    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const;
    BigInt operator*(const BigInt& other) const;
```
1. Addition operator `+` : If their signs are the same, do the addition digit by digit. If they are differnt, do subtraction.
2. Subtraction operator `-` : If their signs are different, do the addition after changing the second number's sign. If not, check which number has the greater absolute value, by comparing lengths (If their lengths are the same then compare the), then subtract the smaller absolute value from the greater absolute value digit by digit. The sign of the result aligns with the one who has the greater absolute value.
3. Multiplication operator `*` : For each digit in the first number, multiply by each digit in the second number and add to the corresponding position in the result. The sign of the result is the XOR of the two numbers’ signs.
### Compound Functions
```cpp
    BigInt& operator+=(const BigInt& other);
    BigInt& operator-=(const BigInt& other);
    BigInt& operator*=(const BigInt& other);
```







### Unary Operators
```cpp
    BigInt operator-() const;
    BigInt& operator++();
    BigInt operator++(int);
    BigInt& operator--();
    BigInt operator--(int);
```
1. Unary minus `operator-()` : If the value is 0, nothing changes. Otherwise, it uses `is_negative` and returns a new `BigInt` object, which all the digits remain the same but the sign is changed.
2. Pre-increment `operator++()`: It adds 1 to the current `BigInt` object, then returns the updated value by reference.
3. Post-increment `operator++(int)`: It creates a copy, adds the current object, then returns the object.
4. Pre-decrement `operator--()`: It subtracts 1 to the current `BigInt` object, then returns the updated value by reference.
5. Pre-decrement `operator--(int)`: It creates a copy, subtracts the current object, then returns the object.

### Comparision Operators

