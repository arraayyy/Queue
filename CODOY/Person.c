#include <stdio.h>
#include <string.h>
#include "Person.h"
#include "CircularArrayQ.h"

#define PERSON_H

#define MAX_LIST 20
#define MAX_VSPACE 30

typedef char String[30];

typedef struct {
    String name;
    char sex;
    String city;
} Person;

typedef struct {
    Person data[MAX_LIST];
    int count;
} PersonStaticArrayList;

typedef struct {
    Person *data;
    int count;
    int max;
} PersonDynamicArrayList, *PersonDynamicArrayListPointer;

typedef struct node{
    Person elem;
    struct node *next;
} PersonNode, *PersonLinkedList;

typedef int Position;
typedef int PersonCusorBasedList;

typedef struct {
    Person elem;
    Position next;
} CNode;

typedef struct {
    CNode data[MAX_VSPACE];
    Position avail;
} VSpace;


Person createPerson(String name, char sex, String city) {
    Person p;

    strcpy(p.name, name);
    p.sex = sex;
    strcpy(p.city, city);

    return p;
}

void displayPersonInfo(Person p) {
     printf("{%s | %c | %s}", p.name, p.sex, p.city);
}

/* Static Array List*/
void init_SAL(PersonStaticArrayList *list) {
    list->count = 0;
}
void insert_first_SAL(PersonStaticArrayList *list, Person p) {
    int i;
    if(list->count != MAX_LIST){
        for(i = list->count; i > 1; i--){
            list->data[i] = list->data[i - 1];
        }
        list->data[0] = p;
        list->count += 1;
    }
}
void insert_last_SAL(PersonStaticArrayList *list, Person p) {
    if(list->count != MAX_LIST){
        list->data[list->count] = p;
        list->count++;
    }
}
void insert_at_SAL(PersonStaticArrayList *list, Person p, int index) {
     int i;
    if(list->count != MAX_LIST){
        for(i = list->count; i > index + 1; i--){
            list->data[i] = list->data[i - 1];
        }
        list->data[index] = p;
        list->count += 1;
    }
}
void delete_first_SAL(PersonStaticArrayList *list) {
    int i;
    if(list->count > 0){
        for(i = 0;i < list->count; i++){
            list->data[i] = list->data[i + 1];
        }
        list->count -= 1;
    }
}
void delete_last_SAL(PersonStaticArrayList *list) {
      if(list->count > 0){
        list->count -= 1;
    }
}
void delete_by_sex_SAL(PersonStaticArrayList *list, char sex) { // all ocurrences
    int i, j;
    if(list->count>0){
        for(i = 0; i < list->count; i++){
            if(list->data[i].sex == 'F'){
                for(j = i; j < list->count; j++){
                    list->data[j] = list->data[j + 1];
                }
                list->count -= 1;
            }
        }
    }
}
void display_SAL(PersonStaticArrayList list) {
    int i;
    if(list.count  >0){
        for(i = 0;i < list.count; i++){
            displayPersonInfo(list.data[i]);
        }
    }
}

/* Dynamic Array List - v1 
 * Doubles the maximum size of the array when full.
 */
void init_DAL(PersonDynamicArrayList *list);
void insert_first_DAL(PersonDynamicArrayList *list, Person p) {
    int i;
    if(list->count == list->max && list->max < MAX_LIST){
        list->data = realloc(list->data, (list->max * 2) * sizeof(Person));
        list->max *= 2;
    }
    if(list->count < list->max){
        for(i = list->count; i>1; i--){
            list->data[i] = list->data[i - 1];
        }
        list->data[0] = p;
        list->count += 1;
    }
}
void insert_last_DAL(PersonDynamicArrayList *list, Person p) {
    int i;
    if(list->count == list->max && list->max < MAX_LIST){
        list->data = realloc(list->data, (list->max * 2) * sizeof(Person));
        list->max *= 2;
    }
    if(list->count < list->max){
        list->data[list->count] = p;
        list->count += 1;
    }
}
void insert_at_DAL(PersonDynamicArrayList *list, Person p, int index) {
    int i;
    if(list->count == list->max && list->max < MAX_LIST){
        list->data = realloc(list->data, (list->max * 2) * sizeof(Person));
        list->max *= 2;
    }
    if(list->count < list->max){
        for(i = list->count; i > index + 1; i--){
            list->data[i] = list->data[i - 1];
        }
        list->data[index] = p;
        list->count += 1;
    }
}
void delete_first_DAL(PersonDynamicArrayList *list) {
    int i;
    if(list->count > 0){
        for(i = 0; i < list->count; i++){
            list->data[i] = list->data[i  +1];
        }
        list->count -= 1;
    }
}
void delete_last_DAL(PersonDynamicArrayList *list) {
    if(list->count > 0){
        list->count -= 1;
    }
}
void delete_by_city_DAL(PersonDynamicArrayList *list, String city) { // first ocurrence
    int i;
    if(list->count > 0){
        for(i = 0; i < list->count; i++){
            if(strcmp(list->data[i].city, city) == 0){
                for(; i<list->count; i++){
                    list->data[i] = list->data[i + 1];
                }
                list->count -= 1;
                break;
            }
        }
    }
}
void display_DAL(PersonDynamicArrayList list) {
    int i;
    for(i  =0; i < list.count; i++){
        displayPersonInfo(list.data[i]);
    }
}

/* Dynamic Array List - v2 
 * Doubles the maximum size of the array when full.
 * The Dynamic Array List must also be created in the heap.
 */
void init_DAL_2(PersonDynamicArrayList **list);
void insert_first_DAL_2(PersonDynamicArrayList *list, Person p) {
    int i;
    if(list->count == list->max && list->max < MAX_LIST){
        list->data = realloc(list->data, (list->max * 2) * sizeof(Person));
        list->max *= 2;
    }
    if(list->count < list->max){
        for(i = list->count; i > 1; i--){
            list->data[i] = list->data[i - 1];
        }
        list->data[0] = p;
        list->count += 1;
    }
}
void insert_last_DAL_2(PersonDynamicArrayList *list, Person p) {
    int i;
    if(list->count == list->max && list->max < MAX_LIST){
        list->data = realloc(list->data, (list->max * 2) * sizeof(Person));
        list->max *= 2;
    }
    if(list->count < list->max){
        list->data[list->count] = p;
        list->count += 1;
    }
}
void insert_at_DAL_2(PersonDynamicArrayList *list, Person p, int index) {
    int i;
    if(list->count == list->max && list->max < MAX_LIST){
        list->data = realloc(list->data, (list->max*2)*sizeof(Person));
        list->max *= 2;
    }
    if(list->count < list->max){
        for(i = list->count; i>index+1; i--){
            list->data[i] = list->data[i - 1];
        }
        list->data[index] = p;
        list->count += 1;
    }
}
void delete_first_DAL_2(PersonDynamicArrayList *list) {
    int i;
    if(list->count > 0){
        for(i = 0; i < list->count; i++){
            list->data[i] = list->data[i+1];
        }
        list->count -= 1;
    }
}
void delete_last_DAL_2(PersonDynamicArrayList *list) {
     if(list->count > 0){
        list->count -= 1;
    }
}
void delete_by_name_DAL_2(PersonDynamicArrayList *list, String name) { // last ocurrence
    int i, j;
    if(list->count > 0){
        for(i = 0; i < list->count; i++){
            if(strcmp(list->data[i].name, name) == 0){
                j = i;
            }
        }
        for(i = j; i < list->count; i++){
            list->data[i] = list->data[i+1];
        }
        list->count -= 1;
    }
}
void display_DAL_2(PersonDynamicArrayList list) {
    int i;
    for(i = 0; i < list.count; i++){
        printf("\n");
        displayPersonInfo(list.data[i]);
    }
}

/* Singly Linked List */
void insert_first_LL(PersonLinkedList *list, Person p) {
     PersonLinkedList temp, *ctr;
    temp=malloc(sizeof(PersonNode));
    if(temp != NULL){
        temp->elem = p;
        temp->next = *list;
        *list = temp;
    }
}
void insert_last_LL(PersonLinkedList *list, Person p) {
    PersonLinkedList temp, *ctr;
    temp=malloc(sizeof(PersonNode));
    if(temp != NULL){
        for(ctr = list; *ctr != NULL; ctr = &(*ctr)->next){
        }
        temp->elem = p;
        temp->next = *ctr;
        *ctr = temp;
    }
}
void insert_after_LL(PersonLinkedList *list, Person p, String name) {
    PersonLinkedList temp, *ctr;
    temp = malloc(sizeof(PersonNode));
    if(temp != NULL){
        for(ctr = list; *ctr != NULL && strcmp((*ctr)->elem.name, name)<0; ctr = &(*ctr)->next){
        }
        temp->next = *ctr;
        *ctr = temp;
    }
}
void delete_first_LL(PersonLinkedList *list) {
    PersonLinkedList tmp;
    tmp = *list;
    *list = tmp->next;
}
void delete_last_LL(PersonLinkedList *list) {
    PersonLinkedList *ctr;
    for(ctr = list; (*ctr)->next != NULL; ctr = &(*ctr)->next){}
    free(*ctr);
    *ctr = NULL;
}
void delete_by_city_LL(PersonLinkedList *list, String city) { // all ocurrences
    PersonLinkedList *ctr, tmmp;
    for(ctr = list; *ctr != NULL; ctr = &(*ctr)->next){
        if(strcmp((*ctr)->elem.city, city) == 0){
            temp = *ctr;
            *ctr = temp->next;
            free(temp);
        }
    }
}
void display_LL(PersonLinkedList list) {
    PersonLinkedList ctr;
    for(ctr = list; ctr != NULL; ctr = ctr->next){
        printf("\n");
        displayPersonInfo(ctr->elem);
    }
}

/* Implement all VSpace conncept and Cusor Based List*/
void init_vspace(VSpace *vs) {
     int i;
    for(i=MAX_VSPACE-1; i>=0; --i) {
        vs->data[i].next = i-1;
    }
    vs->avail = MAX_VSPACE-1;
}
Position alloc_space(VSpace *vs) {
    Position avail = vs->avail;

    if(avail != -1) {
        vs->avail = vs->data[avail].next;
    }

    return avail;
}
void free_space(VSpace *vs, Position index) {
    if(index != -1 && index < MAX_VSPACE) {
        strcpy(vs->data[index].elem.name, NULL);
        vs->data[index].elem.sex = '\0';
        strcpy(vs->data[index].elem.city, NULL);
        vs->data[index].next = vs->avail;
        vs->avail = index;
    }
}
void insert_first_CBL(VSpace *vs, PersonCusorBasedList *list, Person p) {
    Position temp;
    temp = alloc_space(vs);
    if(temp != -1){
        vs->data[temp].elem = p;
        vs->data[temp].next = *list;
        *list = temp;
    }
}
void insert_last_CBL(VSpace *vs, PersonCusorBasedList *list, Person p) {
    Position i, temp;
    temp=alloc_space(vs);
    if(temp!=-1){
        for(i=*list; i!=-1; i=vs->data[i].next){
        }
        vs->data[i].next=vs->avail;
        vs->data[temp].elem=p;
    }
}
void insert_at_CBL(VSpace *vs, PersonCusorBasedList *list, Person p, int index) {
void delete_first_CBL(VSpace *vs, PersonCusorBasedList *list) {
    Position tmp;
    if(list != -1) {
        temp = &list;
        list = vs->data[&list]->next;
        free_space(vs, tmp);
    }
}
void delete_last_CBL(VSpace *vs, PersonCusorBasedList *list) {
    Position i;
    if(list != i) {
        for(i = list; vs->data[i].next != 1; i &(vs->data[i].next)){}
        free_space(vs, i);
        i = -1;
    }
}
void delete_by_sex_CBL(VSpace *vs, PersonCusorBasedList *list, char sex) {
    Position ndx, i;
    if(list != -1) {
        i = list;
        while(vs->data[i].next!= -1) {
            if(vs->data[i].elem.sex == "F") {
                temp = i;
                i = vs->data[i].next;
                free_space(vs, ndx);
            } else
                i = &(vs->data[i].next);
        }
    }
} // all ocurrences
void display_CBL(VSpace vs, PersonCusorBasedList list) {
    int i;
    printf("{");
    for(i=list; i != -1; i = vs.data[i].next) {
       displayPersonInfo(vs.data[i].elem);
    }
    printf("}\n");
}
