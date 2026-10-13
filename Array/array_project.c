/*
   This program is the final and
   most advanced version of our
   professional Dynamic Array System.

     ** The Peak of ARRAYS **
   - we are moving from basic Array
    concepts to building a complete
    and reliable memory management
    system.

       ** The HEAP Power **
   - After seeing the power of using
     the Heap to store our Array in
     the previous program, we will use
     it in this program to take full
     control over the variables Lifetime.
   - The array will not die until we
     decide to destroy it with free().

      **   The STRUCT   **
   - We will build a Struct to gather
     all array variables(ptr, size, capacity)
     and encapsulate them into one single
     unit for better organization.

     **  Pass by Reference  **
   - Instead of wasting memory by copying
     the whole struct, we will pass it
     by reference(pointer) to modify the
     original data directly and efficiently.

     ** The Arrow Operator (->) **
   - We will use the arrow operator (->)
     that combines dereference (*) operation
     and access (.) operation.
   - It automatically performs the dereference
     to the pointer and accesses the specific
     element in one single step.

     **  Complexity Analysis  **
   - Access element by index: O(1).                       "Fast Access time"
   - Append element at last: O(1).
   - Prepend element at first: O(n).                       "costly shifting"
   - Insert element in the middle: O(n).                   "costly shifting"
   - Delete element from the end: O(1).
   - Delete element from the middle: O(n).                 "costly shifting"
   - Delete element from the start: O(n).                  "costly shifting"
   - Resize Array (grow || shrink): O(n).             "costly copying to new place"
   - Update Value of element by index: O(1).
   - Search for element by linear search: O(n).
   - Search for element by binary search: O(log n).
   - Sort elements by Selection sort: O(n^2), Omega (n^2).  "Blind Algorithm"
   - Sort elements by Bubble sort: O(n^2), Omega (n).       "Intelligent Algorithm"

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct array{
    int* data;          //the pointer to array elements.
    int capacity;       //the capacity of the array.
    int size;           //the current number of elements in array.
    int is_sorted;      //the status of sorting, it is useful as we sort array once.
} arr;

int my_get_int(char* request);        //this function to take numbers from the user.
int get_positive_int(char* request);  //this function to get positive integer for index from user.
char my_get_char(char* request);      //this fucnction to take single characters from the user.
arr* init_array(int capacity);        //this function to initialize array variables.
int resize_array(arr* array, int new_cap);      //this function to resize array.
int append(arr* array, int element);       //this function to append element in array.
int insert_at(arr* array, int element, int place); //this function to insert element at specific place.
int insert_at_first(arr* array, int element);   //this function to insert element at the first index.
void update(arr* array, int place, int new_value);  //this function to update element at specific place.
void update_last(arr* array, int new_value);     //this function to update value of the last element.
void print_array(arr* array);         //this function to print all array elements.
void reset_array(arr* array, int init_cap);     //this function to reset array to the initial case.
void delete_at(arr* array, int place);         //this function to delete a specific element by index.
void delete_last(arr* array);                 //this function to delete the last element from array.
void display_info(arr* array);              //this function to display array data(size, capacity).
void display_at(arr* array, int place);     //this function to display number at specific index.
void display_last(arr* array);              //this function to display the last element in array.
void selection_sort(arr* array);            //this function to sort array elements by selection sort.
void bubble_sort(arr* array);      //this function to sort array elements by intelligent bubble sort.
void linear_search(arr* array, int target); //this function to search for specific element by linear search.
void binary_search(arr* array, int target); //this function to search for specific element by binary search.
int binary_search_recursive(arr* array, int first, int last, int target); //if the array is unsorted it sort it first.
void shrink_array(arr* array);  //this function to shrink array memory to fit elements to save memory.
void destroy_array(arr* array);         //this function destroy our array by free its memory.


int main(void){

    //initialize array with init function.
    const int initial_cap = 10;             //store the initial capacity to use it in reset.
    arr* my_array = init_array(initial_cap);
    if (my_array == NULL){      //we check if there is no space for either struct or array
        return 1;                       //data and return 1 if there is no space.
    }
    //inform the user of valid operations on array.
    printf("\nWelcome to Array Mangement System.\n\nWhich operation you want to perform:\n");
    printf("A:append elements            T:insert elements at specific place  F:insert element at first index\n");
    printf("U:update specific elements   X:update value of last element\n");
    printf("D:delete specific elements   Z:delete last element                R:reset array\n");
    printf("P:print all elements         S:display specific elements          Y:display last element\n");
    printf("N:sort array with selection sort  O:sort array with bubble sort   I:display array info\n");
    printf("L:search for element by linear search   B:search for elemnt by binary search\n");
    printf("E:exit the system\n");

    //ask the user to choose operation to perform on array until he exit the system.
    char input;     //we put this variable here to be in the scope of while.
    do{
        //ask the user to enter code of operation.
        input = my_get_char("\nEnter the code of the operation you want to perform: ");
        //append operation.
        if (input == 'A' || input == 'a'){  //get number of elements the user want to append in array.
            int n = get_positive_int("Enter number of elements you want to append: ");
            for(int i = 0; i < n; i++){     //ask the user for n elements values.
                int element = my_get_int("Enter element : ");
                int status = append(my_array, element);    //we get the element then pass it append.
                if(status == 0){      //if the append function returns zero then there is no available
                    break;                     //space even with resizing so we exit the loop.
                }
            }
        }
        //insert elements at specific places.
        else if (input == 'T' || input == 't'){  //ask the user for number of elements he want to insert.
            int n = get_positive_int("Enter number of elements you want to insert: ");
            for (int i = 0; i < n; i++){                       //we get the element and index
                int element = my_get_int("Enter element: ");    //then pass them to insert function.
                int place = get_positive_int("Enter index you want insert in it: ");
                int status = insert_at(my_array, element, place);
                if (status == 0){  //if the append function returns zero then there is no available
                    break;         //space even with resizing so we exit the loop.
                }
            }
        }
        //insert element at first index.
        else if (input == 'F' || input == 'f'){
            int element = my_get_int("Enter element: "); //we get the number then pass it to "insert at first"
            int status = insert_at_first(my_array, element); //function to insert it at first index.
        }
        //update value of specific element.
        else if (input == 'U' || input == 'u'){  //get number of elements he want to update its value.
            int n = get_positive_int("Enter number of elements you want to update them: ");
            for (int i = 0; i < n; i++){
                int place = get_positive_int("Enter index of the element : ");
                int new_value = my_get_int("Enter new value: ");  //get the index of element and the
                update(my_array, place, new_value);     //new value then pass them to update function.
            }
        }
        //update value of the last element.
        else if (input == 'X' || input == 'x'){       //we get the new value from user then pass it to
            int new_value = my_get_int("Enter the new value: ");  //update last function to update the
            update_last(my_array, new_value);                     //value of the last element.
        }
        //delete element at specific place.
        else if (input == 'D' || input == 'd'){     //get number of elements he want to delete.
            int n = get_positive_int("Enter number of elements you want to delete: ");
            for (int i = 0; i < n; i++){   //get the index of element then pass it to delete function.
                int place = get_positive_int("Enter the index of element : ");
                delete_at(my_array, place);     //we call the delete function with the index of element.
                shrink_array(my_array);   //then we call shrink function to check if the array has lots of
            }                             //empty places and shrink it to fit size and save memory.
        }
        //delete last element.
        else if (input == 'Z' || input == 'z'){  //we call delete last function to delete last element
            delete_last(my_array);     //then we call shrink function to check if the array have lots of
            shrink_array(my_array);    //empty places and shrink it to fit size and save memory.
        }
        //reset array.
        else if (input == 'R' || input == 'r'){     //we call the reset function to reset array to the
            reset_array(my_array, initial_cap);     //initial case and remove all elements.
        }
        //print all elements.
        else if (input == 'P' || input == 'p'){     //we call the print function to display all elements
            print_array(my_array);                  //that exist in array.
        }
        //display specific elements.
        else if (input == 'S' || input == 's'){  //we ask the user for number of elements he want
            int n = get_positive_int("Enter number of elements you want to display: "); //to display.
            for (int i = 0; i < n; i++){
                int place = get_positive_int("Enter index of element : ");
                display_at(my_array, place);
            }
        }
        //display last element.
        else if (input == 'Y' || input == 'y'){     //we call the display last function to display
            display_last(my_array);                 //the last element in the array.
        }
        //display array info.
        else if (input == 'I' || input == 'i'){     //we call the display info function to print
            display_info(my_array);                 //information about array.
        }
        //sort array with selection sort.
        else if (input == 'N' || input == 'n'){    //we call the selection sort function and it
            selection_sort(my_array);               //does not have a return value.
        }
        //sort array with bubble sort.
        else if (input == 'O' || input == 'o'){    //we call the bubble sort function and it does not
            bubble_sort(my_array);                  //have a return value.
        }
        //search for element by linear search.
        else if (input == 'L' || input == 'l'){     //we take the value and pass it to linear search
            int element = my_get_int("Enter number you want to search for it: ");   // function.
            linear_search(my_array, element);
        }
        //search for element by binary search.
        else if (input == 'B' || input == 'b'){  //we take the value of element and pass it to binary
            int element = my_get_int("Enter number you want to search for it: ");  //search function.
            binary_search(my_array, element);
        }
        //exit the system.
        else if (input == 'E' || input == 'e'){
            printf("Exit the array management system\n");
        }
        //invalid input.
        else{               //if the user enters invalid character we notify him.
            printf("Invalid input! Try again\n");
        }

    } while(input != 'E' && input != 'e');  //we exit loop when user exit the system by enter 'E' or 'e'.

    destroy_array(my_array);        //call destroy function to free memory allocated.
    return 0;
}

int my_get_int(char* request){      //this function to get valid integer from user.

    int value;              //we put variables here to be in the scope of condition and return.
    int status;
    do{
        printf("%s", request);
        status = scanf("%i", &value);   //scanf prints a new line automatically.
        while(getchar() != '\n');    //cleaning the buffer from garbage input or '\n' at every trial.
    } while(status == 0);           //we check the return value of scanf as it return zero if the
                                    //user entered invalid input and repeat until get valid one.
    return value;
}

int get_positive_int(char* request){

    int value;          //we put variable here to be in the scope of while.
    do{
        value = my_get_int(request);    //we call my_get_int until return positive number.
    } while(value < 0);

    return value;           //return valid positive integer.
}

char my_get_char(char* request){      //this function to get valid character from user.

    char value;              //we put variables here to be in the scope of condition and return.
    int status;
    do{
        printf("%s", request);
        status = scanf("%c", &value);
        while(getchar() != '\n');   //cleaning the buffer from garbage input or '\n' at every trial.
    } while(status == 0);           //we check the return value of scanf as it return zero if the
                                    //user entered invalid input and repeat until get valid one.
    return value;
}

arr* init_array(int capacity){

    arr* array = malloc(sizeof(arr));   //we allocate space for the struct itself first.
    if (array == NULL){
        return NULL;
    }
    array -> data = malloc(capacity * sizeof(int));     //we allocate space for the array data.
    if(array -> data == NULL){
        free(array);            //if there is no space for the array data we return NULL after
        return NULL;            //freeing the struct as its useless, there is no space for array.
    }
    array -> capacity = capacity;
    array -> size = 0;
    array -> is_sorted = 0;
    //if we make the struct itself in stack it will die at the end of this function.
    return array;
}

int resize_array(arr* array, int new_cap){

    int* temp = realloc(array -> data, new_cap * sizeof(int));
    if (temp != NULL){         //we put return value in temp variable as if realloc does not found
        array -> data = temp;  //any space it return NULL and we will lose the pointer to the old
        array-> capacity = new_cap;               //space.
        return 1;
    }else{
        return 0;               //we return zero if resize did not succeed.
    }
}

int append(arr* array, int element){

    //we try to append element and if the array is full we try to resize it. If resize failed we tell
    //the user that the appened failed.
    if (array -> size < array -> capacity){
        array -> data[array -> size] = element;
        array -> size++;
        printf("element appended successfully\n");
        array-> is_sorted = 0;      //change the value of is_sorted as user can add unsorted numbers.
        return 1;
    }else{
        int status = resize_array(array, (array -> capacity) + 10);
        if (status == 1){                   //after resizing we call the function again to append
            return append(array, element);  //element and return its return value.
        }else{                              //if resize failed we cannot add element and return zero.
            printf("Failed to append element! there is no space available to add more elements\n");
            return 0;   //we return zero only if there is no space to add elements even with resize.
        }
    }
}

int insert_at(arr* array, int element, int place){

    //we try to insert element and if the array is full we try to resize it. if resize failed we tell
    //the user that the insertion failed.

    if (place > array -> size){     //if the place is beyond the last index we cannot insert here.
        printf("cannot insert in this place. Elements must be in sequential order\n");
        return 1;                           //user error not error from our program so we return 1.
    }else if( place == array->size){            //if the place is the next one to last element we
        return append(array, element);       //call the append function and return its return value.
    }else{
        if(array-> size < array-> capacity){    //we check if the array is full, if not we insert.
             for(int i = array -> size; i > place; i--){    //we shift all elements after the palce
                 array -> data[i] = array->data[i - 1];     //one step to the right.
             }
             array->data[place] = element;        //we add element in index place then increase size.
             array->size++;
             printf("element Inserted successfully\n");
             array-> is_sorted = 0;      //change the value of is_sorted as user can add unsorted numbers.
             return 1;
        }else{                  //if the array is full we try to resize it first.
            int status = resize_array(array, array->capacity + 10);
            if(status == 1){
                return insert_at(array, element, place); //after resizing we call the function again
            }else{                                      //to insert the element after resizing.
                printf("Insert failed! there is no available space to add more elements\n");
                return 0;      //if resizing failed we cannot insert element and we return zero.
            }
        }
    }
}

int insert_at_first(arr* array, int element){
    int place = 0;
    return insert_at(array, element, place);   //call inset function and pass index zero and return
}                                                              //its return value.

void update(arr* array, int place, int new_value){
    //update the value of specific element using its index.
    if (array->size == 0){              //if the array is empty there is no elements to update.
        printf("The array is empty! There is no elements to update.\n");
        return;
    }
    if (place >= array-> size){     //if the index is out of size range there is no element to update.
        printf("there is no element in this place to update its value\n");
    }else{
        array-> data[place] = new_value;    //update the value of element in constant time by index.
        printf("element updated successfully\n");
        array-> is_sorted = 0;      //change the value of is_sorted as user can add unsorted numbers.
    }
}

void update_last(arr* array, int new_value){

    int place = (array->size - 1);      //this function call update function with the last index.
    update(array, place, new_value);
}

void print_array(arr* array){
    //if the array is empty.
    if (array->size == 0){
        printf("The array is empty!\n");
        return;
    }
    //else, print all existing elements and use size to stop the loop.
    printf("All Array elements\n");
    for(int i = 0; i < array-> size; i++){
        printf("Element in index %i: %i\n", i, array->data[i]);
    }
}

void reset_array(arr* array, int init_cap){

    int status = resize_array(array, init_cap);    //return array capacity to initial case.
    if (status == 1){
        array-> capacity = init_cap;    //return capacity to initial capacity.
        array-> size = 0;       //return size to zero makes the array empty.
        array-> is_sorted = 0;  //return sort case to unsorted.
        printf("Array is reseted successfully\n");
    }else{
        printf("reset failed\n");
    }
}

void delete_at(arr* array, int place){

    if (array->size == 0){               //if the array is empty there is no elements to delete.
        printf("The array is empty! There is no elements to delete.\n");
        return;
    }
    if (place >= array-> size){         //if the user entered a place after the last element.
        printf("There is no element in this place!\n");
    }else{
        //we move all elements after the place one step to the left to keep them in sequential order.
        for(int i = place; i < (array-> size - 1); i++){    //we put condition (i < sizen-1) as we
            array->data[i] = array->data[i + 1];            //put the element (i + 1) in index i to
        }                                           //avoid putting garbage value in the last index.
        array->size--;      //decreases the value of size after deleting element.
        printf("Element deleted successfully\n");
    }
}

void delete_last(arr* array){

    int place = (array->size - 1);      //this function call dalete_at function with the last index.
    delete_at(array, place);
}

void display_info(arr* array){

    printf("The capacity of array: %i\n", array-> capacity);    //print current capacity of the array.
    printf("The current number of elements in array: %i\n", array-> size);  //print current size.
    printf("The last element in array exist in index: %i\n", (array->size) - 1);  //print index of last element.
    if(array->is_sorted == 1){
        printf("The array is sorted\n");    //print the array status (sorted or unsorted).
    }else{
        printf("The array is unsorted\n");
    }
}

void display_at(arr* array, int place){
    //this function to print the value of specific element with its index.
    if (array->size == 0){
        printf("The array is empty! There is no elements to display.\n");
        return;         //if size equals zero there is no elements in array so we return.
    }
    if (place >= array->size){      //if place is out of size range there is no element in this place.
        printf("There is no element in this place\n");
    }else{                      //access the element in constant time by its index and print its value.
        printf("The element in this place is: %i\n", array->data[place]);
    }
}

void display_last(arr* array){
    int place = (array->size - 1);      //this function calls display_at function with the last index.
    display_at(array, place);
}

void selection_sort(arr* array){

    if (array -> size <= 1){            //if the array has one or zero elements it is sorted.
        printf("The Array is sorted\n");
        array-> is_sorted = 1;
        return;
    }else{

        for(int i = 0; i < (array-> size - 1); i++){
            int min_index = i;        //we initialize min_index with the first one of unsorted part.

            for (int j = i + 1; j < array-> size; j++){
                if (array->data[j] < array->data[min_index]){
                    min_index = j;  //we store the index of minimum number to do one swap at the end.
                }
            }
            //swap the current element we sort it with the minimum number in the unsorted list.
            int temp = array->data[i];
            array->data[i] = array->data[min_index];
            array->data[min_index] = temp;
        }

        printf("Array is sorted successully\n");
        array-> is_sorted = 1;        //change the value of is_sorted variable after sorting arrary.
        return;
    }
}

void bubble_sort(arr* array){

    if (array-> size <= 1){              //if the array is empty or has only one element then the
        printf("The array is sorted\n"); //array is sorted and we return after assign 1 to is_sorted.
        array -> is_sorted = 1;
        return;
    }else{

        for (int i = 0; i < (array->size - 1); i++){    //this the intelligent condition which
            int swaps = 0;                              //calculate number of swaps in full cycle.
            for (int j = (array->size - 2); j >= i; j--){
                if (array->data[j + 1] < array->data[j]){   //swap numbers to catch the samllest
                    int temp = array->data[j];              //number to the sorted part.
                    array->data[j] = array->data[j + 1];
                    array->data[j + 1] = temp;

                    swaps++;          //increase number of swaps in each swap time.
                }
            }
                            //if we do not make any swap in the full cycle then the array is sorted.
            if(swaps == 0){
                printf("The array is sorted successfully\n");
                array-> is_sorted = 1;
                return;
            }
        }

        printf("The array is sorted successfully\n");
        array-> is_sorted = 1;      //change the value of is_sorted variable to be 1.
        return;
    }
}

void linear_search(arr* array, int target){

    if (array-> size == 0){                 //if the array is empty there is no elements to search
        printf("The array is empty\n");     //for target in them.
        return;
    }else{
        for(int i = 0; i < array->size; i++){   //we search for element in each index from zero to
            if(array->data[i] == target){       //(n-1) and if we find it we stop.
                printf("Element found in index: %i\n", i);
                return;
            }
        }
        printf("Element Not Found\n");          //if the loop ends without finding element then
    }                                           //it is not in the array.
}

void binary_search(arr* array, int target){

    if (array-> size == 0){                   //if the array is empty, there is no elements.
        printf("The array is empty\n");
        return;
    }else{
        if (array -> is_sorted == 0){   //if the array is unsorted we sort it first.
            bubble_sort(array);       //we choose bubble sort as if the user entered sorted elements
        }                            //bubble sort will do less steps as it is intelligent algorithm.
        //this the actual binary search recursive that apply recursion in searching.
        int place = binary_search_recursive(array, 0, (array->size - 1), target);
        if (place == -1){
            printf("Element Not Found\n");
        }else{
            printf("Element found in index: %i\n", place);
        }
    }
}

int binary_search_recursive(arr* array, int first, int last, int target){

    if (first == last){                         //base case if there is one element remaining.
        if (array->data[first] == target){
            return first;
        }else{
            return -1;
        }
    }else if (last < first){        //if the last becomes less than first then element not found.
        return -1;
    }else{

        int middle = (first + last)/2;  //calculate middle index at each time.
        //check the three cases.
        if(array-> data[middle] == target){         //Case 1: target equalls middle.
            return middle;
        }else if(target < array-> data[middle]){    //Case 2: target is smaller than middle.
            return binary_search_recursive(array, first, middle - 1, target);
        }else{                                      //Case 3 target is greater than middle.
            return binary_search_recursive(array, middle + 1, last, target);
        }
    }
}

void shrink_array(arr* array){     //this function to shrink array memory to fit size and save memory.
    if (array->capacity <= 20){     //if the capacity is less than or equal 20 its not necessary
        return;                                       //to shrink its space
    }
    if (array->capacity > (array->size * 2)){   //if more than the half of the array is empty it will
        int status = resize_array(array, (array->size + (array->size / 2)));
        if (status == 1){                       //shrink to have only more half of size empty places.
            printf("array shrinked successfully to fit size and save memory\n");
        }           //if the reallocation succeeded we print that the array is shrinked.
    }     //we leave more space to save time as realloc takes O(n) to move elements to another place.
}

void destroy_array(arr* array){

    if (array != NULL){         //we check array as we access the data pointer in this place.
         free(array-> data);     //order is important if we free my_array first we will lose
         free(array);             //the data pointer and cause memory leak.
    }
}
