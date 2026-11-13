// A. Ruta hasta el empleado
// Idea: el arbol se recorre con un BFS desde el director (1) guardando quien
// fue el jefe por el que llegamos a cada empleado. Despues subimos de t hacia
// el 1 usando esos jefes y volteamos la lista.

#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, t;
    cin >> n >> t;

    vector< vector<int> > vecinos(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        vecinos[u].push_back(v);
        vecinos[v].push_back(u);
    }

    vector<int> jefe(n + 1, 0);
    vector<bool> visitado(n + 1, false);

    // BFS con un vector usado como cola (no hace falta nada mas)
    vector<int> cola;
    cola.push_back(1);
    visitado[1] = true;

    for (size_t i = 0; i < cola.size(); i++) {
        int u = cola[i];
        for (size_t k = 0; k < vecinos[u].size(); k++) {
            int v = vecinos[u][k];
            if (!visitado[v]) {
                visitado[v] = true;
                jefe[v] = u;      // a v llegamos desde u
                cola.push_back(v);
            }
        }
    }

    // subimos de t hasta el director
    vector<int> camino;
    int actual = t;
    while (actual != 0) {
        camino.push_back(actual);
        actual = jefe[actual];   // jefe[1] == 0, ahi se corta
    }

    cout << camino.size() << "\n";
    for (int i = (int)camino.size() - 1; i >= 0; i--) {
        cout << camino[i];
        if (i > 0) cout << " ";
    }
    cout << "\n";

    return 0;
}
