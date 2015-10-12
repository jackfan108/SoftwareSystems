/* Example code for Software Systems at Olin College.

Based on an example from http://www.learn-c.org/en/Linked_lists

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node * next;
} Node;

Node *make_node(int val, Node *next) {
    Node *node = malloc(sizeof(Node));
    node->val = val;
    node->next = next;
    return node;
}

void print_list(Node *head) {
    Node *current = head;

    while (current != NULL) {
        printf("%d\n", current->val);
        current = current->next;
    }
}

int pop(Node **head) {

    int retval;
    Node *next_node;
    Node* first = *head;

    if (first == NULL) {
        return -1;
    }

    next_node = first->next;
    retval = first->val;
    free(first);
    *head = next_node;

    return retval;
}

// Add a new element to the beginning of the list.
void push(Node **head, int val) {
    *head = make_node(val, *head);
}

void append(Node *head, int val) {
    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    Node* new_node = make_node(val, NULL);
    current->next = new_node;
}

// Remove the first element with the given value; return the number
// of nodes removed.
int remove_by_value(Node **head, int val) {
    if ((*head)->val == val) {
        pop(head);
        return 1;
    }
    Node* current = *head;
    Node* next = current->next;

    while(next->next != NULL) {
        //printf("Current: %d\n", current->val);
        //printf("Next: %d\n", next->val);
        if (next->val == val) {
            Node* temp = next->next;
            free(current->next);
            current->next = temp;
            return 1;
        }
        current = next;
        next = next->next;
    }

    /*
    Node current = *(*head);
    Node next = *current.next;
    while (next.next != NULL) {
        printf("Current: %d\n", current.val);
        printf("Next: %d\n", next.val);
        if (next.val == val) {
            Node* temp = next.next;
            free(current.next);
            current.next = temp;
            return 1;
        }
        current = next;
        next = *next.next;
    }*/
    return 0;
}

// Reverse the elements of the list without allocating new nodes.
void reverse(Node **head) {
    
    if ((*head)->next == NULL) {
        return;
    }
    
    Node* previous = *head;
    Node* current = previous->next;
    Node* next;

    previous->next = NULL; // remember to set the new last value to NULL, otherwise you get a recursive linked list

    while (1) {
        if (current->next != NULL) {
            next = current->next;
            current->next = previous;
            previous = current;
            current = next;
            continue;
        }
        current->next = previous;
        *head = current;
        break;
    }
}


int main() {
    Node *test_list = make_node(1, NULL);
    int i;
    for (i = 2; i <= 12; i++) {
        append(test_list, i);
    }

    int retval = pop(&test_list);
    push(&test_list, retval+10);

    remove_by_value(&test_list, 3);
    remove_by_value(&test_list, 7);

    reverse(&test_list);

    print_list(test_list);
}