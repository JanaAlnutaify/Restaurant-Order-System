#ifndef ORDERSYSTEM_H
#define ORDERSYSTEM_H

#include <iostream>
#include <string>
using namespace std;

// Order structure
struct Order {
    int orderId;
    string customerName;
    string itemList;
    string status; // Pending, Completed, Canceled
    double totalPrice;
    Order *left;
    Order *right;

    Order(int id, string name, string items, double price, string stat = "Pending")
        : orderId(id), customerName(name), itemList(items), totalPrice(price), status(stat), left(NULL), right(NULL) {}
};

// Node structure for Queue and Stack
struct Node {
    Order *order;
    Node *next;
    Node(Order *o) : order(o), next(NULL) {}
};

// Queue Implementation (for Pending Orders)
class OrderQueue {
private:
    Node *front;
    Node *rear;

public:
    OrderQueue() : front(NULL), rear(NULL) {}

    bool isEmpty() {
        return front == NULL;
    }

    void enqueue(Order *order) {
        Node *newNode = new Node(order);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    Order *dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return NULL;
        }
        Node *temp = front;
        Order *order = temp->order;
        front = front->next;
        if (!front) rear = NULL;
        delete temp;
        return order;
    }

    Order *peek() {
        return isEmpty() ? NULL : front->order;
    }
};

// Stack Implementation (for Canceled Orders)
class OrderStack {
private:
    Node *top;

public:
    OrderStack() : top(NULL) {}

    bool isEmpty() {
        return top == NULL;
    }

    void push(Order *order) {
        Node *newNode = new Node(order);
        newNode->next = top;
        top = newNode;
    }

    Order *pop() {
        if (isEmpty()) {
            cout << "Stack is empty.\n";
            return NULL;
        }
        Node *temp = top;
        Order *order = temp->order;
        top = top->next;
        delete temp;
        return order;
    }

    Order *peek() {
        return isEmpty() ? NULL : top->order;
    }
};

// Binary Search Tree Implementation (for Orders)
class OrderTree {
private:
    Order *root;

    Order *insert(Order *node, Order *newOrder) {
        if (!node) return newOrder;
        if (newOrder->customerName < node->customerName)
            node->left = insert(node->left, newOrder);
        else
            node->right = insert(node->right, newOrder);
        return node;
    }

    void inOrder(Order *node) {
        if (!node) return;
        inOrder(node->left);
        cout << "Order ID: " << node->orderId << ", Customer: " << node->customerName
             << ", Items: " << node->itemList << ", Price: $" << node->totalPrice
             << ", Status: " << node->status << endl;
        inOrder(node->right);
    }

    Order *search(Order *node, const string& name) {
        if (!node || node->customerName == name) return node;
        if (name < node->customerName)
            return search(node->left, name);
        return search(node->right, name);
    }

public:
    OrderTree() : root(NULL) {}

    void addOrder(Order *newOrder) {
        root = insert(root, newOrder);
    }

    void displayOrders() {
        inOrder(root);
    }

    Order *searchOrder(const string &name) {
        return search(root, name);
    }
};

// Main Restaurant Order System
class RestaurantOrderSystem {
private:
    OrderQueue pendingOrders;
    OrderStack canceledOrders; 
    OrderTree orderTree;    
    int nextOrderId = 1;

public:
    void addOrder();
    void processNextOrder();
    void cancelOrder();
    void viewCanceledOrders();
    void searchOrder();
    void displayAllOrders();
};

#endif
