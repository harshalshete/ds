/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
void insert(struct ListNode *t, struct ListNode *head) {
    struct ListNode *tmp = head;
    struct ListNode *p = malloc(sizeof(struct ListNode));
    
    // printf("elem %d\n", t->val);
    
    if (!p) {
        printf("error: unable to allocate memory\n");
        exit(0);
    }
    // allocate and initialize the new node.
    memset(p, 0, sizeof(struct ListNode));
    p->val = t->val;    
    
    if (!tmp) {
        head = p;
    } else {
        while (tmp->next) {
            tmp = tmp->next;
        }
        tmp->next = p;
    }
}

/*
 * Given n sorted lists, this function merges them in to a single
 * sorted list, and return the new lists head pointer.
 */
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize){
    struct ListNode *list[listsSize+1];
    int i = 0, ti = 0, index = 0;
    struct ListNode *t = NULL, *t1 = NULL;
    struct ListNode *nh = NULL, *ptr = NULL, *tmp = NULL;
    int found = 0;    
    
    printf("Number of lists = %d\n", listsSize);
    
    // TODO: Check if all the input strings are sorted or not?
    // If the input lists are not sorted then this algorithm will fail.
    // CheckIfSorted(struct ListNode** lists, int listsSize);
    
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
        
        
        
        ptr = malloc(sizeof(struct ListNode));    
        if (!ptr) {
            printf("error: unable to allocate memory\n");
            exit(0);
        }
        // allocate and initialize the new node.
        memset(ptr, 0, sizeof(struct ListNode));
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
