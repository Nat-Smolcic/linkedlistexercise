#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

/*
 * FILE: linked list address book.cpp
 * PROJECT: Linked List Exercise
 * PROGRAMMER: Nat Smolcic
 * DATE: Jan 16 2023
 * DESCRIPTION: Example of a simple, unsorted linked list used to create an address book. 
 *				This program can add info into the linked list, delete individual nodes, search nodes, and print a found node. 
 */


// STRUCT DECLARATIONS 
typedef struct addressInfo {
	char name[51];
	char address[51];
	char phone[11];
};

typedef struct addressNode {
	struct addressInfo info;
	struct addressNode* next;
};



// PROTOTYPES 
void delete_info(addressNode* head);

addressNode* find_node(addressNode* head, char findName[51]);

void fill_node(addressInfo* node);

void delete_node(addressNode* head);



int main() {
	// always initialize head node to NULL
	struct addressNode* head = NULL;

	// allocate memory for a new node
	addressNode* block = (addressNode*)malloc(sizeof(addressNode));

	// always check malloc() return value
	if (block == NULL) {
		printf("ERROR : Unable to allocate memory for new node\n");
	}

	// start the list by assigning the address of the newly allocated block to the head variable
	if (head == NULL) {
		head = block;
		block->next = NULL;
	}

	// fill in the node with user inputted values
	fill_node(head->info);

	while (1) {
		// prompt user for input 
		printf("Press 'X' to delete a list entry, 'Z' to stop filling in address book information, \n");
		printf("'F' to find and print an entry, or 'N' to input a new entry to the address book.\n");
		char userInput[51];

		// if user wishes to break loop
		if (strcmp(userInput, "Z") == 0) {
			break;
		}

		// if user wishes to delete an entry
		else if (strcmp(userInput, "X") == 0) {
			delete_node(head);
		}

		// if user wishes to add an entry
		else if (strcmp(userInput, "N") == 0) {

			// always initialize new node to NULL
			struct addressNode* node = NULL;

			// allocate memory for a new node
			addressNode* block = (addressNode*)malloc(sizeof(addressNode));

			// always check malloc() return value
			if (block == NULL) {
				printf("ERROR : Unable to allocate memory for new node\n");
			}

			// assign the address of the newly allocated block to the new node variable
			if (node == NULL) {
				node == block;
				block->next = NULL;
			}

			fill_node(node->info);
		}

		// if user wishes to find and print an entry
		else if (strcmp(userInput, "F") == 0) {
			// get user input to declare the string we are trying to find
			char findName[51];
			printf("Please input the name of the person's address you'd like to find. Hit enter when done.\n");
			printf("Make sure there is no extra whitespace at the end of the name.");
			fgets(findName, 51, stdin);

			// find the given node and assign it to a variable
			addressNode* foundNode = find_node(head, findName);

			// print the given node to the screen
			printf("Name: %s\nAddress: %s\nNumber: %s\n", foundNode->info.name, foundNode->info.address, foundNode->info.phone);
		}

		// if the user inputs some invalid letter code 
		else {
			printf("ERROR : Invalid Input");
		}
	}

	// freeing the memory
	delete_info(head);

	return 0;
}



// FUNCTION: delete_info()
// PARAMETERS: addressNode* head: pointer to the head of a linked list
// RETURN VALUES: none
// DESCRIPTION: Deletes an entire linked list 
void delete_info(addressNode* head) {
	addressNode* curr = NULL;
	addressNode* pNode = NULL;

	pNode = head;

	while (pNode != NULL) {
		// save current cell
		curr = pNode;
		// move to next cell
		pNode = pNode->next;
		// free current cell
		free(curr);
	}
}


// FUNCTION: find_node()
// PARAMETERS: addressNode* head: pointer to the head of a linked list
//			   char findName[51]: C-style string of the name of the desired node to be found
// RETRUN VALUES: addressNode* pNode: a pointer to the found node. NULL if it was not found.
// DESCRIPTION: Traverses a linked list to find a node given a name field
addressNode* find_node(addressNode* head, char findName[51]) {
	addressNode* pNode = head;

	while (strcmp(pNode->info.name, findName) != 0) {
		pNode = pNode->next;
	}

	return pNode;
}


// FUNCITON: fill_node()
// PARAMETERS: addressInfo* node: the node that the user wants to fill in with information
// RETURN VALUES: none
// DESCRIPTION: adds personal information into a node in a linked list
void fill_node(addressInfo* node) {
	char name[51];
	printf("Please enter the name: ");
	fgets(name, 51, stdin);

	char address[51];
	printf("\nPlease enter the address: ");
	fgets(address, 51, stdin);

	char phone[11];
	printf("\nPlease enter the phone number with no dashes or spaces: ");
	fgets(phone, 11, stdin);

	node->name = name;
	node->address = address;
	node->phone = phone;
}


// FUNCTION: delete_node()
// PARAMETERS: addressNode* head: the pointer to the head of the linked list
// RETURN VALUES: none
// DESCRIPTION: prompts the user for the name of a node to delete from the given linked list
void delete_node(addressNode* head) {
	// prompt user for name to delete
	char name[51];
	printf("Please input the name of the person's entry you'd like to delete: ");
	fgets(name, 51, stdin);

	// find the node to delete
	addressNode* pNode = head;
	addressNode* prevNode = NULL;

	while (strcmp(pNode->info.name, name) != 0) {
		prevNode = pNode;
		pNode = pNode->next;
	}

	// link the previous node to the node after the current node
	addressNode* nextNode = pNode->next;
	prevNode->next = nextNode->next;

	// delete the current node
	free(pNode);
}

