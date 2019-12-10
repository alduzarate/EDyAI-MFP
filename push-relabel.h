#if !defined(__PUSH_RELABEL__)
#define __PUSH_RELABEL__

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define INFINITE 10000000

void push(int* C, int * F, int *excess, int u, int v, int cantNodos);

void relabel(int* C, int* F, int *height, int u, int cantNodos);

void discharge(int* C, int * F, int *excess, int *height, int *seen, int u, int cantNodos);

void moveToFront(int i, int *A, int cantNodos);

int pushRelabel(int* C, int * F, int source, int sink, int cantNodos);

void printMatrix(int* M, int cantNodos);

#endif  // __PUSH_RELABEL__