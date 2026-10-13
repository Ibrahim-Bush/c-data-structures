/*
   This program presents a clear and optimized
   version of a standard FIFO Queue data structure.
   This implementation is built using a Singly
   Linked List to manage data elements dynamically
   in memory. This design ensures flexible memory
   allocation and guarantees constant-time execution
   for core operations on the queue.

    **  Advantages of Linked List Implementation  **

   - Linked List Foundation:
     Implementing a queue using a singly linked list
     provides excellent dynamic behavior because elements
     are allocated independently in memory only when needed.
     This approach completely eliminates the need for
     fixed capacity, checking if the queue is full, or
     running complex resizing and shrinking algorithms.
   - The Time Space Trade-off:
     While a dynamic circular array requires a periodic
     resize operation that consumes O(n) time when the
     allocated space is full, the linked list implemenation
     guarantees that every enqueue and dequeue operation
     runs in pure O(1) constant time. However this time
     efficiency comes with a space cost. Each element (node)
     in the queue must store an extra pointer to the next node,
     which increases the overall memory consumption compared
     to a contiguous array block.
   - Cleanup Operation Overhead:
     Unlike an array where the entire block of memory can be
     freed in a single step, a linked list requires moving
     through every single node one by one to free its memory.
     This makes the clear and destroy operations take O(n) time.
     However, because we only clean up memory less often compared
     to adding and removing elements, the overall program stays
     very fast and efficient for continuous use.

    **        Core Queue Tracking Components         **

   - First and Last Pointers:
     These two markers define the active boundaries of the queue
     within the heap memory. The First pointer tracks the oldest
     element waiting at the front of the line to be processed
     next during a dequeue operation. The Last pointer tracks
     the newest element that just joined the back of the line,
     allowing instant insertion during an enqueue operation
     without searching through the list.
   - The Size Entity:
     To maintain perfect administrative control, we use
     a dedicated size variable. This tracking variable maintains
     an exact count of the active elements currently stored in the queue.
     It allows the program to instantly check is the queue is empty
     when size is zero, and provides an immediate answer about
     the element count without traversing the nodes manually.

    **             Core Queue Operations              **

   - Enqueue Operation:
     Inserts a new element at the back of the queue. The system
     dynamically allocates a new node in memory, stores the value
     inside it, and links it to the current Last node in the queue.
     Finally, it updates the Last pointer to point to this newly
     added node and increments the size. If the queue was empty,
     both First and Last pointers are initialized to point to
     the single new node.
   - Dequeue Operation:
     Removes the oldest element from the front of the queue.
     It safely secures the current First node using a temporary
     pointer, shifts the First pointer forward to the next node
     in line, and then frees the memory of the isolated node.
     It also decrements the size entity. If this operation
     leaves the queue completely empty, the Last pointer is
     safely reset to NULL to avoid leaving an invalid pointer.

    **                    Program Goal                   **
   - To build a clean, clear, and highly optimized program
     that illustrates the precise logic, dynamic memory
     management, and efficient operations of a Singly
     Linked List-based FIFO Queue.

    **                  Time Complexity                  **
   - Enqueue element at the end of the queue:     O(1).
   - Dequeue the first element from the queue:     O(1).
   - Get value of the first element in the queue: O(1).
   - Get the current size of the queue:           O(1).                "Thanks to Size entity"
   - Display all elements stored in the queue:    O(n).       "Requires traversing to display each element"
   - Reset the queue to the initial state:        O(n).          "Requires traversing to free each node"
   - Destroy the queue by freeing its space:      O(n).          "Requires traversing to free each node"

   * Queue operations are fast and efficient and usually have O(1).
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node{

  int data;                 //the data stored in the node.
  struct node* next;        //the pointer to the next node.
} node;

typedef struct{

  node* first;            //the pointer to the first node in the queue.
  node* last;             //the pointer to the last node in the queue.
  int size;               //the number of elements stored in the queue.
} QUEUE;

//input functions.
int get_int(char* request);                     //this function to take an integer value from the user.
void display_template();                //this function to display the valid operations to perform on the queue.

//QUEUE functions.
QUEUE* init_queue();                   //this function to allocate space for a new queue initialize its variables.
node* create_node(int value);               //this function to create a node for a new element of given value.
void enqueue(QUEUE* queue, node* ptr);        //this function to enqueue a new node at the end of the queue.
int dequeue(QUEUE* queue, int* value); //this function to dequeue the first element at the queue and pass its value.
int peek(QUEUE* queue, int* value);           //this function to get the value of the first element at the queue.
int is_empty(QUEUE* queue);                      //this function to check whether the queue is empty or not.
int get_size(QUEUE* queue);                          //this function to get the current size of the queue.
void display_queue(QUEUE* queue);                 //this function to display all elements stored in the queue.
void clear_queue(QUEUE* queue);                       //this function to reset queue to the initial state.
void destroy_queue(QUEUE* queue);    //this function to free all memory allocated for the queue to avoid memory leak.

int main(void){

  //initialize a new queue.
  QUEUE* my_queue = init_queue();
  if (my_queue == NULL){
    return 1;           //if the function fails to allocate space for the queue, we exit the program.
  }
  //Welcome the user and display operations template.
  printf("\nWelcome to Queue management system.\nThis implementation is built using a Singly Linked List.\n\n");
  display_template();

  //ask the user for the code of desired operation.
  int code;
  do{
    code = get_int("\nEnter the code of the operation you want to perform on the queue: ");
    //check the code and perform the desired operation.
    if (code == 1){     //Enqueue process.
      int value = get_int("Enter the value of the element you want to enqueue: ");
      node* ptr = create_node(value);   //create a new node for the element.
      if (ptr == NULL){
        destroy_queue(my_queue);    //if the function fails to allocate space for node we free all memory allocated,
        return 1;                                          //then exit the program.
      }
      enqueue(my_queue, ptr);       //enqueue the node with enqueue function.
      printf("Element enqueued successfully to the queue.\n");
    }else if (code == 2){    //Dequeue process.
      int value;      //this variable to store the dequeued value.
      int status = dequeue(my_queue, &value);     //dequeue the first element with dequeue function.
      if (status == 0){     //if the function returns zero then the queue is empty.
        printf("The queue is empty! There is No elements to delete!\n");
      }else{                //else, the element dequeued successfully.
        printf("First element: %i dequeued successfully from the queue.\n", value);
      }
    }else if (code == 3){   //Peek process.
      int value;      //this variable to store the value of the first element in the queue.
      int status = peek(my_queue, &value);
      if (status == 0){        //if the function returns zero then the queue is empty.
        printf("The queue is empty! There is No elements to display!\n");
      }else{                    //else, the value passed successfully.
        printf("The value of current first element at the queue is: %i\n",value);
      }
    }else if (code == 4){   //Get size.
      int size = get_size(my_queue);
      if (size == 0){       //if size is zero then the queue is empty.
        printf("The queue is empty. There is No elements stored in the queue.\n");
      }else{                //else display current size of the queue.
        printf("The current number of elements stored in the queue is: %i\n", size);
      }
    }else if (code == 5){   //Display queue.
      display_queue(my_queue);                    //display elements with display function.
    }else if (code == 6){   //Reset process.
      clear_queue(my_queue);
      printf("The queue reseted successfully to the initial state.\n");
    }else if (code == 7){   //Display template.
      display_template();
    }else if (code == 8){   //Exit process.
      printf("Exit the system.\n");
    }else{                  //Invalid input.
      printf("Invalid input! Enter (7) to check operations template.\n");
    }
  } while (code != 8);          //iterate until the user enters exit code (8).

  //at the end of the program, we free all memory allocated for the queue to avoid memory leak.
  destroy_queue(my_queue);
  return 0;
}

int get_int(char* request){

  int value;        //this variable to store the input value.
  int status;       //this variable to store the return value of scanf to check it.
  do{
    printf("%s", request);            //print request to ask the user for input.
    status = scanf("%i", &value);     //get the input with scanf and store its return value.
    while(getchar() != '\n');         //clear the buffer from garbage input or '\n'.
  } while (status == 0);        //iterate until scanf gets a valid input as it returns zero in case of failure.

  return value;
}

QUEUE* init_queue(){

  QUEUE* queue = malloc(sizeof(QUEUE));   //allocate space for QUEUE variables using malloc.
  if (queue == NULL){
    return NULL;      //if the function fails to allocate space it returns NULL.
  }
  //initialize queue variables.
  queue->first = queue->last = NULL;
  queue->size = 0;

  return queue;
}

node* create_node(int value){
  //allocate space for new node.
  node* ptr = malloc(sizeof(node));
  if (ptr == NULL){
    return NULL;        //if the function fails to allocate space for the node it returns NULL.
  }
  //initialize node variables.
  ptr->data = value;
  ptr->next = NULL;

  return ptr;
}

void enqueue(QUEUE* queue, node* ptr){
  //if the queue is empty.
  if (is_empty(queue) == 1){
    //make first and last pointers point to the new and only node.
    queue->first = queue->last = ptr;
    queue->size++;
  }else{    //else if the queue has stored elements.
    queue->last->next = ptr;      //make the last node points to the new node.
    queue->last = ptr;            //update last pointer to point to the new node.
    queue->size++;
  }
}

int dequeue(QUEUE* queue, int* value){
  //if the queue is empty.
  if (is_empty(queue) == 1){
    return 0;         //return zero to tell that the queue is empty.
  }else if (queue->first == queue->last){     //else if the queue has only one node.
    *value = queue->first->data;      //pass the value stored in the first node at the queue.
    free(queue->first);                   //free the node space to avoid memory leak.
    queue->first = queue->last = NULL;    //make first and last pointers point to NULL.
    queue->size = 0;
  }else{          //else if the list has many elements.
    *value = queue->first->data;      //pass the value stored in the first node at the queue.
    node* temp = queue->first;        //store the address of the first node at temporary pointer.
    queue->first = queue->first->next;    //update first pointer to point to the next node.
    free(temp);                           //free the first node with the temporary variable.
    queue->size--;
  }
  return 1;   //at the end of successfull deletion we retrun (1) to tell that first element dequeued successfully.
}

int peek(QUEUE* queue, int* value){
  //if the queue is empty.
  if (is_empty(queue) == 1){
    return 0;       //we return zero to tell that the queue is empty.
  }else{      //else if the queue has stored elements.
    *value = queue->first->data;    //pass the value stored in the first node at the queue.
    return 1;       //then return (1) to tell that the value passed successfully.
  }
}

int is_empty(QUEUE* queue){
  //we check the actual queue pointers, if the first pointers points to NULL.
  if (queue->first == NULL){
    return 1;         //return (1) to tell that the queue is empty.
  }else{
    return 0;         //else, return zero to tell that the queue is not empty.
  }
}

int get_size(QUEUE* queue){
  return queue->size;         //return the current queue size.
}

void display_queue(QUEUE* queue){
  //if the queue is empty.
  if (is_empty(queue) == 1){
    printf("The queue is empty! There is No elements to display!\n");
  }else{    //else if the queue has stored elements.
    printf("All elements stored in the queue from first to last:\n");
    //iterate to display all elements stored in the queue.
    for (node* current = queue->first; current != NULL; current = current->next){
      printf("%i\n", current->data);
    }
  }
}

void display_template(){
  //Display codes of the valid operations on the queue.
  printf("These are the codes of the valid operations to perform on the queue:\n");
  printf("1.Enqueue element at the end of the queue.              2.Dequeue the first element from the queue.\n");
  printf("3.Get value of the current first element.               4.Get the current size of the queue.\n");
  printf("5.Display all elements stored in the queue.             6.Reset the queue to the initial state.\n");
  printf("7.Display operations template.                          8.Exit the system.\n");
}

void clear_queue(QUEUE* queue){
  //if the queue has stored elements.
  if (is_empty(queue) == 0){
    //first: iterate to free all nodes of the queue.
    node* current = queue->first;
    while (current != NULL){
      node* temp = current->next;     //store address of the next node in temporary pointer.
      free(current);                  //free current node.
      current = temp;                 //update current to point to the next node with the temporary pointer.
    }
  }
  //Then: reset queue variables whether the queue is empty or not.
  queue->first = queue->last = NULL;
  queue->size = 0;
}

void destroy_queue(QUEUE* queue){
  //if the queue is not empty.
  if (is_empty(queue) == 0){
    //first: iterate to free all nodes at the queue.
    node* current = queue->first;
    while (current != NULL){
      node* temp = current->next;   //store the address of the next node in temporary pointer.
      free(current);                 //free the current node.
      current = temp;               //update current to point to the next node with the temporary pointer.
    }
  }
  //Then: free the queue space that store the tracking variables whether the queue was empty or not.
  free(queue);
}
