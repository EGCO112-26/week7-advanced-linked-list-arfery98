// Fig. 12.3: fig12_03.c
// Inserting and deleting nodes in a list
#include <stdio.h>
#include <stdlib.h>
#include "ll.h"

int main(void) {
   LLPtr startPtr = NULL;
   unsigned int choice;
   int id;
   char name[50];

   instructions();
   printf("? ");
   scanf("%u", &choice);

   while (choice != 3) {
      switch (choice) {
         case 1:
            printf("Enter id and name: ");
            scanf("%d %s", &id, name);
            insert(&startPtr, id, name);
            printList(startPtr);
            printListR(startPtr);
            break;
         case 2:
            if ( !isEmpty(startPtr) ) {
               printf("Enter number to be deleted: ");
               scanf("%d", &id);
                  if (deletes(&startPtr, id)) {
                     printf("%d deleted.\n", id);
                     printList(startPtr);
                     printListR(startPtr);
                  } else {
                        printf("%d not found.\n", id);
                  }
               } else {
                  puts("List is empty.\n");
               }
               break;
         default:
            puts("Invalid choice.\n");
            instructions();
            break;
      }

      printf("? ");
      scanf("%u", &choice);
   }

   puts("Clear all nodes");
   clearList(&startPtr);
   puts("End of run.");
   return 0;
}