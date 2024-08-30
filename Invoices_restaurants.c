#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct items {
    char item[30];
    float price;
    int qty;
};

struct orders {
    char customer[50];
    char date[30];
    int numOfItems;
    struct items itm[50];
    float totalPaid;
    float balance;
    float discount;
};

const char *menuItems[] = {
    "Pepper Barbecue",
    "Chicken Fiesta",
    "Deluxe Veggie",
    "Paneer Tikka",
    "Margherita Pizza",
    "Cheese Garlic Bread",
    "Chocolate Lava Cake",
    "Coke",
    "Water Bottle",
    "Spicy Hot Wings",
    "Chili Paneer",
    "Szechuan Noodles",
    "Spicy Potato Wedges",
    "Hot Garlic Bread"
};

const float menuPrices[] = {
    220.0, // Pepper Barbecue
    270.0, // Chicken Fiesta
    180.0, // Deluxe Veggie
    200.0, // Paneer Tikka
    150.0, // Margherita Pizza
    90.0,  // Cheese Garlic Bread
    120.0, // Chocolate Lava Cake
    75.0,  // Coke
    50.0,  // Water Bottle
    300.0, // Spicy Hot Wings
    250.0, // Chili Paneer
    220.0, // Szechuan Noodles
    100.0, // Spicy Potato Wedges
    95.0   // Hot Garlic Bread
};

void displayMenu() {
    printf("\n\t\t*** MENU ***\n");
    printf("---------------------------------------\n");
    printf("Item No.\tItem\t\t\tPrice\n");
    printf("---------------------------------------\n");
    for(int i = 0; i < (int)(sizeof(menuItems) / sizeof(menuItems[0])); i++) {
        printf("%d\t\t%-20s\t%.2f\n", i + 1, menuItems[i], menuPrices[i]);
    }
    printf("---------------------------------------\n");
}

void generateBillHeader(char name[50], char date[30]){
    printf("\n\n");
    printf("\t    The Pizza Place");
    printf("\n\tMarthahalli, Bangalore");
    printf("\n\t   Mobile: 9876543210");
    printf("\nInvoice No.: 530");
    printf("\nDate: %s", date);
    printf("\nBill To: %s", name);
    printf("\n---------------------------------------\n");
    printf("Items\t\tQty\tRate\tAmount\n");
    printf("---------------------------------------\n");
}

void generateBillBody(char item[30], int qty, float price){
    printf("%-15s %5d %10.2f %10.2f\n", item, qty, price, qty * price);
}

void generateBillFooter(float total, float discount, float totalPaid){
    float discountedTotal = total * ((100 - discount) / 100);
    float sgst = 0.12 * discountedTotal;
    float cgst = 0.12 * discountedTotal;
    float grandTotal = discountedTotal + sgst + cgst;
    float balance = totalPaid - grandTotal;

    printf("\n---------------------------------------");
    printf("\nSub Total\t\t\t%.2f", total);
    printf("\nDiscount\t\t\t%.2f%%", discount);
    printf("\nAfter Discount\t\t\t%.2f", discountedTotal);
    printf("\nSGST @12%%\t\t\t%.2f", sgst);
    printf("\nCGST @12%%\t\t\t%.2f", cgst);
    printf("\n---------------------------------------");
    printf("\nGrand Total\t\t\t%.2f", grandTotal);
    printf("\nTotal Paid\t\t\t%.2f", totalPaid);
    printf("\nBalance\t\t\t\t%.2f", balance);
    printf("\n---------------------------------------\n");
}

void editInvoice(){
    char name[50];
    int invoiceFound = 0;
    struct orders order;
    FILE *fp, *temp;

    printf("Enter the name of the customer whose invoice you want to edit:\t");
    fgets(name, 50, stdin);
    name[strlen(name) - 1] = 0;

    fp = fopen("RestaurantBill.dat", "rb");
    temp = fopen("TempBill.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while(fread(&order, sizeof(struct orders), 1, fp)){
        if(!strcmp(order.customer, name)){
            invoiceFound = 1;
            float tot = 0;
            generateBillHeader(order.customer, order.date);
            for(int i = 0; i < order.numOfItems; i++){
                generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                tot += order.itm[i].qty * order.itm[i].price;
            }
            generateBillFooter(tot, order.discount, order.totalPaid);

            // Allow editing
            printf("\nEdit the number of items:\t");
            scanf("%d", &order.numOfItems);
            fgetc(stdin); // Clear newline character from buffer
            for(int i = 0; i < order.numOfItems; i++){
                displayMenu();
                int itemNo;
                printf("\nEnter the new item number for item %d:\t", i + 1);
                scanf("%d", &itemNo);
                fgetc(stdin); // Clear newline character from buffer
                if(itemNo > 0 && itemNo <= (int)(sizeof(menuItems) / sizeof(menuItems[0]))){
                    strcpy(order.itm[i].item, menuItems[itemNo - 1]);
                    order.itm[i].price = menuPrices[itemNo - 1];
                    printf("Enter the new quantity for %s:\t", order.itm[i].item);
                    scanf("%d", &order.itm[i].qty);
                } else {
                    printf("Invalid item number, please try again.\n");
                    i--; // retry current item
                }
            }

            // Recalculate totals
            printf("\nEnter the new discount percentage:\t");
            scanf("%f", &order.discount);
            printf("\nEnter the new total amount paid:\t");
            scanf("%f", &order.totalPaid);

            // Save the updated invoice
            fwrite(&order, sizeof(struct orders), 1, temp);
            printf("\nInvoice updated successfully!\n");
        } else {
            fwrite(&order, sizeof(struct orders), 1, temp);  // Save other invoices unchanged
        }
    }

    fclose(fp);
    fclose(temp);

    remove("RestaurantBill.dat");
    rename("TempBill.dat", "RestaurantBill.dat");

    if(!invoiceFound){
        printf("Sorry, no invoice found for %s\n", name);
    }
}

int main(){
    int opt, n, itemNo;
    struct orders ord;
    struct orders order;
    char saveBill = 'y', contFlag = 'y';
    FILE *fp;

    while(contFlag == 'y'){
        float total = 0;
        int invoiceFound = 0;
        printf("\t============The Pizza Place============");
        printf("\n\nPlease select your preferred operation");
        printf("\n\n1. View Menu");
        printf("\n2. Generate Invoice");
        printf("\n3. Show all Invoices");
        printf("\n4. Search Invoice");
        printf("\n5. Edit Invoice");
        printf("\n6. Exit");

        printf("\n\nYour choice:\t");
        scanf("%d", &opt);
        fgetc(stdin); // Clear newline character from buffer

        switch(opt){
            case 1:
                displayMenu();
                break;

            case 2:
                printf("\nPlease enter the name of the customer:\t");
                fgets(ord.customer, 50, stdin);
                ord.customer[strlen(ord.customer) - 1] = 0;
                strcpy(ord.date, __DATE__);
                printf("\nPlease enter the number of items:\t");
                scanf("%d", &n);
                ord.numOfItems = n;

                for(int i = 0; i < n; i++){
                    fgetc(stdin); // Clear newline character from buffer
                    displayMenu();
                    printf("\nEnter the item number for item %d:\t", i + 1);
                    scanf("%d", &itemNo);

                    if(itemNo > 0 && itemNo <= (int)(sizeof(menuItems) / sizeof(menuItems[0]))){
                        strcpy(ord.itm[i].item, menuItems[itemNo - 1]);
                        ord.itm[i].price = menuPrices[itemNo - 1];
                        printf("Enter the quantity for %s:\t", ord.itm[i].item);
                        scanf("%d", &ord.itm[i].qty);
                        total += ord.itm[i].qty * ord.itm[i].price;
                    } else {
                        printf("Invalid item number, please try again.\n");
                        i--;
                    }
                }

                printf("\nEnter the discount percentage:\t");
                scanf("%f", &ord.discount);

                printf("\nEnter the total amount paid:\t");
                scanf("%f", &ord.totalPaid);

                generateBillHeader(ord.customer, ord.date);
                for(int i = 0; i < ord.numOfItems; i++){
                    generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
                }
                generateBillFooter(total, ord.discount, ord.totalPaid);

                printf("\nDo you want to save the invoice [y/n]:\t");
                scanf(" %c", &saveBill);

                if(saveBill == 'y'){
                    fp = fopen("RestaurantBill.dat", "ab");
                    if (fp != NULL){
                        fwrite(&ord, sizeof(struct orders), 1, fp);
                        fclose(fp);
                        printf("\nSuccessfully saved the invoice\n");
                    } else {
                        printf("\nError saving the invoice\n");
                    }
                }
                break;

            case 3:
                fp = fopen("RestaurantBill.dat", "rb");
                if(fp == NULL){
                    printf("\nSorry, no invoices available!\n");
                } else {
                    printf("\n  *****Your Previous Invoices*****\n");
                    while(fread(&order, sizeof(struct orders), 1, fp)){
                        float tot = 0;
                        generateBillHeader(order.customer, order.date);
                        for(int i = 0; i < order.numOfItems; i++){
                            generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                            tot += order.itm[i].qty * order.itm[i].price;
                        }
                        generateBillFooter(tot, order.discount, order.totalPaid);
                    }
                    fclose(fp);
                }
                break;

            case 4:
                fp = fopen("RestaurantBill.dat", "rb");
                if(fp == NULL){
                    printf("\nSorry, no invoices available!\n");
                } else {
                    char name[50];
                    printf("\nEnter the name of the customer:\t");
                    fgets(name, 50, stdin);
                    name[strlen(name) - 1] = 0;
                    while(fread(&order, sizeof(struct orders), 1, fp)){
                        float tot = 0;
                        if(!strcmp(order.customer, name)){
                            invoiceFound = 1;
                            generateBillHeader(order.customer, order.date);
                            for(int i = 0; i < order.numOfItems; i++){
                                generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                                tot += order.itm[i].qty * order.itm[i].price;
                            }
                            generateBillFooter(tot, order.discount, order.totalPaid);
                        }
                    }
                    if(!invoiceFound){
                        printf("Sorry, no invoice found for %s\n", name);
                    }
                    fclose(fp);
                }
                break;

            case 5:
                editInvoice();
                break;

            case 6:
                printf("\nThank you for visiting The Pizza Place!\n\n");
                exit(0);
                break;

            default:
                printf("Invalid option. Please try again.\n");
                break;
        }

        printf("\nDo you want to perform another operation? [y/n]:\t");
        scanf(" %c", &contFlag);
        fgetc(stdin); // Clear newline character from buffer
    }

    printf("\nThank you for visiting The Pizza Place!\n\n");
    return 0;
}
