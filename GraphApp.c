#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int vertex;
    char name[50];
    char surname[50];
    struct node* next;
} NODE;



typedef struct graph{
	int numVertices;
	struct node** adjLists;
	int* visited;
}GRAPH;

typedef struct queue {
    int front;
    int rear;
} QUEUE;


GRAPH* readFileAndCreateGraph();
void add_edge (GRAPH* graph, int s, int d);
GRAPH* remove_vertex(GRAPH* graph, int vertex);
void enqueue (QUEUE* q, int);
int dequeue(QUEUE* q);
void display(QUEUE* q);
int isEmpty(QUEUE* q);
QUEUE* createQueue();
void degreeCount (int degreCount[], GRAPH* graph, int *bas);
GRAPH* create_adjList (GRAPH* graph, char* line);
GRAPH* calculateInDegree(GRAPH* graph, int degreCount []);
void print_graph (GRAPH* graph);
void DFS(GRAPH* graph, int vertex, int *visited);

int main()
{
	int visited[12][12]= {0};
	int i, j=0, adj[12]={0}, degreCount[12], sonuc;
	GRAPH *graph = readFileAndCreateGraph();
	GRAPH* g=readFileAndCreateGraph();
	print_graph(graph);
	g->visited = malloc(g->numVertices * sizeof(int));
	for (i = 0; i < 12; i++) {
		g->visited[i] = 0;
	}
	for(i=0;i<g->numVertices; i++){
		DFS(g, i, visited[i]);
	}
	
	for(i=0;i<g->numVertices; i++){
		for(j=0;j<g->numVertices; j++){
			adj[j]+=visited[i][j];
		}
	}
	
	printf("Normal mod icin 1, Detay mod icin 2'ye basiniz: \n");
	scanf("%d", &sonuc);
	if(sonuc==1) {
		int X, Y;
		graph=calculateInDegree(graph, degreCount);
		printf("X degerini giriniz\n");
		scanf("%d", &X);
		printf("Y degerini giriniz\n");
		scanf("%d", &Y);
		for (i=0;i<graph->numVertices; i++){
			if(adj[i]>=Y && degreCount[i]>=X){
				printf("\nvertex: %d-->isim:%s-->dolayli baglanti sayisi:%d ",i+1, graph->adjLists[i]->name, adj[i]-1);
			}
		}
	}
	else if(sonuc==2){
		int a=0, X, Y;
		for (i=0;i<12;i++) {
			degreCount[i]=0;
		}
		degreeCount(degreCount, graph, &a); 
		printf("baslangic dugum sayilari\n");
		for(i=0;i<graph->numVertices; i++){
			printf("dugum: %d-->indegree: %d\n", i+1, degreCount[i]);
		}
	}
	
	
	
}

int dequeue(QUEUE* q) {
        
        if (q->front == q->rear) {
            q->front = -1;
            q->rear = -1;
        } else {
            q->front= (q->front + 1) % 12;
        }
        int item = q->front;
    	return item;
}

int isEmpty(QUEUE* q) {
    return q->front == -1 && q->rear == -1;
}

void enqueue(QUEUE* q, int item) {
	
        if (isEmpty(q)) {
            q->front = 0;
            q->rear = 0;
        } else {
            q->rear = (q->rear + 1) % 12;
        }
        q->rear = item;

}

GRAPH* calculateInDegree(GRAPH* graph, int degreCount [])
{
	int loop=1, k, i, m;
	printf("m degerini giriniz\n");
	scanf("%d", &m);
	while(loop==1){
		loop=0;
		int a=0;
		for(i=0; i<12;i++) {
			degreCount[i]=0;
		}
		if (graph->numVertices>0) {
			degreeCount(degreCount, graph, &a);
		}	
		k=0;
		for(i=0;i<graph->numVertices; i++) {
			if(degreCount[graph->adjLists[k]->vertex-1]<m) {
			graph=remove_vertex(graph, k+1);
			k--;
			loop=1;
			}
			k++;
		}
	}
	return graph;
}

void degreeCount(int degreCount [], GRAPH* graph, int *bas)
{
	int i, k=0, m=0;
	QUEUE* q = createQueue();
	graph->visited = malloc(12 * sizeof(int));
	for (i=0; i < 12; i++){
	graph->visited[i] = 0;
	}
	int numb=graph->adjLists[*bas]->vertex;
	graph->visited[numb-1]=1; 	
	enqueue(q, *bas);
	while(!isEmpty(q)){
		int currentVertex = dequeue(q);
		NODE* tmp;
		NODE* temp = graph->adjLists[currentVertex];
		tmp=temp;
		(*bas)++;
		while(temp!= NULL){
			m=0;
			int adjVertex = temp->vertex;
			if(graph->visited[adjVertex-1]==0){
				degreCount[adjVertex-1]++;
				graph->visited[adjVertex-1] = 1;
				while(graph->numVertices>m && graph->adjLists[m]->vertex!=adjVertex) {
					m++;
				}
				if (m=graph->numVertices) {
					return;
				}
				else{
					enqueue(q,m);
					tmp=tmp->next;
				}
			}
			else if(tmp->next!=NULL && tmp->next->vertex==adjVertex){
				degreCount[adjVertex-1]++;
				tmp=tmp->next;
			}
			temp=temp->next;
		}
	}
	if((*bas)!=graph->numVertices){
		degreeCount(degreCount,graph,bas);
	}
}

QUEUE* createQueue(){
	QUEUE* q=malloc(sizeof(struct queue));
	q->front=-1;
	q->rear=-1;	
}



GRAPH* remove_vertex(GRAPH* graph, int vertex)
{
	int i;
	int vtx=graph->adjLists[vertex-1]->vertex;
	while(graph->adjLists[vertex-1] != NULL){
		NODE* temp=graph->adjLists[vertex-1];
		graph->adjLists[vertex-1] = graph->adjLists[vertex-1]->next; 
		free(temp);
	}
	for (i=vertex-1; i < graph->numVertices; i++) {
		graph->adjLists[i]= graph->adjLists [i + 1];
	}
	
	graph->numVertices--;
	graph->adjLists = realloc(graph->adjLists, graph->numVertices * sizeof (NODE*));
	for (i=0;i<graph->numVertices; i++){
		NODE* temp=graph->adjLists[i];
		while(temp!=NULL){
			if(temp->next!= NULL && temp->next->vertex==vtx) {
				NODE* tmp=temp->next;
				temp->next=temp->next->next;
				free(tmp);
				graph->adjLists[i]=temp;
			}
			temp=temp->next;
		}
	}

	return graph;
}

void print_graph (GRAPH* graph)
{
	int i;	
	for(i=0; i<graph->numVertices; i++){
		printf("%d: %s %s ", graph->adjLists[i]->vertex, graph->adjLists[i]->name, graph->adjLists[i]->surname);
		NODE* current = graph->adjLists[i]->next;
		while (current!=NULL) {
			printf("%d: %s %s", current->vertex, current->name, current->surname);
			current = current->next;
		}
		printf("\n");
	}
}



GRAPH* create_adjList(GRAPH* graph, char* line)
{
	NODE *temp = (NODE*)malloc(sizeof(NODE));
	char* column= strtok(line, ",");
	int x = atoi(column);
	temp->vertex=x;
	column = strtok(NULL, ",");
	strcpy(temp->name,column);
	column = strtok(NULL, ",");
	strcpy(temp->surname,column);
	graph->adjLists[x-1]=temp;
	graph->adjLists[x-1]->next=NULL;
	graph = realloc(graph, sizeof(NODE)*(x+1));
	graph->adjLists= realloc(graph->adjLists, sizeof(NODE*)*(x+1));
	graph->adjLists[x] = realloc(graph->adjLists, sizeof(NODE*)*(x+1));
	return graph;
}




void add_edge(GRAPH* graph, int s, int d)
{
	NODE* new_node = malloc(sizeof(NODE));
	strcpy(new_node->name, graph->adjLists[d]->name);
 	strcpy(new_node->surname, graph->adjLists[d]->surname);
	new_node->vertex=d+1;
	if (new_node) {
		new_node->next = graph->adjLists[s]->next;
		graph->adjLists[s]->next = new_node;
	}
}
 

void DFS(GRAPH* graph, int vertex, int *visited)
{
	NODE* adjList = graph->adjLists [vertex];
	NODE* temp = adjList;
	visited[vertex] = 1;
	while (temp != NULL) {
		int connectedVertex = temp->vertex;
		if (visited[connectedVertex-1]==0){
			DFS(graph, connectedVertex-1, visited);
		}
		temp =temp->next;
	}
}


GRAPH* readFileAndCreateGraph()
{
	int i=0, count=0, k=0, m=2;
	char line[256];
	FILE *fp;
	fp = fopen("socialNET. txt", "r");
	if(fp==NULL){
		printf("Not found");
		return NULL;
	}
	
	GRAPH *graph = malloc(sizeof(GRAPH));
	graph->adjLists=malloc(sizeof(NODE*));	
	graph->adjLists[0] = malloc(sizeof(NODE*));
	
	while(fgets(line, sizeof(line), fp) != NULL)
	{
		if(count%2==0) {
			graph=create_adjList(graph, line);
		}
		count++;

	}
	count=count/2;
	
	graph->numVertices=count; 
	rewind(fp);
	
	
	while(fgets(line, sizeof(line), fp) != NULL){
		if (k%2!=0) {
			char* column=strtok(line, ",");
			
			while(column!=NULL){
				int ato=atoi(column);
				add_edge(graph, (k/2), ato-1);
				column = strtok(NULL, ",");
			}	
		}
		k++;	
	}
	
	return graph;
	
}

