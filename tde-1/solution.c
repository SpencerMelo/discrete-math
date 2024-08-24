/*
  Author: Spencer Matheus de Melo.
  Date: 08/24/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Element Element;
struct Element {
  char value[64];
  Element* next;
};

bool containsValue(Element* head, Element* target) {
  Element* curr = head;
  while (curr != NULL) {
    if (strcmp(curr->value, target->value) == 0) return true;
    curr = curr->next;
  }
  return false;
}

void printElementList(Element *head) {
  printf("{");
  Element* curr = head;
  while (curr != NULL) {
    if (curr->next != NULL) {
      printf(" %s,", curr->value);
    } else {
      printf(" %s", curr->value);
    }
    curr= curr->next;
  }
  printf(" }");
}

Element* getElements(FILE *filePointer) {
  Element* result = NULL;
  Element* currElement = NULL;
  char buffer[64];
  int bufferPos = 0;
  char curr;

  do {
    curr = fgetc(filePointer);
    if (curr == ',' || curr == 10) {
      Element* newElement = (Element*) malloc(sizeof(Element));
      buffer[bufferPos++] = '\0';

      strcpy(newElement->value, buffer);
      if (containsValue(result, newElement)) {
        free(newElement);
      } else {
        if (result == NULL) result = newElement;
        if (currElement == NULL) {
          currElement = newElement;
        } else {
          currElement->next = newElement;
          currElement = currElement->next;
        }
      }
      bufferPos = 0;
      buffer[bufferPos] = '\0';
    } else {
      buffer[bufferPos++] = curr;
    }
  } while (curr != 10);
  return result;
}

void append(Element** head, char val[64]) {
  Element* new = (Element*) malloc(sizeof(Element));
  strcpy(new->value, val);

  if (*head == NULL) {
    *head=new;
  } else {
    (*head)->next = new;
    *head=new;
  }
}

Element* unionSets(Element* setA, Element* setB) {
  Element* curr = (Element*) malloc(sizeof(Element));
  strcpy(curr->value, setA->value);
  Element* head = curr;

  while(setA != NULL) {
    if (!containsValue(head, setA)) append(&curr, setA->value);
    setA=setA->next;
  }
  while(setB != NULL) {
    if (!containsValue(head, setB)) append(&curr, setB->value);
    setB=setB->next;
  }
  return head;
}

Element* intersect(Element* setA, Element* setB) {
    Element* curr = NULL;
    Element* head = NULL;
    while (setA != NULL) {
      if (containsValue(setB, setA)) {
        if (curr == NULL) {
          curr = (Element*) malloc(sizeof(Element));
          strcpy(curr->value, setA->value);
          head=curr;
        } else {
          append(&curr, setA->value);
        }
      }
      setA=setA->next;
    }
    return head;
}

Element* difference(Element* setA, Element* setB) {
  Element* curr = NULL;
  Element* head = NULL;

  Element* currA = setA;
  while (currA != NULL) {
    if (!containsValue(setB, currA)) {
      if (curr == NULL) {
        curr = (Element*) malloc(sizeof(Element));
        strcpy(curr->value, currA->value);
        head=curr;
      } else {
        append(&curr, currA->value);
      }
    }
    currA=currA->next;
  }

  while (setB != NULL) {
    if (!containsValue(setA, setB)) {
      if (curr == NULL) {
        curr = (Element*) malloc(sizeof(Element));
        strcpy(curr->value, setB->value);
        head=curr;
      } else {
        append(&curr, setB->value);
      }
    }
    setB=setB->next;
  }
  return head;
}

Element* cartesianProduct(Element* setA, Element* setB) {
  Element* cartesian = NULL;
  Element* head = NULL;

  while(setA != NULL) {
    Element* tempB = setB;
    while (tempB != NULL) {
      char product[64];
      strcat(product, "(");
      strcat(product, setA->value);
      strcat(product, ",");
      strcat(product, tempB->value);
      strcat(product, ")");

      if (cartesian == NULL) {
        cartesian = (Element*) malloc(sizeof(Element));
        strcpy(cartesian->value, product);
        head=cartesian;
      } else {
        append(&cartesian, product);
      }
      product[0] = '\0';
      tempB=tempB->next;
    }
    setA=setA->next;
  }
  return head;
}

int main(int argc, char *argv[]) {
  FILE *filePointer;
  filePointer = fopen(argv[1], "r");

  if (filePointer == NULL) {
    printf("Not able to open file '%s'\n", argv[1]);
    return 1;
  }

  fgetc(filePointer); // Discard count from line 1
  fgetc(filePointer); // Discard '\n' from line 1

  char curr = fgetc(filePointer);
  while (curr != EOF) {
    char operation = curr;
    fgetc(filePointer); // Discard \n

    Element* setA = getElements(filePointer);
    Element* setB = getElements(filePointer);

    curr = fgetc(filePointer); // Get next operation

    switch (operation) {
      case 'U': {
        printf("Union: set A ");
        printElementList(setA);
        printf(", set B ");
        printElementList(setB);
        printf(". Result: ");
        printElementList(unionSets(setA, setB));
        break;
      }
      case 'I': {
        printf("Intersection: set A ");
        printElementList(setA);
        printf(", set B ");
        printElementList(setB);
        printf(". Result: ");
        printElementList(intersect(setA, setB));
        break;
      }
      case 'D': {
        printf("Difference: set A ");
        printElementList(setA);
        printf(", set B ");
        printElementList(setB);
        printf(". Result: ");
        printElementList(difference(setA, setB));
        break;
      }
      case 'C': {
        printf("Cartesian: set A ");
        printElementList(setA);
        printf(", set B ");
        printElementList(setB);
        printf(". Result: ");
        printElementList(cartesianProduct(setA, setB));
        break;
      }
    }
    puts("");
  }
}
