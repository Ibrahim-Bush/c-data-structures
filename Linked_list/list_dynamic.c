/*
   in this program we evolve our Linked
   List from a simple storage container
   into an intelligent dynamic system.
   This stage is designed to shift the
   responsibility of organization from
   the user to the program itself.

   **   User Interaction Principle  **
   - The user will just provide the data
     and do not care about ordering, and
     instead of manually choosing where
     to insert (Head, Tail, Index), The
     program insert it in it's correct place
     to keep the list ordered all the time.
   - Every element the user adds will be
     insereted in order to the list.

     **   The Automatic Ordering  **
   - The program automatically handles
     the mathematical positioning without
     any manual index or position input.
   - The program identifies the correct
     place of new element by comparing
     its value as following:
     1. if the list is empty: just insert
        at the first of the list.
     2. if value < Head: it automatically
        becomes the new head.
     3. if value > tail: it automatically
        becomes the new tail.
     4. if value is in-between: The program
        traverses to find the exact mathimatical
        position to mantian ascending order.

       **   The Search Efficiency   **
   - Even though the list is perfectly sorted,
     searching still requires a linear time
     complexity O(n).
   - Unlike Arrays, Linked Lists do not support
     "Random Access", meaning we cannot jump
     to the middle element instantly
     (Binary search is not applicable).
   - To find any value, the program must start
     from the Head and traverse element by element
     until the target is found or the end of the
     list is reached making the search operation
     has Big O(n).

     **   The Optimized Linear Search   **
   - Since the list is always maintained in
     a sorted state, we can implement an
     optimized linear search algorithm that
     makes use of the list's sorting by
     implementing an "early exit" condition
     to save processing time.
   - The search stops immediately if the current
     value becomes greater than the target.
   - This optimization avoids checking the rest
     of the list because all following elements
     are guaranteed to be larger and will not
     match the target value.
   - However, the time complexity remains O(n)
     in the worst case if the target is the tail
     or a value larger than tail.

       **    Structural Goal     **
   - This program is designed to ensure
     the list remains sorted at all times
     keeping our head, tail and size perfectly
     updated after every intelligent deciscion.
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
} LIST;

LIST* init_list();                           //this function to initialize a new list.
node* create_node(int element);             //this function to create a new node with given data.
int get_int(char* request);                 //this funciton to get an integer number from the user.
void insert_in_order(LIST* list, node* ptr);   //this is the inelligent function that insert
                                          //the element in its correct order to keep the list sorted.
void search_by_value(LIST* list, int value);  //this function use linear search to find element with value.
void delete_node(LIST* list, int value);      //this function delete specific node by its value.
void display_list(LIST* list);               //this function to display all elements of the list.
void destroy_list(LIST* list);               //this function to free all the list to avoid memory leak.

int main(void){

  //initialize a list with init_list function.
  LIST* my_list = init_list();
  if (my_list == NULL){
    return 1;
  }
  //inform the user about code of available operations to perform.
  printf("\nWe have sorted linked list management system\n");
  printf("Which operation you want to perform:  1. Add new elements,   2. Search for specific elements\n");
  printf("3. Delete specific elements,  4. Display all the list,   5. Display current size,   6.Exit\n");
  int answer;
  do {
    //ask the user for the code of operation he want to perform.
    answer = get_int("\nEnter the code of operation you want to perform: ");

    //check the input of user to perform the desired operation.
    //adding elements process.
    if (answer == 1){             //take number of elements to iterate n times.
      int number = get_int("Enter the number of new elements you want to add: ");
      for (int i = 0; i < number; i++){   //ask the user for data n times.
        int data = get_int("Enter a number: ");   //take the data.
        node* ptr = create_node(data);            //create a node for it.
        if (ptr == NULL){
          destroy_list(my_list);    //if we fail to allocate space for new node we free all memory allocated
          return 1;                             //to avoid memory leak then return.
        }
        insert_in_order(my_list, ptr);  //pass the list and the new node to smart insertion function.
      }
    }
    //searching process.
    else if (answer == 2){
      int number = get_int("Enter number of elements you want to search for them: ");
      for (int i = 0; i < number; i++){
        int value = get_int("Enter the value of element you want to search for: ");
        search_by_value(my_list, value);
      }
    }
    //deletion process.
    else if (answer == 3){
      int number = get_int("Enter number of elements you want to delete: ");
      for (int i = 0; i < number; i++){
        int value = get_int("Enter value of the element you want to delete: ");
        delete_node(my_list, value);
      }
    }
    //Display elements.
    else if (answer == 4){
      display_list(my_list);
    }
    //Display size of list.
    else if (answer == 5){
      printf("The number of current elements in the list is %i\n", my_list->size);
    }
    //exit process.
    else if (answer == 6){
      printf("Exit the system!\n");
    }
    //invalid input.
    else{
      printf("Invalid input! Try again!\n");
    }
  } while (answer != 6);          //iterate until the user enters 6 to exit.

  //free all the memory allocated in the list to avoid memory leak.
  destroy_list(my_list);
  return 0;
}

LIST* init_list(){

  //reserve a space for the list.
  LIST* list = malloc(sizeof(LIST));
  if (list == NULL){
    return NULL;
  }
  //initilialize head and tail with NULL and size with zero.
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;

  return list;
}

node* create_node(int element){

  //reserve a space for the node.
  node* ptr = malloc(sizeof(node));
  if (ptr == NULL){
    return NULL;
  }
  //initialize node data and pointer.
  ptr->data = element;
  ptr->next = NULL;

  return ptr;
}

int get_int(char* request){

  //ask the user for integer number until enters valid input.
  int data;
  int status;
  do{
    printf("%s", request);          //print the request argument to ask the user for input.
    status = scanf("%i", &data);    //scan input with scanf and store it in the place of data.
    while(getchar() != '\n');       //clean the buffer from '\n' or garbage input.
  } while(status == 0);             //if scanf fails it returns zero so we iterate until it sucess.

  return data;
}

void insert_in_order(LIST* list, node* ptr){

  //if the list is empty we just add node at first.
  if (list->head == NULL){
    list->head = list->tail = ptr;
    list->size++;
    printf("Element inserted successfully\n");
  } //if the new element is smaller than or equal the head data it become the new head.
  else if (ptr->data <= list->head->data){
    ptr->next = list->head;
    list->head = ptr;
    list->size++;
    printf("Element prepended successfully\n");
  } //if there is only one node and the new element is larger than it we append at to become new tail.
  else if (list->head == list->tail){
    list->tail->next = ptr;
    list->tail = ptr;
    list->size++;
    printf("Element appended successfully\n");
  }
  //if the new element is in-between values of other element we traverse until reaching correct place.
  else{
    for (node* current = list->head; current != NULL; current = current->next){
      //if the next element is bigger than new one we add the node before it and return.
      if (ptr->data <= current->next->data){
        ptr->next = current->next;    //make new node points to the next node to current.
        current->next = ptr;          //then, make current node points to new node.
        list->size++;
        printf("Element inserted successfully\n");
        return;                         //we return after adding the node.
      }  //if reaching the end of the list then new element is the bigget so, we add the element at the end.
      else if (current-> next == list->tail){
        list->tail->next = ptr;       //make the last node points to new node.
        list->tail = ptr;             //update tail to points to the new node as it becomes the new tail.
        list->size++;
        printf("Element appended successfully\n");
        break;
      }
    }
  }
}

void search_by_value(LIST* list, int value){

  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty!\n");
  }else{  //if there are elements in the list.
    int place = 0;    //set a counter to track the place of each element.
    //start a loop from the head to search for element until the end of list.
    for (node* current = list->head; current != NULL; current = current -> next){
      //compare the value of current node with the target.
      if (current -> data == value){
        printf("Element found in place %i\n", place);
        return;     //we return after founding the element otherwise we will perform wastefull iterations.
      }else if (current->data > value){
        break;       //if value of current element becomes greater than target then it is not in the list.
      }
      place++;      //increase place every iteration to keep track of current element.
    }
    //if the loop ended without finding the element then it is not found.
    printf("Element not found in the list\n");
  }
}

void delete_node(LIST* list, int value){

  //if the list is empty we notify the user then return.
  if (list->head == NULL){
    printf("The list is empty! There is no elements to delete!\n");
    return;
  }
  else if (value == list->head->data){     //if the value is the first node we must update head pointer.
    node* temp = list->head;          //store the address of first node in a temporary pointer.
    if (list->head == list->tail){    //check if it is the only element in the list to update last.
      list->tail = NULL;              //if it is the only element we make tail points to NULL.
    }
    list->head = list->head->next;    //update the head to points to the next node or null.
    free(temp);                       //free the first node by temporary variable.
    list->size--;                     //decrease the list size by one then return.
    printf("Element deleted successfully\n");
    return;
  }else if (list->head == list->tail){     //else if there is only one element in the list and it does not
    printf("Element not found in the list\n");          //the target then it is not found.
    return;
  }
  else{      //else traverse until reaching the previous node to the target.
    for (node* current = list->head; current != NULL; current = current->next){
      if (current->next == list->tail){       //if we reached the previous node to tail we have two cases:
        if (list->tail->data == value){       //1. if the tail is the target (special case).
          free(list->tail);         //free the tail.
          current->next = NULL;     //make current node points to NULL.
          list->tail = current;     //make tail points to current as it becomes the new tail.
          list->size--;             //decreasing size of the list by one.
          printf("Element deleted successfully\n");
          return;                   //return after deleting the element.
        }else{                               //2. if the tail does not equal target then it does not exist.
          printf("Element not found in the list\n");
          return;
        }
      }else if (current->next->data == value){    //otherwise we compare the next node with the target.
            //if the next node is target:
            node* temp = current->next;         //store the address of the target in a temporary pointer.
            current->next = current->next->next; //update the current pointer to points to the next of target.
            free(temp);                         //free the target node by the temporary variable.
            list->size--;                       //decreasing size of the list by one.
            printf("Element deleted successfully\n");
            return;                            //return after deleting element sucessfully.
      }
    }
  }
}

void display_list(LIST* list){

  //if the list is empty.
  if (list->head == NULL){
    printf("The list is empty!\n");
    return;
  }
  //traverse the list and print data of each node.
  int i = 0;    //counter to track the current place.
  printf("All stored elements in the list:\n");
  for (node* current = list->head; current != NULL; current = current->next){
    printf("Element in place %i: %i\n", i, current->data);
    i++;    //increase counter at every step.
  }
}

void destroy_list(LIST* list){

  //free all nodes of the list at first.
  node* current = list->head;
  while (current != NULL){        //Order of steps is important:
    node* temp = current->next;   //store the next pointer in temporary pointer.
    free(current);                //free current node.
    current = temp;               //update current to the next node by temporary variable.
  }
  //now, free the space allocated to the list itself.
  free(list);
}
