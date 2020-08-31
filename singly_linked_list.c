#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct list {
    int val;
    struct list *next;
} list_t;

void insert(int val, list_t **head) {

    list_t *tmp = NULL;

    tmp = malloc(sizeof(struct list));
    if (!tmp) {
        printf("Unable to allocate memory\n");
        exit(0);
    }

    memset (tmp, 0, sizeof(struct list));
    tmp->val = val;

    if (*head) {
        tmp->next = *head;
        *head = tmp;
    } else {
        *head = tmp;
    }
}

void delete(int val, list_t **head) {
    list_t *tmp = NULL, *prev = NULL;

    prev = *head;

    while ((prev) && (prev->val == val)) {
        *head = prev->next;
        free(prev);
        prev = *head;
    }

    if (prev) {
        tmp = prev->next;
    }


    while (tmp) {

        if (tmp->val == val) {
            prev->next = tmp->next;
            free(tmp);
            tmp = prev->next;
            continue;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

void reverse_ll(list_t **head) {
    list_t  *p = NULL, *c = NULL, *t = NULL;

    c = *head;

    while (c) {
        t = c->next;
        c->next = p;
        p = c;
        c = t;
    }

    *head = p;
}

/*
 * Given n sorted lists, this function merges them in to a single
 * sorted list, and return the new lists head pointer.
 */
list_t* mergeKLists(list_t ** lists, int listsSize){
    list_t *list[listsSize+1];
    int i = 0, ti = 0, index = 0;
    list_t *t = NULL, *t1 = NULL;
    list_t *nh = NULL, *ptr = NULL, *tmp = NULL;
    int found = 0;    
    
    printf("Number of lists = %d\n", listsSize);
    
    // TODO: Check if all the input strings are sorted or not?
    // If the input lists are not sorted then this algorithm will fail.
    // CheckIfSorted(struct list_t** lists, int listsSize);
    
    for (i=0; i < listsSize; i++) {
        list[i] = lists[i];        
        printf("i = %d, list = %p ", i, list);        
    }
    
    
    while (1) {       
        
        ti = index = i =0;
        t = NULL; t1 = NULL;
        
        while ((!t) && (i < listsSize)) {
            t = list[i];
            ti = i;
            i++;
        }
        
        while ((!t1) && (i < listsSize)) {
            t1 = list[i];
            if (t1)
                break;
            i++;
        }
        
        index = ti;
        
        #if 0
        while (i < listsSize) {
            if (t && t1 && (t->val > t1->val)) {
                t = t1;
                index = i;
            }
            t1 = list[i+1];
            i++;
        }
        #endif
        while (t1) {
            t1 = list[i];
            if (t && t1 && (t->val > t1->val)) {
                t = t1;
                index = i;
            }            
            i++;
            if (i == listsSize)
                break;
        }
        
        
        
        ptr = malloc(sizeof(struct list));    
        if (!ptr) {
            printf("error: unable to allocate memory\n");
            exit(0);
        }
        // allocate and initialize the new node.
        memset(ptr, 0, sizeof(struct list));
        ptr->val = t->val;
        ptr->next = NULL;
        tmp = nh;
        
        if (!tmp) {
            nh = ptr;
        } else {
            while (tmp->next) {
                tmp = tmp->next;
            }
            tmp->next = ptr;
        }        
        list[index] = t->next;
        
        found = 0;
        for (i=0; i<listsSize; i++) {
            if (list[i]) {
                found = 1; break;
            }
        }
        
        if (found == 0)
            break;
    }
    
    printf("\nOutput: ");
    ptr = nh;
    while (ptr) {
        printf("%d ", ptr->val);
        ptr = ptr->next;
    }
    printf("\nEnd: ");
    
    return (nh);
}


void display(list_t **head) {
    list_t *tmp = *head;

    while (tmp) {
        printf("%d\t", tmp->val);
        tmp = tmp->next;
    }
    printf("\n");
}

int main() {
    list_t *head = NULL;

    printf("\n");
    printf("\n");
    insert(30, &head);
    insert(10, &head);
    insert(20, &head);
    insert(30, &head);
    insert(40, &head);
    insert(30, &head);
    insert(50, &head);
    insert(30, &head);

    printf("List:\t");
    display(&head);
    printf("\n");
    printf("\n");
    printf("List After deleting value 30\nList:\t");
    delete(30, &head);
    display(&head);
    printf("\n");
    printf("\n");

    printf("Reversed List is:\t");
    reverse_ll(&head);
    display(&head);
    printf("\n");
    printf("\n");
    return 0;
}
