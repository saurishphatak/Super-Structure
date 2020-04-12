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
 * 2020-April-12	[SP]: put() method modified.
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
private:
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

        // If the nodeToBeAdded's key is greater than the key
        // of nodeToBeAdded
        if (nodeToBeAdded->key > currentNode->value)
        {
            // Call the addToTree function again with
            // currentNode->right
            currentNode->right = addToTree(nodeToBeAdded, currentNode->right, status);
        }

        // If the nodeToBeAdded's key is less than or equal to
        // the currentNode's key
        else
        {
            // Call the addToTree function with
            // currentNode->left
            currentNode->left = addToTree(nodeToBeAdded, currentNode->left, status);
        }

        // Return the currentNode
        return currentNode;
    }

    // Method to remove a key-value pair from the Linked List
    bool removeFromLinkedList(int key)
    {
        // Search for the given key
        for (Node *currentNode = head, *peechu = head; currentNode; currentNode = currentNode->next)
        {
            // If the value is found
            if (key == currentNode->key)
            {
                // If this is the ONLY Node in the Linked List
                if (head == tail)
                {
                    // Simply make the head and tail nullptr
                    head = tail = nullptr;

                    // Return true
                    return true;
                }

                // If this Node is the FIRST Node in the Linked List
                if (head == currentNode)
                {
                    // Simply make the head point to the next Node
                    head = head->next;

                    // Return true
                    return true;
                }

                // If this is the LAST Node in the Linked List
                if (tail == currentNode)
                {
                    // Simply point the tail to the previous Node
                    tail = peechu;

                    // Make peechu's next as null
                    peechu->next = nullptr;

                    // Return true
                    return true;
                }

                // If the node is in BETWEEN
                // Point the peechu's next to the next Node
                peechu->next = currentNode->next;

                // Return true
                return true;
            }

            // Key not found
            // Make the peechu jump ahead
            peechu = currentNode;
        }

        // Key not found in the Linked List
        // Return false
        return false;
    }

    // Method to remove a key-value pair from the Tree
    Node *removeFromTree(Node *currentNode, int key, bool &status)
    {
        // If the currentNode is nullptr
        if (!currentNode)
        {
            // Return currentNode
            return currentNode;
        }

        // If the given key is more than the currentNode's key
        if (key > currentNode->key)
        {
            // Call the removeFromTree function with currentNode->right
            currentNode->right = removeFromTree(currentNode->right, key, status);
        }

        // If the given key is less than the currentNode's key
        if (key < currentNode->key)
        {
            // Call the removeFromTree function with currentNode->left
            currentNode->left = removeFromTree(currentNode->left, key, status);
        }

        // If the key was found
        if (key == currentNode->key)
        {
            // If this node has no children
            if (!currentNode->left && !currentNode->right)
            {
                // The currentNode has been successfully removed from the Tree
                status = true;

                // Simply pass nullptr to the parent Node
                return nullptr;
            }

            // If this node has a left child ONLY
            if (currentNode->left && !currentNode->right)
            {
                // The currentNode has been successfully removed from the Tree
                status = true;

                // Simply pass the left child to the parent Node
                return currentNode->left;
            }

            // If this node has a right child ONLY
            if (!currentNode->left && currentNode->right)
            {
                // The currentNode has been successfully removed from the Tree
                status = true;

                // Simply pass the right child to the parent Node
                return currentNode->right;
            }

            // If this node has both the children
            if (currentNode->left && currentNode->right)
            {
                // Find the Successor Node
                Node *successor = currentNode->right;

                while (successor->left)
                {
                    successor = successor->left;
                }

                // Now first take care of the successor's child
                currentNode->right = removeFromTree(currentNode->right, successor->key, status);

                // If the successor's child has been taken care of
                if (status)
                {
                    // The successor node has now been disconnected.
                    // Simply copy the left and right of th currentNode
                    // to the successor Node
                    // This way, we won't have to "move" the successor Node
                    successor->left = currentNode->left;
                    successor->right = currentNode->right;

                    // Make the status true
                    // as the currentNode has successfully been removed from the
                    // Tree
                    status = true;
                }

                // If the successor's child hasn't been taken care of
                // It means that the removal of currentNode has been ONE GIGANTIC FAIL

                // Return the successor
                return successor;
            }
        }

        // Everything done
        // Return the currentNode
        return currentNode;
    }

    // Method to remove a key-value pair from the Super Structure
    bool removeFromSuperStructure(int key)
    {
        // Find the hash of the given value
        int hash = getHash(key);

        // If the table[hash] is empty
        if (!table[hash])
        {
            // Then it means that there is only ONE
            // Entry in this row
            // Simply delete this Entry
            delete table[hash];

            // Make the table[hash] nullptr
            table[hash] = nullptr;

            // Removal from Super Structure successfull
            // return true
            return true;
        }

        // If the table[hash] is not empty
        if (table[hash])
        {
            // It means that there are MORE THAN ONE
            // Entries in this row

            // Capture the current Entry pointed to
            // by the table[hash]
            Node *currentEntry = table[hash];

            // Simply point the table[hash] to the
            // next Entry in the row
            table[hash] = currentEntry->next;

            // Delete the current Entry
            delete currentEntry;

            // Removal from Super Structure successful
            // return true
            return true;
        }

        // Removal from the Super Structure unsuccessful
        // return false
        return false;
    }

    // Method to print values in Ascending Order
    void printAscendingOrder(Node *currentNode)
    {
        // If the currentNode is nullptr
        if (!currentNode)
        {
            // Simply return
            return;
        }
        // Go to the currentNode's left first
        printAscendingOrder(currentNode->left);

        // Now print the value
        cout << "[Key : " << currentNode->key << ", Value : " << currentNode->value << "]" << endl;

        // Now go to the currentNode's right
        printAscendingOrder(currentNode->right);
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
     * removeFromLinkedList : removes a node from the Linked List
     * 
     * removeFromTree : removes a node from the Tree
     * 
     * removeFromSuperStructure : removed an entry from the Super Structure 
     * 
     * printInAscendingOrder : prints the key-value pair in Ascending Order
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

    // Print LL
    void printLL();

    // Print Tree
    void printT();
};