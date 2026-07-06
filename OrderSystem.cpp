#include "OrderSystem.h"

void RestaurantOrderSystem::addOrder() {
    string customerName, itemList;
    double totalPrice;
    cout << "Enter customer name: ";
    cin.ignore();
    getline(cin, customerName);
    cout << "Enter item list: ";
    getline(cin, itemList);
    cout << "Enter total price: $";
    cin >> totalPrice;

    Order *newOrder = new Order(nextOrderId++, customerName, itemList, totalPrice);
    pendingOrders.enqueue(newOrder);
    orderTree.addOrder(newOrder);
    cout << "Order added successfully.\n";
}

void RestaurantOrderSystem::processNextOrder() {
    Order *order = pendingOrders.dequeue();
    if (order) {
        order->status = "Completed";
        cout << "Processed Order ID: " << order->orderId << ", Customer: " << order->customerName << endl;
    }
}

void RestaurantOrderSystem::cancelOrder() {
    Order *order = pendingOrders.dequeue();
    if (order) {
        order->status = "Canceled";
        canceledOrders.push(order);
        cout << "Order ID: " << order->orderId << " has been canceled and moved to the canceled stack.\n";
    }
}

void RestaurantOrderSystem::viewCanceledOrders() {
    cout << "Canceled Orders:\n";
    while (!canceledOrders.isEmpty()) {
        Order *order = canceledOrders.pop();
        cout << "Order ID: " << order->orderId << ", Customer: " << order->customerName
        << ", Status: " << order->status << endl;
    }
}

void RestaurantOrderSystem::searchOrder() {
    string customerName;
    cout << "Enter customer name to search: ";
    cin.ignore();
    getline(cin, customerName);

    Order *order = orderTree.searchOrder(customerName);
    if (order) {
        cout << "Order found: Order ID: " << order->orderId << ", Items: " << order->itemList
             << ", Price: $" << order->totalPrice << ", Status: " << order->status << endl;
    } else {
        cout << "No order found for customer: " << customerName << endl;
    }
}

void RestaurantOrderSystem::displayAllOrders() {
    orderTree.displayOrders();
}
