/*
 * --------------------------------------------------------------------------------
 * File :         TestPrint.cpp
 * Project :      sup
 * Author :       Saurish 
 * 
 * 
 * Description : Test the put function by printing the values
 * --------------------------------------------------------------------------------
 * 
 * Revision History : 
 * 2020-April-12	[SP] : Created
 * --------------------------------------------------------------------------------
 */

#include <iostream>
#include "SuperStructure.cpp"

using namespace std;

int main()
{
    int key;
    int value;

    // Create a new Super Structure
    SuperStructure *test = new SuperStructure(11);

    // Take input of key-value pairs
    while (cout << "Key (0 to stop) :",
           cin >> key,
           key)
    {
        cout << "Value : ";
        cin >> value;

        // Call the add function
        test->put(key, value);
    }

    // Print Tree
    test->printInAscendingOrder();

    // Remove some value
    test->remove(3);

    test->printInsertionSequence();
    test->printInAscendingOrder();
    test->printHashTable();
}