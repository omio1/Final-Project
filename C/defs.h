#define NUMBER_OF_COLORS 2

char* colorChars = "RGX";

typedef enum Color {
  RED = 0, GREEN = 1
} Color;


typedef struct Vertex {
  int id;
  int* neighbors;
  int maxNeighbors;
  int currentNeighbors;
  int edgeColorList[NUMBER_OF_COLORS];
} Vertex;

typedef struct Edge {
  Vertex v1;
  Vertex v2;
  Color col;
} Edge;

typedef struct Graph {
  Edge* edges;
  int numEdges;
  Vertex* vertices;
  int numVertices;
} Graph;

typedef struct GraphPtrList {
  Graph ** graphs;
  int size;
} GraphPtrList;

typedef enum Boolean {
  TRUE = 1, FALSE = 0
} bool;
