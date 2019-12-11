# EDyAI-MFP
Resolución del problema del flujo máximo en un grafo dirigido bajo las condiciones del enunciado en TP Diciembre.pdf

Para compilar el programa, descomprimir el archivo ZarateAldana.tar.gz, abrir una consola en la carpeta descomprimida e ingresar

$ make

y luego para ejecutarlo:

$ ./main archivoEntrada.txt archivoSalida.txt

Nota: los nombres de los nodos en archivoEntrada deben ser un string con menos de 50 caracteres.

En este trabajo se propuso resolver el problema de encontrar el flujo máximo en una red de flujos. Para ello, en una primera instacia se trataron algunos algoritmos derivados del clásico Ford-Fulkerson pero más con fines relacionados a la materia Complementos I que otra cosa. Por los artículos que pude leer, elegir un algoritmo me resultó difícil pues su eficiencia práctica
depende mucho de la naturaleza de la entrada (densidad, espaciamiento de nodos en el grafo, etc).
Entonces, en una búsqueda de ver algo nuevo, se implementó una versión diferente, utilizando el algoritmo Push-Relabel.
Si comparamos los algoritmos, el Ford-Furkerson toma un approach totalmente diferente al Push-Relabel. El Ford-Fulkerson siempre conserva un flujo válido en todo momento y lo va aumentando hasta que no exista un camino aumentante desde la fuente hasta el sumidero, mientras que en el push-relabel no existe dicho camino en todo momento, sino que se va mejorando el preflujo hasta que se convierte en un flujo válido.

El algoritmo tiene dos estapas bien diferenciadas. La primera clacula un pre-flujo maximo realizando operaciones de descarga
en nodos activos cuyas etiquetas son menores a n. La segunda, convierte el maximo pre-flujo en un flujo máximo retornando el exceso de flujo que no puede alcanzar el sumidero hacia la fuente. 

A lo largo de la ejecución, el algoritmo mantiene un "preflujo" que progresivamente se va convirtiendo en un flujo máximo moviendo flujo entre vértices conectados, usando la operación push. Siempre y cuando se pueda, chequeandose esto con la función relabel.

El algoritmo en líneas muy generales:

push-relabel-generico(G, c, s, t):
    crear un pre-flujo que satura todas las aristas salientes de la fuente
    hight[fuente]=cantidadNodos
    hight[v]=0 para todos los nodos restantes
    while existe la posibilidad de aplicar una operación push o relabel
        ejecutar dicha operación

Cabe destacar que en esta oportunidad, se utilizó como regla para elegir los nodos activos el algoritmo relabel-to-front push-relabel. Este organiza todos los nodos en una lista y mantiene la invariante que la lista está topológicamente ordenada respecto a la red admisible. "Escanea" la lista desde el frente hacia atrás y va haciendo operaciones de descarga en el nodo actual si este está activo. Si un nodo es re-etiquetado, se lo mueve al frente de la lista, y el escaneo comienza nuevamente desde el frente.


Para representar los datos, se utilizó una estructura llamada Grafo, con todas los elementos relacionados al grafo de entrada, es decir:
1) Una lista simplemente enlazada para almacenar los nombres de los nodos, donde a cada nodo se le asigna un índice según el orden en el que fue agregado en la lista. (Se eligió esta estructura a fin de ahorrar memoria)
2) Una matriz n x n, siendo n la cantidad de nodos del grafo. Donde A[i][j] indica que desde el nodo i al nodo j, existe una conexión con capacidad= A[n * i + j]. (Diseñamos de esta forma la matriz para poder acceder de esta manera y acelerar dicho cálculo)
3) Entero que representa la cantidad de nodos en el grafo.

Algunas consideraciones:
1. El programa fue testeado numerosas veces con un generador de entradas sencillo, se dejan adjuntas algunas entradas como ejemplo. Los tiempos de ejecución pueden verse al finalizar el programa.
2. Por la naturaleza del algoritmo, se omitieron imprimir aquellas conexiones cuyo flujo en el flujo maximal fuesen 0.

Se utilizó como principal guía el paper de Golberg y Tarjan, adjuntado en la carpeta Fuentes.
