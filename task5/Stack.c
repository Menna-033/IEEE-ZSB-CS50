#include <stdio.h>
#include <stdlib.h>

// تعريف الـ node كما اعتدنا
typedef struct node {
    int number;
    struct node *next;
} node;

// دوال الـ Stack
void push(node **stack, int number);
int pop(node **stack);
void print_stack(node *stack);

int main(void) {
    node *stack = NULL;

    // إضافة أرقام للـ Stack
    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    printf("Stack after pushes:\n");
    print_stack(stack);

    // سحب أرقام من الـ Stack
    printf("\nPopped: %i\n", pop(&stack));
    printf("Popped: %i\n", pop(&stack));

    printf("\nStack after pops:\n");
    print_stack(stack);

    return 0;
}

// دالة الـ Push (هي نفسها الـ Insert التي كتبناها)
void push(node **stack, int number) {
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL) return;
    new_node->number = number;
    new_node->next = *stack;
    *stack = new_node;
}

// دالة الـ Pop (تحذف العنصر من الأعلى وترجع قيمته)
int pop(node **stack) {
    if (*stack == NULL) return -1; // إذا كان الـ Stack فارغاً
    
    node *tmp = *stack;
    int val = tmp->number;
    *stack = (*stack)->next;
    free(tmp);
    return val;
}

// للطباعة
void print_stack(node *stack) {
    node *ptr = stack;
    while (ptr != NULL) {
        printf("%i\n", ptr->number);
        ptr = ptr->next;
    }
}