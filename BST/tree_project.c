/*
   This program presents an optimized and interactive
   implementation of a Binary Search Tree (BST) 
   data structure in C. While supporting standard
   tree operations, it focuses on managing the tree 
   structure as a whole, checking its balanced state,
   and allowing the user to optimize its performance.

    **      Tree Analysis and Optimization      **

   - Tree Rebalancing: Provides a feature to collect 
     existing node pointers into an array and smartly 
     relink the nodes into a balanced structure. 
     This works directly through pointer manipulation 
     without destroying nodes or allocating new memory.

    **         Tree Properties Tracking         **

   - General Tree Summary:
     Gathers the metadata of the tree like total size,
     height, balance state, and node counts into a single
     query option, using efficient traversals to provide
     a complete status report in one step.
   - Logical Tree Validation:
     Scans the structure to confirm that all nodes strictly
     follow the mathematical sorting rules of the BST.
   - Global Data Counts:
     Counts the number of leaf nodes and internal nodes
     to give the user a clear report of the tree's content.
   - Direct Value Bounds:
     Locates the minimum and maximum values stored in the
     tree structure.
   - Ordered Value Relations:
     Allows the user to find the immediate successor or
     predecessor of any given element, helping to track
     the exact sorted order of the data.

    **         Layout and Memory Control         **

   - Tree Displays and Layout:
     Provides multiple ways to view the tree data, including
     inorder, preorder, postorder and levelorder traversals,
     as well as a visual print that shows the actual shape
     of the structure on the screen.
   - Full Tree Copying:
     Creates a complete and separate duplicate of the entire
     tree structure in memory. This allows the user to save
     the current state before making modifications and
     compare different tree structures.
   - Safe Memory Lifecycle:
     Provides tools to safely clear nodes from memory to
     empty the tree and reset the tree to the initial state,
     as well as fully free all allocated heap space when
     the program ends to avoid any memory leak.

    **                Program Goal                **  

   - The objective of this program is to build a stable 
     and fully observable binary search tree interface.
     It focuses on tree-level properties and user-driven
     optimization to ensure predictable performance and
     reliable memory control under various user inputs.

    **               Time Complexity               **

   - Insert new element into the tree:         Average(log n), O(n).
   - Delete specific element from the tree:    Average(log n), O(n).
   - Search for specific element in the tree:  Average(log n), O(n).
   - Find the smallest element in the tree:    Average(log n), O(n).
   - Find the largest element in the tree:     Average(log n), O(n).
   - Find the successor of element in tree:    Average(log n), O(n).
   - Find the predecessor of element in tree:  Average(log n), O(n).
   - Get the maximum height of the tree:                O(n).         "Rquires checking left and right height"
   - Test the tree balance state:                       O(n).        "Requires testing balance for all subtrees"
   - Get the current size of the tree:                  O(1).                  "Thanks to size entity"
   - Get the number of leafs and internal nodes:        O(n).         "Requires traversing to get node counts"
   - Test the sorting logic all over the tree:          O(n).        "Requires checking logic for all subtrees"
   - Take a copy of the current tree content:           O(n).        "Requires traversing to copy all elements"
   - Rebalance tree by relinking its nodes:             O(n).        "Requires relinking all nodes of the tree"
   - Display all elements of the tree:                  O(n).       "Requires traversing to display all elements"
   - Reset the tree to its initial state:               O(n).          "Requires traversing to free all nodes"
   - Destroy the tree at the end of the program:        O(n).        "Requires freeing all nodes and tree struct"
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
int get_int(char* request);                    //this function to take an integer value from user.
void display_template();              //this function to display the valid operations to perform on the tree.

//BST functions.
BST* init_tree();                                    //this function to initialize a new tree structure.
node* create_node(int value);                     //this function to create a new node for the given element.
int insert_into(BST* tree, node* ptr);            //this function to insert a new node into the tree structure.
int insert_recursive(node* root, node* ptr);      //this function to find the correct position for the new node.
int delete(BST* tree, int target);                //this function to delete specific element from the tree.
node* delete_recursive(node* root, int target, int* success); //this function to find replacement for deleted node.
node* search_for(node* root, int target);         //this function to search for specific element in the tree.
node* find_minimum(node* root);                   //this function to find the minimum value stored in the tree.
node* find_maximum(node* root);                   //this function to find the maximum value stored in the tree.
node* find_successor(node* root, int target, node* prob_successor); //this function to find the immediate larger element than target.
node* find_predecessor(node* root, int target, node* prob_predecessor); //this function to find the immediate smaller element than target.
int get_tree_status(node* root, int* is_balanced);//this function to get tree height and check balance of the tree.
int get_size(BST* tree);                          //this function to get the current size of the tree.
void get_node_counts(node* root, int* leafs, int* internals); //this function to get number of leafs and internal nodes in tree.
void validate_tree(node* root, int* is_valid);    //this function to check the sorting rules for the entire tree structure.
BST* copy_tree(BST* original_tree);               //this function to create a copy of the enitr tree in memory.
void copy_recursive(node* original_root, BST* copied_tree, int* is_complete); 
void rebalance_tree(BST* tree);    //this function to balance the tree structure to maintian efficient operations.
void store_ordered(node* root, node* array[], int* size_ptr); //this function to collect all node addresses in the tree.
node* link_balanced_tree(node* array[], int first, int last); //this function to relink nodes in balanced tree.
void preorder_display(node* root);                //this function to display all elements using preorder traversal.
void inorder_display(node* root);                 //this function to display all elements using inorder traversal.
void postorder_display(node* root);               //this function to display all elements using postorder traversal.
void levelorder_display(BST* tree);               //this function to display all elements level by level from tree.
void display_recursive(node* queue[], int size, int first, int last); //this function to track nodes of each level.
void print_tree_layout(node* root, int space);    //this function to display all elements in a tree layout.
void clear_tree(BST* tree);                       //this function to reset the tree to the initial state.
void destroy_tree(BST* tree);                     //this function to free all memory at the end of the program.
void destroy_recursive(node* root);               //this function to recursively free all nodes in the tree.

int main(void){

  //initialize new tree.
  BST* my_tree = init_tree();
  if (my_tree == NULL){
    return 1;     //if the function fails to allocate space for the tree structure, exit the program.
  }
  //initialize a pointer to the copy with NULL.
  BST* copied_tree = NULL;
  //welcome the user.
  printf("\nWelcome to the final version of Binary Search Tree management system.\n\n");
  display_template();
  //ask the user for the code of desired operation.
  int code;
  do{
    code = get_int("\nEnter the code of the operation you want to perform on the BST: ");
    //check code and perform desired operation.
    if (code == 1){    //Insert process.
      int times = get_int("Enter the number of elements you want to insert: ");
      for (int i = 0; i < times; i++){           //get the value of elements.
        int value = get_int("Enter value of element you want to insert into the tree: ");
        node* ptr = create_node(value);         //create a new node for each element.
        if (ptr == NULL){
          destroy_tree(my_tree);
          destroy_tree(copied_tree);
          return 1;       //if the function fails to allocate space for the node, free all memory and exit.
        }
        int status = insert_into(my_tree, ptr);     //insert the node with insertion function.
        if (status == 1){     //if the function returns (1) then the element inserted successully.
          printf("Element: %i inserted successfully into the tree.\n", value);
        }else{       //else if the function returns zero then the element is already stored in the tree.
          printf("This element is already stored in the tree.\n");
        }
      }
    }else if (code == 2){   //Deletion process.
      int times = get_int("Enter the number of elements you want to delete: ");
      for (int i = 0; i < times; i++){            //get the value of elements.
        int value = get_int("Enter value of element you want to delete from the tree: ");
        int status = delete(my_tree, value);      //delete the element with deletion function.
        if (status == 1){     //if the function returns (1) then element deleted successfully.
          printf("Element: %i deleted successfully from the tree.\n", value);
        }else{              //else if the function returns zero then the target not found in the tree.
          printf("This element does not exist in the tree.\n");
        }
      }
    }else if (code == 3){   //Search process.
      int value = get_int("Enter value of element you want to search for: ");
      node* element = search_for(my_tree->root, value);     //search for the target with search function.
      if (element == NULL){       //if the function returns NULL then element not found.
        printf("This element does not exist in the tree.\n");
      }else{         //else if the function returns address then it is the address of target in the tree.
        printf("Element: %i found in the tree.\n", value);
      }
    }else if (code == 4){   //Get minimum.
      node* minimum = find_minimum(my_tree->root);   //get minimum value with get minimum function.
      if (minimum == NULL){       //if the function returns NULL, then the tree is empty.
        printf("The tree is empty! There is No elements stored in the tree.\n");
      }else{          //else if the function returns address then it is the address of smallest element.
        printf("The minimum value stored in the tree is: %i\n", minimum->data);
      }
    }else if (code == 5){   //Get maximum.
      node* maximum = find_maximum(my_tree->root);     //get maximum value with get maximum function.
      if (maximum == NULL){       //if the function returns NULL then the tree is empty.
        printf("The tree is empty! There is No elements stored in the tree.\n");
      }else{              //else if the function returns address then it is the address of largest element.
        printf("The maximum value stored in the tree is: %i\n", maximum->data);
      }
    }else if (code == 6){   //Get successor.
      int value = get_int("Enter value of element you want to get its successor: ");
      node* successor = NULL;       //initialize a pointer to the successor with NULL.
      successor = find_successor(my_tree->root, value, successor);
      if (successor == NULL){   //if the function returns NULL then either target not found or has no successor.
        printf("This element does not exist in the tree or it is the largest element and has no successor.\n");
      }else{        //else if the function returns address then it is the address of the successor.
        printf("The immediate successor of this element in the tree is: %i\n", successor->data);
      }
    }else if (code == 7){   //Get predecessor.
      int value = get_int("Enter value of element you want to get its predecessor: ");
      node* predecessor = NULL;       //initialize a pointer to the predecessor with NULL.
      predecessor = find_predecessor(my_tree->root, value, predecessor);
      if (predecessor == NULL){ //if the function returns NULL then the element not found or has no predecessor.
        printf("This element does not exist in the tree or it is the smallest element and has no predecessor.\n");
      }else{              //else if the function returns address then it is the address of the predecessor.
        printf("The immediate predecessor of this element in the tree is: %i\n", predecessor->data);
      }
    }else if (code == 8){   //Get info about tree.
      int size = get_size(my_tree);
      if (size == 0){      //if the tree is empty.
        printf("The tree is empty! There is No elements stored in the tree.\n");
      }else{              //else if the tree has stored elements.
        //call getter functions to get all info about the tree.
        int is_balanced = 1;
        int height = get_tree_status(my_tree->root, &is_balanced);
        int internals = 0, leafs = 0;
        get_node_counts(my_tree->root, &leafs, &internals);
        //display all info to user.
        printf("The current number of elements stored in the tree is: %i\n", size);
        printf("The maximum height (number of edges) of the tree is: %i\n", height);
        printf("The maximum number of levels in the tree is: %i\n", height + 1);
        printf("The number of inernal nodes in the tree is: %i\n", internals);
        printf("The number of leaf (no children) nodes in the tree is: %i\n", leafs);
        if (is_balanced == 1){    //if the tree is balanced the function does not change value of the variable.
          printf("The tree is perfectly balanced and this ensure efficient operations.\n");
        }else{      //else if any node is unbalanced, it changes the value of the variable to zero.
          printf("The tree is not balanced and can be modified to improve efficiency.\n");
        }
      }
    }else if (code == 9){   //Validate tree.
      //initialize variable to store testing result with one.
      int is_valid = 1;
      validate_tree(my_tree->root, &is_valid);
      if (is_valid == 1){    //if the sorting rules are maintained, the function does not change the variable.
        printf("The sorting rules are maintained all over the BST and all subtrees of the tree.\n");
      }else{          //else if the rules are violated, the function changes the variable to zero.
        printf("The BST does not perfectly apply the sorting rules to all parts!\n");
        printf("There are some parts that does not follow the rules!\n");
      }
    }else if (code == 10){    //Copy process.
      BST* new_copy = copy_tree(my_tree); //copy the tree with copy function and store address of the copied tree.
      if (new_copy == NULL){    //if the function returns NULL then copy failed.
        printf("Copy failed! There is No space to copy the entire tree.\n");
      }else{      //else if the function returns address then the copy succeeded.
        printf("The tree is copied successfully.\n");
        destroy_tree(copied_tree);      //first we free all memory allocated for the old copy then,
        copied_tree = new_copy;              //store the address of the new copy of the tree.
      }
    }else if (code == 11){    //Rebalance process.
      rebalance_tree(my_tree);
      printf("The tree is rebalanced successfully to maintain efficient operations.\n");
    }else if (code == 12){   //Preorder display.
      preorder_display(my_tree->root);
    }else if (code == 13){    //Inorder display
      inorder_display(my_tree->root);
    }else if (code == 14){    //Postorder display.
      postorder_display(my_tree->root);
    }else if (code == 15){    //Levelorder display.
      levelorder_display(my_tree);
    }else if (code == 16){    //Print tree layout.
      print_tree_layout(my_tree->root, 0);
    }else if (code == 17){    //Display copy.
      if (copied_tree != NULL){     //if there is a copy of the tree, display recent copy.
        print_tree_layout(copied_tree->root, 0);
      }else{                        //else, there is no copies to display.
        printf("There is No copies stored of any tree!\n");
      }
    }else if (code == 18){    //Display subtree.
      int value = get_int("Enter the root of the subtree you want to display: ");
      node* root = search_for(my_tree->root, value);      //search for the value of the root.
      if (root == NULL){      //if the function returns NULL then the element not found.
        printf("This element does not exist in the tree!\n");
      }else{                  //else if the function returns address then it is the address of the target.
        print_tree_layout(root, 0);
      }
    }else if (code == 19){    //Display template.
      display_template();
    }else if (code == 20){    //Reset tree.
      clear_tree(my_tree);
      printf("The tree reseted successfully to the initial state.\n");
    }else if (code == 21){    //Exit process.
      printf("Exit the system.\n");
    }else{                    //Invalid input.
      printf("Invalid input! Enter (19) to check operations template.\n");
    }

  } while (code != 21);          //iterate until the user enters exit code (21).

  //free all memory allocated for the original and copy tree to avoid memory leak.
  destroy_tree(my_tree);
  destroy_tree(copied_tree);

  return 0;
}

int get_int(char* request){

  int value;                        //this variable to store the input value.
  int status;               //this variable to store the return value of scanf to check it.
  do{
    printf("%s", request);          //print request to ask the user for input.
    status = scanf("%i", &value);   //get the input value with scanf.
    while(getchar() != '\n');       //clear the buffer from garbage input or '\n'.
  } while (status == 0);      //iterate until scanf gets a valid input as it returns zero in case of failure.
  
  return value;
}

void display_template(){
  printf("These are the codes of the valid operations to perform on the BST:\n");
  printf("1.Insert new element into the tree.              2.Delete specific element from the tree.\n");
  printf("3.search for specific element in the tree.       4.Get the smallest element in the tree.\n");
  printf("5.Get the largest element in the tree.           6.Get the immediate successor of specific element.\n");
  printf("7.Get immediate predecessor of specific element. 8.Get info about the current state of the tree.\n");
  printf("9.Check sorting rules for the entire tree.       10.Take a copy of the current tree.\n");
  printf("11.Rebalance tree to maintain efficiency.        12.Display all elements using preorder traversal.\n");
  printf("13.Display all elements using inorder traversal. 14.Display all elements using postorder traversal.\n");
  printf("15.Display all elements level by level.          16.Display all elements in a tree layout.\n");
  printf("17.Display the recent copy of the tree.          18.Display a subtree in the big tree with its root.\n");
  printf("19.Display template of the valid operations.     20.Reset the tree to the initial state.             ");
  printf("21.Exit the system.\n");
}

BST* init_tree(){

  BST* tree = malloc(sizeof(BST));        //allocate space for the tree structure.
  if (tree == NULL){
    return NULL;        //if the function fails to allocate space for the tree, it returns NULL.
  }
  //initialize tree variables.
  tree->root = NULL;
  tree->size = 0;

  return tree;
}

node* create_node(int value){

  node* ptr = malloc(sizeof(node));     //allocate space for a new node.
  if (ptr == NULL){
    return NULL;      //if the function fails to allocate space for the node, it returns NULL.
  }
  //initialize node variables.
  ptr->data = value;
  ptr->left = NULL;
  ptr->right = NULL;

  return ptr;
}

int insert_into(BST* tree, node* ptr){
  //if the tree is empty.
  if (tree->root == NULL){
    tree->root = ptr;       //the new node becomes the root of the tree.
    tree->size++;
    return 1;       //return (1) to tell that the node inserted successfully into the tree.
  }else{      //else if the tree has stored elements.
    int result = insert_recursive(tree->root, ptr); //call recursive function to insert the node in the correct position.
    if (result == 1){
      tree->size++;     //if the function insert the element successfully, we increase size by one.
    }
    return result; //return result to tell whether the element inserted successfully or already stored in tree.
  }
}

int insert_recursive(node* root, node* ptr){
  //if the new element equals root.
  if (root->data == ptr->data){
    free(ptr);    //free the new node and return zero to tell that the element is already stored in the tree.
    return 0;
  }else if (root->data > ptr->data){    //else if the root is larger than new element.
    //if the root does not have left child.
    if (root->left == NULL){
      root->left = ptr;  //the new node becomes the left child of the current root then return (1) for success.
      return 1;
    }else{        //else if it has left child, call the function recursively with the left child.
      return insert_recursive(root->left, ptr);
    }
  }else{                    //else if the root if smaller than new element.
    //if the root does not have right child.
    if (root->right == NULL){
      root->right = ptr;  //the new node becomes the right child of the current root then return (1) for success.
      return 1;
    }else{      //else if the root has right child, call the function recursively with the right child.
      return insert_recursive(root->right, ptr);  
    }
  }
}

int delete(BST* tree, int target){
  //make variable to tell whether element deleted or not found.
  int is_deleted = 0;
  tree->root = delete_recursive(tree->root, target, &is_deleted);
  //if the target deleted successfully, decrease size by one.
  if (is_deleted == 1){
    tree->size--;
  }
  return is_deleted;    //return flag variable to tell whether element deleted or not found.
}

node* delete_recursive(node* root, int target, int* success_ptr){
  //if the root is NULL.
  if (root == NULL){
    return NULL;
  }else if (root->data == target){    //else if the current root is target.
    //we have three cases to handle based on number of children of target.
    if (root->right == NULL && root->left == NULL){     //case 1: target has no children.
      free(root);     //free the root then pass success code (1) and return NULL to replace the root address.
      *success_ptr = 1;
      return NULL;
    }else if (root->right == NULL || root->left == NULL){   //case 2: target has one child.
      //store address of the child.
      node* child;
      if (root->left == NULL){
        child = root->right;
      }else{
        child = root->left;
      }
      free(root);       //free the root and pass success code (1) then return child address to replace it.
      *success_ptr = 1;
      return child;
    }else{                //case 3: target has two children.
      node* child = find_minimum(root->right);      //get the minimum element in the right subtree.
      root->data = child->data;    //replace the value of the target with the minimum value in right subtree.
      root->right = delete_recursive(root->right, root->data, success_ptr);
      return root;      //call the function recursively to delete the duplicate node then return root,
                                // as the replacement is stored at the same address of target.
    }
  }else if (root->data > target){       //else if the current root is larger than target.
    root->left = delete_recursive(root->left, target, success_ptr);
    return root; //call the function recursively with the left pointer and return root as it is not the target.
  }else{                //else if the current root is smaller than target.
    root->right = delete_recursive(root->right, target, success_ptr);
    return root; //call the function recursively with the right pointer and return root as it is not the target.
  }
}

node* search_for(node* root, int target){
  //if the root is NULL.
  if (root == NULL){
    return NULL;        //return NULL to tell that the element not found.
  }else if (root->data == target){
    return root;      //else if the root is the target return the root which is the address of the element.
  }else if (root->data > target){
    return search_for(root->left, target);  //else if the root is larger than target, call the function 
  }else{                                                 //recursively with the left pointer.
    return search_for(root->right, target); //else if the root is smaller than target, call the function
  }                                                       //recursively with the right pointer.
}

node* find_minimum(node* root){
  //if the root is NULL.
  if (root == NULL){
    return NULL;        //return NULL to tell that the tree is empty.
  }else if (root->left == NULL){
    return root;      //else if the root does not have left child, then it is the minimum value in the tree.
  }else{        //else if it has left child, call the function recursively until finding the minimum value.
    return find_minimum(root->left);
  }
}

node* find_maximum(node* root){
  //if the root is NULL.
  if (root == NULL){
    return NULL;      //return NULL to tell that the tree is empty.
  }else if (root->right == NULL){
    return root;    //else if the root does not have right child, then it is the maximum value in the tree.
  }else{    //else if the root has right child, call the function recursively until finding maximum value.
    return find_maximum(root->right);
  }
}

node* find_successor(node* root, int target, node* prob_successor){
  //if the current root is NULL.
  if (root == NULL){
    return NULL;      //return NULL to tell that the target does not exist in the tree.
  }else if (root->data == target){    //else if the current root is the target.
    //if the root has right child.
    if (root->right != NULL){
      return find_minimum(root->right);   //then, the successor is the smallest element at the right subtree.
    }else{    //else if it does not have right child, then return the parent if the root was at the left.
      return prob_successor;
    }
  }else if (root->data > target){   //else if the root is bigger than target.
    prob_successor = root;   //store the address of root as it could be the successor of the target.
    return find_successor(root->left, target, prob_successor);
  }else{      //else if the root is smaller than the target.
    return find_successor(root->right, target, prob_successor);
  }
}

node* find_predecessor(node* root, int target, node* prob_predecessor){
  //if the root is NULL.
  if (root == NULL){
    return NULL;      //return NULL to tell that the target does not exist in the tree.
  }else if (root->data == target){    //else if the current root is the target.
    //if the root has left child.
    if (root->left != NULL){
      return find_maximum(root->left);   //then the predecessor is the largest element at the left subtree.
    }else{     //else if it does not has left child, then return the parent if the root was at the right.
      return prob_predecessor;
    }
  }else if (root->data > target){     //else if the root is larger than the target.
    return find_predecessor(root->left, target, prob_predecessor);
  }else{      //else if the root is smaller than the target.
    prob_predecessor = root;   //store the address of the root as it could be the predecessor of the target.
    return find_predecessor(root->right, target, prob_predecessor);
  }
}

int get_tree_status(node* root, int* is_balanced){
  //if the root is NULL.
  if (root == NULL){
    return -1;        //return (-1) to tell that the tree is empty.
  }else{    //else if the tree has stored elements.
    //get the height of the left and right subtrees.
    int left_height = get_tree_status(root->left, is_balanced);
    int right_height = get_tree_status(root->right, is_balanced);
    //check balance.
    int BF = (left_height - right_height);
    if (BF < -1 || BF > 1){   //if the balance factor is not in the valid range {1, 0, -1}.
      *is_balanced = 0;           //then pass zero to tell that the tree is unbalanced.
    }
    //calculate height (return the bigger height value + (1) for the root level).
    if (left_height >= right_height){
      return (left_height + 1);   
    }else{
      return (right_height + 1);
    }
  }
}

int get_size(BST* tree){
  return tree->size;      //return the current number of elements in the BST.
}

void get_node_counts(node* root, int* leafs, int* internals){
  //if the root is NULL.
  if (root == NULL){
    return;      //return as the tree is empty.
  }else if (root->left != NULL){  //else if the root has left subtree, we call the function recursively,
    get_node_counts(root->left, leafs, internals);              //to get counts of the left subtree.
  }
  //if the root has right subtree, call the function recursively to get counts of the right subtree.
  if (root->right != NULL){
    get_node_counts(root->right, leafs, internals);
  }
  //check part.
  if (root->left == NULL && root->right == NULL){
    (*leafs)++;     //if the root does not have left or right child then it is a leaf.
  }else{
    (*internals)++; //else if the root has one or two children then it is an internal node.
  }
}

void validate_tree(node* root, int* is_valid){
  //if the root is NULL.
  if (root == NULL){
    return;
  }else if (root->left != NULL){    //if the root has left child.
    //if the root is smaller than or equal left child.
    if (root->data <= root->left->data){
      *is_valid = 0;      //pass zero to tell that the sorting rules is violated then return.
      return;
    }else{      //else check the left subtree.
      validate_tree(root->left, is_valid);
    }
  }
  //if the root has right child.
  if (root->right != NULL){
    //if the root is larger than or equal right child.
    if (root->data >= root->right->data){
      *is_valid = 0;      //pass zero to tell that the sorting rules is violated then return.
      return;
    }else{      //else check the right subtree.
      validate_tree(root->right, is_valid);
    }
  }
}

BST* copy_tree(BST* original_tree){
  //allocate space for the new tree structure.
  BST* copied_tree = init_tree();
  if (copied_tree == NULL){
    return NULL; //if the function fails to allocate space for new tree, return NULL to tell that there is no space.
  }
  //call recursive function to copy all nodes of the tree.
  int is_complete = 1;      //this variable to tell whether the entire tree is copied or not.
  copy_recursive(original_tree->root, copied_tree, &is_complete);
  //check whether the tree copied successfully or not.
  if (is_complete == 1){
    return copied_tree;     //in case of completely copied, return the address of the copied tree.
  }else{  //else if copy failed, free all memory allocated for copied tree and return NULL to tell there is no space.  
    destroy_tree(copied_tree);    
    return NULL;
  }
}

void copy_recursive(node* original_root, BST* copied_tree, int* is_complete){
  //if the root is NULL.
  if (original_root == NULL){
    return;     //there is no elements to copy.
  }else{    //else if the original tree has stored elements, copy them using preorder traversal.
    //first copy the root.
    node* ptr = create_node(original_root->data);    //create a node for the root value.
    if (ptr == NULL){
      *is_complete = 0;     //if the function fail to allocate space for the node, pass zero to tell that
      return;                                     //the copy failed then return.
    }     //after creating the node, insert it into the copied tree.
    int status = insert_into(copied_tree, ptr);
    //then copy the left subtree recursively.
    if (original_root->left != NULL){
      copy_recursive(original_root->left, copied_tree, is_complete);
    }
    //finally copy the right subtree recursively.
    if (original_root->right != NULL){
      copy_recursive(original_root->right, copied_tree, is_complete);
    }
  }
}

void rebalance_tree(BST* tree){
  //rebalance tree if it has elements more than two to maintain efficient operations.
  if (tree->size > 2){
    //first: create an array to store addresses of nodes.
    node* elements[tree->size];
    int size = 0;
    //then: collect all nodes of the tree sorted in ascending order in the array.
    store_ordered(tree->root, elements, &size);
    //finally: relink all nodes to create balanced tree.
    int first = 0;
    int last = tree->size - 1;
    tree->root = link_balanced_tree(elements, first, last);
  }
}

void store_ordered(node* root, node* array[], int* size_ptr){
  //if the root is NULL.
  if (root == NULL){
    return;     //there is no element to add.
  }else{    //else if there are elements stored.
    //first: add the left subtree recursively to maintain order.
    if (root->left != NULL){
      store_ordered(root->left, array, size_ptr);
    }
    //then: add the current root.
    array[*size_ptr] = root;
    (*size_ptr)++;
    //finally: add the right subtree recursively.
    if (root->right != NULL){
      store_ordered(root->right, array, size_ptr);
    }
  }
}

node* link_balanced_tree(node* array[], int first, int last){
  //create a base case to stop recursion.
  if (first > last){
    return NULL;   //if first index exceeds last then it is the end of linking and we reach leafs of the tree.
  }
  //calculate middle index to be the root of the balanced tree.
  int middle = (first + last)/ 2;
  //then relink the left subtree recursively.
  array[middle]->left = link_balanced_tree(array, first, middle - 1);
  //after that: relink the right subtree recursively.
  array[middle]->right = link_balanced_tree(array, middle + 1, last);
  //finally: return the value of the root.
  return array[middle];
}

void preorder_display(node* root){
  //if the root is NULL.
  if (root == NULL){
    printf("The tree is empty! There is No elements to display.\n");
  }else{    //else if the tree has stored elements.
    //first: display the current root.
    printf("%i\n", root->data);
    //then: display the left subtree.
    if (root->left != NULL){
      preorder_display(root->left);
    }
    //finally display the right subtree.
    if (root->right != NULL){
      preorder_display(root->right);
    }
  }
}

void inorder_display(node* root){
  //if the root is NULL.
  if (root == NULL){
    printf("The tree is empty! There is No elements to display.\n");
  }else{      //else if the tree has stored elements.
    //first: display the left subtree to maintain order.
    if (root->left != NULL){
      inorder_display(root->left);
    }
    //then: display the current root.
    printf("%i\n", root->data);
    //finally: display the right subtree.
    if (root->right != NULL){
      inorder_display(root->right);
    }
  }
}


void postorder_display(node* root){
  //if the root is NULL.
  if (root == NULL){
    printf("The tree is empty! There is No elements to display.\n");
  }else{      //else if the tree has stored elements.
    //first: display the left subtree.
    if (root->left != NULL){
      postorder_display(root->left);
    }
    //then: display the right subtree.
    if (root->right != NULL){
      postorder_display(root->right);
    }
    //finally: display the current root.
    printf("%i\n", root->data);
  }
}

void levelorder_display(BST* tree){
  //if the tree is empty.
  if (tree->root == NULL){
    printf("The tree is empty! There is No elements to display.\n");
  }else{      //else if the tree has stored elements.
    //create a queue to track nodes of each level.
    node* elements[tree->size];
    //initialize queue with the root node.
    elements[0] = tree->root;
    int first = 0, last = 0, size = 1;
    display_recursive(elements, size, first, last);
  }
}

void display_recursive(node* queue[], int size, int first, int last){
  //iterate until the queue becomes empty.
  while (size > 0){
    //first: display the first element in the queue and store current size to display nodes of level in one line.
    for (int i = 0, times = size; i < times; i++){
      printf("%i   ", queue[first]->data);
      //then enqueue the children of first element from left to right.
      if (queue[first]->left != NULL){
        last++;
        queue[last] = queue[first]->left;
        size++;
      }
      if (queue[first]->right != NULL){
        last++;
        queue[last] = queue[first]->right;
        size++;
      }
      //finally: dequeue the first element from queue.
      first++;
      size--;
    }
    printf("\n");
  }
}

void print_tree_layout(node* root, int space){
  //if the root is NULL.
  if (root == NULL){
    printf("The tree is empty! There is No elements to display.\n");
  }else{    //else if the tree has stored elements.
    //first: display the right subtree recursively.
    if (root->right != NULL){
      print_tree_layout(root->right, space + 1);
    }
    //then: display the current root.
    for (int i = 0; i < space; i++){
      printf("   ");
    }
    printf("%i\n", root->data);
    //finally: display the left subtree recursively.
    if (root->left != NULL){
      print_tree_layout(root->left, space + 1);
    }
  }
}

void clear_tree(BST* tree){
  //if the tree is not NULL.
  if (tree != NULL){
    //free all nodes of the tree.
    destroy_recursive(tree->root);
    //then: reset tree variables.
    tree->root = NULL;
    tree->size = 0;
  }
}

void destroy_tree(BST* tree){
  //if the tree is not NULL.
  if (tree != NULL){
    //first: free all nodes of the tree recursively.
    destroy_recursive(tree->root);
    //then: safely free the tree structure.
    free(tree);
  }
}

void destroy_recursive(node* root){
  //if the root is NULL.
  if (root == NULL){
    return;
  }else{      //else if the tree has stored elements.
    //first: free the left subtree recursively.
    if (root->left != NULL){
      destroy_recursive(root->left);
    }
    //then: free the right subtree recursively.
    if (root->right != NULL){
      destroy_recursive(root->right);
    }
    //finally: free the current root.
    free(root);
  }
}