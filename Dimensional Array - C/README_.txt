Taiye Bello|bello067@umn.edu|5257909

*Program Description: A three dimensional array is used to store data that is used to calculate totals based on user input. 

*Data structure definition for 3 deminesional array: 
	-The dimensions in the array represent 4 months in a season, 4 weeks in a season, and 3 games a week (Monday, Wednesday, and Friday).
*Functions Definitions(input type,output type,algorithm descriptions):
	Function 1: 
		-No input type
		-Returns an int and prints the sum of total points scored in a season
		-The purpose of this function is to add and print all the scores scored by one person in a season. Three for loops are used to iterate through the 			array 'scores' and the int variable counter is changed after each loop to get the final sum.
	Function 2: 
		-No input type
		-Returns an int and prints the sum of total points scored in the last week of every month in the season
		-The purpose of this function is to add and print all the scores scored by one person in the last week of every month of the season. Two loops are used 		to iterate throughout the array 'scores' and the int varibale counter is changed after each loop to get the final sum. Counter is incremented 			by indexing 'scores' i is the length of the array, j is hard coded to index at the last week of each month and k is the length of the games played in a 		week which is three.
	Funciton 3: 
		-Int intput type
		-Returns an int and prints the sum of total points scored on a given day throughout the season
		-The purpose of this function is to add all the scores scored by one person on a given day throughout the season. Two loops are used to iterate 		throughout the array 'scores' and the int varibale counter is incremented after each loop to finally reach the final sum. The index used to 			change counter is i the length of the array/months in the season, j the weeeks in season, and k which is given by the user, the days played per week in 		the season. 
*Files required and file types:
	-Lab1.c: C code
	-myData.h: Header file
	-design.txt: Text file
	-lab1.txt: Test Script


