/*
   in this program we implement
   a "Doubly Linked List".
   This is an advanced data structure
   that organizes data in a "Bidirectional Chain",
   allowing movement in both directions
   (Forward and Backword) smoothly.

      **   Features of Doubly List    **
   - Flexible Traversal: Every node contains
     two pointers (next & prev) for two-way
     traversal.
   - Faster Tail updates: Unlike singly list,
     updating the Tail after insertion or deletion
     does not require traversing, as we can access
     previous node directly so it becomes O(1).
   - Dual Connectivity: Each node is secured by
     two distinct links, making the structure
     stable and reliable.
   - Clear Termination: It starts at Head and
     ends at Tail where ends point to NULL,
     making termination logic simple and effective.

      **   Advantages of Doubly List   **
   - Two-Way Traversal: Fast movement between
     nodes in two directions which makes it easier
     to access the previous node without need for
     full cycle O(1).
   - High Accessibility: Any node can be accessed
     from either direction, optimizing search efficiency
     and make it easier to access every node from any
     starting point without need to reset pointer to head.
   - Fast Insertion and Deletion: Removing a specific
     node becomes much easier as we do not need to find
     the previous node, we need only the node itself.
   - Fault Tolerant: If one pointer fails, the other
     can be used to reconstruct or trace the path.

      **   Disadvantages of Doubly List   **
   - Memory Overhead: Each node consumes more RAM
     as it contains two pointers and each pointer
     requires "8 Bytes" of storage.
   - Complex Pointer Logic: Operations require precise
     updates of multiple links to maintian the integrety
     of the chain.
   - High Sensitivity: A single error in any pointer
     can break the bidirectional flow, leading to
     logic bugs that are harder to debug than singly list.

      **         Structural Goal          **
   - To build a "High-Connective System" where nodes
     are interconnected, ensuring maximum flexibility
     and high-speed access and modifications at any
     point in the list.
   */

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
                             //each node has three components:
  int data;                   //the data stored in the node.
  struct node* next;          //pointer to the following node.
  struct node* prev;          //pointer to the previous node.
} node;

typedef struct{

  node* head;
  node* tail;
  int size;
} DOUBLYLIST;              //this contains all basic DOUBLYLIST variables.

//input functions.
int get_int(char* request);                  //this functions to get integer number from user.
int get_positive_int(char* request);        //this function to get positive integer number from user.

//DOUBLYLIST functions.
DOUBLYLIST* init_doublylist();              //this function to allocate a new DOUBLYLIST and initialize it.
node* create_node(int value);                    //this function to create a new node for a given value.
void append(DOUBLYLIST* list, node* ptr);          //this function to append a new node to the list.
void prepend(DOUBLYLIST* list, node* ptr);         //this function to prepend a new node to the list.
void insert_at(DOUBLYLIST* list, node* ptr, int place); //this function to insert a new node at specific place.
void delete_first(DOUBLYLIST* list);               //this function to delete the first node from the list.
void delete_last(DOUBLYLIST* list);                //this function to delete tha last node from the list.
void delete_at(DOUBLYLIST* list, int place);      //this function to delete a node from specific place at list.
void update_first(DOUBLYLIST* list, int new_value);     //this function to update value of the first element.
void update_last(DOUBLYLIST* list, int new_value);      //this function to update value of the last element.
void update_at(DOUBLYLIST* list, int place, int new_value); //this function to update element at specific place.
void search_for(DOUBLYLIST* list, int target);    //this function to search for specific element and get its place.
void delete_by_value(DOUBLYLIST* list, int target);  //this function to delete specific element with its value.
void update_by_value(DOUBLYLIST* list, int target, int new_value); //this function update element by its value.
void reverse_list(DOUBLYLIST* list);              //this function to reverse the order of the entire list.
void display_forward(DOUBLYLIST* list);       //this function to display elements in the list from head to tail.
void display_backward(DOUBLYLIST* list);      //this function to display elements in the list from tail to head.
void check_doublylist(DOUBLYLIST* list);      //this function to ensure that we can traverse in two directions.
void display_templete();                    //this function to display codes of all valid operations on the list.
void destroy_list(DOUBLYLIST* list);       //this function to free all memory allocated to the list and nodes.


int main(void){

  //build a new doubly list.
  DOUBLYLIST* my_list = init_doublylist();
  if (my_list == NULL){            //if init function fail to allocate space for list we return.
    return 1;
  }
  //welcome the user and tell him about the system.
  printf("\nWelcome to Doubly List management system.\n\n");
  display_templete();

  //ask the user for code of operation he want to perform until exit the system.
  int input;
  do{
    //take user input.
    input = get_int("\nEnter the code of operation you want to perform: ");
    //check the code and perform desired operation.
    //Prepending process.
    if (input == 1){        //ask the user for number of elements he want to prepend.
      int times = get_int("Enter number of elements you want to prepend: ");
      for (int i = 0; i < times; i++){    //iterate number of times to take elements then prepend them.
        int value = get_int("Enter element you want to prepend: ");
        node* ptr = create_node(value);     //create a node for the new element.
        if (ptr == NULL){
          destroy_list(my_list);    //if we fail to allocate space for the node we free all memory allocated
          return 1;                                //to avoid memory leak then return.
        }
        prepend(my_list, ptr);    //then we prepend node to the list with prepend function.
      }
    } //Appending process.
    else if (input == 2){         //ask the user for number of elements he want to append.
      int times = get_int("Enter number of elements you want to append: ");
      for (int i = 0; i < times; i++){  //iterate number of times to take elements from user.
        int value = get_int("Enter element you want to append: ");
        node* ptr = create_node(value);     //create node for the element.
        if (ptr == NULL){
          destroy_list(my_list);    //if we fail to allocate space for the node we free all memory allocated
          return 1;                                   //to avoid memory leak then return.
        }
        append(my_list, ptr);     //then we append the node for the list with append function.
      }
    }  //Insertion process.
    else if (input == 3){     //we insert one element only at a time as indicies change after each insertion.
      int value = get_int("Enter element you want to insert: ");
      int place = get_positive_int("Enter index (start from 0) you want to insert at: ");
      node* ptr = create_node(value);       //create node for the new element.
      if (ptr == NULL){
        destroy_list(my_list);    //if we fail to allocate space for the element we free all memory allocated
        return 1;                                     //to avoid memory leak then return.
      }
      insert_at(my_list, ptr, place);     //then insert the node in the list with insretion function.
    } //Deleting first element process.
    else if (input == 4){         //ask the user for number of elements he want to delete.
      int times = get_int("Enter number of elements you want to delete from the start: ");
      for (int i = 0; i < times; i++){
        delete_first(my_list);      //call delete function number of times to delete elements.
      }
    } //Deleting last element process.
    else if (input == 5){         //ask the user for number of elements he want to delete.
      int times = get_int("Enter number of elements you want to delete from the end: ");
      for (int i = 0; i < times; i++){
        delete_last(my_list);       //call delete function number of times to delete elements.
      }
    } //Deleting by place process.
    else if (input == 6){       //we delete only one element at a time as indicies change after each deletion.
      int place = get_positive_int("Enter index (start from 0) of element you want to delete: ");
      delete_at(my_list, place);    //delete element with deletion function.
    } //Updating first element process.
    else if (input == 7){
      int new_value = get_int("Enter new value you want to update first element with: ");
      update_first(my_list, new_value);   //call update function to update element.
    } //Updating last element process.
    else if (input == 8){
      int new_value = get_int("Enter new value you want to update last element with: ");
      update_last(my_list, new_value);    //call update function to update element.
    } //Updating element by place process.
    else if (input == 9){           //ask the user for number of elements he want to update.
      int times = get_int("Enter number of elements you want to update its value: ");
      for (int i = 0; i < times; i++){     //take place of elements we want to update and the new value.
        int place = get_positive_int("Enter index (start from 0) of element you want to update: ");
        int new_value = get_int("Enter new value you want to update element with: ");
        update_at(my_list, place, new_value);   //update desired element with update function.
      }
    } //Searching process.
    else if (input == 10){           //ask the user for number of elements he want to search for.
      int times = get_int("Enter number of elements you want to search for: ");
      for (int i = 0; i < times; i++){  //iterate number of times to ask user for values he want to search for.
        int value = get_int("Enter element you want to search for its place: ");
        search_for(my_list, value);     //search for element with search function.
      }
    } //Deleting by value process.
    else if (input == 11){          //ask the user for number of elements he want to delete.
      int times = get_int("Enter number of elements you want to delete: ");
      for (int i = 0; i < times; i++){      //iterate number of times to take values of elements.
        int value = get_int("Enter value of element you want to delete: ");
        delete_by_value(my_list, value);      //delete elements with deletion function.
      }
    } //Updating by value process.
    else if (input == 12){           //ask the user for number of elements he want to update.
      int times = get_int("Enter number of elements you want to update its value: ");
      for (int i = 0; i < times; i++){    //iterate number of times to take values and update elements.
        int value = get_int("Enter current value of element you want to update its value: ");
        int new_value = get_int("Enter value you want to update element with: ");
        update_by_value(my_list, value, new_value);   //update element with updating function.
      } //Display forward process.
    }
    else if (input == 13){
      display_forward(my_list);     //display list elements by display forward function.
    } //Display backward process.
    else if (input == 14){
      display_backward(my_list);    //display list elements by display backward function.
    } //Checking list feature process.
    else if (input == 15){
      check_doublylist(my_list);    //checking doubly list with checking function.
    } //Reversing process.
    else if (input == 16){
      reverse_list(my_list);        //reverse the list order with reverse function.
    } //Display templete process.
    else if (input == 17){
      display_templete();           //display operations templete with display function.
    } //Exit process.
    else if (input == 18){
      printf("Exit the system.\n");
    }else{  //Invalid input.
      printf("Invalid input! Enter 17 to check operations templete.\n");
    }
  }while (input != 18);     //we iterate to take code of operation until user exit the system with code (18).

  destroy_list(my_list);    //at the end, we free all memory we have allocated to avoid memory leak.
  return 0;
}

int get_int(char* request){

  int data;             //variable to the data we will take from user.
  int status;           //variable to check the return value of scanf function.
  do{
    printf("%s", request);      //print the request to ask the user for input.
    status = scanf("%i", &data);   //we must pass the address of our variable to save input to it.
    while(getchar() != '\n');   //this loop to clear garbage input or '\n' from buffer.
  } while (status == 0);     //we iterate until scanf gets a correct input as it return zero in case of failure.

  return data;
}

int get_positive_int(char* request){

  int data;         //this variable to store the user input.
  do{
    data = get_int(request);    //we call get_int function until it returns positive (>= 0) value.
  } while(data < 0);

  return data;
}

DOUBLYLIST* init_doublylist(){

  DOUBLYLIST* list = malloc(sizeof(DOUBLYLIST));
  if (list == NULL){        //if malloc fails to allocate space for the list we return NULL.
    return NULL;
  }
  list->head = NULL;        //otherwise, we initialize list variables.
  list->tail = NULL;
  list->size = 0;

  return list;
}

node* create_node(int value){

  node* ptr = malloc(sizeof(node));
  if (ptr == NULL){         //if malloc fails to allocate space for the node we return NULL.
    return NULL;
  }
  ptr->data = value;        //otherwise, we initialize node variables.
  ptr->next = NULL;
  ptr->prev = NULL;

  return ptr;
}

void append(DOUBLYLIST* list, node* ptr){
  //if the list is empty:
  if (list->head == NULL){
    list->head = list->tail = ptr;        //make head and tail point to new and only node.
    list->size++;
  }else{  //if there are stored elments already.
    list->tail->next = ptr;                 //make last node (next) points to new node.
    ptr->prev = list->tail;                 //make the new node (prev) points to last node of list.
    list->tail = list->tail->next;          //update tail to point to new node.
    list->size++;
  }
  printf("Element appended successfully\n");
}

void prepend(DOUBLYLIST* list, node* ptr){
  //if the list is empty:
  if (list->head == NULL){
    list->head = list->tail = ptr;        //make head and tail point to new and only node.
    list->size++;
  }else{    //if the list has stored elements already.
    ptr->next = list->head;               //make new node (next) point to head of the list.
    list->head->prev = ptr;               //make head node (prev) point to new node.
    list->head = ptr;                     //update head to point to new node.
    list->size++;
  }
  printf("Element prepended successfully\n");
}

void insert_at(DOUBLYLIST* list, node* ptr, int place){
  //if the place is beyond the size of list.
  if (place > list->size){
    printf("We can not insert at place %i! Total size of the list is %i!\n", place, list->size);
    printf("Operation skipped\n");
    free(ptr);   //we free the node as we will lose its pointer if we do not add it to list to avoid memory leak.
  }else if (place == 0){
    prepend(list, ptr);        //if place is index zero we call prepend function to prepend the node.
  }else if (place == list->size){
    append(list, ptr);          //if place is equal to list size we call append function to append it.
  }else{          //if place is index in the middle of list.
    int index = 0;    //this variable to track the current index.
    for (node* current = list->head; current != NULL; current = current->next){
      //if we reach the place we want to insert at:
      if (place == index){                              //set new node pointers:
        ptr->prev = current->prev;              //make new node (prev) points to prev of current node.
        ptr->next = current;                    //make new node (next) points to current node.
        current->prev->next = ptr;              //then, make previous node of current points next to new node.
        current->prev = ptr;                    //and finnaly make current node (prev) points to new node.
        list->size++;
        printf("Element inserted successfully at index %i\n", place);
        break;      //after insertion we break the loop to save processing time.
      }
      index++;    //increase index to track current place.
    }
  }
}

void delete_first(DOUBLYLIST* list){
  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! There is No elements to delete!\n");
    return;
  }else if (list->head == list->tail){    //if there is only one node at the list:
    free(list->head);                     //we free it then make head and tail point to NULL.
    list->head = list->tail = NULL;
    list->size--;
  }else{  //if the list has stored elements:
    node* tmp = list->head;           //store the place of head in temporary variable.
    list->head = list->head->next;    //updata head to points to the next node.
    list->head->prev = NULL;          //make new head node (prev) points to NULL.
    free(tmp);                        //free the old head node with temporary variable.
    list->size--;
  }
  printf("Element deleted successfully\n");
}

void delete_last(DOUBLYLIST* list){
  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! There is No elements to delete!\n");
    return;
  }else if (list->head == list->tail){    //if there is only one element in the list.
    free(list->tail);                     //free it then update head and tail to point to NULL.
    list->head = list->tail = NULL;
    list->size--;
  }else{            //else if the list has stored elements.
    list->tail = list->tail->prev;      //make list tail points to the previous of current tail.
    free(list->tail->next);             //free the old tail with next pointer of current tail.
    list->tail->next = NULL;            //update next pointer of current tail to point to NULL.
    list->size--;
  }
  printf("Element deleted successfully\n");
}

void delete_at(DOUBLYLIST* list, int place){
  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! There is No elements to delete!\n");
  }else if (place >= list->size){   //else if place is bigger than or equal size.
    printf("There is no elements in this place to delete!\n");
  }else if (place == 0){            //if place is index zero we call delete first function to delete it.
    delete_first(list);
  }else if (place == list->size - 1){   //if place is the last index in the list we call delete last function.
    delete_last(list);
  }else{              //if the index is in the middle of the list.
    int index = 0;        //this variable to track the current index.
    for (node* current = list->head; current != NULL; current = current->next){
      //if we reach the element we want to delete.
      if (place == index){
        current->prev->next = current->next;    //make previous node points (next) to the next node of current.
        current->next->prev = current->prev;    //make next node of current points (prev) to previous of current.
        free(current);                          //then, free current node which is the target.
        list->size--;
        printf("Element deleted successfully\n");
        break;        //after deletion we break the loop to save processing time.
      }
      index++;            //increase index to track current place.
    }
  }
}

void update_first(DOUBLYLIST* list, int new_value){
  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! There is No elements to update!\n");
  }else{    //else, if the list has stored elements.
    list->head->data = new_value;             //we update first element directly with head pointer.
    printf("Element updated successfully\n");
  }
}

void update_last(DOUBLYLIST* list, int new_value){
  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! There is No elements to update!\n");
  }else{    //else, if there are elements stored in the list.
    list->tail->data = new_value;             //we update last element directly with tail pointer.
    printf("Element updated sucessfully\n");
  }
}

void update_at(DOUBLYLIST* list, int place, int new_value){
  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! There is No elements to update!\n");
  }else if (place >= list->size){               //if place is bigger than or equal size.
    printf("There is No elements in this place to update!\n");
  }else if (place == list->size - 1){  //if place was the last element we call update last to access it directly.
    update_last(list, new_value);
  }else{            //else if place was in the middle of list.
    int index = 0;    //we set a counter to track the current index.
    for (node* current = list->head; current != NULL; current = current->next){
      if (place == index){              //if we reach to element we update it to new_value then break loop.
        current->data = new_value;
        break;
      }
      index++;      //we increase the counter at every iteration to keep tracking current index.
    }
    printf("Element updated successfully.\n");
  }
}

void search_for(DOUBLYLIST* list, int target){
  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! There is No elements to search!\n");
    return;
  }else{      //else, if the list has stored elements.
    int index = 0;        //set a counter to track the current index.
    for (node* current = list->head; current != NULL; current = current->next){
      if (current->data == target){
        printf("Element found at index %i\n", index);
        return;
      }
      index++;      //we increase counter at every iteration to keep tracking current index.
    }
    printf("Element Not found in the list\n");
  }
}
/*#NOTE: we could user search function to get index, then call delete_at function with the index, But this
         would require traversing multiple times: one for searching and the other for actual deletion.
         So, we will build new function that find element and delete it at the same traverse to save time.*/
void delete_by_value(DOUBLYLIST* list, int target){
  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! There is No elements to delete!\n");
  }else if (target == list->head->data){    //if the target is the head of the list we call delete_first function,
    delete_first(list);                     //as it is a special case that require updating head pointer.
  }else if (target == list->tail->data){    //if the target is the tail of the list we call delete_last function,
    delete_last(list);                      //as it is a special case that require updating tail pointer.
  }else{          //if element was at the middle of list or it does not exist in the list.
    for (node* current = list->head; current != NULL; current = current->next){
      if (current->data == target){         //if we reach the target element.
        current->prev->next = current->next; //make previous node to current points (next) to next node of current.
        current->next->prev = current->prev; //make the next node to current points (prev) to previous of current.
        free(current);                        //then, free the current node which is the target.
        list->size--;
        printf("ELement deleted successfully in efficient way to save time.\n");
        return;
      }
    }
    printf("Element Not Found in the list!\n");    //if the loop ended without founding the element and delete it,
  }                                               //then the element does not exist in the list.
}

/*NOTE: we could use search function to find index then call update_at index to update value at that index,
  But this would require traverse two times: one for searching and the other for actual updating value.*/
void update_by_value(DOUBLYLIST* list, int target, int new_value){
  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! There is No elements to update!\n");
    return;
  }else{  //else, if there are stored elements in the list.
    for (node* current = list->head; current != NULL; current = current->next){
      //if we find element we update it then return.
      if (current->data == target){
        current->data = new_value;
        printf("Element updated successfully in efficient way to save time.\n");
        return;
      }
    }
    printf("Element Not Found in the list!\n");        //if the loop ended without finding element
  }                                                            // then it is not in list.
}

void reverse_list(DOUBLYLIST* list){
  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! Add some elements first to reverse list.\n");
  }else{    //else, if the list has stored elements.
    //first: we iterate and swap the (next, prev) pointers of each node to reverse order of nodes.
    node* current = list->head;         //we use while loop to update current correctly.
    while (current != NULL){
      node* temp = current->next;             //save value of next pointer in temporary variable.
      current->next = current->prev;          //make next pointer equal to prev pointer.
      current->prev = temp;                   //then, make prev pointer equal temp (old next value)
      current = temp;             //when updating current we use temp as it stores address of next node.
    }
    //then: swap the (head, tail) pointers of the list.
    node* temp = list->head;                //store the value of head in temporary variable.
    list->head = list->tail;                //make head pointer equal to tail pointer.
    list->tail = temp;                      //then make tail pointer equal to tmep.
    printf("The list reversed successfully.\n");
  }
}

void display_forward(DOUBLYLIST* list){
  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! There is No elements to display!\n");
  }else{    //else if the list has stored elements.
    printf("All elements of the list from start to end:\n");
    int index = 0;          //we make this counter to track current place.
    for (node* current = list->head; current != NULL; current = current->next){
      printf("Element at index %i: %i\n", index, current->data);
      index++;    //at every iteration we increase the counter to track current index.
    }
  }
}

void display_backward(DOUBLYLIST* list){
  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty! There is No elements to display!\n");
  }else{    //else, if the list has stored elements.
    printf("All elements of the list from end to start:\n");
    int index = list->size - 1;   //we start from the last index at the list.
    for (node* current = list->tail; current != NULL; current = current->prev){
      printf("Element at index %i: %i\n", index, current->data);
      index--;     //at every iteration we decrease the counter as we move from end to start.
    }
  }
}

void check_doublylist(DOUBLYLIST* list){
  //if the list is empty or has one element.
  if (list->head == NULL || list->head == list->tail){
    printf("The list is empty or has one element! \nYou should add more elements to check doubly list features.\n");
  }else{    //else if the list has more elements.
    printf("The main feature of doubly list is that we can traverse in both sides forward and backward.\n");
    printf("In the forward traverse:\n");
    display_forward(list);
    printf("\nIn the backward traverse:\n");
    display_backward(list);
  }
}

void display_templete(){
  //print codes of valid operations on the doubly list.
  printf("These are the codes of valid operaions on the Doubly List:\n");
  printf("1.Add elements at first.        2.Add elements at the end.       3.Add element at specific place.\n");
  printf("4.Delete first element.         5.Delete last element.           6.Delete element from specific place.\n");
  printf("7.Update first element.         8.Update last element.           9.Update element at specific place.\n");
  printf("10.search for specific element. 11.Delete element by its value.  12.Update element by its value.\n");
  printf("13.Display list in forward way. 14.Display list in backward way. 15.Check Doubly list features.\n");
  printf("16.reverse order of the list.   17.Display operations templete.  18.Exit the Doubly list system.\n");
}

void destroy_list(DOUBLYLIST* list){

  //first: we iterate and free each node in the list.
  node* current = list->head;
  while (current != NULL){          //Order of steps is very important:
    node* temp = current->next;     //store the address of the next node in temporary variable.
    free(current);                  //then, free current node.
    current = temp;                 //finally we update current to equal temp which is the address of next node.
  }
  //then: we free the memory allocated to list variables itself.
  free(list);
}
