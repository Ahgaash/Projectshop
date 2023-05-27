#include <stdio.h>
#include "purchase_mode.h"


int main(){
   int choix;   // Variable pour stocker le choix de l'utilisateur
   int num_products;
   Product products[MAX_PRODUCTS]; // Tableau pour stocker les produits
  printf("Welcome to ATM.INC 🚗💨\n"); 
  printf("~ Unleash the Power of Elegance ✨ and Performance ⚡ ~\n");
  do{
  printf("Choose 1 for 'purchase mode 🛒' or 2 for 'management mode ⚙️ ': ");
    scanf("%d",&choix);
    empty_buffer();
  } while (choix!=1 && choix!=2);
  if (choix==1){
    purchase_mode();     // Appeler la fonction du mode d'achat
    
  }
  if (choix==2){
    management_mode();   // Appeler la fonction du mode gestion
    }
    
  }
     
