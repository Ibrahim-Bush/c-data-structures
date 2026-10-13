/*
   in this program we explore
   The Singly Linked List which
   is a dynamic data structure
   that organizes elements in a
   non-contiguous memory locations
   and link them by using pointers.
   This architecture provides maximum
   flexibility, dynamic size and
   efficiency in using memory.

      **   The Node Structure   **
   - Each node acts as a container
     consisting of two fields:
     - Data Field: The value being stored.
     - Pointer Field: Stores the address of
       the next node.
      *Pointer space: Each pointer consumes
       an extra space (8-bytes) to maintain
       the connection between nodes.

      **      Key Features      **
   - Dynamic Size: The list grows and shrinks
     dynamically and we do not have to resize it.
   - Non Contiguous (fragmentation):
     It can store elements at any available
     separated places in memory and link them
     by pointers which is an efficient use of memory.
   - Not Identical: Nodes can be designed to
     store different types of data easily.

      **     Basic Advantages    **
   - No Fixed Size: The list do not have fixed
     size, so can add or delete elements at
     any time without having to resize it.
   - Easy insertion and deletion: Modifying
     the list is efficient as it only requires
     updating pointers. We do not have to shift
     elements to insert or delete elements from
     any place in the list O(1).
   - Fragmentation Handling: It can store elements
     at small and distributed places in memory
     and link them by pointers which is an
     efficient use of memory.

      **    Basic Disadvantages    **
   - Memory Cost: Each node requires additional
     space for the pointer that points to the
     next node (8-bytes) which consumes memory.
   - No Random Access: We can not access elements
     directly by index, we must traverse from
     the head pointer to the wanted element which
     is time consuming process O(n).
   - One-Way Traversal: In the singly linked list
     navigation is restricted to a single forward
     direction, we can not access the a previous
     element we must start from the head again.
   */

#include <stdio.h>
#include <stdlib.h>

typedef struct node{

  int data;                   //the data stored in the node.
  struct node* next;          //the pointer for the next node.
} node;

int main(void){

  //initializing the Head pointer of the linked list.
  node* list = NULL;      //we set it to NULL to avoid garbage value.

  //set a node for the new element.
  node* ptr = malloc(sizeof(node));   //allocate space for the node with malloc.
  if (ptr == NULL){                 //we use ptr as a temporary pointer to make a new node.
    return 1;                       //if malloc failed to allocate a space we return.
  }
  ptr->data = 72;               //set the value of element and the pointer with NULL initially.
  ptr->next = NULL;

  //add the new node to the list O(1).
  list = ptr;               //we assign the address of the new node to the head pointer of the list.

  //print the element from the list.
  printf("The first element in the list: %i\n", list->data);

  //set a node for a new element.
  ptr = malloc(sizeof(node));
  if (ptr == NULL){
    return 1;
  }
  ptr->data = 73;
  ptr->next = NULL;

  //add the new node to the end of the list O(n).
  //to add element at the end of the list we have to traverse until the last element and then
  for (node* current = list; current != NULL; current = current-> next){  //add the new element O(n).
    if (current-> next == NULL){     //we iterate until reaching the final element then attach new
      current-> next = ptr;                     //element to the last one by pointers.
      break;
    }
  }

  //print existing elements from the list.
  printf("Elements of the list after appending new element at the end of the list: ");
  for (node* current = list; current != NULL; current = current-> next){
    printf("%i  ", current->data);
  }
  printf("\n");

  //set a node for a new element.
  ptr = malloc(sizeof(node));
  if (ptr == NULL){
    return 1;
  }
  ptr->data = 33;
  ptr->next = NULL;

  //add the new node to the start of the list O(1).
  ptr->next = list;     //first we store the value of the head pointer in the next field of the new
  list = ptr;           //node then we set head to point to the new node O(1).

  //print all elements of the list.
  printf("Elements of the list after adding new element at the start of the list: ");
  for (node* current = list; current != NULL; current = current ->next){  //we make current to avoid
    printf("%i  ", current ->data);                          //changing the head pointer of the list.
  }
  printf("\n");

  //add more 5 elements with a loop at the end of the list O(n).
  int numbers1[] = {23, 45, 64, 47, 31};     //the array of elements we want to add them to the list.
  for (int i = 0; i < 5; i++){              //we iterate 5 times to add all elements.

    //set a node for the new element.
    ptr = malloc(sizeof(node));
    if (ptr == NULL){
      return 1;
    }
    ptr->data = numbers1[i];                //add the value of element from the array.
    ptr->next = NULL;

    //traverse the list until reaching the last element to attach the new node O(n).
    for (node* current = list; current != NULL; current = current-> next){
      if (current -> next == NULL){   //if reaching the last element we set the next pointer of it
        current ->next = ptr;                    //to points to the new node then stop.
        break;
      }
    }
  }

  //print all elements of the list.
  printf("Elements after appending more 5 elements at the end of the list: ");
  for (node* current = list; current != NULL; current = current->next){
    printf("%i ", current->data);
  }
  printf("\n");

  //modify the value of specific elements access O(n), modify O(1).  "value: 45 change to 83 and
  for (node* current = list; current != NULL; current = current ->next){ //"47 to 66 and 31 to 38"
    if (current ->data == 45){
      current->data = 83;
    }else if (current->data == 47){
      current->data = 66;
    }else if (current->data == 31){
      current->data = 38;
    }
  }

  //print all elements of the list.
  printf("Elements after modify values of some elements of the list: ");
  for (node* current = list; current != NULL; current = current->next){
    printf("%i ", current->data);
  }
  printf("\n");

  //delete elements from the middle and end of the list "access O(n) then deletion O(1).
  //"delete elements with values: 72, 23, 38"
  for (node* current = list; current != NULL; current = current->next){
    if (current->next->data == 72 || current->next->data == 23 || current->next->data == 38){
      node* temp = current->next;           //if we want to delete the next element to current one
      current->next = current->next->next;  //we set the next pointer of current to equal the poiner
      free(temp);                           //of the next node that we want to delete only O(1).
    } //we save address of the node we want to delete first to keep track of it then free its memory.
  }                                   //to avoid memory leak.

  //delete first element of the list O(1). (special case as we update the head of the list itself)
  node* tmp = list;      //we save the value of the head before updating it to delete first element
  list = list-> next;     //to free the space of this node later to avoid memory leak.
  free(tmp);

  //print all elements of the list.
  printf("Elements after deleting specific elements of the list: ");
  for (node* current = list; current != NULL; current = current->next){
    printf("%i ", current->data);
  }
  printf("\n");

  //add 5 elements  with a loop at the start of the list O(1).
  int numbers2[] = {44, 87, 43, 77, 39};
  for (int i = 0; i < 5; i++){      //we iterate 5 times to add all elements.

    //we set a node for the new element.
    ptr = malloc(sizeof(node));
    if (ptr == NULL){
      return 1;
    }
    ptr->data = numbers2[i];        //add the value of element from the array.
    ptr->next = NULL;

    //add the node at the start of the list.
    ptr->next = list;       //we set the new node to point to the head of the list then we set
    list = ptr;             //the head pointer to point to the new node.
  }

  //print all elements of the list.
  printf("Elements after prepending elements to the list: ");
  for (node* current = list; current != NULL; current = current->next){
    printf("%i ", current->data);
  }
  printf("\n");

  /*inserting specific elements to the middle of the list "access place O(n), insertion O(1)".
  "insert 10 between 87 and 44" and "insert 20 between 64 and 66" and "insert 30 between 77 and 43"*/
  int numbers3[] = {10, 20, 30};    //the numbers we want to insert.
  int sign_num[] = {87, 64, 77};   //the numbers we will insert after them as it changes every time.
  for (int i = 0; i < 3; i++){
    //make a node for the new element.
    ptr = malloc(sizeof(node));
    if (ptr == NULL){
      return 1;
    }
    ptr->data = numbers3[i];
    ptr->next = NULL;
    //insert nodes in the list.
    for (node* current = list; current != NULL; current = current->next){
      if (current->data == sign_num[i]){
        ptr->next = current->next;    //we set pointer of the new node to equal to the pointer of
        current->next = ptr;          //the previous node then set the pointer of the previous node
      }                               //to points to the new node.
    }
  }

  //print all elements of the list.
  printf("Elements after inserting elements to the middle of the list: ");
  for (node* current = list; current != NULL; current = current->next){
    printf("%i ", current->data);
  }
  printf("\n");

  //freeing the memory allocated for nodes in the list.
  node* current = list;
  while(current != NULL){
    node* temp = current->next;   //we store the pointer to the next node as after freeing the
    free(current);                //current node we cannot access the pointer of it, so we save
    current = temp;               //it in temproary pointer then update current to its value.
  }

  return 0;
}
