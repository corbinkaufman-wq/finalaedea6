// C. Lider de la red
// Idea: si existe algun lider, el ultimo servidor en terminar un DFS sobre
// todo el grafo es candidato a lider. Se revisa con un BFS si ese candidato
// llega a todos. Si llega, los lideres son exactamente los servidores que
// pueden llegar al candidato (se cuentan con un BFS por los enlaces al
// reves). Si no llega, no hay ningun lider.

#include <iostream>
#include <vector>
using namespace std;

// BFS simple: cuantos servidores se alcanzan desde "origen" en el grafo g
int cuantosAlcanza(int n, const vector< vector<int> >& g, int origen) {
    vector<bool> visto(n + 1, false);
    vector<int> cola;
    cola.push_back(origen);
    visto[origen] = true;

    for (size_t i = 0; i < cola.size(); i++) {
        int u = cola[i];
        for (size_t k = 0; k < g[u].size(); k++) {
            int v = g[u][k];
            if (!visto[v]) {
                visto[v] = true;
                cola.push_back(v);
            }
        }
    }
    return (int)cola.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector< vector<int> > normal(n + 1);
    vector< vector<int> > alReves(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        normal[u].push_back(v);
        alReves[v].push_back(u);
    }

    // DFS iterativo (sin recursion, para que no se desborde la pila)
    // guardando el orden en que los servidores van terminando
    vector<bool> visto(n + 1, false);
    vector<int> siguiente(n + 1, 0);   // por donde va cada servidor
    vector<int> orden;                 // orden de terminacion

    for (int i = 1; i <= n; i++) {
        if (visto[i]) continue;
        vector<int> pila;
        pila.push_back(i);
        visto[i] = true;

        while (!pila.empty()) {
            int u = pila.back();
            if (siguiente[u] < (int)normal[u].size()) {
                int v = normal[u][siguiente[u]];
                siguiente[u]++;
                if (!visto[v]) {
                    visto[v] = true;
                    pila.push_back(v);
                }
            } else {
                orden.push_back(u);   // u ya termino
                pila.pop_back();
            }
        }
    }

    int candidato = orden.back();   // el ultimo en terminar

    if (cuantosAlcanza(n, normal, candidato) != n) {
        cout << 0 << "\n";          // ni el candidato llega a todos
    } else {
        // los lideres son los que pueden llegar al candidato
        cout << cuantosAlcanza(n, alReves, candidato) << "\n";
    }

    return 0;
}
