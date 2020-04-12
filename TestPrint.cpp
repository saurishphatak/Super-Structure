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

void SuperStructure::print()
{
    cout << "\nEntries in the Hash Table :\n\n";

    // Print the hash entries first
    for (int i = 0; i < this->size; i++)
    {
        // Print the number of row
        cout << i << " ==> ";

        for (Node *current = table[i]; current; current = current->nextInMap)
        {
            cout << "[Key : " << current->key << " Value : " << current->value << "] ";
        }

        cout << "\n\n";
    }
}

int main()
{
    int key;
    int value;

    SuperStructure *test = new SuperStructure(11);

    while (cout << "Key : ",
           cin >> key,
           key)
    {
        cout << "Value : ";
        cin >> value;

        // Call the add function
        test->put(key, value);
    }

    // Print
    test->print();
}