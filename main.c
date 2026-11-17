#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node{  //Declaring the structs wanted by the instructions.
	void* data;
	struct Node* next;
}Node;

typedef struct{
	char type[20];
	int ivals[1];
	double svals[1];
}Asset1;

typedef struct {
	char type[20];
	double svals[2];
	int ivals[2];
}Asset2;

typedef struct{
	char type[20];
	char string1[50];
	char string2[50];
}Asset3;

typedef struct {
	char type[20];
	double value1;
	float value2;
	double value3;
}Asset4;

void fillLinkedList(struct Node** head){
int i, a;
i = rand() % 11 + 10;  //Using rand to declare a number for the number of assets between 10 and 20.
printf("Generating Linked List(%d Assets):\n", i);
struct Node* current = NULL;  //Declaring a node called current which is NULL to use in the linked list.
for(int j=0;j<i;j++){
struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
newNode->next = NULL;
printf("Type: ");
a = rand() % 4;  //Using rand once again to choose a number between 0 an 3 to choose an asset type.
	switch(a){
		case 0:{  //The case for asset1 and declaring the values in the asset1 struct.
		 Asset1* asset1 = (Asset1*)malloc(sizeof(Asset1));
                strcpy(asset1->type, "Asset1");
                asset1->ivals[0] = rand() % 100;
                asset1->svals[0] = (double)rand() / 100000;
                printf("%s, ivals[0]: %d, svals[0]: %.2lf\n", asset1->type, asset1->ivals[0], asset1->svals[0]);
                newNode->data = asset1;  //Making the newNode's data asset1.             
                break;
                }
                case 1:{  //The case for asset2 and declaring the values in the asset2 struct.
		 Asset2* asset2 = (Asset2*)malloc(sizeof(Asset2));
                strcpy(asset2->type, "Asset2");
                asset2->svals[0] = (double)rand() / 100000;
                asset2->svals[1] = (double)rand() / 100000;
                asset2->ivals[0] = rand() % 100;
                asset2->ivals[1] = rand() % 100;
                printf("%s, ivals[0]: %d, ivals[1]: %d, svals[0]: %.2lf, svals[1]: %.2lf\n", asset2->type, asset2->ivals[0], asset2->ivals[1], asset2->svals[0], asset2->svals[1]);
                newNode->data = asset2;  //Making the newNode's data asset1. 
                break;
                }
                case 2:{   //The case for asset3 and declaring the values in the asset3 struct.
                Asset3* asset3 = (Asset3*)malloc(sizeof(Asset3));
                strcpy(asset3->type, "Asset3");
                strcpy(asset3->string1, "Bengisu");
                strcpy(asset3->string2, "Duru");
                printf("%s, string1: %s, string2: %s\n", asset3->type, asset3->string1, asset3->string2);
                newNode->data = asset3;  //Making the newNode's data asset1.
                break;
                }
                case 3:{   //The case for asset4 and declaring the values in the asset4 struct.
                Asset4* asset4 = (Asset4*)malloc(sizeof(Asset4));
                strcpy(asset4->type, "Asset4");
                asset4->value1 = (double)rand() / 100000;
                asset4->value2 = (float)rand() / 100000;
                asset4->value3 = (double)rand() / 100000;
                printf("%s, value1: %.2lf, value2: %.2f, value3: %.2lf\n", asset4->type, asset4->value1, asset4->value2, asset4->value3);
                newNode->data = asset4;   //Making the newNode's data asset1.
                break;
                }
                }
                
                if (*head == NULL) {  //This condition is executed in the beginning. If the head pointer is Null we equalize the head pointer to the newNode which we used in the above switch-case conditions and we equalize the current node to the newNode too to use in the rest of the linked list filling.
                *head = newNode;
                current = newNode;
                } else {
                current->next = newNode;  //This condition is executed in the rest. We equalize the current node's next to the newNode and equalize the current to the newNode once again.
                current = newNode;
                }
       }
                
}

void serializeLinkedList(struct Node* head) {
    FILE* file = fopen("linkedlist.bin", "wb");
    if (file == NULL) {
        printf("File opening failed.\n");
        return;
    }

    struct Node* current = head;
    while (current != NULL) {
        void* data = current->data;

        if (strcmp(((Asset1*)data)->type, "Asset1") == 0) {   //In this function we use if conditions and strcmp to understand the read asset's asset type and read the assets in to a binary file.
            Asset1* asset1 = (Asset1*)data;
            fwrite(asset1->type, sizeof(char), sizeof(asset1->type), file);
            fwrite(asset1, sizeof(Asset1), 1, file);
        } else if (strcmp(((Asset2*)data)->type, "Asset2") == 0) {
            Asset2* asset2 = (Asset2*)data;
            fwrite(asset2->type, sizeof(char), sizeof(asset2->type), file);
            fwrite(asset2, sizeof(Asset2), 1, file);
        } else if (strcmp(((Asset3*)data)->type, "Asset3") == 0) {
            Asset3* asset3 = (Asset3*)data;
            fwrite(asset3->type, sizeof(char), sizeof(asset3->type), file);
            fwrite(asset3, sizeof(Asset3), 1, file);
        } else if (strcmp(((Asset4*)data)->type, "Asset4") == 0) {
            Asset4* asset4 = (Asset4*)data;
            fwrite(asset4->type, sizeof(char), sizeof(asset4->type), file);
            fwrite(asset4, sizeof(Asset4), 1, file);
        }

        current = current->next;  //We equalize the current node to the current node's next node to continue reading the linked list.
    }
    printf("\nSerializing the Linked List...\n\n");	
    fclose(file);
}


void deserializeLinkedList(struct Node** head) {
    FILE* file = fopen("linkedlist.bin", "rb");   //In this function we open the linkedlist.bin file to read the assets from the binary file and reconstruct the linked list.
    if (file == NULL) {
        printf("File opening failed.\n");
        return;
    }

    *head = NULL;  //We declare the head pointer as NULL.
    struct Node* current = NULL;
    printf("Reconstructing Linked List:\n");
    while (1) {
        char type[20];
        memset(type, 0, sizeof(type));  //memset() is used to set all the bytes in a block of memory to a particular char value. I used it for the type value.
        
        if (fread(type, sizeof(char), 20, file) != 20) {
            break;
        }

        if (strcmp(type, "Asset1") == 0) {  //We use strcmp once again to understand the read asset's asset type.
            Asset1* asset1 = (Asset1*)malloc(sizeof(Asset1));  //If it is asset1 we use malloc to open a memory with the size of Asset1.
            fread(asset1, sizeof(Asset1), 1, file);  //We read asset1.
            struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));  //We use malloc to create a node named newNode.
            printf("Type: %s, ivals[0]: %d, svals[0]: %.2lf\n", asset1->type, asset1->ivals[0], asset1->svals[0]);
            newNode->data = asset1;  //We equalize the newNode's data to Asset1 and continue.
            newNode->next = NULL;

            if (*head == NULL) {  //We apply the same process in the fillLinkedList function here.
                *head = newNode;
                current = newNode;
            } else {
                current->next = newNode;
                current = newNode;
            }
        } else if (strcmp(type, "Asset2") == 0) {
            Asset2* asset2 = (Asset2*)malloc(sizeof(Asset2));
            fread(asset2, sizeof(Asset2), 1, file);
            printf("Type: %s, ivals[0]: %d, ivals[1]: %d, svals[0]: %.2lf, svals[1]: %.2lf\n", asset2->type, asset2->ivals[0], asset2->ivals[1], asset2->svals[0], asset2->svals[1]);
            struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

            newNode->data = asset2;
            newNode->next = NULL;

            if (*head == NULL) {
                *head = newNode;
                current = newNode;
            } else {
                current->next = newNode;
                current = newNode;
            }
        } else if (strcmp(type, "Asset3") == 0) {
            Asset3* asset3 = (Asset3*)malloc(sizeof(Asset3));
            fread(asset3, sizeof(Asset3), 1, file);
            struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
            printf("Type: %s, string1: %s, string2: %s\n", asset3->type, asset3->string1, asset3->string2);
            newNode->data = asset3;
            newNode->next = NULL;

            if (*head == NULL) {
                *head = newNode;
                current = newNode;
            } else {
                current->next = newNode;
                current = newNode;
            }
        } else if (strcmp(type, "Asset4") == 0) {
            Asset4* asset4 = (Asset4*)malloc(sizeof(Asset4));
            fread(asset4, sizeof(Asset4), 1, file);
            struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
            printf("Type: %s, value1: %.2lf, value2: %.2f, value3: %.2lf\n", asset4->type, asset4->value1, asset4->value2, asset4->value3);
            newNode->data = asset4;
            newNode->next = NULL;

            if (*head == NULL) {
                *head = newNode;
                current = newNode;
            } else {
                current->next = newNode;
                current = newNode;
            }
        }
    }

    fclose(file);
}



int main(){
srand(time(NULL));  //We use srand to not get the same choosen values in rand again and again.
struct Node* head = NULL;   //Declaring the head pointer as NULL.
fillLinkedList(&head);
serializeLinkedList(head);   //Declaring the functions with the head pointer.
deserializeLinkedList(&head);

return 0;
}






