# Boutique Management System

The **Boutique Management System** is an advanced application designed to streamline and enhance various aspects of boutique operations using Object-Oriented Programming (OOP) principles in C++. It offers a comprehensive suite of tools for inventory management, customer service, sales processes, and detailed reporting.

## Overview

The Boutique Management System provides efficient inventory management, enhanced customer service, streamlined sales processes, and detailed sales and performance reports. It leverages advanced OOP concepts to create a robust and scalable system that addresses the needs of boutique managers and staff.

## Features

### Efficient Inventory Management
- **Track and manage stock levels**: Monitor inventory to ensure the right items are always in stock.
- **Handle orders and deliveries**: Manage incoming and outgoing shipments effectively.

### Enhanced Customer Service
- **Maintain customer profiles**: Store detailed customer information and purchase history.
- **Personalized service**: Use customer data to provide tailored recommendations and improve satisfaction.

### Streamlined Sales Processes
- **Efficient point-of-sale transactions**: Reduce wait times and errors during checkout.

### Detailed Sales and Performance Reports
- **Generate insightful reports**: Analyze sales trends, inventory status, and customer behavior to make informed decisions.

## Functionalities

The system supports three types of users, each with specific privileges:

### Manager
- **Full control over the system**: Can manage inventory, employees, and customer profiles.
- **Access to all reports**: Can generate and view detailed sales, inventory, and performance reports.
- **User management**: Can add, remove, and update employee and customer information.
- **Order management**: Can approve, modify, and track orders and deliveries.

### Employee
- **Sales processing**: Can handle point-of-sale transactions and generate receipts.
- **Inventory assistance**: Can update stock levels and assist in managing deliveries.
- **Customer service**: Can view and update customer profiles and purchase histories.

### Customer
- **Shopping**: Can browse items and make purchases.
- **Profile management**: Can view and update their personal information.
- **Purchase history**: Can view their past purchases and receipts.

### Security
- **User authentication**: Each user logs in with a unique username and password.
- **Access control**: User actions are restricted based on their role.

## Concepts Used

The system is built using core OOP concepts, making it modular, extensible, and maintainable:
- **Classes**: Define objects for inventory, customers, sales, etc.
- **Encapsulation**: Protect data within classes and expose only necessary interfaces.
- **Inheritance**: Create a hierarchy of classes to reuse code and model relationships.
- **Polymorphism**: Allow objects to be treated as instances of their parent class.
- **Enum**: Define a set of named values to represent various statuses or types.
- **Abstract Classes**: Provide a base class that cannot be instantiated.
- **Pure Virtual Functions**: Ensure derived classes implement specific functions.
- **Exception Handling**: Manage errors gracefully and ensure system stability.
- **File Handling**: Read from and write to files for data persistence.

## Usage

1. **Inventory Management**: Add, update, and track items in stock. Manage orders and deliveries.
2. **Customer Management**: Maintain detailed profiles and purchase histories for each customer.
3. **Sales Transactions**: Process sales quickly and accurately.
4. **Reporting**: Generate detailed reports to gain insights into business performance.



## Installation

1. **Clone the repository**:
    ```sh
    git clone https://github.com/TashkeelPasha/boutique-management-system.git
    ```

2. **Navigate to the project directory**:
    ```sh
    cd boutique-management-system
    ```

3. **Compile the project**:
    ```sh
    g++ -o boutique_management main.cpp Inventory.cpp Customer.cpp Sales.cpp Report.cpp User.cpp
    ```

4. **Run the executable**:
    ```sh
    ./boutique_management
    ```

## Conclusion

The Boutique Management System offers comprehensive tools to manage various aspects of a boutique. From inventory control to customer management, it streamlines processes and helps in making informed decisions through detailed reporting. By integrating these functionalities, the system not only enhances operational efficiency but also contributes to better customer service and business growth.

## License

Free for all to use >>>> enjoy....:)
