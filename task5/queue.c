#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int number;
    struct node *next;
} node;

// دوال الـ Queue
void enqueue(node **head, int number);
int dequeue(node **head);
void print_queue(node *head);

int main(void) {
    node *queue = NULL;

    // إضافة عناصر للطابور (أول واحد يدخل هو أول واحد يخرج)
    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);

    printf("Queue contents (Front to Back):\n");
    print_queue(queue);

    // سحب عناصر من الطابور
    printf("\nDequeued: %i\n", dequeue(&queue));
    printf("Dequeued: %i\n", dequeue(&queue));

    printf("\nQueue after dequeues:\n");
    print_queue(queue);

    return 0;
}

// إضافة في النهاية (Enqueue)
void enqueue(node **head, int number) {
    node *new_node = malloc(sizeof(node));
    new_node->number = number;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        node *ptr = *head;
        // نتحرك حتى نصل لآخر عنصر
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = new_node;
    }
}

// حذف من البداية (Dequeue)
int dequeue(node **head) {
    if (*head == NULL) return -1;
    
    node *tmp = *head;
    int val = tmp->number;
    *head = (*head)->next;
    free(tmp);
    return val;
}

// طباعة الطابور
void print_queue(node *head) {
    node *ptr = head;
    while (ptr != NULL) {
        printf("%i -> ", ptr->number);
        ptr = ptr->next;
    }
    printf("NULL\n");
}