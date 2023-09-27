package src_Gangoso_Klock_Jorge;

import core.game.StateObservation;
import core.game.Observation;
import core.player.AbstractPlayer;
import ontology.Types;
import ontology.Types.ACTIONS;
import tools.ElapsedCpuTimer;

import tools.Vector2d;
import java.util.ArrayList;
//import java.util.Random;
import java.util.*;


public class Agent extends AbstractPlayer
{
	Vector2d factor_escala;
	Vector2d posicion_agente;
	Vector2d orientacion_agente;
	Vector2d portal;
	List<Vector2d> diamantes_2d;
	List<Vector2d> enemigos_2d;
	
	int [][] heat_static_map; //Mayor valor indica mayor seguridad
	int [][] heat_dynamic_map; //Resta valores al mapa estatico donde hay enemigos
	
	List<Node> path;
	int nivel; //1-deliberativo simple 2-deliberativo compuesto 3-reactivo simple 4-reactivo compuesto 5-reactivo deliberativo
	int total_columns;
	int total_rows;
//Constructor de la clase, tiene múltiples funciones a parte de inicializar atributos
public Agent (StateObservation stateObs, ElapsedCpuTimer elapsedTimer) 
	{
		//Inicializamos los arrayList
		path = new ArrayList<Node>();
		diamantes_2d = new ArrayList<Vector2d>();
		//Calculamos el factor de escala para el problema que tenemos
		factor_escala = new Vector2d(stateObs.getWorldDimension().width / stateObs.getObservationGrid().length, stateObs.getWorldDimension().height / stateObs.getObservationGrid()[0].length);
		//Capturamos el tamaño completo del mapa
		total_columns = (int)(stateObs.getWorldDimension().width/factor_escala.x);
		total_rows = (int)(stateObs.getWorldDimension().height/factor_escala.y);
		//Capturamos la posicion del individuo
		this.actualizar_posicion(stateObs);
		//Inicializamos el heat_map por si hiciera falta
		heat_static_map = new int[total_rows][total_columns];
		heat_dynamic_map = new int[total_rows][total_columns];
		//Capturamos la posicion de la salida (se asume que solo hay 1 y por eso no se calcula in situ)
		portal_cercano(stateObs);
		//Definir el nivel en que estamos
		this.localizar_diamantes(stateObs);
		this.localizar_enemigos(stateObs);
		
		if (this.diamantes_2d.isEmpty() && enemigos_2d.isEmpty())
			{
			nivel = 1;
			}
		else if (!this.diamantes_2d.isEmpty() && enemigos_2d.isEmpty())
			{
			nivel = 2;
			}
		else if (this.diamantes_2d.isEmpty() && enemigos_2d.size() == 1)
			{
			static_mapping(stateObs);
			nivel = 3;
			}
		else if (this.diamantes_2d.isEmpty() && enemigos_2d.size() == 2)
			{
			static_mapping(stateObs);
			nivel = 4;
			}
		else
			{
			static_mapping(stateObs);
			nivel = 5;		
			}
		
	}
//Función que almacena las posiciones de los enemigos
private void localizar_enemigos(StateObservation stateObs)
{
	this.enemigos_2d = new ArrayList<Vector2d>();
	ArrayList<Observation>[] enemigos = stateObs.getNPCPositions();
	if(enemigos != null)
	{
		for(int i=0; i<enemigos[0].size(); i++)
		{
			Vector2d enemigo_temp = enemigos[0].get(i).position;
			enemigo_temp = this.pixels_to_coord(enemigo_temp.x, enemigo_temp.y);
			this.enemigos_2d.add(enemigo_temp);
		}
	}	
}
//Función que almacena las posiciones de los diamantes
public void localizar_diamantes(StateObservation stateObs)
{
	this.diamantes_2d = new ArrayList<Vector2d>();
	ArrayList<Observation>[] diamantes = stateObs.getResourcesPositions();
	if(diamantes != null) 
	{
		for(int i=0; i<diamantes[0].size(); i++)
		{
			Vector2d diamante_temp = diamantes[0].get(i).position;
			diamante_temp = this.pixels_to_coord(diamante_temp.x, diamante_temp.y);
			this.diamantes_2d.add(diamante_temp);
		}
	}
}
//Función que genera el mapa de calor estatico
public void static_mapping(StateObservation stateObs)
{
	//Asignamos el valor 0 a los muros y N a los que no, donde N son las casillas cercanas libres
	for(int i = 0; i<this.heat_static_map.length; i++)
	{
		for(int j = 0; j<this.heat_static_map[i].length; j++)
		{
			valorar_libertad(i,j, stateObs);
		}
	}
}
//Función que genera el mapa de calor dinamico
public void dynamic_mapping(StateObservation stateObs)
{
	//Copiar el mapa estático
	resetearMapaDinamico();
	this.localizar_enemigos(stateObs);
	//Cogemos el mapa estático y le restamos 2 a las casillas cercanas en linea recta con respecto al enemigo
	//Le restamos 2 también a las casillas diagonales
	//E igualamos a 0 el valor de la casilla donde esta el propio enemigo
	for(int i=0; i<this.enemigos_2d.size(); i++)
	{
		int x = (int)this.enemigos_2d.get(i).x;
		int y = (int)this.enemigos_2d.get(i).y;
		
		devalorar_mapa(y,x);
	}
}
//Función que selecciona el destino más prometedor de una lista de destinos (1 solo enemigo)
private Vector2d seleccionar_destino_prometedor(ArrayList<Vector2d> destinos, StateObservation stateObs) 
{
	int mayor_distancia = 0;
	Vector2d mejor_destino = destinos.get(0);
	for(int i=0; i<destinos.size(); i++)
	{
		int distancia = this.distancia_manhattan(destinos.get(i), this.enemigos_2d.get(0));
				if(distancia>mayor_distancia)
				{
					mayor_distancia = distancia;
					mejor_destino = destinos.get(i);
				}
	}
	return mejor_destino;
}
//Función que selecciona el destino más prometedor de una lista de destinos (1 o Múltiples enemigos)
private Vector2d seleccionar_destino_prometedor_plus(ArrayList<Vector2d> destinos, StateObservation stateObs) {
	//Localizar el enemigo más cercano
	int menor_distancia = Integer.MAX_VALUE;
	Vector2d enemigo_cercano = this.enemigos_2d.get(0);
	for(int i=0; i<this.enemigos_2d.size(); i++)
	{
		int distancia = this.distancia_manhattan(this.enemigos_2d.get(i), this.posicion_agente);
		if(distancia < menor_distancia)
		{
			menor_distancia = distancia;
			enemigo_cercano = this.enemigos_2d.get(i);
		}
	}
	//Buscar el destino de la lista con mayor distancia manhattan al enemigo cercano
	int mayor_distancia = 0;
	Vector2d mejor_destino = destinos.get(0);
	for(int i=0; i<destinos.size(); i++)
	{
		int distancia = this.distancia_manhattan(destinos.get(i), enemigo_cercano);
				if(distancia>mayor_distancia)
				{
					mayor_distancia = distancia;
					mejor_destino = destinos.get(i);
				}
	}
	return mejor_destino;
}
//Función que iguala los valores del mapa dinámico al estático
private void resetearMapaDinamico() 
{
	for(int i=0; i<this.heat_static_map.length; i++)
	{
		for(int j=0; j<this.heat_static_map[i].length; j++)
		{
			this.heat_dynamic_map[i][j] = this.heat_static_map[i][j];
		}
	}
}
//Función que reduce el valor de seguridad del mapa dinámico alrededor de un punto (x,y)
private void devalorar_mapa(int x, int y)
{
this.heat_dynamic_map[x][y] = 0;
	
	if(this.heat_dynamic_map[x+1][y] > 1)
		{
		this.heat_dynamic_map[x+1][y] =2;
		if(this.heat_dynamic_map[x+2][y] != 0) 
			{
			this.heat_dynamic_map[x+2][y] = 2;
			if(this.heat_dynamic_map[x+3][y] != 0) this.heat_dynamic_map[x+3][y] = 2;
			}
		}
	else this.heat_dynamic_map[x+1][y] = 0;
	
	if(this.heat_dynamic_map[x-1][y] > 1)
		{
		this.heat_dynamic_map[x-1][y] =2;
		if(this.heat_dynamic_map[x-2][y] != 0) 
			{
			this.heat_dynamic_map[x-2][y] = 2;
			if(this.heat_dynamic_map[x-3][y] != 0) this.heat_dynamic_map[x-3][y] = 2;
			}
		}
	else this.heat_dynamic_map[x-1][y] = 0;
	
	if(this.heat_dynamic_map[x][y+1] > 1)
		{
		this.heat_dynamic_map[x][y+1] =2;
		if(this.heat_dynamic_map[x][y+2] != 0)
			{
			this.heat_dynamic_map[x][y+2] -= 2;
			if(this.heat_dynamic_map[x][y+3] != 0) this.heat_dynamic_map[x][y+3] = 2;
			}
		}
	else this.heat_dynamic_map[x][y+1] = 0;
	
	if(this.heat_dynamic_map[x][y-1] > 1)
		{
		this.heat_dynamic_map[x][y-1] =2;
		if(this.heat_dynamic_map[x][y-2] != 0)
			{
			this.heat_dynamic_map[x][y-2] = 2;
			if(this.heat_dynamic_map[x][y-3] != 0) this.heat_dynamic_map[x][y-3] = 2;
			}
		}
	else this.heat_dynamic_map[x][y-1] = 0;
	
	if(this.heat_dynamic_map[x+1][y+1] != 0) this.heat_dynamic_map[x+1][y+1] = 2;
	if(this.heat_dynamic_map[x+1][y-1] != 0) this.heat_dynamic_map[x+1][y-1] = 2;
	if(this.heat_dynamic_map[x-1][y+1] != 0) this.heat_dynamic_map[x-1][y+1] = 2;
	if(this.heat_dynamic_map[x-1][y-1] != 0) this.heat_dynamic_map[x-1][y-1] = 2;
}
//Función que comprueba si la posicion (x,y) es un muro
private boolean es_muro(int x, int y, StateObservation stateObs)
{
	int[][] muros = this.localizar_obstaculos(stateObs);
	boolean es_muro = false;
	
	for(int i=0; i<muros.length; i++)
	{
		if (muros[i][0] == x && muros[i][1] == y)
		{
			es_muro = true;
		}
	}
	return es_muro;
}
//Función que comprueba el nivel de seguridad de la posicion del agente
private int valor_seguridad(Vector2d posicion_agente) {
	return this.heat_dynamic_map[(int) posicion_agente.y][(int) posicion_agente.x];
}	
//Función que Buscar en un cuadrado 3x3 formado alrededor del agente las posiciones más seguras
private ArrayList<Vector2d> valor_seguridad_maximo(Vector2d posicion_agente) {
	//Inicializamos los valores
	int mejor_valor = 0;
	ArrayList<Vector2d> mejor_posicion = new ArrayList<Vector2d>(); 
	mejor_posicion.add(posicion_agente);
	
	for(int row=(int)posicion_agente.y-1; row<=(int)posicion_agente.y+1; row++)
	{
		for(int col=(int)posicion_agente.x-1; col<=(int)posicion_agente.x+1; col++)
		{
			int valor = this.heat_dynamic_map[row][col];
			//Almacenamos todos cuyo valor sea máximo
			if(valor == mejor_valor)
			{
				Vector2d tmp = new Vector2d();
				tmp.x = col;
				tmp.y = row;
				mejor_posicion.add(tmp);
			}
			//Si se encuentra un valor mejor, se vacía la lista y se incluye el nuevo mejor elemento
			else if(valor > mejor_valor)
				{
				mejor_valor = valor;
				mejor_posicion = new ArrayList<Vector2d>(); 
				Vector2d tmp = new Vector2d();
				tmp.x = col;
				tmp.y = row;
				mejor_posicion.add(tmp);
				}
		}
	}
	return mejor_posicion;
}
//Función que determina en el mapa de calor estático el grado de libertad que proporciona una casilla
private void valorar_libertad(int i, int j, StateObservation stateObs) 
{
	if(es_muro(i,j,stateObs))	this.heat_static_map[i][j] = 0;
	//Si no es muro, contar casillas libres en las 4 direcciones y añadir un pequeño valor 
	//para diferenciar entre peligro por posicion y peligro por enemigo
	else
	{
		if(!es_muro(i+1,j,stateObs)) this.heat_static_map[i][j] += 1;
		if(!es_muro(i-1,j,stateObs)) this.heat_static_map[i][j] += 1;
		if(!es_muro(i,j+1,stateObs)) this.heat_static_map[i][j] += 1;
		if(!es_muro(i,j-1,stateObs)) this.heat_static_map[i][j] += 1;
		
		this.heat_static_map[i][j] += 2;
	}
	
}
//Función que convierte un vector2d definido en píxeles a coordenadas x,y aplicando el factor de escala
public Vector2d pixels_to_coord(double x, double y)
{
	Vector2d solucion = new Vector2d();
	solucion.x = Math.floor(x / factor_escala.x);
	solucion.y = Math.floor(y / factor_escala.y);
	return solucion;
}
//Función para actualizar la posición del agente
public void actualizar_posicion(StateObservation stateObs)
{
	posicion_agente = stateObs.getAvatarPosition();
	posicion_agente = pixels_to_coord(posicion_agente.x, posicion_agente.y);
}
//Función para guardar las coordenadas del portal más cercano
public void portal_cercano(StateObservation stateObs)
{
	ArrayList<Observation>[] portales = stateObs.getPortalsPositions(stateObs.getAvatarPosition());
	portal = portales[0].get(0).position;
	portal = pixels_to_coord(portal.x, portal.y);
}
//Función para rellenar una matriz de obstáculos con sus coordenadas
public int[][] localizar_obstaculos(StateObservation stateObs)
{
	//Recibimos una lista con todas las posiciones de objetos inmoviles
	ArrayList<Observation>[] objetos_inmoviles = stateObs.getImmovablePositions();
	ArrayList<Vector2d> pos_muros = new ArrayList<Vector2d>();
	//Recorremos la lista guardando las coordenadas de los que son muros
	while(!objetos_inmoviles[0].isEmpty())
	{
		if(objetos_inmoviles[0].get(0).itype == 0)
		{
			Vector2d pos_pixels = objetos_inmoviles[0].get(0).position;
			pos_muros.add(pixels_to_coord(pos_pixels.x, pos_pixels.y));
		}
		objetos_inmoviles[0].remove(0);
	}
	int[][] obstaculos = new int[pos_muros.size()][2];
	//Convertimos a una matriz int[][] para pasarselo al A*
	for (int i=0; i<pos_muros.size(); i++)
	{
		//La coordenada y corresponde a las filas ([0])
		obstaculos[i][0] = (int)pos_muros.get(i).y;
		//La coordenada x corresponde a las columnas ([1])
		obstaculos[i][1] = (int)pos_muros.get(i).x;
	}
	return obstaculos;
}
//Función que calcula la distancia manhattan entre dos pares de coordenadas
public int distancia_manhattan(Vector2d x1, Vector2d x2)
{
	return (int) (Math.abs(x1.x - x2.x) + Math.abs(x1.y - x2.y));
}
//Función que localiza el siguiente objetivo (diamante o portal) de manera greedy
public Vector2d greedy(StateObservation stateObs)
{
	int diamantes_recogidos = 0;
	Vector2d destino = null;
	this.actualizar_posicion(stateObs);
	this.localizar_diamantes(stateObs);
	HashMap<Integer, Integer> recursos = stateObs.getAvatarResources(); //La clave 6 corresponde a diamantes	
	if(recursos.get(6) != null)	diamantes_recogidos = recursos.get(6);
	
	if(diamantes_recogidos >= 9)
	{
		//Si tenemos suficientes diamantes buscamos el portal
		destino = this.portal;
	}
	else
	{
		//Si no buscamos el diamante más cercano
		int distancia_menor = Integer.MAX_VALUE;
		int index_mejor = 0;
		for(int i=0; i<this.diamantes_2d.size(); i++)
		{
			int distancia_temp = distancia_manhattan(this.posicion_agente, this.diamantes_2d.get(i));
			if (distancia_temp < distancia_menor)
			{
				distancia_menor = distancia_temp;
				index_mejor = i;
			}
		}
		destino = this.diamantes_2d.get(index_mejor);
	}
	
	return destino;
}
//Función que transforma la Observation orientación, en un entero 0-Norte 1-Sur 2-Este 3-Oeste
public int orientacion_to_int(StateObservation stateObs)
{
	this.orientacion_agente = stateObs.getAvatarOrientation();
	int orientacion = 0;
	if(this.orientacion_agente.x == 1 && this.orientacion_agente.y == 1) orientacion = 0;
	if(this.orientacion_agente.x == 0 && this.orientacion_agente.y == 1) orientacion = 1;
	if(this.orientacion_agente.x == 1 && this.orientacion_agente.y == 0) orientacion = 2;
	if(this.orientacion_agente.x == -1 && this.orientacion_agente.y == 0) orientacion = 3;
	return orientacion;
}

//Función principal que decide la accion a realizar
public Types.ACTIONS act (StateObservation stateObs, ElapsedCpuTimer elapsedTimer)
	{
	//Creamos la accion solucion, inicializada a nil
	Types.ACTIONS accion = ACTIONS.ACTION_NIL;
	
	//Hacemos un switch para actuar en función del nivel en el que estemos
	switch (this.nivel)
	{
		case 1:
		{
			/************ METODO DELIBERATIVO SIMPLE ************/
			/**Si no tenemos un path que seguir**/
			if(this.path.isEmpty())
			{
					//Capturamos la posicion del agente
					this.actualizar_posicion(stateObs);
					
					//Creamos el nodo de destino
					Node nodo_final = new Node ((int)portal.y, (int)portal.x);
					//Creamos el nodo de inicio
					Node nodo_inicial = new Node((int)posicion_agente.y, (int)posicion_agente.x);
					nodo_inicial.setOrientacion(orientacion_to_int(stateObs));
					nodo_inicial.calculateHeuristic(nodo_final);

					//Creamos la instancia de la clase A* para insertar los muros y calcular el path
					AStar a_estrella = new AStar(total_rows, total_columns, nodo_inicial, nodo_final);		
					a_estrella.setBlocks(localizar_obstaculos(stateObs));
					this.path = a_estrella.findPath();
					//Eliminamos del path el primer elemento que es el nodo de inicio
					path.remove(0);
			}
			break;
		}
		case 2:
		{
			/************ METODO DELIBERATIVO COMPUESTO ************/
			/**Si no estamos siguiendo ya un camino**/
			if(this.path.isEmpty()) {
			//Elegir la gema más cercana mediante greedy
			Vector2d destino = greedy(stateObs);
			//Crear mediante A* la ruta hasta la gema
				//Creamos el nodo destino
				Node nodo_final = new Node ((int)destino.y, (int)destino.x);
				//Creamos el nodo de inicio
				this.actualizar_posicion(stateObs);
				Node nodo_inicial = new Node((int)posicion_agente.y, (int)posicion_agente.x);
				nodo_inicial.setOrientacion(orientacion_to_int(stateObs));
				nodo_inicial.calculateHeuristic(nodo_final);
				
				AStar a_estrella = new AStar(total_rows, total_columns, nodo_inicial, nodo_final);		
				a_estrella.setBlocks(localizar_obstaculos(stateObs));
				this.path = a_estrella.findPath();
				
				
				
				//Eliminamos del path el primer elemento que es el nodo de inicio
				path.remove(0);
			}
			break;
		}
		case 3:
		{
			/************ METODO REACTIVO SIMPLE ************/
			dynamic_mapping(stateObs);
			this.actualizar_posicion(stateObs);
			//Si no estamos en una posicion de máxima seguridad local movernos hacia una por la ruta más corta posible
			ArrayList<Vector2d> destinos = valor_seguridad_maximo(this.posicion_agente);
				//Dentro de los posibles destinos elegir aquel con mayor distancia manhattan respecto al enemigo
				Vector2d destino = seleccionar_destino_prometedor(destinos, stateObs);
			
				//Nodo final
				Node nodo_final = new Node ((int)destino.y, (int)destino.x);
				//Nodo inicial
				Node nodo_inicial = new Node((int)posicion_agente.y, (int)posicion_agente.x);
				nodo_inicial.setOrientacion(orientacion_to_int(stateObs));
				nodo_inicial.calculateHeuristic(nodo_final);
			AStar a_estrella = new AStar(total_rows, total_columns, nodo_inicial, nodo_final);		
			a_estrella.setBlocks(localizar_obstaculos(stateObs));
			this.path = a_estrella.findPath();
			path.remove(0);
			
			
			break;
		}
		case 4:
		{
			/************ METODO REACTIVO COMPUESTO ************/
			dynamic_mapping(stateObs);
			this.actualizar_posicion(stateObs);
			//Si no estamos en una posicion de máxima seguridad local movernos hacia una por la ruta más corta posible
			ArrayList<Vector2d> destinos = valor_seguridad_maximo(this.posicion_agente);
				//Dentro de los posibles destinos elegir aquel con mayor distancia manhattan respecto al enemigo más cercano
				Vector2d destino = seleccionar_destino_prometedor_plus(destinos, stateObs);
			
				//Nodo final
				Node nodo_final = new Node ((int)destino.y, (int)destino.x);
				//Nodo inicial
				Node nodo_inicial = new Node((int)posicion_agente.y, (int)posicion_agente.x);
				nodo_inicial.setOrientacion(orientacion_to_int(stateObs));
				nodo_inicial.calculateHeuristic(nodo_final);
			AStar a_estrella = new AStar(total_rows, total_columns, nodo_inicial, nodo_final);		
			a_estrella.setBlocks(localizar_obstaculos(stateObs));
			this.path = a_estrella.findPath();
			path.remove(0);
			
			break;
		}
		case 5:
		{
			/************ METODO REACTIVO DELIBERATIVO ************/
			//Mientras el nivel de seguridad sea > 2 consideramos que podemos seguir con el plan
			dynamic_mapping(stateObs);
			this.actualizar_posicion(stateObs);
			int seguridad = valor_seguridad(this.posicion_agente);
			
			if(seguridad < 3) //Comportamiento reactivo
			{
				ArrayList<Vector2d> destinos = valor_seguridad_maximo(this.posicion_agente);
				//Dentro de los posibles destinos elegir aquel con mayor distancia manhattan respecto al enemigo más cercano
				Vector2d destino = seleccionar_destino_prometedor_plus(destinos, stateObs);
			
				//Nodo final
				Node nodo_final = new Node ((int)destino.y, (int)destino.x);
				//Nodo inicial
				Node nodo_inicial = new Node((int)posicion_agente.y, (int)posicion_agente.x);
				nodo_inicial.setOrientacion(orientacion_to_int(stateObs));
				nodo_inicial.calculateHeuristic(nodo_final);
			AStar a_estrella = new AStar(total_rows, total_columns, nodo_inicial, nodo_final);		
			a_estrella.setBlocks(localizar_obstaculos(stateObs));
			this.path = a_estrella.findPath();
			path.remove(0);
			
			break;
			}
			else //Comportamiento deliberativo
			{
				if(this.path.isEmpty()) {
					//Elegir la gema más cercana mediante greedy
					Vector2d destino = greedy(stateObs);
					//Crear mediante A* la ruta hasta la gema
						//Creamos el nodo destino
						Node nodo_final = new Node ((int)destino.y, (int)destino.x);
						//Creamos el nodo de inicio
						this.actualizar_posicion(stateObs);
						Node nodo_inicial = new Node((int)posicion_agente.y, (int)posicion_agente.x);
						nodo_inicial.setOrientacion(orientacion_to_int(stateObs));
						nodo_inicial.calculateHeuristic(nodo_final);
						
						AStar a_estrella = new AStar(total_rows, total_columns, nodo_inicial, nodo_final);		
						a_estrella.setBlocks(localizar_obstaculos(stateObs));
						this.path = a_estrella.findPath();

						//Eliminamos del path el primer elemento que es el nodo de inicio
						path.remove(0);
					}
			}
			
			break;
		}
		default:
			System.out.println("Nivel no implementado");
	}
	
	/**Si tenemos un plan que seguir lo hacemos**/
	if(!this.path.isEmpty()) 
	{
	//Ejecutamos el plan ya calculado
	//Actualizamos la posicion del agente
	this.actualizar_posicion(stateObs);
	this.orientacion_agente = stateObs.getAvatarOrientation();
		//Vemos las coordenadas actuales y objetivo
		int fila_objetivo = path.get(0).getRow();
		int columna_objetivo = path.get(0).getCol();
		int fila_actual = (int)posicion_agente.y;
		int columna_actual = (int)posicion_agente.x;
		//Decidimos el movimiento necesario.
		//Sólo quitamos del path el nodo siguiente si es alcanzable en este tick
		//Si no significa que tenemos que usar 1 tick para girar y al siguiente act se quitará
		int orientacion = this.orientacion_to_int(stateObs);
		if(fila_objetivo < fila_actual)
		{
			accion = ACTIONS.ACTION_UP;
			if(orientacion == 0) path.remove(0);
		}
		else if(fila_objetivo > fila_actual)
		{
			accion = ACTIONS.ACTION_DOWN;
			if(orientacion == 1) path.remove(0);
		}
		else if(columna_objetivo < columna_actual)
		{
			accion = ACTIONS.ACTION_LEFT;
			if(orientacion == 3) path.remove(0);
		}
		else if(columna_objetivo > columna_actual)
		{
			accion = ACTIONS.ACTION_RIGHT;
			if(orientacion == 2) path.remove(0);
		}
	}
	return accion;
	}
}

