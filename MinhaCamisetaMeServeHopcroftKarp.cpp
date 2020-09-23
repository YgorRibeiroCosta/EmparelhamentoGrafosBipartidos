#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

string tamanhos[] = {"XXL", "XL", "L", "M", "S", "XS"};
int n, m, dist[100], emp[100], cnt, oo = 0x3f3f3f3f;

vector<vector<int> > grafo;
vector<int> ladoA;
map<string, vector<int> > valoresCamisetas;

void rotular(){
    cnt = 1;

    for(int i=0;i<6;i++){
        for(int j=0;j<n/6;j++){
            valoresCamisetas[tamanhos[i]].push_back(cnt++);
        }
    }

}

bool bfs(){

    queue<int> fila;

    for(int i=0;i<ladoA.size();i++){
        int v = ladoA[i];
        if(emp[v] == v){ /// v é livre
            dist[v] = 0;
            fila.push(v);
        }else{
            dist[v] = oo;
        }
    }

    int k = oo;

    while(!fila.empty()){
        int u = fila.front();
        fila.pop();

        if(dist[u] < k){

            for(int i=0;i<grafo[u].size();i++){
                int v = grafo[u][i];
                if(emp[v] == v && k == oo) k = dist[u] + 1;
                else if(dist[emp[v]] == oo){
                    dist[emp[v]] = dist[u] + 1;
                    fila.push(emp[v]);
                }
            }

        }

    }

    return k != oo;

}

bool dfs(int u){

    for(int i=0;i<grafo[u].size();i++){
        int v = grafo[u][i];
        if(emp[v] == v || (dist[u] + 1 == dist[emp[v]] && dfs(emp[v]))){
            emp[v] = u, emp[u] = v;
            return true;
        }
    }

    return false;

}

int hopcroft_karp(){
    for(int i=0;i<=cnt;i++) emp[i] = i;

    int emparelhamento_maximo = 0;

    while(bfs()){
        for(int i=0;i<ladoA.size();i++){
            int v = ladoA[i];
            if(dist[v] == 0){
                if(dfs(v)) emparelhamento_maximo++;
            }
        }
    }

    return emparelhamento_maximo;

}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&m);
        grafo.assign(100, vector<int> ());
        ladoA.clear();
        valoresCamisetas.clear();
        rotular();

        for(int i=0;i<m;i++){
            string a, b;
            cin >> a >> b;
            for(int j=0;j<valoresCamisetas[a].size();j++){
                grafo[cnt].push_back(valoresCamisetas[a][j]);
                grafo[valoresCamisetas[a][j]].push_back(cnt);
            }
            for(int j=0;j<valoresCamisetas[b].size();j++){
                grafo[cnt].push_back(valoresCamisetas[b][j]);
                grafo[valoresCamisetas[b][j]].push_back(cnt);
            }
            ladoA.push_back(cnt);
            cnt++;
        }

        if(hopcroft_karp() == m) printf("YES\n");
        else printf("NO\n");
    }



    return 0;
}
