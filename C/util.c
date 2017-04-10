#include <stdio.h>    //printf and other io
#include <stdlib.h>   //malloc and stuff
#include <string.h>   //sprintf
#include <math.h>     //various mathy things
#include <time.h>     //to initialize rand
#include "defs.h"     //our custom header file


/*  Accepts a color, and returns a string literal with the corresponding
 * color as text
 */
char* colorToString(Color col){
  switch(col){
    case RED:
      return("red");
      break;
    case GREEN:
      return("green");
      break;
  }
}

/*  Accepts a buffer and an edge pointer
 * Sets the buffer to a human readable representation of the edgeToString
 *
 * Consider rewriting with malloc to return just the string pointer
 */
void edgeToString(char* s, Edge * e){
  sprintf(s, "(%d, %d), %s", e->v1->id, e->v2->id, colorToString(e->col));
}

/*  Initializes a vertex pointer
 *  vin is the vertex pointer
 *  id is the desired new id
 *  n is the number of neighbors expected for this vertex to have
 */
void newVertex(Vertex* vin, int id, int n){
  vin->id = id;
  vin->neighbors = (int*)malloc(n*sizeof(int));
  vin->maxNeighbors = n;
  vin->currentNeighbors = 0;
  int i = 0;
  for(i = 0; i < NUMBER_OF_COLORS; i++){
    vin->edgeColorList[i] = 0;
  }
}

/*  Like newVertex but for an edge
 *  Expects pointers to the new endpoints and the edge's color
 *  Also updates neighbor and color information for those vertices
 */
void newEdge(Edge * e, Vertex * v1, Vertex * v2, Color col){
  e->v1 = v1;
  e->v2 = v2;
  e->col = col;
  v1->neighbors = (int*)realloc(v1->neighbors, (v1->currentNeighbors + 1)*sizeof(int));
  *(v1->neighbors + v1->currentNeighbors) = v2->id;
  v1->currentNeighbors++;
  v1->edgeColorList[col]++;
  v2->neighbors = (int*)realloc(v2->neighbors, (v2->currentNeighbors + 1)*sizeof(int));
  *(v2->neighbors + v2->currentNeighbors) = v1->id;
  v2->currentNeighbors++;
  v2->edgeColorList[col]++;
}

/*  Runs through the first vertex's neighbor list and looks for the second's id
 *  If it is found it returns true, otherwise false
 */
bool areNeighbors(Vertex * v1, Vertex * v2){
  int i = 0;
  for(i = 0; i < v1->currentNeighbors; i++){
    //printf("%d %d\n", *(v1->neighbors + i),v2->id);
    if(*(v1->neighbors + i) == v2->id){
      return TRUE;
    }
  }
  return FALSE;
}

/*  Stores in outGraph all the vertices of inGraph
 * plus all the edges of outGraph that are color col
 */
void getSubGraph(Graph * inGraph, Graph * outGraph, Color col){
  int i;
  int n = inGraph->numVertices;
  outGraph->vertices = (Vertex *) malloc(n*sizeof(Vertex));
  outGraph->numVertices = n;
  outGraph->edges = (Edge *) malloc((n*n-1)/2 * sizeof(Edge));
  outGraph->isNull = FALSE;
  for(i = 0; i < n; i++){
    newVertex(outGraph->vertices + i, i, n);
  }
  char buf[20];
  int k = 0;
  for(i = 0; i < inGraph->numEdges; i++){
    Edge * e = inGraph->edges + i;
    edgeToString(buf, e);
    //printf("Checking edge %s\n", buf);
    if(e->col == col){
      Vertex * v1 = (outGraph->vertices) + e->v1->id;
      Vertex * v2 = (outGraph->vertices) + e->v2->id;
      newEdge(outGraph->edges + k, (outGraph->vertices) + e->v1->id, (outGraph->vertices) + e->v2->id, col);
      k++;
    }

  }
  outGraph->numEdges = k;
}

/*  Runs through a graph and checks all combinations of 3 vertices
 * to see if any form a triangle. Probably more efficient ways to do it
 * involving connected components or something
 */
bool hasK3(Graph * g){
  int n = g->numVertices;
  int i, j, k;

  for(i = 0; i < n - 2; i++){
    Vertex* v1 = g->vertices + i;
    for(j = i + 1; j < n - 1; j++){
      Vertex * v2 = g->vertices + j;
      for(k = j + 1; k < n; k++){
        Vertex * v3 = g->vertices + k;
        if(areNeighbors(v1, v2) && areNeighbors(v2, v3) && areNeighbors(v1, v3)){
          return TRUE;
        }
      }
    }
  }
  return FALSE;
}

/*  Just returns a random color, useful mostly for testing
 */
Color getRandomColor(){
  return rand()%NUMBER_OF_COLORS;
}

/*  Populates old with copies of all the vertices in new,
 *  and with copies of all edges, all in new memory
 *  This allows us to modify the copy without changing the original.
 *  Consider rewriting to return a pointer to the new graph with malloc
 */
void copyGraph(Graph * old, Graph * new){
  new->vertices = (Vertex *)malloc(old->numVertices*sizeof(Vertex));
  new->numVertices = old->numVertices;
  new->edges = (Edge *)malloc(old->numEdges*sizeof(Edge));
  new->numEdges = old->numEdges;
  new->isNull = FALSE;
  int i, j;
  for(i = 0; i < old->numVertices; i++){
    newVertex(new->vertices + i, i, old->numVertices);
  }
  for(i = 0; i < old->numEdges; i++){
    Edge * e = old->edges + i;
    newEdge(new->edges + i, new->vertices + e->v1->id, new->vertices + e->v2->id, e->col);
  }
}

//Simple wrapper for newEdge to color the edge a random color
void newEdgeRandCol(Edge* e, Vertex * v1, Vertex * v2){
  newEdge(e, v1, v2, getRandomColor());
}

/*  Populates g with Kn, the complete graph with n vertices
 *
 *  Consider rewriting to return a pointer to Kn without having to pass in
 *  the pointer, using malloc
 */
void createKn(Graph* g, int n){
  g->vertices = (Vertex *) malloc(n*sizeof(Vertex));
  g->numVertices = n;
  g->edges = (Edge *) malloc((n*n-1)/2 * sizeof(Edge));
  g->numEdges = n*(n-1)/2;
  g->isNull = FALSE;
  int i;
  int j;
  for(i = 0; i < g->numVertices; i++){
    newVertex(g->vertices + i, i, n);
  }
  int k = 0;
  for(i = 0; i < g->numVertices-1; i++){
    for(j = i + 1; j < g->numVertices; j++){
      newEdge(g->edges + k, g->vertices + i, g->vertices + j, 0);
      k++;
    }
  }
}

/*  Prints a human readable representation of g
 *  It prints it's characteristic matrix, where X
 *  represents no edge between the vertices, and a
 *  letter represents its corresponding color.
 */
void printGraph(Graph * g){
  int n = g->numVertices;
  int edgeMatrix[n][n];
  int i, j;
  for(i = 0; i < n; i++){
    for(j = 0; j < n; j++){
      edgeMatrix[i][j] = NUMBER_OF_COLORS;
    }
  }
  for(i = 0; i < g->numEdges; i++){
    Edge * e = g->edges + i;
    edgeMatrix[e->v1->id][e->v2->id] = e->col;
    edgeMatrix[e->v2->id][e->v1->id] = e->col;
  }
  printf("   ");
  for(i = 0; i < n; i++){
    printf("%d  ", i);
  }
  printf("\n");
  for(i = 0; i < n; i++){
    printf(" %d ", i);
    for(j = 0; j < n; j++){
      printf("%c  ", colorChars[edgeMatrix[i][j]]);
    }
    printf("\n");
  }
}

/*  Gives g a new vertex, and does the work of expanding appropriate memory slots
 *  I'm sure there's room for improvement here, like maybe returning a pointer
 *  to the new vertex
 */
void addVertex(Graph * g){
  g -> vertices = (Vertex *)realloc(g->vertices, (g->numVertices+1)*sizeof(Vertex));
  g->numVertices++;
  newVertex(g->vertices + g->numVertices-1, g->numVertices-1, g->numVertices);
}

//used in implementation of qsort
int compareInts(const void * a, const void * b){
  return (*(int*)a - *(int*)b);
}

/*  Returns an array of ints, where each in represents the number of red
 *  edges incident to a vertex. The array is also sorted for easier comparison.
 *
 *  Returns pointer to array, so we need to remember to free the space when we're done
 */
int* getCharList(Graph * g){
  int i, j;
  int* colorList = (int*)malloc(g->numVertices*sizeof(int));
  for(i = 0; i < g->numVertices; i++){
    colorList[i] = 0;
  }
  for(i = 0; i < g->numVertices; i++){
      colorList[i] += (g->vertices + i)->edgeColorList[0];
  }
  qsort(colorList, g->numVertices, sizeof(int), compareInts);
  return colorList;
}


/*  returns TRUE if the characteristic list of the g and h are the same
 */
bool areColorIso(Graph * g, Graph * h){
  if(g != NULL && h!= NULL){
    int * a = getCharList(g);
    int * b = getCharList(h);
    bool ans = !memcmp(a, b, g->numVertices);
    free(a);
    free(b);
    return ans;
  }else{
    return FALSE;
  }
}


/*  Now we get to the good stuff! This function populates outlist
 *  with all the graphs you can generate by adding a vertex to g
 *  and then coloring every new edge every possible combination of color.
 *  There are 2^n such combinations, 2 because there are 2 colors, n because
 *  there are n edges.
 */
void getNextSize(Graph * g, GraphPtrList * outList){
  int n = g -> numVertices;
  int i, k;

  //2^n combinations of new edges to add
  //So the way I implemented this is specific to 2 colors
  //i in binary counts from 00000...000 to 1111111...111 where there are n bits
  //so each edges color is that bit
  for(i = 0; i < pow(2, n); i++){
    Graph * current = *(outList->graphs + i);

    copyGraph(g, current);
    addVertex(current);
    Vertex * newVertex = current->vertices + n;
    current->edges = (Edge*)realloc(current->edges, (current->numEdges + n)*sizeof(Edge));

    int j = i;
    for(k = 0; k < n; k++){
      Vertex * v = current->vertices + k;
      Edge * newEdgePtr = current->edges + current->numEdges + k;
      newEdge(newEdgePtr, newVertex, v, j&1);
      //divides j by 2, essentially moving j over 1 bit
      j = j>>1;
    }
    //maybe write addEdge function? To combine several lines
    current->numEdges += n;
  }
}


/*  Does all the necessary mallocing for a list of graph pointers
 *  Remember to free any pointer this creates
 */
GraphPtrList* newGraphPtrList(int n){
  GraphPtrList* gL = (GraphPtrList *)malloc(sizeof(GraphPtrList));
  gL->size = n;
  gL->graphs = (Graph **)malloc(n*sizeof(Graph*));
  int i;
  for(i = 0; i < n; i++){
    *(gL->graphs + i) = (Graph *)malloc(sizeof(Graph));
  }
  return gL;
}

//deallocates all memory allocated to a graph
void destroyGraph(Graph * g){
  int i;
  for(i = 0; i < g->numVertices; i++){
    free((g->vertices + i)->neighbors);
  }
  free(g->edges);
  free(g->vertices);
  free(g);
}

/*  The other fun part of this program, this function takes a list of graph pointers
 *  and returns a new list that contains only one graph from each isomorphism
 *  equivalence class
 *  Remember to free any pointer made from this
 */
GraphPtrList * clean(GraphPtrList * in){
  int i = 0;
  int j = 0;
  int k = 0;
  int length = in->size;
  int found = 0;
  //for every graph g in 'in'
  while(i < length){
    //if that graph is not NULL
    if(!((*(in->graphs + i))->isNull)){
      //then for every other graph after it h
      for(j = length-1; j > i; j--){
        //if g and h are color isomorphic
        if(areColorIso(*(in->graphs + i), *(in->graphs + j))){
          //set h to null
          (*(in->graphs + j))->isNull = TRUE;
        }
      }
      found++;
    }
    //check the next one
    i++;
  }
  //what we're gonna return


  GraphPtrList * out = newGraphPtrList(found);
  printf("%d\n", out->size);
  //for every graph g in 'in'
  for(i = 0; i < length; i++){
    //if g is not null
    if(!(*(in->graphs + i))->isNull){
      //then set the kth graph of out to be g
      //no need to copy, we're doing this in place
      *(out->graphs+k) = *(in->graphs+i);
      printf("copy loop %d\n", i );
      k++;
    //but if it is null
    }else{
      //free its memory
      destroyGraph(*(in->graphs + i));
    }
  }
  return out;
}

int main(){
  time_t t;
  time(&t);
  srand(t);

  Graph g;
  createKn(&g, 16);
  printGraph(&g);
  int i, j;
  int numNextSizeUp = (int) pow(NUMBER_OF_COLORS, g.numVertices) + .5;
  printf("%d\n", numNextSizeUp);
  GraphPtrList * nextSizeUp = newGraphPtrList(numNextSizeUp);

  getNextSize(&g, nextSizeUp);
  GraphPtrList* cleaned;
  printf("%d\n", nextSizeUp->size);
  cleaned = clean(nextSizeUp);
  printf("Cleaned size: %d\n", cleaned->size);

  return 0;
}
