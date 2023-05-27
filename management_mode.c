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

void empty_buffer();

void save_products(Product products[], int num_products) {
  // Ouvre le fichier "All_vehicles.txt" en mode écriture
  FILE *f = fopen("All_vehicles.txt", "w");
  // Vérifie si l'ouverture du fichier a échoué
  if (f == NULL) {
    printf("Error: cannot open file to save products.\n");
    return; // Termine la fonction en cas d'échec
  }
  // Écrit le nombre total de produits dans le fichier
  fprintf(f, "%d\n", num_products);
  // Parcours chaque produit dans le tableau
  for (int i = 0; i < num_products; i++) {
    // Écrit les détails de chaque produit dans le fichier, séparés par des espaces
    fprintf(f, "%s %s %.2f %d\n", products[i].name, products[i].ref_number,
            products[i].price, products[i].quantity);
  }
  // Ferme le fichier pour libérer les ressources associées
  fclose(f);
}


int load_products(Product products[]) {
  // Ouvre le fichier "All_vehicles.txt" en mode lecture
  FILE *f = fopen("All_vehicles.txt", "r");
  // Vérifie si l'ouverture du fichier a échoué
  if (f == NULL) {
    printf("Product file not found.\n");
    return 0; // Termine la fonction en cas d'échec
  }
  int num_products; // Variable pour stocker le nombre total de produits
  fscanf(f, "%d\n", &num_products); // Lit le nombre total de produits depuis le fichier
  // Parcours chaque produit dans le tableau
  for (int i = 0; i < num_products; i++) {
    // Lit les détails de chaque produit depuis le fichier et les stocke dans le tableau
    fscanf(f, "%s %s %f %d\n", products[i].name, products[i].ref_number,
           &products[i].price, &products[i].quantity);
  }
  // Ferme le fichier pour libérer les ressources associées
  fclose(f);
  return num_products; // Retourne le nombre total de produits chargés
}


void print_products(Product products[], int num_products) {
  printf("List of products:\n");
  // Parcourt chaque produit dans le tableau
  for (int i = 0; i < num_products; i++) {
    // Affiche les détails de chaque produit
    printf("  - %s (%s) : %.2f € (quantity: %d)\n", products[i].name,
           products[i].ref_number, products[i].price, products[i].quantity);
  }
}


void search_product(Product products[], int num_products) {
  char search_term[50]; // Variable pour stocker le terme de recherche saisi par l'utilisateur
  printf("Enter the name or reference number of the product you are looking for: ");
  scanf("%s", search_term); // Lit le terme de recherche saisi par l'utilisateur
  int found = 0; // Variable pour indiquer si un produit correspondant a été trouvé
  // Parcourt chaque produit dans le tableau
  for (int i = 0; i < num_products; i++) {
    // Vérifie si le nom ou le numéro de référence du produit correspond au terme de recherche
    if (strcmp(products[i].name, search_term) == 0 ||
        strcmp(products[i].ref_number, search_term) == 0) {
      printf("Product found:\n");
      // Affiche les détails du produit correspondant
      printf("  - %s (%s) : %.2f€ (quantity: %d)\n", products[i].name,
             products[i].ref_number, products[i].price, products[i].quantity);
      found = 1; // Marque le produit comme trouvé
      break; // Sort de la boucle, car le produit a été trouvé
    }
  }
  if (!found) {
    printf("No products match your search.\n");
  }
}


void add_product(Product products[], int *num_products) {
  // Vérifie si le nombre maximum de produits a été atteint
  if (*num_products == MAX_PRODUCTS) {
    printf("Unable to add new product. %d product limit has been reached.\n", MAX_PRODUCTS);
    return; // Termine la fonction si le nombre maximum de produits est atteint
  }
  // Demande à l'utilisateur d'entrer les détails du nouveau produit
  printf("Enter the product name: ");
  scanf("%s", products[*num_products].name);
  printf("Enter the product reference number: ");
  scanf("%s", products[*num_products].ref_number);
  printf("Enter the product price: ");
  scanf("%f", &products[*num_products].price);
  empty_buffer();
  printf("Enter the quantity of the product: ");
  scanf("%d", &products[*num_products].quantity);
  empty_buffer();
  printf("Enter the product size (small/medium/big): ");
  char size[10];
  scanf("%s", size);
  int quantity_factor;
  // Détermine le facteur de quantité en fonction de la taille du produit
  if (strcmp(size, "small") == 0) {
    quantity_factor = 1;
  } else if (strcmp(size, "medium") == 0) {
    quantity_factor = 2;
  } else if (strcmp(size, "big") == 0) {
    quantity_factor = 4;
  } else {
    printf("Invalid product size.\n");
    return; // Termine la fonction si la taille du produit est invalide
  }
  // Applique le facteur de quantité au produit
  products[*num_products].quantity *= quantity_factor;
  // Ouverture du fichier en mode "append" pour ajouter le nouveau produit
  FILE *fp = fopen("All_vehicles.txt", "a");
  if (fp == NULL) {
    printf("Error: cannot open the file All_vehicles.txt\n");
    return; // Termine la fonction si l'ouverture du fichier échoue
  }
  // Écrit les détails du nouveau produit dans le fichier
  fprintf(fp, "%s,%s,%.2f,%d,%s\n", products[*num_products].name,
          products[*num_products].ref_number, products[*num_products].price,
          products[*num_products].quantity, size);
  fclose(fp); // Ferme le fichier
  (*num_products)++; // Incrémente le nombre total de produits
  printf("Product has been successfully added.\n");
}



void remove_product(Product products[], int *num_products) {
  char search_term[50]; // Variable pour stocker le terme de recherche saisi par l'utilisateur
  printf("Enter the name or reference number of the product to be deleted: ");
  scanf("%s", search_term); // Lit le terme de recherche saisi par l'utilisateur
  int found = 0; // Variable pour indiquer si un produit correspondant a été trouvé
  // Parcourt chaque produit dans le tableau
  for (int i = 0; i < *num_products; i++) {
    // Vérifie si le nom ou le numéro de référence du produit correspond au terme de recherche
    if (strcmp(products[i].name, search_term) == 0 ||
        strcmp(products[i].ref_number, search_term) == 0) {
      printf("Product found and deleted:\n");
      // Affiche les détails du produit correspondant qui va être supprimé
      printf(" - %s (%s) : %.2f € (quantity: %d)\n", products[i].name,
             products[i].ref_number, products[i].price, products[i].quantity);
      // Décale les produits restants vers la gauche pour remplacer le produit supprimé
      for (int j = i; j < *num_products - 1; j++) {
        products[j] = products[j + 1];
      }
      (*num_products)--; // Décrémente le nombre total de produits
      found = 1; // Marque le produit comme trouvé
      break; // Sort de la boucle, car le produit a été trouvé et supprimé
    }
  }
  if (!found) {
    printf("No products match your search.\n");
  }
}


void check_stock(Product products[], int num_products) {
  printf("\nList of products with stock at 0:\n");
  // Parcourt chaque produit dans le tableau
  for (int i = 0; i < num_products; i++) {
    // Vérifie si la quantité du produit est à zéro
    if (products[i].quantity == 0) {
      // Affiche les détails du produit avec une quantité de zéro
      printf(" - %s (%s) : %.2f€ (quantity: %d)\n", products[i].name,
             products[i].ref_number, products[i].price, products[i].quantity);
    }
  }
  printf("\nList of 5 products with the lowest quantity:\n");
  // Trie les produits par quantité croissante en utilisant l'algorithme de tri par sélection
  for (int i = 0; i < num_products - 1; i++) {
    for (int j = i + 1; j < num_products; j++) {
      if (products[j].quantity < products[i].quantity) {
        // Échange les positions des produits dans le tableau pour les trier
        Product temp = products[i];
        products[i] = products[j];
        products[j] = temp;
      }
    }
  }
  int count = 0;
  // Affiche les détails des cinq produits avec la plus faible quantité (supérieure à zéro)
  for (int i = 0; i < num_products && count < 5; i++) {
    if (products[i].quantity > 0) {
      printf(" - %s (%s) : %.2f€ (quantity: %d)\n", products[i].name,
             products[i].ref_number, products[i].price, products[i].quantity);
      count++;
    }
  }
}

void add_quantity(Product products[], int num_products) {
  char search_term[MAX_QUANTITY]; // Variable pour stocker le terme de recherche saisi par l'utilisateur
  printf("Enter the product name or reference: ");
  scanf("%s", search_term); // Lit le terme de recherche saisi par l'utilisateur
  int found = 0; // Variable pour indiquer si un produit correspondant a été trouvé
  // Parcourt chaque produit dans le tableau
  for (int i = 0; i < num_products; i++) {
    // Vérifie si le nom ou le numéro de référence du produit correspond au terme de recherche
    if (strcmp(products[i].name, search_term) == 0 ||
        strcmp(products[i].ref_number, search_term) == 0) {
      int quantity, size_factor;
      printf("Enter the quantity to add or remove for the product %s: ", products[i].name);
      scanf("%d", &quantity);// Lit la quantité à ajouter ou à supprimer
      empty_buffer();
      printf("Enter the size of the product %s : ", products[i].name);
      char size[10];
      scanf("%s", size); // Lit la taille du produit
      // Associe un facteur à la taille du produit pour ajuster la quantité
      if (strcmp(size, "small") == 0) {
        size_factor = 1;
      } else if (strcmp(size, "medium") == 0) {
        size_factor = 2;
      } else if (strcmp(size, "big") == 0) {
        size_factor = 4;
      } else {
        printf("Invalid size. Quantity cannot be changed.\n");
        return;
      }
      // Modifie la quantité du produit en fonction de la quantité saisie et du facteur de taille
      products[i].quantity += quantity * size_factor;

      found = 1;
      break;
    }
  }
  if (found) {
    FILE *fp = fopen("All_vehicles.txt", "w");
    if (fp == NULL) {
      printf("Error: cannot open the file All_vehicles.txt\n");
      return;
    }
    // Écrit les produits modifiés dans le fichier
    for (int i = 0; i < num_products; i++) {
      fprintf(fp, "%s %s %.2f %d %s\n", products[i].name, products[i].ref_number,
              products[i].price, products[i].quantity, products[i].size);
    }
    fclose(fp);
    printf("The quantity has been successfully added.\n");
  } else {
    printf("No products found with name or reference %s\n", search_term);
  }
}



void sorted_products(char *file_name) {
  FILE *fp = fopen(file_name, "r");
  if (fp == NULL) {
    printf("Error:The file cannot be opened.\n");
    return;
  }
  // Ouverture des fichiers de sortie pour chaque catégorie de produits
  FILE *fp_c = fopen("compacts.txt", "w");
  FILE *fp_msuv = fopen("mini_SUV.txt", "w");
  FILE *fp_se = fopen("sedans.txt", "w");
  FILE *fp_br = fopen("break.txt", "w");
  FILE *fp_suv = fopen("SUV.txt", "w");
  FILE *fp_sp = fopen("sports.txt", "w");
  char line[100];
  while (fgets(line, 100, fp) != NULL) {
    char ref_number[10];
    char name[30];
    int quantity;
    float price;
    // Extraction des informations du produit à partir de la ligne lue
    sscanf(line, "%s %s %f %d", name, ref_number, &price, &quantity);
    // Écriture des informations dans le fichier approprié en fonction du numéro de référence
    if (strncmp(ref_number, "C", 1) == 0) {
      fprintf(fp_c, "%s,%s,%.2f,%d\n", name, ref_number, price, quantity);
    }
    else if (strncmp(ref_number, "MSUV", 4) == 0) {
      fprintf(fp_msuv, "%s,%s,%.2f,%d\n", name, ref_number, price, quantity);
    }
    else if (strncmp(ref_number, "SE", 2) == 0) {
      fprintf(fp_se, "%s,%s,%.2f,%d\n", name, ref_number, price, quantity);
    } 
    else if (strncmp(ref_number, "BR", 2) == 0) {
      fprintf(fp_br, "%s,%s,%.2f,%d\n", name, ref_number, price, quantity);
    } 
    else if (strncmp(ref_number, "SUV", 3) == 0) {
      fprintf(fp_suv, "%s,%s,%.2f,%d\n", name, ref_number, price, quantity);
    }
    else if (strncmp(ref_number, "SP", 2) == 0) {
      fprintf(fp_sp, "%s,%s,%.2f,%d\n", name, ref_number, price, quantity);
    }
    else {
      printf("Invalid reference\n");
    }
  }
  // Fermeture des fichiers
  fclose(fp);
  fclose(fp_c);
  fclose(fp_msuv);
  fclose(fp_se);
  fclose(fp_br);
  fclose(fp_suv);
  fclose(fp_sp);
}
void empty_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

int management_mode() {
  Product products[MAX_PRODUCTS];
  int num_products = load_products(products);
  int choice;
  char *file_name = "All_vehicles.txt";
  Product place;
  do {
    check_stock(products, num_products);
    printf("\n What do you want to do?\n");
    printf("  1. View list of products\n");
    printf("  2. Find a product\n");
    printf("  3. Add a product\n");
    printf("  4. Remove a product\n");
    printf("  5. Add/Remove Quantity\n");
    printf("  6. Put into/Update Vehicle Categories\n");
    printf("  7. Exit the program\n");
    printf("Your Choice : ");
    scanf("%d", &choice);
    empty_buffer();
    
    switch (choice) {
    case 1:
      print_products(products, num_products);
      break;
    case 2:
      search_product(products, num_products);
      break;
    case 3:
      add_product(products, &num_products);
      save_products(products, num_products);
      break;
    case 4:
      remove_product(products, &num_products);
      save_products(products, num_products);
      break;
    case 5:
      add_quantity(products, num_products);
      break;
    case 6:
      sorted_products(file_name);
      printf("\nThe information has been updated.\n");
      break;
    case 7:
      printf("\n Goodbye! 👋 \n");
      break;
    default:
      printf("\nInvalid choice. Please try again.\n");
    }
  } while (choice != 7);

  return 0;
}
