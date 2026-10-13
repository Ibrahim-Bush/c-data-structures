/*
   This program is designed to demonstrate
   the exact behaviour and constraints of
   a Queue data structure.
   This implementation of a Queue is built
   using a dynamic circular array foundation.

    **     The Queue (FIFO Structure)    **

   - FIFO Concept:
     The Queue is a linear structure that strictly
     follows the First In, First Out (FIFO) principle.
     This means that the first element you add to
     the queue will be the very first one to be removed,
     perfectly keeping the original order of data processing.
   - Queue Behaviour:
     The Queue behaves exactly like a real-world waiting
     line, such as customers standing in a line at the
     bank counter. New items can only enter from the back
     of the line, and items can only leave from the front.
     We cannot access, modify, or remove elements from
     the middle of the structure directly.

    **      Advantages of Array Implementation &     **
                    Circular mechanism

   - Array Foundation:
     Implementing a queue using an array provides excellent
     cache locality and structural predictability because
     elements are stored in contiguous memory blocks.
     However, a standard linear array causes a serious flaw:
     when elements leave from the front, the space behind
     them becomes completely wasted.
   - The Circular Buffer Solution:
     To eliminate memory waste and avoid the expensive
     overhead of shifting elements backward, we treat
     the array as a circular loop. When an index reaches
     the end of the physical array boundary, it automatically
     wraps around to the beginning. This allows the queue
     to reuse freed spaces continuously and operate like
     an endless ring.

    **         Core Queue Tracking Components         **

   - First and Last Indices:
     These two markers define the active boundaries of
     the queue within the circular array. The First index
     tracks the oldest element waiting at the front of
     the line to be processed next. The Last index tracks
     the newest element that just joined the back of the line.


    **       The Importance of the Size Entity       **

   - Eliminating State Ambiguity:
     In a circular queue design, a serious structural
     challenge arises: both when the queue is completely
     empty and when it is completely full, the tracking
     indices (First, Last) can overlap or point to the
     exact same positions. This creates a state ambiguity
     where the program cannot reliably distinguish between
     a full queue and an empty queue only by comparing
     the positions of its tracking indices.
   - The Size Entity Solution:
     To achieve architectural perfection, we introduce
     a dedicated tracking variable called "Size". By
     maintaining an exact, absolute count of the active
     elements currently stored, the Size entity completely
     eliminates index ambiguity. If the size is zero,
     then the queue is clearly empty; else if the size
     matches the maximum capacity, the queue is clearly
     full. Additionally, it makes answering queries about
     the current element count instant and effortless.

    **           Core Queue Operations            **

   - Enqueue Operation:
     Inserts a new element at the back of the queue.
     If the system detects that the internal storage
     capacity is full occupied, it automatically starts
     a seamless expansion mechanism in the background.
     It allocates a larger memory block, linearizes the
     wrapped elements to a clean starting layout, updates
     the tracking indices, stores the new item safely,
     and increments the size.
   - Dequeue Operation:
     Removes the oldest element from the front of the queue.
     It safely extracts the value located at the First index,
     updates that index circularly to the next position,
     and decrements the size.

    **               Program Goal                 **
   - To build a clean, clear, and highly optimized program
     that illustrates the precise logic, circular memory
     management, and strong state safety of an automated,
     dynamic array-based FIFO Queue.

    **              Time Complexity               **
   - Enqueue element at the end of the queue:      O(1).
   - Dequeue the first element from the queue:     O(1).
   - Get value of the first element in the queue:  O(1).
   - Get the current size of the queue:            O(1).                 "Thanks to size entity"
   - Resize the capacity of the queue block:       O(n).      "Require copying all elements to the new block"
   - Shrink the capacity of the queue to fit size: O(n).      "Require copying all elements to the new block"
   - Display all elements stored in the queue:     O(n).       "Require traversing to display all elements"
   - Reset the queue to the initial state:         O(1).              "Only reset tracking variables"

   * Queue operations are fast and efficient and usually have O(1).
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct{

  int* data;          //this is the pointer to the block of memory allocated for queue elements.
  int first;          //this is the index of the first element in the queue.
  int last;           //this is the index of the last element in the queue.
  int capacity;       //this is the capacity of the block allocated for queue elements.
  int size;           //this is the number of elements currently stored in the queue;
} QUEUE;

//input functions.
int get_int(char* request);                //this function to take an integer value from the user.
void display_template();            //this function to display template of the valid operations on the queue.

//QUEUE functions.
QUEUE* init_queue(int initial_cap);            //this function to initialize a new queue of given capacity.
int enqueue(QUEUE* queue, int value);       //this function to enqueue a given element at the end of the queue.
int dequeue(QUEUE* queue, int* value);     //this function to dequeue and pass the first element from the queue.
int peek(QUEUE* queue, int* value);        //this function to get value of the element at the first of the queue.
int is_empty(QUEUE* queue);                    //this function to check whether the queue is empty or not.
int is_full(QUEUE* queue);                     //this function to check whether the queue is full or not.
int get_size(QUEUE* queue);                        //this function to get the current size of the queue.
int modulus(int capacity, int index); //this function to calculates the next circular index for the passed place.
int resize(QUEUE* queue, int new_cap);//this function to resize the queue and linearize elements to the new block.
void shrink(QUEUE* queue);              //this function to shrink the queue capacity to fit size to save memory.
void display_queue(QUEUE* queue);         //this function to display all elements currently stored in the queue.
void clear_queue(QUEUE* queue, int initial_cap);    //this function to reset the queue to the initial state.
void destroy_queue(QUEUE* queue);                  //this function to free all memory allocated for the queue.
void test_queue(QUEUE* queue);                 //this function to test the queue to ensure efficient use of memory.

int main(void){

  //identify the initial capacity.
  const int initial_cap = 10;

  //initialize new queue.
  QUEUE* my_queue = init_queue(initial_cap);
  if (my_queue == NULL){
    return 1;    //if we fail to allocate space for either queue variables or queue elements we exit the program.
  }
  //welcome the user and display operations template.
  printf("\nWelcome to Queue management system.\nThis implementation is built using a Dynamic array.\n\n");
  display_template();

  //ask the user for the code of desired operation.
  int code;
  do{
    //take user input.
    code = get_int("\nEnter the code of the operation you want to perform on the queue: ");
    //check code to perform desired opertion.
    if (code == 1){     //Enqueue process.
      int value = get_int("Enter value of the element you want to enqueue at the end of the queue: ");
      int status = enqueue (my_queue, value);   //enqueue element with enqueue function and store its return value.
      if (status == 1){      //if the function returns (1) then element enqueued successfully.
        printf("Element enqueued successfully into the queue.\n");
      }else{       //else if the function returns (0) then there is no space to add element even with resizing.
        printf("This element cannot be added! There is No space to add new elements!\n");
      }
    }else if (code == 2){   //Dequeue process.
      int value;      //this variable to store the value of the dequeued element.
      int status = dequeue(my_queue, &value);  //dequeue the first element with dequeue function and store its return.
      if (status == 1){           //if the function returns (1) then element dequeued successfully.
        printf("Element: %i dequeued successfully from the start of the queue.\n", value);
        shrink(my_queue);         //after each deletion, we shrink the queue to fit new size.
      }else{      //else if the function returns (0) then the queue is empty.
        printf("The queue is empty! There is No elements to delete!\n");
      }
    }else if (code == 3){   //Peek process.
      int value;      //this variable to store the value of the first element in the queue.
      int status = peek(my_queue, &value);    //get the value with peek function.
      if (status == 1){     //if the function returns (1) then value passed successfully.
        printf("The value of the current element at the start of the queue is: %i\n", value);
      }else{                //else if the function returns (0) then the queue is empty.
        printf("The queue is empty! There is No elements to display!\n");
      }
    }else if (code == 4){   //Display size.
      int size = get_size(my_queue);          //get current size with get size function.
      if (size == 0){         //if the size is zero then the queue is empty.
        printf("The queue is empty! There is No elements stored in the queue.\n");
      }else{                  //else display current size.
        printf("The current number of elements stored in the queue is: %i\n", size);
      }
    }else if (code == 5){   //Display queue.
      display_queue(my_queue);
    }else if (code == 6){   //Reset queue.
      clear_queue(my_queue, initial_cap);
      printf("The queue reseted successfully to the initial state.\n");
    }else if (code == 7){   //Display template.
      display_template();
    }else if (code == 8){   //Test process.
      test_queue(my_queue);
    }else if (code == 9){   //Exit process.
      printf("Exit the system.\n");
    }else{                  //Invalid input.
      printf("Invalid input! Enter (7) to check operations template.\n");
    }
  } while (code != 9);      //iterate until the user enters exit code (9).

  destroy_queue(my_queue);  //at the end of program we free all memory allocated for the queue to avoid memory leak.
  return 0;
}

int get_int(char* request){

  int value;                 //this variable to store the input value.
  int status;               //this variable to store the return value of scanf to check it.
  do{
    printf("%s", request);            //print request to ask the user for input.
    status = scanf("%i", &value);     //scan user input with scanf and store its return value.
    while (getchar() != '\n');        //clear buffer from garbage input or '\n'.
  } while (status == 0);      //iterate until scanf gets valid input as it returns zero in case of failure.

  return value;
}

QUEUE* init_queue(int initial_cap){
  //allocate space for queue variables.
  QUEUE* queue = malloc(sizeof(QUEUE));
  if (queue == NULL){
    return NULL;        //if the function fails to allocate space for queue variables, it returns NULL.
  }
  //then allocate space of size capacity for queue elements.
  queue->data = malloc(sizeof(int) * initial_cap);
  if (queue->data == NULL){
    return NULL;         //if the function fails to allocate space for queue elements, it returns NULL.
  }
  //initialize queue variables.
  queue->capacity = initial_cap;
  queue->first = queue->last = -1;      //make first and last equal (-1) as the queue is empty.
  queue->size = 0;

  return queue;
}

int enqueue(QUEUE* queue, int value){
  //if the queue is empty.
  if (is_empty(queue) == 1){
    queue->first = queue->last = 0;     //make first and last equal to (0) to point to the new and only element.
    *(queue->data + queue->last) = value;   //store new value at the new place that the last points to.
    queue->size++;              //increase size by (1) and return (1) to tell that element enqueued successfully.
    return 1;
  }else if (is_full(queue) == 1){          //else if the queue is full.
      int status = resize(queue, (queue->capacity * 1.5));  //resize queue and linearize existing elements.
      if (status == 1){   //if resizing suceeded.
        queue->last++;                            //increase last index to point to the next empty place.
        *(queue->data + queue->last) = value;     //store new element at the new place the last points to.
        queue->size++;                //increase size and return (1) to tell that element enqueued successfully.
        return 1;
      }else{
        return 0;  //else if resizing failed we return (0) to tell that element cannot be added into the queue.
      }
  }else if (queue->last == queue->capacity - 1){  //else if the last is pointing to the last physical place in queue.
      //and its guaranteed that the queue is not full as we check this condition and it was not true.
      queue->last = modulus(queue->capacity, queue->last); //wrap last index to point to the next circular empty place.
      *(queue->data + queue->last) = value;     //put the new element at the new place the last points to it.
      queue->size++;                 //increase size and return (1) to tell that element enqueued successfully.
      return 1;
  }else{        //else if last has empty places in front of its place.
    queue->last++;                          //increase last to point to the next empty place.
    *(queue->data + queue->last) = value;   //add element at the new empty place the last index points to it.
    queue->size++;                  //increase size and return (1) to tell that element enqueued successfully.
    return 1;
  }
}

int dequeue(QUEUE* queue, int* value){
  //if the queue is empty.
  if (is_empty(queue) == 1){
    return 0;                 //return zero to tell that the queue is empty.
  }else{      //else if the queue has sored elements.
    *value = *(queue->data + queue->first);     //pass the value of the current first element at the queue.
    queue->size--;                              //decrease size by one.
    if (is_empty(queue) == 1){         //if the queue becomes empty.
      queue->first = queue->last = -1;  //we reset the first and last indices to point to (-1).
    }else if (queue->first == (queue->capacity - 1)){  //else if first points to the last physical place of queue.
      queue->first = modulus(queue->capacity, queue->first); //wrap the first to point to the next circular item.
    }else{                      //else if first has stored elements in front of its place.
      queue->first++;           //increase first to point to the new first element in the queue.
    }
    return 1; //after successfully updating first, we return (1) to tell that first element dequeued successfully.
  }
}

int peek(QUEUE* queue, int* value){
  //if the queue is empty.
  if (is_empty(queue) == 1){
    return 0;             //return zero to tell that the queue is empty.
  }else{      //else if the queue has stored elements.
    *value = *(queue->data + queue->first);     //pass the value stored at the current first index.
    return 1;     //then, return (1) to tell that value of the first element in the queue passed successfully.
  }
}

int is_empty(QUEUE* queue){
  //if the queue is empty.
  if (queue->size == 0){
    return 1;               //return (1) to tell that the queue is empty.
  }else{    //else if the queue has stored elements.
    return 0;              //return (0) to tell that the queue is not empty.
  }
}

int is_full(QUEUE* queue){
  //if the queue is full.
  if (queue->size == queue->capacity){
    return 1;           //return (1) to tell that the queue is full.
  }else{   //else if the queue has empty places.
    return 0;           //return (0) to tell that the queue is not full.
  }
}

int get_size(QUEUE* queue){
  //return current size of the queue.
  return queue->size;
}

int modulus(int capacity, int index){
  //wrap the passed index to point to the first physical position of the queue.
  int new = (index + 1) % capacity;
  return new;
}

int resize(QUEUE* queue, int new_cap){
  //allocate new block of size new_cap
  int* ptr = malloc(sizeof(int) * new_cap);
  if (ptr == NULL){
    return 0;       //if the function failed to allocate new block, it returns zero to tell that resizing failed.
  }
  //if the old queue has stored elements.
  if (is_empty(queue) != 1){
    if (queue->first <= queue->last){     //if the queue is unwrapped means elements stored in linear layout.
      //copy all elements from first to last indices.
      int place = 0;    //initialize counter to track the next empty place at the new block.
      for (int current = queue->first; current <= queue->last; current++){
        *(ptr + place) = *(queue->data + current);   //copy data to empty places from the start of the new block.
        place++;          //after each addition, increase place by one to point to the next empty place.
      }
    }else{        //else if the queue is wrapped we linearize elements and copy them to the new block in order.
      //First: we copy elements from first marker to the physical end of the queue at the start of the new block.
      int place = 0;    //initialize a counter to track the next empty place at the new block.
      for (int current = queue->first; current < queue->capacity; current++){
        *(ptr + place) = *(queue->data + current);
        place++;        //after each addition we increase place to point to the next empty place.
      }
      //Then: we copy wrapped elements from the first of queue to the last marker to the new block.
      for (int current = 0; current <= queue->last; current++){
        *(ptr + place) = *(queue->data + current);
        place++;         //after each addition we increase place to point to the next empty place.
      }
    }
    //at the end of copying:
    queue->first = 0;   //make first equal zero as elements are stored from the physical start of the new block.
    queue->last = (queue->size - 1);  //and make last equal (size - 1) as index start from zero.
  }
  free(queue->data);                //free the old block that contains queue elements to avoid memory leak.
  queue->data = ptr;                //make the pointer points to the new block.
  queue->capacity = new_cap;        //update capacity to equal capacity of the new block.
  return 1;                         //finally, we return (1) to tell that queue resized successfully.
}

void shrink(QUEUE* queue){
  //if the capacity is very small.
  if (queue->capacity <= 20){
    return;                   //shrinking queue will be useless.
  }
  if (queue->capacity > (queue->size * 2)){    //else if the queue is half empty.
    int status = resize(queue, (queue->capacity * 2/3));  //resize queue to fit current size and save memory.
  }
}

void display_queue(QUEUE* queue){
  //if the queue is empty.
  if (is_empty(queue) == 1){
    printf("The queue is empty! There is No elements to display!\n");
  }else{    //else if the queue has stored elements, we display elements from first to last.
    printf("All elements stored in the queue from first to last:\n");
    //if the queue is unwrapped mean that elements are stored in linear layout.
    if (queue->first <= queue->last){
      //iterate from first to last indices and display each element.
      for (int current = queue->first; current <= queue->last; current++){
        printf("%i\n", *(queue->data + current));
      }
    }else{      //else if the queue is wrapped.
      //First: iterate from first to the physical end of the queue.
      for (int current = queue->first; current < queue->capacity; current++){
        printf("%i\n", *(queue->data + current));
      }
      //Then: iterate from zero to the place of the last element stored in the queue.
      for (int current = 0; current <= queue->last; current++){
        printf("%i\n", *(queue->data + current));
      }
    }
  }
}

void display_template(){
  //display code of valid operations on the queue.
  printf("These are the codes of valid operations to perform on the queue:\n");
  printf("1.Enqueue the element at the end of the queue.   2.Dequeue the element at the start of the queue\n");
  printf("3.Get value of the current first element.        4.Get the current size of the queue.\n");
  printf("5.Display all elements stored in the queue.      6.Reset the queue to the initial state.\n");
  printf("7.Display operations template.                   8.Test queue efficiency.           9.Exit the program.\n");
}

void clear_queue(QUEUE* queue, int initial_cap){
  //if the queue is not empty,
  if (is_empty(queue) == 0){
    queue->first = queue->last = -1;          //reset first and last indices to (-1).
    queue->size = 0;                          //make size equal zero to extract all queue elements.
    int status = resize(queue, initial_cap);  //resize queue to the initial capacity.
  }
}

void destroy_queue(QUEUE* queue){
  //First: free block that stores queue elements.
  if (queue->data != NULL){
    free (queue->data);
  }
  //Then: free the space allocated for queue variables.
  free(queue);
}

void test_queue(QUEUE* queue){
  //display queue variables to ensure efficient use of memory.
  printf("The current number of elements stored in the queue: %i\n", queue->size);
  printf("The current capacity of the queue is: %i\n", queue->capacity);
  printf("The first element stored in the queue exist at index: %i\n", queue->first);
  printf("The last element stored in the queue exist at index: %i\n", queue->last);
}
