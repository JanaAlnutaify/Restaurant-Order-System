#include "OrderSystem.h"

int main() {
    RestaurantOrderSystem system;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add Order\n";
        cout << "2. Process Next Order\n";
        cout << "3. Cancel Next Order\n";
        cout << "4. View Canceled Orders\n";
        cout << "5. Search Order\n";
        cout << "6. Display All Orders\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            system.addOrder();
            break;
        case 2:
            system.processNextOrder();
            break;
        case 3:
            system.cancelOrder();
            break;
        case 4:
            system.viewCanceledOrders();
            break;
        case 5:
            system.searchOrder();
            break;
        case 6:
            system.displayAllOrders();
            break;
        case 7:
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
