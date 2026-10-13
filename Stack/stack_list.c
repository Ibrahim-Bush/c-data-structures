/*
   This program is designed to demonstrate
   the exact behaviour and constraints of
   a Stack data structure.
   This implementation of a Stack is built
   using a Singly linked list foundation.

    **   The Stack (LIFO Structure)   **
   - LIFO Concept:
     The Stack is a linear structure that
     strictly follows the Last In, First Out
     (LIFO) principle. This means that the
     last element you add to the stack will
     be the very first one to be removed.
   - Stack Behaviour:
     The Stack behaves exactly like a physical
     stack of books, where you can only place
     a new item on the top, and you can only
     take an item off from the top. You cannot
     access or modify elements in the middle
     or at the bottom of the stack directly.

    **   The Role of the Top Pointer   **
   - The Top Pointer: This pointer is the only
     entry and exit point for the entire program.
     It always points to the element currently
     sitting at the top of the stack (the newest item).
     Because all additions and removals happen only
     at this single point, operations are highly
     efficient and run in O(1) time complexity.

    **       Core Stack Operations      **
   - Push Operation:
     Inserts a new element at the top of the stack
     and links it to the stack by making its next
     pointer point to the previous top element, then
     updates the Top pointer to point to this new node.
   - Pop Operation:
     Removes the current top element from the stack.
     This operation reads the value of the top node,
     shifts the Top pointer down to the next element,
     and then safely deletes the old top node from
     memory to prevent memory leaks, and returns the
     popped value.

       **          Program Goal          **
   - To build a clean, clear, and optimized program
     that illustrates the logic, behaviour and memory
     management of a LIFO Stack.

       **         Time Complexity        **
   - Push new element at the top of stack:      O(1).
   - Pop the element at the top of the stack:   O(1).
   - Get the value of the current top element:  O(1).
   - Update the value of the top element:       O(1).
   - Display all elements stored in the stack:  O(n).          "Requires traversing to display each element"
   - Reset the stack to the initial state:      O(n).             "Requires traversing to free each node"

   * Stack operations are fast and efficient and usually have O(1).
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node{

    int data;
    struct node* next;
} node;

typedef struct{

    node* top;
    int size;
} STACK;

//input functions.
int get_int(char* request);                    //this function to take an integer number from user.
void display_template();                  //this function to display template of valid operations on the stack.

//Stack functions.
STACK* init_stack();                                  //this function to initialize a new stack.
node* create_node(int value);                   //this function to create a node for the new element.
void push(STACK* stack, node* ptr);             //this function to push a new node into the stack.
int pop(STACK* stack, int* value);      //this function to pop the top element from the stack and get its value.
int peek(STACK* stack, int* value);    //this function to get the value of the top element without deleting it.
int update_top(STACK* stack, int new_value);   //this function to update the value of the current top element.
int is_empty(STACK* stack);                     //this function to check if the stack is empty or not.
int get_size(STACK* stack);           //this function to get the current number of stored elements in the stack.
void display_stack(STACK* stack);       //this function to display all elements in the stack from top to bottom.
void clear_stack(STACK* stack);                  //this function to reset the stack to the initial state.
void destroy_stack(STACK* stack);                //this function to free all memory allocated for stack.

int main(void){
    //initialize a new stack.
    STACK* my_stack = init_stack();
    if (my_stack == NULL){
      return 1;             //if the function fails to allocate space for stack, we exit the program.
    }
    //welcome user and display operations templete.
    printf("\nWelcome to Stack management system.\nThis implementation is built using a Singly Linked List.\n\n");
    display_template();

    //ask the user for the code of desired operation.
    int code;
    do{
      code = get_int("\nEnter the code of the operation you want to perform on the stack: ");
      //check code and perform desired operation.
      //Push process.
      if (code == 1){           //take the value of element from user.
        int value = get_int("Enter value of element you want to push into the stack: ");
        node* ptr = create_node(value);   //create a new node for the element.
        if (ptr == NULL){
          destroy_stack(my_stack); //if the function fails to allocate space for node, we free the stack and exit.
          return 1;
        }
        push(my_stack, ptr);      //push the node into the stack with push function.
        printf("Element pushed to the stack successfully.\n");
      }else if (code == 2){   //pop operation.
        int value;            //make variable to store popped value.
        int status = pop(my_stack, &value);       //pop the top element with pop function.
        if (status == 0){         //if pop function return (0) then the stack is empty.
          printf("The list is empty! There is No elements to delete!\n");
        }else{              //else, the function popped element and put its value in the address of the pointer.
          printf("Element: %i deleted successfully from the top of the stack.\n", value);
        }
      }else if (code == 3){   //peek process.
        int value;            //make variable to store value of the top element.
        int status = peek(my_stack, &value);    //get value of top element with peek function.
        if (status == 0){         //if peek function returns (0) then the stack is empty.
          printf("The stack is empty! There is No elements to display!\n");
        }else{                   //else, the function put the value of top element in the address of the pointer.
          printf("The current top element at the stack is: %i\n", value);
        }
      }else if (code == 4){   //updating process.
        int new_value = get_int("Enter the new value you want to update the top element with: ");
        int status = update_top(my_stack, new_value);  //update top element with update function.
        if (status == 0){   //if the function returns zero then the stack is empty.
          printf("The stack is empty! There is No elements to update!\n");
        }else{              //else, the top element updated successfully.
          printf("The top element updated successfully.\n");
        }
      }else if (code == 5){   //Display size.
        int size = get_size(my_stack);
        if (size == 0){       //if size is zero then the list is empty.
          printf("The list is empty! There is No elements in the list.\n");
        }else{                  //else, display the current size.
          printf("The current number of elements in the stack is: %i\n", size);
        }
      }else if (code == 6){   //Display stack.
        display_stack(my_stack);
      }else if (code == 7){   //Reset stack.
        clear_stack(my_stack);
        printf("The stack reseted successfully to the initial state.\n");
      }else if (code == 8){   //Display operations template.
        display_template();
      }else if (code == 9){   //Exit process.
        printf("Exit the system.\n");
      }else{                  //Invalid input.
        printf("Invalid input! Enter (8) to check operations templete.\n");
      }
    } while (code != 9);        //iterate until user enters exit code (9).

    destroy_stack(my_stack);    //free all memory we have allocated to the stack to avoid memory leaks.
    return 0;
}

int get_int(char* request){

  int status;           //this variable to store the return value of scanf to check it.
  int value;            //this is the value we get from user.
  do{
    printf("%s", request);            //print request to ask user for input.
    status = scanf("%i", &value);     //get the input value with scanf.
    while(getchar() != '\n');         //clear the buffer from garbage value or '\n'
  } while(status == 0);       //iterate until scanf gets a valid input as it returns zero in case of failure.

  return value;
}

STACK* init_stack(){

  STACK* stack = malloc(sizeof(STACK));    //allocate space for the stack with malloc.
  if (stack == NULL){
    return NULL;           //if malloc fails to allocate space for stack it returns NULL.
  }
  stack->top = NULL;        //initialize stack variables.
  stack->size = 0;

  return stack;             //return the pointer for allocated space.
}

node* create_node(int value){

  node* ptr = malloc(sizeof(node));     //allocate space for node with malloc.
  if (ptr == NULL){
    return NULL;        //if malloc fails to allocate space for node it returns NULL.
  }
  ptr->data = value;     //initialize node variables.
  ptr->next = NULL;

  return ptr;             //return the pointer for the node.
}

void push(STACK* stack, node* ptr){
  //if the stack is empty.
  if (is_empty(stack) == 1){
    stack->top = ptr;         //only make the top pointer point to new node.
    stack->size++;
  }else{    //else if stack has stored elements.
    ptr->next = stack->top;     //make new node point to current top element.
    stack->top = ptr;           //then make top pointer point to new node.
    stack->size++;
  }
}

/*NOTE: the function returns (1) if we have popped element and put its value in the address of given pointer,
  else if the stack is empty it returns (0).*/
int pop(STACK* stack, int* value){
  //if the list is empty.
  if (is_empty(stack) == 1){
    return 0;                       //return (0) to tell that the stack is empty.
  }else{  //else if list has stored elements.
    node* temp = stack->top;        //store address of the top in temporary pointer.
    *value = stack->top->data;      //put the value of the top element at the address of given pointer.
    stack->top = stack->top->next;  //make top pointer points to next node.
    free(temp);                     //free old top node with the temporary pointer.
    stack->size--;
    return 1;                       //return (1) to tell that the top element popped successfully.
  }
}

/*NOTE: the function returns (1) if we have put the value of the top element in the address of given pointer,
  else if the stack is empty it returns (0).*/
int peek(STACK* stack, int* value){
  //if the stack is empty.
  if (is_empty(stack) == 1){
    return 0;                         //return (0) to tell that the stack is empty.
  }else{    //else if list has stored elements.
    *value = stack->top->data;        //put the value of the top element at the address of given pointer.
    return 1;                         //return (1) to tell that the value of top element put in given place.
  }
}

int update_top(STACK* stack, int new_value){
  //if the stack is empty.
  if (is_empty(stack) == 1){
    return 0;                           //return (0) to tell that the stack is empty.
  }else{    //else if stack has stored elements.
    stack->top->data = new_value;       //update value of the top element to equal new value.
    return 1;                           //return (1) to tell that the top element updated successfully.
  }
}

int is_empty(STACK* stack){
  //if the stack is empty.
  if (stack->top == NULL){
    return 1;               //if the stack is empty, it returns true (1).
  }else{
    return 0;               //else if stack has stored elements, it returns false (0).
  }
}

int get_size(STACK* stack){
  return stack->size;       //return the current size of the stack.
}

void display_stack(STACK* stack){
  //if the stack is empty.
  if (is_empty(stack) == 1){
    printf("The stack is empty! There is No elements to display!\n");
  }else{  //else if the stack has stored elements, we display them.
    printf("All elements stored in the stack from top to bottom:\n");
    for (node* current = stack->top; current != NULL; current = current->next){
      printf("%i\n", current->data);
    }
  }
}

void display_template(){
  //display templete of the valid operations on the stack.
  printf("These are the codes of the valid operations on the stack:\n");
  printf("1.Push element into the stack.              2.Pop the top element from the stack.\n");
  printf("3.Get value of the current top element.     4.Update value of the top element.\n");
  printf("5.Get the current size of the stack.        6.Display all elements stored in the stack.\n");
  printf("7.Reset the stack to the initial state.     8.Display operations template       9.Exit the system.\n");
}

void clear_stack(STACK* stack){
  //if the stack has stored elemnts.
  if (is_empty(stack) == 0){
    //traverse to free each node stored in the stack.
    node* current = stack->top;
    while (current != NULL){
      node* next = current->next;       //store the address of the next node in temporary variable.
      free(current);                    //free current node.
      current = next;                   //then update current to equal next.
    }
    stack->top = NULL;                  //reset stack variables to the initial state.
    stack->size = 0;
  }
}

void destroy_stack(STACK* stack){
  //if the stack has stored elements.
  if (is_empty(stack) == 0){
    //traverse to free nodes of the stack.
    node* current = stack->top;
    while (current != NULL){
      node* next = current->next;     //store the address of the next node in temporary variable.
      free(current);                  //free current node.
      current = next;                 //then update current to equal next.
    }
  }
  //then free stack space even if the list was empty.
  free(stack);
}
