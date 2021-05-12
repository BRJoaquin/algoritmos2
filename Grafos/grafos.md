# Grafos

Calcular las posibles aristas de un grafo:
Grafos dirigidos = V^2
Grafos no dirigidos V.(V-1)/2

## Orden topológico
1. Aplicable para grafos dirigidos y acíclicos.
1. Sirve para detectar ciclos.

#### Codigo
```c
void ordenacionTopologica() {  
	int * gradoEntranda =  initGradoDeEntrada(); // O(V^2) MA || O(A) LA  
	int * visitados = initVisitados(); // O(V)  
	for(int cont = 1; cont <= |V|;cont ++) { // O(V^2)  
		vertice = verticeGradoEntranteCeroNoVisitado(gradoEntrante , visitados); // O(V)  
		if (vertice == -1) //No existe  
			return cout<<“HAY UN CICLO”;  
		else{  
			visitados\[vertice\] = true;  
			cout << vertice << endl;  
			for(int w = 1; w <= |V|: w++)  // O(V) MA <- se puede mejorar con LA  
				if(w adyacente a v)  
					gradoEntranda\[w\]--;  
			}  
	}  
}
```

## Camino más corto en grafo no ponderado
Nos permite saber el camino más corto desde un vértice dado.
Puede verse interpretado como un BFS. Ya que obtenemos los caminos más cortos desde un vertice dado.

| | Lista Adyacencia | Matriz |
| --|-----|----|
| Orden | O(V+A) | - |

#### Código

```c 
void CaminoMasCortoNoPonderado(int origen) {  
	int * visitados =  initVisitados(); // array de V casilleros, empiezan todos en false  
	int * costo = initCosto(origen); // array de V casilleros, todos con valor “INF” a excepción de origen (con 0)  
	int * vengo = initVengo(); // array de V casilleros, todos con valor -1  
  
	Cola<int> cola;  
	cola.encolar(origen);  
  
	while (!cola.EsVacia()) {  
		int vertice = cola.desencolar();  
		visitados[vertice]= true; // lo marco como visitado  
		paraCada w adyacenteA vertice  
		if(costo[w] > costo[vertice] + 1) // solo procesamos los que no hayan sido visitados antes  
			cola.encolar(w);  
			costo[w] = costo[vertice] + 1;  
			vengo[w] = vertice;
```

## Dijkstra
Nos permite saber el costo y el camino a todo vértice desde un origen dado.
Se aplica a grafos ponderados

#### Limitaciones
1. No acepta aristas negativas
2. Una vez procesado el vértice no vuleve a pasar, por ende no mejora el costo ?.
#### Ordenes
| | Lista Adyacencia | Matriz |
| --|-----|----|
| Orden | O(A.logV)| O(Vˆ2) |

#### Código Lista Adyacencia.
```c
void dijkstra(int origen)
	int* visitados = initVisitados(); // all false
	int* costos = initCostos(origen); // costs inited with INT_MAX exepts for origen
	int* vengo = initVengo(); // all -1;
	ColaPrioridad cp();
	for(int i=1; i<=V; i++) { cp.encolar(i, costos[i]) }  // se encolan todos los vértices con inf, menos el origen con 0
	while(!cp.estaVacia()) 
		int v = cp.desencolar(); // extrae el vértice de menor costo no visitado
		visitados[v] = true;
		para cada w adyacente a v 
			if(!visitados[w] && costos[w] > costos[v] + dist(v,w))
				costos[w] = costos[v] + dist(v,w);
				vengo[w] = v;
				cp.actualizarPrioridad(w, costos[w]); // se actualiza la prioridad
```

## Camino más corto con ponderación negativa

Nos permite saber el costo a todo par de vertices e ir mejorando los costos.
Acepta aristas negativas.

#### Ordenes
| | Lista Adyacencia | Matriz |
| --|-----|----|
| Orden | O(A.V)| O(Vˆ2) |

#### Código
```c

void CaminoMasCortoPonderacionNegativa(int origen) {
	int * costo = initCosto(origen); // array de V casilleros, todos con valor “INF” a excepción de origen (con 0)
	int * vengo = initVengo(); // array de V casilleros, todos con valor -1

	Cola<int> cola;
	cola.encolar(origen);

	while (!cola.estaVacia()) 
		int v= cola.desencolar();
		paraCada w adyacenteA vertice
			if(costo[w]  > costo[v] + dist(v,w))
				costo[w] = costo[v] + dist(v,w);
				vengo[w] = v;
				if(!cola.existe(w)) // preguntamos la cola si ya existe el elementos, esto también se puede hacer un array en O(1)
					cola.encolar(w);	
```

## Floyd
Nos permite saber el camino más corto ENTRE TODO PAR DE VERTICES
Acepta aristas negativas.

#### Ordenes
| | Lista Adyacencia | Matriz |
| --|-----|----|
| Orden | O(Vˆ3)| O(Vˆ3) |

#### Código
```c
void floyd() {
	int** matriz = grafoMatriz(); // devuelve una copia de la matriz de adyacencia
	int** matrizCamino = initCaminos(); 
	for(int i=1; i<=V; i++)
		matriz[i][i]=0; // “borramos” la diagonal
	
	for(int k=1; k<=V; k++) // el nodo “intermedio”
		for(int i=1; i<=V; i++)
			for(int j=1; j<=V; j++)
				if(matriz[i][j] > matriz[i][k] + matriz[k][j])
					matriz[i][j] = matriz[i][k] + matriz[k][j]
					matrizCamino[i][j] = k;
```


## Warshall
Nos permite encontrar ciclos en un grafo dirigido.
Obtenemos la matriz de clausura transitiva.

#### Matriz de clausura transitiva para grafo no dirigido
La matriz de clausura transitiva en un grafo no dirigido, cuando ésta está completa de 1s, nos quiere decir que es un grafo conexo.
De lo contrario es no conexo.

#### Matriz de clausura transitiva para grafo dirigido
La matriz de clausura transitiva en un grafo dirigido, cuando ésta está completa de 1s, nos quiere decir que es un grafo fuertemente conexo. 
Si tengo algunos 0s, puede ser no conexo o debilmente conexo.

Para saber si es debilmente conexo fuerzo el grafo a que sea no dirigido y corro warshall. Si tiene 1s en todas las posiciones, quiere decir que es debilmente conexo.

#### Ordenes
| | Lista Adyacencia | Matriz |
| --|-----|----|
| Orden | O(Vˆ3)| O(Vˆ3) |

#### Codigo
```c
void warshall()
	bool** matriz = grafoAristas(); // devuelve una matriz de VxV donde matriz[i][j] = true si hay una arista i->j
	
	for(int k=1; k<=V; k++) // el nodo “intermedio”
		for(int i=1; i<=V; i++)
			for(int j=1; j<=V; j++)
				matriz[i][j] = matriz[i][j] || matriz[i][k] && matriz[k][j];
```

## Prim
(similar a dijkstra)

Sirve para grafos no dirigidos, ponderados y conexos.
Nos permite conectar todos los vertices con el menor costo posible.
Indentificador: Arbol de Cubrimiento Minimo.

#### Ordenes
| | Lista Adyacencia | Matriz |
| --|-----|----|
| Orden | O(A.logV)| O(Vˆ2) |

#### Código
```c
void prim(int origen)
	int* visitados = initVisitados(); // array V casilleros, todos en false
	int* costos = initCostos(origen); // array V casillero, todos en INF menos origen con 0
	int* vengo= initVengo(); // array V casilleros, todos en -1
	for(int i=0; i<V; i++) 
		int v = verticeDesconocidoDeMenorCosto(visitados, costos); // vértice a procesar
		visitados[v] = true;
		para cada w adyacente a v 
			if(!visitados[w] && costos[w] > dist(v,w))
				costos[w] = dist(v,w);
				vengo[w] = v;
```

## Kruskal
Identificador: Arbol de Cumbrimiento Mínimo.
**Utiliza MFset**

#### Ordenes:
| | Lista Adyacencia | Matriz |
| --|-----|----|
| Orden | O(A.logV)| O(A.logV) |

#### Código
```c
void kruskal() {
	ColaPrioridad cp(); // imp. heap
	insertarAristas(cp); // inserto todas las aristas del grafo
	List<Arista> solucion(); // guardo las aristas que serán parte de la solución
	MFset mfset(V+1); // Merge-Find Set de V+1 elementos
	int aristasAceptadas = 0;
	
	while(!cp.estaVacia() || aristasAceptadas < V-1)
		Arista a = cp.pop();// obtenemos la misma arista sin procesar
		if(mfset.find(a.origen) != mfset.find(a.destino)) // !formaCiclo(solucion, a)
			mfset.merge(a.origen, a.destino);
			solucion.agregar(a);
			aristasAceptadas++;
````

## BFS Amplitud
Recorre el grafo desde el origen dado, recorriendo nivel por nivel.
Nos permite saber si dos vertices están conectados.
Nos permite saber el camino más corto en grafos no ponderados.
Encontrar un nodos a una distacia dada.

#### Ordenes:
| | Lista Adyacencia | Matriz |
| --|-----|----|
| Orden | O(A+V)| O(Vˆ2) |

#### Código
```c
void BFS(int origen)
	bool * encolados = initEncolados(); // array de V+1 pos, todos en false
	Cola c; //FIFO
	c.encolar(origen);
	encolados[origen] = true;
	while(!c.estaVacia())
		int v = c.desencolar();
		para todo w adyacente a v
			if(!encolados[w])
				c.encolar(w);
				encolados[w] = true;
```



## DFS Profundidad
ES RECURSIVO!
Nos permite saber si dos vertices están conectados.
Podemos detectar ciclos.
Podemos encontrar componentes fuertemente conexas en un grafo dirigido.
Podemos identificar puntos de articulación. Sin un punto de articulación el grafo queda dividio en dos.

#### Ordenes:
| | Lista Adyacencia | Matriz |
| --|-----|----|
| Orden | O(A+V)| O(A+V) |

```c
   void DFS(int origen, bool* visitados) // O(V+A) análisis 
	visitados[origen] = true;
	// procesar/imprimir origen
	para cada w adyacente a origen
		if(!visitados[w])
			DFS(w, visitados);
```