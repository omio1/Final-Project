//Class for edges
public class Edge {
   Vertex v1;
   Vertex v2;
   eColor col; //the color of the edge
   
   //constructor w/ default color
   public Edge(Vertex a, Vertex b){
      this.v1 = a;
      this.v2 = b;
      col = eColor.Red;
   }
   
   public Edge(Vertex a, Vertex b, eColor c){
      this.v1 = a;
      this.v2 = b;
      this.col = c;
   }
   
   //Human readable text representation
   public String toString(){
      return "(" + (v1.id + 1) + ", " + (v2.id + 1) + ")";
   }
}
