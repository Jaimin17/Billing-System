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
    int itemType;
} customerData;

//FUNCTION TO ASK USER WHAT FUNCTION HE WANT TO PERFORM
void preferredOption(int *choice){
    printf("==========QUINTET Restaurant==========\n");
    printf("\n");
    printf("\nPlease Select Your Preferred Option:\n");
    printf("1. Generate Invoice\n");
    printf("2. Show all Invoices\n");
    printf("3. Search Invoice\n");
    printf("4. Edit Invoice\n");
    printf("5. Exit\n");
    printf("\nEnter your choice: ");
    scanf("%d", choice);

    // ADD LINE HERE
    return;
}

// HARSHIT, YOU HAVE TO COMPLETE THIS DESIGN FUNCTION NAMED "invoiceDesign"
// USE customerNo TO GET PARTICULAR CUSTOMER'S DETAILS
void invoiceDesign(billData **bills, customerData *customer, int *total, int customerNo){
    int l=0,a;
    printf("\n=============QUINTET Restaurant=============");
    printf("\n%s",customer[customerNo].date);
    printf("\nInvoice To: %s",customer[customerNo].name);
    printf("\n============================================");
    printf("\nItem\t\t    Qty\t\tTotal");
    printf("\n============================================");
    for(int i = 0; i<customer[customerNo].itemType; i++){
           l=strlen(bills[customerNo][i].name);
           printf("\n%s",bills[customerNo][i].name);
           for(int j = 0; j < 20-l; j++)
           {
                printf(" ");
           }
           printf("%d",bills[customerNo][i].quantity);
           printf("\t\t %d",bills[customerNo][i].quantity*bills[customerNo][i].unitPrice); 
        }
    printf("\n============================================");
    printf("\nSub Total\t\t\t %d",total[customerNo]);
    printf("\nDiscount(@10)\t\t         %f",(float)(total[customerNo]*10/100));
    printf("\n             \t\t         ============");
    printf("\nNet Total    \t\t         %d",total[customerNo]-total[customerNo]*10/100);
    printf("\nCGST (@9%)   \t\t         %f",(float)(total[customerNo]*9/100));
    printf("\nSGST (@9%)   \t\t         %f",(float)(total[customerNo]*9/100));
    printf("\n============================================");
    printf("\nGrand Total  \t\t         %f",(float)(total[customerNo]+total[customerNo]*9/100+total[customerNo]*9/100));
    printf("\n============================================\n");
}

// HARSH, YOU HAVE TO COMPLETE THIS CALCULATION FUNCTION NAMED "calculateBill"
// CALCULATE THE TOTAL WITHOUT GST INCLUDED
void calculateBill(billData **bills, customerData *customer, int *total, int customerNo){
    int totalBill = 0;
    for(int i = 0; i < customer[customerNo].itemType; i++){
        totalBill += bills[customerNo][i].quantity * bills[customerNo][i].unitPrice;
    }
    total[customerNo] = totalBill;
    printf("\nTotal Bill: %d\n", totalBill);
    return;
}

//FUNCTION TO PRINTF ALL INVOICES
void showAllInvoices(billData **bills, customerData *customers, int *customerNo, int *total){
    for(int i = 0; i < *customerNo; i++){
        invoiceDesign(bills, customers, total, i);
    }
    return;
}

//FUNCTION TO PRINT INVOICE OF PARTICULAR CUSTOMER
void searchInvoice(billData **bills, customerData *customers, int *customerNo, int *total){
    char searchNumber[30];
    int check = 0;
    printf("\nEnter the number of the customer: ");
    scanf("%s", searchNumber);
        for(int i = 0; i < 10; i++){
            if(searchNumber[i] < '0' || searchNumber[i] > '9'){
                check = 1;
                break;
            }
        }
        if(strlen(searchNumber) != 10 || check == 1){
            printf("\nInvalid Phone Number\n");
            searchInvoice(bills, customers, customerNo, total);
        }
    for(int i = 0; i < *customerNo; i++){
        if(!strncmp(searchNumber, customers[i].number, 10)){
            invoiceDesign(bills, customers, total, i);
        }
    }
    // ADD LINE HERE
    return;
}

//FUNCTION TO EDIT INVOICE OF PARTICULAR CUSTOMER
void editInvoice(billData **bills, customerData *customers, int *customerNo, int *total){
    char searchNumber[12];
    int choice = 0, check = 0;
    lable6:
        fflush(stdin);
        printf("\nEnter the number of the customer: ");
        // scanf("%s", searchNumber);
        gets(searchNumber);
        for(int i = 0; i < 10; i++){
            if(searchNumber[i] < '0' || searchNumber[i] > '9'){
                check = 1;
                break;
            }
        }
        if(strlen(searchNumber) != 10 || check == 1){
            printf("\nInvalid Phone Number\n");
            goto lable6;
        }
        // ADD LINE HERE
        int editSameBill = 0;
        for(int i = 0; i < *customerNo; i++){
            lable5:
                if(!strncmp(searchNumber, customers[i].number, 10)){
                    invoiceDesign(bills, customers, total, i);
                    printf("\nWant to :\n   1. Add new ItemType\n   2. Edit ItemType\n   3. Delete ItemType\n   4. Delete Bill\n   5. Exit\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);
                    // ADD LINE HERE
                    int srNo = 0;
                    switch (choice)
                    {
                    case 1:
                        customers[i].itemType++;
                        bills[i] = realloc(bills[i], sizeof(billData) * customers[i].itemType);
                        fflush(stdin);
                        printf("\nEnter the name of the %d item: ", customers[i].itemType);
                        // scanf("%s", bills[i][customers[i].itemType - 1].name);
                        gets(bills[i][customers[i].itemType - 1].name);
                        printf("\nEnter the quantity of the %d item: ", customers[i].itemType);
                        scanf("%d", &bills[i][customers[i].itemType - 1].quantity);
                        printf("\nEnter the unit price of the %d item: ", customers[i].itemType);
                        scanf("%d", &bills[i][customers[i].itemType - 1].unitPrice);
                        calculateBill(bills, customers, total, i);
                        invoiceDesign(bills, customers, total, i);
                        printf("\nDo You want to Edit More: \n1. With Same Bill Number \n2. With Another Bill Number \n3. Exit");
                        printf("\nEnter You Choice: ");
                        scanf("%d", &editSameBill);
                        // ADD LINE HERE
                        if(editSameBill == 1){
                            goto lable5;
                        }
                        else if(editSameBill == 2){
                            goto lable6;
                        }
                        else{
                            return;
                        }

                    case 2:
                        printf("\nEnter Sr.No of items to be edited: ");
                        scanf("%d", &srNo);
                        // ADD LINE HERE
                        srNo--;
                        fflush(stdin);
                        printf("\nEnter the name of the %d item: ", srNo + 1);
                        // scanf("%s", bills[i][srNo].name);
                        gets(bills[i][srNo].name);
                        printf("\nEnter the quantity of the %d item: ", srNo + 1);
                        scanf("%d", &bills[i][srNo].quantity);
                        printf("\nEnter the unit price of the %d item: ", srNo + 1);
                        scanf("%d", &bills[i][srNo].unitPrice);
                        calculateBill(bills, customers, total, i);
                        invoiceDesign(bills, customers, total, i);
                        // ADD LINE HERE
                        printf("\nDo You want to Edit More: \n1. With Same Bill Number \n2. With Another Bill Number \n3. Exit");
                        printf("\nEnter You Choice: ");
                        scanf("%d", &editSameBill);
                        // ADD LINE HERE
                        if(editSameBill == 1){
                            goto lable5;
                        }
                        else if(editSameBill == 2){
                            goto lable6;
                        }
                        else{
                            return;
                        }

                    case 3:
                        printf("\nEnter Sr.No of items to be deleted: ");
                        scanf("%d", &srNo);
                        // ADD LINE HERE
                        srNo--;
                        for(int j = srNo; j < customers[i].itemType - 1; j++){
                            strcpy(bills[i][j].name, bills[i][j+1].name);
                            bills[i][j].quantity = bills[i][j+1].quantity;
                            bills[i][j].unitPrice = bills[i][j+1].unitPrice;
                        }
                        customers[i].itemType--;
                        calculateBill(bills, customers, total, i);
                        invoiceDesign(bills, customers, total, i);
                        // ADD LINE HERE
                        printf("\nDo You want to Edit More: \n1. With Same Bill Number \n2. With Another Bill Number \n3. Exit");
                        printf("\nEnter You Choice: ");
                        scanf("%d", &editSameBill);
                        // ADD LINE HERE
                        if(editSameBill == 1){
                            goto lable5;
                        }
                        else if(editSameBill == 2){
                            goto lable6;
                        }
                        else{
                            return;
                        }

                    case 4:
                        for(int j = i; j < *customerNo - 1; j++){
                            bills[j] = bills[j+1];
                            customers[j] = customers[j+1];
                            total[j] = total[j+1];
                        }
                        *customerNo = *customerNo - 1;
                        printf("\nInvoice deleted successfully\n");
                        printf("\nDo You want to Edit More: \n1. With Same Bill Number \n2. With Another Bill Number \n3. Exit");
                        printf("\nEnter You Choice: ");
                        scanf("%d", &editSameBill);
                        // ADD LINE HERE
                        if(editSameBill == 1){
                            goto lable5;
                        }
                        else if(editSameBill == 2){
                            goto lable6;
                        }
                        else{
                            return;
                        }

                    case 5:
                        return;
                    }
                }
        }
}

//FUNCTION TO CREATE NEW INVOICE
void invoice(customerData *customer, int *customerNo, int *total, billData **bills){
    int check = 0;
    strcpy(customer[*customerNo].date, __DATE__);
    lable2:
        // gets(customer[*customerNo].name);
        fflush(stdin);
        printf("\nEnter Your Name: ");
        // scanf("%s", customer[*customerNo].name);
        gets(customer[*customerNo].name);
        if(strlen(customer[*customerNo].name) == 0){
            printf("\nPlease Enter Your Name\n");
            goto lable2;
        }
    lable3:
        fflush(stdin);
        printf("\nEnter Your Phone Number: ");
        // scanf("%s", &customer[*customerNo].number);
        gets(customer[*customerNo].number);
        for(int i = 0; i < 10; i++){
            if(customer[*customerNo].number[i] < '0' || customer[*customerNo].number[i] > '9'){
                check = 1;
                break;
            }
        }
        if(strlen(customer[*customerNo].number) != 10 || check == 1){
            printf("\nInvalid Phone Number\n");
            goto lable3;
        }
    lable4:
        printf("\nEnter Your Email: ");
        // scanf("%s", customer[*customerNo].email);
        gets(customer[*customerNo].email);
        int len = strlen(customer[*customerNo].email);
        // printf("%d", len);
        char test[] = ".com";
        // int x = strcmp(&customer[*customerNo].email[len-4], test);
        // printf("%d", x);
        if(strcmp(&customer[*customerNo].email[len-4], test)){
            printf("\nInvalid Email\n");
            goto lable4;
        }
        // ADD LINE HERE
    printf("\n");
    printf("\nEnter the number of Different items you have ordered: ");
    scanf("%d", &customer[*customerNo].itemType);
    // ADD LINE HERE
    billData *bill = calloc(customer[*customerNo].itemType, sizeof(billData));
    bills[*customerNo] = bill;
    for(int i = 0; i < customer[*customerNo].itemType; i++){
        printf("\nEnter the name of the item %d: ", i+1);
        // gets(bills[*customerNo][i].name);
        fflush(stdin);
        gets(bills[*customerNo][i].name);
        printf("Enter the quantity of the item %d: ", i+1);
        scanf("%d", &bill[i].quantity);
        printf("Enter the unit price of the item %d: ", i+1);
        scanf("%d", &bill[i].unitPrice);
        // ADD LINE HERE
    }
    calculateBill(bills, customer, total, *customerNo);
    invoiceDesign(bills, customer, total, *customerNo);
    // ADD LINE HERE
    *customerNo += 1;
    return;
}

//FUNCTION TO MAKE DECISION BASED ON USER CHOICE
void Choice(billData **bills, customerData *customers, int *total, int *customerNo){
    int choice = 0, Continue = 0;
    while(choice > 5 || choice < 1){
        preferredOption(&choice);
    }
    switch(choice){
        case 1:
            invoice(customers, customerNo, total, bills);
            break;
        case 2:
            showAllInvoices(bills, customers, customerNo, total);
            break;
        case 3:
            searchInvoice(bills, customers, customerNo, total);
            break;
        case 4:
            editInvoice(bills, customers, customerNo, total);
            break;
        case 5:
            return;
    }
}

int main(){
    int customerNo = 0, Continue = 0;
    customerData *customers = calloc(100, sizeof(customerData));
    // customerArr[customerNo] = *customers;
    int *total = calloc(100, sizeof(int));
    billData **bills = calloc(100, sizeof(billData *));
    lable1:
        Choice(bills, customers, total, &customerNo);
    // ADD LINE HERE
    printf("\n");
    printf("You want to continue? (1. Yes 2. No) \n");
    scanf("%d", &Continue);
    if(Continue == 1){
        Continue = 0;
        goto lable1;
    }
    else if(Continue == 2){
        Continue = 0;
        printf("\nThank you for using our service.\n");
        // ADD LINE HERE
        return 0;
    }
    else{
        Continue = 0;
        printf("\nInvalid Input.\n");
        goto lable1;;            
    }
    return 0;
}