#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
  int data;
  struct node *previous;
  struct node *next;
};

struct node *head, *tail = NULL;

void addNode(int data) {
  struct node *newNode = (struct node*)malloc(sizeof(struct node));
  newNode->data = data;
  if(head == NULL) {
      head = tail = newNode;
      head->previous = NULL;
      tail->next = NULL;
  }
  else {
      tail->next = newNode;
      newNode->previous = tail;
      tail = newNode;
      tail->next = NULL;
  }
}

void sortList() {
  struct node *current = NULL, *index = NULL;
  int temp;
  if(head == NULL){
      return;
  }
  else {
      for(current = head; current->next != NULL; current = current->next) {
          for(index = current->next; index != NULL; index = index->next) {
              if(current->data > index->data) {
                  temp = current->data;
                  current->data = index->data;
                  index->data = temp;
              }
          }
      }
  }
}

void display() {
  struct node *current = head;
  if(head == NULL) {
      printf("List is empty\n");
      return;
  }
  while(current != NULL) {
      printf("%d ",current->data);
      current = current->next;
  }
  printf("\n");
}






int main()
{
  //Add nodes to the list
  addNode(7);
  addNode(1);
  addNode(4);
  addNode(5);
  addNode(2);

  //Displaying original list
  printf("Original list: \n");
  display();

  //Sorting list
  sortList();

  //Displaying sorted list
  printf("Sorted list: \n");
  display();

  return 0;
}