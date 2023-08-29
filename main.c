
/************************************************
*	Project Name: Clinic Managment System.      *
*	Coded by: Mahmoud Sayed.                    *
************************************************/

#include "linkedlist.h"

void main()
{
	u16 mode, cntr = 0, flag = 0, first = 0,  slots[5]={1,1,1,1,1};
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
					u16 identification = wanted_ID;
					u16 foundID = findNode(head, wanted_ID);
					if(foundID == 1){
						u16 idx;
						u16 wanted_slot;
						printf("select a slot to reserve:\n");
						for(idx = 0; idx<5; idx++){
							if(slots[idx] != 1){
								continue;
							}	
							printf("slot %d\n", idx);
							
						}
						scanf("%d", &wanted_slot);
						slots[wanted_slot] = identification;
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
						u16 idx;
						u16 wanted_slot;
						printf("select a slot to cancel(must be reserved):\n");
						for(idx = 0; idx<5; idx++){
							if(slots[idx] == 1){
								continue;
							}
							printf("slot %d\n", idx);
						}
						scanf("%d", &wanted_slot);
						slots[wanted_slot] = 1;
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
			scanf(" %d", &useroption);
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
				printf("All today's reservations:\n ");
				for(i = 0; i<5; i++){
					if(slots[i] > 1){
						printf("slot %d - patient ID: %d\n", i, slots[i]);
					}
				}
			}
			else
			{
				printf("Invalid user option.\n");
			}
			break;
			default:
			printf("wrong mode!\n");
			
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
	u16 k;
	for(k = 0; k<5; k++){
		slots[k] = 1;
	}
}


