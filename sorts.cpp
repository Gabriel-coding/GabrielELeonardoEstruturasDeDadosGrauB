#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <vector>
using namespace std;
using namespace std::chrono;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<ll> vll;
#define pb push_back

// Bubble Sort 
void bubbleSort(vi& arr) {
    int n = arr.size(); 

    for (int i = n; i > 0; --i) {
        bool ordenado = true;
        for (int j = 1; j < i; ++j) {
            if (arr[j-1] > arr[j]) {
                ordenado = false;
                swap(arr[j-1], arr[j]);
            } 
        }
        if(ordenado){
            break;
        }
    } 
}

// Insertion Sort 
void insertionSort(vi& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        for (int j = i; j > 0 && arr[j-1] > arr[j]; --j) {
            swap(arr[j-1], arr[j]);
        }
    }
}

// Selection Sort
void selectionSort(vi& arr) {
    int n = arr.size();
    for (int i = 0; i < n; ++i) {
        int min = i;
        for (int j = i+1; j < n; ++j) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        swap(arr[i], arr[min]);
    }
}

// Heap Sort
void heapify(vi& arr, int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }
    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}


void heapSort(vi& arr) {
    int n = arr.size();

    for (int i = n/2 - 1; i >= 0; --i) {
        heapify(arr, n, i);
    }
    for (int i = n-1; i > 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Shell Sort 
void shellSort(vi& arr) {
    int n = arr.size();

 
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            int temp = arr[i];
            int j;
            
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// Merge Sort
void merge(vi& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vi L(n1);
    vi R(n2);
    
    for (int i = 0; i < n1; ++i) {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[m + 1 + j];
    }
    int i = 0;
    int j = 0;
    int k = l;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i++];
        } else {
            arr[k] = R[j++];
        }
        ++k;
    }
    
    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }
}


void mergeSortHelper(vi& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortHelper(arr, l, m);
        mergeSortHelper(arr, m+1, r);
        merge(arr, l, m, r);
        
    }
    
}

void mergeSort(vi& arr) {
    mergeSortHelper(arr, 0, arr.size()-1);
}

// Quick Sort
int partition(vi& arr, int low, int high) {
    int pivot = arr[low + (high-low)/2];
    int temp = arr[low];
    while (low != high) {
        if (temp < pivot) {
            swap(temp, arr[low++]);
        } else {
            swap(temp, arr[high--]);
        }
    }
    arr[low] = pivot;
    return low;
}

void sort(vi& arr, int low, int high) {
    if(low < high) {
        int p = partition(arr, low, high);
        sort(arr, low, p - 1);
        sort(arr, p + 1, high);
    }
}

void quickSort(vi& arr) {
    sort(arr, 0, arr.size()-1);
}

//Função para imprimir o tempo levado
void printTempo(ll temp, string sort, int c, int t) {
    cout << temp << " ns (" << sort << " c" << c << " t" << t << ")\n";
}

// Função para calcular a média
ll calcularMedia(const vll arr) {
    ll soma = 0;
    int r = 0;
    for (int i = 0; i < arr.size(); ++i) {
        soma += arr[i]/arr.size();
        r += arr[i] % arr.size();
    }
    r /= arr.size();
    return soma+r;
}

// Função para calcular o desvio padrão
ll calcularDesvioPadrao(const vll arr, ll media) {
    ll somaQuadradosDiferencas = 0;

    for (int i = 0; i < arr.size(); ++i) {
        somaQuadradosDiferencas += pow(arr[i] - media, 2);
    }

    ll variancia = somaQuadradosDiferencas / arr.size();
    return sqrt(variancia);
}

// Função para calcular a média sem os outliers
ll mediaSemOutlier(const vll arr) {
    ll media = calcularMedia(arr);
    ll desvPadr = calcularDesvioPadrao(arr, media);
    vll novoArr;
    for (int i = 0; i < arr.size(); ++i) {
        ll num = arr[i];
        if(media-desvPadr <= num && num <= media + desvPadr) {
            novoArr.pb(num);
        }
    }
    return calcularMedia(novoArr);
}

// Função que verifica se o array foi devidamente ordenado
bool verificaSeOrdenado(vi& arr) {
    for (int i = 0; i < arr.size() - 1;) {
        if (arr[i] > arr[++i]) {
            cout << "Erro: array não foi ordenado.\n";
            return false;
        }
    }
    return true;
} 

int main() {
    random_device rd;
    mt19937 gen(rd());
    
    // Tamanhos de array a serem testados
    vi tamanhos;
    for(int i = 7; i <= 16; ++i) {
        tamanhos.pb(1 << i);
    }
    
    // Número de execuções para cada cenário
    int repeticoes = 10;
    
    // Repetir tudo para cada cenário
    for (int cenario = 1; cenario <= 4; ++cenario) {
        // Repetir tudo para cada tamanho
        for (int t = 0; t < tamanhos.size(); ++t) {
            // Criar um array pra cada repeticao
            vector<vi> arrays;
            for (int r = 0; r < repeticoes; ++r) {
                vi arr;
                switch (cenario) {
                    case 1: // Array ordenado em ordem crescente
                        for (int i = 0; i < tamanhos[t]; ++i) {
                            arr.pb(i);
                        }
                        break;
                    case 2: // Array ordenado em ordem decrescente
                        for (int i = tamanhos[t]-1; i >= 0; --i) {
                            arr.pb(i);
                        }
                        break;
                    case 3: // Array aleatório sem valores repetidos
                        for (int i = 0; i < tamanhos[t]; ++i) {
                            arr.pb(i);
                        }
                        shuffle(arr.begin(), arr.end(), gen);
                        break;
                    case 4: // Array aleatório com valores repetidos
                        uniform_int_distribution<int> dist(0, tamanhos[t]);
                        for (int i = 0; i < tamanhos[t]; ++i) {
                            arr.pb(dist(gen));
                        }
                        break;
                }
                arrays.pb(arr);
            }
            
            // Executar cada algoritmo repetidas vezes
            vi array;
            
            vll bubbleTemp;
            for (int r = 0; r < repeticoes; ++r) {
                array = arrays[r];
                auto start = high_resolution_clock::now();
                bubbleSort(array);
                auto end = high_resolution_clock::now();
                bubbleTemp.pb(duration_cast<nanoseconds>(end - start).count());
                verificaSeOrdenado(array);               
            }
            printTempo(mediaSemOutlier(bubbleTemp), "bubble", cenario, tamanhos[t]);

            vll insertionTemp;
            for (int r = 0; r < repeticoes; ++r) {
                array = arrays[r];
                auto start = high_resolution_clock::now();
                insertionSort(array);
                auto end = high_resolution_clock::now();
                insertionTemp.pb(duration_cast<nanoseconds>(end - start).count());
                verificaSeOrdenado(array);              
            }
            printTempo(mediaSemOutlier(insertionTemp), "insertion", cenario, tamanhos[t]);
            
            vll selectionTemp;
            for (int r = 0; r < repeticoes; ++r) {
                array = arrays[r];
                auto start = high_resolution_clock::now();
                selectionSort(array);
                auto end = high_resolution_clock::now();
                selectionTemp.pb(duration_cast<nanoseconds>(end - start).count());
                verificaSeOrdenado(array);               
            }
            printTempo(mediaSemOutlier(selectionTemp), "selection", cenario, tamanhos[t]);
            
            vll heapTemp;
            for (int r = 0; r < repeticoes; ++r) {
                array = arrays[r];
                auto start = high_resolution_clock::now();
                heapSort(array);
                auto end = high_resolution_clock::now();
                heapTemp.pb(duration_cast<nanoseconds>(end - start).count());
                verificaSeOrdenado(array);               
            }
            printTempo(mediaSemOutlier(heapTemp), "heap", cenario, tamanhos[t]);
            
            vll shellTemp;
            for (int r = 0; r < repeticoes; ++r) {
                array = arrays[r];
                auto start = high_resolution_clock::now();
                shellSort(array);
                auto end = high_resolution_clock::now();
                shellTemp.pb(duration_cast<nanoseconds>(end - start).count());
                verificaSeOrdenado(array);              
            }
            printTempo(mediaSemOutlier(shellTemp), "shell", cenario, tamanhos[t]);
            
            vll mergeTemp;
            int c = 1;
            for (int r = 0; r < repeticoes; ++r) {
                array = arrays[r];
                auto start = high_resolution_clock::now();
                mergeSort(array);
                auto end = high_resolution_clock::now();
                mergeTemp.pb(duration_cast<nanoseconds>(end - start).count());
                verificaSeOrdenado(array);
            }
            printTempo(mediaSemOutlier(mergeTemp), "merge", cenario, tamanhos[t]);
            
            vll quickTemp;
            for (int r = 0; r < repeticoes; ++r) {
                array = arrays[r];
                auto start = high_resolution_clock::now();
                quickSort(array);
                auto end = high_resolution_clock::now();
                quickTemp.pb(duration_cast<nanoseconds>(end - start).count());
                verificaSeOrdenado(array);              
            }
            printTempo(mediaSemOutlier(quickTemp), "quick", cenario, tamanhos[t]);
        }
    }
    return 0;
}