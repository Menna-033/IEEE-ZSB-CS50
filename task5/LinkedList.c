#include <stdio.h>
#include <stdlib.h>

// تعريف هيكل البيانات
typedef struct node
{
    int number;
    struct node *next;
} node;

// دوال التحكم في القائمة
void insert(node **head, int number);
void print_list(node *head);
void free_list(node *head);

int main(void)
{
    node *list = NULL;

    // إضافة عناصر للقائمة
    insert(&list, 10);
    insert(&list, 20);
    insert(&list, 30);

    // طباعة القائمة
    printf("Linked List contents:\n");
    print_list(list);

    // تحرير الذاكرة
    free_list(list);
    return 0;
}

// دالة إضافة عنصر (Insert at beginning)
void insert(node **head, int number)
{
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL)
    {
        return; // فشل تخصيص الذاكرة
    }
    new_node->number = number;
    new_node->next = *head; // الجديد يشير للقديم
    *head = new_node;       // الرأس يصبح هو الجديد
}

// دالة طباعة القائمة
void print_list(node *head)
{
    node *ptr = head;
    while (ptr != NULL)
    {
        printf("%i\n", ptr->number);
        ptr = ptr->next;
    }
}

// دالة تحرير الذاكرة
void free_list(node *head)
{
    while (head != NULL)
    {
        node *tmp = head->next;
        free(head);
        head = tmp;
    }}