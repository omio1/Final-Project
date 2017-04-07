import java.util.ArrayList;
import java.util.Arrays;

public class Graph {
   public ArrayList<Vertex> vertices;
   public ArrayList<Edge> edges;
   
   public Graph(){
      vertices = new ArrayList<Vertex>();
      edges = new ArrayList<Edge>();
   }
   
   
   //returns the subgraph that consists of all vertices plus all edges with color col
   public Graph getSG(eColor col){
      Graph g = new Graph();
 
      for(int i = 0; i < vertices.size(); i++){
         g.vertices.add(new Vertex(i));
      }
      
      for(Edge e : edges){
         if(e.col == col){
            Vertex v1 = g.vertices.get(e.v1.id);
            Vertex v2 = g.vertices.get(e.v2.id);
            
            g.edges.add(new Edge(v1, v2, col));
            v1.addE(col);
            v2.addE(col);
            v1.addNeighbor(v2);
            v2.addNeighbor(v1);
            
         }
      }
      return g;
   }
   
   
   //creates the complete graph with n vertices, defaults to all edges being red
   public static Graph createKn(int n){
      Graph g = new Graph();
      for(int i = 0; i < n; i++){
         g.vertices.add(new Vertex(i));
      }
      for(int i = 0; i < n - 1; i++){
         Vertex v1 = g.vertices.get(i);
         for(int j = i + 1; j < n; j++){
            Vertex v2 = g.vertices.get(j);
            g.edges.add(new Edge(v1, v2));
            v1.addE(eColor.Red);
            v2.addE(eColor.Red);
            v1.addNeighbor(v2);
            v2.addNeighbor(v1);
         }
      }
      
      return g;
   }
   
   //same as createKn but initializes all edges to be of random colors
   public static Graph createRandKn(int n){
      Graph g = new Graph();
      for(int i = 0; i < n; i++){
         g.vertices.add(new Vertex(i));
      }
      for(int i = 0; i < n - 1; i++){
         Vertex v1 = g.vertices.get(i);
         for(int j = i + 1; j < n; j++){
            Vertex v2 = g.vertices.get(j);
            eColor c = tester.randomColor();
            g.edges.add(new Edge(v1, v2, c));
            v1.addE(c);
            v2.addE(c);
            v1.addNeighbor(v2);
            v2.addNeighbor(v1);
         }
      }
      
      return g;
   }
   
   
   //checks this graph to see wether it contains k3 as a subgraph, not efficient
   
   public boolean hasK3(){
      int n = vertices.size();
      
      for(int i = 0; i < n - 2; i++){
         Vertex v1 = vertices.get(i);
         for(int j = i + 1; j < n - 1; j++){
            Vertex v2 = vertices.get(j);
            for(int k = j + 1; k < n; k++){
               Vertex v3 = vertices.get(k);
               
               if(v1.neighborTo(v2) && v1.neighborTo(v3) && v2.neighborTo(v3)){
                  return true;
               }
            }
         }
      }
      return false;
   }
   
   
   //same as hasK3, but with K4
   public boolean hasK4(){
      int n = vertices.size();
      
      for(int i = 0; i < n - 3; i++){
         Vertex v1 = vertices.get(i);
         for(int j = i + 1; j < n - 2; j++){
            Vertex v2 = vertices.get(j);
            for(int k = j + 1; k < n - 1; k++){
               Vertex v3 = vertices.get(k);
               for(int l = k + 1; l < n; l++){
                  Vertex v4 = vertices.get(l);
                  if(v1.neighborTo(v2) && v1.neighborTo(v3) && v1.neighborTo(v4) && v2.neighborTo(v3) && v2.neighborTo(v4) && v3.neighborTo(v4)){
                     return true;
                  }
               }
            }
         }
      }
      return false;
   }
   
   public int getNumEdges(){
      return edges.size();
   }
   
   public int getNumVertices(){
      return vertices.size();
   }
   
   //returns the characteristic list of this graph, useful for checking color isomorphisms
   public int[] getCharList(){
      int[] res = new int[vertices.size()];
      for(Vertex v : vertices){
         res[v.id] = v.redEdges;
      }
      //sorts the result for easier comparison
      Arrays.sort(res);
      return res;
   }
   
   
   //generates a copy to later modify
   public Graph copy(){
      Graph g = new Graph();
      
      for(int i = 0; i < vertices.size(); i++){
         g.vertices.add(new Vertex(i));
      }
      for(Edge e : edges){
            Vertex v1 = g.vertices.get(e.v1.id);
            Vertex v2 = g.vertices.get(e.v2.id);
            
            g.edges.add(new Edge(v1, v2, e.col));
            v1.addE(e.col);
            v2.addE(e.col);
            v1.addNeighbor(v2);
            v2.addNeighbor(v1);
            
      }
      return g;
   }
   
   public boolean isoTo(Graph g){
      return Arrays.equals(this.getCharList(), g.getCharList());
   }
   
   //generates a list of all possible complete graphs with g as a base
   public static ArrayList<Graph> getNextSize(Graph g){
      ArrayList<Graph> newGs = new ArrayList<Graph>();
      eColor[] vals = eColor.values();
      
      int N = g.vertices.size();
      
      for(int i = 0; i < Math.pow(2, N); i++){
         int j = i;
         Graph newG = g.copy();
         Vertex nV = new Vertex(N);
         newG.vertices.add(nV);
         for(int k = 0; k < N; k++){
            Vertex oldV = newG.vertices.get(k);
            newG.edges.add(new Edge(nV, oldV, vals[j%2]));
            nV.addE(vals[j%2]);
            oldV.addE(vals[j%2]);
            nV.addNeighbor(oldV);
            oldV.addNeighbor(nV);
            j = j >> 1;
         }
         newGs.add(newG);
      }
      
      return newGs;
   }
   
   //removes graphs that are color isomorphic to each other
   // and removes graphs that aren't valid
   public static ArrayList<Graph> clean(ArrayList<Graph> gs){
      int i = 0;
      while(i < gs.size()){
         Graph g = gs.get(i);
         for(int j = gs.size() - 1; j > i; j--){
            if(g.isoTo(gs.get(j))){
               gs.remove(j);
            }
         }
         i ++;
      }
      
      ArrayList<Graph> newGs = new ArrayList<Graph>();
      for(Graph g : gs){
         if(!g.getSG(eColor.Red).hasK3() && !g.getSG(eColor.Green).hasK3()){
            newGs.add(g);
         }
      }
      return newGs;
   }
}
