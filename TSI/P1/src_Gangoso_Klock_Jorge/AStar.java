package src_Gangoso_Klock_Jorge;

import java.util.*;

/**
 * A Star Algorithm
 *
 * @author Marcelo Surriabre
 * @version 2.1, 2017-02-23
 * 
 * Version modificada durante 2021 para la práctica de TSI de boulderdash
 * Autor de la modificacion: Jorge Gangoso Klock 49398653N
 * version 2.1.1 2021-04-15
 */
public class AStar {
    private static int DEFAULT_HV_COST = 1; // Coste por defecto
    private static int DEFAULT_DIAGONAL_COST = 14; //Coste por defecto
    private int hvCost; // Coste Horizontal - Vertical 
    private int diagonalCost; //Coste diagonal (sin uso, movimiento diagonal no permitido)
    private Node[][] searchArea; //Matriz de nodos que representa el mapa de exploracion, para rellenar los obstaculos
    private PriorityQueue<Node> openList; //Lista de Abiertos
    private List<Node>closedList; //Lista de cerrados
    private Node initialNode; //Nodo Inicial
    private Node finalNode; //Nodo Final

    //Funcion constructor
    public AStar(int rows, int cols, Node initialNode, Node finalNode, int hvCost, int diagonalCost) {
    	//Inicializamos los nodos
        this.hvCost = hvCost;
        this.diagonalCost = diagonalCost;
        setInitialNode(initialNode);
        setFinalNode(finalNode);
        this.searchArea = new Node[rows][cols];
        //Definimos la cola de prioridad (abiertos) bajo la función de comparación F()
        this.openList = new PriorityQueue<Node>(new Comparator<Node>() {
            @Override
            public int compare(Node node0, Node node1) {
                return Integer.compare(node0.getF(), node1.getF());
            }
        });
        //Inicializamos los nodos del mapa
        setNodes();
        this.closedList = new ArrayList<Node>();
    }

    public AStar(int rows, int cols, Node initialNode, Node finalNode) {
        this(rows, cols, initialNode, finalNode, DEFAULT_HV_COST, DEFAULT_DIAGONAL_COST);
    }
    //Funcion para inicializar searchArea
    private void setNodes() {
        for (int i = 0; i < searchArea.length; i++) {
            for (int j = 0; j < searchArea[0].length; j++) {
                Node node = new Node(i, j);
                //En mi implementación searchArea solo se utiliza para definir los muros asi que esto no es necesario
                //node.calculateHeuristic(getFinalNode());
                this.searchArea[i][j] = node;
            }
        }
    }
    //Funcion que rellena searchArea de muros
    public void setBlocks(int[][] blocksArray) {
        for (int i = 0; i < blocksArray.length; i++) {
            int row = blocksArray[i][0];
            int col = blocksArray[i][1];
            setBlock(row, col);
        }
    }
    //Funcion A* (pathfinder)
    public List<Node> findPath() {
    	//Se añade el nodo inicial a abiertos
        openList.add(initialNode);
        //Mientras haya nodos por explorar en abiertos
        while (!isEmpty(openList)) {
        	//Elegimos el nodo más prometedor
            Node currentNode = openList.poll();
            //(Se va a cerrados)
            closedList.add(currentNode);
            //Comrpobamos si es nodo Objetivo, si lo es terminamos
            if (isFinalNode(currentNode))	return getPath(currentNode);
            //Si no es nodo objetivo expandimos los vecinos
            else 
            {
                addAdjacentNodes(currentNode);
            }
        }
        //Devolvemos un array vacio si no se ha podido encontrar nodo objetivo antes de tener abiertos vacío
        return new ArrayList<Node>();
    }
    //Funcion que develve la lista de nodos desde el objetivo hacia arriba accediendo a los nodos padre
    private List<Node> getPath(Node currentNode) {
        List<Node> path = new ArrayList<Node>();
        path.add(currentNode);
        Node parent;
        while ((parent = currentNode.getParent()) != null) {
            path.add(0, parent);
            currentNode = parent;
        }
        return path;
    }
    //Funcion que genera los nodos vecinos (el de encima, los dos colindantes izq y der, y el de debajo)
    private void addAdjacentNodes(Node currentNode) {
        addAdjacentUpperRow(currentNode);
        addAdjacentMiddleRow(currentNode);
        addAdjacentLowerRow(currentNode);
    }
    //Funcion que expande el nodo situado debajo del actual
    private void addAdjacentLowerRow(Node currentNode) {
        int row = currentNode.getRow();
        int col = currentNode.getCol();
        int lowerRow = row + 1;
        
        if (lowerRow < getSearchArea().length) 
        {
            if (col - 1 >= 0) {
                //checkNode(currentNode, col - 1, lowerRow, getDiagonalCost()); // Comment this line if diagonal movements are not allowed
            }
            if (col + 1 < getSearchArea()[0].length) {
                //checkNode(currentNode, col + 1, lowerRow, getDiagonalCost()); // Comment this line if diagonal movements are not allowed
            }
            checkNode(currentNode, col, lowerRow, getHvCost());
        }
    }
    //Funcion que expande los nodos colindantes a izquierda y derecha
    private void addAdjacentMiddleRow(Node currentNode) {
        int row = currentNode.getRow();
        int col = currentNode.getCol();
        int middleRow = row;
        if (col - 1 >= 0) 
        {
        	//expandimos el nodo a la izquierda
        	checkNode(currentNode, col - 1, middleRow, getHvCost());	
        }
        if (col + 1 < getSearchArea()[0].length) 
        {
        	//expandimos el nodo a la derecha
        	checkNode(currentNode, col + 1, middleRow, getHvCost());
        }
    }
    //Funcion que expande el nodo superior
    private void addAdjacentUpperRow(Node currentNode) {
        int row = currentNode.getRow();
        int col = currentNode.getCol();
        int upperRow = row - 1;
        if (upperRow >= 0) {
            if (col - 1 >= 0) {
                //checkNode(currentNode, col - 1, upperRow, getDiagonalCost()); // Comment this if diagonal movements are not allowed
            }
            if (col + 1 < getSearchArea()[0].length) {
                //checkNode(currentNode, col + 1, upperRow, getDiagonalCost()); // Comment this if diagonal movements are not allowed
            }
            checkNode(currentNode, col, upperRow, getHvCost());
        }
    }
    
    //Funcion expandir nodo (nodo previo, columna nueva, fila nueva, coste de ir del nodo previo al nuevo)
    private void checkNode(Node currentNode, int col, int row, int cost) {
        //Comprobamos en search area si el nodo expandido es un muro
    	Node block_node = getSearchArea()[row][col];
        //Y generamos el nodo por si no lo fuera, añadiendo su orientacion dependiendo de su 
    	//posicion relativa respecto al nodo previo
        Node adjacentNode = new Node(row, col);
        if(row<currentNode.getRow()) adjacentNode.setOrientacion(0);
        if(row>currentNode.getRow()) adjacentNode.setOrientacion(1);
        if(col>currentNode.getCol()) adjacentNode.setOrientacion(2);
        if(col<currentNode.getCol()) adjacentNode.setOrientacion(3);
        
        //SI no es un bloque Ni esta en cerrados
        if (!block_node.isBlock() && !getClosedList().contains(adjacentNode)) 
        	{        	
	            //Si no está en abiertos
	        	if (!getOpenList().contains(adjacentNode))
	        	{
	        		//Lo añadimos a abiertos, recordando el nodo previo como padre
	                adjacentNode.setNodeData(currentNode, cost);
	                getOpenList().add(adjacentNode);
	            } 
	        	//Si ya esta en abiertos
	        	else 
	            {
	        		//Tiene que quitarse el peor y mantener en abiertos solo el mejor!!
	                boolean changed = adjacentNode.checkBetterPath(currentNode, cost);
	                if (changed)
	                {
	                	//Quitamos y añadimos el nodo modificado para que la cola de prioridad vuelva a ordenarse
	                	//aplicando el posible nuevo coste del nodo
	                	//Debido a la representacion del problema que estamos usando estoy bastante seguro de que
	                	//es increiblemente improbable que se generen dos nodos iguales y sea necesario recalcular el 
	                	//mejor padre, pero por si acaso está implementado
	                    getOpenList().remove(adjacentNode);
	                    getOpenList().add(adjacentNode);

	                }
	            }
        	}
        }
    //Funcion que comprueba si el nodo actual esta en la posicion del nodo final
    private boolean isFinalNode(Node currentNode) {
    	//La funcion equal no nos sirve porque verifica también la orientación y no nos interesa la orientacion
    	//del nodo objetivo
    	return currentNode.getCol() == finalNode.getCol() && currentNode.getRow() == finalNode.getRow();
    }
    //Funcion que devuelve si la cola de abiertos esta vacia
    private boolean isEmpty(PriorityQueue<Node> openList) {
        return openList.size() == 0;
    }
    //Funcion que le da valor de muro a una posicion del searchArea
    private void setBlock(int row, int col) {
        this.searchArea[row][col].setBlock(true);
    }
    //Getter del nodo inicial
    public Node getInitialNode() {
        return initialNode;
    }
    //Setter del nodo inicial
    public void setInitialNode(Node initialNode) {
        this.initialNode = initialNode;
    }
    //Getter del nodo final
    public Node getFinalNode() {
        return finalNode;
    }
    //Setter del nodo final
    public void setFinalNode(Node finalNode) {
        this.finalNode = finalNode;
    }
    //Getter del searchArea
    public Node[][] getSearchArea() {
        return searchArea;
    }
    //Setter del searchArea
    public void setSearchArea(Node[][] searchArea) {
        this.searchArea = searchArea;
    }
    //Getter de la cola abiertos
    public PriorityQueue<Node> getOpenList() {
        return openList;
    }
    //Setter de la cola abiertos (copia)
    public void setOpenList(PriorityQueue<Node> openList) {
        this.openList = openList;
    }
    //Getter de la lista cerrados
    public List<Node> getClosedList(){
    	return closedList;
    }
    //Setter de la lista cerrados (copia)
    public void setClosedList(List<Node> closedList)
    {
    	this.closedList = closedList;
    }
    //Getter y Setter del coste Horizontal-Vertical
    public int getHvCost() {
        return hvCost;
    }
    public void setHvCost(int hvCost) {
        this.hvCost = hvCost;
    }
    //Getter y setter del coste Diagonal
    private int getDiagonalCost() {
        return diagonalCost;
    }

    private void setDiagonalCost(int diagonalCost) {
        this.diagonalCost = diagonalCost;
    }
}

