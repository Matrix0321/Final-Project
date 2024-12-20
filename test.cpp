#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>     
#include "bigint.hpp"  



void Tests() {
    string BigIntToString(const BigInt& num) {
    stringstream ss;
    ss << num;
    return ss.str();
    }
    
    // Three constructors
    BigInt number1; // Default constructor, should be zero
    cout << "number1:" << number1 << endl;

    BigInt number2(-1234567890123456789LL); // Constructor from int64_t input
    cout << "number2:" << number2 << endl;
    BigInt number3("9876543210987654321");   // Constructor from string input
    cout << "number3:" << number3 << endl;
    

    // 1. Test addition operator `+`
    try {
        BigInt res1 = number1 + BigInt(2);
        cout << "number1 + 2:" << res1 << endl;
        if (res1 == BigInt("2")) 
        {
            cout << "Succeeded: addition operator `+`" << endl;
        } 
        else 
        {
            cout << "Failed: addition operator `+`" << endl;
        }
    } catch (const exception& e) {
        cout << "Failed: addition operator `+`" << endl;
    }

    // 2. Test subtraction operator `-`
    try {
        BigInt res2 = number2 - BigInt(100);
        cout << "number2- 100:" << res2 << endl;
        if (res2 == BigInt("-1234567890123456889")) 
        {
            cout << "Succeeded: subtraction operator `-`" << endl;
        } 
        else 
        {
            cout << "Failed: subtraction operator `-`" << endl;
        }
    } catch (const exception& e) 
    {
        cout << "Failed: subtraction operator `-`" << endl;
    }

    // 3. Test multiplication operator `*`
    try {
        BigInt res3 = number3 * BigInt(-50);
        cout << "number3 * -50:" << res3 << endl;
        if (res3 == BigInt("-493827160549382716050")) 
        {
            cout << "Succeeded: multiplication operator `*`" << endl;
        } 
        else 
        {
            cout << "Failed: multiplication operator `*`" << endl;
        }
    } catch (const exception& e) {
        cout << "Failed: multiplication operator `*`" << endl;
    }

    // 4. Test compound operator `+=`
    try {
        number1 += BigInt(5);
        cout << "number1 += 5:" << number1 << endl;
        if (number1 == BigInt("5")) 
        {
            cout << "Succeeded: compound operator `+=`" << endl;
        } 
        else 
        {
            cout << "Failed: compound operator `+=`" << endl;
        }
    } catch (const exception& e) {
        cout << "Failed: compound operator `+=`"<< endl;
    }

    // 5. Test compound operator `-=`
    try {
        number2 -= BigInt(200);
        cout << "number2 -= 200:" << number2 << endl;
        if (number2 == BigInt("-1234567890123456989")) 
        {
            cout << "Succeeded: compound operator `-=`" << endl;
        } 
        else 
        {
            cout << "Failed: compound operator `-=`" << endl;
        }
    } catch (const exception& e) {
        cout << "Failed: compound operator `-=`" << endl;
    }
    // 6. Test Compound Assignment *=
    try {
        number3 *= BigInt(3);
        cout << "number3 *= 3:" << number3 << endl;
        if (number3 == BigInt("29629629632962962963")) 
        {
            cout << "Succeeded: compound operator `*=`" << endl;
        } 
        else 
        {
            cout << "Failed: compound operator `*=`" << endl;
        }
    } catch (const exception& e) {
        cout << "Failed: compound operator `*=`" << endl;
    }


    // 7. Test comparision operator '=='
    try {
        if (number1 == BigInt(5)) 
        {
            cout << "Succeeded: comparision operator '=='" << endl;
        } 
        else
        {
            cout << "Failed: comparision operator '=='"  << endl;
        }
    } catch (const exception& e) {
        cout << "Failed: comparision operator '=='"  << endl;
    }

    // 8. Test comparision operator '!='
    try {
        if (number2 != BigInt("-1234567890123456789")) 
        {
            cout << "Succeeded: comparision operator '!='" << endl;
        } 
        else 
        {
            cout << "Failed: comparision operator '!='" << endl;
        }
    } catch (const exception& e) {
        cout << "Failed: comparision operator '!='" << endl;
    }


    // 9. Test comparision operator '>'
    try {
        if (number3 > BigInt("250944794186760908")) 
        {
            cout << "Succeeded: comparision operator '>'"  << endl;
        } 
        else 
        {
            cout << "Failed: comparision operator '>'" << endl;
        }
    } catch (const exception& e) {
        cout << "Failed: comparision operator '>'" << endl;
    }

    // 10. Test comparision operator '<'
    try {
        if (number1 < BigInt(10)) 
        {
            cout << "Succeeded: comparision operator '<'" << endl;
        } 
        else 
        {
            cout << "failed: comparision operator '<'" << endl;
        }
    } catch (const exception& e) {
        cout << "Failed: comparision operator '<'" << endl;
    }

    // 11. Test comparision operator '>='
    try {
        if (number1 >= BigInt ("5")) 
        {
            cout << "Succeeded: comparision operator '>='" << endl;
        } 
        else 
        {
            cout << "Failed: comparision operator '>='" << endl;
        }
    } catch (const exception& e) {
        cout << "Failed: comparision operator '>='" << endl;
    }

    // 12. Test comparision operator '<='
    try {
        if (number1 <= BigInt("5")) 
        {
            cout << "Succeeded: comparision operator '<='" << endl;
        } 
        else 
        {
            cout << "Failed: comparision operator '<='" << endl;
        }
    } catch (const exception& e) {
        cout << "Failed: comparision operator '<='" << endl;
    }

    // 13. Test unary operator '-'
    try {
        BigInt res13 = -number1;
        cout << "-number1:" << res13 << endl;
        if (res13 == BigInt("-5")) 
        {
            cout << "Succeeded: unary operator '-'" << endl;
        } 
        else 
        {
            cout << "Failed: unary operator '-'" << endl;
        }
    } catch (const exception& e) {
        cout << "Failed: nary operator '-'" << endl;
    }
    // 14. Test pre-increment operator
    try {
        cout << "++number1:" << ++number1 << endl;
        if (number1 == BigInt("6")) 
        {
            cout << "Succeeded: pre-increment operator" << endl;
        } 
        else 
        {
            cout << "Failed: pre-increment operator" << endl;
        }
    } catch (const exception& e) {
        cout << "Failed: pre-increment operator" << endl;
    }

    // 15. Test post-increment operator
    try {
        BigInt temp1 = number1;
        cout << "number1++:" << number1++ << endl;
        if (temp1 == BigInt("6") && number1 == BigInt("7")) 
        {
            cout << "Succeeded: post-increment operator" << endl;
        } 
        else 
        {
            cout << "Failed: post-increment operator" << endl;
        }
    } catch (const exception& e) {
        cout << "Failed: post-increment operator" << endl;
    }

    // 16. Test pre-decrement operator
    try {
        cout << "--number3:" << --number3 << endl;
        if (number3 == BigInt("29629629632962962962")) 
        {
            cout << "Succeeded: pre-decrement operator" << endl;
        } 
        else 
        {
            cout << "Failed: pre-decrement operator" << endl;
        }
    } 
    catch (const exception& e) {
        cout << "Failed: pre-decrement operator" << endl;
    }

    // 17. Test post-decrement operator
    try {
        BigInt temp2 = number3;
        cout << "number3--:" << number3-- << endl;
        if (temp2 == BigInt("29629629632962962962") && number3 == BigInt("29629629632962962961")) 
        {
            cout << "Succeeded: post-decrement operator" << endl;
        } 
        else 
        {
            cout << "Failed: post-decrement operator" << endl;
        }
    } 
    catch (const exception& e) {
        cout << "Failed: post-decrement operator" << endl;
    }
    // 18. Integration tests
    try {
        BigInt res181 = number1 - number2 - number3;
        BigInt res182 = number1 - number3 - number2;
        cout << "number1 - number2 - number3:" << res181 << endl;
        cout << "number1 - number3 - number2:" << res182 << endl;
        if (res181 == res182) 
        {
            cout << "Succeeded: Integration" << endl;
        } 
        else 
        {
            cout << "Failed: Integration" << endl;
        }
    } catch (const exception& e) {
        cout << "Failed: Integration" << endl;
    }

    //19. Consistency Test
    try {
        BigInt res191 = (number1 + number2) - number3;
        BigInt res192 = (number1 - number3) + number2;
        cout << "(number2 + number3) - number1:" << res191 << endl;
        cout << "(number2 - number1) + number3:" << res192 << endl;
        if (res191 == res192) 
        {
            cout << "Succeeded: Consistency" << endl;
        } 
        else 
        {
            cout << "Failed: Consistency" << endl;
        }
    } catch (const exception& e) {
        cout << "Failed: Consistency" << endl;
    }
    //20. Random test and Stress test
    try {
        string random_string1 = "";
        string random_string2 = "";
        for(int i = 1; i < 1000; ++i) 
        /* randomly generate two very large numbers (with thousands of digits).
        The loop start with 1, to avoid 0 as the first digit.*/
        {
            random_string1 += to_string(rand() % 10);
            random_string2 += to_string(rand() % 10);
        }
        BigInt random1(random_string1);
        BigInt random2(random_string2);
        // If the case is succeed, the res20 would be 0
        BigInt res20 = random1 + random2 - random1 - random2;
        cout << "random1 + random2 - random1 - random2:" << res20 << endl;
        if (res20 == BigInt("0")) 
        {
            cout << "Succeeded: Random test and Stress test" << endl;
        } 
        else 
        {
            cout << "Failed: Random test and Stress test" << endl;
        }
    } catch (const exception& e) {
        cout << "Failed: Random test and Stress test" << endl;
    }




}
int main()
{
    Tests();
    return 0;
}
