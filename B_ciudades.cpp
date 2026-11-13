// B. Ciudades atendidas (ida y regreso desde la ciudad 1)
// Idea: Dijkstra dos veces. Una sobre el grafo normal para el tiempo de ida
// (1 -> i) y otra sobre el grafo con las carreteras al reves para el tiempo
// de regreso (i -> 1). Una ciudad se atiende si los dos tiempos existen.

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef long long ll;
const ll INF = 4000000000000000000LL;

struct Arista {
    int destino;
    ll peso;
};

// Dijkstra clasico con cola de prioridad (la cola solo ordena, el algoritmo
// esta escrito a mano)
vector<ll> dijkstra(int n, const vector< vector<Arista> >& g, int origen) {
    vector<ll> dist(n + 1, INF);
    dist[origen] = 0;

    priority_queue< pair<ll,int>, vector< pair<ll,int> >, greater< pair<ll,int> > > pq;
    pq.push(make_pair(0LL, origen));

    while (!pq.empty()) {
        ll d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;   // entrada vieja

        for (size_t k = 0; k < g[u].size(); k++) {
            int v = g[u][k].destino;
            ll nueva = d + g[u][k].peso;
            if (nueva < dist[v]) {
                dist[v] = nueva;
                pq.push(make_pair(nueva, v));
            }
        }
    }
    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector< vector<Arista> > normal(n + 1);
    vector< vector<Arista> > alReves(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        Arista a;
        a.destino = v; a.peso = w;
        normal[u].push_back(a);
        a.destino = u; a.peso = w;
        alReves[v].push_back(a);
    }

    vector<ll> ida = dijkstra(n, normal, 1);
    vector<ll> regreso = dijkstra(n, alReves, 1);

    ll ciudades = 0;
    ll total = 0;
    for (int i = 1; i <= n; i++) {
        if (ida[i] < INF && regreso[i] < INF) {
            ciudades++;
            total += ida[i] + regreso[i];
        }
    }

    cout << ciudades << " " << total << "\n";
    return 0;
}
