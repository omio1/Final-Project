import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class tester {
   public static void main(String[] args){
      ArrayList<ArrayList<Graph>> set = new ArrayList<ArrayList<Graph>>();
      ArrayList<Graph> first = new ArrayList<Graph>();
      first.add(Graph.createKn(1));
      set.add(first);
      for(int i = 0; i < 13; i++){
         ArrayList<Graph> newS = new ArrayList<Graph>();
         System.out.println("Starting row " + i);
         long m = System.currentTimeMillis();
         for(Graph g : set.get(i)){
            
            newS.addAll(Graph.clean(Graph.getNextSize(g)));
            
         }
         System.out.println("Row done, took " + (System.currentTimeMillis() - m)/1000.0);
         Graph.clean(newS);
         set.add(newS);
      }
      for(ArrayList<Graph> l : set){
         System.out.println("Here are valid coloring(s) of K" + (set.indexOf(l) + 1) + ": ");
         /*
         for(Graph g : l){
            System.out.println(Arrays.toString(g.getCharL()));
         }*/
         System.out.println("There is (are) " + l.size() + " of them.");
         System.out.println("---------------------------------------------------");
      }
         /*for(Graph g : set.get(set.size() - 1)){
            System.out.println(Arrays.toString(g.getSG(eC.R).edges.toArray()));
            System.out.println(Arrays.toString(g.getSG(eC.G).edges.toArray()));
         }
         System.out.println("---------------------------------------------------");*/

   }
   
   
   private static final List<eColor> VALUES = Collections.unmodifiableList(Arrays.asList(eColor.values()));
   private static final int SIZE = VALUES.size();
   private static final Random RANDOM = new Random();
   public static eColor randomColor()  {
     return VALUES.get(RANDOM.nextInt(SIZE));
   }
}
