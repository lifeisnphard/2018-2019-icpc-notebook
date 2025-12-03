/*
Ternary search to find out the numerical constant that gives the maximal result in a dijkstra algorithm.
*/
#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-12;
const int N = 1e3 + 10, M = 1e4 + 10;

vector<pair<int, int> > adj[N];
pair<int, int> edge[M];
double dist[N];

double dijkstra(int n, double t){
    dist[1] = 0;
    for(int i = 2; i <= n; i++){
        dist[i] = 1e12;
    }
    set<pair<double, int> > s;
    s.insert(make_pair(0, 1));
    while(!s.empty()){
        pair<double, int> tmp = *s.begin(); s.erase(s.begin());
        double d = tmp.first; int u = tmp.second;

        if(dist[u] < d) continue;

        for(int i = 0; i < adj[u].size(); i++){
            int v = adj[u][i].first, e = adj[u][i].second;
            int a = edge[e].first, b = edge[e].second;
            double cost = a*t + b;

            if(d + cost < dist[v]){
                dist[v] = d + cost;
                s.insert(make_pair(dist[v], v));
            }
        }
    }
    return dist[n];
}

int main(){
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);

    int n, m;
    scanf("%d %d", &n, &m);
	for(int i = 0, x, y, a, b; i < m; i++){
		scanf("%d %d %d %d", &x, &y, &a, &b);
		adj[x].push_back(make_pair(y, i));
		adj[y].push_back(make_pair(x, i));
		edge[i] = make_pair(a, b);
	}
	double l = 0, r = 24*60;
	for(int k = 0; k < 100; k++){ // finding maximum in a monotonic function
		double len = (r - l)/3.0;
		double m1 = l + len, m2 = r - len;
		double t1 = dijkstra(n, m1), t2 = dijkstra(n, m2);
		if(t1 > t2){
			r = m2;
		}else{
			l = m1;
		}
	}
	printf("%.5lf\n", dijkstra(n, l));
    return 0;
}
