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

// Define a class SuperStructure
class SuperStructure
{
    /**
     * Fields : 
     * 
     * table : points to the Trump Tower
     * size : contains the size of the Trump Tower
     * head : points to the head of the Linked List
     * tail : points to the tail of the Linked List
     * root : points to the root of the BST
     */
    Node **table;
    int size;
    Node *head;
    Node *tail;
    Node *root;

public:
    // Constructor
    SuperStructure(int size = 11)
    {
        // Initialize the fields
        this->size = size;
        table = new Node *[this->size];
        head = nullptr;
        tail = nullptr;
        root = nullptr;
    }

    /**
     * Methods : 
     * 
     * getHash : calculates the hash of a given key
     * 
     */
    int getHash(int key)
    {
        // A simple hash function is used
        // returns key mod size
        return key % size;
    }
};