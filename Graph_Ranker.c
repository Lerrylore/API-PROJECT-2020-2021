#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct RankHeapNode
{
	int idx;
	int sum;
};

struct MinHeapNode
{
	int v;
	int weight;
};

void parsingIsMyLife(char *s, int *matrix, int dim)
    {
        int i, number, temp=0, idx=0;
        char virgola[]=",", accapo[]="\n"; 
        while(idx<dim)
        {
            number=(int)s[temp]-48;
            for(i=temp+1;s[i]!=virgola[0] && s[i]!=accapo[0];i++){
                number = ((int)*(s+i)-48)+number*10;
            }
            matrix[idx]=number;
            temp=i+1;
            idx++;
        }
        return;

    }

    ////////////////////////////////////////////////////////////////////// RANKING SYSTEM
//nodo padre
int parent(int i) {
    return (i - 1) / 2;
}

//nodo figlio sinistro
int left_child(int i) {
    return 2*i + 1;
}

//nodo figlio destro
int right_child(int i) {
    return 2*i + 2;
}

void swap(struct RankHeapNode *x, struct RankHeapNode *y) { 
    struct RankHeapNode temp = *x;
    *x = *y;
    *y = temp;
}

void max_heapify(struct RankHeapNode a[], int i, int n){
	
	int right = right_child(i);
    int left = left_child(i);
    int largest = i;

    //nodo sinistro maggiore di current?
    if (left <= n && a[left].sum > a[largest].sum) {
        largest = left;
    }

    //nodo destro maggiore di current?
    if (right <= n && a[right].sum > a[largest].sum) {
        largest = right;
    }


    // scambia il nodo più grande con quello corrente finchè non è più grande del destro e sinistro
    
    if (largest != i) {
        struct RankHeapNode temp = a[i];
        a[i].idx = a[largest].idx;
        a[i].sum = a[largest].sum;
        a[largest] = temp;
        max_heapify(a, largest, n);
    }

}
// Rimuovi il massimo
struct RankHeapNode extract_max(struct RankHeapNode a[], int *n) {
	
    struct RankHeapNode max_item = a[0];

    //rimpiazza il primo con l'ultimo elemento
    a[0] = a[*n - 1];
    *n = *n - 1;

    // ristora le proprietà dell'heap
    max_heapify(a, 0, *n);
    return max_item;
}
void insert(struct RankHeapNode a[], struct RankHeapNode data, int *n, int k) {
    if (*n >= k) {
        if(data.sum < a[0].sum)
        {
        	extract_max(a, n);
        	insert(a, data, n, k);
    	}
        return;
    }
    // prima inserisci nell'ultima posizione dell'array e poi scorrilo di uno
    a[*n] = data;
    *n = *n + 1;


    int i = *n - 1;
    while (i != 0 && a[parent(i)].sum < a[i].sum) {
        swap(&a[parent(i)], &a[i]);
        i = parent(i);
    }
}	


// prints the heap
void print_heap(struct RankHeapNode a[], int n) {
    int i;
    if(n != 0)
    {
    	printf("%d", a[0].idx);
        for (i = 1; i < n; i++) {
         printf(" %d", a[i].idx);
        }
        
    }
    printf("\n");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool isInMinHeap(struct MinHeapNode *minHeap, int v, int *pippo, int *pos)
{
   if (pos[v] < *pippo)
     return true;
   return false;
}

int isEmpty(struct MinHeapNode* minHeap, int pippo)
{
    return pippo == 0;
}

void swapMinHeapNode(struct MinHeapNode* a,struct MinHeapNode* b) //serve per MinHeapify
{
    struct MinHeapNode t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeapNode* minHeap, int idx, int *pippo, int *pos)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if (left < *pippo && minHeap[left].weight < minHeap[smallest].weight )
      smallest = left;
 
    if (right < *pippo && minHeap[right].weight < minHeap[smallest].weight )
      smallest = right;
 
    if (smallest != idx)
    {
        // i nodi da swappare nel min heap
        struct MinHeapNode smallestNode = minHeap[smallest];
        struct MinHeapNode idxNode = minHeap[idx];
        // le posizioni da scambiare
        pos[smallestNode.v] = idx;
        pos[idxNode.v] = smallest;
        //scambia le posizioni
        swapMinHeapNode(&minHeap[smallest], &minHeap[idx]);
 		minHeapify(minHeap, smallest, pippo, pos);
    }
}

struct MinHeapNode extractMin(struct MinHeapNode* minHeap, int *pippo, int *pos)
{
    struct MinHeapNode root = minHeap[0];
 	
    // rimpiazza la radice con un ultimo nodo
    struct MinHeapNode lastNode = minHeap[*pippo - 1];
    minHeap[0] = lastNode;
   
    //aggiorna la posizione dell'ultimo nodo
    pos[root.v] = *pippo-1;
    pos[lastNode.v] = 0;
 	
    //riduci la size dell'heap
    --*pippo;
    minHeapify(minHeap, 0, pippo, pos);
 
    return root;
}



void decreaseKey(struct MinHeapNode* minHeap, int v, int dist, int *pos)
{
    //Prendi l'indice di v in un array
    int i = pos[v];
    //Update the distance value
    minHeap[i].weight = dist;
 
    while (i && minHeap[i].weight < minHeap[(i - 1) / 2].weight)
    {
        //scambia il nodo con il padre
        pos[minHeap[i].v] =(i-1)/2;
        pos[minHeap[(i-1)/2].v] = i;
        swapMinHeapNode(&minHeap[i], &minHeap[(i - 1) / 2]);
        //Muovi all'indice padre
        i = (i - 1) / 2;
    }
}

int dijkstra(int * matrix, int src, int dim)
{
	int i, j;
	int pos[dim];
    int sum=0;
    int *pippo;//è la size
    //Numero di vertici
    int V = dim;
    int dist[V];    
    pippo=(int*)malloc(sizeof(int));
    struct MinHeapNode* minHeap = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode)*dim);
 	
    //Inizializzazione min heap
    for (int v = 0; v < V; ++v)
    {
        dist[v] = 2147483647;
        minHeap[v].weight = dist[v];
        minHeap[v].v = v;
        pos[v]=v;
    }
    
 	
    // /src e' 0 in questo caso.
    minHeap[src].weight = dist[src]; //potrebbe non servire
    pos[src] = 0;
    dist[src] = 0;
    decreaseKey(minHeap, 0, dist[src], pos);
	*pippo=V;
    //uso il minheap per storare i nodi le cui distanze sono incognite
    while (!isEmpty(minHeap,*pippo))
    {
        //estrai il vertice con valore minimo
        struct MinHeapNode minHeapNode = extractMin(minHeap, pippo, pos);
       // printf("%d\n", minHeapNode.v);
        //immagazzina il vertice estratto
        int u = minHeapNode.v;
 		
        //attraversa tutti i vertici
     	 	for(j=0;j<dim;j++)
        	{
	            int v = j;
	            
	            if (isInMinHeap(minHeap, v, pippo, pos) && dist[u] != 2147483647 && matrix[u*dim +j] + dist[u] < dist[v] && matrix[u*dim +j]!= 0)
	            {
	                dist[v] = dist[u] + matrix[u*dim+j];
	                //aggiorna la distanza
	                decreaseKey(minHeap, v, dist[v], pos);
	            }
	           // printf("%d %d %d\n", minHeap[0].v, minHeap[1].v, minHeap[2].v);
        	}
    }
    // le shortest distance
    
    for (i=0;i<V;i++){
    	if(dist[i]<2147483647){
    		sum += dist[i];
    	}
	}
	return sum;
}


int main(){
    int dim;
    int *pippo;
    int k, i, sum, idx = 0;
    char s[100000];
    if(scanf("%d %d\n",&dim, &k) == 1){}
    int* matrix;//matrice di adiacenza
    struct RankHeapNode* rank = malloc(sizeof(struct RankHeapNode)*k); //classifica max-heap
    struct RankHeapNode data;
	matrix = (int *)malloc(sizeof(int)*dim*dim); 
	pippo= (int *)malloc(sizeof(int));
  	*pippo=0;

    while(fgets(s, 100000, stdin) != NULL)
    {
       
        if(strcmp(s, "AggiungiGrafo\n") == 0)
        {

        	for(i=0;i<dim;i++){	//registro la matric+e dall'input
        		if(fgets(s, 100000, stdin)==NULL);
                parsingIsMyLife(s, matrix + i*dim, dim);
    		}
    		

        	sum = dijkstra(matrix, 0, dim);
        	data.sum = sum;
        	
        	data.idx = idx;
        	idx++;
        	
        	insert(rank, data, pippo, k); //aggiunta al max-heap
           
        }
        //printf("1 + %s\n",s);

        if(strcmp(s,"TopK\n") == 0)
        {
            //TopK();
            print_heap(rank, *pippo);
        }
    	
    	
	}

    free(matrix);
	
	return 0;
}
