#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "record_Data.h"
int count_Num_Record;
int count_Num_Changes;

int size_Of_Database(){
	return (sizeof(address) * count_Num_Record);
}

void* add_Record(void* ptr,address a){
	
	void* new;
	new = malloc(sizeof(address) * (count_Num_Record+1));//allocate new memory
	int size_Of_Address = (sizeof(address) * (count_Num_Record+1));
	memcpy(new,ptr,size_Of_Database());
	void* new_Ptr = ptr + (sizeof(address) * count_Num_Record);
	memcpy(new_Ptr,&a,sizeof(a));
	free(ptr);
	
	count_Num_Record += 1;
	count_Num_Changes +=1;
	return new;
	


}

void* delete_Record(void* beg){
	void* new;
	new = malloc(sizeof(address) * (count_Num_Record-1));
	int size_Of_Address = (sizeof(address) * (count_Num_Record-1));
	memcpy(new,beg,size_Of_Database());
	count_Num_Record -= 1;
	count_Num_Changes +=1;
	free(beg);
	return new;

}



void* print_Record(void* beg){
	for(int i =0; i < size_Of_Database();i++){
		address *one = (beg + (sizeof(address) * i));
		printf("Address: %s\n", one->address);
		printf("City: %s\n", one->city);
		printf("State: %s\n", one->state);
		printf("Zipcode: %d\n", one->zip_Code);
	}
	
}

int main(int argc, char** argv) {
    
    void* ptr;
    ptr = add_Record(ptr,one);
    ptr = add_Record(ptr,two);
    ptr = add_Record(ptr,three);
    ptr = add_Record(ptr,four);
    ptr = add_Record(ptr,five);

    while(1) {
	int x;
	char buf_Address[50];
	char buf_City[50];
	char buf_State[50];
	char buf_Zipcode[10];

	char sel = 0;
        int day = 0;
        printf("MENU\n");
        printf("=====\n");
        printf("1. Print all records\n"); //print fxn
        printf("2. Print number of records\n"); //global var
        printf("3. Print size of database\n"); //size fxn
	printf("4. Add record\n"); //add fxn
	printf("5. Delete record\n"); //delete fxn
	printf("6. Print number of accesses to database\n"); //global var
	printf("7. Exit\n");
        printf("Enter selection: ");
	sel = getchar();
	while(getchar() != '\n');
        switch (sel) {
            case 49:
                //print_Record();
                break;
            case 50:
                printf("Number of records: %d\n", count_Num_Record);
                break;
            case 51:
                printf("Size of database: %d\n", size_Of_Database());
		break;
            case 52:

		printf("Please enter an address: ");
		fgets(buf_Address, 50, stdin);
		printf("Please enter a city: ");
		fgets(buf_City, 50, stdin);
		printf("Please enter a state: ");
		fgets(buf_State, 50, stdin);
		printf("Please enter a zipcode: ");
		fgets(buf_Zipcode, 10, stdin);	
		
		x = atoi(buf_Zipcode);

		address one = {.address = *buf_Address, .city = *buf_City, .state = *buf_State, .zip_Code = x};
		ptr = add_Record(ptr, one);
                break;
            case 53:
		ptr = delete_Record(ptr);
		break;
	    case 54:
		printf("Number of accesses to database: %d\n", count_Num_Changes);
		break;
            case 55:
	    	printf("Exit\n");
                return (EXIT_SUCCESS);
            default:
                printf("Invalid entry, try again\n");
        }
    } 
    return (EXIT_SUCCESS);    
}

