import java.util.ArrayList;

public class Vertex {
   static int total = 0;
   int id = 0;
   private ArrayList<Vertex> neighbors = new ArrayList<Vertex>();
   boolean selected = false;
   int redEdges = 0;
   int greenEdges = 0;
   
   public void addE(eColor c){
      if(c == eColor.Red) {
         redEdges++;
      }else{
         greenEdges++;
      }
   }
   
   public Vertex(){
      this.id = total;
      total++;
   }
   public Vertex(int i){
      this.id = i;
   }
   public void addNeighbor(Vertex v){
      neighbors.add(v);
   }
   public boolean neighborTo(Vertex v){
      return neighbors.contains(v);
   }
   public void clearNeighbors(){
      neighbors.clear();
   }
}
