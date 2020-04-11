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
        // Make every pointer in the Array of Pointers nullptr
        for (int i = 0; i < this->size; i++)
            table[i] = nullptr;

        // Initialize rest of the fields
        head = nullptr;
        tail = nullptr;
        root = nullptr;
    }

    /**
     * Methods : 
     * 
     * getHash : calculates the hash of a given key
     * put : adds an Entry (Node) in the Hash Table and then calls
     *       other methods like addToLinkedList and addToTree
     *       to add the Entry (Node) there 
     * 
     * addToLinkedList : adds the Node to the Linked List
     * addToTree : adds the Node to the tree 
     *
     */
    // Method to calculate the hash of the given key
    int getHash(int key)
    {
        // A simple hash function is used
        // returns key mod size
        return key % size;
    }

    // Method to add the Entry to the Super Structure
    bool put(int key, int value)
    {
        // Create a new Entry
        Node *newNode = new Node(key, value);

        // If the allocation has been successful
        if (!newNode)
        {
            // The allocation has been unsuccesful
            // return false
            return false;
        }

        // The allocation has been successful
        // Find the hash of the key
        int hash = getHash(key);

        // Add the Entry to the Hash Table
        // If the table[hash] is nullptr
        if (!table[hash])
        {
            // An Entry already exists
            // Simple add the new Entry before the old one
            // 1 - newNode->next points to table[hash] (old Entry)
            newNode->next = table[hash];

            // Now point the table[hash] to the new Node
            table[hash] = newNode;
        }

        // Add the Node in the Linked List
        if (!addToLinkedList(newNode))
        {
            // Addition to the Linked List failed
            // return false
            return false;
        }
        // Add the Node in the BST
    }

    // Method to add the Node to the Linked List
    bool addToLinkedList(Node *nodeToBeAdded)
    {
        // If the head and tail are null
        if (!head && !tail)
        {
            // It means this is the first Node
            // Point the head to this Node
            head = nodeToBeAdded;
        }

        // If this is not the first Node
        else
        {
            // Add the new Node after the tail
            tail->next = nodeToBeAdded;
        }

        // Point the tail to the new Node
        tail = nodeToBeAdded;

        // Addition successful
        // return true
        return true;
    }

    // Method to add the Node to the Tree
    Node *addToTree(Node *nodeToBeAdded, Node *currentNode, int &status)
    {
        // If the currentNode is nullptr
        if (!currentNode)
        {
            // Assign the nodeToBeAdded to the currentNode
            currentNode = nodeToBeAdded;

            // Successful addition
            // Make the status to true
            status = true;
        }

        // If the nodeToBeAdded's value is greater than the value
        // of nodeToBeAdded
        if (nodeToBeAdded->value > currentNode->value)
        {
            // Call the addToTree function again with
            // currentNode->right
            currentNode->right = addToTree(nodeToBeAdded, currentNode->right, status);
        }

        // If the nodeToBeAdded's value is less than or equal to
        // the currentNode's value
        else
        {
            // Call the addToTree function with
            // currentNode->left
            currentNode->left = addToTree(nodeToBeAdded, currentNode->left, status);
        }

        // Return the currentNode
        return currentNode;
    }
};