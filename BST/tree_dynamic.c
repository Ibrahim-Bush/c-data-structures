/*
   This program presents an interactive and dynamic
   implementation of a Binary Search Tree (BST)
   data structure. Building on the basic structure,
   it introduces tools to check tree properties,
   verify tree correctness, and find relationships
   between nodes. The main focus in this program is 
   real-time user interaction, strong input validation,
   and runtime tree analysis.

    **      The Major Disadvantage of Standard BST      **
  
   - The major disadvantage of a standard Binary Search Tree
     is that it can be reduced to a singly linked list in
     the worst-case scenario. If the user enters numbers
     that are already sorted in ascending or descending order,
     the tree becomes completely unbalanced. When this linear
     structure occurs, the hierarchical benefit is lost, and 
     all basic operations like search, insertion, and deletion
     slow down, forcing the system to perform at O(n) efficiency.

    **             New Structural Additions             **

   - Advanced Node Tracking:
     Introduces functions to look up node relationships by
     finding the immediate parent of a specific value and
     calculating the exact depth (the number of edges from root)
     for any given element.
   - Tree Validation:
     Features a validation tool that scans the entire structure
     to confirm that the mathematical sorting rules of a BST
     are perfectly preserved across all subtrees.
   - Operational Status Tracking:
     Core operations are enhanced to return explicit status codes
     such as success, duplicate value, or missing element to
     safely track structural updates during runtime.
   - Value Queries:
     Adds direct access to locate the absolute minimum and
     maximum values currently stored within the tree structure.

    **             Layout and Memory Control             **

   - Visual Tree Layout:
     Prints the tree shape from left to right using clear
     level-based spaces, making the hierarchical branches
     visible on the screen.
   - Structural Reset:
     Safely clears all existing nodes from memory to empty
     the tree layout while keeping the main container ready
     for new data.
   - Full Tree Destruction:
     Ensures a complete memory cleanup by recursively freeing
     every allocated node from the heap when the program ends.

    **                    Program Goal                    **

   - The objective of this intermediate program is to build
     a highly stable and interactive interface around our
     binary search tree mechanics. By managing live, 
     unpredictable user behavior and providing immediate
     structural feedback, this version ensures our fundamental
     pointer logic is completely solid in all possible cases.

    **                   Time Complexity                   **

   - Insert new element into the tree:             Average(log n), O(n).
   - Delete specific element from the tree:        Average(log n), O(n).
   - Search for specific element in the tree:      Average(log n), O(n).
   - Find the smallest element in the tree:        Average(log n), O(n).
   - Find the largest element in the tree:         Average(log n), O(n).
   - Get the depth of specific node in the tree:   Average(log n), O(n).
   - Get the parent of specific node in the tree:  Average(log n), O(n).
   - Get the current size of the tree:                    O(1).                "Thanks to size entity"
   - Test the sorting rules all over the tree:             O(n).            "Requires checking all subtrees"
   - Display all elements of the tree:                     O(n).            "Requires access to all elements"
   - Reset the tree to the initial state:                  O(n).               "Requires freeing all nodes"
   - Destroy the tree at the end of program:               O(n).               "Requires freeing all memory"

   ** When the Binary Search Tree reduces to a Singly Linked List, the system loses its hierarchical advantages
      and is forced to operate at O(n) time complexity for most core operations. This architectural shift
      completely eliminates the optimized logarithmic search paths, heavily reducing the overall efficiency
      of the data structure to O(n) time complexity.
   */

#include <stdio.h>
#include <stdlib.h>

typedef struct node{

    int data;                   //the data stored in the node.
    struct node* left;          //the pointer to the left child of the node.
    struct node* right;         //the pointer to the right child of the node.
} node;

typedef struct{

    node* root;                 //the pointer to the root of the tree.
    int size;                   //the current size of the tree.
} BST;

//input functions.
int get_int(char* request);                         //this function to get an integer value from the user.
void display_template();                    //this function to display the valid operations to perform on the tree.

//BST functions.
BST* init_tree();                                        //this function to initialize a new BST.
node* create_node(int value);                   //this function to create a new node for the given element.
int insert_into(BST* tree, node* ptr);          //this function to insert a new node into the tree structure.
int insert_recursive(node* root, node* ptr);    //this helper function to find the correct position to insert a node.
int delete(BST* tree, int target);              //this function to delete a specific element from the tree.
node* delete_recursive(node* root, int target, int* success_ptr); //this function to find the correct replacement for the deleted node.
int search_for(node* root, int target);         //this function to search for specific element in the tree.
int find_smallest(node* root, int* value_ptr);  //this function to find the smallest element in the tree.
int find_largest(node* root, int* value_ptr);   //this function to find the largest element in the tree.
int check_node(node* ptr, int* value_ptr);      //this function to get the number of children of specific node.
int is_empty(BST* tree);                        //this function to check whether the tree is empty or not.
int get_size(BST* tree);                        //this function to get the current size of the tree.
int get_depth(node* root, int target, int* value_ptr); //this function to get the depth of a specific element in the tree.
int get_parent(node* root, int target, int* value_ptr);//this function to get the parent of a specific element in the tree.
void validate_tree(node* root, int* result_ptr);//this function to check the ordering rules for all subtrees in the tree.
void display_ordered(node* root);               //this function to display all elements of the tree in the correct order.
void display_tree_shape(node* root, int space); //this function to display all elements in a tree layout.
void clear_tree(BST* tree);                     //this function to reset the tree to the initial state.
void destroy_tree(BST* tree);                   //this function to free all memory allocated for the tree to destroy it.
void destroy_recursive(node* root);             //this helper function to free all nodes of the tree recursively.

int main(void){

  //initialize new BST.
  BST* my_tree = init_tree();
  if (my_tree == NULL){
    return 1;             //if the function fails to allocate space for a new tree, we exit the program.
  }
  //welcome the user and display operations template.
  printf("\nWelcome to Binary Search Tree (BST) management system.\n\n");
  display_template();

  //ask the user for the code of desired operation.
  int code;
  do{
    code = get_int("\nEnter the code of the operation you want to perform: ");
    //check code to perform the desired operation.
    if (code == 1){     //Insertion process.
      int number = get_int("Enter the number of elements you want to insert: ");
      for (int i = 0; i < number; i++){     //iterate number of times to take elements and insert them.
        int value = get_int("Enter value of element you want to insert: ");   //get the value of element.
        node* ptr = create_node(value);       //create a new node for the element.
        if (ptr == NULL){
          destroy_tree(my_tree);
          return 1;   //if the function fails to allocate space for a new node, we free all memory and exit program.
        }
        //insert the new node with insertion function.
        int status = insert_into(my_tree, ptr);
        if (status == 1){       //if the function insert the node successfully, it returns one.
          printf("Element inserted successfully into the tree.\n");
        }else{              //else if the element is already stored in the tree it returns zero.
          printf("This element is already stored in the tree!\n");
        }
      }
    }else if (code == 2){     //Deletion process.
      int number = get_int("Enter the number of elements you want to delete from the tree: ");
      for (int i = 0; i < number; i++){           //iterate number of times to take values and delete them.
        int target = get_int("Enter value of element you want to delete: ");   //get the value of the element.
        int status = delete(my_tree, target);       //delete the element with deletion function.
        if (status == 1){     //if the function deleted the target successfully it return one.
          printf("Element: %i deleted successfully from the tree.\n", target);
        }else{            //else if the function returns zero then element not found in the tree.
          printf("This element does not exist in the tree!\n");
        }
      }
    }else if (code == 3){   //Searching process.
      int target = get_int("Enter the element you want to search for in the tree: ");  //get value of the target.
      int status = search_for(my_tree->root, target);       //search for the target with search function.
      if (status == 1){         //if the element is found in the tree the function returns one.
        printf("Element: %i found in the tree.\n", target);
      }else{                //else if the element is not found in the tree the function returns zero.
        printf("This element does not exist in the tree.\n");
      }
    }else if (code == 4){   //Get size process.
      int size = get_size(my_tree);     //get current size with get size function.
      if (size == 0){       //if the current size is zero, the tree is empty.
        printf("The tree is empty! There is No elements stored in the tree.\n");
      }else{                //else display current size.
        printf("The current number of elements stored in the tree is: %i\n", size);
      }
    }else if (code == 5){     //Get Smallest process.
      int value;      //this variable to store the smallest element.
      int status = find_smallest(my_tree->root, &value);   //get the smallest element with find smallest function.
      if (status == 1){       //if the function returns one, then the value passed successfully.
        printf("The value of the smallest element stored in the tree is: %i\n", value);
      }else{                  //else if the function returns zero the tree is empty.
        printf("The tree is empty! There is No elements stored in the tree.\n");
      }
    }else if (code == 6){     //Get Largest process.
      int value;    //this variable to store the largest element.
      int status = find_largest(my_tree->root, &value);     //get the largest element with find largest function.
      if (status == 1){       //if the function returns one then the value passed successfully.
        printf("The value os the largest element stored in the tree is: %i\n", value);
      }else{                  //else if the function returns zero then the tree is empty.
        printf("The tree is empty! There is No elements stored in the tree.\n");
      }
    }else if (code == 7){     //Get depth process.
      int value = get_int("Enter value of the element you want to get its depth: ");
      int depth = 0;         //this variable to store the value of the depth.
      int status = get_depth(my_tree->root,value, &depth);      //get the depth with get depth function.
      if (status == 1){     //if the function passed the depth successfully, it returns one.
        printf("The depth of this element (number of edges from root to node) is: %i\n", depth);
      }else{              //else if the function returns zero, then the element is not found.
        printf("This element does not exist in the tree.\n");
      }
    }else if (code == 8){   //Get Parent process.
      int value = get_int("Enter value of element you want to get its parent node: ");
      int parent;         //this variable to store the value of the parent.
      int status = get_parent(my_tree->root, value, &parent);      //get the parent with get parent function.
      if (status == 1){       //if the function found the target successfully it returns one.
        printf("The value of the parent node of this element is: %i\n", parent);
      }else if (status == 2){   //else if the function returns (2) then it is the root node.
        printf("This element is the root of the tree! The root does not have parent!\n");
      }else{            //else if the function returns zero then the element does not exist in the tree.
        printf("This element does not exist in the tree.\n");
      }
    }else if (code == 9){     //Inorder display.
      display_ordered(my_tree->root);     //display elements in order with display ordered function.
    }else if (code == 10){    //Display Tree Layout.
      display_tree_shape(my_tree->root, 0);     //display tree layout and pass zero as initial identation.
    }else if (code == 11){    //Check Tree Rules.
      int result = 1;       //this variable to store the result of testing and initialize it with one.
      validate_tree(my_tree->root, &result);      //test the tree with validate tree function.
      if (result == 1){       //if the result still one then the tree is perfectly meets rules.
        printf("The Sorting Rules are maintained all over the BST and all subtrees of the tree.\n");
      }else{                  //else if the result becomes zero then the rules is violated.
        printf("The BST does not perfectly apply the sorting rules to all parts!\n"); 
        printf("There are some parts that does not follow the rules!\n");
      }
    }else if (code == 12){    //Reset process.
      clear_tree(my_tree);                      //reset the tree with reset function.
      printf("The tree reseted successfully to the initial state.\n");
    }else if (code == 13){     //Display template process.
      display_template();
    }else if (code == 14){
      printf("Exit the system.\n");
    }else{                      //Invalid input.
      printf("Invalid input! Enter (13) to check operations template.\n");
    }
  } while(code != 14);        //iterate until the user enters exit code (14).

  destroy_tree(my_tree);      //free all memory allocated for the tree to avoid memory leak.
  return 0;
}

int get_int(char* request){

  int value;            //this variable to store the input value.
  int status;           //this variable to store the return value of scanf to check it.
  do{
    printf("%s", request);          //print request to ask the user for input.
    status = scanf("%i", &value);   //get the user input with scanf.
    while(getchar() != '\n');       //clear the buffer from garbage value or '\n'.
  } while (status == 0);      //iterate until scanf gets a valid input as it returns zero in case of failure.

  return value;
}

void display_template(){
  //display all valid operations to perform on the tree.
  printf("These are the codes of the valid operations to perform on the BST:\n");
  printf("1.Insert new elements into the tree.              2.Delete specific element from the tree.\n");
  printf("3.Search for specific element in the tree.        4.Get the current size of the tree.\n");
  printf("5.Get value of the smallest element in the tree.  6.Get value of the largest element in the tree.\n");
  printf("7.Get depth of a specific element from the root.  8.Get value of the parent of a specific element.\n");
  printf("9.Display elements of the tree in correct order.  10.Display all elements in a tree layout.\n");
  printf("11.Check the BST sorting rules for all subtrees.  12.Reset the tree to the initial state.\n");
  printf("13.Display template of the valid operations.      14.Exit the system.\n");
}

BST* init_tree(){

  BST* tree = malloc(sizeof(BST));       //allocate space for a new BST container.
  if (tree == NULL){
    return NULL;        //if the function fails to allocate space for the tree it returns NULL.
  }
  //initialize tree variables.
  tree->root = NULL;
  tree->size = 0;

  return tree;
}

node* create_node(int value){

  node* ptr = malloc(sizeof(node));         //allocate space for a new node.
  if (ptr == NULL){
    return NULL;        //if the function fails to allocate sapce for the node it returns NULL.
  }
  //initialize node variables.
  ptr->data = value;
  ptr->left = NULL;
  ptr->right = NULL;  

  return ptr;
}

int insert_into(BST* tree, node* ptr){
  //if the tree is empty.
  if (is_empty(tree) == 1){
    //the new node becomes the new root of the tree.
    tree->root = ptr;
    tree->size++;
    return 1;             //return (1) to tell that the insertion succeeded.
  }else{    //else if the tree has stored elements.
    int result = insert_recursive(tree->root, ptr); //call helper function to find the correct position for new node.
    if (result == 1){
      tree->size++;       //if the insertion succeeded, increase size by one.
    }
    return result;       //return result to tell the result of insertion process.
  }
}

int insert_recursive(node* root, node* ptr){
  //if the value of new element equal the root value.
  if (root->data == ptr->data){
    free(ptr);     //free the new node as we will not insert it into the tree to avoid memory leak.
    return 0;       //return zero to tell that this element is already stored in the tree.
  }else if (root->data > ptr->data){    //else if new value is samller than current root.
    //if there is no left child for the current root.
    if (root->left == NULL){
      root->left = ptr;       //the new node becomes the left child of the current root.
      return 1;           //return (1) to tell that the node inserted successfully.
    }else{      //else if the current root has left child.
      return insert_recursive(root->left, ptr);   //call the function recursively with the left pointer.
    }
  }else{    //else if the new value is larger than the current root.
    //if there is no right child for the current root.
    if (root->right == NULL){
      root->right = ptr;      //the new node becomes the new right child of the current root.
      return 1;                   //return (1) to tell that element inserted successfully.
    }else{      //else if the current root has right child.
      return insert_recursive(root->right, ptr);    //call the function recursively with the right pointer.
    }
  }
}

int delete(BST* tree, int target){

  int success = 0;      //this variable works as a flag to know whether deletion succeed or element not found.
  //call helper function to delete target and find the correct replacement to maintain ordering rules of the tree.
  tree->root = delete_recursive(tree->root, target, &success);
  if (success == 1){
    tree->size--;     //if deletion succeeded we decrease size by one.
  }
  return success;   //return value of success flag to tell whether the deletion succeeded or not.
}

node* delete_recursive(node* root, int target, int* success_ptr){
  //if the current root equals NULL, there is no elements to delete.
  if (root == NULL){
    return NULL;
  }else if (root->data == target){    //if the current root is target.
    //First: check number of children of target.
    int child_num;      //this variable to store number of children of the node.
    int status = check_node(root, &child_num);
    //we have three cases to handle based on number of children.
    if (child_num == 0){      //Case 1: the target has no children.
      free(root);           //free the target and pass success value then return NULL as there is no replacement.
      *success_ptr = 1;
      return NULL;
    }else if (child_num == 1){    //Case 2: the target has one child.
      node* temp;       //this pointer to store the address of the child.
      if (root->left == NULL){
        temp = root->right;     //check whether the node has right or left child and store its address.
      }else{
        temp = root->left;
      }
      free(root);        //free the target and pass success value then return the address of the child,
      *success_ptr = 1;                //as it will be the replacement of the deleted node.
      return temp;
    }else{                    //Case 3: the target has two children.
      int replacement;      //this variable to store the replacement value.
      int status = find_smallest(root->right, &replacement);  //find the smallest value at the right subtree.
      root->data = replacement;     //make the target equals the replacement value.
      //then call the delete function to delete the duplicate value and make this process pass the success value;
      root->right = delete_recursive(root->right, root->data, success_ptr);
      return root;      //return the same address as the replacement is stored at the same address.
    }
  }else if (root->data > target){     //else if the current root is bigger than the target.
    root->left = delete_recursive(root->left, target, success_ptr);
    return root; //call delete function recursively with the left pointer and return root as it is not the target.
  }else{              //else if the current root is smaller than the target.
    root->right = delete_recursive(root->right, target, success_ptr);
    return root; //call delete function recursively with the right pointer and return root as it is not the target.
  }
}

int search_for(node* root, int target){
  //if the current root is NULL.
  if (root == NULL){
    return 0;         //return zero to tell that the target not found in the tree.
  }else if (root->data == target){    //else if current node is the target.
    return 1;         //return (1) to tell that the target is found in the tree.
  }else if (root->data > target){     //else if current node is bigger than target.
    return search_for(root->left, target); //call search function recursively with the left pointer.
  }else{      //else if the current node is smaller than the target.
    return search_for(root->right, target); //call search function recursively with the right pointer.
  }
}

int find_smallest(node* root, int* value_ptr){
  //if the root is NULL.
  if(root == NULL){
    return 0;       //return zero to tell that the tree is empty.
  }else if (root->left == NULL){      //else if the current root does not have left child.
    *value_ptr = root->data; //pass the value of the root and return (1) to tell that the value passed successfully.
    return 1;
  }else{      //else if the current root has left child.
    return find_smallest(root->left, value_ptr);   //call the function recursively until finding the smallest value.
  }
}

int find_largest(node* root, int* value_ptr){
  //if the root is NULL.
  if (root == NULL){
    return 0;       //return zero to tell that the tree is empty.
  }else if (root->right == NULL){   //else if the current root does not have right child.
    *value_ptr = root->data; //pass the value of the root and return (1) to tell that the value passed successfully.
    return 1; 
  }else{      //else if the root has right child.
    return find_largest(root->right, value_ptr);  //call the function recursively until finding the largest value.
  }
}

int check_node(node* ptr, int* value_ptr){
  //if the ptr is NULL.
  if (ptr == NULL){
    return 0;     //return zero to tell that the pointer is NULL.
  }else if (ptr->left == NULL && ptr->right == NULL){   //if the node has no children.
    *value_ptr = 0;   //pass zero as the number of children and return (1) to tell that value passed successfully.
    return 1;
  }else if (ptr->left == NULL || ptr->right == NULL){   //else if the node has one child.
    *value_ptr = 1;   //pass one as the number of children and return (1) to tell that value passed successfully.
    return 1;
  }else{          //else if the node has two children.
    *value_ptr = 2;   //pass two as the number of children and return (1) to tell that value passed successfully.
    return 1;
  }
}

int is_empty(BST* tree){
  //if the root is NULL.
  if (tree->root == NULL){
    return 1;     //return (1) to tell that the tree is empty.
  }else{    
    return 0;   //else if the tree has stored elements return zero to tell that the tree is not empty.
  }
}

int get_size(BST* tree){
  return tree->size;      //return the current size of the tree.
}

int get_depth(node* root, int target, int* value_ptr){
  //if the current root is NULL.
  if (root == NULL){
    return 0;         //return zero to tell that the target does not exist.
  }else if (root->data == target){    //else if the current root is the target.
    return 1;     //return (1) to tell that the current value is the depth of the target.
  }else if (root->data > target){     //else if the current root is bigger than target.
    (*value_ptr)++;     //increase current value by one, as we will jump to the left child.
    return get_depth(root->left, target, value_ptr);
  }else{            //else if the current root is smaller than target.
    (*value_ptr)++;     //increase current value by one, as we will jump to the right child.
    return get_depth(root->right, target, value_ptr);
  }
}

int get_parent(node* root, int target, int* value_ptr){
  //if the current root is NULL.
  if (root == NULL){
    return 0;         //return zero to that the target does not exist.
  }else if (root->data == target){    //Special case: if the current root equals target.
    return 2;         //return (2) to tell that the target is the root and it has no parent.
  }else if (root->data > target){       //else if the current root is bigger than the target.
    //if the left pointer is not NULL.
    if (root->left != NULL){
      //if the target is the left child.
      if (root->left->data == target){
        *value_ptr = root->data;        //pass the current root as it is the parent of the target.
        return 1;                        //return (1) to tell that the value passed successfully.
      }else{      //else if the target is not the left child.
        return get_parent(root->left, target, value_ptr);   //call the function recursively with the left child.
      }
    }else{    //else if the left pointer is NULL.
      return 0;       //return zero to tell that the target does not exist in the tree.
    }
  }else{      //else if the current root is smaller than the target.
    //if the right pointer is not NULL.
    if (root->right != NULL){
      //if the right child is the target.
      if (root->right->data == target){
        *value_ptr = root->data;      //pass the current root as it is the parent of the target.
        return 1;                     //return (1) to tell that the value passed successfully.
      }else{        //else if the right child is not the target.
        return get_parent(root->right, target, value_ptr);  //call the function recursively with the right child.
      }
    }else{      //else if the right pointer is NULL.
      return 0;         //return zero to tell that the target does not exist in the tree.
    }
  }
}

void validate_tree(node* root, int* result_ptr){
  //if the current root is NULL.
  if (root == NULL){
    return;       //return as there is no elements to check ordering rules.
  }else if (root->left != NULL){     //else if the left pointer is not NULL.
    //if the left child is bigger than or equal root.
    if (root->left->data >= root->data){
      *result_ptr = 0;    //pass zero as this breaks ordering rules then return.
      return;
    }else{      //else if the left child is smaller than root.
      validate_tree(root->left, result_ptr);    //call the function recursively to check left subtree.
    }
  }
  //if the right pointer is not NULL.
  if (root->right != NULL){
    //if the right child is smaller than or equal root.
    if (root->right->data <= root->data){
      *result_ptr = 0;    //pass zero as this breaks ordering rules then return. 
      return;
    }else{      //else if the right child is bigger than the root.
      validate_tree(root->right, result_ptr);     //call the function recursively to check right subtree.
    }
  }
}

void display_ordered(node* root){
  //if the root is NULL.
  if (root == NULL){
    printf("The Tree is empty! There is No elements to display.\n");
    return;
  }else if (root->left != NULL){      //else if there are children at the left.
    display_ordered(root->left);    //call the function recursively to display them first.
  }
  //then display current node data.
  printf("%i\n", root->data);
  //finally display right children.
  if (root->right != NULL){     //if there are children at the right.
    display_ordered(root->right); //call the function recursively to display them.
  }
}

void display_tree_shape(node* root, int space){
  //if the current root is NULL.
  if (root == NULL){
    printf("The tree is empty! There is No elements to display.\n");
    return;
  }else if (root->right != NULL){     //if there are children at the right.
    display_tree_shape(root->right, space + 1);   //call the function recursively to display them with identation.
  }
  //then display current root data.
  for (int i = 0; i < space; i++){      //first display identation to show tree layout.
    printf("   ");      
  }                                     
  printf("%i\n", root->data);         //then display the data stored in the current root.
  //finally, display left children.
  if (root->left != NULL){
    display_tree_shape(root->left, space + 1);   //call the function recursively to display them with identation.
  }
}

void clear_tree(BST* tree){
  //if the tree is not empty.
  if (is_empty(tree) != 1){
    destroy_recursive(tree->root);    //First: free all nodes of the tree to avoid memory leak.
  }
  //then, reset tree variables.
  tree->root = NULL;
  tree->size = 0;
}

void destroy_tree(BST* tree){
  //if the tree is not empty.
  if (is_empty(tree) != 1){
    destroy_recursive(tree->root);    //First: free all nodes of the tree to avoid memory leak.
  }
  //then, free the space of the tree variables.
  free(tree);
}

void destroy_recursive(node* root){
  //if the root is NULL.
  if (root == NULL){
    return;           //there is no memory to free.
  }else if (root->left != NULL){      //if there are elements at the left.
    destroy_recursive(root->left);    //call the function recursively to free the left children first.
  }
  //then free the right children.
  if (root->right != NULL){           //if there are elements at the right.
    destroy_recursive(root->right);   //call the function recursively to free the right children.
  }
  //finally, free the current root.
  free(root);
}