/*
   This program is designed to demonstrate
   the full mechanics, dynamic behaviour,
   and performance characteristics of the
   Hash Table data structure.
   This implementation builds a robust key-value 
   storage system using a two-dimensional Hash table 
   combined with singly linked lists with optimized
   lookup, insertion and deletion capabilities.

    **    The need for Hash table structure    **

   - Limitation of Basic structures: Data structures
     like arrays and linked lists require scanning
     elements sequentially, which forces search operations 
     into slow O(n) linear time, while BST rely on O(log n)
     that can reduce to O(n) if the tree is unbalanced.

    **      Core Hash table architecture      **

   - Hash Table Concept: 
     A Hash Table is an associative data structure
     designed to store data in key-value pairs. It
     provides direct mapping, allowing elements to 
     be retrieved based on unique keys rather than
     sequential index scanning.
   - Core Architecture:
     It utilizes a mathematical transformation known
     as a Hash Function to convert given keys into
     numerical indices within an underlying storage
     structure. In the average case, this architecture
     enables O(1) constant-time access for search,
     insertion and deletion operations, but still
     degrades to O(n) in the worst case scenario 
     if all elements have the same key.

    **   Hashing Mechanism & Structural Logic   **

   - Dual-Character Indexing:
     Maps keys into a fixed grid within the two-dimensional
     array (729 total buckets) by a custom hash function
     using the first character for the row index and 
     the second for the column index.
   - Character Mapping Rules:
     Letters 'A' through 'Z' (case-insensitive) map to
     indices (0 - 25); while special characters, numbers
     or missing characters map to index (26).
   - Fixed Grid Architecture:
     Eliminates dynamic array resizing overhead by 
     maintaining a static 2D grid of bucket head pointers.

    **    Collision Resolution & Complexity     **

   - Separate Chaining Strategy:
     Each cell in the two-dimensional matrix acts as
     the head of a dynamic singly linked list to resolve
     collisions and store multiple entries.
   - Search Performance:
     Delivers near O(1) average search time. If multiple
     entries share the exact same first two characters,
     search degrades to O(n) along that specific chain.
   - Memory Vs Speed Trade-off:
     Uses (729) bucket pointers to minimize collision
     frequency, trading lightweight memory space for 
     fast search performance without wasting lots of
     memory with empty unused buckets.

    **          Layout & Memory Control          **

   - Dynamic Allocation:
     Allocates nodes dynamically on the heap with
     isolated memory allocation for data storage.
   - Safe Operations:
     Supports adding, searching, and removing entries
     while preserving pointer linkage across all 
     bucket chains.
   - Resource Cleanup:
     Traverses all buckets on program exit or reset
     operations, freeing every allocated node and 
     data storage from the heap to guarantee zero
     memory leaks.

    **               Program Goal               **

   - The main objective of this program is to understand
     the hash table mechanics and build a highly stable
     and efficient dictionary system in C by combining
     multi-level array hashing with dynamic linked lists,
     ensuring solid performance across all lookup and
     storage operations.
     
    **              Time Complexity              **

   - Insert new element into the table:       Average(1), O(n).
   - Delete specific element from table:      Average(1), O(n).
   - Search for specific element in table:    Average(1), O(n).
   - Update specific element in table:        Average(1), O(n).
   - Get the current size of the table:            O(1).                   "Thanks to size entity"
   - Get the current load factor of the table:     O(1).                   "Thanks to size entity"
   - Get the current empty and full buckets:       O(1).               "Thanks to fixed table structure"
   - Get the maximum chain length in the table:    O(n).        "Require traversal to check length of all chains"
   - Display all elements of the table:            O(n).           "Require traversal to access all elements"
   - Count the actual number of element in table:  O(n).           "Require traversal to count all elements"
   - Reset the table to the initial state.         O(n).              "Require traversal to free all nodes"
   - Destroy the table at the end of the program:  O(n).              "Require traversal to free all nodes"
   */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define dimension_len 27
#define name_cap      30
#define number_cap    20

typedef struct node{
  char   name[name_cap];
  char   number[number_cap];
  struct node* next;
} node;

typedef struct {
  node* buckets[dimension_len][dimension_len];
  int   size;
} HTABLE;

typedef struct {
  int row_key;
  int column_key;
} KEY;

//input functions.
char get_char(char* request);                          //this function to get a character from the user.
int get_int(char* request);                            //this function to get an integer value from user.
void get_string(char* request, char* input, int len);  //this function to get a string from the user.
void display_template();         //this function to display the template of valid operations on the hash table.

//Hash table functions.
HTABLE* init_table();                              //this function to initialize a new hash table.
node* create_node(char* name, char* number);    //this function to create a new node for given data.
KEY hash_function(char* name);          //this function to get the appropriate key for elemnts.
int insert_into(HTABLE* table, node* ptr);  //this function to insert a new element into hash table.
int delete_element(HTABLE* table, char* target);  //this function to delete specific element from the table.
int update_element(HTABLE* table, char* target, char* new_num); //this function to update specific element in the table.
node* search_for(HTABLE* table, char* target);  //this function to search fot specific element in the table.
int get_size(HTABLE* table);            //this function to get the current number of elements in the hash table.
void display_table(HTABLE* table);      //this function to display all elements in the hash table.
int is_empty_section(node** section);   //this function to check if the section is empty or has stored elements.
void handle_display_section(HTABLE* table, char input); //this function to handle user input and display desired section.
void display_section(node** section, int section_key);  //this function to display specific section in the table.
float get_load_factor(HTABLE* table);   //this function to get the current load factor of the hash table.
int get_table_status(HTABLE* table, int* full, int* empty, int* max_chain); //this function to get the table status.
int validate_integrity(HTABLE* table);  //this function to check the size entity and makes it match the actual size.
int get_chain_length(node* root);       //this function to get the length of specific chain in the hash table.
void clear_table(HTABLE* table);        //this function to reset the hash table to the initial state.
void destroy_table(HTABLE* table);      //this function to destroy all memory allocated at program exit.
void destroy_list(node* root);          //this helper function to free all nodes in the passed chain.

int main(void){

  //initialize a new hash table.
  HTABLE* my_table = init_table();
  if (my_table == NULL){
    return 1;
  }

  //define variables for input data.
  char input_name[name_cap];
  char input_number[number_cap];
  
  //welcome the user.
  printf("\n\nWelcome to the Hash Table management system.\n");
  //display template of valid operations.
  display_template();
  //iterate to take user input.
  int code;
  do{
    code = get_int("\nEnter the code of the operation you want to perform: ");
    //check the input.
    if (code == 1){     //Insert process.
      //get the element.
      get_string("Enter the name of new element you want to insert (only 28 characters): ", input_name, name_cap);
      get_string("Enter the number of new element you want to insert (only 18 symbols): ", input_number, number_cap);  
      //create a new node for element.
      node* ptr = create_node(input_name, input_number);
      //check the pointer.
      if (ptr == NULL){
        destroy_table(my_table);
        return 1;
      }
      //insert the node in the table.
      int status = insert_into(my_table, ptr);
      //check the status.
      if (status == 1){
        printf("Element inserted successfully into the table.\n");
      }else if (status == 2){
        printf("This element already exists in the table.\n");
      }else{
        printf("Error: could not insert the new element.\n");
      }
    }else if (code == 2){   //Deletion process.
      //get the target.
      get_string("Enter name of the element you want to delete: ", input_name, name_cap);
      //delete the element.
      int status = delete_element(my_table, input_name);
      //check result.
      if (status == 1){
        printf("Element deleted successfully.\n");
      }else{
        printf("Element not found in the table.\n");
      }
    }else if (code == 3){   //Update process.
      //get the target and new data.
      get_string("Enter name of the element you want to update: ", input_name, name_cap);
      get_string("Enter the new number: ", input_number, number_cap);    
      //update the target.
      int status = update_element(my_table, input_name, input_number);
      //check result.
      if (status == 1){
        printf("Element updated successfully.\n");
      }else{
        printf("Element not found in the table.\n");
      }
    }else if (code == 4){   //Search process.
      //get the target.
      get_string("Enter name of the element you want to search for: ", input_name, name_cap);
      //get target.
      node* target = search_for(my_table, input_name);
      //check the result.
      if (target == NULL){
        printf("Element not found in the table.\n");
      }else{
        printf("Element %s: %s\n", target->name, target->number);
      }
    }else if (code == 5){   //Display table.
      //display all elements.
      display_table(my_table);
    }else if (code == 6){
      //get the required section.
      char section = get_char("Enter the section (prefix) you want to display: ");
      //display section.
      handle_display_section(my_table, section);
    }else if (code == 7){   //Get size.
      //get table size.
      int size = get_size(my_table);
      //check result.
      if (size == 0){
        printf("The table is empty! There are No elements stored in the table.\n");
      }else{
        printf("The current number of elements in the table: %i\n", size);
      }
    }else if (code == 8){   //Get status.
      //get the table status.
      int full_buckets;
      int empty_buckets;
      int max_chain;
      int status = get_table_status(my_table, &full_buckets, &empty_buckets, &max_chain);
      //check result.
      if (status == 1){
        printf("The current number of full buckets in the table: %i\n", full_buckets);
        printf("The current number of empty buckets in the table: %i\n", empty_buckets);
        printf("The maximum chain length in the table: %i\n", max_chain);
      }else{
        printf("Error: could not get the table status\n");
      }
    }else if (code == 9){   //Get load factor.
      //get load factor.
      float load_factor = get_load_factor(my_table);
      if (load_factor == 0){
        printf("The table is empty! There are No stored elements.\n");
      }else{
        printf("The current load factor of the hash table: %.4f\n", load_factor);
      }
    }else if (code == 10){    //Validate integrity.
      //validate size integrity.
      int status = validate_integrity(my_table);
      if (status == 1){
        printf("The integrity of the hash table is perfectly maintained.\n");
      }else{
        printf("Table size did not match the actual count!\nTable size updated successfully to actual count.\n");
      }
    }else if (code == 11){    //Reset process.
      //reset table.
      clear_table(my_table);
      printf("Hash table reseted successfully to the initial state.\n");
    }else if (code == 12){    //Display template.
      //display operations template.
      display_template();
    }else if (code == 13){    //Exit process.
      printf("Exit the program.\n");
    }else{                    //Invalid input.
      printf("Invalid input! Enter (12) to check operations template.\n");
    }

  }while(code != 13);     //iterate until the user enters exit code (13).

  //free all memory allocated to avoid memory leak.
  destroy_table(my_table);
  return 0;
}

char get_char(char* request){

  char value;                       //this variable to store the input data.
  int status;                       //this variable to check the result of scanf.
  do {
    printf("%s", request);           //display request to ask the user for input. 
    status = scanf("%c", &value);    //get the user input.
    while(getchar() != '\n');        //clear the buffer from '\n' or garbage input.
  } while (status == 0);     //iterate until scanf function get a valid input.

  return value;
}

int get_int(char* request){

  int value;                        //this variable to store the input data.
  int status;                       //this variable to check the result of scanf.
  do {
    printf("%s", request);           //display request to ask the user for input. 
    status = scanf("%i", &value);    //get the user input.
    while(getchar() != '\n');        //clear the buffer from '\n' or garbage input.
  } while (status == 0);     //iterate until scanf function get a valid input.

  return value;
}

void get_string(char* request, char* input, int len){

  //display request to ask user for input.
  printf("%s", request);
  //get the user input.
  char* result = fgets(input, len, stdin);
  //check result.
  if (result == NULL){
    //pass empty input and return.
    input[0] = '\0';
    return;
  }
  //clear '\n' from input.
  int length = strlen(input);
  if (length > 0 && input[length - 1] == '\n'){
    input[length - 1] = '\0';
  }else{    //else if the user enters long input.
    //clear buffer from garbage input.
    while(getchar() != '\n');
  }
  //check white spaces at the start.
  int spaces = 0;
  while (input[spaces] == ' ' || input[spaces] == '\t'){
    spaces++;
  }
  //clear spaces at the start.
  if (spaces > 0) {
    int index = 0;
    while (input[spaces] != '\0'){
      input[index] = input[spaces];
      index++;
      spaces++;
    }
    //end the copied input with '\0'.
    input[index] = '\0';
  }
  //clear spaces at the end.
  int new_len = strlen(input);
  int index = (new_len - 1);
  while (index >= 0 && (input[index] == ' ' || input[index] == '\t')){
    input[index] = '\0';
    index--;
  }
}

void display_template(){
  //display the template of operations.
  printf("These are the codes of the valid operations to perform on the Hash Table:\n");
  printf("1.Insert new element into table.                  2.Delete specific element in the table.\n");
  printf("3.Update specific element in the table.           4.Search for specific element in the table.\n");
  printf("5.Display all elements in the table.              6.Display specific section in the table.\n");
  printf("7.Get the number of elements in the table.        8.Get the current status of the table.\n");
  printf("9.Get the current load factor of the table.       10.Validate hash table integrity.\n");
  printf("11.Reset the hash table to the initial state.     12.Display operations template.          13.Exit the program.\n");
}
 
HTABLE* init_table(){
  //first allocate space for the hash table.
  HTABLE* table = malloc(sizeof(HTABLE));
  if (table == NULL){
    return NULL;
  }
  //set all buckets to NULL.
  for (int row = 0; row < dimension_len; row++){
    for (int column = 0; column < dimension_len; column++){
      table->buckets[row][column] = NULL;
    }
  }
  //set size to zero.
  table->size = 0;
  //return hash table.
  return table;
}

node* create_node(char* name, char* number){
  //allocate space for node.
  node* new_node = malloc(sizeof(node));
  if (new_node == NULL){
    return NULL;
  }
  //set the passed data to node.
  strcpy(new_node->name, name);
  strcpy(new_node->number, number);
  new_node->next = NULL;
  //return the node.
  return new_node;
}

KEY hash_function(char* name){
  //define a KEY object.
  KEY keys;
  //get the row key.
  if (name[0] == '\0'){
    keys.row_key = dimension_len - 1;
    keys.column_key = dimension_len - 1;
    return keys;
  }
  char letter_1 = toupper(name[0]);
  if (letter_1 >= 'A' && letter_1 <= 'Z'){
    keys.row_key = letter_1 - 'A';
  }else{
    keys.row_key = dimension_len - 1;
  }
  //get the column key.
  if (name[1] != '\0'){
    char letter_2 = toupper(name[1]);
    if (letter_2 >= 'A' && letter_2 <= 'Z'){
      keys.column_key = letter_2 - 'A';
    }else{
      keys.column_key = dimension_len - 1;
    }
  }else{
    keys.column_key = dimension_len - 1;
  }
  //return the keys.
  return keys;
}

int insert_into(HTABLE* table, node* ptr){
  //check the table.
  if (table == NULL || ptr == NULL){
    return 0;
  }
  //get the key for the element.
  KEY keys = hash_function(ptr->name);
  //get the insertion place.
  node* place = table->buckets[keys.row_key][keys.column_key];
  //if the place is empty.
  if (place == NULL){
    //the new node becomes the head.
    table->buckets[keys.row_key][keys.column_key] = ptr;
    table->size++;
    return 1;
  }else{    //else if the place has stored elements.
    //traverse to add node at the end of list.
    for(node* current = place; current != NULL; current = current->next){
      //if the element already stored.
      if (strcasecmp(current->name, ptr->name) == 0){
        //free the new node and return.
        free(ptr);
        return 2;
      }else if (current->next == NULL){
        //the new node becomes the new tail.
        current->next = ptr;
        table->size++;
        return 1;
      }
    }
  }
  //if any thing went wrong, free node and return.
  free(ptr);
  return 0;
}

int update_element(HTABLE* table, char* target, char* new_num){
  //check the table.
  if (table == NULL){
    return 0;
  }
  //get the key of the target.
  KEY keys = hash_function(target);
  //get the place of target.
  node* place = table->buckets[keys.row_key][keys.column_key];
  //traverse to the target.
  for (node* current = place; current != NULL; current = current->next){
    //if the target found.
    if (strcasecmp(current->name, target) == 0){
      //update his number.
      strcpy(current->number, new_num);
      return 1;
    }
  }
  //if the target not found, return 0.
  return 0;
}

int delete_element(HTABLE* table, char* target){
  //check the table.
  if (table == NULL){
    return 0;
  }
  //get the key of element.
  KEY keys = hash_function(target);
  //get the place of the element.
  node* place = table->buckets[keys.row_key][keys.column_key];
  if (place == NULL){
    return 0;
  }
  //check if it was the head of the list.
  if (strcasecmp(place->name, target) == 0){
    //delete the target and return.
    table->buckets[keys.row_key][keys.column_key] = place->next;
    free(place);
    table->size--;
    return 1;
  }
  //else if it was in the middle of list.
  for (node* current = place; current->next != NULL; current = current->next){
    //if reaching the previous node to target.
    if (strcasecmp(current->next->name, target) == 0){
      //free target and update pointers.
      node* temp = current->next;
      current->next = current->next->next;
      free(temp);
      table->size--;
      return 1;
    }
  }
  //if the target not found.
  return 0;
}

node* search_for(HTABLE* table, char* target){
  //check the table.
  if (table == NULL){
    return NULL;
  }
  //get the key of the target.
  KEY keys = hash_function(target);
  //get the place.
  node* place = table->buckets[keys.row_key][keys.column_key];
  //traverse list to search for element.
  for (node* current = place; current != NULL; current = current->next){
    //if reaching the target.
    if (strcasecmp(current->name, target) == 0){
      return current;
    }
  }
  //if target not found.
  return NULL;
}

void display_table(HTABLE* table){
  //check the table.
  if (table == NULL){
    printf("There is No hash table structure!\n");
    return;
  }else if (table->size == 0){
    printf("The hash table is empty! There are No elements to display!\n");
    return;
  }
  //traverse all sections to display elements.
  for (int row = 0; row < dimension_len; row++){
    //check if the section is empty.
    int is_empty = is_empty_section(table->buckets[row]);
    //if the section is not empty.
    if (is_empty == 0){
      //display section.
      int row_key;
      if (row < (dimension_len - 1)){
        row_key = 'A' + row;
        printf("\n\nSection %c\n", row_key);
      }else{
        row_key = dimension_len - 1;
        printf("\n\nSection special\n");
      }
      //display all elements in that section.
      display_section(table->buckets[row], row_key);
    }
  }
}

void display_section(node** section, int section_key){
  //check the section.
  if (section == NULL){
    printf("The section is empty! There are No elements to display!\n");
    return;
  }
  //check if the section is empty.
  int is_empty = is_empty_section(section);
  //if the section is empty.
  if (is_empty == 1){
    printf("The section is empty! There are No elements to display!\n");
    return;
  }
  //if the section has stored elements.
  for (int column = 0; column < dimension_len; column++){
    //if the bucket is not empty.
    if (section[column] != NULL){
      int column_key;
      if (column < (dimension_len - 1) && section_key >= 'A'){
        column_key = column + 'A';
        printf("\n  -Prefix [%c%c]:\n", section_key, column_key);
      }else if (section_key >= 'A'){
        printf("\n  -Prefix [%c]:\n", section_key);
      }else{
        printf("\n  -Prefix special:\n");
      }
      //display all elements.
      for (node* current = section[column]; current != NULL; current = current->next){
        printf("    %-28s: %s\n", current->name, current->number);
      }
    }
  }
}

void handle_display_section(HTABLE* table, char input){
  //first check table.
  if (table == NULL){
    return;
  }
  //normalize input section.
  node** section;
  int section_key;
  char code = toupper(input);
  if (code >= 'A' && code <= 'Z'){
    int index = code - 'A';
    section = table->buckets[index];
    section_key = code;
    printf("\nSection %c\n", section_key);
  }else{
    int index = dimension_len - 1;
    section = table->buckets[index];
    section_key = index;
    printf("\nSection special\n");
  }
  //call display section function.
  display_section(section, section_key);
}

int is_empty_section(node** section){
  //check the section.
  if (section == NULL){
    return 1;
  }
  //traverse to check elements.
  for (int column = 0; column < dimension_len; column++){
    //if any place has elements.
    if (section[column] != NULL){
      return 0;
    }
  }
  //if all places were empty.
  return 1;
}

int get_size(HTABLE* table){
  //check the table.
  if (table != NULL){
    return table->size;
  }
  //if the table is NULL.
  return 0;
}

float get_load_factor(HTABLE* table){
  if (table == NULL){
    return 0;
  }
  //return the load factor.
  int elements = table->size;
  int capacity = dimension_len * dimension_len;
  float load_factor = ((float) elements / capacity);
  return load_factor;
}

int get_table_status(HTABLE* table, int* full, int* empty, int* max_chain){
  //check the table.
  if (table == NULL){
    return 0;
  }
  //get the table status.
  int empty_buckets = 0;
  int full_buckets = 0;
  int chain_length = 0;
  //traverse to get buckets status.
  for (int row = 0; row < dimension_len; row++){
    for (int column = 0; column < dimension_len; column++){
      //check the bucket status.
      node* bucket = table->buckets[row][column];
      if (bucket == NULL){
        empty_buckets++;
      }else{
        full_buckets++;
        int new_len = get_chain_length(bucket);
        //compare new length with current one.
        if (new_len > chain_length){
          chain_length = new_len;
        }
      }
    }
  }
  //pass the results.
  *full = full_buckets;
  *empty = empty_buckets;
  *max_chain = chain_length;
  return 1;
}

int validate_integrity(HTABLE* table){
  //check the table.
  if (table == NULL){
    return 0;
  }
  //check the actual number of elements in the table.
  int actual_size = 0;
  //iterate to get actual size.
  for (int row = 0; row < dimension_len; row++){
    for (int column = 0; column < dimension_len; column++){
      //check the bucket.
      node* bucket = table->buckets[row][column];
      if (bucket != NULL){
        int count = get_chain_length(bucket);
        actual_size += count;
      }
    }
  }
  //compare actual size with stored size.
  if (table->size != actual_size){
    table->size = actual_size;
    return 0;
  }
  //if size is correct.
  return 1;
}

int get_chain_length(node* root){
  //check the root.
  if (root == NULL){
    return 0;
  }
  //iterate over chain to get length.
  int length = 0;
  for (node* current = root; current != NULL; current = current->next){
    length++;
  }
  //return result.
  return length;
}

void clear_table(HTABLE* table){
  //check the table.
  if (table == NULL){
    return;
  }
  //free all stored nodes.
  for(int row = 0; row < dimension_len; row++){
    for(int column = 0; column < dimension_len; column++){
      //check the bucket.
      node* bucket = table->buckets[row][column];
      if (bucket != NULL){
        destroy_list(bucket);
        //reset bucket to NULL.
        table->buckets[row][column] = NULL;
      }
    }
  }
  //reset size to zero.
  table->size = 0;
}

void destroy_table(HTABLE* table){
  //check the table.
  if (table == NULL){
    return;
  }
  //free all stored nodes.
  for(int row = 0; row < dimension_len; row++){
    for(int column = 0; column < dimension_len; column++){
      //check the bucket.
      node* bucket = table->buckets[row][column];
      if (bucket != NULL){
        destroy_list(bucket);
      }
    }
  }
  //free the table structure.
  free(table);
}

void destroy_list(node* root){
  //check the root.
  if (root == NULL){
    return;
  }
  //free all nodes in the list.
  node* current = root;
  while(current != NULL){
    node* temp = current;
    current = current->next;
    free(temp);
  }
}