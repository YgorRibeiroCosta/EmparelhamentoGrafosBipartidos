#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<vector<int> > grafo;

int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

int getCelula(int i, int j, int m){
    i--;
    return (i * m) + j;
}

int cores[100 * 100 + 5], seen[100 * 100 + 5], emp[100 * 100 + 5];

void colorirVertices(int u, int cor){
    cores[u] = cor;

    for(int i=0;i<grafo[u].size();i++){
        int v = grafo[u][i];

        if(cores[v] == -1){
            colorirVertices(v, cor ^ 1);
        }

    }
}

bool acha_caminho_aumento(int u) {
	for (int i = 0; i <grafo[u].size(); i++) {
        int v = grafo[u][i];
		if(seen[v]) continue;
		seen[v] = true;
		if (emp[v] == v) {
			emp[u] = v;
			emp[v] = u;
			return true;
		}
		if (acha_caminho_aumento(emp[v])) {
			emp[u] = v;
			emp[v] = u;
			return true;
		}

	}
	return false;
}


int main(){
    int n, m;
    while(scanf("%d%d",&n,&m)){
        if(!n && !m) break;
        int k;
        scanf("%d",&k);
        int vis[105][105];
        memset(vis, 0, sizeof vis);
        memset(cores, -1, sizeof cores);

        while(k--){
            int a, b;
            scanf("%d%d",&a,&b);
            vis[a][b] = 1;
        }

        grafo.assign((n*m)+5, vector<int> ());

        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(vis[i][j]) continue;

                for(int k=0;k<4;k++){
                    int x = i + dx[k], y = j + dy[k];
                    if(x <= 0 || x > n || y <= 0 || y > m || vis[x][y]) continue;
                    int a = getCelula(i, j, m), b = getCelula(x, y, m);
                    grafo[a].push_back(b);
                    grafo[b].push_back(a);
                    
                }

            }
        }



        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(vis[i][j]) continue;

                if(cores[getCelula(i, j, m)] == -1) colorirVertices(getCelula(i, j, m), 0);

            }
        }

        int emparelhamento_maximo = 0;

        for(int i=1;i<=n*m;i++) emp[i] = i;

        for(int i=1;i<=n*m;i++){
            if(cores[i] == 0){
                if(emp[i] == i) { //se i e livre
                    memset(seen, 0, sizeof seen);
                    if(acha_caminho_aumento(i)){
                        emparelhamento_maximo++;
                    }
                }

            }
        }

        printf("%d\n", emparelhamento_maximo);




    }
    return 0;
}
