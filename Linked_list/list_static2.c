/*
   In this program we evolve our
   previous implementaion by introducing
   key sturctural optimizations.
   This program is an intermediate
   stage designed to evolve from
   manual node management to a more
   organized and efficient linked
   list structure.

     **   The List Descriptor    **
   - Instead of managing independent
     nodes, we introduce a "LIST" struct
     to act as a container. This centeralizes
     the "Head", "Tail" and "Size" turning
     the list into a single manageable entity.

     **  The Tail Pointer Optimization  **
   - We added a tail pointer to maintain
     a direct reference to the last node.
   - Benefits: This eleminates the need to
     traverse the list for appending element
     at the end of the list. This reduces
     the time complexity from O(n) to be
     constant time O(1) regardless of number
     of elements in the list.

     **    The Modular Approach    **
   - Instead of writing all the logic inside
     the main function, we divided the tasks
     into separate, reusable functions.
   - Benefits: This makes the code cleaner,
     easier to read and improves reusability
     and prevents redundancy and repeating
     the same logic multiple times.
     */

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* next;
} node;

typedef struct{
    node* head;
    node* tail;       //this pointer to make the appending process O(1).
    int size;         //this variable to keep track of the current number of elements in the list.
} LIST;

LIST* init_list();                 //this function to initialize a new list.
node* create_node(int data);     //this functions takes data and encapsulates it into a new node.
void append_node(LIST* list, node* ptr); //this function to append a node at the end of the list.
void prepend_node(LIST* list, node* ptr); //this function to prepend a node at the start of the list.
void insert_at(LIST* list,int place, node* ptr);  //this function to insert a node at specific place.
void delete_last(LIST* list);      //this function to delete last node of the list.
void delete_first(LIST* list);     //this function to delete the first node of the list.
void delete_at(LIST* list, int place);   //this function to delete element at specific place from list.
void display_list(LIST* list);    //this function to print all elements of the list.
void free_list(LIST* list);       //this function to free all nodes of the list to avoid memory leak.


int main(void){

    //the array of all numbers we will store in the list.
    int numbers[] = {72, 73, 32, 84, 45, 63, 16, 86, 36, 27, 24, 79, 43, 65, 23, 54, 56, 76, 75, 12};

    //make a new list with init_list function.
    LIST* my_list = init_list();   //we will pass the list by reference to modify the original list.
    if (my_list == NULL){
      return 1;           //if init fails to allocate memory and returned null we exit the program.
    }

    //create five nodes and append and append them to the list O(1).
    for (int i = 0; i < 5; i++){
      node* ptr = create_node(numbers[i + 10]);   //append last five elements in array.
      if (ptr == NULL){
        free_list(my_list);     //if we fail to allocate space for the new node we free all memory allocated
        return 1;                               //to avoid memory leak then return.
      }
      append_node(my_list, ptr);
    }

    //print all elements of the list traverse: O(n), print O(1).
    printf("\nList after appending five elements:\n");
    display_list(my_list);

    //create five nodes and insert them in different place travers: O(n), insert: O(1).
    //array of places we will append at (last, first, out of bound, place 2, place 5).
    int insert_places[] = {my_list->size, 0, my_list->size + 4, 2, 5};
    for (int i = 0; i < 5; i++){
      node* ptr = create_node(numbers[i + 5]);
      if (ptr == NULL){
        free_list(my_list);     //if we fail to allocate space for the new node we free memory allocated
        return 1;                             //to avoid memory leak then return.
      }
      insert_at(my_list, insert_places[i], ptr);
    }

    //print all elements of the list traverse: O(n), print O(1).
    printf("\nList after inserting five elements in different places:\n");
    display_list(my_list);

    //create five new nodes and prepend them into list O(1).
    for (int i = 0; i < 5; i++){
      node* ptr = create_node(numbers[i]);
      if (ptr == NULL){
        free_list(my_list);     //if we fail to allocate space for the new node we free memory allocated
        return 1;                             //to avoid memory leak then return.
      }
      prepend_node(my_list, ptr);
    }

    //print all elements of the list traverse: O(n), print O(1).
    printf("\nList after prepending five elements:\n");
    display_list(my_list);

    //delete three elements from the end of the list traverse: O(n), deletion: O(1).
    for (int i = 0; i < 3; i++){
      delete_last(my_list);
    }

    //print all elements of the list traverse: O(n), print O(1).
    printf("\nList after deleting three elements from the end of list:\n");
    display_list(my_list);

    //delete five elements from five different places traverse: O(n), deletion: O(1).
    //array of places we will delete from (last, place 7, place 3, out of bound, first).
    int delete_places[] = {my_list->size - 1, 7, 3, my_list->size + 3, 0};
    for (int i = 0; i < 5; i++){
      delete_at(my_list, delete_places[i]);
    }

    //print all elements of the list traverse: O(n), print O(1).
    printf("\nList after deleting five elements from different places:\n");
    display_list(my_list);

    //delete three elements from the start of the list O(1).
    for (int i = 0; i < 3; i++){
      delete_first(my_list);
    }

    //print all elements of the list traverse: O(n), print O(1).
    printf("\nList after deleting three elements from the start of the list:\n");
    display_list(my_list);

    //freeing all nodes and the list space we allocated to avoid memory leak.
    free_list(my_list);

    return 0;
}

LIST* init_list(){

  LIST* new_list = malloc(sizeof(LIST));    //we allocate space for the list by malloc and if it
  if (new_list == NULL){                          //failed we return NULL to the main.
      return NULL;
  }
  new_list->head = NULL;                //assign NULL to the head and tail pointers initially
  new_list->tail = NULL;                //and set size to zero as the list is empty.
  new_list->size = 0;

  return new_list;
}

node* create_node(int data){

  node* ptr = malloc(sizeof(node));   //we allocate space for the node with malloc and if it failed
  if (ptr == NULL){                              //we return NULL to the main.
    return NULL;
  }
  ptr->data = data;       //assign data to the new node and assign NULL to the pointer initially.
  ptr->next = NULL;

  return ptr;
}

void append_node(LIST* list, node* ptr){

  //if the list is empty.
  if (list->tail == NULL){
      list->head = list->tail = ptr;    //make head and tail point to the new and only node.
      list->size++;                     //we increase the size of the list by one.
  }else{        //if there are elements in the list.
    list->tail->next = ptr;           //first we make the last node points to the new node then
    list->tail = list->tail->next;          //we update the tail to point to the new node.
    list->size++;               //increase the size by one.
  }
}

void prepend_node(LIST* list, node* ptr){

  //if the list is empty.
  if (list->head == NULL){
    list->head = list->tail = ptr;    //we make head and tail point to the new and only node.
    list->size++;                       //increase the size by one.
  }else{        //if there are elements in the list.
    ptr->next = list->head;         //first we make new node points to the first node of the list
    list->head = ptr;               //then we update the head to point to the new node.
    list->size++;                   //increase the size by one.
  }
}

void insert_at(LIST* list,int place, node* ptr){

  if (place == 0){    //if the place is zero we call prepend function to add element at the start.
    prepend_node(list, ptr);
  }else if (place == list->size){  //if the place equal size we call append to add element at last.
    append_node(list, ptr);
  }else if ( place > list->size){ //if place is greater than size we cannot insert here so we skip it.
    printf("\nInsertion Warning: cannot insert at index %i! Total size of list is %i!\n",place, list->size);
    printf("Operation skipped\n");
    free(ptr);            //we free the node as we will not link it to avoid memory leak.
  } else{                     //if place is valid index we insert it.
    //travers until reaching the previous node to place.
    int i = 0;      //we make a counter to track the current place.
    for (node* current = list->head; current != NULL; current = current-> next){
      if (place == i + 1){           //when reaching the previoys node to place we make new node
        ptr->next = current->next;  //point to the next node to current node then update the
        current->next = ptr;        //current node to point to new node and increase size by one.
        list->size++;
      }
      i++;      //every cycle we increase counter to keep track of current index.
    }
  }
}

void delete_last(LIST* list){

  //if the list is empty.
  if (list->head == NULL){
    printf("Deletion skipped! The list is empty!\n");
  }else if (list->head == list->tail){    //if there is only one node in the list
    free(list->tail);                     //we free the node and update head and tail to NULL,
    list->head = list->tail = NULL;       //then we decrease size by one (to zero).
    list->size--;
  }
  else{
    /*we traverse until reaching the previous node to last to update tail as we are retstricted with
      one-way traversal in singly linked list, we cannot access the previous node to last directly.*/
    for (node* current = list->head; current != NULL; current = current->next){
      //when reaching previous node to last.
      if (current->next == list->tail){
        free(list->tail);         //free the last node memory to avoid memory leak.
        list->tail = current;     //update last pointer to the previous node.
        current->next = NULL;     //and make the new last points to NULL.
        list->size--;             //decrease the list size by one.
      }
    }
  }
}

void delete_first(LIST* list){

  //if the list is empty.
  if (list->head == NULL){
    printf("Deletion skipped! The list is empty!\n");
  }else if (list->head == list->tail){    //if there is only one node in the list
    free(list->head);                     //we free the node and update head and tail to NULL,
    list->head = list->tail = NULL;       //then we decrease size by one (to zero).
    list->size--;
  }
  else{
    node* temp = list->head;            //first we save a temporary pointer to the first node.
    list->head = list->head->next;      //then update head to the next node.
    free(temp);                         //then free the first node to avoid memory leak.
    list->size--;                       //finally we decrease the list size by one.
  }
}

void delete_at(LIST* list, int place){

  //if the place was the first node we call delete_first function.
  if (place == 0){
    delete_first(list);
  }else if (place == (list->size - 1)){   //if place was the last node we call delete_last function.
    delete_last(list);
  }else if (place >= list->size){   //if place was out of range of the list size.
    printf("\nDeletion skipped! There is no elements in place %i! Total size is %i\n",place, list->size);
  }else{                    //if the place is valid.
    //traverse until reaching the previous node to the node we want to delete.
    int i = 0;    //counter to know the current place.
    for (node* current = list->head; current != NULL; current = current->next){
      if (place == i + 1){             //when reaching the previous node to target.
        node* temp = current->next;     //save a temporary pointer to the target node.
        current->next = current->next->next; //update pointer of current to point to equal the pointer
        free(temp);                       //of the target node then free target to avoid memory leak.
        list->size--;             //decrease the list size by one.
      }
      i++;      //every cycle we increase the counter to keep track of current index.
    }
  }
}

void display_list(LIST* list){

  //if the list is empty.
  if (list->size == 0){
    printf("The list is empty!\n");
    return;
  }else{
    int i = 0;                  //counter to track number of index.
    //traverse the list and print data and the address of each node.
    for (node* current = list->head; current != NULL; current = current->next){
      printf("Element at place %i: %i,   stored in address: %p,   next pointer: %p\n",i, current->data, current, current->next);
     // printf(" next pointer of this node: %p\n", current->next);
      i++;
    }
  }
}

void free_list(LIST* list){

  //First: travers the list and free nodes one by one.
  node* current = list->head;
  while (current != NULL){   //we should use while loop to control steps inside the body of the loop.
    node* temp = current->next;
    free(current);       //we cannot increment current until freeing the node first
    current = temp;      //if we increment current first we will start a new cycle.
  }
  //Now, after freeing all nodes we free the list struct memory we have allocated.
  free(list);
}
