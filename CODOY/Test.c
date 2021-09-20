#include <stdio.h>
#include <string.h>
#include "Exercise1.h"
#include "CircularArrayQ.h"

/** \fn int get_queue_length(CircularArrayQueue list);
 *  \brief Get the number of elements in the current queue.
 *  \param list The current queue.
*/
int get_queue_length(CircularArrayQueue list) {
    int length = 0;
    if(list.front < list.rear) {
        length = list.rear - list.front + 1;
        return length;
    } else {
        length = MAX - (list.front - list.rear - 1);
        return length;
    }
}

/** \fn PersonLinkedList get_all_females(CircularArrayQueue list);
 *  \brief Returns all females as a linked list using the current list without removing them in the current list.
 *  \param list The current queue.
 *  Note: Use the queue basic operations (enqueue, dequeue, front)
*/
PersonLinkedList get_all_females(CircularArrayQueue list) {
    int i;
    PersonLinkedList head = NULL;

    for(i = list.front; i % MAX != (list.rear + 1) % MAX; i++) {
        if(list.data[i % MAX].sex == 'F') {
            PersonNode temp;
            temp.elem = list.data[i % MAX];
            if(head == NULL) {
                temp.next = NULL;
            } else {
                temp.next = head;
            }
            head = &temp;
        } 
    }
        
    return head;
}

/** \fn PersonDynamicArrayList remove_all_males(CircularArrayQueue *list);
 *  \brief Remove all males in the current list and returns the removed males as a dynamic array list.
 *  \param list The current queue.
 *  Note: Use the concept of queue with out using the basic operations.
*/
PersonDynamicArrayList remove_all_males(CircularArrayQueue *list) {
    int i;
    PersonDynamicArrayList res;
    res.max = 10;
    res.count = 0;
    res.data = malloc(sizeof(Person) * res.max);
    
    for(i = list->front; i % MAX != (list->rear + 1) % MAX; i++) {
        if(list->data[i % MAX].sex == 'M') {
            if(res.count == res.max) {
                    res.max *=2;
                    res.data = realloc(res.data, sizeof(Person) * res.max);
            }
            res.data[res.count++] = list->data[i % MAX];
            int j;
            for(j = i; j % MAX != list->rear % MAX; j++) {
                list->data[j % MAX] = list->data[(j + 1) % MAX]; // move
            } 
            list->rear--;
        }
    }

    return res;
}

int main(void) 
{
    Person p;
    bool retval;
    CircularArrayQueue list;
    PersonDynamicArrayList m;
    PersonLinkedList females;
    
    list = create_array_queue();
    init_array_queue(&list);

    p = create_array_queue("Roe", 'F', "Cebu");
    retval = enqueue(&list, p);

    p = create_array_queue("Ann", 'F', "Cebu");
    retval = enqueue(&list, p);

    p = create_array_queue("Row", 'M', "Carcar");
    retval = enqueue(&list, p);

    return 0;
}

