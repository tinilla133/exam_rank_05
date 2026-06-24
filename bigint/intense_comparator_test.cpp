#include "bigint.hpp"
#include <iostream>
#include <string>

// Helper function to create a bigint from a string representation
// This is slow but avoids needing a string constructor.
bigint from_string(const std::string& s) {
    if (s == "0") return bigint(0);
    bigint res(0);
    for (size_t i = 0; i < s.length(); ++i) {
        res <<= 1; // Multiply by 10
        res += bigint(s[i] - '0');
    }
    return res;
}

void check(const std::string& name, bool result, bool expected) {
    std::cout << name << ": " << (result == expected ? "PASS" : "FAIL")
              << " (Got: " << result << ", Expected: " << expected << ")" << std::endl;
}

int main() {
    std::cout << "--- Intense Comparator Tests ---" << std::endl;

    bigint zero(0);
    bigint n1(123);
    bigint n2(12345);
    bigint n3(12345);
    
    bigint large1 = (bigint(9) << 1) + bigint(9); // 99
    large1 = (large1 << 1) + bigint(9); // 999
    for (int i = 0; i < 15; ++i) { // Create 999... (18 digits)
        large1 <<= 1;
    }

    bigint large2 = large1;
    bigint large3 = large1 + bigint(1);
    bigint large4 = large1;
    // Manually create a number one less than large1
    bigint one(1);
    // This is tricky without subtraction. Let's use a different smaller number.
    bigint large5 = (bigint(9) << 1) + bigint(8); // 98
     for (int i = 0; i < 15; ++i) {
        large5 <<= 1;
    }


    std::cout << "\n--- 1. Different Lengths ---" << std::endl;
    check("123 < 12345", n1 < n2, true);
    check("12345 > 123", n2 > n1, true);
    check("12345 < 123", n2 < n1, false);
    check("123 >= 12345", n1 >= n2, false);

    std::cout << "\n--- 2. Same Length, Equal ---" << std::endl;
    check("12345 == 12345", n2 == n3, true);
    check("12345 != 12345", n2 != n3, false);
    check("12345 < 12345", n2 < n3, false);
    check("12345 > 12345", n2 > n3, false);
    check("12345 <= 12345", n2 <= n3, true);
    check("12345 >= 12345", n2 >= n3, true);

    std::cout << "\n--- 3. Very Large Numbers ---" << std::endl;
    check("large1 == large2", large1 == large2, true);
    check("large1 < large2", large1 < large2, false);
    check("large1 < large3 (one bigger)", large1 < large3, true);
    check("large3 > large1", large3 > large1, true);
    check("large1 >= large3", large1 >= large3, false);
    check("large1 > large5 (one smaller)", large1 > large5, true);


    std::cout << "\n--- 4. Zero Comparisons ---" << std::endl;
    check("123 > 0", n1 > zero, true);
    check("0 < 123", zero < n1, true);
    check("0 == 0", zero == bigint(0), true);
    check("123 == 0", n1 == zero, false);
    check("0 >= 0", zero >= bigint(0), true);

    std::cout << "\n--- 5. Same prefix ---" << std::endl;
    bigint p1 = (bigint(123) << 2); // 12300
    bigint p2 = (bigint(123) << 1); // 1230
    check("12300 > 1230", p1 > p2, true);
    check("1230 < 12300", p2 < p1, true);
    
    bigint p3 = p1 + bigint(45); // 12345
    bigint p4 = p1 + bigint(46); // 12346
    check("12345 < 12346", p3 < p4, true);
    check("12346 > 12345", p4 > p3, true);
    check("12345 == 12346", p3 == p4, false);


    return 0;
}
