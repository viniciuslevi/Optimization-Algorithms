#include <vector>
#include <iostream>
#include <iomanip>
#include <queue>
#include <unordered_set>

using namespace std;
int counter = 0;

vector<vector<int>> idealVetor = {  { 0, 1, 2 },
                                    { 3, 4, 5 },
                                    { 6, 7, 8 } };
                            
struct NO {
    vector<vector<int>> vetor;
    NO* noPai = nullptr;
    int zeroCol;
    int zeroRow;
};

// Função de hash para vector<vector<int>>
struct VectorHash {
    size_t operator()(const vector<vector<int>>& v) const {
        size_t hash = 0;
        for (const auto& row : v) {
            for (int num : row) {
                hash ^= std::hash<int>()(num) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
            }
        }
        return hash;
    }
};

void printSolution(NO*);
void printMatriz(vector<vector<int>>);

// Função para verificar se a matriz está ordenada
bool verify(const std::vector<std::vector<int>>& matriz) {
    return matriz == idealVetor;
}

// Função para trocar elementos e gerar um novo nó
NO* swapElements(NO* no, int numRow, int numCol) {
    NO* newNo = new NO();  // Alocar memória para o novo nó
    newNo->vetor = no->vetor;
    newNo->noPai = no;
    
    // Trocar os elementos
    newNo->vetor[no->zeroRow][no->zeroCol] = no->vetor[numRow][numCol];
    newNo->vetor[numRow][numCol] = 0; // O zero ocupa a nova posição

    newNo->zeroRow = numRow;
    newNo->zeroCol = numCol;    

    return newNo;
}

NO* solve(NO* no) {

    unordered_set<vector<vector<int>>, VectorHash> set;
    queue<NO*> q;

    q.push(no);
    set.emplace(no->vetor).second;
            
            
    int contador = 0;

    while (!q.empty() && counter++ < 1000000) {
        
        NO* qNo = q.front();

        q.pop();

        if (verify(qNo->vetor)) {
                
            return qNo;
        }

        NO* aux;
        
        // Para cima
        if (qNo->zeroRow - 1 >= 0) {
            aux = swapElements(qNo, qNo->zeroRow - 1, qNo->zeroCol);

            if(set.insert(aux->vetor).second){
                q.push(aux);
                 
                
            }
        }

        // Para baixo
        if (qNo->zeroRow + 1 < 3) {
            aux = swapElements(qNo, qNo->zeroRow + 1, qNo->zeroCol);
            
            if(set.insert(aux->vetor).second)
                q.push(aux);
            
        }

        // Para direita
        if (qNo->zeroCol + 1 < 3) {
            aux = swapElements(qNo, qNo->zeroRow, qNo->zeroCol + 1);
            
            if(set.insert(aux->vetor).second)
                q.push(aux);
        }

        // Para a esquerda
        if (qNo->zeroCol - 1 >= 0) {
            aux = swapElements(qNo, qNo->zeroRow, qNo->zeroCol - 1);
            if(set.insert(aux->vetor).second)
                q.push(aux);
        }
    }   

    set.clear();
    return nullptr;  // Caso não encontre solução, retorna nullptr
}

void printMatriz(vector<vector<int>> vetor){
    for (auto linha : vetor) {
        for (int elemento : linha) {
            std::cout << std::setw(4) << elemento; // Ajusta a largura de cada elemento para 4 caracteres
        }
        cout << '\n';
    }
        cout <<"\n\n";
}
// Função para imprimir a solução
void printSolution(NO* no) {
    NO* aux = no;
    while(aux != nullptr){
        printMatriz(aux->vetor);
        aux = aux->noPai;
    }
}
pair<int, int> findZero(vector<vector<int>> matriz){
    for(int i=0;i<matriz.size();i++){
        for(int j=0;j<matriz[i].size();j++){
            if(matriz[i][j] == 0){
                return make_pair(i,j);
            }
        }
    }
}
int main() {
    
    //edite esta matriz

    vector<vector<int>> vec = { { 3, 1, 7 },
                                { 6, 4, 2 },
                                { 5, 8, 0 } };

    NO* no = new NO();
    no->noPai = nullptr;
    no->vetor = vec;
    no->zeroRow = findZero(vec).first;
    no->zeroCol = findZero(vec).second;

    NO* solution = solve(no);
     cout << counter <<endl;

    //cout << "printando o caminho\n\n"; 
        
    printSolution(solution);


    return 0;
}
