#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct billData{
    char name[20];
    int quantity;
    int unitPrice;
} billData;

typedef struct customerData{
    char name[30];
    char number[12];
    char email[40];
} customerData;

void preferredOption(int *choice){
    for(int i = 0; i < 21; i++){
        if(i == 11){
            printf("HJHP Restaurant");
        }
        else{
            printf("=");
        }
    }
    printf("\n");
    printf("\nPlease Select Your Preferred Option:\n");
    printf("1. Generate Invoice\n");
    printf("2. Show all Invoices\n");
    printf("3. Search Invoice\n");
    printf("4. Exit\n");
    printf("\nEnter your choice: ");
    scanf("%d", choice);
    return;
}

// HARSHIT, YOU HAVE TO COMPLETE THIS DESIGN FUNCTION NAMED "invoiceDesign"
// USE customerNo TO GET PARTICULAR CUSTOMER'S DETAILS
void invoiceDesign(billData *bill, customerData *customer, int *total, int customerNo, int itemType){

}

// HARSH, YOU HAVE TO COMPLETE THIS CALCULATION FUNCTION NAMED "calculateBill"
// CALCULATE THE TOTAL WITHOUT GST INCLUDED
void calculateBill(billData *bill, int *total, int customerNo, int itemType){
    int totalBill = 0;
    for(int i = 0; i < itemType; i++){
        totalBill += bill[i].quantity * bill[i].unitPrice;
    }
    *total = totalBill;
    // printf("\nTotal Bill: %d\n", totalBill);
    return;
}

void showAllInvoices(){

}

void searchInvoice(){

}

void invoice(customerData *customer, int *customerNo, int *total){
    int itemsType = 0;
    printf("\nEnter Your Name: ");
    scanf("%s", customer[*customerNo].name);
    printf("\nEnter Your Phone Number: ");
    scanf("%d", &customer[*customerNo].number);
    printf("\nEnter Your Email: ");
    scanf("%s", customer[*customerNo].email);
    printf("\n");
    printf("\nEnter the number of Different items you hove ordered: ");
    scanf("%d", &itemsType);
    billData *bills = calloc(100, sizeof(billData));
    billData *bill = calloc(itemsType, sizeof(billData));
    bills[*customerNo] = *bill;
    for(int i = 0; i < itemsType; i++){
        printf("\nEnter the name of the item %d: ", i+1);
        scanf("%s", bill[i].name);
        printf("Enter the quantity of the item %d: ", i+1);
        scanf("%d", &bill[i].quantity);
        printf("Enter the unit price of the item %d: ", i+1);
        scanf("%d", &bill[i].unitPrice);
    }
    calculateBill(bill, total, *customerNo, itemsType);
    invoiceDesign(bill, customer, total, *customerNo, itemsType);
    *customerNo++;
    return;
}

int main(){
    int choice = 0, customerNo = 0;
    // customerData *customerArr = calloc(20, sizeof(customerData *));
    customerData *customers = calloc(100, sizeof(customerData));
    // customerArr[customerNo] = *customers;
    int *total = calloc(100, sizeof(int));
    while(choice != 1 && choice != 2 && choice != 3 && choice != 4)
    {
        preferredOption(&choice);
    }
    switch(choice){
        case 1:
            invoice(customers, &customerNo, total);
            break;
        case 2:
            showAllInvoices();
            break;
        case 3:
            searchInvoice();
            break;
        case 4:
            return 0;
    }
    return 0;
}