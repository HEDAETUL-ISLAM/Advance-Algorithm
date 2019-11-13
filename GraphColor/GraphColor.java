public class GraphColor{
    int color[];
    final int V = 10; //total node number
    boolean isSafe(int v, int graph[][], int color[], int c){
        for(int i = 0; i < V; i++){
            if(graph[v][i] == 1 && c ==color[i]){
                return false;
            }
        }
        return true;
    }

    boolean graphColoringUtil(int graph[][], int m, int color[], int v){
        if(v ==V) //all vertices are assigned a color
            return true;
        for(int c =1; c <= m; c++){// different colot for a vertex
            if(isSafe(v,graph,color,c)){
                color[v]=c;
                if(graphColoringUtil(graph, m, color, v+1)){
                    return true;
                }
                color[v]=0;
            }
        }
        return false;
    }

    boolean graphColoring(int graph[][], int m){
        color = new int[V];
        for(int i = 0; i < V; i++){//initialy all are zero adjacency
            color[i]=0;
        }
        if(!graphColoringUtil(graph, m, color, 0)){
            System.out.println("not found");
            return false;
        }
        printSolution(color);
        return true;
    }
    void printSolution(int color[]){
        System.out.println("colours are: ");
        for(int i = 0; i < V; i++){
            System.out.println(" "+color[i]+" ");
        }
        System.out.println();
    }
    public static void main(String arg[]){
        GraphColor graphColor = new GraphColor();
        int graph[][] = {
            {0,1,1,1,0,0,0,0,0,0},
            {1,0,0,0,1,0,0,0,1,0},
            {1,0,0,0,0,1,0,0,0,1},
            {1,0,0,0,0,0,1,1,0,0},
            {0,1,0,0,0,1,0,1,0,0},
            {0,0,1,0,1,0,1,0,0,0},
            {0,0,0,1,0,1,0,0,1,0},
            {0,0,0,1,1,0,0,0,0,1},
            {0,1,0,0,0,0,1,0,0,1},
            {0,0,1,0,0,0,0,1,1,0}
        };
        int m = 3;
        graphColor.graphColoring(graph,m);
    }
}