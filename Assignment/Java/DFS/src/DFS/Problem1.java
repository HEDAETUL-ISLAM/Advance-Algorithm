package DFS;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Collections;
import java.util.Scanner;
import java.util.Vector;

public class Problem1 {
    protected Vector<Node> graph = new Vector<>();
    protected Scanner scanner = new Scanner(System.in);
    protected String fileName;
    protected int expanded;

    public Problem1() {
        initializer();
        readFile();
    }

    public Node initialState() {
        graph.get(0).pathcost = 0;
        return graph.get(0);
    }

    public void initializer() {
        graph.add(new Node("Arad"));
        graph.add(new Node("Zerind"));
        graph.add(new Node("Oradea"));
        graph.add(new Node("Sibiu"));
        graph.add(new Node("Fagaras"));
        graph.add(new Node("Rimnicu Vilcea"));
        graph.add(new Node("Pitesti"));
        graph.add(new Node("Timisoara"));
        graph.add(new Node("Lugoj"));
        graph.add(new Node("Mehadia"));
        graph.add(new Node("Dobreta"));
        graph.add(new Node("Craiova"));
        graph.add(new Node("Bucharest"));
        graph.add(new Node("Giurgiu"));
        graph.add(new Node("Urziceni"));
        graph.add(new Node("Hirsova"));
        graph.add(new Node("Vaslui"));
        graph.add(new Node("Eforie"));
        graph.add(new Node("Iasi"));
        graph.add(new Node("Neamt"));
    }

    public void readFile() {
        String fileName = "graph.txt";
        File file = new File(fileName);
        String[] edge = new String[3];
        try {
            Scanner filereader = new Scanner(file);
            do {
                String s = filereader.nextLine();
                edge[0] = s.split(",")[0];
                edge[1] = s.split(",")[1];
                edge[2] = s.split(",")[2];
                addNeighbors(edge[0], edge[1], edge[2]);
            } while (filereader.hasNext());
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    private void addNeighbors(String s1, String s2, String cost) {
        for (int i = 0; i < graph.size(); i++) {
            if (graph.get(i).getValue().equals(s1)) {
                graph.get(i).adjNodes.add(new Edge(new Node(s2), Double.parseDouble(cost)));
            }
            else if (graph.get(i).getValue().equals(s2)) {
                graph.get(i).adjNodes.add(new Edge(new Node(s1), Double.parseDouble(cost)));
            }
        }
    }

    public Vector<Node> actions(Node n) {
        Vector<Node> v = new Vector<>();
        for (int i = 0; i < graph.size(); i++) {
            if (graph.get(i).getValue().equals(n.getValue())) {
                for (int j = 0; j < graph.get(i).adjNodes.size(); j++) {
                    v.add(graph.get(i).adjNodes.get(j).target);
                }
            }
        }
        return v;
    }

    public double getCost(Node current, Node next) {
        for (int i = 0; i < graph.size(); i++) {
            if (graph.get(i).getValue().equals(current.getValue())) {
                for (int j = 0; j < graph.get(i).adjNodes.size(); j++) {
                    if (graph.get(i).adjNodes.get(j).target.getValue().equals(next.getValue()))
                        return graph.get(i).adjNodes.get(j).cost;
                }
            }
        }
        return 0.0;
    }

    protected void addHeuristic(String node, String heuristic) {
        for (int i = 0; i < graph.size(); i++) {
            if (graph.get(i).getValue().equals(node)) {
                graph.get(i).heuristic = Double.parseDouble(heuristic);
            }
            for (int j = 0; j <graph.get(i).adjNodes.size() ; j++) {
                if (graph.get(i).adjNodes.get(j).target.getValue().equals(node)){
                    graph.get(i).adjNodes.get(j).target.heuristic = Double.parseDouble(heuristic);
                }
            }
        }
    }

    protected void printPath(Node target){
        Vector<Node> path = new Vector<>();
        for(Node node = target ; node !=null ; node = node.parent) {
            path.add(node);
            if (node.getValue().equals(initialState().getValue()))
                break;
        }
        System.out.println("The path from start to the goal");
        Collections.reverse(path);
        for (int i = 0; i < path.size(); i++) {
            System.out.print(path.get(i).getValue() + " -> ");
        }
        System.out.println();
    }
}