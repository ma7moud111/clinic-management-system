/*******************************************
*	Project Name: Clinic Managment System. *
*	Coded by: Mahmoud Sayed.               *
********************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "STD_TYPES.h"

typedef struct patient{
	u8 name[20];
	u16 age;
	u8 gender;
	u16 ID;
	struct patient* next;
}patient_t;

void addNodeToEnd(patient_t* Head, patient_t value);
void printNode(patient_t* head, u16 given_ID);
u16 findNode(patient_t* head, u16 given_ID);
void editNode(patient_t* head, u16 given_ID, patient_t newValue);

void main()
{
	u16 mode, cntr = 0, flag = 0, first = 0,  slots[5]={-1,-1,-1,-1,-1};
	u8 req_pass[4] = "1234";
	u8 pass[4];
	patient_t* head = (patient_t*)malloc(sizeof (patient_t));
	head->next = NULL;
	printf("Welcome to Clinic Management System\n");
	while(1)
	{
		// selecting mode 
		printf("Please select mode:\n1-Admin mode\n2-User mode\n");
		scanf("%d", &mode);
		
		switch (mode)
		{
			case 1:							// admin mode
			while(cntr < 3){
				printf("Enter Password: "); // entering password to login to admin mode
				scanf("%s", &pass);
				if(pass[0] == req_pass[0] && pass[1] == req_pass[1] && pass[2] == req_pass[2] && pass[3] == req_pass[3])
				{
					flag = 1;
					break;
				}
				else{
					printf("Wrong pass\n");
					cntr++;
				}
			}
			if(flag == 0){
				printf("system logged out\n");
			}
			else if(flag == 1){
				u16 option;
				printf("select option:\n");
				printf("1- Add new patient record\n2- Edit patient record\n3- Reserve a slot with the doctor\n4- Cancel reservation\n");
				scanf("%d", &option);
				if(option == 1) 				//1- add a patient in admin mode
				{
					patient_t pat;
					printf("Enter patient name: ");
					scanf("%s", &pat.name);
					printf("Enter patient age: ");
					scanf("%d", &pat.age);
					printf("Enter patient gender: ");
					scanf(" %c", &pat.gender);
					printf("Enter patient ID: ");
					scanf(" %d", &pat.ID);
					if(first == 0){
						strcpy(head->name,pat.name);
						head->age = pat.age;
						head->gender = pat.gender;
						head->ID = pat.ID;
						first = 1;
						printf("first patient added successfuly.\n");
						
					}
					else{
						u16 foundDuplicateID = findNode(head, pat.ID);
						if(foundDuplicateID == 1){
							printf("Couldn't add patient, duplicate ID found!\n");
						}
						else{
							addNodeToEnd(head, pat);
							printf("patient added successfuly.\n");
						}	
					}	
				}
				else if(option == 2) 		// edit patient record in admin mode
				{
					u16 pat_ID;
					printf("Enter patient ID you want to update his/her data: ");
					scanf("%d", &pat_ID);
					u16 foundID = findNode(head, pat_ID);
					if(foundID == 1){
						patient_t newData;
						printf("Enter patient new name: ");
						scanf("%s", &newData.name);
						printf("Enter patient new age: ");
						scanf("%d", &newData.age);
						printf("Enter patient new gender: ");
						scanf(" %c", &newData.gender);
						printf("Enter patient new ID: ");
						scanf(" %d", &newData.ID);
						editNode(head,pat_ID,newData);
						printf("Data for given ID updated successfully.\n");
						
					}
					else{
						printf("Incorrect ID.\n");
					}
				}
				else if(option == 3)		// reserve a slot in the admin mode
				{
					u16 wanted_ID;
					printf("Enter the patient ID(must be exist): ");
					scanf("%d", &wanted_ID);
					u16 foundID = findNode(head, wanted_ID);
					if(foundID == 1){
						u16 i;
						u16 wanted_slot;
						printf("select a slot to reserve:\n");
						for(i = 0; i<5; i++){
							if(slots[i] > -1){
								continue;
							}
							else{
								printf("slot %d\n", i);
							}
						}
						scanf("%d", &wanted_slot);
						slots[wanted_slot] = wanted_ID;
						printf("slot reserved successfully.\n");
					}
					else{
						printf("ID not found\n");
					}
				}
				else if(option == 4)			// cancel reservation in admin mode
				{
					u16 wanted_ID;
					printf("Enter the patient ID(must be exist): ");
					scanf("%d", &wanted_ID);
					u16 foundID = findNode(head, wanted_ID);
					if(foundID == 1){
						u16 i;
						u16 wanted_slot;
						printf("select a slot to cancel(must be reserved):\n");
						for(i = 0; i<5; i++){
							if(slots[i] <= -1){
								continue;
							}
							else{
								printf("slot %d\n", i);
							}
						}
						scanf("%d", &wanted_slot);
						slots[wanted_slot] = 0;
						printf("slot canceled successfully.\n");
					}
					else{
						printf("ID not found\n");
					}
				}
				else
				{
					printf("Invalid admin Option.\n");
				}
			}		
			break;
			
			case 2:;							// user mode
			u16 useroption;
			printf("select option:\n");
			printf("1- view patient record.\n2- view today's reservations.\n");
			scanf("%d", &useroption);
			if(useroption == 1)
			{
				u16 wanted_ID;
				printf("Enter the patient ID(must be exist): ");
				scanf("%d", &wanted_ID);
				u16 foundID = findNode(head, wanted_ID);
				if(foundID == 1){
					printf("Patient found:\n");
					printNode(head, wanted_ID);
				}
				else{
					printf("patient not found!\n");
				}
			}
			else if(useroption == 2)
			{
				u16 i;
				printf("All today's reservations: ");
				for(i = 0; i<5; i++){
					if(slots[i] > -1){
						printf("slot %d - patient ID: %d\n", i, slots[i]);
					}
				}
			}
			else
			{
				printf("Invalid user option.\n")
			}
			break;
			default:
			printf("wrong mode!");
			
		}
		u8 cont;
		printf("continue? y/n: ");
		scanf(" %c", &cont);
		if(cont == 'n'){
			break;
		}
		else{
			continue;
		}
	}
}


void addNodeToEnd(patient_t* Head, patient_t value){
	
	/*creating a temp node to traverse through the linked list and starting from head node*/
	patient_t* temp = Head;
	
	/*creating a new node*/
	patient_t* newNode = (patient_t*)malloc(sizeof(patient_t));
	
	/* assign the new node data*/
	strcpy(newNode->name,value.name);
	newNode->age = value.age;
	newNode->gender = value.gender;
	newNode->ID = value.ID;
	
	/* traverse through the linked list to reach the final node*/
	while(temp->next != NULL){
		temp = temp->next;
	}
	
	/*make the current node points to the final new node created*/
	temp->next = newNode;
	
	/*make the new node points to NULL*/
	newNode->next = NULL;
}

void printNode(patient_t* head, u16 given_ID){
	patient_t* temp = head;
	u16 f = 0;
	while(temp != NULL){
		if(temp->ID == given_ID){
			f = 1;
			break;
		}
		temp = temp->next;
	}
	if(f){
		printf("patient name: %s\n", temp->name);
		printf("patient age: %d\n", temp->age);
		printf("patient gender: %c\n", temp->gender);
		printf("patient ID: %d\n", temp->ID);
	}
}

u16 findNode(patient_t* head, u16 given_ID){
	patient_t* temp = head;
	while(temp != NULL){
		if(temp->ID == given_ID){
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}

void editNode(patient_t* head, u16 given_ID, patient_t newValue){
	
	patient_t* temp = head;
	u16 f = 0;
	while(temp != NULL){
		if(temp->ID == given_ID){
			f = 1;
			break;
		}
		temp = temp->next;
	}
	if(f){
		strcpy(temp->name, newValue.name);
		temp->age = newValue.age;
		temp->gender = newValue.gender;
		temp->ID = newValue.ID;
	}
	
}