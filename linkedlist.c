
/************************************************
*	Project Name: Clinic Managment System.      *
*	Coded by: Mahmoud Sayed.                    *
************************************************/

#include "linkedlist.h"


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