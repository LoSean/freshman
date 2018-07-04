target:hw6_2 hw6_3
CFLAG = -Wall -O2 -o 

hw6_2:hw6_2.c avl.c bst.c rb.c
	gcc hw6_2.c avl.c bst.c rb.c $(CFLAG) hw6_2

hw6_3:hw6_3.c avl_ntudsa.c 
	gcc hw6_3.c avl_ntudsa.c $(CFLAG) hw6_3

clean:
	rm -rf hw6_2 hw6_3
