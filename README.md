# CSE 701 final project
## Introduction
In C++ programming language, a signed 64-bit integer has aminimum value of -9,223,372,036,854,775,808 and a maximum value of 9,223,372,036,854,775,807, but sometimes the numbers we need to calculate are beyond this range. So we made this `BigInt` project, which can deal with arbitrary-precision integers. It has many operation types, including arithmatic operation, compound operation, unary operation, and comparision. With this program, we can calculate some very large numbers without worrying about exceeding the range.

This project has 3 files. The `README.md` includes instructions, the `bigint.hpp` contains all the functions, and the `test.cpp` shows some tests.
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
The `BigInt` contains three constructors. <br>
1. `BigInt()` is a default constructor which sets the number to 0 by default.
2. `BigInt(int64_t number)` is a constructor which takes a signed 64-bit integer and converts it to `BigInt`.
3. `BigInt(const string& str)` is a constructor which takes a string of digits (the string version of a large number) and converts it to `BigInt`. It could also check the empty and invalid inputs, check the `+` and `-` signs.

### Arithmetic Functions
```cpp
    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const;
    BigInt operator*(const BigInt& other) const;
```
1. Addition operator `+` : If their signs are the same, do the addition by adding their absolute values. If they are differnt, subtract the smaller absolute value from the greater one.
2. Subtraction operator `-` : If their signs are different, do the addition. If not, check which number has the greater absolute value, by comparing lengths (If their lengths are the same then compare the), then subtract the smaller absolute value from the greater absolute value digit by digit. The sign of the result aligns with the one who has the greater absolute value.
3. Multiplication operator `*` : For each digit in the first number, multiply by each digit in the second number and add to the corresponding position in the result. The sign of the result is the XOR of the two numbers’ signs.
### Compound Functions
```cpp
    BigInt& operator+=(const BigInt& other);
    BigInt& operator-=(const BigInt& other);
    BigInt& operator*=(const BigInt& other);
```
The logic is the same as the arithmatic functions. Only update the original number after the operation.

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
```cpp
    bool operator==(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    bool operator<(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;
```
1. `operator==`: If they have the same sign (`is_negative` return the same result), and they have the same digits.
2. `operator!=`: The nagation of `operator==`.
3. `operator<` and `operator>`: If their signs are different, the negative number is smaller. If their signs are the same, compare the length of the digit strings (the number with less digits in absolute value is smaller if both are positive; if both negative, the one with less digits is actually greater in absolute value). If their digits have the same length, compare them digit by digit.
4. `operator<=`, `operator>=`: The same logic as `case 1` combining `case3`.

### Stream Output
```cpp
    friend std::ostream& operator<<(std::ostream& os, const BigInt& num)
```
If `num.is_negative` is true and `num.value != "0"`, prints `-`. Then iterates `num.value.rbegin()` to `num.value.rend()` to print the digits from left to right.

## Test 
### Compile and Run
```cpp
g++ -Wall -Wextra -Wconversion -Wsign-conversion -Wshadow -Wpedantic -std=c++20 test.cpp -o test
./test
```

### Output
```cpp
(base) matrix@MatrixMacBook-Pro 701 % ./test
number1:0
number2:-1234567890123456789
number3:9876543210987654321
number1 + 2:2
Succeeded: addition operator `+`
number2- 100:-1234567890123456889
Succeeded: subtraction operator `-`
number3 * -50:-493827160549382716050
Succeeded: multiplication operator `*`
number1 += 5:5
Succeeded: compound operator `+=`
number2 -= 200:-1234567890123456989
Succeeded: compound operator `-=`
number3 *= 3:29629629632962962963
Succeeded: compound operator `*=`
Succeeded: comparision operator '=='
Succeeded: comparision operator '!='
Succeeded: comparision operator '>'
Succeeded: comparision operator '<'
Succeeded: comparision operator '>='
Succeeded: comparision operator '<='
-number1:-5
Succeeded: unary operator '-'
++number1:6
Succeeded: pre-increment operator
number1++:6
Succeeded: post-increment operator
--number3:29629629632962962962
Succeeded: pre-decrement operator
number3--:29629629632962962962
Succeeded: post-decrement operator
number1 - number2 - number3:-28395061742839505965
number1 - number3 - number2:-28395061742839505965
Succeeded: Integration
(number2 + number3) - number1:-30864197523086419943
(number2 - number1) + number3:-30864197523086419943
Succeeded: Consistency
random1 + random2 - random1 - random2:0
Succeeded: Random test and Stress test
```

In this `test.cpp`, we made different cases to test the effectiveness of this program. <br>
For operations test, we compare the result calculated by the `BigInt` program with the result calculated by the calculator, if they are the same, this test case is considered succeed.<br>
For intergeation test, we compare if the results of `number1 - number2 - number3` and `number1 - number3 - number2` are the same. <br>
For Consistency test, we compare if the results of `(number2 + number3) - number1` and `(number2 - number1) + number3` are the same. <br>
And for Random and Stress test, we generate two numbers randomly with thousands of digits, and if `random1 + random2 - random1 - random2` equals to zero, without knowing what the exact number is, we can tell it succeeded. <br>

We also print the log to see clearly whether each test is successful or not. And it shows that each of our tests succeeded.
