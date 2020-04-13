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
 * 2020-April-12	[SP]: remove() method completed.
 * 2020-April-12	[SP]: printInAscendingOrder() method completed.
 * 2020-April-12	[SP]: printInsertionSequence() method completed.
 * 2020-April-12	[SP]: printHashTable() method completed.
 * 2020-April-12	[SP]: put() method modified.
 * 2020-April-11	[SP]: put() method completed.
 * 2020-April-09	[SP] : Created.
 * --------------------------------------------------------------------------------
 */

#include <iostream>

using namespace std;

// Define a Node
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

    /**
     * Methods : 
     * 
     * getHash() : calculates the hash of the given key
     * 
     * addToTree : adds the key-value pair to the Tree
     * 
     * removeFromLinkedList : removes the key-value pair from the Linked List
     * 
     * removeFromTree : removes the key-value pair from the Tree
     * 
     * removeFromHashTable : removes the key-value from the Hash Table
     * 
     * printAscendingOrder : prints the key-value pair in Ascending Order on
     *                       the basis of key
     */

    // Method to generate the hash of the key
    int getHash(int key)
    {
        // Return key % size
        return key % this->size;
    }

    // Method to add the Node to the Tree
    Node *addToTree(Node *nodeToBeAdded, Node *currentNode)
    {
        // If the currentNode is nullptr
        if (!currentNode)
        {
            // Assign the nodeToBeAdded to the currentNode
            currentNode = nodeToBeAdded;

            // Return currentNode
            return currentNode;
        }

        // If the nodeToBeAdded's key is greater than the key
        // of nodeToBeAdded
        if (nodeToBeAdded->key > currentNode->key)
        {
            // Call the addToTree function again with
            // currentNode->right
            currentNode->right = addToTree(nodeToBeAdded, currentNode->right);
        }

        // If the nodeToBeAdded's key is less than or equal to
        // the currentNode's key
        else
        {
            // Call the addToTree function with
            // currentNode->left
            currentNode->left = addToTree(nodeToBeAdded, currentNode->left);
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

    // Method to remove a key-value pair from the Hash Table
    bool removeFromHashTable(int key)
    {
        // Find the hash of the given value
        int hash = getHash(key);

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
            table[hash] = currentEntry->nextInMap;

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
     * put : adds the Entry to the Super Structure (wrapper function)
     * 
     * printInAscedingOrder : wrapper function for print the key-value pairs
     *                        in Ascending Order
     * 
     * printHashTable : prints the Entire Hash Table
     * 
     * printInsertionSequence : prints the key-value pair in the order they were inserted
     * 
     * remove : removes the key-value pair from the Super Structure
     */

    // Method to add the Entry to the Super Structure
    bool put(int keyToBeAdded, int value)
    {
        // Create a newNode
        Node *newNode = new Node(keyToBeAdded, value);

        // If the allocation failed
        if (!newNode)
        {
            // Return false
            return false;
        }

        // Allocation successful
        // Get the hash of the key
        int hash = getHash(keyToBeAdded);

        // Check if the key already exists in the Hash Table
        for (Node *currentNode = table[hash]; currentNode; currentNode = currentNode->nextInMap)
        {
            // If the duplicate key is found
            // Return false
            // Addition to the Super Structure failed
            if (keyToBeAdded == currentNode->key)
                return false;
        }

        // Adding this key for the first time in the Hash Table
        newNode->nextInMap = table[hash];
        table[hash] = newNode;

        // If this is the first Node in the Linked List
        if (head == nullptr)
            head = newNode;

        // This is not the first Node in the Linked List
        else
            tail->next = newNode;

        // Move the tail ahead
        tail = newNode;

        // Finally, add the newNode in the Tree
        root = addToTree(newNode, root);

        // Addition complete
        // return true
        return true;
    }

    // Method that prints the key-value pair in Ascending Order
    void printInAscendingOrder()
    {
        cout << "\n\nAscending Order : " << endl;

        // Call the printAscending method and pass ther root
        printAscendingOrder(root);
    }

    // Method to print the Entire Hash Table
    void printHashTable()
    {
        cout << "\nHash Table : \n";

        // Go over each row
        for (int i = 0; i < this->size; i++)
        {
            // Print the row number
            cout << i << " ==> ";

            // Print all the Entries in that row
            for (Node *currentNode = table[i]; currentNode; currentNode = currentNode->nextInMap)
            {
                // Print the key-value pair
                cout << "[Key : " << currentNode->value << ", Value : " << currentNode->value << "] ";
            }

            // Change the line after a row has been printed
            cout << endl;
        }
    }

    // Method to print the Insertion Sequence
    void printInsertionSequence()
    {
        cout << "\n\nInsertion Sequence : " << endl;
        // Start from the head
        cout << "HEAD";

        // Go until current Node becomes null
        for (Node *currentNode = head; currentNode; currentNode = currentNode->next)
        {
            // Print the key-value pair
            cout << " ==> "
                 << "[Key : " << currentNode->key << ", Value : " << currentNode->value << "]";
        }

        // Once the Linked List has been printed
        // Print a blank line for better formatting
        cout << endl;
    }

    // Method to remove a key-value pair from Super Structure
    bool remove(int key)
    {
        // If the key-value pair is removed from the Linked List
        if (removeFromLinkedList(key))
        {
            // Remove the key-value from the Tree
            bool status = false;

            root = removeFromTree(root, key, status);

            // If the removal from the Tree is sucessful
            if (status)
            {
                // Finally, remove the key-value from the Hash Table
                // thereby removing it from the Super Structure itself
                if (removeFromHashTable(key))
                {
                    // Successful deletion from the Hash Table
                    // key-value pair removed from the Super Structure
                    // return true
                    return true;
                }
            }

            // Removal from Tree unsuccessful
            // return false
            return false;
        }

        // Removal from the Linked List unsuccessful
        // return false
        return false;
    }
};