#include "bigint.hpp"
#include <iostream>

void print(const std::string& prefix, const bigint& val) {
    std::cout << prefix << val << std::endl;
}

int main() {
    std::cout << "--- CONSTRUCTORS ---" << std::endl;
    bigint z; print("z: ", z);
    bigint a(42); print("a: ", a);
    bigint b(0); print("b: ", b);
    bigint c(999999999); print("c: ", c);

    std::cout << "\n--- ADDITION WITHOUT CARRY ---" << std::endl;
    print("123 + 456: ", bigint(123) + bigint(456));
    print("10 + 20: ", bigint(10) + bigint(20));

    std::cout << "\n--- ADDITION WITH CASCADE CARRY ---" << std::endl;
    print("9 + 1: ", bigint(9) + bigint(1));
    print("99 + 1: ", bigint(99) + bigint(1));
    print("999999999 + 1: ", bigint(999999999) + bigint(1));
    
    // Massive Number Addition Check (Constructed via shifts)
    bigint massive(9999);
    massive <<= 10; 
    massive += bigint(9999); 
    print("Massive 99990000009999 + 1: ", massive + bigint(1));

    // Shift tests
    std::cout << "\n--- DIGIT SHIFTS ---" << std::endl;
    bigint shift_test(123);
    print("123 << 0: ", shift_test << 0);
    print("123 << 2: ", shift_test << 2);
    print("12300 >> 2: ", (shift_test << 2) >> 2);
    print("123 >> 5: ", shift_test >> 5);
    shift_test <<= bigint(5);
    print("123 <<= bigint(5): ", shift_test);
    shift_test >>= bigint(3);
    print("after >>= bigint(3): ", shift_test);

    // Subject exact tests (isolated variable scope)
    std::cout << "\n--- SUBJECT COMPATIBILITY ---" << std::endl;
    {
        const bigint sa(42);
        bigint sb(21), sc, sd(1337), se(sd);

        std::cout << sa << "\n" << sb << "\n" << sc << "\n" << sd << "\n" << se << std::endl;
        std::cout << sa + sb << std::endl;
        std::cout << (sc += sa) << std::endl;
        std::cout << sb << std::endl;
        std::cout << ++sb << std::endl;
        std::cout << sb++ << std::endl;
        std::cout << ((sb << 10) + 42) << std::endl;
        std::cout << (sd <<= 4) << std::endl;
        std::cout << (sd >>= (const bigint)2) << std::endl;
        std::cout << sa << "\n" << sd << std::endl;
        std::cout << (sd < sa) << "\n" << (sd <= sa) << "\n" << (sd > sa) << "\n" 
                  << (sd >= sa) << "\n" << (sd == sa) << "\n" << (sd != sa) << std::endl;
    }

    // Edge sizes
    std::cout << "\n--- EDGES & DIFFERENT SIZES COMPARISON ---" << std::endl;
    bigint small(12);
    bigint big(1324);
    std::cout << (small < big) << std::endl; // 1
    std::cout << (big > small) << std::endl; // 1
    std::cout << (small == bigint(12)) << std::endl; // 1
    std::cout << (small != big) << std::endl; // 1

    std::cout << "\n--- POST/PRE INCREMENT ---" << std::endl;
    bigint inc(0);
    std::cout << inc++ << std::endl; // 0
    std::cout << inc << std::endl;   // 1
    std::cout << ++inc << std::endl; // 2

    return 0;
}
