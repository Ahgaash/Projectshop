#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "management_mode.h"
#define CLIENTS_MAX 200
#define FI "customers_file.txt"

typedef struct {
  char last_name[100];
  char first_name[100];
} Customer;



void Read_customer(Customer customer[], int *nbr_customers);
void add_customer(Customer customer[], int *nbr_customers, char last_name[], char first_name[]);
void search_product_customer(Product products[], int num_products);
int load_products_cust(Product products[]);
void displayProducts(Product products[], int numProducts);
void updateQuantityInFile(Product products[], int numProducts);
void fillShoppingCart();
bool customerWantsToUnsubscribe();
void removeCustomerFromFile(Customer customer[], char last_name[], char first_name[]);
void removePurchaseHistoryFile(char last_name[], char first_name[]);
void savePurchaseHistory(const char* last_name, const char* first_name, const int cart[], const int cartQuantities[], const Product products[], int numCartItems);
void readLastThreePurchases(const char* last_name, const char* first_name);
int find_client(Customer customer[], int nbr_customers, char last_name[], char first_name[]);
int purchase_mode();