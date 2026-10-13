/*
   in this program we implement
   a "Circular Linked List".
   This is a formal data strucrure
   that organizes data in a "Closed Loop",
   where the sequence stays connected
   without any breaks.

    **  Features of Circular List   **
   - The program follows a "No-NULL"
     principle No node points to NULL.
   - The last node (Tail) is always
     linked back to the first node (Head).
   - This creates a one-way path that can
     go around the list infinitely.
   - In a single-node list, the node
     points to its own address to keep
     the loop.

    **   Advantages of Circular List   **
   - Full connectivity: Every node is reachable
     from any other node starting point by
     traversing the circle.
   - Direct Tail-to-Head Access: We can reach
     the beginning of the list again from the
     Tail without restarting or resetting the
     pointer.
   - Infinite Traversal: Perfectly suited for
     processes that need to repeat in cycles
     without manual pointer redirection.

    **   Disadvantages of Circular List   **
   - Infinite Loop Risks: Termination logic
     requires precision, we must compare
     node addresses instead of checking for NULL.
   - Logical Complexity: Operations like insertion
     and deletion require precise updates to keep
     the "Closing Link" maintained.
   - One-Way Traversal: To reach a previous node,
     we must complete a full cycle because there
     is no "Prev" pointer to point to previous node.

         **    Structural Goal     **
   - To build a "Closed Circuit" system where
     the "Head" and "Tail" remain connected,
     ensuring the circle is never broken
     during any operation.
   */

#include <stdio.h>
#include <stdlib.h>

typedef struct node{

    int data;
    struct node *next;
} node;

typedef struct{

    node* head;
    node* tail;
    int size;
} CIRCULARLIST;

//input functions.
int get_int(char* request);                         //this function to take an integer from user.
int get_positive_int(char* request);            //this function to take a positive integer from user.

//CIRCULARLIST functions.
CIRCULARLIST* init_circularlist();                //this function to initialize a new CIRCULARLIST.
void display_templete();                         //this function display the valid operations templete.
node* create_node(int value);                    //this function to create a new node with given value.
void prepend(CIRCULARLIST* list, node* ptr); //this function to add a new node at the start of the list.
void append(CIRCULARLIST* list, node* ptr);   //this function to add a new node at the end of the list.
void insert_at(CIRCULARLIST* list, node* ptr, int place); //this function to add a new node at given place.
void delete_first(CIRCULARLIST* list);      //this function to delete the first node (Head) of the list.
void delete_last(CIRCULARLIST* list);       //this function to delete the last node (tail) of the list.
void delete_at(CIRCULARLIST* list, int place);  //this function to delete node from specific place.
int search_for(CIRCULARLIST* list, int target); //this function to search for specific element, return index.
void delete_by_value(CIRCULARLIST* list, int value); //this function delete specific element by its value.
void display_list(CIRCULARLIST* list);      //this function to display all elements of the list.
void check_circular(CIRCULARLIST* list);    //this function to ensure that the tail points back to the head.
void destroy_list(CIRCULARLIST* list);     //this function to free all memory allocated for nodes and LIST.

int main(void){

    //initializing a circular list using init_circularlist function.
    CIRCULARLIST* my_list = init_circularlist();
    if (my_list == NULL){
      return 1;    //if function failed to allocate a space for list we exit the program.
    }

    //inform the user about the operations he can perform.
    printf("\nWelcome to Circular List management system\n\n");
    display_templete();

    //ask the user for the code of any operation he want to perform until he exit the system.
    int answer;     //this variable stores the input of user.
    do {
      //ask for the code of operation.
      answer = get_int("\nEnter the code of operation you want to perform: ");

      //prepending process.
      if (answer == 1){         //ask the user for number of elements he will add.
        int count = get_int("Enter the number of elements you want to prepend: ");
        for (int i = 0; i < count; i++){
          int value = get_int("Enter an element: ");
          node* ptr = create_node(value);     //make a node for the new element.
          if (ptr == NULL){                 //if the function fails to allocate space for node we exit.
            destroy_list(my_list);  //if we fail to allocate space for the new node we free all memory allocated
            return 1;                         //to avoid memory leak then return.
          }
          prepend(my_list, ptr);  //pass pointers of list and node to prepend function to add the new node.
        }
      }
      //appending process.
      else if (answer == 2){     //ask the user for number of elements he will add.
        int count = get_int("Enter the number of elements you want to append: ");
        for (int i = 0; i < count; i++){
          int value = get_int("Enter an element: ");
          node* ptr = create_node(value);       //create a node for the new element.
          if (ptr == NULL){
            destroy_list(my_list);  //if we fail to allocate space for the new node we free all memory allocated
            return 1;                                 //to avoid memory leak then return.
          }
          append(my_list, ptr);   //pass pointers of list and node to append function to add the new node.
        }
      }
      //inserting function.
      else if (answer == 3){          //we insert one element at a time as inserting change order.
        int value = get_int("Enter the element: ");
        //we use get_positive_int function when taking the index to ensure it must be valid index (>= 0).
        int place = get_positive_int("Enter the place (start from 0) you want to insert at: ");
        node* ptr = create_node(value);   //we create a node for the new element.
        if (ptr == NULL){
          destroy_list(my_list);  //if we fail to allocate space for new node we free all memory allocated
          return 1;                            //to avoid memory leak then return.
        }
        insert_at(my_list, ptr, place);  //pass pointers of list and node and the place to insert function.
      }
      //deleting first element process.
      else if (answer == 4){      //ask the user for the number of elements he want to delete from head.
        int count = get_int("Enter the number of elements you want to delete: ");
        for (int i = 0; i < count; i++){    //iterate (count) times and call delete_first function to
          delete_first(my_list);            //delete all elements the user wants to delete from head.
        }
      }
      //deleting last element process.
      else if (answer == 5){      //ask the user for the number of elements he want to delete from Tail.
        int count = get_int("Enter the number of elements you want to delete: ");
        for (int i = 0; i < count; i++){    //iterate (count) times and call delete_last function to
          delete_last(my_list);            //delete all elements the user wants to delete from Tail.
        }
      }
      //deleting by place process.
      else if (answer == 6){   //we will delete one element at a time as deleting from middle changes order.
        int place = get_positive_int("Enter the place (start from 0) of element you want to delete: ");
        delete_at(my_list, place);  //pass the list pointer and place to delete the element at given place.
      }
      //searching process.
      else if (answer == 7){    //ask the user for the number of elements he want to search for.
        int count = get_int("Enter the number of elements you want to search for their place: ");
        for (int i = 0; i < count; i++){
          int value = get_int("Enter an element: ");    //get value of element we want to search for.
          int index = search_for(my_list, value);   //call search function with the value and store its
        }                                           //return value in a garbage variable.
      }
      //deleting by value process.
      else if (answer == 8){         //ask the user for the number of elements he want to delete.
        int count = get_int("Enter the number of elements you want to delete: ");
        for (int i = 0; i < count; i++){
          int value = get_int("Enter a value of element you want to delete: ");
          delete_by_value(my_list, value);  //this function combines search and delete_at functions, so it
        }                                 //search for the place of element then call delete_at with place.
      }
      //displaying list process.
      else if (answer == 9){
        display_list(my_list);    //call display list function to display all elements of list.
      }
      //check circularity process.
      else if (answer == 10){
        check_circular(my_list);    //call check circular function to ensure circularity feature of list.
      }
      //display operations templete process.
      else if (answer == 11){
        display_templete();         //call display templete to display all valid operations.
      }
      //exit process.
      else if (answer == 12){         //the condition is checked after the body of do-while ends.
        printf("Exit the system.\n");
      }
      //invalid input process.
      else{
        printf("Invalid input! Enter (11) to check operations templete.\n");
      }
    } while (answer != 12);       //iterate until the user enters exit code (12).

    destroy_list(my_list);  //At the end, we call destroy function to free
    return 0;               //all allocated memory to prevend memory leak.
}

int get_int(char* request){

  int value;        //the input value and we put it here to be in scope of return.
  int status;       //this is the return value of scanf, put here to be in scope of while.
  do {                              //Every iteration we do three steps:
    printf("%s", request);          //print the request to ask for input.
    status = scanf("%i", &value);   //scan the input using scanf function.
    while (getchar() != '\n');       //clear buffer from garbage input or '\n'
  } while (status == 0);            //if scanf failed (do not match input type) it returns zero so
                                    //we iterate until scanf succeed.
  return value;
}

int get_positive_int(char* request){

  int value;       //this is return value of get_int function (value), put here to be in scope of while.
  do {
    value = get_int(request);       //store the return value of get_int in the value variable.
  } while (value < 0);             //we iterate untill it returns positive number.

  return value;                     //finally, we return the positive number.
}

CIRCULARLIST* init_circularlist(){

  CIRCULARLIST* list = malloc(sizeof(CIRCULARLIST));    //allocate space for CIRCULARLIST variables.
  if (list == NULL){                                   //and store the return value in list pointer.
    return NULL;           //if malloc fails to allocate space it returns NULL so we return WARN to main.
  }
                        //in case of success we initialize the CIRCULARLIST variables:
  list->head = NULL;    //set head and tail pointers to NULL and size with zero.
  list->tail = NULL;
  list->size = 0;

  return list;            //finally, we return the list pointer to the main function.
}

node* create_node(int value){

  node* ptr = malloc(sizeof(node));   //allocate space for a new node and store address in ptr pointer.
  if (ptr == NULL){                   //if malloc fails it return NULL so we WARN the main function.
    return NULL;
  }
  ptr->data = value;    //in case of success we initilize node's data with given value and next with NULL.
  ptr->next = NULL;

  return ptr;             //finally we return the pointer of the new node.
}

void prepend(CIRCULARLIST* list, node* ptr){

  //there are two cases to handle when prepending new node:
  //1: if the list is empty
  if (list->head == NULL){             //in case of empty the head points to NULL
    list->head = list->tail = ptr;     //we make head and tail point to new and only node.
    ptr->next = ptr;                   //we make the new and only node points to its place by set the next
    list->size++;                      //field to the address of new node (ptr) to make the list circular.
  }
  //2: if the list has elements already.
  else{
    ptr->next = list->head;           //we make new node points to the list head.
    list->head = ptr;                 //then we update list head to points to the new node (new head).
    list->tail->next = list->head;   //then make the last node points back to the new head by tail pointer.
    list->size++;                     //finally increase list size by one.
  }
  printf("Element prepended successfully\n");   //after any case we tell the user that prepending succeed.
}

void append(CIRCULARLIST* list, node* ptr){

  //we have two cases to handle when appending a new node.
  //1. if the list is empty
  if (list->head == NULL){          //if the list is empty then the head will be points to NULL.
    list->head = list->tail = ptr;  //we make head and tail pointers point to new and only node.
    ptr->next = ptr;                //then, we make new and only node points to its place by setting
    list->size++;                   //the next field to the address of node (ptr) to make circular list.
  }
  //2. if the list has elements already.
  else{
    ptr->next = list->tail->next;   //first we make next field of new node equalls the current tail->next
    list->tail->next = ptr;         //which points to the head then make last node points to new node.
    list->tail = ptr;               //then, update the tail pointer to point to new node (new tail).
    list->size++;                   //finally, increase the list size by one.
  }
  printf("Element appended successfully\n");   //after any case we tell the user that appending succeed.
}

void insert_at(CIRCULARLIST* list, node* ptr, int place){

  //we have four cases to handle when insert a new node at given place.
  //1. if the place is beyond the size of the list.
  if (place > list->size){
    printf("Insert Failed! we cannot insert at place %i! All size of the list is %i!\n",place, list->size);
    free(ptr);  //we free the node as we will not insert it and it will cause memory leak if it becomes isolated.
  }
  //2. if the place is zero we call prepend function.
  else if (place == 0){
    prepend(list, ptr);
  }
  //3. if place was the following to tail we call append function.
  else if (place == list->size){
    append(list, ptr);
  }
  //4. if place was in the middle of the list.
  else{
    //we traverse until reaching the node before the place.
    int i = 0;    //this is a counter to track the index of current node.
    node* current = list->head;
    do{     //we use do-while loop to perform the first iteration and update current before checking it.
      //check if the place is the following to current node.
      if (place == i + 1){              //if place was the following to current node.
        ptr->next = current->next;      //we make new node points to the next node to current.
        current->next = ptr;            //then make the current points to new node.
        list->size++;                   //we increase size by one.
        printf("Element inserted successfully\n");
        return;             //we return after insertion to prevent wasteful iterations.
      }
      i++;       //increase the counter to the index of the next node.
      current = current->next;
    } while (current != list->head);  //check if reaching the end of list as the last element points back
  }                                                     //to the first element (head).
}

void delete_first(CIRCULARLIST* list){

  //we have three cases to handle when deleting first node.
  //1. if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! No elements to delete!\n");
    return;           //we return to avoid printing deleting message.
  }
  //2. if the list has only one element.
  else if (list->head == list->tail){
    free(list->head);                 //free the only node we have.
    list->head = list->tail = NULL;   //make head and tail point to NULL.
    list->size--;                     //decrease size by one.
  }
  //3. if the list has elements more than one.
  else{
    node* temp = list->head;          //use temp pointer to free the first node.
    list->head = list->head->next;    //update the head to point to next node (new head).
    list->tail->next = list->head;    //update the tail to point to new head.
    free(temp);                       //free the first node by temp pointer.
    list->size--;
  }
  printf("Element deleted successfully\n");  //after deletion succeed at any case we notify the user.
}

void delete_last(CIRCULARLIST* list){

  //we have three cases to handle when deletin last node.
  //1. if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! No elements to delete!\n");
    return;
  }
  //2. if there is only one element in the list.
  else if (list->head == list->tail){
    free(list->tail);                   //freeing the last and only node.
    list->head = list->tail = NULL;     //make head and tail point to NULL.
    list->size--;                       //decrease size by one.
  }
  //3. if there are elements in the list more than one.
  else{
    //traverse until reaching the previous node to last to update tail pointer.
    node* current = list->head;
    do{     //we use do-while loop to perform the first iteration and update current before checking it.
      //check if the next node was last one.
      if (current ->next == list->tail){
        current->next = current->next->next; //make current node point to head that the last node points to it.
        free(list->tail);                    //free last node by tail pointer.
        list->tail = current;                //update list tail to point to current node (new tail)
        list->size--;                        //decrease size by one.
      }
      current = current->next;
    } while (current != list->head);    //check if we reach end of list as it points back to the head.
  }
  printf("Element deleted successfully\n");   //after any successful deletion we notify the user.
}

void delete_at(CIRCULARLIST* list, int place){

  //we have five cases to handle when deleting a node from specific place.
  //1. if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! No elements to delete!\n");
    return;
  }
  //2. if place as beyond the size of list.
  else if (place >= list->size){
    printf("There is no element in this place to delete!\n");
    return;
  }
  //3. if the place was the head of the list.
  else if (place == 0){
    delete_first(list);     //we call delete_first function to deal with this case.
  }
  //4. if the place was the tail of the list.
  else if (place == list->size - 1){
    delete_last(list);
  }
  //5. if the place was in the middle of the list.
  else{
    int i = 0;    //set a counter to track the index of current node.
    //traverse until reaching the previous node to target.
    node* current = list->head;
    do{     //we use do-while loop to perform the first iteration and update current before checking it.
      //check if the target was the next node.
      if (place == i + 1){
        node* temp = current->next;   //store address of the next node (target) in temporary pointer.
        current->next = current->next->next;      //make current node points to the next node of target.
        free(temp);                   //free the target with the temporary pointer to avoid memory leak.
        list->size--;
        printf("Element deleted successfully\n");     //after successful deletion we notify the user.
        return;
      }
      i++;
      current = current->next;
    } while (current != list->head);
  }
}

int search_for(CIRCULARLIST* list, int target){

  //we have three cases to handle when searching for specific element.
  //1. if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! No elements in the list\n");
    return -1;        //we return (-1) as special return value in case of not founding the target.
  }
  //2. if the list has stored elements already.
  else{
    int i = 0;      //set a counter to track the index of current node.
    //traverse until finding the target element or reaching the end of list.
    node* current = list->head;
    do{   //we use do-while loop to perform the first iteration and update current before checking it.
      //check if the current element is the target.
      if (current->data == target){
        printf("Element found in place %i\n", i);   //we print the place of elment.
        return i;                                   //and return it to be used in other operations.
      }
      i++;
      current = current->next;
    } while(current != list->head);   //we check if reaching the end of list as it points back to head.

    //if the loop ended without founding the target, then it does not exist in the list.
    printf("This element does not exist in the list\n");
    return -1;
  }
}

void delete_by_value(CIRCULARLIST* list, int value){  //this function combine the two previous functions.

  //first: we identify the index of element by search_for function.
  int place = search_for(list, value);
  if (place == -1){           //if the element does not exist in the list we return.
    return;
  }
  //then: we pass the index of founded element to delete_at function to delete element.
  delete_at(list, place);
}

void display_list(CIRCULARLIST* list){

  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty!\n");
  }
  //if the list has stored elements.
  else {
    printf("All elements stored in list\n");
    //traverse the list until reaching the last node and print the value of each one.
    int i = 0;    //we set a counter to track the index of current node.
    node* current = list->head;
    do{   //we use do-while loop to perform the first iteration and update current before checking it.
      printf("Element at index: %i is %i\n", i, current->data);
      i++;        //increase counter to track the current index.
      current = current->next;
    } while(current != list->head);  //we check if reaching the end of list as last element points to head.
  }
}

void check_circular(CIRCULARLIST* list){

  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! Add elements to check circular list\n");
  }
  //if the list has stored elements already.
  else{
    //display the address of head and the address that the last node points to it.
    printf("The address of the first node (head) is %p\n", list->head);
    printf("The last node of the list points to address %p\n", list->tail->next);
    printf("\nThis ensures that the last element points back to the head in circular list\n");
  }
}

void display_templete(){

  //print the templete of the all possible operation we can perform and code of each operation.
    printf("you can perform the following set of operation on the Circular List:\n");
    printf("1. Add elements at first,  2. Add elements at the end,    3. Add element at specific place\n");
    printf("4. Delete first element,   5. Delete last element,     6. Delete element from specific place\n");
    printf("7. Search for specific element,       8. Delete specific element by its value\n");
    printf("9. Display all elements in the list,  10. Check circularity of the list\n");
    printf("11. Display operations templete,      12. Exit the system\n");
}

void destroy_list(CIRCULARLIST* list){

  //if the list is empty.
  if (list->head == NULL){
    free(list);       //we free list and return to avoid segmentation fault when making temp points
    return;           //to next of head which is NULL and in Circular list we do not check NULL to stop.
  }
  //else if there are elements in the list.
  //first: we traverse the list and free each node of the list.
  node* current = list->head;
  do{
    node* temp = current->next;
    free(current);
    current = temp;
  } while (current != list->head);

  //then: we free the list space itself.
  free(list);
}
