
/************************************************
*	Project Name: Clinic Managment System.      *
*	Coded by: Mahmoud Sayed.                    *
************************************************/


#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

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

#endif