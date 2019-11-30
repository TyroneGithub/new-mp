/***
Programmed by: Tyrone Sta. Maria S11A 
Description:
Last modified: 11-30-19
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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
void mainMenu(struct customer*);
void customer(struct customer*);
void customerMenu (struct customer* ,int customerNumber);
void foodMenu(struct customer*, int customerNumber);
void orderList(struct customer*, int customerNumber);
void sendOrder (struct customer* arrCustomer);
void viewOrder(struct customer* arrCustomer);
void chef(struct customer* arrCustomer);
void cookOrder(struct customer* arrCustomer);
void chefViewOrder(struct customer* arrCustomer);
void chefDeliverOrder(struct customer* arrCustomer);
void waiterSendDish(struct customer* arrCustomer);
void customerPay(struct customer* arrCustomer, int customerNumber);

/* VALUE RETURNING FUNCTIONS*/
char* customerStatus (struct customer* arrCustomer, int customerNumber);
char* orderStatus (struct customer* arrCustomer, int customerNumber, int x);
int countCustomers (struct customer* arrCustomer);
int countOrders (struct customer* arrCustomer);

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

char
*orderStatus (struct customer* arrCustomer, int customerNumber, int x)
{
	static char status[] = "?";
	
	switch(arrCustomer[customerNumber - 1].order[x].status[0]){
		case 'O':
			strcpy(status, "Ordered");
			break;
		case 'E':
			strcpy(status, "Eating");
			break;
		case 'P':
			strcpy(status, "Pending");
			break;
		case 'C':
			strcpy(status, "Cooked");
			break;
		case 'D':
			strcpy(status, "Delivered");
			break;
		default:
			strcpy(status, "");
			break;
	}
	return status; 
}


char 
*customerStatus (struct customer* arrCustomer, int customerNumber)
{
	static char status[] = "?";
	switch(arrCustomer[customerNumber - 1].status[0]){
		case 'W':
			strcpy(status, "Waiting");
			break;
		case 'E':
			strcpy(status, "Eating");
			break;
		case 'P':
			strcpy(status, "Paid");
			break;
	}
	return status; 
}

int 
countCustomers (struct customer* arrCustomer)
{
	int x;
	int customerCount = 0;
	for(x = 0; x < 20; x++){
			if(arrCustomer[x].id > 0 && arrCustomer[x].status[0] != 'P')
				customerCount++;
	}
	return customerCount;
}
	
int 
countOrders (struct customer* arrCustomer)	
{
	int k, j;
	int orderCount = 0;
	for(k = 0; k < 20; k++){
		if(arrCustomer[k].id != 0){
			for(j = 0; j < arrCustomer[k].numOrder; j++)
				orderCount++;
		}
	}
	return orderCount;
}


/******  CUSTOMER FUNCTIONS START   ******/
void
foodMenu (struct customer* arrCustomer, int customerNumber)
{
	short i, j, k; //iteration variable
	short orderNum = arrCustomer[customerNumber - 1].numOrder;
	short orderCount; 
	bool exception = true; // exception handlers
	bool exception2 = true;
	//bool confirmOrder = true;
	unsigned short nChoice;
	char confirmNumOrder; 
	
	
	struct food foodList[] = {
	{1, 50.00, "Siomai\0"}, {2, 90.00, "Siopao\0"}, {3, 110.00, "Pares\0"},
	{4, 115.00, "Mami\0"}, {5, 85.00, "Chicken\0"}
	};
	
	
	printf("\n\t= = = = = Food Menu = = = = = \n");
	for(i = 0; i < 5; i++){
		printf("\t\n\t(%d) %-15s%10.2f",foodList[i].id, foodList[i].name, foodList[i].price);
	}	
	
	orderCount = countOrders(arrCustomer);

	//printf("\n\tor count: %d\n", orderCount);
	
	
	while (exception){
		
		exception2 = true;
		
		if(arrCustomer[customerNumber - 1].numOrder <= 3){
			printf("\n\tEnter input: ");
			scanf("%d",&nChoice);
			
			exception = false; 
			switch(nChoice){
				case 1: case 2:	case 3: case 4:
				case 5:
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
				if(orderCount <= 20){
				
					if(arrCustomer[customerNumber - 1].numOrder < 3){
						
						printf("\n\tWould you like to order again (Y/N)?: ");			
						scanf(" %c",&confirmNumOrder);	
						
						if(confirmNumOrder == 'Y' || confirmNumOrder == 'y'){
							exception = true;
							arrCustomer[customerNumber - 1].numOrder++;
						}
							
							
						else if(confirmNumOrder == 'N' || confirmNumOrder== 'n' )
							printf("\n\tThank you for ordering!");
							
						else{
							exception2 = true;
							fputs("\n\tInvalid input please try again.\n",stderr);
							empty_stdin();
						}
					}
					else{
						printf("\n\tMaximum number of orders reached. Proceeding to checkout\n\n");
					}
				}
				else 
					printf("\n\tThe restaurant can only hold 20 orders daily. Proceeding to checkout\n\n");
			}
		}
		else
			printf("\n\tMaximum number of orders reached. Proceeding to checkout\n\n");
	}
	customerMenu(arrCustomer, customerNumber);
}
	



void 
customer (struct customer* arrCustomer)
{
	int option;
	short x ,y;
	short customerCount;
	short orderCount = 0;
	bool found = false; // indicator if an array element is existing
	bool exception = true; // exception handler
	bool exception2 = true;
	short nCustomerNumber;
	

	while (exception){
		printf("\tOld or new customer?\n");
		printf("\t(1) New\n");
		printf("\t(2) Old\n");
		printf("\t(3) Main menu\n");
		printf("\tInput: ");
		scanf("%d",&option);
		
		exception = false;
		
		/* get current number of active customers */
		customerCount = countCustomers(arrCustomer);
		
		/* get current number of orders */
		orderCount = countOrders(arrCustomer);
		
		switch(option){
			case 1:
				for(x = 0; x < 20; x++){
					if(orderCount < 20){
						if(customerCount < 5){
							if(arrCustomer[x].id == 0){
							
								arrCustomer[x].id = x+1;
								arrCustomer[x].status[0] = 'W';
								printf("\n\tYour customer number is: %02d\n", arrCustomer[x].id);	
								printf("\n");
								foodMenu(arrCustomer, arrCustomer[x].id);
							
							}
						}
						else{
							printf("\n\tRestaurant is Full!\n\n");
							customer(arrCustomer);		
						}
					}
					else{
						printf("\n\tThe restaurant is not accepting orders anymore.\n\n");
						mainMenu(arrCustomer);
					}
						
				}
				break;
			case 2:
				/** THIS FUNCTION IS SUBJECTED TO CHANGE WIEEEE **/
				if(arrCustomer[0].id == 0){
					exception = true;
					printf("\n\tThere are no customers at the moment please try again\n\n");
				}
				else{
					while(exception2){
						printf("\tEnter your customer number: ");
						scanf("%d",&nCustomerNumber);
						exception2 = false;
						
						for(x = 0; x < 20 ; x++){
							if(nCustomerNumber == arrCustomer[x].id){
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
							customerMenu(arrCustomer, nCustomerNumber);
					}
				}
				break;
			case 3:
				mainMenu(arrCustomer);
				break;
			default:
				exception = true;
				fputs("\n\tInvalid input please try again\n\n",stderr);
				empty_stdin();
				break;
		}
	}
}

void
orderList (struct customer* arrCustomer, int customerNumber){
	short x, y, z;
	float sum;
	struct food foodList[] = {
	{1, 50.00, "Siomai\0"}, {2, 90.00, "Siopao\0"}, {3, 110.00, "Pares\0"},
	{4, 115.00, "Mami\0"}, {5, 85.00, "Chicken\0"}
	};

	for(x = 0; x < arrCustomer[customerNumber - 1].numOrder; x++){
		printf("\t(%d) ",x+1);
		printf("%s",foodList[arrCustomer[customerNumber - 1].order[x].food - 1].name);
		printf("\t%s", orderStatus(arrCustomer, customerNumber, x));
		printf("\n");
	}
	
	customerMenu(arrCustomer, customerNumber);
	
}


void
customerMenu (struct customer* arrCustomer, int customerNumber)
{
	bool found = false; // indicator if an array element is existing
	bool exception = true; // exception handler
	unsigned short menuChoice;
	short x, i; //iteration variable

	while(exception){
		printf("\n\t= = = = = CUSTOMER MENU = = = =  =\n");
		printf("\t");
		for(i=1; i<=17; i++)
			printf("==");
		printf("\n");
		
		printf("\t(1) Order Status\n");
		printf("\t(2) Display Customer Number\n");
		printf("\t(3) Pay\n");
		printf("\t(4) Exit\n");
		printf("\tInput: ");
		scanf("%d",&menuChoice);
		exception = false;
		
		switch(menuChoice){
			case 1:
				orderList(arrCustomer, customerNumber);
				break;
			case 2:
				printf("\n\tCustomer number: %02d\n", customerNumber);
				printf("\n\tStatus: %s\n", customerStatus(arrCustomer, customerNumber));
				exception = true;
				break;
			case 3:
				customerPay(arrCustomer, customerNumber);
				break;
			case 4:
				mainMenu(arrCustomer);
				break;
			default:
				exception = true;
				fputs("\n\tInvalid input please try again:\n\n",stderr);
				empty_stdin();
				break;
		}
	}
}

void
customerPay(struct customer* arrCustomer, int customerNumber)
{
	short x, y, z;
	float sum = 0;
	float fAmountPaid;
	struct food foodList[] = {
	{1, 50.00, "Siomai\0"}, {2, 90.00, "Siopao\0"}, {3, 110.00, "Pares\0"},
	{4, 115.00, "Mami\0"}, {5, 85.00, "Chicken\0"}
	};
	printf("\n");
	printf("\t%-15s%13s\n\n","Food","Price");
	for(x = 0; x < arrCustomer[customerNumber - 1].numOrder; x++){
		sum += foodList[arrCustomer[customerNumber - 1].order[x].food - 1].price;
		printf("\t(%d) ",x+1);
		printf("%-15s%10.2f\n",foodList[arrCustomer[customerNumber - 1].order[x].food - 1].name,
							   foodList[arrCustomer[customerNumber - 1].order[x].food - 1].price);
		printf("\n");
	}
	printf("\t%-19s%10.2f\n","Total",sum);
	printf("\tEnter Amount: ");
	scanf("%f",&fAmountPaid);
	customerMenu(arrCustomer,customerNumber);
}

/******  CUSTOMER FUNCTIONS END   ******/




/*****   WAITER FUNCTIONS START    *******/
void
waiter (struct customer* arrCustomer)
{
	short nOption;
	short i, j;
	bool exception = true;
	while(exception){
	
		printf("\n\t= = = = = = WAITER MENU = = = = = \n\t");
		for(i=1; i<=17; i++)
			printf("==");
			
		printf("\n\t(1) Send orders\n");
		printf("\t(2) View Orders\n");
		printf("\t(3) Serve dish\n");
		printf("\t(4) View paid\n");
		printf("\t(5) Exit\n");
		
		
		printf("\tInput: ");
		scanf("%d",&nOption);
		exception = false;
		switch(nOption){
			case 1:
				/*** THIS FUNCTION IS SUBJECT TO CHANGE WIEEE ***/
				if(arrCustomer[0].id == 0){
					printf("\tNo customers at the moment\n");
					exception = true;
				}
				else
					sendOrder(arrCustomer);
				break;
			case 2:
				viewOrder(arrCustomer);
				break;
			case 3:
				waiterSendDish(arrCustomer);
				break;
			case 4:
				break;
			case 5:
				mainMenu(arrCustomer);
				break;
			default:
				exception = true;
				fputs("\n\tInvalid input please try again:\n\n",stderr);
				empty_stdin();
				break;
		}
	}
}


void 
sendOrder (struct customer* arrCustomer)
{
	int i, j;
	for(i = 0; i < 20; i++){
		if(arrCustomer[i].id != 0){
			for(j = 0; j < arrCustomer[i].numOrder; j++){
				if(arrCustomer[i].order[j].status[0] == 'O')
					arrCustomer[i].order[j].status[0] = 'P';
					//printf("%c",arrCustomer[i].order[j].status[0]);
			}
		}			
	}
	printf("\n\tOrders sent!\n");
	waiter(arrCustomer);
}

void
viewOrder(struct customer* arrCustomer)
{
	char orderStat[15];
	short i, j, k;
	char food[15];
	
	struct food foodList[] = {
	{1, 50.00, "Siomai\0"}, {2, 90.00, "Siopao\0"}, {3, 110.00, "Pares\0"},
	{4, 115.00, "Mami\0"}, {5, 85.00, "Chicken\0"}
	};
	printf("\n\tPending Orders:\n");
	printf("\t");
	for(k = 1; k <= 17; k++)
		printf("==");
	printf("\n");
	printf("\t%-10s  %15s  %15s","Ordered By","Food","Status\n");
	for(i = 0; i < 20; i++){
		if(arrCustomer[i].id != 0){
			for(j = 0; j < arrCustomer[i].numOrder ; j++){
				strcpy(orderStat, orderStatus(arrCustomer, arrCustomer[i].id, j));
				strcpy(food, foodList[arrCustomer[i].order[j].food -1].name);
				printf("\t%-10s%02d %14s %14s \n","Customer no.",arrCustomer[i].id,food,orderStat);
			}
		}
	}
	waiter(arrCustomer);
	
}

void 
waiterSendDish(struct customer* arrCustomer)
{
	short i, j;
	for(i = 0; i < 20; i++){
		if(arrCustomer[i].id != 0){
			for(j = 0; j < arrCustomer[i].numOrder; j++){
				if(arrCustomer[i].order[j].status[0] == 'D'){
					arrCustomer[i].order[j].status[0] = 'E';
					arrCustomer[i].status[0] = 'E';
				}
			}
		}		
	}
	printf("Dishes Served!");
	waiter(arrCustomer);
}
/*****   WAITER FUNCTIONS END    *******/


/*****   CHEF FUNCTIONS START    *******/
void
chef(struct customer* arrCustomer)
{
	short nOption;
	short i, j;
	bool exception = true;
	while(exception){
	
		printf("\n\t= = = = = = CHEF MENU = = = = = \n\t");
		for(i=1; i<=17; i++)
			printf("==");
			
		printf("\n\t(1) View Pending Orders\n");
		printf("\t(2) Cook Dishes\n");
		printf("\t(3) Deliver Dishes\n");
		printf("\t(4) Exit\n");
		
		
		printf("\tInput: ");
		scanf("%d",&nOption);
		exception = false;
		switch(nOption){
			case 1:
				/*** SUBJECT TO CHANGE WIEEEEE  ***/
				if(arrCustomer[0].id == 0){
					printf("\tNo customers at the moment\n");
					exception = true;
				}
				else
					chefViewOrder(arrCustomer);
				break;
			case 2:
				cookOrder(arrCustomer);
				break;
			case 3:
				chefDeliverOrder(arrCustomer);
				break;
			case 4:
				mainMenu(arrCustomer);
				break;
			default:
				exception = true;
				fputs("\n\tInvalid input please try again:\n\n",stderr);
				empty_stdin();
				break;
		}
	}
}


void
cookOrder(struct customer* arrCustomer)
{
	short i, j;
	short cookedDishes = 0;
	for(i = 0; i < 20; i++){
		if(arrCustomer[i].id != 0 && cookedDishes < 3){
			for(j = 0; j < arrCustomer[i].numOrder; j++){
				if(arrCustomer[i].order[j].status[0] == 'P'){
					arrCustomer[i].order[j].status[0] = 'C';
					cookedDishes++;
				}
			}
		}		
	}

	printf("\n\tOrders Cooked!\n");
	chef(arrCustomer);
}

void
chefViewOrder(struct customer* arrCustomer)
{
	char orderStat[15];
	short i, j, k;
	char food[15];
	
	struct food foodList[] = {
	{1, 50.00, "Siomai\0"}, {2, 90.00, "Siopao\0"}, {3, 110.00, "Pares\0"},
	{4, 115.00, "Mami\0"}, {5, 85.00, "Chicken\0"}
	};
	printf("\n\tPending Orders:\n");
	printf("\t");
	for(k = 1; k <= 17; k++)
		printf("==");
	printf("\n");
	printf("\t%-10s  %15s  %15s","Ordered By","Food","Status\n");
	for(i = 0; i < 20; i++){
		if(arrCustomer[i].id != 0){
			for(j = 0; j < arrCustomer[i].numOrder ; j++){
				if(arrCustomer[i].order[j].status[0] == 'P' || arrCustomer[i].order[j].status[0] == 'C' ){
					strcpy(orderStat, orderStatus(arrCustomer, arrCustomer[i].id, j));
					strcpy(food, foodList[arrCustomer[i].order[j].food -1].name);
					printf("\t%-10s%02d %14s %14s \n","Customer no.",arrCustomer[i].id,food,orderStat);	
				}
				else
					printf("\n\tNo pending orders at the moment!\n");
				
			}
		}
	}
	chef(arrCustomer);
} 

void
chefDeliverOrder(struct customer* arrCustomer)
{
	short i, j;
	short cookedDishes = 0;
	for(i = 0; i < 20; i++){
		if(arrCustomer[i].id != 0 && cookedDishes < 3){
			for(j = 0; j < arrCustomer[i].numOrder; j++){
				if(arrCustomer[i].order[j].status[0] == 'C'){
					arrCustomer[i].order[j].status[0] = 'D';
					cookedDishes++;
				}
			}
		}		
	}
	chef(arrCustomer);
}

/*****   CHEF FUNCTIONS END   *******/




void 
mainMenu (struct customer* arrCustomer)
{
	short x, y; // iteration variables 
	
	unsigned short nOption; // main menu options (customer, waiter chef)
	
	bool nException = true; // exception handler
	
	char arrOptions[4][10] ={"Customer\n\0", "Waiter\n\0", "Chef\n\0", "Exit\n\0"};
	printf("\t= = = = WELCOME TO AAAAAAA = = = = \n");
	printf("\t");
	for(x=1; x<=17; x++)
		printf("==");
	printf("\n");

	while(nException){
	
		printf("\t= = = = = =  MAIN MENU = = = = = = \n");
		printf("\t");
		for(x=1; x<=17; x++)
			printf("==");
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
			printf("\n\t= = = = = = = CUSTOMER = = = = = =\n");
			printf("\t");
			for(x=1; x<=17; x++)
				printf("==");
			printf("\n");
			customer(arrCustomer);
			break;
		case 2: 
			waiter(arrCustomer);
			break;
		case 3:
			chef(arrCustomer);
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


int 
main()
{

	struct customer arrCustomer[] = {
	{0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"}, {0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"}, {0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"},
	{0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"}, {0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"}, {0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"},
	{0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"}, {0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"}, {0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"},
	{0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"}, {0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"}, {0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"},
	{0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"}, {0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"}, {0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"},
	{0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"}, {0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"}, {0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"},
	{0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"}, {0,0,0,"\0",0,0,"\0",0,0,"\0",1,"\0"}
	};
	

	
	mainMenu(arrCustomer);
	
	return 0;
}

