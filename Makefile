
ATM_INC : main.o purchase_mode.o management_mode.o

	gcc -o ATM_INC main.o purchase_mode.o management_mode.o

main.o : main.c

	gcc -c main.c -o main.o

purchase_mode.o : purchase_mode.c

	gcc -c purchase_mode.c -o purchase_mode.o

management_mode.o : management_mode.c 

	gcc -c management_mode.c -o management_mode.o
 
