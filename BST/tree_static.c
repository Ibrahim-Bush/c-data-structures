/*
   This program presents a simple implementation
   of a Binary Search Tree (BST) data structure.
   This basic implementation marks our transition
   from linear data structures, like arrays and
   linked lists, to non-linear data structures.
   It demonstrates how data is organized in
   a non-linear, hierarchical layout, focusing
   on the core behaviour of nodes and pointers.

    **        The Need for Tree Structures        **

   - Overcoming Linear Search Limitations: previously,
     we saw the great power of linked lists and pointers
     in dynamic memory allocation. However, linked list
     suffer from a major drawback: the inability to perform
     binary search. Because elements are not stored continguously,
     we are restricted to a slow linear search. This limits
     our search efficiency to an O(n) time complexity for
     every search operation. Trees solve this problem
     completely by introducing a hierarchical layout.

    **      Core Binary Search Tree Architecture      **

   - The Ordering Rule: The structural integrity of a BST
     relies on a strict mathematical rule. For any given
     node, every element in its right subtree must have
     a value larger than the node itself, and every element
     in its left subtree must have a value smaller than
     the node itself. This rule applies universally to every
     single node across the entire tree. By enforcing this
     structure, the tree guarantees that our search efficiency
     stays at an optimized O(log n) time complexity.

    **       Core Binary Search Tree Operations       **

   - Search Operation: To find an element, the algorithm
     starts by checking the root node. This process evaluates
     three distinct cases:
     1. If the target value matches the value of the current
        node, the element is successfully found.
     2. If the target value is smaller than the value of the
        current node, the search moves recursively into the
        left subtree.
     3. If the target value is larger than the value of the
        current node, the search moves recursively into the
        right subtree.
     If the search reaches a NULL pointer, it means the element
     does not exist in the tree.

   - Insertion Operation: When adding a new node, the system
     traverses the tree recursively to find its correct
     structural position. At each step, it checks if the new
     value is larger or smaller than the current node.
     1. If the new value is smaller than the current node,
        the algorithm moves recursively to the left.
     2. If the new value is larger than the current node,
        the algorithm moves recursively to the right.
     3. If the value is exactly equal to an existing node,
        the value is completely ignored and considered
        already stored to avoid duplicate elements.

   - Deletion Operation: Removing a node from a BST requires
     careful management to preserve the sorting rules of the tree.
     The operation handles three distinct cases based on
     the number of children of the target node:
     1. Leaf Node: If the node has no children, it is safely
        freed from memory, and its parent's pointer is
        updated to NULL.
     2. One Child: If the node has only one child (left or right),
        the node is removed, and its single child directly
        connects with the parent node.
     3. Two Children: If the node has two children, we must
        find a suitable replacement value. We look for either
        the smallest element in its right subtree or the largest
        element in its left subtree. This replacement value is
        copied into the target node, and the duplicate replacement
        node is then recursively deleted from below.

    **                 Program Goal                   **

   - The main objective of this program is to understand the
     fundamental mechanics of a Binary Search Tree. We focus
     on learning how pointers connect nodes hierarchically
     and how the basic rules of insertion, deletion, and
     searching work in practice.

    **                Time Complexity                 **
   In the Balanced Binary Search Tree:
   - Insert new element into the tree:        O(log n).        "Require finding the correct position for insertion"
   - Delete specific element from the tree:   O(log n).        "Require finding the target and suitable replacement"
   - Search for specific element in the tree: O(log n).                   "using efficient Binary Search"
   - Display all elements of the tree:          O(n).               "Require access to all nodes to display them"
   - Destroy the whole tree by freeing memory:  O(n).                "Require access to all nodes to free them"
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node{

   int data;                     //the data stored in the node.
   struct node* right;           //the pointer to the right node.
   struct node* left;            //the pointer to the left node.
} node;

typedef struct BST{

   node* root;                   //the pointer to the root node.
   int size;                     //the number of elements stored in the tree.
} BST;

//BST functions.
BST* init_tree();                                            //this function to initialize a new tree.
node* create_node(int value);                          //this function to create a new node for a given value.
int insert_into(BST* tree, node* ptr);                   //this function to insert a new node into the tree.
int insert_recursive(node* root, node* ptr); //this helper function to detect the correct position to insert the node.
int search_recursive(node* root, int target);//this function to search for specific element using Binary Search algorithm.
int delete(BST* tree, int target);                    //this function to delete specific element from the tree.
node* delete_recursive(node* root, int target, int* success_ptr); //this helper function to detect the suitable
                                                                      //replacement for the deleted node.
int check_node(node* ptr);                //this helper function to check the number of children for specific node.
int find_smallest(node* ptr);                  //this helper function to find the smallest element in the tree.
void display_ordered(node* root);       //this function to display all elements of the tree in their correct order.
void destroy_tree(BST* tree);           //this function to destroy the tree by freeing all memory allocated for it.
void destroy_recursive(node* root);         //this helper function to recursively free the all nodes of the tree.

int main(void){

   //initialize new BST.
   BST* my_tree = init_tree();
   if (my_tree == NULL){
      return 1;            //if the function failed to allocate space for the tree we exit the program.
   }

   printf("\nThis is the first program for the Binary Search Tree.\n\n");
   //set the elements we will insert into the tree.
   int values[] = {10, 6, 15, 8, 18, 16, 7, 3, 13, 11, 14, 20, 9, 1, 5};

   //insert first five element of the array into the tree.
   printf("Insertion Testing:\n");
   for (int i = 0; i < 5; i++){
      //first create a node for the new element.
      node* ptr = create_node(values[i]);
      if (ptr == NULL){  //if the function fails to allocate space for the node we free all memory allocated and exit.
         destroy_tree(my_tree);
         return 1;
      }  //insert the new node into the tree.
      int status = insert_into(my_tree, ptr);
      if (status == 1){        //if the node inserted successfully the function returns (1).
         printf("Element: %i inserted successfully into the tree.\n", values[i]);
      }else{            //else if the function returns zero then the element already stored in the tree.
         printf("Element: %i is already stored in the tree.\n", values[i]);
      }
   }
   //display all list elements after insertion.
   printf("\nThe current size of the tree is: %i\n", my_tree->size);
   printf("All elements of the tree in the correct order after inserting elements:\n");
   display_ordered(my_tree->root);

   //insert more seven elements into the tree with first two elements already stored in the tree.
   printf("\nInserting elements with some elements already exist in the tree:\n");
   for (int i = 3; i < 10; i++){
      //first create a node for the new elements.
      node* ptr = create_node(values[i]);
      if (ptr == NULL){    //if the function fails to allocate space for node, we free all memory and exit program.
         destroy_tree(my_tree);
         return 1;
      }  //insert nodes with insertion function.
      int status = insert_into(my_tree, ptr);
      if (status == 1){       //if the function returns (1) then element inserted successfully.
         printf("Element: %i inserted successfully into the tree.\n", values[i]);
      }else{             //else if the function returns zero then element already stored in the tree.
         printf("Element: %i is already stored in the tree.\n", values[i]);
      }
   }
   //display all list elements after insertion.
   printf("\nThe current size of the tree is: %i\n", my_tree->size);
   printf("All elements of the tree in the correct order after inserting elements:\n");
   display_ordered(my_tree->root);

   //Searching for specific elements in the tree.
   printf("\nSearching sor specific elements in the tree:\n");
   for (int i = 0; i < 15; i += 2){
      int status = search_recursive(my_tree->root, values[i]);
      if (status == 1){    //if the function returns (1) then element found in the tree.
         printf("Element: %i found in the tree.\n", values[i]);
      }else{         //else if the function returns zero then element not found in the tree.
         printf("Element: %i not found in the tree.\n", values[i]);
      }
   }

   //Deleting five elements from the tree.
   printf("\nDeletion Testing:\n");
   for (int i = 5; i < 15; i += 2){
      int status = delete(my_tree, values[i]);
      if (status == 1){       //if the function returns (1) then element deleted successfully.
         printf("Element: %i deleted successfully from the tree.\n", values[i]);
      }else{               //else if the function returns zero then element not found in the tree.
         printf("Element: %i not found in the tree.\n", values[i]);
      }
   }
   printf("\nThe current size of the tree is: %i\n", my_tree->size);
   printf("All elements of the tree after deleting some elements:\n");
   display_ordered(my_tree->root);

   //inserting the last five elements of the array.
   printf("\nInserting elements with some of them already stored in the tree:\n");
   for (int i = 6; i < 15; i++){
      //create a node for the new element.
      node* ptr = create_node(values[i]);
      if (ptr == NULL){   //if the function fails to allocate space for the node we free all memory and exit program.
         destroy_tree(my_tree);
         return 1;
      }  //insert nodes with insertion function.
      int status = insert_into(my_tree, ptr);
      if (status == 1){       //if the function returns (1) then element inserted successfully.
         printf("Element: %i inserted successfully into the tree.\n", values[i]);
      }else{            //else if the function returns zero then the element already stored in the tree.
         printf("Element: %i already stored in the tree.\n", values[i]);
      }
   }
   printf("\nThe current size of the tree is: %i\n", my_tree->size);
   printf("All elements of the tree after inserting some elements:\n");
   display_ordered(my_tree->root);

   //searching for specific elements at the tree.
   printf("\nSearching for some elements at the tree:\n");
   for (int i = 5; i < 15; i += 2){
      int status = search_recursive(my_tree->root, values[i]);
      if (status == 1){    //if the function returns (1) then element found in the tree.
         printf("Element: %i found in the tree.\n", values[i]);
      }else{         //else if the function returns zero then element not found in the tree.
         printf("Element: %i not found in the tree.\n", values[i]);
      }
   }

   //Delete some elements from the tree.
   printf("\nDeleting some elements from the tree:\n");
   for (int i = 1; i < 15; i += 2){
      int status = delete(my_tree, values[i]);
      if (status == 1){       //if the function returns (1) then element deleted successfully.
         printf("Element: %i deleted successfully from the tree.\n", values[i]);
      }else{               //else if the function returns zero then element not found in the tree.
         printf("Element: %i not found in the tree.\n", values[i]);
      }
   }
   printf("\nThe current size of the tree is: %i\n", my_tree->size);
   printf("All elements of the tree after deleting some elements:\n");
   display_ordered(my_tree->root);

   //Destroy the tree by freeing all memory allocated to it to avoid memory leak.
   destroy_tree(my_tree);

   return 0;
}

BST* init_tree(){

   BST* tree = malloc(sizeof(BST));             //allocate space for the BST.
   if (tree == NULL){
      return NULL;                            //if allocation fails we return NULL.
   }
   tree->root = NULL;                             //initialize tree variables.
   tree->size = 0;

   return tree;
}

node* create_node(int value){

   node* ptr = malloc(sizeof(node));            //allocate space for a new node.
   if (ptr == NULL){
      return NULL;                           //if allocation fails we return NULL.
   }
   ptr->data = value;                              //initialize node variables.
   ptr->right = NULL;
   ptr->left = NULL;

   return ptr;
}

int insert_into(BST* tree, node* ptr){
   //if the tree is empty.
   if (tree->root == NULL){
      tree->root = ptr;       //the new node becomes the root of the tree.
      tree->size++;           //then increase size by one and return (1) to tell that element inserted successfully.
      return 1;
   }else{
      //call helper function to detect the correct position for the new node to maintain sorting rules of the tree.
      int status = insert_recursive(tree->root, ptr);
      //if the new element inserted successfully, the helper function returns (1) else the value already stored in tree.
      if (status == 1){
         tree->size++;        //if the new element insert successfully, we increase tree size by one.
      }
      return status;       //return status to tell whether element insert successfully or already exist in the tree.
   }
}

int insert_recursive(node* root, node* ptr){
   //if the root equal new element.
   if (root->data == ptr->data){
      free(ptr);  //free the new node before losing its address as we will not insert it into the tree.
      return 0;            //return zero to tell that element already stored in the tree.
   }else if (root->data > ptr->data){     //else if new value is smaller than the root.
      //if the left pointer is NULL.
      if (root->left == NULL){
         root->left = ptr;       //make the left pointer points to the new node and return (1) after insertion.
         return 1;
      }else{      //else if there are elements at the left of current node.
         return insert_recursive(root->left, ptr);       //call the function recursively to detect correct position.
      }
   }else{    //else if new value is greater than the root.
      //if the right pointer is NULL.
      if (root->right == NULL){
         root->right = ptr;      //make the right pointer points to the new node and return (1) after insertion.
         return 1;
      }else{      //else if there are elements at the right og the current node.
         return insert_recursive(root->right, ptr);
      }
   }
}

int search_recursive(node* root, int target){
   //if the tree is empty.
   if (root == NULL){
      return 0;        //return zero to tell that element not found in the tree.
   }else if (root->data == target){    //else if the value stored in the current root equal target
      return 1;                         //return (1) to tell that the element found in the tree.
   }else if (root->data > target){     //else if target is smaller than the value of the root.
      return search_recursive(root->left, target); //search recursively in the left subtree.
   }else{              //else if target is greater than the value of the root.
      return search_recursive(root->right, target); //search recursively in the right subtree.
   }
}

int delete(BST* tree, int target){
   //create variable to know whether element deleted or not found.
   int success = 0;     //initialize it with zero as not found.
   //call helper function to delete target and find the correct raplacement to maintain sorting rules.
   tree->root = delete_recursive(tree->root, target, &success);//store return value at the root as it can be the target.
   //check whether element deleted or not.
   if (success == 1){
      tree->size--;     //decrease size by one if element deleted successfully.
   }
   return success;   //return value of success to tell whether element deleted or not.
}

node* delete_recursive(node* root, int target, int* success_ptr){
   //if the tree is empty.
   if (root == NULL){
      return root;
   }else if (root->data == target){    //else if the current root is the target.
      //we have three cases to handle based on number of children of the target.
      int child_num = check_node(root);   //call helper function to get number of children of the node.
      //case 1: leaf (no children)
      if (child_num == 0){
         free(root);             //safely free the target and pass (1) to tell that element deleted successfully.
         *success_ptr = 1;
         return NULL;            //return NULL to the caller function as there is No nodes at that place anymore.
      }else if (child_num == 1){       //case 2: the target node has only one child.
         //store the address of the child to replace the target.
         node* temp;    //this pointer to store the address of the child.
         if (root->left == NULL){
            temp = root->right;        //check whether the node has left or right child and store its address.
         }else{
            temp = root->left;
         }
         //free the target node and return child address to the parent to replace the target.
         free(root);
         *success_ptr = 1;
         return temp;
      }else{           //case 3: the target node has two children.
         //find the correct replacement which can be the smallest element at the right subtree.
         root->data = find_smallest(root->right);    //store the value at the target and delete the duplicate value.
         //delete the duplicate value and make it pass the success flag.
         root->right = delete_recursive(root->right, root->data, success_ptr);
         return root;   //return root as the address of the replacement is the same as the target as we change value.
      }
   }else if (root->data > target){     //else if root is bigger than target.
      root->left = delete_recursive(root->left, target, success_ptr);
      return root;      //we return root as the current node is not the target.
   }else{                    //else if the root is smaller than target.
      root->right = delete_recursive(root->right, target, success_ptr);
      return root;      //we return root as the current node is not the target.
   }
}

int check_node(node* ptr){
   //case 1: if the node has no children.
   if (ptr->right == NULL && ptr->left == NULL){
      return 0;      //return zero to tell that the node has no children.
   }else if (ptr->right == NULL || ptr->left == NULL){    //case 2: the node has one child.
      return 1;      //return (1) to tell that the node has one child.
   }else{      //else if the two pointers does not equal NULL then the node has two children.
      return 2;       //return (2) to tell that the node has two children.
   }
}

int find_smallest(node* ptr){
   //if the node has no left child.
   if (ptr->left == NULL){
      return ptr->data;       //then the current node is the smallest one.
   }else{      //else if it has left child.
      return find_smallest(ptr->left);       //call the function recursively with the left child.
   }
}

void display_ordered(node* root){
   //if the tree is empty.
   if (root == NULL){
      printf("The tree is empty!\n");
      return;
   }
   //if the node has left children we display them first to maintain order.
   if (root->left != NULL){
      display_ordered(root->left);
   }
   //then display the data of the node itself.
   printf("%i\n", root->data);
   //finally, if the node has right children we display them.
   if (root->right != NULL){
      display_ordered(root->right);
   }
}

void destroy_tree(BST* tree){
   //first free all nodes of the tree recursively.
   destroy_recursive(tree->root);
   //then safely free the tree variables space.
   free(tree);
}

void destroy_recursive(node* root){
   //if the tree is empty.
   if (root == NULL){
      return;        //return as there is no elements to free its space.
   }
   //if the node has left children we free them all first.
   if (root->left != NULL){
      destroy_recursive(root->left);
   }
   //then, if the node has right children we free them all.
   if (root->right != NULL){
      destroy_recursive(root->right);
   }
   //finally, we free the node itself.
   free(root);
}
