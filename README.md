# Restaurant-Billing-System
This code is for a restaurant's billing system.

It allows you to:

1. **View the menu**: See the list of items available with their prices.
2. **Generate an invoice**: Create a bill for a customer based on what they ordered.
3. **Show all invoices**: Display all the invoices that have been saved.
4. **Search for an invoice**: Find a specific customer's invoice.
5. **Edit an invoice**: Make changes to an already saved invoice.
6. **Exit the program**: Stop running the program.


Let's go through the code step by step in a very simple and easy-to-understand way.

### Overview
This code is for a pizza restaurant billing system. It helps you do several things like showing the menu, creating a bill (invoice) for a customer, saving that bill, showing all bills, searching for a specific bill, and even editing a bill.

### Key Sections of the Code

1. **Structures (`struct`)**:
   - **`struct items`**: This is like a blueprint that describes an item on the menu. It includes:
     - `item[30]`: The name of the item (like "Pepper Barbecue").
     - `price`: The price of the item (like 220.0).
     - `qty`: How many of that item the customer orders.

   - **`struct orders`**: This is another blueprint that describes an order (or bill). It includes:
     - `customer[50]`: The name of the customer.
     - `date[30]`: The date when the order was made.
     - `numOfItems`: The number of different items in the order.
     - `itm[50]`: A list of the items ordered (using the `struct items`).
     - `totalPaid`: The total amount of money the customer paid.
     - `balance`: Any money that’s left after paying (if the customer paid more than needed).
     - `discount`: Any discount given to the customer.

2. **Menu Items and Prices**:
   - **`menuItems[]`**: This is a list of all the items you can order at the restaurant, like "Pepper Barbecue", "Coke", etc.
   - **`menuPrices[]`**: This is a list of prices for each of those items, in the same order as `menuItems[]`.

3. **Functions**:
   - **`displayMenu()`**: Shows the menu with all items and their prices.
   - **`generateBillHeader()`**: Prints the top part of the bill, showing the restaurant's name, date, and customer name.
   - **`generateBillBody()`**: Prints each item on the bill, showing the name, quantity, price, and total for that item.
   - **`generateBillFooter()`**: Prints the bottom part of the bill, showing the subtotal, discount, taxes, and the final amount the customer needs to pay.

4. **Main Program Flow**:
   - **Menu Display**:
     - When the program starts, it asks you what you want to do (like view the menu, create a bill, etc.).
     - If you choose to view the menu, it calls `displayMenu()` to show all the items and prices.
  
   - **Generate Invoice**:
     - You enter the customer's name.
     - You choose how many items you want to order and pick them from the menu.
     - You also enter the quantity for each item.
     - The program calculates the total amount, applies any discount, and shows you the final bill.
     - You can choose to save this bill to a file.
  
   - **Show All Invoices**:
     - If you want to see all the saved bills, the program reads them from the file and shows them to you.
  
   - **Search for an Invoice**:
     - If you want to find a specific bill, you enter the customer's name, and the program searches for it in the file.
     - If found, it shows the bill.

   - **Edit an Invoice**:
     - You can edit a saved bill by changing items, quantities, or the discount.
     - The program then saves the updated bill.

5. **File Handling**:
   - The bills (invoices) are saved in a file called `RestaurantBill.dat`.
   - When you edit a bill, the program temporarily saves the changes in a different file (`TempBill.dat`) and then replaces the old file with this new one.

### Summary
- **Menu**: Shows items and prices.
- **Generate Invoice**: Create a new bill.
- **Show All Invoices**: View all saved bills.
- **Search Invoice**: Find a specific bill.
- **Edit Invoice**: Make changes to an existing bill.



![Screenshot 2024-08-30 203929](https://github.com/user-attachments/assets/a6fc7120-d7ae-4702-9bdc-adf266e8a690)

![Screenshot 2024-08-30 203959](https://github.com/user-attachments/assets/669e2e0a-db2c-4ca1-9098-19738e8e1e16)

![Screenshot 2024-08-30 204020](https://github.com/user-attachments/assets/d54448be-a3d9-4b81-9816-71309d9870be)

![Screenshot 2024-08-30 204041](https://github.com/user-attachments/assets/5970b288-11f0-41ce-aec1-760a06d1281b)

![Screenshot 2024-08-30 204056](https://github.com/user-attachments/assets/557aed95-b8aa-4501-8c91-7f2c5f932647)

![Screenshot 2024-08-30 204115](https://github.com/user-attachments/assets/a03d1f39-230b-473d-b4db-04686624ddf9)







