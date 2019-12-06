/***
Programmed by: Tyrone Sta. Maria S11A 
Description: This program simulates a simple process in a restaurant.
Customer -> Waiter -> Chef then Chef -> Waiter -> Customer
Last modified: 12-06-19
[Ackwnoledgements:
https://fresh2refresh.com/c-programming/c-array-of-structures/
https://stackoverflow.com/questions/53056369/c-infinite-loop-when-char-input-instead-of-int] 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>

#define MAXCUST 20
#define MAX_ORDER 20
struct order
{
	short id;  // order id 
	short food; // food id from struct food 
	char status[1];	// status if food is served or cooked
} ;

struct customer
{
	short id; // customer number
	struct order order[3];
	short numOrder; // number of orders 
	char status[1]; // status if customer is waiting, eating or paid
	
	
};

struct food
{
	short id; // variable to identify which food item is ordered
	float price; 
	char name[10]; // the name of the food 
	
};

/* function declarations to avoid implicit declaration warning */

/* VOID FUNCTIONS */
void mainMenu(struct customer*, bool* boolRestoClose);
void customer(struct customer*, bool* boolRestoClosed);
void customerMenu (struct customer* ,int customerNumber, bool* boolRestoClosed);
void foodMenu(struct customer*, int customerNumber, bool* boolRestoClosed);
void orderList(struct customer*, int customerNumber, bool* boolRestoClosed);
void waiter (struct customer*, bool* boolRestoClosed);
void sendOrder (struct customer* arrCustomer, bool* boolRestoClosed);
void viewOrder(struct customer* arrCustomer, bool* boolRestoClosed);
void chef(struct customer* arrCustomer, bool* boolRestoClosed);
void cookOrder(struct customer* arrCustomer, bool* boolRestoClosed);
void chefViewOrder(struct customer* arrCustomer, bool* boolRestoClosed);
void chefDeliverOrder(struct customer* arrCustomer, bool* boolRestoClosed);
void waiterSendDish(struct customer* arrCustomer, bool* boolRestoClosed);
void customerPay(struct customer* arrCustomer, int customerNumber, bool* boolRestoClosed);
void waiterDisplayIncome(struct customer* arrCustomer, bool* boolRestoClosed);
void waiterCloseResto(struct customer*, bool* boolRestoClosed);

/* VALUE RETURNING FUNCTIONS*/
char* customerStatus (struct customer* arrCustomer, int customerNumber);
char* orderStatus (struct customer* arrCustomer, int customerNumber, int x);
short countCustomers (struct customer* arrCustomer);
short countOrders (struct customer* arrCustomer);
short countTotalCust (struct customer* arrCustomer);

/*	
FUNCTION DERIVED FROM :
https://stackoverflow.com/questions/53056369/c-infinite-loop-when-char-input-instead-of-int
@return(void) no return value 
get empty white spaces from char input to from an int input prompt to prevent infinite loop
*/
void 
empty_stdin(void)
{
	int c = getchar();
	while(c!='\n' && c!= EOF )
		c = getchar();
}


/*
This function returns the whole word of the order's status ex.
 O = Ordered, E = Eating, P = Pending, C = Cooked, D = Delivered, A = Paid.
 @param (struct*) arrCustomer is the pointer for the structure customer. This holds 
 the different data of the customer (customer id, orders, number of orders, status).
 @param (int) customerNumber (array index) 
 this indicates which customer's order should be read in the array index.
 @param (int) x (array index) this specifies the order that is read by the function 
 
 @return (String) returns a string of the corresponding character input.

*/
char
*orderStatus (struct customer* arrCustomer, int customerNumber, int x)
{
	char *cStatus = malloc(50);
	
	switch(arrCustomer[customerNumber - 1].order[x].status[0]){
		case 'O':
			strcpy(cStatus, "Ordered");
			break;
		case 'E':
			strcpy(cStatus, "Eating");
			break;
		case 'P':
			strcpy(cStatus, "Pending");
			break;
		case 'C':
			strcpy(cStatus, "Cooked");
			break;
		case 'D':
			strcpy(cStatus, "Delivered");
			break;
		case 'A':
			strcpy(cStatus, "Paid");
			break;
		default:
			strcpy(cStatus, "");
			break;
	}
	return cStatus; 
}

/*
This function returns the whole word of the customer's status ex.
E = Eating, P = Paid, W = Waiting.

 @param (struct*) arrCustomer is the pointer for the structure customer. This holds 
 the different data of the customer (customer id, orders, number of orders, status).
 @param (int) customerNumber (array index) 
 this indicates which customer's order should be read in the array index.
 
 @return (String) returns a string of the corresponding character input.

*/
char 
*customerStatus (struct customer* arrCustomer, int customerNumber)
{
	char* cStatus = malloc(50);
	switch(arrCustomer[customerNumber - 1].status[0]){
		case 'W':
			strcpy(cStatus, "Waiting");
			break;
		case 'E':
			strcpy(cStatus, "Eating");
			break;
		case 'P':
			strcpy(cStatus, "Paid");
			break;
	}
	return cStatus; 
}


/*
This function counts the current number of customers inside the restaurant (customers that haven't paid yet).
 @param (struct*) arrCustomer is the pointer for the structure customer. This holds 
 the different data of the customer (customer id, orders, number of orders, status).
 
 @return (short) returns an integer value of the current number of customers

*/

short 
countCustomers (struct customer* arrCustomer)
{
	short x;
	short nCustomerCount = 0;
	for(x = 0; x < MAXCUST; x++){
			if(arrCustomer[x].id > 0 && arrCustomer[x].status[0] != 'P')
				nCustomerCount++;
	}
	return nCustomerCount;
}


/*
This function counts the total number of orders that has been ordered, served, or paid.
 @param (struct*) arrCustomer is the pointer for the structure customer. This holds 
 the different data of the customer (customer id, orders, number of orders, status).
 
 @return (short) returns an integer value of the total number of orders

*/
short 
countOrders (struct customer* arrCustomer)	
{
	short k, j;
	short nOrderCount = 0;
	for(k = 0; k < MAXCUST; k++){
		if(arrCustomer[k].id != 0){
			for(j = 0; j < arrCustomer[k].numOrder; j++)
				nOrderCount++;
		}
	}
	return nOrderCount;
}


/*
This function counts the total number of customers regardless if paid or not
 @param (struct*) arrCustomer is the pointer for the structure customer. This holds 
 the different data of the customer (customer id, orders, number of orders, status).
 
 @return (short) returns an integer value of the total number of customers

*/

short
countTotalCust (struct customer* arrCustomer)
{
	short i;
	short nCustomerCount = 0;
	for(i = 0; i < MAXCUST; i++){
		if(arrCustomer[i].id != 0)
			nCustomerCount++;
	}
	
	return nCustomerCount;
}

/******  CUSTOMER FUNCTIONS START   ******/



/*
This function handles the ordering of the customer.
 @param (struct*) arrCustomer is the pointer for the structure customer. This holds 
 the different data of the customer (customer id, orders, number of orders, status).
 @param (int) customerNumber indicates which customer is currently in use.
 @param(bool) boolRestoClosed indicates whether the restaurant is closed or not 
 @return (void) no return value
*/

void
foodMenu (struct customer* arrCustomer, int customerNumber, bool* boolRestoClosed)
{
	short i, j, k, x; //iteration variables
	short orderNum = arrCustomer[customerNumber - 1].numOrder;
	short orderCount; 
	bool exception = true; // exception handlers
	bool exception2 = true;
	short nChoice;
	short confirmNumOrder; 
	
	
	struct food foodList[] = {
	{1, 50.00, "Siomai\0"}, {2, 90.00, "Siopao\0"}, {3, 110.00, "Pares\0"},
	{4, 115.00, "Mami\0"}, {5, 85.00, "Chicken\0"}
	};
	
	
	printf("\n\t%20s\n","Food Menu");
	printf("\t");
	for(x=1; x<=34; x++)
		printf("-");
	printf("\n");
	
	printf("\t\n\t%s  %-5s%13s","Code","Name", "Price\n");
	for(i = 0; i < 5; i++){
		printf("\t\n\t#%03d  %-8s%10.2f",foodList[i].id, foodList[i].name,foodList[i].price);
	}	
	
	orderCount = countOrders(arrCustomer);

	//printf("\n\tor count: %d\n", orderCount);
	
	
	while (exception){
		
		exception2 = true;
		
		if(arrCustomer[customerNumber - 1].numOrder <= 3){
			printf("\n\n\tEnter input: ");
			scanf(" %d",&nChoice);	
			exception = false; 
		
			
			switch(nChoice){
				case 1: case 2:	case 3: case 4:
				case 5:
					/* Puts the corresponding order number and order status to its specific array index/position */
					arrCustomer[customerNumber - 1].order[arrCustomer[customerNumber - 1].numOrder - 1].food = nChoice;
					arrCustomer[customerNumber - 1].order[arrCustomer[customerNumber - 1].numOrder - 1].status[0] = 'O';
					orderCount++;
					break;
				
				default:
					exception = true;
					exception2 = false;
					fputs("\n\tInvalid input please try again.\n",stderr);
					empty_stdin();
					break;
			}
			
			while(exception2){
				exception2 = false;
				/* checks if the number of orders is less than the max number of orders per day 
					(where MAX_ORDER = 20)
				*/
				if(orderCount <= MAX_ORDER){
					
					if(arrCustomer[customerNumber - 1].numOrder < 3){
						
						printf("\n\tWould you like to order again?\n\t0 - NO/6 - YES: ");			
						scanf(" %d",&confirmNumOrder);	
						//getchar();
						
						if(confirmNumOrder == 6 ){
							exception = true;
							arrCustomer[customerNumber - 1].numOrder++;
						}
						else if(confirmNumOrder == 0)
							printf("\n\tThank you for ordering!");
							
						else{
							exception2 = true;
							fputs("\n\tInvalid input please try again.\n",stderr);
							empty_stdin();
						}
					}
					else
						printf("\n\tMaximum number of orders reached. Proceeding to checkout\n\n");
				}
				else 
					printf("\n\tThe restaurant can only hold 20 orders daily. Proceeding to checkout\n\n");
			}
		}
		else
			printf("\n\tMaximum number of orders reached. Proceeding to checkout\n\n");
	}
	customerMenu(arrCustomer, customerNumber, boolRestoClosed);
}



/*
This function indicates whether the customer is a new or old customer.
 @param (struct*) arrCustomer is the pointer for the structure customer. This holds 
 the different data of the customer (customer id, orders, number of orders, status).
 @param(bool) boolRestoClosed indicates whether the restaurant is closed or not 
 
 @return (void) no return value
*/


void 
customer (struct customer* arrCustomer, bool* boolRestoClosed)
{
	short nOption; // for selection
	short x ,y; // iteration variables
	
	/* For counting variables refer below to functions countCustomers, 
	countOrders, countTotalCust */
	short customerCount; // count current number of customers
	short totalCustCount; // count total number of customers 
	short orderCount = 0; // count total number of orders
		
	bool found = false; // indicator if an array element is existing
	bool exception = true; // exception handler
	bool exception2 = true;
	short nCustomerNumber;
	
	printf("\n\n\t%21s\n","Customer");
	printf("\t");
	for(x=1; x<=34; x++)
		printf("-");
	printf("\n");
	while (exception){
		printf("\tOld or new customer?\n");
		printf("\t(1) New\n");
		printf("\t(2) Old\n");
		printf("\t(3) Main menu\n");
		printf("\tInput: ");
		scanf("%d",&nOption);
		
		exception = false;
		
		/* get current number of active customers */
		customerCount = countCustomers(arrCustomer);
		
		/* get number of orders served*/
		orderCount = countOrders(arrCustomer);
		
		/* get number of customers served */
		totalCustCount = countTotalCust(arrCustomer);
		
		switch(nOption){
			case 1:
				for(x = 0; x < MAXCUST; x++){
						
						if(orderCount < MAX_ORDER && totalCustCount < MAXCUST && !*boolRestoClosed){
							if(customerCount < 5){
								if(arrCustomer[x].id == 0){
								
									arrCustomer[x].id = x+1;
									arrCustomer[x].status[0] = 'W';
									printf("\n\tYour customer number is: %02d\n", arrCustomer[x].id);	
									printf("\n");
									foodMenu(arrCustomer, arrCustomer[x].id, boolRestoClosed);
								
								}
							}
							else{
								printf("\n\tRestaurant is Full!\n\n");
								customer(arrCustomer, boolRestoClosed);		
							}
						}
						else{
							printf("\n\tThe restaurant is now closed.\n\n");
							mainMenu(arrCustomer, boolRestoClosed);
						}
					}
				
				break;
			case 2:
				if(arrCustomer[0].id == 0){
					exception = true;
					fputs("\n\tThere are no customers at the moment please try again\n\n",stderr);
					empty_stdin();
				}
				else{
					while(exception2){
						printf("\tEnter your customer number: ");
						scanf("%d",&nCustomerNumber);
						exception2 = false;
						
						for(x = 0; x < MAXCUST ; x++){
							if(nCustomerNumber == arrCustomer[x].id && nCustomerNumber != 0){
								found = true;
								break;
							}
						}
							if (!found){
								exception2 = true;
								fputs("\n\tCustomer ID not found try again:\n\n",stderr);
								empty_stdin();
							}
							else
								customerMenu(arrCustomer, nCustomerNumber, boolRestoClosed);
					}
				}
				break;
			case 3:
				system("cls");
				mainMenu(arrCustomer, boolRestoClosed);
				break;
			default:
				exception = true;
				fputs("\n\tInvalid input please try again\n\n",stderr);
				empty_stdin();
				break;
		}
	}
}



/*
This function displays the orders of the customer with its status and price.

 @param (struct*) arrCustomer is the pointer for the structure customer. This holds 
 the different data of the customer (customer id, orders, number of orders, status).
 @param (int) customerNumber indicates which customer is currently in use.
 @param(bool) boolRestoClosed indicates whether the restaurant is closed or not 
 @return (void) no return value
*/

void
orderList (struct customer* arrCustomer, int customerNumber, bool* boolRestoClosed){
	short x, y, z; // iteration variables
	struct food foodList[] = {
	{1, 50.00, "Siomai\0"}, {2, 90.00, "Siopao\0"}, {3, 110.00, "Pares\0"},
	{4, 115.00, "Mami\0"}, {5, 85.00, "Chicken\0"}
	};
	
	
	printf("\n\t%-5s %-8s%-8s%7s\n","Code", "Name", "Status","Price");
	printf("\t");
	for(y = 1; y <= 30; y++)
		printf("-");
	printf("\n");
	
	for(x = 0; x < arrCustomer[customerNumber - 1].numOrder; x++){
		printf("\t#%03d ",foodList[arrCustomer[customerNumber - 1].order[x].food - 1].id);
		printf(" %-8s",foodList[arrCustomer[customerNumber - 1].order[x].food - 1].name);
		printf("%-8s", orderStatus(arrCustomer, customerNumber, x));
		printf("\t%.2f",foodList[arrCustomer[customerNumber - 1].order[x].food - 1].price);
		printf("\n\n");
	}
	
	free (orderStatus(arrCustomer, customerNumber, x));
	customerMenu(arrCustomer, customerNumber, boolRestoClosed);
	
}



/*
This function serves as the main menu for the customer.
 @param (struct*) arrCustomer is the pointer for the structure customer. This holds 
 the different data of the customer (customer id, orders, number of orders, status).
 @param (int) customerNumber indicates which customer is currently in use.
 @param(bool) boolRestoClosed indicates whether the restaurant is closed or not 
 @return (void) no return value
*/
void
customerMenu (struct customer* arrCustomer, int customerNumber, bool* boolRestoClosed)
{
	bool found = false; // indicator if an array element is existing
	bool exception = true; // exception handler
	unsigned short menuChoice;
	short x, i; //iteration variable

	while(exception){
		printf("\n\n\t%22s\n","Customer Menu");
		printf("\t");
		for(i=1; i<=34; i++)
			printf("-");
		printf("\n");
		
		printf("\t(1) Order Status\n");
		printf("\t(2) Display customer number and status\n");
		printf("\t(3) Pay\n");
		printf("\t(4) Exit\n");
		printf("\tInput: ");
		scanf("%d",&menuChoice);
		exception = false;
		
		switch(menuChoice){
			case 1:
				orderList(arrCustomer, customerNumber, boolRestoClosed);
				break;
			case 2:
				printf("\n\tCustomer number: %02d\n", customerNumber);
				printf("\n\tStatus: %s\n", customerStatus(arrCustomer, customerNumber));
				exception = true;
				break;
			case 3:
				customerPay(arrCustomer, customerNumber, boolRestoClosed);
				break;
			case 4: 
				system("cls");
				mainMenu(arrCustomer, boolRestoClosed);
				break;
			default:
				exception = true;
				fputs("\n\tInvalid input please try again:\n\n",stderr);
				empty_stdin();
				break;
		}
	}
}


/*
This function handles the customer payments.
 @param (struct*) arrCustomer is the pointer for the structure customer. This holds 
 the different data of the customer (customer id, orders, number of orders, status).
 @param (int) customerNumber indicates which customer is currently ordering.
 @param(bool) boolRestoClosed indicates whether the restaurant is closed or not 
 @return (void) no return value
*/
void
customerPay(struct customer* arrCustomer, int customerNumber, bool* boolRestoClosed)
{
	short x, y, z; // iteration variables 
	bool boolException = true; // exception handler
	float fTotalPrice = 0; // total price of ordered food/s 
	float fAmountPaid; // amount paid by the customer
	struct food foodList[] = {
	{1, 50.00, "Siomai\0"}, {2, 90.00, "Siopao\0"}, {3, 110.00, "Pares\0"},
	{4, 115.00, "Mami\0"}, {5, 85.00, "Chicken\0"}
	};
	printf("\n");
	printf("\t%-15s%13s\n\n","Food","Price");
	for(x = 0; x < arrCustomer[customerNumber - 1].numOrder; x++){
		if(arrCustomer[customerNumber - 1].order[x].status[0] == 'E'){
			fTotalPrice += foodList[arrCustomer[customerNumber - 1].order[x].food - 1].price;
			printf("\t(#%03d) ",foodList[arrCustomer[customerNumber - 1].order[x].food - 1].id);
			printf("%-15s%7.2f\n",foodList[arrCustomer[customerNumber - 1].order[x].food - 1].name,
								   foodList[arrCustomer[customerNumber - 1].order[x].food - 1].price);
			printf("\n");	
		}
		else if(arrCustomer[customerNumber - 1].order[x].status[0] == 'A'){
			printf("\n\tYou have already paid.\n\n");
			customerMenu(arrCustomer,customerNumber, boolRestoClosed);
		}
		else{
			printf("\n\tThe food is not served yet.\n\n");
			customerMenu(arrCustomer,customerNumber, boolRestoClosed);
		}
			
	}
	printf("\t%-19s%10.2f\n","Total",fTotalPrice);
	while(boolException){
		printf("\tEnter Amount: ");
		scanf("%f",&fAmountPaid);
		boolException = false;
		
		if(fAmountPaid >= fTotalPrice){
			printf("\n\tChange: %.2f\n\n", fAmountPaid - fTotalPrice);
			arrCustomer[customerNumber - 1].status[0] = 'P';
			for(x = 0; x < arrCustomer[customerNumber - 1].numOrder; x++){
				arrCustomer[customerNumber - 1].order[x].status[0] = 'A';
			}
		}
		
		else{
			printf("\n\tInvalid amount paid\n\n");
			boolException = true;
		}
		
	}

	customerMenu(arrCustomer,customerNumber, boolRestoClosed);
}

/******  CUSTOMER FUNCTIONS END   ******/




/*****   WAITER FUNCTIONS START    *******/



/*
This function serves as the main menu for the waiter.
 @param (struct*) arrCustomer is the pointer for the structure customer. This holds 
 the different data of the customer (customer id, orders, number of orders, status).
 @param(bool) boolRestoClosed indicates whether the restaurant is closed or not 
 @return (void) no return value
*/
void
waiter (struct customer* arrCustomer, bool* boolRestoClosed)
{
	short nOption; // input option for menu 
	short i, j; // iteration varaibles
	short nCustomerCount; // counts current number of customers 
	bool exception = true; // exception handler
	

	while(exception){
	
		printf("\n\t%22s\n\t","Waiter Menu");
		for(i=1; i<=34; i++)
			printf("-");
			
		printf("\n\t(1) Send orders\n");
		printf("\t(2) View orders\n");
		printf("\t(3) Serve dish\n");
		printf("\t(4) View daily report\n");
		printf("\t(5) Close restaurant\n");
		printf("\t(6) Exit\n");
		printf("\tInput: ");
		
		scanf("%d",&nOption);
		exception = false;
		
		/* check if there are current customers who are not yet paid*/ 
		nCustomerCount = countCustomers(arrCustomer);
		
		switch(nOption){
			case 1:
				if(nCustomerCount > 0)
					sendOrder(arrCustomer, boolRestoClosed);
				else{
					printf("\tNo customers at the moment\n");
					exception = true;
				}	
				break;
			case 2:
				viewOrder(arrCustomer, boolRestoClosed);
				break;
			case 3:
				/*** THIS FUNCTION IS SUBJECT TO CHANGE WIEEE ***/
				if(nCustomerCount > 0) 
					waiterSendDish(arrCustomer, boolRestoClosed);
				else{
					printf("\tNo customers at the moment\n");
					exception = true;	
				}
				break;
			case 4:
				system("cls");
				waiterDisplayIncome(arrCustomer, boolRestoClosed);
				break;
			case 5:
				waiterCloseResto(arrCustomer,boolRestoClosed);
				break;
			case 6:
				system("cls");
				mainMenu(arrCustomer, boolRestoClosed);
				break;
			default:
				exception = true;
				fputs("\n\tInvalid input please try again:\n\n",stderr);
				empty_stdin();
				break;
		}
	}
}

/*
This function sends the order to the chef wherein the customers' orders will hold a PENDING status.
 @param (struct*) arrCustomer is the pointer for the structure customer. This holds 
 the different data of the customer (customer id, orders, number of orders, status).
 @param(bool) boolRestoClosed indicates whether the restaurant is closed or not 
 @return (void) no return value
*/
void 
sendOrder (struct customer* arrCustomer, bool* boolRestoClosed)
{
	int i, j; // iteration variables 
	char *sMessage = malloc(75); // string for output message
	
	for(i = 0; i < MAXCUST; i++){
		if(arrCustomer[i].id != 0){
			for(j = 0; j < arrCustomer[i].numOrder; j++){
				if(arrCustomer[i].order[j].status[0] == 'O'){
					arrCustomer[i].order[j].status[0] = 'P';
					strcpy(sMessage,"Orders sent!\0" );
				}
				else
					strcpy(sMessage,"No orders to be sent at the moment\0");
			}
		}			
	}
	
	printf("\n\t%s\n\n",sMessage);
	free(sMessage);
	waiter(arrCustomer, boolRestoClosed);
}


/*
This function displays the customers' orders and its status.
 @param (struct*) arrCustomer is the pointer for the structure customer. This holds 
 the different data of the customer (customer id, orders, number of orders, status).
 @param(bool) boolRestoClosed indicates whether the restaurant is closed or not 
 @return (void) no return value
*/
void
viewOrder(struct customer* arrCustomer, bool* boolRestoClosed)
{
	char *orderStat = malloc(50); // string for order status 
	short i, j, k; // iteration variables 
	char *food = malloc(50); // string for food 
	
	struct food foodList[] = {
	{1, 50.00, "Siomai\0"}, {2, 90.00, "Siopao\0"}, {3, 110.00, "Pares\0"},
	{4, 115.00, "Mami\0"}, {5, 85.00, "Chicken\0"}
	};
	printf("\n\tPending Orders:\n");
	printf("\t");
	for(k = 1; k <= 44; k++)
		printf("-");
	printf("\n");
	printf("\t%-10s  %15s  %15s","Ordered By","Food","Status\n");
	for(i = 0; i < MAXCUST; i++){
		if(arrCustomer[i].id != 0){
			for(j = 0; j < arrCustomer[i].numOrder ; j++){
				if(arrCustomer[i].order[j].status[0] != 'A'){
					strcpy(orderStat, orderStatus(arrCustomer, arrCustomer[i].id, j));
					strcpy(food, foodList[arrCustomer[i].order[j].food -1].name);
					printf("\t%-10s%02d %14s %14s \n","Customer no.",arrCustomer[i].id,food,orderStat);	
				}
				
			}
		}
	}
	printf("\n");
	free(orderStat);
	free(food);
	waiter(arrCustomer, boolRestoClosed);
	
}



/*
This function serves as the main menu for the waiter.
 @param (struct*) arrCustomer is the pointer for the structure customer. This holds 
 the different data of the customer (customer id, orders, number of orders, status).
 @param(bool) boolRestoClosed indicates whether the restaurant is closed or not 
 @return (void) no return value
*/
void 
waiterSendDish(struct customer* arrCustomer, bool* boolRestoClosed)
{
	short i, j; // iteration variables 
	short nCustomerCount = 0; // count customers to be served 
	char *sMessage = malloc(75); // string for output message 
	
	for(i = 0; i < MAXCUST; i++){
		if(arrCustomer[i].id != 0){
			for(j = 0; j < arrCustomer[i].numOrder; j++){
				if(arrCustomer[i].order[j].status[0] == 'D'){
					arrCustomer[i].order[j].status[0] = 'E';
					arrCustomer[i].status[0] = 'E';
					strcpy(sMessage,"Dishes Served!");
					nCustomerCount++;
					
				}
				else{	
					if(nCustomerCount > 0)
						strcpy(sMessage,"Dishes Served!");
					else
						strcpy(sMessage,"No dishes can be served at the moment");	
				}
			}
		}
	
	}
	printf("\n\t%s\n\n",sMessage);
	free(sMessage);
	waiter(arrCustomer, boolRestoClosed);
}


/*
This function displays the income, current number of customers, 
total number of customers, and number of orders served
of the restaurant .
@param (struct*) arrCustomer is the pointer for the structure customer. This holds 
the different data of the customer (customer id, orders, number of orders, status).
@param(bool) boolRestoClosed indicates whether the restaurant is closed or not 
@return (void) no return value
*/
void 
waiterDisplayIncome(struct customer* arrCustomer, bool* boolRestoClosed)
{
	short i,j; // iteration variable 
	float fTotalPaid = 0; // total paid price for the food per customer
	float fTotalIncome = 0; // total income for the day 
	
	struct food foodList[] = {
	{1, 50.00, "Siomai\0"}, {2, 90.00, "Siopao\0"}, {3, 110.00, "Pares\0"},
	{4, 115.00, "Mami\0"}, {5, 85.00, "Chicken\0"}
	};
	
	
	printf("\n\t%-15s%12s\n","Customer","Paid");
	
	printf("\t");
	for(i=1; i<=34; i++)
		printf("-");
	printf("\n");
	
	for(i = 0; i < MAXCUST; i++){
		if(arrCustomer[i].status[0] == 'P'){
			for(j = 0; j < arrCustomer[i].numOrder; j++)
				fTotalPaid += foodList[arrCustomer[i].order[j].food - 1].price;
			printf("\n\t%s %02d%12.2f","Customer no.", i + 1, fTotalPaid);
			fTotalIncome += fTotalPaid;
			fTotalPaid = 0;
		}
	}
	printf("\n");
	printf("\t");
	for(i=1; i<=34; i++)
		printf("-");
		
	printf("\n\n\tTotal Income: %3.2f\n",fTotalIncome);
	printf("\n\n\tTotal Customers: %3d", countTotalCust(arrCustomer));
	printf("\n\tCurrent Customers: %d", countCustomers(arrCustomer));
	printf("\n\tOrders Served: %5d\n\n",countOrders(arrCustomer));
	waiter(arrCustomer, boolRestoClosed);
	
}


/*
This function closes the restaurant if all the current customers have already paid. This prevents 
new customers to enter the restaurant.  
@param (struct*) arrCustomer is the pointer for the structure customer. This holds 
the different data of the customer (customer id, orders, number of orders, status).
@param(bool) boolRestoClosed indicates whether the restaurant is closed or not 
@return (void) no return value
*/
void 
waiterCloseResto(struct customer* arrCustomer ,bool* boolRestoClosed)
{
	short i, j; // iteration variables
	short countPaid = 0; // count number of customers who have paid 
	short totalCust; // total number of customers 
	char *sMessage = malloc(75); // String for output message
	
	/* get the total number of customers*/
	totalCust = countTotalCust(arrCustomer);
	
	for(i = 0; i < totalCust ; i++){
		if(arrCustomer[i].status[0] == 'P')
			countPaid++;
	}
	if(countPaid == totalCust){
		*boolRestoClosed = true;
		strcpy(sMessage,"The restaurant is now closed!");
	}
	else{
		*boolRestoClosed = false;
		strcpy(sMessage,"Customer payments are not yet complete");
	}
				
		
	printf("\n\t%s\n\n",sMessage);
	mainMenu(arrCustomer, boolRestoClosed);
}
/*****   WAITER FUNCTIONS END    *******/


/*****   CHEF FUNCTIONS START    *******/

/*
This function serves as the main menu for the chef.
 @param (struct*) arrCustomer is the pointer for the structure customer. This holds 
 the different data of the customer (customer id, orders, number of orders, status).
 @param(bool) boolRestoClosed indicates whether the restaurant is closed or not 
 @return (void) no return value
*/
void
chef(struct customer* arrCustomer, bool* boolRestoClosed)
{
	short nOption; // option for menu selection
	short i, j; // iteration variables 
	short nCustomerCount; // count number of customers 
	bool exception = true; // exception handler
	
	while(exception){
	
		printf("\n\t%21s\n\t","Chef Menu");
		for(i=1; i<=34; i++)
			printf("-");
			
		printf("\n\t(1) View Pending Orders\n");
		printf("\t(2) Cook Dishes\n");
		printf("\t(3) Deliver Dishes\n");
		printf("\t(4) Exit\n");
		
		
		printf("\tInput: ");
		scanf("%d",&nOption);
		exception = false;
		
		/* count current number of customers */
		nCustomerCount = countCustomers(arrCustomer);
		
		switch(nOption){
			case 1:
		
				if(nCustomerCount == 0){
					printf("\tNo customers at the moment\n");
					exception = true;
				}
				else
					chefViewOrder(arrCustomer, boolRestoClosed);
				break;
			case 2:
				if(nCustomerCount == 0){
					printf("\tNo customers at the moment\n");
					exception = true;
				}
				else
					cookOrder(arrCustomer, boolRestoClosed);
				break;
			case 3:
				if(nCustomerCount == 0){
					printf("\tNo customers at the moment\n");
					exception = true;
				}
				else
					chefDeliverOrder(arrCustomer, boolRestoClosed);
				break;
			case 4:
				system("cls");
				mainMenu(arrCustomer, boolRestoClosed);
				break;
			default:
				exception = true;
				fputs("\n\tInvalid input please try again:\n\n",stderr);
				empty_stdin();
				break;
		}
	}
}



/*
This function cooks N pending orders where N <= 3 .
 @param (struct*) arrCustomer is the pointer for the structure customer. This holds 
 the different data of the customer (customer id, orders, number of orders, status).
 @param(bool) boolRestoClosed indicates whether the restaurant is closed or not 
 @return (void) no return value
*/
void
cookOrder(struct customer* arrCustomer, bool* boolRestoClosed)
{
	short i, j; // iteration variables 
	short nDishes ; // N dishes to be cooked where N <= 3
	short cookedDishes = 0; // number dishes being cooked where N <= 3 
	bool exception = true; // exception handler
	char *sMessage = malloc(50); //string for output message
	
	while(exception){
		
		printf("\n\tEnter N dishes: ");
		scanf("%d",&nDishes);
		exception = false;
		
		if(nDishes > 3 || nDishes < 0){
			exception = true;
			fputs("\n\tIncorrect input please try again\n\n",stderr);
			empty_stdin();
		}	
			
	}
	
	for(i = 0; i < MAXCUST; i++){
		if(arrCustomer[i].id != 0){
			for(j = 0; j < arrCustomer[i].numOrder; j++){
				if(arrCustomer[i].order[j].status[0] == 'P'){
					arrCustomer[i].order[j].status[0] = 'C';
					cookedDishes++;
					strcpy(sMessage,"Orders Cooked!" );
					if(cookedDishes >= nDishes)
						break;
						
				}	
				else{
					if(cookedDishes > 0){
						strcpy(sMessage,"Orders Cooked!" );
						break;
					}
					strcpy(sMessage,"No pending orders available" );
				}
					
				
			}
		}
		if(cookedDishes >= nDishes)
			break;	
	}

	printf("\n\t%s\n",sMessage);
	chef(arrCustomer, boolRestoClosed);
}



/*
This function displays the pending orders that can be cooked by the chef. It also displays 
orders that were cooked but not yet delivered to the waiter.
 @param (struct*) arrCustomer is the pointer for the structure customer. This holds 
 the different data of the customer (customer id, orders, number of orders, status).
 @param(bool) boolRestoClosed indicates whether the restaurant is closed or not 
 @return (void) no return value
*/
void
chefViewOrder(struct customer* arrCustomer, bool* boolRestoClosed)
{
	char *orderStat = malloc(50); // string for order status 
	short i, j, k; // iteration variables
	char *food = malloc(50); // string for food name
	short nCountPending = 0; // count pending orders 
	
	
	struct food foodList[] = {
	{1, 50.00, "Siomai\0"}, {2, 90.00, "Siopao\0"}, {3, 110.00, "Pares\0"},
	{4, 115.00, "Mami\0"}, {5, 85.00, "Chicken\0"}
	};
	
	printf("\n\tPending Orders:\n");
	printf("\t");
	for(k = 1; k <= 34; k++)
		printf("-");
	printf("\n");
	printf("\t%-10s  %15s  %15s","Ordered By","Food","Status\n");
	for(i = 0; i < MAXCUST; i++){
		if(arrCustomer[i].id != 0){
			for(j = 0; j < arrCustomer[i].numOrder ; j++){
				if(arrCustomer[i].order[j].status[0] == 'P' || arrCustomer[i].order[j].status[0] == 'C' ){
					strcpy(orderStat, orderStatus(arrCustomer, arrCustomer[i].id, j));
					strcpy(food, foodList[arrCustomer[i].order[j].food -1].name);
					printf("\t%-10s%02d %14s %14s \n","Customer no.",arrCustomer[i].id,food,orderStat);	
					strcpy(orderStat,"");
					nCountPending++;
				}
				else{
					if(nCountPending > 0){
						if(arrCustomer[i].order[j].status[0] == 'O')
							strcpy(orderStat,"");
						else
							strcpy(orderStat, "No pending orders at the moment!");	
					}
					else
						strcpy(orderStat, "No pending orders at the moment!");	
				}	
			}
		}
	}
	printf("\n\t%s\n\n",orderStat);
	
	free(orderStat);
	free(food);
	chef(arrCustomer, boolRestoClosed);
} 


/*
This function delivers 3 COOKED orders at a time to the waiter.
 @param (struct*) arrCustomer is the pointer for the structure customer. This holds 
 the different data of the customer (customer id, orders, number of orders, status).
 @param(bool) boolRestoClosed indicates whether the restaurant is closed or not 
 @return (void) no return value
*/
void
chefDeliverOrder(struct customer* arrCustomer, bool* boolRestoClosed)
{
	short i, j; // iteration variables 
	short cookedDishes = 0; // count number of cooked dishes 
	char *sMessage = malloc(75); // string for output message 
	
	
	for(i = 0; i < MAXCUST; i++){
		if(arrCustomer[i].id != 0){
			for(j = 0; j < arrCustomer[i].numOrder; j++){
				if(arrCustomer[i].order[j].status[0] == 'C'){
					arrCustomer[i].order[j].status[0] = 'D';
					cookedDishes++;
					strcpy(sMessage, "Cooked Dishes Delivered!");
					if(cookedDishes >= 3)
						break;
				}
				else {
					if(cookedDishes > 0 && cookedDishes <= 3){
						strcpy(sMessage, "Cooked Dishes Delivered!");
						break;
					}
					strcpy(sMessage, "No cooked dishes can be delivered at the moment");
				}
					
			}
		}
		if(cookedDishes >= 3)
			break;
	}
	printf("\n\t%s\n\n",sMessage);
	free(sMessage);
	chef(arrCustomer, boolRestoClosed);
}

/*****   CHEF FUNCTIONS END   *******/

/*
This function serves as the main menu for the whole system wherein it lets the user choose 
whether to use a .
 @param (struct*) arrCustomer is the pointer for the structure customer. This holds 
 the different data of the customer (customer id, orders, number of orders, status).
 @param(bool) boolRestoClosed indicates whether the restaurant is closed or not 
 @return (void) no return value
*/
void 
mainMenu (struct customer* arrCustomer, bool* boolRestoClosed)
{
	short x, y; // iteration variables 
	
	unsigned short nOption; // main menu options (customer, waiter chef)
	
	bool nException = true; // exception handler
	
	char arrOptions[4][10] ={"Customer\n\0", "Waiter\n\0", "Chef\n\0", "Exit\n\0"};
	
	/*display line*/
	printf("\t");
	for(x=1; x<=34; x++)
		printf("-");
		
	printf("\n\t%23s\n","Pares Express");
	printf("\t");
	
	/*display line*/
	for(x=1; x<=34; x++)
		printf("-");
	printf("\n");

	while(nException){
	
		printf("\t%21s\n","Main Menu");
		
		/*display line*/
		printf("\t");
		for(x=1; x<=34; x++)
			printf("-");
		printf("\n");
		
		for (x = 0; x<4; x++){
			printf("\t(%d) ",x+1);
			for (y=0; arrOptions[x][y]; y++)
			printf("%c",arrOptions[x][y]);
		}
		
		printf("\tInput: ");
		scanf("%d",&nOption);
		nException = false;
		
		switch(nOption){
		case 1:
			system("cls");
			customer(arrCustomer, boolRestoClosed);
			break;
		case 2:
			system("cls");
			waiter(arrCustomer, boolRestoClosed);
			break;
		case 3:
			system("cls");
			chef(arrCustomer, boolRestoClosed);
			break;
		case 4:
			exit(0);
			break;
		default:
			nException = true;
			fputs("\n\tInvalid input please try again:\n\n",stderr);
			empty_stdin();
			break;
		}
	}
	
	
}

/*
Main function. Stores the different data from the structure.
 @return (int) return 0
*/
int 
main()
{
	bool boolRestoClosed = false; // indicates whether the restaurant is closed or not 
	
	/*Storage of data of each customer*/ 
	struct customer arrCustomer[] = {
	{0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"}, {0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"}, {0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"},
	{0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"}, {0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"}, {0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"},
	{0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"}, {0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"}, {0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"},
	{0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"}, {0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"}, {0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"},
	{0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"}, {0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"}, {0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"},
	{0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"}, {0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"}, {0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"},
	{0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"}, {0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"}
	};
	
	mainMenu(arrCustomer, &boolRestoClosed);
	
	return 0;
}

