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
 * 2020-April-11	[SP]: put() method completed
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

    // Method to add the Node in the Hash Table
    bool putInHashTable(int key, int value, Node *nodeToBeAdded)
    {
        // If the node to be added is nullptr
        if (!nodeToBeAdded)
        {
            // Addition to the Hash Table failed
            // return false
            return false;
        }

        // If the node to be added is not nullptr
        // Find the hash of the key
        int hash = getHash(key);

        // If the table[hash] is full
        if (table[hash])
        {
            // It means that another Node with the same key
            // already exists
            // Add the new Node before the old Node
            // Point the node to be added's nextInMap to
            // the existing Node at table[hash]
            nodeToBeAdded->nextInMap = table[hash];
        }

        // If the table[hash] is not full
        // Or the new Node has been added before the
        // old Node
        // Simply point the table[hash] to the new Node
        table[hash] = nodeToBeAdded;

        // Addition to the Hash Table successful
        // Return true
        return true;
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
    Node *addToTree(Node *nodeToBeAdded, Node *currentNode, bool &status)
    {
        // If the currentNode is nullptr
        if (!currentNode)
        {
            // Assign the nodeToBeAdded to the currentNode
            currentNode = nodeToBeAdded;

            // Successful addition
            // Make the status to true
            status = true;

            // Return currentNode
            return currentNode;
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
     * 
     * put : adds the Entry to the Super Structure (wrapper function)
     * 
     * putInHashTable : adds the Entry to the Hash Table
     * 
     * addToLinkedList : adds the Node to the Linked List
     * 
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
        // Create a newNode
        Node *newNode = new Node(key, value);

        // If the allocation failed
        if (!newNode)
        {
            // Return false
            return false;
        }

        // Allocation successful
        // Add the Node to the Hash Table
        if (!putInHashTable(key, value, newNode))
        {
            // Addition to the Hash Table failed
            // Return false
            return false;
        }

        // Add the Node in the Linked List
        if (!addToLinkedList(newNode))
        {
            // Addition to the Linked List failed
            // return false
            return false;
        }

        // Check the status of addition to Tree
        bool status = false;

        // Add the Node in the BST
        root = addToTree(newNode, root, status);

        // If the addition to the Tree failed
        if (!status)
        {
            // Return false
            return false;
        }
    }

    // Print Method
    void print();
};