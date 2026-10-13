/*
   in this program we learn about
   array as a data structure that
   allows storing multiple values
   of the same type. we explore its
   behavior in memory and how to
   manage it manually.

   Basic features of Array:
   - Fixed Size: we cannot change the
     size of array after allocating it.
   - Identical: all elements in array
     must be of the same type.
   - Sequential: elements are stored in
     contiguous memory places with no
     gaps among them.

   Basic advantage of Array:
   - Fast access: the main advantage
     is the unbeatable speed O(1) when
     access a specific element with
     its index, as data is stored in
     contiguous memory, allowing the
     CPU to calculate addresses instantly.

   Basic disadvantages of Array:
   - Manual Resizing: to grow the size of
     array, we must create a new bigger
     array and move data element by element
     to it, which costs O(n) time.
   - Type Restriction: we cannot store
     elements of different types in the same
     array, as it is identical.
   - Sequential Storage: this property causes
     many negatives:
      - Space issue: since arrays must be
        stored in contiguous memory, it can
        be hard to find enough space for a
        very large array even if there is
        free memory available in different
        separate locations.
      - Shifting Cost: if we want to insert
        or delete an element in the middle
        we must shift all following elements
        to maintain the sequential order.
        making the operation time consuming O(n).
*/

#include <stdio.h>

int main(void){

    int capacity = 10;          //to store the capacity of array.
    int arr[capacity];          //making array of size capacity.
    int size = 0;               //to store current number of elements in array.

    //store elements in array.
    for(int i = 0; i < 5; i++){     //store 5 elements in array.
        arr[i] = i + 1;
        size++;                 //increasing the size after each addition process.
    }

    //print stored elements.
    printf("\nelements stored in array:\n");
    for(int i = 0; i < size; i++){      //using the size to stop the printing process.
        printf("element in index %i: %i\n", i, arr[i]);
    }
    printf("\n");

    //modifying elements using index.
    arr[0] = 11;                   //we access elements in constant time using index O(1).
    arr[2] = 12;
    arr[4] = 14;

    //adding more elements to array until filling it.
    for(int i = size; i < capacity; i++){           //we start adding after the last element
        arr[i] = i + 1;                             //existing in array.
        size++;             //we increase size in each addition process, but this does not affect
    }                 //the initialization of i as it is initialized once before starting the loop.

    //print all existing elements in array.
    printf("Array after adding more elements to make array full:\n");
    for(int i = 0; i < size; i++){
        printf("element in index %i: %i\n", i, arr[i]);
    }

    //modifying all elements using indices.
    for(int i = 0; i < size; i++){
        arr[i] += 5;
    }

    //print all existing elements in array.
    printf("\nArray after modifying all elements:\n");
    for(int i = 0; i < size; i++){
        printf("element in index %i: %i\n", i, arr[i]);
    }

    //now, we cannot add any element in array as the array is full.
    //if we want to add extra elements we must RESIZE array to be able to store more elements.

    //resizing array O(n).
    //array is fixed size so if we want to resize array, we have to create a new bigger array
    //and copy existing elements from the old array to the new one, then add extra elements.
    //this operation is time consuming O(n).

    capacity += 10;                   //increasing capacity to be the new array capacity.
    int new_arr[capacity];              //create a new array of increased capacity.
    int new_size = 0;                       //the size of the new array.

    //copying existing data from the old array to the new one.
    for(int i = 0; i < size; i++){      //using the old array size to stop the loop.
        new_arr[i] = arr[i];
        new_size++;
    }  //now, we have a new array with increased capacity and store the old data in it, and we can
        //add extra elements in it and we do not need the old array any more.
        //we can not set old array pointer to the new one because in C array is a const pointer
        //points to a specific place in memory and we cannot change its value after allocation.

    //add extra elements to the increased-capacity array.
    for(int i = new_size; i < capacity; i++){
        new_arr[i] = i + 6;
        new_size++;        //it do not affect initialization as it is performed once before the loop.
    }

    //print all elements in the new array.
    printf("\nelements in the new array after resizing:\n");
    for(int i = 0; i < new_size; i++){
        printf("element in index %i: %i\n", i, new_arr[i]);
    }

    //if we want to delete element from the middle of the array we have to shift all elements that
    //lies after this place to keep sequential order of elements, this process is consuming O(n).

    //delete the element in index 9 from array.
    //we set the value of each element after the index to be the value of the next one and the last
    //element is left and considered as garbage value by decreasing the size to ignore the last element.
    for(int i = 9; i < new_size - 1; i++){                //Time complexity: O(n).
      new_arr[i] = new_arr[i + 1];
    }
    new_size--;         //decreasing number of elements by one.

    //print elements after deleting the element.
    printf("\nelements after deleting the element at index 9:\n");
    for(int i = 0; i < new_size; i++){
      printf("element in index %i: %i\n", i, new_arr[i]);
    }

    //if we want to insert an element in the middle of array we must shift elements to make a space
    //for the element we want to insert.

    //insert an element in index 7.
    //we set the value of each element after the index to be the value of the previous index and
    //the index itself is set to the new element.
    for(int i = new_size; i > 7; i--){                  //Time complexity: O(n).
      new_arr[i] = new_arr[i - 1];
    }
    new_arr[7] = 33;
    new_size++;

    //print elements after inserting the element.
    printf("\nelements after inserting element at index 7:\n");
    for(int i = 0; i < new_size; i++){
      printf("element in index %i: %i\n", i, new_arr[i]);
    }

    return 0;
}
