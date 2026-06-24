#include <iostream>
#include <cassert>
#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"
#include "set.hpp"

// Helper function to check size for array_bag by accessing protected member
// This is a workaround for testing since there is no public size() method.
class TestHelper_array_bag : public searchable_array_bag {
public:
    int get_size() const { return this->size; }
};

// We can't easily get the size of the tree_bag without changing its interface,
// so we will comment out size checks for it.

void test_searchable_array_bag() {
    std::cout << "--- Testing searchable_array_bag ---" << std::endl;

    // Test default constructor
    searchable_array_bag b1_raw;
    TestHelper_array_bag& b1 = reinterpret_cast<TestHelper_array_bag&>(b1_raw);
    assert(b1.get_size() == 0);
    assert(!b1.has(5));
    std::cout << "Default constructor test passed." << std::endl;

    // Test insert and has
    b1.insert(10);
    assert(b1.get_size() == 1);
    assert(b1.has(10));
    assert(!b1.has(5));
    std::cout << "Insert and has test passed." << std::endl;

    // Test inserting multiple elements
    b1.insert(20);
    b1.insert(5);
    assert(b1.get_size() == 3);
    assert(b1.has(20));
    assert(b1.has(5));
    std::cout << "Insert multiple elements test passed." << std::endl;
    
    // Test inserting duplicate elements
    b1.insert(10);
    assert(b1.get_size() == 4);
    assert(b1.has(10));
    std::cout << "Insert duplicate elements test passed." << std::endl;

    // Test copy constructor
    searchable_array_bag b2_raw(b1);
    TestHelper_array_bag& b2 = reinterpret_cast<TestHelper_array_bag&>(b2_raw);
    assert(b2.get_size() == 4);
    assert(b2.has(10));
    assert(b2.has(20));
    assert(b2.has(5));
    std::cout << "Copy constructor test passed." << std::endl;

    // Test assignment operator
    searchable_array_bag b3_raw;
    TestHelper_array_bag& b3 = reinterpret_cast<TestHelper_array_bag&>(b3_raw);
    b3.insert(100);
    b3 = b1;
    assert(b3.get_size() == 4);
    assert(b3.has(10));
    assert(!b3.has(100));
    std::cout << "Assignment operator test passed." << std::endl;
    
    // Test with empty bag
    searchable_array_bag empty_bag_raw;
    TestHelper_array_bag& empty_bag = reinterpret_cast<TestHelper_array_bag&>(empty_bag_raw);
    assert(empty_bag.get_size() == 0);
    assert(!empty_bag.has(1));
    searchable_array_bag empty_bag_copy_raw(empty_bag);
    TestHelper_array_bag& empty_bag_copy = reinterpret_cast<TestHelper_array_bag&>(empty_bag_copy_raw);
    assert(empty_bag_copy.get_size() == 0);
    searchable_array_bag empty_bag_assign_raw;
    TestHelper_array_bag& empty_bag_assign = reinterpret_cast<TestHelper_array_bag&>(empty_bag_assign_raw);
    empty_bag_assign = empty_bag;
    assert(empty_bag_assign.get_size() == 0);
    std::cout << "Empty bag tests passed." << std::endl;
}

void test_searchable_tree_bag() {
    std::cout << "\n--- Testing searchable_tree_bag ---" << std::endl;

    // Test default constructor
    searchable_tree_bag t1;
    // assert(t1.size() == 0); // No size method
    assert(!t1.has(5));
    std::cout << "Default constructor test passed." << std::endl;

    // Test insert and has
    t1.insert(10);
    // assert(t1.size() == 1);
    assert(t1.has(10));
    assert(!t1.has(5));
    std::cout << "Insert and has test passed." << std::endl;

    // Test inserting multiple elements (testing the BST structure)
    t1.insert(5);
    t1.insert(20);
    t1.insert(15);
    t1.insert(1);
    // assert(t1.size() == 5);
    assert(t1.has(5));
    assert(t1.has(20));
    assert(t1.has(15));
    assert(t1.has(1));
    assert(!t1.has(100));
    std::cout << "Insert multiple elements test passed." << std::endl;

    // Test inserting duplicate elements
    t1.insert(10);
    // assert(t1.size() == 6);
    assert(t1.has(10));
    std::cout << "Insert duplicate elements test passed." << std::endl;

    // Test copy constructor
    searchable_tree_bag t2(t1);
    // assert(t2.size() == 6);
    assert(t2.has(10));
    assert(t2.has(5));
    assert(t2.has(20));
    assert(t2.has(15));
    assert(t2.has(1));
    std::cout << "Copy constructor test passed." << std::endl;

    // Test assignment operator
    searchable_tree_bag t3;
    t3.insert(99);
    t3 = t1;
    // assert(t3.size() == 6);
    assert(t3.has(10));
    assert(!t3.has(99)); // Assuming assignment overwrites
    std::cout << "Assignment operator test passed." << std::endl;

    // Test with empty bag
    searchable_tree_bag empty_bag;
    // assert(empty_bag.size() == 0);
    assert(!empty_bag.has(1));
    searchable_tree_bag empty_bag_copy(empty_bag);
    // assert(empty_bag_copy.size() == 0);
    searchable_tree_bag empty_bag_assign;
    empty_bag_assign = empty_bag;
    // assert(empty_bag_assign.size() == 0);
    std::cout << "Empty bag tests passed." << std::endl;
}

void test_set() {
    std::cout << "\n--- Testing set ---" << std::endl;

    // Test with searchable_array_bag
    searchable_array_bag sab;
    set s_array(sab);
    // No public size method in set
    
    s_array.insert(10);
    assert(s_array.has(10));

    // Test inserting duplicate
    s_array.insert(10);
    // We can't check size, but we can check behavior
    assert(s_array.has(10));

    s_array.insert(20);
    assert(s_array.has(20));
    std::cout << "Set with searchable_array_bag tests passed." << std::endl;

    // Test with searchable_tree_bag
    searchable_tree_bag stb;
    set s_tree(stb);
    // No public size method in set

    s_tree.insert(100);
    assert(s_tree.has(100));

    // Test inserting duplicate
    s_tree.insert(100);
    assert(s_tree.has(100));

    s_tree.insert(50);
    s_tree.insert(200);
    assert(s_tree.has(50));
    assert(s_tree.has(200));
    assert(!s_tree.has(99));
    std::cout << "Set with searchable_tree_bag tests passed." << std::endl;
    
    // Test set copy and assignment (polymorphism)
    set s_tree_copy(s_tree);
    assert(s_tree_copy.has(100));
    
    searchable_array_bag sab2;
    set s_array_assign(sab2);
    s_array_assign = s_tree;
    assert(s_array_assign.has(100));
    assert(s_array_assign.has(50));
    assert(s_array_assign.has(200));
    std::cout << "Set copy and assignment tests passed." << std::endl;
}


int main() {
    test_searchable_array_bag();
    test_searchable_tree_bag();
    test_set();

    std::cout << "\nAll tests passed successfully!" << std::endl;

    return 0;
}
