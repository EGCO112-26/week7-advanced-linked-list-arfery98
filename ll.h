#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// self-referential structure
struct Node {
    int id;                // เก็บ ID
    char name[50];         // เก็บชื่อ
    struct Node *nextPtr;  // ชี้ไปโหนดถัดไป
    struct Node *pPtr;     // ชี้ไปโหนดก่อนหน้า
};

typedef struct Node LLnode; // synonym for struct listNode
typedef LLnode *LLPtr;      // synonym for ListNode*

// prototypes

int deletes(LLPtr *sPtr, int value);
int isEmpty(LLPtr sPtr);
void insert( LLPtr *sPtr, int id, char name[] );
void printList(LLPtr currentPtr);
void printListR(LLPtr currentPtr);
void instructions(void);

// display program instructions to user
void instructions(void){
   puts("Enter your choice:\n"
      "   1 to insert an element into the list.\n"
      "   2 to delete an element from the list.\n"
      "   3 to end.");
} // end function instructions

// ฟังก์ชันแทรกข้อมูลแบบเรียงลำดับ ID
void insert(LLPtr *sPtr, int id, char name[]) {
   LLPtr newPtr = malloc(sizeof(LLnode));

   if (newPtr != NULL) {
      newPtr->id = id;
      strcpy(newPtr->name, name);
      newPtr->nextPtr = NULL;
      newPtr->pPtr = NULL;

      LLPtr previousPtr = NULL;
      LLPtr currentPtr = *sPtr;

        // หาตำแหน่งที่จะแทรก (เรียงตาม ID)
      while (currentPtr != NULL && id > currentPtr->id) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
      }

      if (previousPtr == NULL) { // แทรกที่หัว list
         newPtr->nextPtr = *sPtr;
         
         if (*sPtr != NULL) {
            (*sPtr)->pPtr = newPtr;
         }
            *sPtr = newPtr;
      } else { // แทรกกลางหรือท้าย
            newPtr->nextPtr = currentPtr;
            newPtr->pPtr = previousPtr;
            previousPtr->nextPtr = newPtr;
            if (currentPtr != NULL) {
               currentPtr->nextPtr->pPtr = newPtr; // แก้ไขจุดนี้ให้ถูกต้อง
            }
      }
   }
}

// return 1 if the list is empty, 0 otherwise
int isEmpty(LLPtr sPtr){
   return sPtr == NULL;
} // end function isEmpty

void printList(LLPtr currentPtr) {
   if (currentPtr == NULL) {
      puts("List is empty.\n");
      return;
   }
   puts("The list is:");
   while (currentPtr != NULL) {
      printf("%d %s -->", currentPtr->id, currentPtr->name);
      currentPtr = currentPtr->nextPtr;
   }
   puts("%d %s -->NULL", currentPtr->id, currentPtr->name);
}

void printListR(LLPtr currentPtr) {
   if (currentPtr == NULL) return;
   // เดินไปให้สุดก่อน
   while (currentPtr->nextPtr != NULL) {
      currentPtr = currentPtr->nextPtr;
   }
   // ถอยหลังกลับ
   while (currentPtr != NULL) {
      printf(" %d %s -->", currentPtr->id, currentPtr->name);
      currentPtr = currentPtr->pPtr;
   }
   puts("NULL\n");
}

// ฟังก์ชันลบข้อมูลตาม ID
int deletes(LLPtr *sPtr, int id) {
    LLPtr currentPtr = *sPtr;

   while (currentPtr != NULL && currentPtr->id != id) {
      currentPtr = currentPtr->nextPtr;
   }

   if (currentPtr != NULL) {
      LLPtr tempPtr = currentPtr;
      
      if (currentPtr->pPtr == NULL) { // ลบตัวแรก
            *sPtr = currentPtr->nextPtr;
            if (*sPtr != NULL) (*sPtr)->pPtr = NULL;
      } else {
            currentPtr->pPtr->nextPtr = currentPtr->nextPtr;
            if (currentPtr->nextPtr != NULL) {
               currentPtr->nextPtr->pPtr = currentPtr->pPtr;
            }
      }
      free(tempPtr);
      return 1;
   }
   return 0;
}

// ฟังก์ชันล้าง Memory ทั้งหมดตอนจบโปรแกรม
void clearList(LLPtr *sPtr) {
   LLPtr currentPtr = *sPtr;
   LLPtr tempPtr;
   
   while (currentPtr != NULL) {
      tempPtr = currentPtr;
      printf("delete %d\n", tempPtr->id);
      currentPtr = currentPtr->nextPtr;
      free(tempPtr);
   }

   *sPtr = NULL;
}

