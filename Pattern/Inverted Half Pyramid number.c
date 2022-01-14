// Program: In this section we will make a inverted half pyramid program of numbers.
// In this program we will print the maximum number of integers (in increasing order) in first row 
// and we will decrease the number of printing integers by one.

#include<stdio.h>

void main(){
	
	// to make a half pyramid program we need two loop 
	// one loop will track the row and other one will track the columns.
	int i,j;
	for(i=0; i<=10; i++){
		
		for(j=1; j<=10-i; j++){
			
			printf("%d ", j);			
		}
		printf("\n");
		
	}
}
