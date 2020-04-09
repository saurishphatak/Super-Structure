/*
 * --------------------------------------------------------------------------------
 * File :         SuperStructure.cpp
 * Project :      sup
 * Author :       Saurish 
 * 
 * 
 * Description : This is my implementation of Super Structure 
 * --------------------------------------------------------------------------------
 * 
 * Revision History : 
 * 2020-April-09	[SP] : Created
 * --------------------------------------------------------------------------------
 */

#include <iostream>

using namespace std;

// Define a node
struct Node
{
    /**
     * Fields :
     * 
     * left : points to the left child of the node
     * key : holds the key of the node
     * value : holds the value of the node
     * right : points to the right child of the node
     * next : points to the next node in the Linked List
     * nextInMap : points to the next node with the same hash
     */
    Node *left;
    int key;
    int value;
    Node *right;
    Node *next;
    Node *nextInMap;

    // Constructor
    Node(int key, int value)
    {
        // Initialize all the fields
        left = nullptr;
        this->key = key;
        this->value = value;
        right = nullptr;
        next = nullptr;
        nextInMap = nullptr;
    }
};
