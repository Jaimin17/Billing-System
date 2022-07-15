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
    char date[10];
} customerData;

void preferredOption(int *choice){
    // for(int i = 0; i < 21; i++){
    //     if(i == 11){
    //         printf("QUINTET Restaurant");
    //     }
    //     else{
    //         printf("=");
    //     }
    // }
    printf("==========QUINTET Restaurant==========\n");
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
void invoiceDesign(billData **bills, customerData *customer, int *total, int customerNo, int itemType){
    
    printf("\n=============QUINTET Restaurant=============");
    // printf("\n%s",customer[customerNo].date);
    printf("\nInvoice To: %s",customer[customerNo].name);
    printf("\n============================================");
    printf("\nItem\t\tQty\t\t  Total");
    printf("\n============================================");
    for(int i = 0; i < itemType; i++){
        printf("\n%s\t\t%d\t\t  %d",bills[customerNo][i].name,bills[customerNo][i].quantity,bills[customerNo][i].quantity * bills[customerNo][i].unitPrice);
    }
    printf("\n============================================");
    printf("\nSub Total\t\t\t  %d",total[customerNo]);
    printf("\nDiscount(@10)\t\t          %f",(float)(total[customerNo]*10/100));
    printf("\n             \t\t          ===========");
    printf("\nNet Total    \t\t          %d",total[customerNo]-total[customerNo]*10/100);
    printf("\nCGST (@9%)   \t\t          %f",(float)(total[customerNo]*9/100));
    printf("\nSGST (@9%)   \t\t          %f",(float)(total[customerNo]*9/100));
    printf("\n============================================");
    printf("\nGrand Total  \t\t          %f",(float)(total[customerNo]+total[customerNo]*9/100+total[customerNo]*9/100));
    printf("\n============================================");
}

// HARSH, YOU HAVE TO COMPLETE THIS CALCULATION FUNCTION NAMED "calculateBill"
// CALCULATE THE TOTAL WITHOUT GST INCLUDED
void calculateBill(billData **bills, int *total, int customerNo, int itemType){
    int totalBill = 0;
    for(int i = 0; i < itemType; i++){
        totalBill += bills[customerNo][i].quantity * bills[customerNo][i].unitPrice;
    }
    total[customerNo] = totalBill;
    printf("\nTotal Bill: %d\n", totalBill);
    return;
}

void showAllInvoices(billData **bills, customerData *customers, int *itemsType, int *customerNo, int *total){
    for(int i = 0; i < customerNo; i++){
        
    }
    //TODO 
}

void searchInvoice(billData **bills, customerData *customers, int *itemsType, int *customerNo){
    //TODO 
    
    
    printf("\nEnter the Customer Name : ");
    scanf("%s", &customer);
    
}

void invoice(customerData *customer, int *customerNo, int *total, billData **bills){
    int itemsType = 0;
    printf("\nEnter Your Name: ");
    scanf("%s", customer[*customerNo].name);
    printf("\nEnter Your Phone Number: ");
    scanf("%d", &customer[*customerNo].number);
    printf("\nEnter Your Email: ");
    scanf("%s", customer[*customerNo].email);
    printf("\n");
    printf("\nEnter the number of Different items you have ordered: ");
    scanf("%d", &itemsType);
    billData *bill = calloc(itemsType, sizeof(billData));
    bills[*customerNo] = bill;
    for(int i = 0; i < itemsType; i++){
        printf("\nEnter the name of the item %d: ", i+1);
        scanf("%s", bill[i].name);
        printf("Enter the quantity of the item %d: ", i+1);
        scanf("%d", &bill[i].quantity);
        printf("Enter the unit price of the item %d: ", i+1);
        scanf("%d", &bill[i].unitPrice);
    }
    calculateBill(bills, total, *customerNo, itemsType);
    invoiceDesign(bills, customer, total, *customerNo, itemsType);
    *customerNo++;
    return;
}

int main(){
    int choice = 0, customerNo = 0;
    // customerData *customerArr = calloc(20, sizeof(customerData *));
    customerData *customers = calloc(100, sizeof(customerData));
    // customerArr[customerNo] = *customers;
    int *total = calloc(100, sizeof(int));
    billData **bills = calloc(100, sizeof(billData *));
    while(choice != 1 && choice != 2 && choice != 3 && choice != 4)
    {
        preferredOption(&choice);
    }
    switch(choice){
        case 1:
            invoice(customers, &customerNo, total, bills);
            break;
        case 2:
            // showAllInvoices();
            break;
        case 3:
            searchInvoice();
            break;
        case 4:
            return 0;
    }
    return 0;
}
