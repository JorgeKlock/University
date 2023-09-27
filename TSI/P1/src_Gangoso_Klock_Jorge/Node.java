package src_Gangoso_Klock_Jorge;

/**
 * Node Class
 *
 * @author Marcelo Surriabre
 * @version 2.0, 2018-02-23
 * 
 * Version modificada durante 2021 para la práctica de TSI de boulderdash
 * Autor de la modificacion: Jorge Gangoso Klock 49398653N
 * version 2.0.1 2021-04-15
 */
public class Node {

    private int g; 
    private int f;
    private int h;
    private int row;
    private int col;
    private int orientacion; //0-Norte 1-Sur 2-Este 3-Oeste
    private boolean isBlock;
    private Node parent;

    //Funcion constructor
    public Node(int row, int col) {
        super();
        this.row = row;
        this.col = col;
    }
    //Funcion para calcular H mediante distancia manhattan
    public void calculateHeuristic(Node finalNode) {
        this.h = Math.abs(finalNode.getRow() - getRow()) + Math.abs(finalNode.getCol() - getCol());
    }
    //Getter y Setter de la orientacion
    public int getOrientacion(){return orientacion;}
    public void setOrientacion(int orientacion) {this.orientacion = orientacion;}
    //Funcion para generar los datos asociados a un nodo (normalmente usado tras su expansion)
    public void setNodeData(Node currentNode, int cost) {
    	//Añadir al coste g: 1, en caso de que el nodo expandido haya requerido un giro
        int giro = 0;
        if(currentNode.getOrientacion() != 0 && this.getRow()<currentNode.getRow())
        {
        	giro = 1;
        }
        else if(currentNode.getOrientacion() != 1 && this.getRow()>currentNode.getRow())
        {
        	giro = 1;
        }
        else if(currentNode.getOrientacion() != 2 && this.getCol()>currentNode.getCol())
        {
        	giro = 1;
        }
        else if(currentNode.getOrientacion() != 3 && this.getCol()<currentNode.getCol())
        {
        	giro = 1;
        }
        
        
    	int coste = cost + giro;
    	
    	int gCost = currentNode.getG() + coste;
    	//Establecer el nodo padre
        setParent(currentNode);
        setG(gCost);
        //Calcular F
        calculateFinalCost();
    }
    //Calcular el padre con mejor F en generar el mismo nodo por dos caminos
    public boolean checkBetterPath(Node currentNode, int cost) {
    	
    	int fCost = currentNode.getF() + cost;
        if (fCost < this.getF()) 
        {
            setNodeData(currentNode, cost);
            return true;
        }
        return false;
    }
    //Funcion calcular F
    private void calculateFinalCost() {
        int finalCost = getG() + getH();
        setF(finalCost);
    }
    //Funcion equals para comprobar la igualdad de dos nodo (usado durante la funcion .contains() de una lista)
    @Override
    public boolean equals(Object arg0) {
        Node other = (Node) arg0;
        if(other == null || !(other instanceof Node)) return false;
        return (this.getOrientacion() == other.getOrientacion() && this.getRow() == other.getRow() && this.getCol() == other.getCol());
    }
    //Funcion toString() para facilitar el debug del programa
    @Override
    public String toString() {
        return "Node [row=" + row + ", col=" + col + ", ori=" + orientacion +"]";
    }
    //Getter y Setter de H
    public int getH() {
        return h;
    }
    public void setH(int h) {
        this.h = h;
    }
    //Getter y Setter de G
    public int getG() {
        return g;
    }
    public void setG(int g) {
        this.g = g;
    }
    //Getter y Setter de F
    public int getF() {
        return f;
    }
    public void setF(int f) {
        this.f = f;
    }
    //Getter y Setter del nodo padre
    public Node getParent() {
        return parent;
    }
    public void setParent(Node parent) {
        this.parent = parent;
    }
    //Comprobar la propiedad de muro de un nodo
    public boolean isBlock() {
        return isBlock;
    }
    //Otorgar la propiedad de muro a un nodo
    public void setBlock(boolean isBlock) {
        this.isBlock = isBlock;
    }
    //Getter y setter de la posicion (fila=row, columna=col)
    public int getRow() {
        return row;
    }
    public void setRow(int row) {
        this.row = row;
    }
    public int getCol() {
        return col;
    }
    public void setCol(int col) {
        this.col = col;
    }
}
