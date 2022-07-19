#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <conio.h>

typedef struct billData{
    char name[20];
    int quantity;
    int unitPrice;
} billData;

typedef struct customerData{
    char name[30];
    char number[12];
    char email[40];
    char date[12];
    int itemType;
} customerData;

//TODO CHECK FSCANF FUNCTION

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
    printf("\n============================================\n");
    return;
}

void saveInvoice(billData **bills, customerData *customer, int *total, int customerNo){
    char c;
    int l = 0;
    printf("\n Do You want to save this invoice? (y/n): ");
    scanf(" %c",&c);
    if(c == 'y' || c == 'Y'){
        FILE *fp;
        fp = fopen("invoice.txt", "a");
        fprintf(fp, "=============QUINTET Restaurant=============");
        fprintf(fp, "\n%s",customer[customerNo].date);
        fprintf(fp, "\nInvoice To: %s",customer[customerNo].name);
        fprintf(fp, "\nCustomer No: %s",customer[customerNo].number);
        fprintf(fp, "\nCustomer Email-ID: %s",customer[customerNo].email);
        fprintf(fp, "\n============================================");
        fprintf(fp, "\nItem\t\t    Qty\t\tTotal");
        fprintf(fp, "\n============================================");
        for(int i = 0; i<customer[customerNo].itemType; i++){
            l=strlen(bills[customerNo][i].name);
            fprintf(fp, "\n%s",bills[customerNo][i].name);
            for(int j = 0; j < 20-l; j++)
            {
                    fprintf(fp, " ");
            }
            fprintf(fp, "%d",bills[customerNo][i].quantity);
            fprintf(fp, "\t\t %d",bills[customerNo][i].quantity*bills[customerNo][i].unitPrice); 
        }
        fprintf(fp, "\n============================================");
        fprintf(fp, "\nSub Total\t\t\t %d",total[customerNo]);
        fprintf(fp, "\nDiscount(@10)\t\t         %f",(float)(total[customerNo]*10/100));
        fprintf(fp, "\n             \t\t         ============");
        fprintf(fp, "\nNet Total    \t\t         %d",total[customerNo]-total[customerNo]*10/100);
        fprintf(fp, "\nCGST (@9%)   \t\t         %f",(float)(total[customerNo]*9/100));
        fprintf(fp, "\nSGST (@9%)   \t\t         %f",(float)(total[customerNo]*9/100));
        fprintf(fp, "\n============================================");
        fprintf(fp, "\nGrand Total  \t\t         %f",(float)(total[customerNo]+total[customerNo]*9/100+total[customerNo]*9/100));
        fprintf(fp, "\n============================================\n\n\n");
        fclose(fp);
        return;
    }
    else{
        return;
    }
}

// HARSHIT, YOU HAVE TO COMPLETE THIS DESIGN FUNCTION NAMED "invoiceDesign"
// USE customerNo TO GET PARTICULAR CUSTOMER'S DETAILS
void invoiceDesign(billData **bills, customerData *customer, int *total, int customerNo){
    int l=0,a;
    char c;
    printf("\n=============QUINTET Restaurant=============");
    printf("\n%s",customer[customerNo].date);
    printf("\nInvoice To: %s",customer[customerNo].name);
    printf("\nContact No: %s",customer[customerNo].number);
    printf("\nCustomer Email-ID: %s",customer[customerNo].email);
    printf("\n============================================");
    printf("\nItem\t\t    Qty\t\tTotal");
    printf("\n============================================");
    for(int i = 0; i<customer[customerNo].itemType; i++){
        l=strlen(bills[customerNo][i].name);
        printf("\n%s",bills[customerNo][i].name);
        for(int j = 0; j < 20-l; j++){
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

    saveInvoice(bills, customer, total, customerNo);
    return;
}

// HARSH, YOU HAVE TO COMPLETE THIS CALCULATION FUNCTION NAMED "calculateBill"
// CALCULATE THE TOTAL WITHOUT GST INCLUDED
void calculateBill(billData **bills, customerData *customer, int *total, int customerNo){
    int totalBill = 0;
    FILE *fp;
    fp = fopen("dataTotal.txt", "a");
    for(int i = 0; i < customer[customerNo].itemType; i++){
        totalBill += bills[customerNo][i].quantity * bills[customerNo][i].unitPrice;
    }
    total[customerNo] = totalBill;
    fprintf(fp, "%d ", totalBill);
    // printf("\nTotal Bill: %d\n", totalBill);
    fclose(fp);
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
    int n;
    printf("\nSearch According to: 1. Number 2. Name");
    printf("\n Enter the choice: ");
    scanf("%d",&n);

    if(n==1){
        char searchNumber[30];
        int check = 0;
        printf("\nEnter the Number of customer: ");
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
    }
    else{
        char searchName[30];
        int p = 0;
        fflush(stdin);
        printf("\nEnter the Name of the customer: ");
        gets(searchName);
        for(int i = 0; searchName[i] != '\0'; i++){
            if(searchName[i] <= 90 && searchName[i] >= 65){
                    searchName[i] = searchName[i] + 32;
            }
        }
        for(int i = 0; i < *customerNo; i++){
            if(*customers[i].name <= 90 && *customers[i].name >= 65){
                *customers[i].name = *customers[i].name + 32;
            }
        }
        for(int i = 0; i < *customerNo; i++){
            p=strcmp(searchName,customers[i].name);
            if(p == 0){
                invoiceDesign(bills, customers, total, i);
            }    
        }
        if(p == 1){
            printf("\n Invalid Customer Name");
        }
    }

    // ADD LINE HERE
    printf("\n============================================");
    return;
}

//FUNCTION TO EDIT INVOICE OF PARTICULAR CUSTOMER
void editInvoice(billData **bills, customerData *customers, int *customerNo, int *total){
    char searchNumber[12];
    int choice = 0, check = 0;
    fflush(stdin);
    lable6:
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
        lable5:
            printf("\n============================================");

            printf("\nDo you want to: 1. Edit the Invoice 2. Delete the Invoice: ");
            scanf("%d", &choice);

            printf("\n============================================");
        FILE *fp;
        FILE *fp1;
        FILE *fp2;
        FILE *fp3;
        int editSameBill = 0;
        fp = fopen("dataCustomers.txt", "w");
        fp1 = fopen("dataBills.txt", "w");
        fp2 = fopen("dataTotal.txt", "w");
        fp3 = fopen("dataCustomerNo.txt", "w");
        switch (choice){
            case 1:
                for(int i = 0; i < *customerNo; i++){
                    fprintf(fp, "%s ", customers[i].name);
                    fprintf(fp, "%s ", customers[i].number);
                    fprintf(fp, "%s ", customers[i].email);
                    fprintf(fp, "%s ", customers[i].date);

                    if(!strncmp(searchNumber, customers[i].number, 10)){
                    invoiceDesign(bills, customers, total, i);
                    printf("\nWant to :\n   1. Add new ItemType\n   2. Edit ItemType\n   3. Delete ItemType\n   4. Exit\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);
                    // ADD LINE HERE
                    printf("\n============================================");
                    int srNo = 0;
                    switch (choice){
                        case 1:
                            for(int j = 0; j < customers[i].itemType; j++){
                                fprintf(fp1, "%s ", bills[i][j].name);
                                fprintf(fp1, "%d ", bills[i][j].quantity);
                                fprintf(fp1, "%d\n", bills[i][j].unitPrice);
                            }
                            customers[i].itemType++;
                            fprintf(fp3, "%d", *customerNo);
                            fprintf(fp, "%d\n", customers[i].itemType);
                            bills[i] = realloc(bills[i], sizeof(billData) * customers[i].itemType);
                            fflush(stdin);
                            printf("\nEnter the name of the %d item: ", customers[i].itemType);
                            // scanf("%s", bills[i][customers[i].itemType - 1].name);
                            gets(bills[i][customers[i].itemType - 1].name);
                            fprintf(fp1, "%s ", bills[i][customers[i].itemType - 1].name);
                            printf("\nEnter the quantity of the %d item: ", customers[i].itemType);
                            scanf("%d", &bills[i][customers[i].itemType - 1].quantity);
                            fprintf(fp1, "%d ", bills[i][customers[i].itemType - 1].quantity);
                            printf("\nEnter the unit price of the %d item: ", customers[i].itemType);
                            scanf("%d", &bills[i][customers[i].itemType - 1].unitPrice);
                            fprintf(fp1, "%d\n", bills[i][customers[i].itemType - 1].unitPrice);
                            calculateBill(bills, customers, total, i);
                            fprintf(fp2, "%d\n", total[i]);
                            invoiceDesign(bills, customers, total, i);
                            for(++i; i < *customerNo; i++){
                                for(int j = 0; j < customers[i].itemType; j++){
                                    fprintf(fp1, "%s ", bills[i][j].name);
                                    fprintf(fp1, "%d ", bills[i][j].quantity);
                                    fprintf(fp1, "%d\n", bills[i][j].unitPrice);
                                }
                                fprintf(fp2, "%d\n", total[i]);
                                fprintf(fp, "%s ", customers[i].name);
                                fprintf(fp, "%s ", customers[i].number);
                                fprintf(fp, "%s ", customers[i].email);
                                fprintf(fp, "%s ", customers[i].date);
                                fprintf(fp, "%d\n", customers[i].itemType);
                            }
                            printf("\n============================================");
                            printf("\nDo You want to Edit More: \n1. With Same Bill Number \n2. With Another Bill Number \n3. Exit");
                            printf("\nEnter You Choice: ");
                            scanf("%d", &editSameBill);
                            fclose(fp);
                            fclose(fp1);
                            fclose(fp2);
                            fclose(fp3);
                            // ADD LINE HERE
                            printf("\n============================================");
                            if(editSameBill == 1){
                                goto lable5;
                            }
                            else if(editSameBill == 2){
                                goto lable6;
                            }
                            else{
                                return;
                            }
                            return;

                        case 2:
                            fprintf(fp3, "%d", *customerNo);
                            printf("\nEnter Sr.No of items to be edited: ");
                            scanf("%d", &srNo);
                            for(int j = 0; j < srNo - 1; j++){
                                fprintf(fp1, "%s ", bills[i][j].name);
                                fprintf(fp1, "%d ", bills[i][j].quantity);
                                fprintf(fp1, "%d\n", bills[i][j].unitPrice);
                            }

                            // ADD LINE HERE
                            printf("\n============================================");
                            srNo--;
                            fflush(stdin);
                            printf("\nEnter the name of the %d item: ", srNo + 1);
                            // scanf("%s", bills[i][srNo].name);
                            gets(bills[i][srNo].name);
                            fprintf(fp1, "%s ", bills[i][srNo].name);
                            printf("\nEnter the quantity of the %d item: ", srNo + 1);
                            scanf("%d", &bills[i][srNo].quantity);
                            fprintf(fp1, "%d ", bills[i][srNo].quantity);
                            printf("\nEnter the unit price of the %d item: ", srNo + 1);
                            scanf("%d", &bills[i][srNo].unitPrice);
                            fprintf(fp1, "%d\n", bills[i][srNo].unitPrice);
                            calculateBill(bills, customers, total, i);
                            fprintf(fp2, "%d\n", total[i]);
                            invoiceDesign(bills, customers, total, i);
                            fprintf(fp, "%d\n", customers[i].itemType);
                            for(int j = srNo + 1; j < customers[i].itemType; j++){
                                fprintf(fp1, "%s ", bills[i][j].name);
                                fprintf(fp1, "%d ", bills[i][j].quantity);
                                fprintf(fp1, "%d\n", bills[i][j].unitPrice);
                            }
                            for(int n = i + 1; n < *customerNo; n++){
                                for(int j = 0; j < customers[i].itemType; j++){
                                fprintf(fp1, "%s ", bills[n][j].name);
                                fprintf(fp1, "%d ", bills[n][j].quantity);
                                fprintf(fp1, "%d\n", bills[n][j].unitPrice);
                                }
                                fprintf(fp2, "%d\n", total[n]);
                            }
                            for(++i; i < *customerNo; i++){
                                fprintf(fp, "%s ", customers[i].name);
                                fprintf(fp, "%s ", customers[i].number);
                                fprintf(fp, "%s ", customers[i].email);
                                fprintf(fp, "%s ", customers[i].date);
                                fprintf(fp, "%d\n", customers[i].itemType);
                            }
                            // ADD LINE HERE
                            printf("\n============================================");
                            printf("\nDo You want to Edit More: \n1. With Same Bill Number \n2. With Another Bill Number \n3. Exit");
                            printf("\nEnter You Choice: ");
                            scanf("%d", &editSameBill);
                            fclose(fp);
                            fclose(fp1);
                            fclose(fp2);
                            fclose(fp3);
                            // ADD LINE HERE
                            printf("\n============================================");
                            if(editSameBill == 1){
                                goto lable5;
                            }
                            else if(editSameBill == 2){
                                goto lable6;
                            }
                            else{
                                return;
                            }
                            return;

                        case 3:
                            fprintf(fp3, "%d", *customerNo);
                            printf("\n============================================");
                            printf("\nEnter Sr.No of items to be deleted: ");
                            scanf("%d", &srNo);
                            // ADD LINE HERE
                            printf("\n============================================");
                            srNo--;
                            fprintf(fp, "%d\n", customers[i].itemType - 1);
                            for(int j = 0; j < srNo; j++){
                                fprintf(fp1, "%s ", bills[i][j].name);
                                fprintf(fp1, "%d ", bills[i][j].quantity);
                                fprintf(fp1, "%d\n", bills[i][j].unitPrice);
                            }
                            for(int j = srNo; j < customers[i].itemType - 1; j++){
                                strcpy(bills[i][j].name, bills[i][j+1].name);
                                fprintf(fp1, "%s ", bills[i][j + 1].name);
                                bills[i][j].quantity = bills[i][j+1].quantity;
                                fprintf(fp1, "%d ", bills[i][j + 1].quantity);
                                bills[i][j].unitPrice = bills[i][j+1].unitPrice;
                                fprintf(fp1, "%d\n", bills[i][j + 1].unitPrice);
                            }
                            customers[i].itemType--;
                            calculateBill(bills, customers, total, i);
                            fprintf(fp2, "%d\n", total[i]);
                            invoiceDesign(bills, customers, total, i);
                            for(int n = i + 1; n < *customerNo; n++){
                                for(int j = 0; j < customers[i].itemType; j++){
                                fprintf(fp1, "%s ", bills[n][j].name);
                                fprintf(fp1, "%d ", bills[n][j].quantity);
                                fprintf(fp1, "%d\n", bills[n][j].unitPrice);
                                }
                                fprintf(fp2, "%d\n", total[n]);
                                fprintf(fp, "%s ", customers[n].name);
                                fprintf(fp, "%s ", customers[n].number);
                                fprintf(fp, "%s ", customers[n].email);
                                fprintf(fp, "%s ", customers[n].date);
                                fprintf(fp, "%d\n", customers[n].itemType);
                            }
                            // ADD LINE HERE
                            printf("\n============================================");
                            printf("\nDo You want to Edit More: \n1. With Same Bill Number \n2. With Another Bill Number \n3. Exit");
                            printf("\nEnter You Choice: ");
                            scanf("%d", &editSameBill);
                            fclose(fp);
                            fclose(fp1);
                            fclose(fp2);
                            fclose(fp3);
                            // ADD LINE HERE
                            printf("\n============================================");
                            if(editSameBill == 1){
                                goto lable5;
                            }
                            else if(editSameBill == 2){
                                goto lable6;
                            }
                            else{
                                return;
                            }
                            return;
                            
                        case 4:
                            for(i; i < *customerNo; i++){
                                fprintf(fp, "%s ", customers[i].name);
                                fprintf(fp, "%s ", customers[i].number);
                                fprintf(fp, "%s ", customers[i].email);
                                fprintf(fp, "%s ", customers[i].date);
                                fprintf(fp, "%d\n", customers[i].itemType);
                                fprintf(fp2, "%d\n", total[i]);
                                for(int j = 0; j < customers[i].itemType; j++){
                                    fprintf(fp1, "%s ", bills[i][j].name);
                                    fprintf(fp1, "%d ", bills[i][j].quantity);
                                    fprintf(fp1, "%d\n", bills[i][j].unitPrice);
                                }
                            }
                            fprintf(fp3, "%d", *customerNo);
                            fclose(fp);
                            fclose(fp1);
                            fclose(fp2);
                            fclose(fp3);
                            return;
                        }
                    }
                    for(int j = 0; j < customers[i].itemType; j++){
                        fprintf(fp1, "%s ", bills[i][j].name);
                        fprintf(fp1, "%d ", bills[i][j].quantity);
                        fprintf(fp1, "%d\n", bills[i][j].unitPrice);
                    }
                    fprintf(fp2, "%d\n", total[i]);
                    fprintf(fp, "%d\n", customers[i].itemType);
                }

            case 2:
                for(int i = 0; i < *customerNo; i++){
                    if(!strncmp(searchNumber, customers[i].number, 10)){
                        if(i == *customerNo - 1){
                            *customerNo = *customerNo - 1;
                            printf("\nInvoice deleted successfully\n");
                            break;
                        }
                        for(int j = i; j < *customerNo - 1; j++){
                                bills[j] = bills[j+1];
                                customers[j] = customers[j+1];
                                total[j] = total[j+1];
                        }
                        *customerNo = *customerNo - 1;
                        printf("\nInvoice deleted successfully\n");
                        for(int j = 0; j < customers[i].itemType; j++){
                            fprintf(fp1, "%s ", bills[i][j].name);
                            fprintf(fp1, "%d ", bills[i][j].quantity);
                            fprintf(fp1, "%d\n", bills[i][j].unitPrice);
                        }
                        fprintf(fp2, "%d\n", total[i]);
                        fprintf(fp, "%s ", customers[i].name);
                        fprintf(fp, "%s ", customers[i].number);
                        fprintf(fp, "%s ", customers[i].email);
                        fprintf(fp, "%s ", customers[i].date);
                        fprintf(fp, "%d\n", customers[i].itemType);
                    }
                    else{
                        fprintf(fp, "%s ", customers[i].name);
                        fprintf(fp, "%s ", customers[i].number);
                        fprintf(fp, "%s ", customers[i].email);
                        fprintf(fp, "%s ", customers[i].date);
                        fprintf(fp, "%d\n", customers[i].itemType);
                        fprintf(fp2, "%d\n", total[i]);
                        for(int j = 0; j < customers[i].itemType; j++){
                            fprintf(fp1, "%s ", bills[i][j].name);
                            fprintf(fp1, "%d ", bills[i][j].quantity);
                            fprintf(fp1, "%d\n", bills[i][j].unitPrice);
                        }
                    }
                }
            fprintf(fp3, "%d", *customerNo);
            fclose(fp);
            fclose(fp1);
            fclose(fp2);
            fclose(fp3);
            printf("\n============================================");
            printf("\nDo You want to Edit More: \n1. With Same Bill Number \n2. With Another Bill Number \n3. Exit");
            printf("\nEnter You Choice: ");
            scanf("%d", &editSameBill);
            // ADD LINE HERE
            printf("\n============================================");
            if(editSameBill == 1){
                goto lable5;
            }
            else if(editSameBill == 2){
                goto lable6;
            }
            else{
                return;
            }
        }
    return;
}

//FUNCTION TO CREATE NEW INVOICE
void invoice(customerData *customer, int *customerNo, int *total, billData **bills){
    int check = 0;
    strcpy(customer[*customerNo].date, __DATE__);
    FILE *fp;
    fp = fopen("dataCustomers.txt", "a");
    lable2:
        // gets(customer[*customerNo].name);
        printf("\nEnter Your Name: ");
        scanf("%s", customer[*customerNo].name);
        // gets(customer[*customerNo].name);
        if(strlen(customer[*customerNo].name) == 0){
            printf("\nPlease Enter Your Name\n");
            goto lable2;
        }
        fprintf(fp, "%s ", customer[*customerNo].name);

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
        fprintf(fp, "%s ", customer[*customerNo].number);
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
        fprintf(fp, "%s ", customer[*customerNo].email);
        fprintf(fp, "%s ", customer[*customerNo].date);
    // fclose(fp);
        // ADD LINE HERE
        printf("\n============================================");
    printf("\n");
    printf("\nEnter the number of Different items you have ordered: ");
    scanf("%d", &customer[*customerNo].itemType);
    fprintf(fp, "%d\n", customer[*customerNo].itemType);
    fclose(fp);
    // ADD LINE HERE
    printf("\n============================================\n");
    billData *bill = calloc(customer[*customerNo].itemType, sizeof(billData));
    bills[*customerNo] = bill;
    fp = fopen("dataBills.txt", "a");
    for(int i = 0; i < customer[*customerNo].itemType; i++){
        printf("\nEnter the name of the item %d: ", i+1);
        // gets(bills[*customerNo][i].name);
        fflush(stdin);
        gets(bills[*customerNo][i].name);
        fprintf(fp, "%s ", bills[*customerNo][i].name);
        printf("Enter the quantity of the item %d: ", i+1);
        scanf("%d", &bill[i].quantity);
        fprintf(fp, "%d ", bill[i].quantity);
        printf("Enter the unit price of the item %d: ", i+1);
        scanf("%d", &bill[i].unitPrice);
        fprintf(fp, "%d\n", bill[i].unitPrice);
        // ADD LINE HERE
        printf("\n============================================\n");
    }
    fclose(fp);
    calculateBill(bills, customer, total, *customerNo);
    invoiceDesign(bills, customer, total, *customerNo);
    // ADD LINE HERE
    printf("\n============================================");
    *customerNo += 1;
    fp = fopen("dataCustomerNo.txt", "w");
    fprintf(fp, "%d", *customerNo);
    fclose(fp);
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

void readData(billData **bills, customerData *customers, int *total, int *customerNo){
    FILE *fp;
    fp = fopen("dataCustomerNo.txt", "r");
    fscanf(fp, "%d", customerNo);
    fclose(fp);

    fp = fopen("dataTotal.txt", "r");
    for(int i = 0; i < *customerNo; i++){
        fscanf(fp, "%d", &total[i]);
    }
    fclose(fp);

    fp = fopen("dataCustomers.txt", "r");
    for(int i = 0; i < *customerNo; i++){
        fscanf(fp, "%s ", customers[i].name);
        fscanf(fp, "%s ", customers[i].number);
        fscanf(fp, "%s ", customers[i].email);
        fgets(customers[i].date, 12, fp);
        fscanf(fp, "%d", &customers[i].itemType);
    }
    fclose(fp);

    fp = fopen("dataBills.txt", "r");
    for(int i = 0; i < *customerNo; i++){
        billData *bill = calloc(customers[i].itemType, sizeof(billData));
        bills[i] = bill;
        for(int j = 0; j < customers[i].itemType; j++){
            fscanf(fp, "%s ", bills[i][j].name);
            fscanf(fp, "%d ", &bills[i][j].quantity);
            fscanf(fp, "%d", &bills[i][j].unitPrice);
        }
    }
    fclose(fp);
    return;
}

void login()
{
	int a=0,i=0;
    char uname[10],c=' '; 
    char pword[10],code[10];
    char user[10]="user";
    char pass[10]="WTF!!!";
    do{
        system("cls");
        printf("\n  =========================  LOGIN FORM  =========================  ");
        printf(" \n                       ENTER USERNAME:-");
        scanf("%s", &uname); 
        printf(" \n                       ENTER PASSWORD:-");
        while(i<10){
            pword[i]=getch();
            c=pword[i];
            if(c==13) break;
            else printf("*");
            i++;
        }
        pword[i]='\0';
        //char code=pword;
        i=0;
        //scanf("%s",&pword); 
            if(strcmp(uname,"user")==0 && strcmp(pword,"WTF!!!")==0){
        printf("  \n\n\n       WELCOME TO OUR SYSTEM !!!! LOGIN IS SUCCESSFUL");
        printf("\n\n\n\t\t\t\tPress any key to continue...");
        getch();//holds the screen
        break;
        }
        else{
            printf("\n        SORRY !!!!  LOGIN IS UNSUCCESSFUL");
            a++;
            getch();//holds the screen
        }
    }
    while(a<=2);
        if (a>2)
        {
            printf("\nSorry you have entered the wrong username and password for four times!!!");
            
            getch();
            
            }
            system("cls");	
}

int main(){
    int customerNo = 0, Continue = 0;
    customerData *customers = calloc(100, sizeof(customerData));
    // customerArr[customerNo] = *customers;
    int *total = calloc(100, sizeof(int));
    billData **bills = calloc(100, sizeof(billData *));
    readData(bills, customers, total, &customerNo);
    login();
    lable1:
        Choice(bills, customers, total, &customerNo);
    // ADD LINE HERE
    lable8:
        printf("\n============================================\n");
        printf("\nYou want to continue? (1. Yes 2. No): ");
        scanf("%d", &Continue);
        printf("\n============================================\n");
    if(Continue == 1){
        Continue = 0;
        goto lable1;
    }
    else if(Continue == 2){
        Continue = 0;
        printf("\nThank you for using our service.\n");
        // ADD LINE HERE
        printf("\n============================================");
        return 0;
    }
    else{
        Continue = 0;
        printf("\nInvalid Input.\n");
        goto lable8;            
    }
    return 0;
}