#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

typedef struct tnode {
    int val;
    struct tnode *l;
    struct tnode *r;
} tnode_t;


void inorder(tnode_t *n) {
    if (n == NULL)
        return;

    inorder(n->l);
    printf(" %d ", n->val);
    inorder(n->r);
}

void inorder_k(tnode_t* root, int k, int *a) {
    if (root == NULL)
        return;

    inorder_k(root->l, k, a);
    a[0] = a[0] + 1;
    if (a[0] == k) {
        a[1] = root->val;
    }

    inorder_k(root->r, k, a);
}

int ksmallest(tnode_t *n, int k) {
    int a[2];

    memset(a, 0, sizeof(a));    
    inorder_k(n, k, a);

    printf("Kth(%d) element is %d\n", k, a[1]);
    return (a[1]);
}

tnode_t *search_bst(int val, tnode_t **root) {
    tnode_t *node = *root;

    while (node) {
        if (node->val == val)
            break;
        else if (node->val > val)
            node = node->l;
        else if (node->val < val)
            node = node->r;
    }
    return node;
}

tnode_t *alloc_node(int val) {
    tnode_t *n = malloc(sizeof(tnode_t));
    if (n) {
        memset(n, 0, sizeof(tnode_t));
        n->val = val;
    }
    return n;
}

void insert_bst(int val, tnode_t **root) {
    tnode_t *tmp = NULL, *n = NULL;
    tnode_t *parent = NULL;
    int dir;

    tmp = search_bst(val, root);
    if (tmp) {
        printf("%s():%d: Element already exists, skipping insertion.\n", __func__, __LINE__);
        return ;
    }

    n = alloc_node(val);
    if (n == NULL) {
        printf("unable to allocate memory, skipping insertion.\n");
        return ;
    }

    tmp = *root;
    if (tmp == NULL) {
        printf("Element %d added as root.\n", val);
        *root = n;
        return ;
    }
#define LEFT    1
#define RIGHT   2
    while (tmp) {
        parent = tmp;
        if (tmp->val > val) {
            tmp = tmp->l;
            dir = LEFT;            
        } else if (tmp->val < val) {
            tmp = tmp->r;
            dir = RIGHT;            
        } else {
            free(n);
            printf("Element already exists, skipping insertion.\n");
            return ;
        }
    }

    if (dir == LEFT) {
        parent->l = n;
        printf("Element %d added to left of %d.\n", val, parent->val);
    } else if (dir == RIGHT) {
        parent->r = n;
        printf("Element %d added to right of %d.\n", val, parent->val);
    }
}

struct node {
    void *v;
    int cascade;
    struct node *next;
};
struct node *head;

void enqueue(tnode_t *n) {
    struct node *nw = NULL;

#if 0
    if (!n) {
        return;
    }
#endif

    nw = malloc(sizeof(struct node));
    if(!nw) {
        printf("failed to allocate memory\n");        
        return;
    }
    memset(nw, 0, sizeof(*nw));
    nw->v = n;

    if (head == NULL) {
        head = nw;
    } else {
        struct node *t = head;
        while (t->next) {
             t= t->next;
        }
        t->next = nw;
    }
}

tnode_t * dequeue() {
    struct node *n = head;
    tnode_t *t = NULL;

    if (head) {
        n = head;
        t = n->v;
        head = head->next;
        free(n);
    }
    return (t);
}

/* Function which displays tree contents levelwise. */
void level_display(tnode_t **root) {
    tnode_t *tmp = NULL;

    tmp = *root;
    enqueue(tmp);
    printf("\nLevel wise Tree: ");
    while (tmp = dequeue()) {
        printf("%d\t", tmp->val);
        if (tmp->l)
            enqueue(tmp->l);
        if (tmp->r)
            enqueue(tmp->r);
    }
    printf("\n");
} 

void delete(int val, tnode_t **root) {
    tnode_t *temp, *parent = NULL;
    temp = *root;
    int found = 0;

    while (temp) {
        if (temp->val == val) {
            printf("Found\n");
            found = 1;
            break;
        } else if (temp->val > val) {
            parent = temp;
            temp = temp->l;
        } else if (temp->val < val) {
            parent = temp;
            temp = temp->r;
        }
    }

    if (found == 0) {
        printf("Item not Found\n");
        return ;
    }

    if (parent == NULL) {
        printf("Root node can not be deleted\n");
        return ;
    }
    
    if (temp && (temp->l == NULL) && (temp->r == NULL)) {
        // leaf node.
        if (parent->l == temp) {
            parent->l = NULL;
        } else if (parent->r == temp) {
            parent->r = NULL;
        }
    } else if ((temp && (temp->l == NULL) && temp->r) ||
    (temp && (temp->r == NULL) && temp->l)) {
        // Node to be deleted has only one child.
        if (parent->r == temp && temp->r) {
            parent->r = temp->r;
            free(temp);
        } else if (parent->r == temp && temp->l) {
            parent->r = temp->l;
            free(temp);
        } else if (parent->l == temp && temp->r) {
            parent->l = temp->r;
            free(temp);
        } else if (parent->l == temp && temp->l) {
            parent->l = temp->l;
            free(temp);
        }
    } else if (temp && temp->l && temp->r) {
        // Node to be deleted has two children.
        printf("Node can not be deleted\n");
        if (parent->l == temp) {
            // temps rights leftmost should be copied to temp and delete that leaf node.
        } else if (parent->r == temp){
            // temps leftmost should be copied to temp and delete that leaf node.
        }

    }
}

int isbst(tnode_t *root, int min, int max) {
    tnode_t *node = root;

    if (node == NULL) {
        return 1;
    }

    if (node->val < min || node->val > max)
        return 0;

    return isbst(node->l, min, node->val) &&
        isbst(node->r, node->val, max);
}

/* 
    We can maintain a counter and keep the total count,
    or we can call this function which calculated in O(n)
*/
void total_nodes(tnode_t *root, int *a) {
    if (!root)
        return;
    total_nodes(root->l, a);
    *a = *a + 1;
    total_nodes(root->r, a);
}

void leftsideview(tnode_t **root) {
    tnode_t *tmp = NULL;
    int cnt = 0;

    tmp = *root;
    enqueue(tmp);
    tmp = NULL;
    enqueue(tmp);
    printf("\nLeft side view Tree: ");

    while (tmp = dequeue()) {
        printf("%d\t", tmp->val);
        do {
            if (tmp->l) {
                // printf("%d\t", tmp->l->val);
                enqueue(tmp->l);
            }
            if (tmp->r) {
                // printf("%d\t", tmp->r->val);
                enqueue(tmp->r);
            }                
        } while (tmp = dequeue());
        cnt++;
        tmp = NULL;
        enqueue(tmp);
        // printf("\n");
    }
    printf("\n");
}


void rightsideview(tnode_t **root) {
    tnode_t *tmp = NULL;
    tnode_t *print = NULL;
    int cnt = 0;

    tmp = *root;
    enqueue(tmp);
    tmp = NULL;
    enqueue(tmp);
    printf("\nRight side view Tree: ");

    while (tmp = dequeue()) {
        do {
            if (tmp->l) {
                // printf("%d\t", tmp->l->val);
                enqueue(tmp->l);
            }
            if (tmp->r) {
                // printf("%d\t", tmp->r->val);
                enqueue(tmp->r);
            }
            print = tmp;
        } while (tmp = dequeue());
        cnt++;
        enqueue(tmp);
        printf("%d\t", print->val);
    }
    printf("\n");
}

int main() {
    tnode_t *root = NULL;
    int val[] = {80, 40, 120, 60, 90, 120, 130, 5, 12, 55, 58, 65};
    int i = 0;
    int n = (sizeof(val) / sizeof(int));

    for (i=0; i < n; i++) {
        insert_bst(val[i], &root);
    }
    leftsideview(&root);
    rightsideview(&root);
    printf("\n");
    if (search_bst(40, &root)) {
        printf("40 found\n");
    }

    if (isbst(root, INT_MIN, INT_MAX)) {
        printf("\n This Binary tree is indeed a binary search tree.\n");
    } else {
        printf("\n error: Tree is not a BST\n");
    }
    
    i = 0;
    total_nodes(root, &i);
    printf("\nNumber of nodes in tree: %d\n", i);

    level_display(&root);
    printf("\nInorder : ");
    inorder(root);
    printf("\n");

#if 0
    delete(80, &root);
    printf("\n");
    level_display(&root);

    delete(60, &root);
    printf("\n");
    level_display(&root);
#endif
    for (i=0; i < n; i++) {
        delete(val[i], &root);
    }
    printf("\nInorder : ");
    inorder(root);
    printf("\n");
    return 0;
}
