#include <stdlib.h>
#include <stdio.h>
#include "push-relabel.h"

void push(int* C, int * F, int *excess, int u, int v, int cantNodos) {
  int send = MIN(excess[u], C[cantNodos * u + v] - F[cantNodos * u + v]);
  F[cantNodos * u + v] += send;
  F[cantNodos * v + u] -= send;
  excess[u] -= send;
  excess[v] += send;
}

void relabel(int* C, int* F, int *height, int u, int cantNodos) {
  int min_height = INFINITE;
  for (int v = 0; v < cantNodos; v++) {
    if (C[cantNodos * u + v] - F[cantNodos * u + v] > 0) {
      min_height = MIN(min_height, height[v]);
      height[u] = min_height + 1;
    }
  }
}

void discharge(int* C, int * F, int *excess, int *height, int *seen, int u, int cantNodos) {
  while (excess[u] > 0) {
    if (seen[u] < cantNodos) {
      int v = seen[u];
      if ((C[cantNodos * u + v] - F[cantNodos * u + v] > 0) && (height[u] > height[v])) {
        push(C, F, excess, u, v, cantNodos);
      } else {
        seen[u] += 1;
      }
    } else {
      relabel(C, F, height, u, cantNodos);
      seen[u] = 0;
    }
  }
}

void moveToFront(int i, int *A, int cantNodos) {
  int temp = A[i];
  for (int n = i; n > 0; n--) {
    A[n] = A[n-1];
  }
  A[0] = temp;
}

int pushRelabel(int* C, int * F, int source, int sink, int cantNodos) {
  int *excess, *height, *list, *seen, p;

  excess = (int *) calloc(cantNodos, sizeof(int));
  height = (int *) calloc(cantNodos, sizeof(int));
  seen = (int *) calloc(cantNodos, sizeof(int));

  list = (int *) calloc((cantNodos-2), sizeof(int));

  for (int i = 0, p = 0; i < cantNodos; i++){
    if((i != source) && (i != sink)) {
      list[p] = i;
      p++;
    }
  }

  height[source] = cantNodos;
  excess[source] = INFINITE;
  for (int i = 0; i < cantNodos; i++)
    push(C, F, excess, source, i, cantNodos);

  p = 0;
  while (p < cantNodos - 2) {
    int u = list[p];
    int old_height = height[u];
    discharge(C, F, excess, height, seen, u, cantNodos);
    if (height[u] > old_height) {
      moveToFront(p, list, cantNodos);
      p = 0;
    } else {
      p += 1;
    }
  }
  int maxflow = 0;
  for (int i = 0; i < cantNodos; i++)
    maxflow += F[cantNodos * source + i];

  free(list);

  free(seen);
  free(height);
  free(excess);

  return maxflow;
}

void printMatrix(int* M, int cantNodos) {
  for (int i = 0; i < cantNodos; i++) {
    for (int j = 0; j < cantNodos; j++)
      printf("%d\t",M[cantNodos * i + j]);
    printf("\n");
  }
}
