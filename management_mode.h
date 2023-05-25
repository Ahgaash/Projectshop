#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_PRODUCTS 100
#define MAX_QUANTITY 300


typedef struct {
  char name[50];
  char ref_number[10];
  float price;
  int quantity;
  char size[10];
} Product;


void save_products(Product products[], int num_products);
int load_products(Product products[]);
void print_products(Product products[], int num_products);
void search_product(Product products[], int num_products);
void add_product(Product products[], int *num_products);
void remove_product(Product products[], int *num_products);
void check_stock(Product products[], int num_products);
void add_quantity(Product products[], int num_products);
void sorted_products(char *file_name);
void empty_buffer();
int management_mode();