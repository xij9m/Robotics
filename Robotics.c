#include <stdio.h>
#include <stdlib.h>

int map[5][5] = { {4,3,2,3,4},
                    {3,2,1,2,3},
                    {2,1,0,1,2},
                    {3,2,1,2,3},
                    {4,3,2,3,4} };

int x = 0;
int y = 0;
int curr = map[x][y];

// Data structure to represent a stack
struct stack
{
    int maxsize;    // define max capacity of the stack
    int top;
    int* items;
};

// Utility function to initialize the stack
struct stack* newStack(int capacity)
{
    struct stack* pt = (struct stack*)malloc(sizeof(struct stack));

    pt->maxsize = capacity;
    pt->top = -1;
    pt->items = (int*)malloc(sizeof(int) * capacity);

    return pt;
}

// Utility function to return the size of the stack
int size(struct stack* pt) {
    return pt->top + 1;
}

// Utility function to check if the stack is empty or not
int isEmpty(struct stack* pt) {
    return pt->top == -1;                   // or return size(pt) == 0;
}

// Utility function to check if the stack is full or not
int isFull(struct stack* pt) {
    return pt->top == pt->maxsize - 1;      // or return size(pt) == pt->maxsize;
}

// Utility function to add an element `x` to the stack
void push(struct stack* pt, int x)
{
    // check if the stack is already full. Then inserting an element would
    // lead to stack overflow
    if (isFull(pt))
    {
        printf("Overflow\nProgram Terminated\n");
        exit(EXIT_FAILURE);
    }

    printf("Inserting %d\n", x);

    // add an element and increment the top's index
    pt->items[++pt->top] = x;
}

// Utility function to return the top element of the stack
int peek(struct stack* pt)
{
    // check for an empty stack
    if (!isEmpty(pt)) {
        return pt->items[pt->top];
    }
    else {
        exit(EXIT_FAILURE);
    }
}

// Utility function to pop a top element from the stack
int pop(struct stack* pt)
{
    // check for stack underflow
    if (isEmpty(pt))
    {
        printf("Underflow\nProgram Terminated\n");
        exit(EXIT_FAILURE);
    }

    printf("Removing %d\n", peek(pt));

    // decrement stack size by 1 and (optionally) return the popped element
    return pt->items[pt->top--];
}

void updateDist(struct stack* pt)
{
    if (!isEmpty(pt))
    {
        push(pt, curr);
    }
    while (!isEmpty(pt))
    {
        int check = pop(pt);
        //if we are in the top left corner
        if (x == 0 && y == 0)
        {
            if (check == 1 + map[x + 1][y] && check == 1 + map[x][y + 1])
                return;
            else
            {
                curr = 1 + minNeighbor();
                push(pt, map[x][y + 1]);
                push(pt, map[x + 1][y]);
            }
        }
        //if we are in the top right corner
        else if (x == 0 && y == 4)
        {
            if (check == 1 + map[x + 1][y] && check == 1 + map[x][y - 1])
                return;
            else
            {
                curr = 1 + minNeighbor();
                push(pt, map[x][y - 1]);
                push(pt, map[x + 1][y]);
            }
        }
        //if we are in the bottom left corner
        else if (x == 4 && y == 0)
        {
            if (check == 1 + map[x - 1][y] && check == 1 + map[x][y + 1])
                return;
            else
            {
                curr = 1 + minNeighbor();
                push(pt, map[x][y + 1]);
                push(pt, map[x - 1][y]);
            }
        }
        //if we are in the bottom right corner
        else if (x == 4 && y == 4)
        {
            if (check == 1 + map[x - 1][y] && check == 1 + map[x][y - 1])
                return;
            else
            {
                curr = 1 + minNeighbor();
                push(pt, map[x][y - 1]);
                push(pt, map[x - 1][y]);
            }
        }
        //if we are in the top row and we are not in a corner
        else if (x == 0 && y != 0 && y != 4)
        {
            if (check == 1 + map[x - 1][y] && check == 1 + map[x + 1][y] && check == 1 + map[x][y - 1])
                return;
            else
            {
                curr = 1 + minNeighbor();
                push(pt, map[x][y - 1]);
                push(pt, map[x + 1][y]);
                push(pt, map[x - 1][y]);
            }
        }
        //if we are in the bottom row and not in a corner
        else if (x == 4 && y != 0 && y != 4)
        {
            if (check == 1 + map[x][y - 1] && check == 1 + map[x][y + 1] && check == 1 + map[x - 1][y])
                return;
            else
            {
                curr = 1 + minNeighbor();
                push(pt, map[x][y + 1]);
                push(pt, map[x][y - 1]);
                push(pt, map[x - 1][y]);
            }
        }
        //if we are in the first coloumn and not a corner
        else if (y == 0 && x != 0 && x != 4)
        {
            if (check == 1 + map[x - 1][y] && check == 1 + map[x + 1][y] && check == 1 + map[x][y + 1])
                return;
            else
            {
                curr = 1 + minNeighbor();
                push(pt, map[x][y + 1]);
                push(pt, map[x + 1][y]);
                push(pt, map[x - 1][y]);
            }
        }
        //if we are in the last column and not a corner
        else if (y == 4 && x != 0 && x != 4)
        {
            if (check == 1 + map[x - 1][y] && check == 1 + map[x + 1][y] && check == 1 + map[x][y - 1])
                return;
            else
            {
                curr = 1 + minNeighbor();
                push(pt, map[x][y - 1]);
                push(pt, map[x + 1][y]);
                push(pt, map[x - 1][y]);
            }
        }
        //not on a boundary
        else
        {
            if (check == 1 + map[x - 1][y] && check == 1 + map[x + 1][y] && check == 1 + map[x][y - 1] && check == 1 + map[x][y + 1])
                return;
            else
            {
                curr = 1 + minNeighbor();
                push(pt, map[x][y + 1]);
                push(pt, map[x][y - 1]);
                push(pt, map[x + 1][y]);
                push(pt, map[x - 1][y]);
            }
        }
    }
}

int minNeighbor()
{
    int size = 0;
    int neighborVals[4];
    int min = neighborVals[0];
    //north east west south
    if (byte[0] == 0) 
    {
        push(pt, map[x - 1][y]);
        size++;
    }
        
    if (byte[1] == 0)
    {
        push(pt, map[x][y + 1]);
        size++;
    }
    if (byte[2] == 0)
    {
        push(pt, map[x][y - 1]);
        size++;
    }
       
    if (byte[3] == 0)
    {
        push(pt, map[x + 1][y]);
        size++;
    }
        
    for (int i = 1; i < size; i++)
    {
        neighborVals[1] = pop(pt);
        if (neighborVals[i] < min)
            min = neighborVals[i];
    }
    return min;
    
}

int main()
{

}

