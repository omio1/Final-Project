

//function headers
Graph * createKn(int n);

GraphList * getNextSize(Graph * g);
int * getCharList(Graph * g);
Graph * getSubgraph(Color c);
Color getEdgeColor(Graph * g, int m, int n);
void printGraph(Graph * g);


typedef struct GraphList {
  int size;
  Graph * graphs;
}

typedef enum Color {
  NONE = 0, RED = 1, GREEN = 2
} Color;


typedef struct Graph {
  int n;
  Color * edges;
} Graph;
