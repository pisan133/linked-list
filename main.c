#include <stdio.h>
#include <stdlib.h>

// self-referential Node structure
struct Node {
  // each Node contains an int
  int data;
  // pointer to next node */
  struct Node *nextPtr;
};

// synonym for struct Node
typedef struct Node Node;

// print all nodes starting from given node
void print(Node *curr) {
  while (curr != NULL) {
    printf("%d --> ", curr->data);
    curr = curr->nextPtr;
  }
  printf("NULL\n");
}

// get an int from keyboard
int getInt(const char *prompt) {
  char *cstr;
  char buffer[256];
  printf("%s", prompt);
  cstr = fgets(buffer, 255, stdin);
  return atoi(cstr);
}

// add a new item to the end of the list
void add(Node *curr, int value) {
  // create new node
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = value;
  newNode->nextPtr = NULL;
  // find the tail
  while (curr->nextPtr != NULL) {
    curr = curr->nextPtr;
  }
  curr->nextPtr = newNode;
}

// free all nodes
void freeAll(Node *curr) {
  while (curr != NULL) {
    Node *todelete = curr;
    curr = curr->nextPtr;
    printf("Deleting %d\n", todelete->data);
    free(todelete);
  }
}

// get new values from user and add them to the list
Node *createLinkedList() {
  // head is set to a node instead of NULL for simplicity
  Node *head = (Node *)malloc(sizeof(Node));
  head->data = -1000;
  head->nextPtr = NULL;
  int input = getInt("Enter a number (-1 to end): ");
  while (input != -1) {
    add(head, input);
    print(head);
    input = getInt("Enter a number (-1 to end): ");
  }
  // freeAll(head);
  return head;
}

// dummy node will be skipped
int sumUp(Node *dummy) {
  int sum = 0;
  Node *curr = dummy->nextPtr;
  while (curr != NULL) {
    sum += curr->data;
    curr = curr->nextPtr;
  }
  return sum;
}

int multiply(Node *dummy) {
  int product = 1;
  Node *curr = dummy->nextPtr;
  while (curr != NULL) {
    product *= curr->data;
    curr = curr->nextPtr;
  }
  return product;
}

int length(Node *dummy) {
  int ln = 0;
  Node *curr = dummy->nextPtr;
  while (curr != NULL) {
    ++ln;
    curr = curr->nextPtr;
  }
  return ln;
}

double average(Node *dummy) { return (double)sumUp(dummy) / length(dummy); }

// https://repl.it/@pisanuw/133linkedlist

// insert Node with value before existing Node with other
void addBefore(Node *dummy, int value, int other) {
  Node *prev = dummy;
  Node *curr = dummy->nextPtr;
  while (curr->data != other) {
    printf("Looking at %d\n", curr->data);
    curr = curr->nextPtr;
    prev = prev->nextPtr;
  }
  printf("Prev has value %d\n", prev->data);
  printf("Curr has value %d\n", curr->data);
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = value;
  newNode->nextPtr = curr;
  prev->nextPtr = newNode;
}

// insert Node with value after existing Node with other
void addAfter(Node *dummy, int value, int other) {
  Node *curr = dummy->nextPtr;
  while (curr->data != other) {
    printf("Looking at %d\n", curr->data);
    curr = curr->nextPtr;
  }
  printf("Curr has value %d\n", curr->data);
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = value;
  newNode->nextPtr = curr->nextPtr;
  curr->nextPtr = newNode;
}

int main(void) {
  printf("Hello World\n");
  Node *head = createLinkedList();
  // print it
  printf("Inside main: ");
  print(head);
  // sum up all values - write a new function
  printf("Sum of all values is: %d\n", sumUp(head));
  printf("Product of all values is: %d\n", multiply(head));

  printf("Average of all values is: %f\n", average(head));
  // 9 comes before 10
  // assuming the list is [7 - 8 - 10 ]
  addBefore(head, 9, 10);
  print(head);
  addAfter(head, 111, 10);
  print(head);
  // delete it
  freeAll(head);
  return 0;
}