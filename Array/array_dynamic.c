/*
   in this program we evolve from
   static to dynamic arrays.
   we shift out storage from the
   stack to the heap to gain
   flexibility, while using pointer
   arithmetic to control our data
   at a lower level.

   ** Lifetime and Availability **
   - unlike stack variables that
     die when their function ends,
     Heap memory stays alive until
     we manually destroy it with free().
   - This allows data created in one
     function to stay available and
     safely used across the entire
     program.

    **  HEAP Memory Management  **
    - malloc(): Allocates the initial
      memory block on the HEAP at runtime.
    - realloc(): Modifies the array size
      dynamically by expanding or
      reallocating the block of memory.
    - free(): Releases the memory block
      to the system to prevent memory leaks.

    ** Modular Program Structure **
    - This program is designed using
      a modular approach by dividing
      logic into specialized functions.
    - This structure improves code
      readability and mantainability
      allowing each task to be handled
      independently.
    - Communication between functions
      is managed using pass by reference
      to directly modify the original
      variables.

    **  Dynamic Pointer Behaviour  **
    - Unlike fixed static arrays, Our pointer
      can be reassigned to a new memory block.
    - This is useful as if realloc moves our
      data to a new area, we can update our
      pointer to the new address without losing
      our data after freeing the old block.

    **  CORE Advantages of REALLOC  **
    - It eliminates the need for Manual
      Copying as it handles the allocation
      of a new block of memory and copy
      the old data to it automatically
      then it frees the old memory block.
    - It optimizes performance by attampting
      to grow the memory in-place whenever
      possible, this saves time as we do not
      need to copy data which is time consuming O(n).
   */

#include <stdio.h>
#include <stdlib.h>

int my_get_int(char* request);              //this function to take user integer input.
char my_get_char(char *request);            //this function to take single character from user.
void print_array(int* ptr, int size);       //this function to print the elements of array.
int* resize(int* ptr, int new_size);        //this function to Resize the array.
int append(int* arr, int capacity, int* size_ptr, int number);  //this function to append a number.
//this function to insert element at specific place.
int insert(int* arr, int capacity, int* size_ptr, int number, int place);
void delete(int* arr, int* size_ptr, int place);  //this function delete element at specific place.

int main(void){

    //initializing the array variables.
    int capacity = 10;                          //store the capacity of array.
    int* arr = malloc(capacity * sizeof(int));  //allocating a space for array of length capacity.
    if(arr == NULL){                              //if something went wrong we exit.
        return 1;
    }
    int size = 0;                               //storing the number of elements in array.

    //ask the user for the operation he want until he finish the loop.
    printf("\nwe have array of size %i\n", capacity);
    char input;
    do{
        printf("\nWhich operation you want to perform?\n");
        input = my_get_char("A: append, I: insert, D:delete, P: print all elements, E: exit :");

        //appending process.
        if (input == 'A' || input == 'a'){      //we ask the user for number of elements.
           int number = my_get_int("How many elements you want to append: ");

           for(int i = 0; i < number; i++){     //get numbers and append them one by one.
              int value = my_get_int("Enter number: ");
              int status = append(arr, capacity, &size, value);   //we pass size by reference to apply
                                                                  //changes to original value.
              if (status == 1){         //if the array becames full we ask the user to resize array.
                printf("There is No Space for this element\n");
                char resize_answer = my_get_char("Do you want to resize array to add more elements[y/n]: ");

                if (resize_answer == 'y' || resize_answer == 'Y'){
                  int* space = resize(arr, capacity + 10);
                  if (space != NULL){
                     arr = space;    //add more 10 places only at every resizing time to save memory.
                     capacity += 10;
                     printf("Array resized successfully. Now, we have more ten places.\n");
                     append(arr, capacity, &size, value);
                     printf("element appended successfully\n");
                  }else{
                    printf("Resizing failed!\n");     //in case of returnning NULL by resize function.
                    return 1;
                  }
                }
              }else{
                printf("element appended successfully\n");
              }
           }
        }

        //inserting process.
       else if (input == 'I' || input == 'i'){

          int value = my_get_int("Enter number: ");
          int index = my_get_int("Enter index you want to insert element in it: ");
          if(index <= size){
              int status = insert(arr, capacity, &size, value, index);

              if (status == 1){           //if the array is full we ask the user to resize it.
                printf("There is No Space for this element\n");
                char resize_answer = my_get_char("Do you want to resize array to add more elements[y/n]: ");
                if (resize_answer == 'y' || resize_answer == 'Y'){
                    int* space = resize(arr, capacity + 10);
                    if(space != NULL){
                        arr = space;
                        capacity += 10;
                        printf("Array resized successfully. Now, we have more ten places.\n");
                        insert(arr, capacity, &size, value, index);
                        printf("element inserted successfully\n");
                    }else{
                      printf("Resizing failed!\n");   //in case of return NULL by resize function.
                    }
                }
             }else{
                printf("element inserted successfully\n");
             }
          }else{
            printf("we cannot insert in this place! Elements must be in sequential order.\n");
          }
      }

          //delete process.
         else if (input == 'D' || input == 'd'){      //get place of element the user wants to delete.
              int index = my_get_int("Enter the index of element you want to delete: ");
              if (index < size){
                  delete(arr, &size, index);
                  printf("element deleted successfully\n");
              }else{
                printf("There is no elements in this place\n");
              }
          }

          //printing process.
          else if (input == 'p' || input == 'P'){
            print_array(arr, size);
          }
          else if (input == 'e' || input == 'E'){
            printf("exit program\n");
          }else{
            printf("Invalid input! Try again\n");
          }

    } while(input != 'E' && input != 'e');    //this loop will end only if user enters 'E' or 'e'
      //we can combine conditions using a logic gate and the output of gate will be the condition.

    free(arr);          //at the end we free the array to avoid memory leak.

    return 0;
}

int my_get_int(char* request){          //function to take user input.

    int value;             //we put variables here to be in the scope of scanf and return functions.
    int status;
    do{
        printf("%s", request);
        status = scanf("%i", &value);
        while(getchar() != '\n');   //clearing the buffer from garbage input or '\n' after each trial.
    } while(status == 0);           //repeating steps if the user enters invalid input.

    return value;
}

char my_get_char(char* request){

    char value;
    int status;
    do{
        printf("%s", request);
        status = scanf("%c", &value);
        while(getchar() != '\n');
    } while(status == 0);

    return value;
}

void print_array(int* ptr, int size){       //print function.

    //if the array is empty.
    if (size == 0){
      printf("The array is empty!\n");
      return;
    }
    //if the array has stored elements.
    printf("All elements stored in array:\n");
    for(int i = 0; i < size; i++){
        printf("element in index %i: %i\n", i, *(ptr + i));
    }
}

int* resize(int* ptr, int new_size){        //Resizing function.

    int* temp = realloc(ptr, new_size * sizeof(int));   //we pass two arguments: the current block
    if(temp == NULL){                                        //and size of new block we want.
        printf("There is no space in memory to allocate\n");
        return NULL;
    }                //now we have a new block of memory with different size and stores the old data
    return temp;      //in it so we can set the old pointer to the new block.
}                    //so we return the pointer as ptr is just a copy of the original array pointer.

int append(int* arr, int capacity, int* size_ptr, int number){

    if (*size_ptr == capacity){
        return 1;             //if no space we return 1 to main function.
    }
    *(arr + *size_ptr) = number;
    (*size_ptr)++;            //size is a copy to facilate code and improve readability.
    return 0;                  //if we add number successfully we return 0.
}

int insert(int* arr, int capacity, int* size_ptr, int number, int place){

    if (*size_ptr == capacity){
      return 1;             //if no space we return 1 to main function.
    }

    for(int i = *size_ptr; i > place; i--){
      *(arr + i)= *(arr + i - 1);
    }
    *(arr + place) = number;
    (*size_ptr)++;
    return 0;             //return 0 if we insert element successfully.
}

void delete(int* arr, int* size_ptr, int place){

    for (int i = place; i < *(size_ptr) - 1; i++){         //size - 1 to keep the last value with no change
      *(arr + i) = *(arr + i + 1);                    //and we will ignore it by decreasing the size.
    }
    *(size_ptr) -= 1;
}
