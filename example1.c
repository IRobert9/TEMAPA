#include <stdio.h>
#include <stdlib.h>

// Structura pentru nodul grafului
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Structura pentru graful în sine
typedef struct Graph {
    int v;
    int* vis;
    Node** alst;
} Graph;

// Structura pentru stivă
typedef struct Stack {
    int t;
    int scap;
    int* arr;
} Stack;

// Funcție pentru crearea unui nod
Node* create_node(int v) {
    Node* nn = malloc(sizeof(Node));
    if (nn == NULL) {
        printf("Eroare la alocarea memoriei pentru nod.\n");
        exit(EXIT_FAILURE);
    }
    nn->data = v;
    nn->next = NULL;
    return nn;
}

// Funcție pentru adăugarea unei muchii între două noduri
void add_edge(Graph* g, int src, int dest) {
    Node* nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;
    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

// Funcție pentru crearea grafului
Graph* create_graph(int v) {
    int i;
    Graph* g = malloc(sizeof(Graph));
    if (g == NULL) {
        printf("Eroare la alocarea memoriei pentru graf.\n");
        exit(EXIT_FAILURE);
    }
    g->v = v;
    g->alst = malloc(v * sizeof(Node*));
    g->vis = malloc(v * sizeof(int));
    if (g->alst == NULL || g->vis == NULL) {
        printf("Eroare la alocarea memoriei pentru lista de adiacență sau vectorul de vizitare.\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < v; i++) {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }
    return g;
}

// Funcție pentru crearea unei stive
Stack* create_stack(int scap) {
    Stack* s = malloc(sizeof(Stack));
    if (s == NULL) {
        printf("Eroare la alocarea memoriei pentru stivă.\n");
        exit(EXIT_FAILURE);
    }
    s->arr = malloc(scap * sizeof(int));
    if (s->arr == NULL) {
        printf("Eroare la alocarea memoriei pentru vectorul din stivă.\n");
        exit(EXIT_FAILURE);
    }
    s->t = -1;
    s->scap = scap;
    return s;
}

// Funcție pentru adăugarea unui element în stivă
void push(int pshd, Stack* s) {
    s->t++;
    s->arr[s->t] = pshd;
}

// Funcție pentru parcurgerea DFS a grafului
void DFS(Graph* g, Stack* s, int v_nr) {
    Node* adj_list = g->alst[v_nr];
    Node* aux = adj_list;
    g->vis[v_nr] = 1;
    printf("%d ", v_nr);
    push(v_nr, s);
    while (aux != NULL) {
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0)
            DFS(g, s, con_ver);
        aux = aux->next;
    }
}

// Funcție pentru introducerea muchiilor în graf
void insert_edges(Graph* g, int edg_nr, int nrv) {
    int src, dest, i;
    printf("Adauga %d muchii (de la 1 la %d)\n", edg_nr, nrv);
    for (i = 0; i < edg_nr; i++) {
        scanf("%d %d", &src, &dest);
        add_edge(g, src, dest);
    }
}

// Funcție pentru inițializarea vectorului de vizitare cu 0
void wipe(Graph* g, int nrv) {
    for (int i = 0; i < nrv; i++) {
        g->vis[i] = 0;
    }
}

// Funcție pentru verificarea echivalenței a două aranjamente
void can_be(Graph* g, int nrv, Stack* s1, Stack* s2) {
    int i;
    int ans = 1; // Presupunem că aranjamentele sunt echivalente până când găsim o contradicție
    if (s1->t != s2->t) {
        ans = 0; // Numărul de elemente din stive este diferit, deci aranjamentele nu pot fi echivalente
    } else {
        for (i = 0; i <= s1->t && ans; i++) {
            if (s1->arr[i] != s2->arr[i]) {
                ans = 0; // Am găsit o contradicție între elementele din stive, deci aranjamentele nu pot fi echivalente
            }
        }
    }

    if (ans) {
        printf("Cele două aranjamente sunt echivalente.\n");
    } else {
        printf("Cele două aranjamente nu sunt echivalente.\n");
    }
}

int main() {
    int nrv, edg_nr;

    printf("Cate noduri are graful? ");
    scanf("%d", &nrv);

    printf("Cate muchii are graful? ");
    scanf("%d", &edg_nr);

    // Crearea grafului
    Graph* g = create_graph(nrv);

    // Crearea stivelor pentru parcurgerea DFS
    Stack* s1 = create_stack(2 * nrv);
    Stack* s2 = create_stack(2 * nrv);

    // Introducerea muchiilor în graf
    insert_edges(g, edg_nr, nrv);

    // Afișarea parcurgerii DFS a grafului
    printf("Parcurgerea DFS a grafului este: ");
    DFS(g, s1, 0); // Parcurgerea începe de la nodul 0, poți alege alt nod dacă dorești
    printf("\n");

    // Testarea funcționalității de verificare a echivalenței a două aranjamente
    char choice;
    printf("Doresti sa testezi functionalitatea de verificare a echivalentei a doua aranjamente? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        can_be(g, nrv, s1, s2);
    }

    // Eliberarea memoriei
    free(g->vis);
    free(g->alst);
    free(g);
    free(s1->arr);
    free(s1);
    free(s2->arr);
    free(s2);

    return 0;
}