/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/* 
 * File:   main.c
 * Author: taiye
 *
 * Created on September 13, 2018, 5:20 PM
 */
#include <stdio.h>
#include <stdlib.h>
#include "myData.h"
/*
 * 
 */
int sumTotal(void) {
    int counter = 0;
    int i,j,k;
    for(i=0;i<4;i++){
      for(j=0;j<4;j++){
        for(k=0;k<3;k++){
          counter += scores[i][j][k];
        }
      }  
    }
    printf("%d\n", counter);
    return 0;
}
int sumWeek(void) {
    int counter = 0;
    int i,k;
    for(i=0;i<4;i++){
        for(k=0;k<3;k++){
            counter += scores[i][3][k];
        }
    }
    printf("%d\n", counter);
    return 0;
}
int sumDay(int n) {
    int counter = 0;
    int i,j;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            counter += scores[i][j][n];
        }
    }
    printf("%d\n", counter);
    return 0;
}
int main(int argc, char** argv) {
    while(1) {
	char sel = 0;
        int day = 0;
        printf("MENU\n");
        printf("=====\n");
        printf("1. The sum of points scored in a 4 month season\n");
        printf("2. The sum of points scored in the last week of every month in the season\n");
        printf("3. The sum of points scored on a given day throughout the season\n");
	printf("4. Exit\n");
        printf("Enter selection: ");        
	sel = getchar();
	while(getchar() != '\n');
        switch (sel) {
            case 49:
                sumTotal();
                break;
            case 50:
                sumWeek();
                break;
            case 51:
		day = 0;
		char c[1];
		while(1){
                printf("Enter a day (Monday =0, Wedensday =1, Friday =2): ");
		c[0] = getchar();
		day = atoi(&c[0]);
		if(day > 2){
			printf("Must be between 0 and 2, try again:\n");
			continue;
		}
		else{
			break;
		}
		}
                while( getchar() != '\n');
		sumDay(day);
                break;
            case 52:
                printf("Exit\n");
                return (EXIT_SUCCESS);
            default:
                printf("Invalid entry, try again\n");
        }
    } 
    return (EXIT_SUCCESS);
}
