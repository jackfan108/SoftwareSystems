#include <stdio.h>
#include <stdlib.h>

int decideValue(char card_name[]);
int updateCount(int val, int count);

int main() {
    char card_name[3];
    int count = 0;
    int val;
    while (card_name[0] != 'x') {
	puts("Enter the card_name: ");
	scanf("%2s", card_name);
	val = decideValue(card_name);
	count = updateCount(val, count);
	printf("Current count: %i\n", count);
    }
    return 0;
}
/*
 this function decides the value of each card_name
 KQJ are 10, A is 11 and anything less than 1 or more than 10 results in 0
*/

int decideValue(char name[]) {
    int val;
    switch(name[0]) {
	case 'K':
	case 'Q':
	case 'J':
	    val = 10;
	    break;
	case 'A':
	    val = 11;
	    break;
	case 'X':
	default:
	    val = atoi(name);
	    if ((val < 1) || (val > 10)) {
		puts("I don't understand that value !");
	    }
    }
    return val;
}

/* 
 this function updates count based on the value calculated from decideValue
 if value is in between 3 and 6, count is increased by 1
 if value is 10, count is decreased by 1
*/

int updateCount(int val, int count) {
    if ((val > 2) && (val < 7)) {
            count++;
        } else if (val == 10) {
            count--;
        }
    return count;  
}