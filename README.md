# Projectshop

The chosen project is the CYshop, designed by MURALEESWARAN Ahgaash, ABDESSLAM Mehdi and ROBERT Charly.


At the start of the program, the user is asked to choose between "management mode" and "purchase mode".

If the user selects "management mode" (intended for the seller), he will be shown the list of products with a quantity stored in the warehouse of 0, and the list of the 5 products with the least quantity stored in the warehouse.
After that, a menu is displayed, giving the user a choice of options:
-The first allows you to see all the products in the store;
-The second allows you to search for a product by name or reference number;
-The third allows you to add a new product to the store;
-The fourth allows you to remove a product from the store;
-The fifth allows you to modify the quantity of product in stock, a positive number will add it and a negative number will remove it;
-The sixth allows you to move a product into a category (in this case, a vehicle). To place them in the different categories, the reference number must meet a condition depending on the type of vehicle. The first character must be: 
  ¤ "C" for "compact" vehicles,
  ¤ "MSUV" for "mini-SUV" vehicles,
  ¤ "BR" for "estate" cars,
  ¤ "SE" for "sedan" vehicles,
  ¤ "SUV" for "SUV" vehicles,
  ¤ "SP" for "sports" vehicles,
-The seventh is simply to exit the program.

And if the user chooses the "purchase mode" (intended for the customer), he'll be asked to enter his first and last name to determine whether the customer already exists in the file or not. If the customer exists, his last three purchases will be displayed.
A menu is then displayed, and the user can choose between different services:
-The first is the calalog of products
-The second allows you to search for a product by name;
-If the user chooses not to validate, the purchase will be deleted, and if they validate, the purchase will be recorded in their personal history. If the product they are looking for is no longer in stock, the user will be asked to choose whether or not they wish to unsubscribe from the store;
-The fourth allows the user to unsubscribe from the store;
-The fifth is simply to exit the program.

Unresolved bug: when the user does anything on one of the functions available on the 2 modes, and then repeats this action on the menu, the menu buffer will not work and will display the previously selected function.
