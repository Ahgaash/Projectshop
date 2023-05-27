#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "management_mode.h"

#define FILENAME "All_vehicles.txt"
#define TEMP_FILENAME "temp.txt"
#define CLIENTS_MAX 20
#define FI "customers_file.txt"

typedef struct {
  char last_name[100];
  char first_name[100];
} Customer;

int load_products_cust(Product products[]) {
  // Ouvre le fichier "All_vehicles.txt" en mode lecture
  FILE *f = fopen(FILENAME, "r");
  // Vérifie si l'ouverture du fichier a échoué
  if (f == NULL) {
    printf("Product file not found.\n");
    return 0;// Termine la fonction en cas d'échec
  }
  int num_products; // Variable pour stocker le nombre total de produits
  fscanf(f, "%d\n", &num_products);// Lit le nombre total de produits depuis le fichier
  // Parcours chaque produit dans le tableau
  for (int i = 0; i < num_products; i++) {
    // Lit les détails de chaque produit depuis le fichier et les stocke dans le tableau
    fscanf(f, "%s %s %f %d\n", products[i].name, products[i].ref_number,
           &products[i].price, &products[i].quantity);
  }
  fclose(f);// Ferme le fichier pour libérer les ressources associées
  return num_products;// Retourne le nombre total de produits chargés
}

void Read_customer(Customer customer[], int *nbr_customers) {
  char last_name[100];
  char first_name[100];
  FILE *file = fopen(FI, "r");
  if (file != NULL) {
    while (fscanf(file, "%s %s", last_name, first_name) == 2 && *nbr_customers < CLIENTS_MAX) {
      strncpy(customer[*nbr_customers].first_name, first_name, sizeof(customer[*nbr_customers].first_name));
      strncpy(customer[*nbr_customers].last_name, last_name, sizeof(customer[*nbr_customers].last_name));
      (*nbr_customers)++;
    }
    fclose(file);
  }
}

void add_customer(Customer customer[], int *nbr_customers, char last_name[], char first_name[]) {
  if (*nbr_customers < CLIENTS_MAX) {
    strncpy(customer[*nbr_customers].first_name, first_name, sizeof(customer[*nbr_customers].first_name));
    strncpy(customer[*nbr_customers].last_name, last_name, sizeof(customer[*nbr_customers].last_name));
    (*nbr_customers)++;
    FILE *file = fopen(FI, "a");
    fprintf(file, "%s %s\n", last_name, first_name);
    fclose(file);
    printf("\nThanks and welcome %s %s !\n", last_name, first_name);
  } else {
    printf("\nMaximum number of customers reached\n");
  }
}

int find_client(Customer customer[], int nbr_customers, char last_name[], char first_name[]) {
  int i;
  for (i = 0; i < nbr_customers; i++) {
    if (strcmp(customer[i].last_name, last_name) == 0 && strcmp(customer[i].first_name, first_name) == 0) {
      return i;
    }
  }
  return -1;
}
void search_product_customer(Product products[], int num_products) {
  char search_term[50];
  printf("\nEnter the name of the product you are looking for : ");
  scanf("%s", search_term);
  int found=0;
  for (int i = 0; i < num_products; i++) {
    if (strcmp(products[i].name, search_term) == 0) {
      printf("Product found:\n");
      printf("  - %s: %.2f€\n", products[i].name, products[i].price);
      found = 1;
      break;
    }
  }
  if (!found) {
    printf("No products match your search.\n");
  }
}
void displayProducts(Product products[], int numProducts) {
    printf("\nAvailable products :\n");
    for (int i = 0; i < numProducts; i++) {
        printf("%s: price (%.2f €)\n",products[i].name, products[i].price);
    }
}
void updateQuantityInFile(Product products[], int numProducts) {
    FILE* file = fopen(FILENAME, "w");  // Ouverture du fichier en mode écriture
    if (file == NULL) {
        printf("Error opening file %s.\n", FILENAME);
        return;
    }

    fprintf(file, "%d\n", numProducts);  // Écriture du nombre total de produits dans le fichier

    for (int i = 0; i < numProducts; i++) {
        fprintf(file, "%s %s %.2f %d\n", products[i].name, products[i].ref_number,
                products[i].price, products[i].quantity);  // Écriture des informations de chaque produit dans le fichier
    }

    fclose(file);  // Fermeture du fichier
}
void savePurchaseHistory(const char* last_name, const char* first_name, const int cart[], const int cartQuantities[], const Product products[], int numCartItems) {
    char fileName[100];  // Variable pour stocker le nom du fichier
    sprintf(fileName, "%s_%s.txt", last_name, first_name);  // Création du nom du fichier en utilisant les noms du client

    FILE* file = fopen(fileName, "a");  // Ouverture du fichier en mode ajout (append)
    if (file == NULL) {
        printf("Error opening file %s.\n", fileName);
        return;
    }

    for (int i = 0; i < numCartItems; i++) {
        int index = cart[i];  // Indice du produit dans le panier
        fprintf(file, "%s\t\t%.2f\t%d\n", products[index].name, products[index].price, cartQuantities[i]);  // Écriture des informations du produit dans le fichier
    }

    fclose(file);  // Fermeture du fichier
    printf("Purchase history recorded in the %s file.\n", fileName);
}
void readLastThreePurchases(const char* last_name, const char* first_name) {
    char fileName[100];  // Variable pour stocker le nom du fichier
    sprintf(fileName, "%s_%s.txt", first_name, last_name);  // Création du nom du fichier en utilisant les noms du client

    FILE* file = fopen(fileName, "r");  // Ouverture du fichier en lecture
    if (file == NULL) {
        printf("You have no purchase history.\n");
        return;
    }

    char line[100];  // Variable pour stocker chaque ligne lue depuis le fichier
    int numLines = 0;  // Nombre total de lignes dans le fichier
    while (fgets(line, sizeof(line), file) != NULL) {
        numLines++;
    }

    fseek(file, 0, SEEK_SET);  // Retour au début du fichier
    int startLine = (numLines >= 3) ? (numLines - 3) : 0;  // Ligne de début de lecture (les 3 dernières lignes ou le début du fichier)
    int currentLine = 0;  // Compteur de ligne courante

    while (fgets(line, sizeof(line), file) != NULL) {
        if (currentLine >= startLine) {
            printf("%s", line);  // Affichage de la ligne (historique d'achat)
        }
        currentLine++;
    }

    fclose(file);  // Fermeture du fichier
}


void removeCustomerFromFile(Customer customer[], char last_name[], char first_name[]) {
    // Ouvrir le fichier en lecture
    FILE *file = fopen(FI, "r");
    if (file == NULL) {
        printf("Error while opening the file %s.\n", FI);
        return;
    }

    // Créer un fichier temporaire pour stocker les clients sans celui à supprimer
    FILE *tempFile = fopen("temp_customer_file.txt", "w");
    if (tempFile == NULL) {
        printf("Error while creating the temporary file.\n");
        fclose(file);
        return;
    }

    // Parcourir le fichier et copier tous les clients sauf celui à supprimer dans le fichier temporaire
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        char current_last_name[50], current_first_name[50];
        sscanf(line, "%s %s", current_last_name, current_first_name);

        if (strcmp(current_last_name, last_name) != 0 || strcmp(current_first_name, first_name) != 0) {
            fputs(line, tempFile);
        }
    }

    // Fermer les fichiers
    fclose(file);
    fclose(tempFile);

    // Supprimer le fichier original
    remove(FI);

    // Renommer le fichier temporaire pour le remplacer
    rename("temp_customer_file.txt", FI);

    printf("The customer has been successfully removed.\n");
}
void removePurchaseHistoryFile(char last_name[], char first_name[]) {
    // Construire le nom du fichier d'historique d'achat du client
    char filename[100];
    snprintf(filename, sizeof(filename), "%s_%s.txt", first_name, last_name);

    // Supprimer le fichier d'historique d'achat
    if (remove(filename) == 0) {
        printf("The purchase history file has been successfully deleted.\n");
    } else {
        printf("Error when deleting the purchase history file.\n");
    }
}


void fillShoppingCart(Customer customer[], char last_name[], char first_name[]) {
    Product products[MAX_PRODUCTS];  // Tableau de produits
    int numProducts = 0;  // Nombre de produits disponibles
    char size[10];  // Variable pour stocker la taille du produit choisi
    int nbr_customers = 0;  // Variable pour le nombre de clients
    FILE *file = fopen(FILENAME, "r");  // Ouverture du fichier de produits en lecture
    if (file == NULL) {
        printf("Error opening file %s.\n", FILENAME);
        return;
    }

    char line[256];
    fgets(line, sizeof(line), file);  // Lecture de la première ligne du fichier

    // Lecture des produits du fichier
    while (fscanf(file, "%s %s %f %d", products[numProducts].name, products[numProducts].ref_number,
              &products[numProducts].price, &products[numProducts].quantity) == 4) {
        numProducts++;
    }

    fclose(file);  // Fermeture du fichier

    // Affichage des produits disponibles
    printf("\nList of available products :\n");
    for (int i = 0; i < numProducts; i++) {
        printf("%d. %s  - Price ( %.2f EUR)\n", i + 1, products[i].name,  products[i].price);
    }

    int cart[MAX_PRODUCTS];  // Tableau pour stocker les indices des produits choisis
    int cartQuantities[MAX_PRODUCTS];  // Tableau pour stocker les quantités des produits choisis
    int numCartItems = 0;  // Nombre d'articles dans le panier
    float totalPrice = 0.0;  // Prix total dans le panier
    // Boucle pour choisir les produits à ajouter au panier
    while (1) {  // Boucle infinie, on sortira de la boucle avec un "break"
        int choice, quantity;
        printf("\n Select the product number from the catalog or 0 to finish your cart : ");
        scanf("%d", &choice);
        empty_buffer();

        if (choice == 0)
            break;

        choice--;

        // Vérification si le choix est valide
        if (choice < 0 || choice >= numProducts) {
            printf("Invalid product.\n");
            continue;
        }

        // Vérification si le produit est en stock
        if (products[choice].quantity == 0) {
            printf("Sorry, we are out of stock for this product.\n");
            // if (customerWantsToUnsubscribe()) {
                 char answer;
                printf("Would you like to unsubscribe (y/n) 😞? ");
                scanf(" %c", &answer);
                if (answer == 'y' || answer == 'Y') {
                removeCustomerFromFile(customer, last_name, first_name);
                removePurchaseHistoryFile(last_name, first_name);
                printf("You have been successfully unsubscribed.\n");
                exit(EXIT_SUCCESS);
            } 
            else if (answer == 'n' || answer == 'N') {
              printf("Merci de rester avec nous 👍");
            continue;}
           else {
             printf ("Invalide choice");
             continue;
           }
        }

        printf("How many do you want : ");
        scanf("%d", &quantity);
        empty_buffer();

        // Vérification de la validité de la quantité choisie
        if (quantity <= 0 || quantity > products[choice].quantity) {
            printf("Invalid quantity.\n");
            continue;
        }

        printf("Size (small, medium, big) : ");
        scanf("%s", size);

        // Multiplication de la quantité en fonction de la taille choisie
        if (strcmp(size, "small") == 0)
            quantity *= 1;
        else if (strcmp(size, "medium") == 0)
            quantity *= 2;
        else if (strcmp(size, "big") == 0)
            quantity *= 4;
        else {
            printf("Invalid size.\n");
            continue;
        }

        // Vérification de la validité de la quantité après multiplication
        if (quantity <= 0 || quantity > products[choice].quantity) {
            printf("Invalid quantity.\n");
            continue;
        }

        // Ajout du produit au panier
        cart[numCartItems] = choice;
        cartQuantities[numCartItems] = quantity;
        numCartItems++;
        totalPrice += (products[choice].price * quantity);

        // Mise à jour de la quantité dans la structure de produits
        products[choice].quantity -= quantity;
    }

    // Affichage du contenu du panier
    printf("\nProducts in the cart :\n");
    for (int i = 0; i < numCartItems; i++) {
        int index = cart[i];
        printf("%d x %s  - price ( %.2f EUR)\n", cartQuantities[i], products[index].name, products[index].price);
    }

    printf("Total cart price: %.2f EUR\n", totalPrice);


    char confirmation;
    printf("Confirm cart (y/n) ? ");
    scanf(" %c", &confirmation);

    if (confirmation == 'y' || confirmation == 'Y') {
        printf("Payment done. Thank you for your purchase! 😁\n");
        updateQuantityInFile(products, numProducts);  // Mise à jour de la quantité dans le fichier
        savePurchaseHistory(first_name, last_name, cart, cartQuantities, products, numCartItems);  // Sauvegarde de l'historique d'achat
    } else if (confirmation == 'n' || confirmation == 'N') {
        // Annulation du panier, restauration des quantités de produits
        for (int i = 0; i < numCartItems; i++) {
            int index = cart[i];
            products[index].quantity += cartQuantities[i];
        }

        printf("Items in cart removed successfully\n");
    } else {
        printf("Error\n");
        // En cas d'erreur, restauration des quantités de produits
        for (int i = 0; i < numCartItems; i++) {
            int index = cart[i];
            products[index].quantity += cartQuantities[i];
        }
    }
}





int purchase_mode() {
  Customer customer[CLIENTS_MAX];
  int nbr_customers = 0;
  char last_name[100];
  char first_name[100];
  int existing_customer = -1;
  Product products[MAX_PRODUCTS];
  int choice;
  int cart[MAX_PRODUCTS];
  int cartSize = 0;
  int num_products= load_products_cust(products);
   char answer;
  Read_customer(customer, &nbr_customers);

  printf("\nEnter the customer's last name\n");
  scanf("%s", last_name);

  printf("Enter the customer's first name\n");
  scanf("%s", first_name);

  existing_customer = find_client(customer, nbr_customers, last_name, first_name);
  if (existing_customer == -1) {
    add_customer(customer, &nbr_customers, last_name, first_name);
  } else {
    printf("~ Welcome back %s %s ~\n", last_name, first_name);
    readLastThreePurchases(last_name,  first_name);

  } 
 do {
    printf("\n What do you want to do?\n");
    printf("  1. View Product List\n");
    printf("  2. Search products\n");
    printf("  3. Add to cart\n");
    printf("  4. Unsubscribe\n");
    printf("  5. Exit the program\n");
    printf("Your Choice : ");
    scanf("%d", &choice);
    empty_buffer();

    switch (choice) {
        case 1:
       displayProducts( products, num_products); 
      break;
        case 2:
       search_product_customer(products, num_products);
      break;
        case 3:
       fillShoppingCart(customer,last_name,first_name); 
      break; 
      case 4:
                printf("Would you like to unsubscribe (y/n) 😞? ");
                scanf(" %c", &answer);
                if (answer == 'y' || answer == 'Y') {
                removeCustomerFromFile(customer, last_name, first_name);
                removePurchaseHistoryFile(last_name, first_name);
                printf("You have been successfully unsubscribed.\n");
                exit(EXIT_SUCCESS);
            } 
            else if (answer == 'n' || answer == 'N') {
              printf("Thanks to stay with us 👍\n");
            continue;}
           else {
             printf ("Invalide Choice");
             
           }
        case 5:
      printf("\nGoodbye! See you soon! 👋 \n");
      break;
    default:
      printf("\nInvalid choice. Please try again.\n");

    } 
 } while (choice != 5);

  return 0;
}
