/*
   This is the final and most advanced
   version of the Singly Linked List.
   This complete implementation focuses on
   integrating advanced algorithms, sorting
   techniques, and safe memory management.

    **      Advanced Functionality     **

   - Sorting Algorithms: Includes optimized
     implementations of both Bubble Sort and
     Selection Sort, designed for linked structure
     by swapping node data to preserve pointer
     integrity and maintain node connectivity.

   - Optimized Linear Search: Includes an optimized
     sequential search implementation that makes
     use of sorted list and terminates early if
     reaching a value greater than the target.
     In case of unsorted, it searches normally
     until reaching the target or the end of the list.

   - Reverse Function: An efficient in-place
     implementation that reverses the entire list
     structure by redirecting node pointers,
     alterning the sequence without allocating
     additional memory.

   - Reset Function: A full memory cleanup function
     that safely deallocates all nodes from the heap
     to prevent memory leaks and reset the list to
     its initial state.

    **      The Search Limitations      **
   - No Binary Search: The major limitation in
     linked list structure is that Binary Search
     is not possible to apply on linked list.
     Because nodes are stored in non-contiguous
     memory locations we cannot access nodes
     with index. Binary Search requires access to the
     middle element of list instantly to be applicable.
     In linked list we must traverse the list from
     the Head to reach the middle element. Therefore
     Searching is strictly limited to Linear Search
     with time complexity of O(n).

   **           Structural Goal           **
   - To build a clean, fully optimized and advanced
     linear structure that demonstrates how to perform
     sorting, searching and proper memory deallocation
     in a Singly Linked List.

   **         Complexity Analysis         **
   - Prependind a new node to the list:  O(1).                       "Updating pointers only"
   - Appending a new node to the list:   O(1).                       "Thanks to Tail pointer"
   - Inserting node at specific place:   O(n).                    "Require traversing to place"
   - Deleting the first node from list:  O(1).                       "Updating pointers only"
   - Deleting the last node from list:   O(n).                   "Require traverse to update tail"
   - Deleting element at specific place: O(n).                   "Require traverse to find place"
   - Updating first element of the list: O(1).
   - Updating last element of the list:  O(1).                       "Thanks to Tail pointer"
   - Updating element at specific place: O(n).                    "Require traverse to find place"
   - Searching for specific element:     O(n)   Omega(1).        "Limited to Linear Search algorithm"
   - Deleting element by its value:      O(n)   Omega(1).        "Require traversing to find target"
   - Updating element by its value:      O(n)   Omega(1).        "Require traversing to find target"
   - Sort list with Selection Sort:      O(n^2) Omega(n^2).               "Blind algorithm"
   - Sort list with Bubble Sort:         O(n^2) Omega(n).              "Intelligent algorithm"
   - Reverse the entire list order:      O(n).                  "Require traversing to reverse pointers"
   - Display all elements of the list:   O(n).                  "Require traversing to display elements"
   - Reset the list to initial state:    O(n).                     "Require traversing to free nodes"
   */

#include <stdio.h>
#include <stdlib.h>

typedef struct node{

  int data;
  struct node* next;
} node;

typedef struct{

  node* head;
  node* tail;
  int size;
  int is_sorted;
} LIST;

//input functions.
int get_int(char* request);                            //this function to take integer value from user.
int get_positive_int(char* request);              //this function to take positive integer value from user.

//Linked List functions.
LIST* init_list();                                        //this function to initialize a new LIST.
node* create_node(int value);                     //this function to create a new node for the given element.
void prepend(LIST* list, node* ptr);                  //this function to prepend a new node to the list.
void append(LIST* list, node* ptr);                    //this function to append a new node to the list.
void insert_at(LIST* list, node* ptr, int place); //this function to insert a new node at specific place in list.
void delete_first(LIST* list);                        //this function to delete the first node from the list.
void delete_last(LIST* list);                         //this function to delete the last node from the list.
void delete_at(LIST* list, int place);            //this function to delete node at specific place from list.
void update_first(LIST* list, int new_value);       //this function to update the first element of the list.
void update_last(LIST* list, int new_value);        //this function to update the last element of the list.
void update_at(LIST* list, int place, int new_value); //this function to update element at specific place in list.
void search_for(LIST* list, int target);            //this function to search for the place of specific element.
void delete_by_value(LIST* list, int target);       //this function to delete specific element by its value.
void update_by_value(LIST* list, int target, int new_value);//this function to update specific element by its value.
void selection_sort(LIST* list);               //this function to sort elements of the list with selection sort.
void bubble_sort(LIST* list);                   //this function to sort elements of the list with bubble sort.
void insert_in_order(LIST* list, node* ptr);  //this function to insert new node in its correct order to the list.
void reverse_list(LIST* list);                      //this function to reverse the order of the entire list
void display_list(LIST* list);                    //this function to display all elements stored in the list.
void display_info(LIST* list);                      //this function to display information about the list.
void display_templete();                        //this function to display operations templete and their codes.
void reset_list(LIST* list);         //this function to free all nodes of list and return it to the initial state.
void destroy_list(LIST* list);                //this function to free all memory we have allocated to the list.

int main(void){

  //initialize a new list.
  LIST* my_list = init_list();
  if (my_list == NULL){
    return 1;             //if we fail to allocate space for the list we end the program.
  }
  //welcome user and display operations templete.
  printf("\nWelcome to Singly Linked List management system.\n\n");
  display_templete();

  //take user input and perform desired operations.
  int code;
  do{
    code = get_int("\nEnter the code of operation you want to perform: ");
    //check code and perform desired operation.
    //Prepending process.
    if (code == 1){         //ask user for number of elements he will prepend.
      int number = get_int("Enter number of elements you want to prepend: ");
      for (int i = 0; i < number; i++){     //iterate to take value of elements and prepend them.
        int value = get_int("Enter element you want to prepend: ");
        node* ptr = create_node(value);     //create a new node for the element.
        if (ptr == NULL){
          destroy_list(my_list);    //if function fails to allocate space for node we free the list and exit.
          return 1;
        }
        prepend(my_list, ptr);      //prepend the node by prepending function.
      }
    }else if (code == 2){    //Appending process.
      int number = get_int("Enter number of elements you want to append: ");
      for (int i = 0; i < number; i++){     //iterate to take value of elements and append them.
        int value = get_int("Enter element you want to append: ");
        node* ptr = create_node(value);     //create a new node for the element.
        if (ptr == NULL){
          destroy_list(my_list);    //if function fails to allocate space for node we free the   list and exit.
          return 1;
        }
        append(my_list, ptr);       //append the node by appending function.
      }
    }else if (code == 3){   //Inserting process.
      int value = get_int("Enter value of element you want to insert: ");
      int place = get_positive_int("Enter place (start from 0) you want to insert at: ");
      node* ptr = create_node(value);     //create new node for the element.
      if (ptr == NULL){
        destroy_list(my_list);    //if function fails to allocate space for node we free the list and exit.
        return 1;
      }
      insert_at(my_list, ptr, place);   //insert the node at given place by insertion function.
    }else if (code == 4){   //Deleting first element process.
      int number = get_int("Enter number of elements you want to delete from the start: ");
      for (int i = 0; i < number; i++){   //iterate and delete the number of elements.
        delete_first(my_list);
      }
    }else if (code == 5){   //Deleting last element process.
      int number = get_int("Enter number of elements you want to delete from the end: ");
      for (int i = 0; i < number; i++){     //iterate and delete the number of elements.
        delete_last(my_list);
      }
    }else if (code == 6){   //Deleting by place process.
      int place = get_positive_int("Enter place (start from 0) you want to delete from: ");
      delete_at(my_list, place);    //take index from user and delete element by deletion function.
    }else if (code == 7){   //Updating first process.
      int new_value = get_int("Enter new value you want to update first element with: ");
      update_first(my_list, new_value);   //take new value from user and update element by update function.
    }else if (code == 8){   //Updating last process.
      int new_value = get_int("Enter new value you want to update last element with: ");
      update_last(my_list, new_value);  //take new value from user and update element by update function.
    }else if (code == 9){   //Updating by place process.
      int number = get_int("Enter number of elements you want to update its value: ");
      for (int i = 0; i < number; i++){   //iterate to take places and new values to update elements.
        int place = get_positive_int("Enter place (start from 0) of element you want to upadte: ");
        int new_value = get_int("Enter new value you want to update this element with: ");
        update_at(my_list, place, new_value);   //update desired elements by update function.
      }
    }else if (code == 10){    //Searching process.
        int number = get_int("Enter number of elements you want to search for: ");
        for (int i = 0; i < number; i++){   //iterate to take elements and search for them.
          int target = get_int("Enter value of element you want to search for its place: ");
          search_for(my_list, target);
        }
    }else if (code == 11){    //Deleting by value process.
      int number = get_int("Enter number of elements you want delete by its value: ");
      for (int i = 0; i < number; i++){
        int target = get_int("Enter value of element you want to delete from list: ");
        delete_by_value(my_list, target);
      }
    }else if (code == 12){    //Updating by value process.
      int number = get_int("Enter number of elements you want to update by its value: ");
      for (int i = 0; i < number; i++){   //iterate to take targets and new values to update elements.
        int target = get_int("Enter value of element you want to update: ");
        int new_value = get_int("Enter new value you want to update this element with: ");
        update_by_value(my_list, target, new_value);  //update desired element by update function.
      }
    }else if (code == 13){    //Sorting with Selection Sort process.
      selection_sort(my_list);
    }else if (code == 14){    //Sorting with Bubble sort process.
      bubble_sort(my_list);
    }else if (code == 15){    //Inserting in order process.
      printf("#To perform this operation, we will sort the list if it was unsorted.\n");
      int answer = get_int("If you agree to sort list and perform operation, Enter 1: ");
      if (answer == 1){   //if the user agrees to sort the list we ask for number of elements he want to insert.
        int number = get_int("\nEnter number of elements you want to insert in order: ");
        for (int i = 0; i < number; i++){     //iterate to take elements we will insert in order.
          int value = get_int("Enter value of element you want to insert in order:  ");
          node* ptr = create_node(value);     //create new node for the element.
          if (ptr == NULL){
            destroy_list(my_list);   //if function fails to allocate space for node we free all memory and exit.
            return 1;
          }
          insert_in_order(my_list, ptr);      //insert elements in correct order with customized function.
        }
      }
    }else if (code == 16){    //Display elements process.
      display_list(my_list);
    }else if (code == 17){    //Display info process.
      display_info(my_list);
    }else if (code == 18){    //Display operations templete process.
      display_templete();
    }else if (code == 19){    //Reversing list process.
      reverse_list(my_list);
    }else if (code == 20){    //Reset list process.
      reset_list(my_list);
    }else if (code == 21){    //Exit process.
      printf("Exit the system.\n");
    }else{                    //Invalid input process.
      printf("Invalid input! Enter (18) to check operations templete.\n");
    }
  } while (code != 21);       //iterate until user enters exit code (21).

  destroy_list(my_list);      //at the end we free all memory we have allocated to avoid memory leak.
  return 0;
}

int get_int(char* request){

  int value;            //this variable to store the scanned value.
  int status;           //this variable to store the return value of scanf.
  do{
    printf("%s", request);            //print request to ask user for input.
    status = scanf("%i", &value);     //scan the input with scanf and store its return value.
    while(getchar() != '\n');         //clean the buffer from garbage input or '\n'.
  } while (status == 0);      //we iterate until we get a valid input as scanf return zero in case of failure.

  return value;
}

int get_positive_int(char* request){

  int value;         //this variable to store the return value of get int function.
  do{
    value = get_int(request);
  } while (value < 0);    //we iterate and call get int function until it returns a positive (>= 0) value.

  return value;
}

LIST* init_list(){

  LIST* ptr = malloc(sizeof(LIST));
  if (ptr == NULL){
    return NULL;        //if malloc fails to allocate space for list it return NULL.
  }
  ptr->head = NULL;                  //initialize list variables.
  ptr->tail = NULL;
  ptr->size = 0;
  ptr->is_sorted = 0;

  return ptr;                //return the pointer of the memory we allocated.
}

node* create_node(int value){

  node* ptr = malloc(sizeof(node));
  if (ptr == NULL){
    return NULL;        //if malloc fails to allocate space for node it return NULL.
  }
  ptr->data = value;                  //initialize node variables.
  ptr->next = NULL;

  return ptr;              //return the pointer of the memory allocated for node.
}

void prepend(LIST* list, node* ptr){
  //if the list is empty.
  if (list->head == NULL){
    list->head = list->tail = ptr;    //make head and tail point to new and only node.
    list->size++;                     //increase list size by one.
    list->is_sorted = 1;              //change is_sorted to true (1) as there is only one element.
  }else{  //if the list has stored elements already.
    ptr->next = list->head;           //make new node point to head of the list.
    list->head = ptr;                 //update head to point to new node.
    list->size++;                     //increase size by one.
    list->is_sorted = 0;              //change is_sorted to false (0) as new element can be out of order.
  }
  printf("Element prepended successfully.\n");
}

void append(LIST* list, node* ptr){
  //if the list is empty.
  if (list->head == NULL){
    list->head = list->tail = ptr;    //make head and tail point to new and only node.
    list->size++;                     //increase size by one.
    list->is_sorted = 1;              //change is_sorted to true (1) as there is only only element.
  }else{   //else, is the list has stored element already.
    list->tail->next = ptr;           //make the tail node points to new node.
    list->tail = ptr;                 //update tail to points to the new node.
    list->size++;                     //increase size by one.
    list->is_sorted = 0;              //change is_sorted to false (0) as new element can be out of order.
  }
  printf("Element appended successfully.\n");
}

void insert_at(LIST* list, node* ptr, int place){
  //if the place is bigger than list size.
  if (place > list->size){
    printf("We cannot insert at place %i! Total size of list is %i!\n", place, list->size);
    printf("Operation Skipped!\n");
    free(ptr);      //free the memory allocated for node as we will lose its address if we do not add it to list.
  }else if (place == list->size){
    append(list, ptr);           //if place equalls list size we call append function to update tail pointer.
  }else if (place == 0){
    prepend(list, ptr);           //if place equalls zero we call prepend function to update head pointer.
  }else{  //if place is in-between two elements in the list.
    int index = 0;          //this variable to track the current index.
    for (node* current = list->head; current != NULL; current = current->next){
      //if we reach the previous node to place.
      if (place == index + 1){
        ptr->next = current->next;      //make the new node points to next node of current.
        current->next = ptr;            //make current node points to new node.
        list->size++;                   //increase size by one.
        list->is_sorted = 0;            //change is_sorted to false (0) as new element can be out of  order.
        printf("Element inserted successfully.\n");
        return;                         //then, return to avoid wasteful iterations.
      }
      index++;                          //increase index by one to keep track of current place.
    }
  }
}

void delete_first(LIST* list){
  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! There is No elements to delete!\n");
    return;
  }else if (list->head == list->tail){ //Special case (Only one element at list): require updating tail pointer.
    free(list->head);                 //free the only node at list.
    list->head = list->tail = NULL;   //make head and tail point to NULL.
    list->size--;
  }else{  //else if list has more elements than one.
    node* temp = list->head;           //store address of first node at temporary variable.
    list->head = list->head->next;     //update head to be the next node of head.
    free(temp);                        //free the first node with the temporary variable.
    list->size--;
  }
  printf("Element deleted successfully.\n");
}

void delete_last(LIST* list){
  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! There is No elements to delete!\n");
    return;
  }else if (list->head == list->tail){  //Special case (Only one element at list): require updating head pointer.
    free(list->tail);                   //free the only node.
    list->head = list->tail = NULL;     //make head and tail point to NULL.
    list->size--;
  }else{  //else if list has more element than one, we must traverse to update the tail pointer.
    for (node* current = list->head; current != NULL; current = current->next){
      //if reaching the previous node to tail.
      if (current->next == list->tail){
        free(list->tail);         //free the tail node.
        list->tail = current;     //update tail to point to previous node.
        current->next = NULL;     //make new tail point to NULL.
        list->size--;
      }
    }
  }
  printf("Element deleted successfully.\n");
}

void delete_at(LIST* list, int place){
  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! There is No elements to delete!\n");
  }else if (place >= list->size){    //if place is greater than list size.
    printf("There is No elements at that place to delete!\n");
  }else if (place == list->size - 1){  //if place equalls (size - 1) we call delete last to update tail pointer.
    delete_last(list);
  }else if (place == 0){  //if place equalls zero we call delete first to update head pointer.
    delete_first(list);
  }else{    //if place is in the middle of the list we traverse until finding it.
    int index = 0;          //this variable to track the current place.
    for (node* current = list->head; current != NULL; current = current->next){
      //if reaching the previous node to target.
      if (place == index + 1){
        node* temp = current->next;           //store tha address of next node (target) in temporary variable.
        current->next = current->next->next;      //make current node points to the next node of target.
          free(temp);                               //free the target with the temporary variable.
          list->size--;
        printf("Element deleted successfully.\n");
        return;                               //return after deleting the target to avoid wasteful iterations.
      }
      index++;                                //increase index to keep tracking current place.
    }
  }
}

void update_first(LIST* list, int new_value){
  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! There is No elements to update!\n");
  }else{    //if there are stored elements in the list.
    list->head->data = new_value;             //update head node data to equal new value.
    list->is_sorted = 0;                      //change is_sorted to false (0) as new value can be out of order.
    printf("Element updated successfully.\n");
  }
}

void update_last(LIST* list, int new_value){
  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! There is No elements to update!\n");
  }else{  //else if the list has stored elements already.
    list->tail->data = new_value;               //update tail node data to equal new value.
    list->is_sorted = 0;                        //change is_sorted to false (0) as new value can be out of order.
    printf("Element updated successfully.\n");
  }
}

void update_at(LIST* list, int place, int new_value){
  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! There is No elements to update!\n");
  }else if (place >= list->size){       //else if place is bigger than list size.
    printf("There is No elements in this place to update!\n");
  }else if (place == list->size - 1){
    update_last(list, new_value); //else if place is the last element we call update last to avoid traversing O(n).
  }else{    //else if place is in the middle of the list.
    int index = 0;        //this counter to track current place.
    for (node* current = list->head; current != NULL; current = current->next){
      //if reaching the target place.
      if (place == index){
        current->data = new_value;        //update data stored in current node to equal new value.
        list->is_sorted = 0;       //change is_sorted variable to be false (0) as new value can be out of order.
        printf("Element updated successfully.\n");
        return;                     //after updating target we return to avoid wasteful iterations.
      }
      index++;                  //at every iteration we increase index by one to keep tracking current place.
    }
  }
}
//this function use intelligent search that makes use of list if it was sorted and exit early if reaching a value
void search_for(LIST* list, int target){  //bigger than target, otherwise it continue searching until end of list.
  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! There is No elements to search for!\n");
  }else{  //else if list has stored elements.
    int index = 0;        //set a counter to track current index.
    for (node* current = list->head; current != NULL; current = current->next){
      //if reaching target.
      if (current->data == target){
        printf("Element: (%i) found at index %i.\n", target, index);
        return;       //after finding the target we return to avoid wasteful iterations.
      }else if (list->is_sorted == 1 && current->data > target){
        printf("Early detection: Element is not in the list.\n");
        return;  //if the list is sorted and we reach a value bigger than target then target is not in the list.
      }
      index++;    //at every iteration we increase counter to keep tracking current index.
    }
    printf("Element Not fount in the list.\n");
  }
}
/*NOTE: We could easily call search function to find place then call delete_at function with that place.
But this is not efficient as we will traverse two times: first for searching and the second for actual deletion.*/
void delete_by_value(LIST* list, int target){
  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! There is No elements to delete!\n");
  }else if (target == list->head->data){
    delete_first(list);       //if target is the head element we call delete first to update head pointer.
  }else if (target == list->tail->data){
    delete_last(list);  //if target is the last element we call delete last to avoid traverse and to update tail.
  }else{    //else if element is in the middle of list.
    for (node* current = list->head; current->next != NULL; current = current->next){
      //if reaching previous node to target.
      if (target == current->next->data){
        node* temp = current->next;           //store address of target in temporary variable.
        current->next = current->next->next;  //make current node points to next node of target.
        free(temp);                           //free target node by tmeporary variable.
        list->size--;
        printf("Element deleted successfully.\n");
        return;                               //return after deleting target to avoid wasteful iterations.
      }
    }
    printf("Element not found in the list!\n");
  }
}

void update_by_value(LIST* list, int target, int new_value){
  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! There is No elements to update!\n");
  }else{    //else if list has stored elements.
    for (node* current = list->head; current != NULL; current = current->next){
      //if reaching the target.
      if (current->data == target){
        current->data = new_value;        //update data stored in target to equal new value.
        list->is_sorted = 0;          //change is_sorted variable to false (0) as new value can be out of order.
        printf("Element updated successfully.\n");
        return;                       //return after updating element to avoid wasteful iterations.
      }
    }
    printf("Element not found in the list!\n");
  }
}

void selection_sort(LIST* list){
  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! There is No elements to sort!\n");
  }else{  //else if list has stored elements.
    if (list->is_sorted == 1){    //if the list is already sorted.
      printf("The list is already sorted!\n");
    }else{        //else if list is unsorted.
      for (node* current = list->head; current != NULL; current = current->next){
        for (node* compare = current->next; compare != NULL; compare = compare->next){
          //if any value of the following elements is smaller than current we swap them.
          if (compare->data < current->data){
            int temp = current->data;       //store value of current in temporary variable.
            current->data = compare->data;  //make current node equal the smaller value of compare.
            compare->data = temp;           //make compare value equal temp.
          }
        }
      }
      list->is_sorted = 1;    //change is_sorted variable to true (1) after sorting the entire list.
      printf("The list is sorted successfully in ascending order.\n");
    }
  }
}

void bubble_sort(LIST* list){
  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! There is No elements to sort!\n");
  }else if (list->is_sorted == 1){    //if the list is sorted.
    printf("The list is already sorted!\n");
  }else{    //else if list is unsorted.
  //this implementation sort elements from end as we cannot traverse in backward, so we use size to stop the loop.
    for (int stop_place = list->size - 1; stop_place > 0; stop_place--){
      int swaps = 0;    //set counter to track number of swaps to exit early if there are no swaps.
      int index = 0;    //set counter to track current place to stop if reaching sorted part.
      for (node* current = list->head; index < stop_place; current = current->next){
        //if value at current node is bigger than value of the next one, we swap them.
        if (current->data > current->next->data){
          int temp = current->data;
          current->data = current->next->data;
          current->next->data = temp;
          swaps++;          //increase swaps by one after any swap to check early exit condition.
        }
        index++;            //increase index by one to stop if reaching the sorted part.
      }
      if (swaps == 0){
        printf("Early exit condition activated to ensure efficient sorting.\n");
        break;      //after a full loop: if there is no swaps, then the list is sorted so we break outer loop.
      }
    }
    list->is_sorted = 1;    //change is_sorted variable to true (1) after sorting the list.
    printf("The list is sorted successfully in ascending order.\n");
  }
}

void insert_in_order(LIST* list, node* ptr){
  //if the list is empty we just prepend it.
  if (list->head == NULL){
    prepend(list, ptr);
  }else{    //else if list has stored elements already.
    bubble_sort(list);    //first: we must sort existing elements before insert the new node.
    //then: we insert the new node in its correct order.
    if (ptr->data <= list->head->data){         //if new element is smaller than head node.
      prepend(list, ptr); //we call prepend function to prepend new node, but we must change is_sorted to true (1).
      list->is_sorted = 1;           //as prepend function suppose that the new node can be out of order.
    }else if (ptr->data >= list->tail->data){   //else if new element if bigger than tail node.
      append(list, ptr);  //we call append function to append new node but, we must change is_sorted to true (1).
      list->is_sorted = 1;           //as append function suppose that the new node can be out of order.
    }else{      //else, the correct place must be in the middle of list.
      for (node* current = list->head; current->next != NULL; current = current->next){
        //if the value of next node is bigger than or equal new node we insert new element before it.
        if (current->next->data >= ptr->data){
          ptr->next = current->next;
          current->next = ptr;
          list->size++;
          printf("Element inserted successfully in its correct place.\n");
          return;               //return after insertion to avoid wasteful iterarions.
        }
      }
    }
  }
}

void reverse_list(LIST* list){
  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! There is No elements to reverse order!\n");
  }else{  //else if list has stored elements.
    //FIRST: traverse all nodes of list and reverse their order by pointers.
    node* current = list->head;        //make current pointer equal list head.
    node* following = current;         //keep two pointers to track next and later node addresses.
    node* later = current->next;
    while (later != NULL){
      following = later;          //first we update following to equal later to point to the next node of current.
      later = later->next;        //then, update later to equal later next to point to the next node of following.
      following->next = current;  //after that, make the following node points to current to reverse the order.
      current = following;        //finally, we update current to go to the next node.
    }
    //THEN: swap list head with list tail.
    list->head->next = NULL;       //first make head node points to NULL as it becomes the new tail node.
    node* temp = list->head;       //then, swap head with tail to ensure complete reversing.
    list->head = list->tail;
    list->tail = temp;
    if (list->head != list->tail){  //if the list contains more than one element and it was sorted,
      list->is_sorted = 0;          //then after reversing elements it becomes unsorted (in reverse order).
    }
    printf("The list is reversed successfully.\n");
  }
}

void display_list(LIST* list){
  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! There is No elements to display!\n");
  }else{  //else if list has stored elements.
    printf("All elements stored in the list:\n");
    int index = 0;    //set counter to track current place.
    for (node* current = list->head; current != NULL; current = current->next){
      printf("Element stored at index %i: %i\n", index, current->data);
      index++;      //at every iteration we increase counter to track current place.
    }
  }
}

void display_info(LIST* list){
  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! There is No elements stored in the list.\n");
  }else{  //else if list has stored elements.
    printf("This is a Singly Linked List Structure.\n");
    printf("The number of elements stored in the list is: %i\n", list->size);
    printf("The last element exist at index: %i\n", list->size - 1);
    if (list->is_sorted == 1){
      printf("The elements of the list are stored in ascending order.\n");
    }else{
      printf("The elements of the list are unsorted.\n");
    }
  }
}

void display_templete(){
  //display code of valid operations on the list.
  printf("These are the codes of operations you can perform on the list:\n");
  printf("1.Add element at the start.       2.Add element at the end.      3.Add element at specific place.\n");
  printf("4.Delete first element.           5.Delete last element.         6.Delete element from specific place.\n");
  printf("7.Update first element.           8.Update last element.         9.Update element at specific place.\n");
  printf("10.Search for specific element.   11.Delete element by value.    12.update element by its value.\n");
  printf("13.Sort list with Selection Sort. 14.Sort list with Bubble sort. 15.Insert element in correct order.\n");
  printf("16.Display all elements of list.  17.Display info about list.    18.Display operations templete.\n");
  printf("19.Reverse the entire list.       20.Reset list to initial state.      21.Exit the system.\n");
}

void reset_list(LIST* list){
  //if the list is empty.
  if (list->head == NULL){
    printf("The list is already at initial state!\n");
  }else{    //else if list has stored elements.
    //First, we traverse and free all nodes of the list.
    node* current = list->head;
    while (current != NULL){
      node* temp = current->next;   //store the address of the next node in temporary variable.
      free(current);                                  //free current node.
      current = temp;                 //then, update current to the next node by temp pointer.
    }
    //Then, reset list variables to initial state.
    list->head = list->tail = NULL;
    list->size = 0;
    list->is_sorted = 0;
    printf("The list is back to the initial state.\n");
  }
}

void destroy_list(LIST* list){
  //if the list is empty.
  if (list->head == NULL){
    free(list);     //if the list has No elements, we just free the list space.
  }else{  //else if list has stored elements.
    //First: traverse and free all nodes of the list.
    node* current = list->head;
    while (current != NULL){
      node* temp = current->next;         //store address of the next node in temporary pointer.
      free(current);                      //free the current node space.
      current = temp;                     //then, update current to point to the next node with temp pointer.
    }
    //Then: we can safely free the list space.
    free(list);
  }
}
