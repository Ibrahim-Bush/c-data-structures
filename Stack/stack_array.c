/*
   In this program we implement the stack
   data structure using a dynamic Array.

    **    The Stack (LIFO Structure)    **

   - The stack is a linear data structure
     governed strictly by the Last In, First Out
     (LIFO) principle. In this architecture,
     the most recently added element is always
     the first one to be removed. Access to to
     the data structure is highly restricted,
     meaning elements cannot be accessed, modified
     or traversed from the middle or bottom directly;
     all operations are limited to the specific entry
     and exit point known as the top.

    **   Advantages of the Array-Based Stack   **

   - Implementing a Stack using a dynamic array
     allocated in the Heap provides distinct
     advantages over a linked list foundation:
     - Contiguous Memory Locality:
       sorting elements in sequential memory locations
       ensures high cache efficiency and significantly
       reduces hardware access latency during traversal.
     - Zero Pointer Overhead:
       Unlike lists, which require an extra pointer space
       for every single node to maintain connectivity,
       the array structure stores only the raw data elements.
       this result in a much smaller memory usage.
     - Controlled Lifetime and Growth:
       Allocating the array block dynamically within
       the Heap ensure precise control over the structure's
       lifetime, ensuring that the allocated memory remains
       active across function calls until deallocate it.
     - Instant State Resets:
       Resetting the data structure does not require
       sequential memory traversal or individual node
       deallocations. The entire stack can be instantly
       cleared by updating internal tracking variables,
       leaving old data to be cleanly overwritten by
       subsequent operations.

    **       The Role of the Top Index      **

   - The internal tracking mechanism relies on an integer
     variable representing the Top index. This variable
     monitors the exact boundary of the data within the
     continuous block. It initializes at (-1) to indicate
     an entirely empty state, increments as elements are
     introduced, and is strictly bounded by the maximum
     capacity of the array.

    **         Core Stack Operations         **

   Push Operation:
   Before adding an element, the system verifies that
   the current Top Index has not reached the maximum
   capacity limit. Once validated, the Top Index
   is incremented and the incoming element is written
   directly into that specific array position.
   Pop Operation:
   Before removing an element, the system verifies that
   the Top Index is not in its initial empty state (-1).
   Once validated, the element currently existing at
   the Top Index is extracted and returned via a pointer
   reference, and the Top Index is subsequently decremented.

    **               Program Goal              **
   - The objective of this design is to construct
     a safe, well-structured and highly optimized
     dynamic array-based stack that emphasizes strong
     memory management, strict validation constraints,
     and reliable resource control within the Heap.

    **            Time Complexity            **
   - Push new element at the top of the stack:  O(1).
   - Pop the element at the top of the stack:   O(1).
   - Get the value of the current top element:  O(1).
   - Update value of the current top element:   O(1).
   - Resize the capacity of the stack block:    O(n).         "Require moving all elements to the new block"
   - Shrink the space of the stack to fit size: O(n).         "Require moving all elements to the new block"
   - Display all elements stored in the stack:  O(n).          "Require traversing to display each element"
   - Reset the stack to the initial state:      O(1).                   "Only reset the Top Index"

   * Stack operations are fast and efficient and usually have O(1).
    */

#include <stdio.h>
#include <stdlib.h>

typedef struct{

   int* data;           //pointer to the block of memory allocated for the stack.
   int capacity;        //stores the current maximum capacity of the stack.
   int top;             //index of the current top element in the stack.
} STACK;

//input functions.
int get_int(char* request);                  //this function to get an integer value from user.
void display_template();                   //this function to display template of valid operations on the stack.

//Stack functions.
STACK* init_stack(int initial_cap);          //this function to initialize a new stack of given capacity.
int push(STACK* stack, int value);        //this function to push a new element into the stack.
int pop(STACK* stack, int* value);        //this function to pop the current top element from the stack.
int peek(STACK* stack, int* value);       //this function to get the value of the top element without deleting it.
int update_top(STACK* stack, int new_value); //this function to update the value of the current top element.
int is_empty(STACK* stack);                //this function to check if the stack is empty or have stored elements.
int is_full(STACK* stack);                 //this function to check if the stack reaches the maximum capacity.
int get_size(STACK* stack);                //this function to get the current number of elements in the stack.
int resize_stack(STACK* stack, int new_cap); //this function to resize the stack capacity to store more elements.
void shrink_stack(STACK* stack);           //this function to shrink the space of the array to fit size.
void display_stack(STACK* stack);   //this funtion to display all elements stored in the stack from top to bottom.
void clear_stack(STACK* stack, int initial_cap);     //this function to reset the stack to the initial state.
void destroy_stack(STACK* stack);                    //this function to free all memory allocated for the stack.


int main(void){

   //identify the initial capacity.
   const int initial_cap = 10;

   //initialize a new stack.
   STACK* my_stack = init_stack(initial_cap);   //allocate space for stack variables and block to store elements.
   if (my_stack == NULL){
      return 1;            //if allocation fails, we exit the program.
   }
   //welcome the user to the system display valid operations on stack.
   printf("\nWeclome to Stack management system.\nThis implementation is built using a Dynamic Array.\n\n");
   display_template();

   //ask the user for the code of desired operation.
   int code;
   do{
      //ask the user for code.
      code = get_int("\nEnter the code of the operation you want to perform: ");
      //check the code to perform desired operation.
      if (code == 1){        //push process.
         int value = get_int("Enter the value of element you want to push into the stack: ");
         int status = push(my_stack, value);    //push element into the stack with push function.
         if (status == 1){    //if the function returns (1) then element added successfully.
            printf("Element pushed into the stack successfully.\n");
         }else{               //else if function returns (0) then there is No space even with resizing.
            printf("This element cannot be added! There is No space to add new elements!\n");
         }
      }else if (code == 2){   //Pop process.
         int value;           //this variable to store the popped value.
         int status = pop(my_stack, &value);    //pop the top element with pop function.
         if (status == 0){    //if the function returns zero then the stack is empty.
            printf("The stack is empty! There is No elements to delete!\n");
         }else{            //else if the function returns (1) then the popped element was put in the variable.
            printf("Element: %i deleted successfully from the top of the stack.\n", value);
            shrink_stack(my_stack);    //after deletion we shrink stack if there are more empty places than full.
         }
      }else if (code == 3){    //Peek process.
         int value;            //this variable to store value of the top element.
         int status = peek(my_stack, &value);      //get value of top element with peek function.
         if (status == 0){       //if the function returns zero then the stack is empty.
            printf("The stack is empty! There is No elements to display!\n");
         }else{         //else if the function returns (1) then the value of top element was put in the variable.
            printf("The current top element in the stack is: %i\n", value);
         }
      }else if (code == 4){   //Update top process.
         int new_value = get_int("Enter new value you want to update the top element with: ");
         int status = update_top(my_stack, new_value);   //update top element with update top function.
         if (status == 0){    //if the function returns zero then the stack is empty.
            printf("The stack is empty! There is No elements to update!\n");
         }else{               //else if the function returns (1) then the element updated successfully.
            printf("The top element updated successfully.\n");
         }
      }else if (code == 5){   //Display size.
         int size = get_size(my_stack);
         if (size == 0){      //if size equal zero, the stack is empty.
            printf("The stack is empty! There are No elements stored in the stack.\n");
         }else{               //else display current size.
            printf("The current number of elements stored in the stack is: %i\n", size);
         }
      }else if (code == 6){   //Display stack.
         display_stack(my_stack);
      }else if (code == 7){    //Reset stack.
         clear_stack(my_stack, initial_cap);       //reset the stack with clear function.
         printf("The stack reseted successfully to initial state.\n");
      }else if (code == 8){     //Display template.
         display_template();
      }else if (code == 9){      //Exit process.
         printf("Exit the system.\n");
      }else{                     //Invalid input.
         printf("Invalid input! Enter (8) to check operations template.\n");
      }
   } while (code != 9);             //iterate until the user enters exit code (9).

   destroy_stack(my_stack);         //free all memory allocated for the stack to avoid memory leak.
}

int get_int(char* request){

   int value;        //this variable to store the input value.
   int status;       //this variable to store the return value of scanf to check it.
   do{
      printf("%s", request);           //ask the user for input.
      status = scanf("%i", &value);    //get input value by scanf and store its return value.
      while(getchar() != '\n');        //clear the buffer from garbage input or '\n'
   } while (status == 0);   //iterate until scanf gets a valid input as it returns zero in case of failure.

   return value;
}

STACK* init_stack(int initial_cap){

   STACK* stack = malloc(sizeof(STACK));     //allocate space for the stack variables.
   if (stack == NULL){
      return NULL;           //if there is No available space the function returns NULL.
   }
   stack->data = malloc(sizeof(int) * initial_cap);  //then allocate space of initial cap for stack elements.
   if (stack->data == NULL){
      free(stack);               //if there is No space for the data, we free the block allocated for stack,
      return NULL;                                      //and return NULL.
   }
   stack->capacity = initial_cap;      //initialize stack capacity and the Top index is initialized to (-1).
   stack->top = -1;

   return stack;
}

int push(STACK* stack, int value){
   //if the stack is full.
   if (is_full(stack) == 1){     //resize stack to take more elements and make new_cap equal (cap * 3/2).
      int status = resize_stack(stack, (stack->capacity * 1.5));
      if (status == 1){          //if resizing succeed we call push function with the value.
         return push(stack, value);
      }else{
         return 0;               //else if resizing failed we return (0) to tell that element cannot be added.
      }
   }else{      //else if stack has empty places.
      stack->top++;                          //increase Top index by one to add the new element at the top.
      *(stack->data + stack->top) = value;    //put the new value at the index of top.
      return 1;
   }
}

/*NOTE: the function returns (1) if we have popped element and put its value in the address of given pointer,
  else if the stack is empty it returns (0).*/
int pop(STACK* stack, int* value){
   //if the stack is empty.
   if (is_empty(stack) == 1){
      return 0;                  //we return zero to tell that the stack is empty.
   }else{
      *value = *(stack->data + stack->top);     //put the value of top element at the address of given pointer.
      stack->top--;                       //decrement Top index by one to extract the top element from the stack.
      return 1;                                 //return (1) to tell that the top element deleted successfully.
   }
}

/*NOTE: the function returns (1) if we have put the value of the top element in the address of given pointer,
  else if the stack is empty it returns (0).*/
int peek(STACK* stack, int* value){
   //if the stack is empty.
   if (is_empty(stack) == 1){
      return 0;               //we return 0 to tell that the stack is empty.
   }else{ //else if stack has stored elements we put the value of the top element at the address of given pointer.
      *value = *(stack->data + stack->top);
      return 1;
   }
}

int update_top(STACK* stack, int new_value){
   //if the stack is empty.
   if (is_empty(stack) == 1){
      return 0;               //we return(0) to tell that the stack is empty.
   }else{  //else we update the value of the top element and return (1) to tell that element updated successfully.
      *(stack->data + stack->top) = new_value;
      return 1;
   }
}

int is_empty(STACK* stack){   //this function returns (1) if the stack is empty otherwise, it returns (0).
   //if the stack is empty.
   if (stack->top == -1){     //if the Top index is at intial state (-1), then the stack is empty.
      return 1;
   }else{
      return 0;
   }
}

int is_full(STACK* stack){   //this function returns (1) if the stack is full otherwise, it returns (0).
   //if the stack is empty.
   if (stack->top == stack->capacity - 1){
      return 1;              //if the Top index equalls (capacity - 1) then the stack is full.
   }else{
      return 0;
   }
}

int get_size(STACK* stack){
   return (stack->top + 1);      //return current size of the stack (top + 1) as index start with (0).
}

int resize_stack(STACK* stack, int new_cap){
   //reallocate current stack data to a new block of capacity equal new_cap.
   int* temp = realloc(stack->data, sizeof(int) * new_cap);
   if (temp == NULL){      //if realloc fails it returns NULL so we must check before asign it to (stack->data).
      return 0;            //if it fails we return (0) to tell that the resizing failed.
   }else{
      stack->data = temp;    //else, we asign the address of the new block to the (stack->data) and make capacity
      stack->capacity = new_cap;     //equal new cap then return (1) to tell that the stack resized successfully.
      return 1;
   }
}
//the purpose of shrink function is to save space if the stack has more empty places than full places.
void shrink_stack(STACK* stack){
   if (stack->capacity < 20){    //if stack has small capacity, shrinking it is not important.
      return;
   }              //if stack is half empty, we resize it to fit size and save memory.
   if (stack->capacity > (stack->top * 2)){  //make new capacity equal current capacity * (2/3)
      int status = resize_stack(stack, (stack->capacity * 2/3));
   }
}

void display_stack(STACK* stack){
   //if the stack is empty.
   if (is_empty(stack) == 1){
      printf("The stack is empty! There is No elements to display!\n");
   }else{   //else if stack has stored elements, we display elements from top to bottom.
      printf("All elements stored in the stack from top to bottom:\n");
      int current = stack->top;           //initialize place with top index.
      while (current >= 0){               //iterate while current index is bigger than or equal zero.
         printf("%i\n", *(stack->data + current));    //print the element at current place.
         current--;                       //decrease counter by one.
      }
   }
}

void display_template(){
   //display code of valid operations to perform on the stack.
   printf("These are the codes of valid operations to perform on the stack:\n");
   printf("1.Push element into the stack.             2.Pop the top element from the stack.\n");
   printf("3.Get value of the current top element.    4.Update value of the top element.\n");
   printf("5.Get the current size of the stack.       6.Display all elements stored in the stack.\n");
   printf("7.Reset the stack to the initial state.    8.Display operations template.       9.Exit the system.\n");
}

void clear_stack(STACK* stack, int initial_cap){
   //if the stack is not empty.
   if (is_empty(stack) == 0){
      //we clear the stack by making Top index equals (-1) to extract all elements.
      stack->top = -1;
      int status = resize_stack(stack, initial_cap);         //and resize stack to the initial capacity.
   }
}

void destroy_stack(STACK* stack){
   //first free the block that stores elements of the stack.
   if (stack->data != NULL){
      free(stack->data);
   }
   //then, free the block that stores stack variables.
   free(stack);
}
