#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Structure to hold coffee details
typedef struct Coffee
{
  int id;        // Unique identifier for the coffee
  char name[50]; // Name of the coffee
  float price;   // Price of the coffee
} Coffee;
// Structure to hold order details
typedef struct Order
{
  int orderId;        // Unique identifier for the order
  Coffee coffee;      // Coffee being ordered
  int quantity;       // Quantity of the coffee ordered
  int sugarAmount;    // Amount of sugar in the coffee
  struct Order *next; // Pointer to the next order in the linked list
} Order;
Order *head = NULL;    // Head of the linked list of orders
int orderCount = 0;    // Counter to keep track of the number of orders
char customerName[50]; // Customer's name
char phoneNumber[50];  // Customer's phone number
char address[50];      // Customer's address
// Function declarations
void displayMenu();
void placeOrder();
void viewOrders();
void updateOrder();
void deleteOrder();
void searchOrder();
void printInvoice();
void displayOrderDetails(Order *order);

// Array to hold coffee menu items
Coffee coffeeMenu[] = {
    {1, "Milk Tea", 1.50},
    {2, "Tea Latte", 2.75},
    {3, "Matcha Latte", 5.25},
    {4, "Passion Aloe Vera", 2.00},
    {5, "Passion Cream", 3.75},
    {6, "Cappuccino", 3.75},
    {7, "Chocolate Cream", 3.50},
    {8, "Coffee Milk", 2.50},
    {9, "Americano", 5.99},
    {10, "Ice Latte", 3.55},
};

int main()
{
  int choice;
  // Collecting personal information from the user
  printf("\n\t______ Please fill in personal information _____\n");
  printf("\n\tName: ");
  gets(customerName);
  printf("\tPhone number: ");
  gets(phoneNumber);
  printf("\tAddress: ");
  gets(address);
  printf("\n\t______  Your personal information ______\n");
  printf("\tName: %s\n\tPhone number: %s\n\tAddress: %s\n", customerName, phoneNumber, address);

  // Main menu loop
  while (1)
  {
  backMenu:
    printf("\n\t_____ Coffee Ordering System ______\n");
    printf("\n\t1. View Coffee Menu\n");
    printf("\t2. Place an Order\n");
    printf("\t3. View All Orders\n");
    printf("\t4. Update an Order\n");
    printf("\t5. Delete an Order\n");
    printf("\t6. Search an Order\n");
    printf("\t7. Show Invoice\n");
    printf("\t8. Exit\n");
    printf("\tEnter your choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      displayMenu();
      break;
    case 2:
      placeOrder();
      break;
    case 3:
      viewOrders();
      break;
    case 4:
      updateOrder();
      break;
    case 5:
      deleteOrder();
      break;
    case 6:
      searchOrder();
      break;
    case 7:
      printInvoice();
      break;
    case 8:
      exit(0); // Exit the program
      break;
    default:
      printf("\tInvalid choice! Please try again.\n");
    }
  }
  return 0;
}

// Function to display the coffee menu
void displayMenu()
{
  printf("\n\t_________Menu____________\n\n");
  for (int i = 0; i < sizeof(coffeeMenu) / sizeof(Coffee); i++)
  {
    printf("\t%d. %s  ( $%.2f)\n", coffeeMenu[i].id, coffeeMenu[i].name, coffeeMenu[i].price);
  }
  printf("\t11. Back\n");
}

// Function to place an order
void placeOrder()
{
  int coffeeChoice, sugarAmount, quantity;
  char continueShopping;

  do
  {
    displayMenu();
    printf("\tChoose the drink you want to buy (From 1-10): ");
    scanf("%d", &coffeeChoice);
    if (coffeeChoice == 11)
    {
      return; // Return to the main menu
    }

    if (coffeeChoice < 1 || coffeeChoice > sizeof(coffeeMenu) / sizeof(Coffee))
    {
      printf("\tInvalid choice! Please try again.\n");
      continue;
    }

    printf("\n\t________ %s___________\n", coffeeMenu[coffeeChoice - 1].name);
    printf("\n\tEnter the quantity: ");
    scanf("%d", &quantity);

    if (quantity < 1)
    {
      printf("\tInvalid quantity! Please try again.\n");
      continue;
    }

    printf("\tEnter the amount of sugar (0-100): ");
    scanf("%d", &sugarAmount);

    if (sugarAmount < 0 || sugarAmount > 100)
    {
      printf("\tInvalid sugar amount! Please try again.\n");
      continue;
    }

    // Creating a new order
    Order *newOrder = (Order *)malloc(sizeof(Order));
    newOrder->orderId = ++orderCount;
    newOrder->coffee = coffeeMenu[coffeeChoice - 1];
    newOrder->quantity = quantity;
    newOrder->sugarAmount = sugarAmount;
    newOrder->next = NULL;

    // Adding the new order to the linked list
    if (head == NULL)
    {
      head = newOrder;
    }
    else
    {
      Order *temp = head;
      while (temp->next != NULL)
      {
        temp = temp->next;
      }
      temp->next = newOrder;
    }
  back:
    // Menu for continuing or managing orders
    printf("\n\t1. Continue order\n");
    printf("\t2. Update an order\n");
    printf("\t3. Delete an order\n");
    printf("\t4. Back to menu\n");
    printf("\t5. Stop order and show invoice\n");
    printf("\tEnter your choice: ");
    scanf(" %c", &continueShopping);
    switch (continueShopping)
    {
    case '1':
      continueShopping = 'y';
      break;
    case '2':
      updateOrder();
      goto back;
      break;
    case '3':
      deleteOrder();
      goto back;
      break;
    case '4':
      return;
    case '5':
      continueShopping = 'n'; // Exit order
      break;
    default:
      printf("\tInvalid choice! Please try again.\n");
      continueShopping = 'y';
    }

  } while (continueShopping == 'y' || continueShopping == 'Y');

  printf("\tOrder placed successfully!\n");
  printInvoice();
}

// Function to view all orders
void viewOrders()
{
  if (head == NULL)
  {
    printf("\tNo orders placed yet.\n");
    return;
  }
  Order *temp = head;
  printf("\n\t_____ All Orders ______\n");
  while (temp != NULL)
  {
    displayOrderDetails(temp);
    temp = temp->next;
  }
}

// Function to update an existing order
void updateOrder()
{
  int id, sugarAmount, quantity;
  if (head == NULL)
  {
    printf("\tNo orders to update.\n");
    return;
  }
  viewOrders();
  printf("\n\tEnter the Order ID to update: ");
  scanf("%d", &id);
  Order *temp = head;
  while (temp != NULL && temp->orderId != id)
  {
    temp = temp->next;
  }
  if (temp == NULL)
  {
    printf("\tOrder not found!\n");
    return;
  }
  printf("\tEnter new quantity: ");
  scanf("%d", &quantity);
  printf("\tEnter new sugar amount (0-100): ");
  scanf("%d", &sugarAmount);
  temp->quantity = quantity;
  temp->sugarAmount = sugarAmount;
  printf("\tOrder updated successfully!\n");
  printf("\t________ After update_________\n\n");
  displayOrderDetails(temp);
}
// Function to delete an existing order
void deleteOrder()
{
  int id;
  if (head == NULL)
  {
    printf("\tNo orders to delete.\n");
    return;
  }
  viewOrders(); // Display all orders to help the user identify the order ID
  printf("\tEnter the Order ID to delete: ");
  scanf("%d", &id);
  Order *temp = head;
  Order *prev = NULL;
  // Find the order to delete
  while (temp != NULL && temp->orderId != id)
  {
    prev = temp;
    temp = temp->next;
  }
  if (temp == NULL)
  {
    printf("\tOrder not found!\n");
    return;
  }
  // Delete the order
  if (prev == NULL)
  {
    head = temp->next;
  }
  else
  {
    prev->next = temp->next;
  }
  free(temp);
  printf("\tOrder deleted successfully!\n");
}

void searchOrder()
{
  int id;
  printf("\tEnter the Order ID to search: ");
  scanf("%d", &id);
  Order *temp = head;
  // Search for the order
  while (temp != NULL && temp->orderId != id)
  {
    temp = temp->next;
  }

  if (temp == NULL)
  {
    printf("\tOrder not found!\n");
    return;
  }
  // Display order details
  printf("\n\t_____ Order Details ______\n");
  displayOrderDetails(temp);
}
void printInvoice()
{
  Order *temp = head;
  float totalAmountPrice = 0;
  int totalQuantity = 0;
  if (temp == NULL)
  {
    printf("\tNo orders to print invoice.\n");
    return;
  }
  printf("\n\t_____ Invoice _____\n\n");
  printf("\tCustomer Name: %s\n", customerName);
  printf("\tPhone Number: %s\n", phoneNumber);
  printf("\tAddress: %s\n\n", address);
  // Print each order and calculate totals
  while (temp != NULL)
  {
    displayOrderDetails(temp);
    totalAmountPrice += temp->coffee.price * temp->quantity;
    totalQuantity += temp->quantity;
    temp = temp->next;
  }
  printf("\tTotal Quantity: %d\n", totalQuantity);
  printf("\tTotal Amount Price: $%.2f\n", totalAmountPrice);
}

void displayOrderDetails(Order *order)
{
  printf("\tOrder ID: %d\n", order->orderId);
  printf("\tCoffee: %s\n", order->coffee.name);
  printf("\tQuantity: %d\n", order->quantity);
  printf("\tSugar Amount: %d\n", order->sugarAmount);
  printf("\tPrice: $%.2f\n", order->coffee.price * order->quantity); // Added price calculation
}
