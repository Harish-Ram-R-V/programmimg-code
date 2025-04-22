//Code for Autonomous Crane Fabrication Unit
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define n 6
// Function for Part Delivery System (Queue): Parts arrive via trucks and queue for fabrication.

// Implementation of stack and queue

// Stack and Queue Structs
typedef struct {
    char* items[n];
    int top;
} Stack;

typedef struct {
    char* items[n];
    int front, rear;
} Queue;

// Queue functions
void enqueue(Queue* q, char* x) 
{
    if (q->rear == n - 1) 
    {
        printf("QUEUE OVERFLOW\n");
    } 
    else if (q->front == -1 && q->rear == -1) 
    {
        q->front = q->rear = 0;
        q->items[q->rear] = x;
    }
    else 
    {
        q->rear++;
        q->items[q->rear] = x;
    }
}

char* dequeue(Queue* q) 
{
    if (q->front == -1 && q->rear == -1) 
    {
        printf("QUEUE UNDERFLOW\n");
        return NULL;
    }
    else
    {
        char* temp = q->items[q->front];
        if (q->front == q->rear) 
        {
            q->front = q->rear = -1;
        } 
        else 
        {
            q->front++;
        }
        return temp;
    }
}

// Stack functions
void push(Stack* s, char* x) 
{
    if (s->top == n - 1)
    {
        printf("STACK OVERFLOW\n");
    } 
    else 
    {
        s->top++;
        s->items[s->top] = x;
    }
}

char* pop(Stack* s) 
{
    if (s->top == -1) 
    {
        printf("STACK UNDERFLOW\n");
        return NULL;
    } 
    else 
    {
        char* temp = s->items[s->top];
        s->top--;
        return temp;
    }
}

// Function to Enqueue all 6 parts -> Dequeue and push onto a stack -> Pop to show assembly order
//Function to Crane Task Manager (Stack): Robots stack parts in LIFO order for load balancing
void SimulateAssembly() 
{
    Queue q;
    q.front = -1;
    q.rear = -1;
    
    Stack s;
    s.top = -1;
    
    char* parts[] = {"Boom", "Counterweight", "Cable", "Hook", "Base", "Pulley"};

    // Enqueue parts
    for (int i = 0; i < 6; i++) 
    {
        enqueue(&q, parts[i]);
    }

    // Dequeue from queue, push to stack
    for (int i = 0; i < 6; i++) 
    {
        char* part = dequeue(&q);
        if (part != NULL) {
            push(&s, part);
        }
    }

    // Pop from stack to simulate LIFO assembly
    printf("Assembly Order (LIFO):\n");
    for (int i = 0; i < 6; i++) 
    {
        char* assembled = pop(&s);
        if (assembled != NULL) 
        {
            printf("- %s\n", assembled);
        }
    }
}

//Using a LIFO (stack) ensures that the last-delivered part is installed first,
//enabling it to assist in lifting heavier components.
//This design prioritizes immediate utility and efficient sequential construction.


//Function to Assembly Storage Unit (Array): Finished cranes store in an array-based yard (size: 6 slots)
// If full, the oldest is deployed.

//Function to Insert the first 6 cranes -> Handle overflow for "Crane7" and "Crane8"
void StoreCranes() 
{
    char* storage[6];
    int count = 0;
    char* cranes[] = {"Crane1", "Crane2", "Crane3", "Crane4", "Crane5", "Crane6", "Crane7", "Crane8"};

    printf("\nAssembly Storage:\n");
    for (int i = 0; i < 8; i++) 
    {
        if (count < 6) 
        {
            storage[count++] = cranes[i];
        } else 
        {
            // Remove oldest
            for (int j = 1; j < 6; j++) 
            {
                storage[j - 1] = storage[j];
            }
            storage[5] = cranes[i];
            printf("Deployed oldest crane to make space.\n");
        }

        printf("Current Storage: ");
        for (int k = 0; k < count; k++) 
        {
            printf("%s ", storage[k]);
        }
        printf("\n");
    }
}

//When site demand spikes, older cranes are automatically deployed to handle urgent lifting or infrastructure projects,
//ensuring that new, calibrated cranes are stored and ready for complex builds

//Function to Repair and Upgrade Tracker (Linked Lists):
//  ->Faulty cranes go to a singly linked list.
//  ->Repaired cranes move to a doubly linked list for dual checks.
//  ->High-priority cranes cycle in a circular linked list for urgent upgrades.

typedef struct Node 
{
    char* data;
    struct Node* next;
    struct Node* prev;
} Node; // For doubly linked list

Node* insertSingly(Node* head, char* data) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = head;
    return newNode;
}

Node* deleteSingly(Node* head, char* target) 
{
    Node *curr = head, *prev = NULL;
    while (curr != NULL && strcmp(curr->data, target) != 0) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) 
        return head;
    if (prev == NULL) 
        head = curr->next;
    else
    {
        prev->next = curr->next;
    }
    free(curr);
    return head;
}

Node* insertDoubly(Node* head, char* data) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = head;
    newNode->prev = NULL;
    if (head) 
        head->prev = newNode;
    return newNode;
}

void traverseForward(Node* head) 
{
    printf("\nForward Traversal (Repaired): ");
    while (head) {
        printf("%s ", head->data);
        if (head->next == NULL) break;
        head = head->next;
    }
    printf("\n");
}

void traverseBackward(Node* tail) 
{
    printf("Backward Traversal (Repaired): ");
    while (tail) {
        printf("%s ", tail->data);
        tail = tail->prev;
    }
    printf("\n");
}

void trackFaultyCranes() 
{
    Node* faulty = NULL;
    faulty = insertSingly(faulty, "Crane5");
    faulty = insertSingly(faulty, "Crane2");

    // Move Crane2 to repaired list
    faulty = deleteSingly(faulty, "Crane2");

    Node* repaired = NULL;
    repaired = insertDoubly(repaired, "Crane2");

    traverseForward(repaired);
    traverseBackward(repaired); // Only one node here
}

//Crane2 experienced a frayed cable issue, a safety hazard
//Repair bots replaced it with a smart tension-controlled fiber cable that automatically adjusts for load and weather conditions.

typedef struct CNode 
{
    char* data;
    struct CNode* next;
} CNode;    // for singly linked list

CNode* insertCirular;
char* insertCircular(CNode* tail, char* data) 
{
    CNode* newNode = (CNode*)malloc(sizeof(CNode));
    newNode->data = data;
    if (!tail) {
        newNode->next = newNode;
        return newNode;
    }
    newNode->next = tail->next;
    tail->next = newNode;
    return newNode;
}

void traverseCircular(CNode* tail, int times) 
{
    if (!tail) return;
    CNode* current = tail->next;
    printf("\nCircular Traversal:\n");
    for (int i = 0; i < times; i++) {
        printf("Upgrade Scheduled: %s\n", current->data);
        current = current->next;
    }
}

void upgradePriorityCranes() {
    CNode* upgradeList = NULL;
    upgradeList = insertCircular(upgradeList, "Crane1");
    upgradeList = insertCircular(upgradeList, "Crane4");
    traverseCircular(upgradeList, 4); // 2 traversals
}

//Crane1 is upgraded with an extended telescopic boom, increasing its max reach
//Crane4 receives a magnetic grip enhancement, enabling safer handling of steel beams and metal sheets

void main()
{
    SimulateAssembly();
    StoreCranes();
    trackFaultyCranes();
    upgradePriorityCranes();        
}
