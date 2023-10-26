#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<stack>
#include<time.h>
#include<Windows.h>
using namespace std;

stack<int> s;

struct spisok_soed {
	int vershina;
	struct spisok_soed* next;
};


struct spisok_soed* creation_element(int nomber) {

	struct spisok_soed* p = NULL;

	if ((p = (spisok_soed*)malloc(sizeof(struct spisok_soed))) == NULL) // выделяем память под новый элемент списка
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}

	p->vershina = nomber;
	p->next = NULL;

	return p;


}

struct spisok_soed* spis;

void creation_spisok(int** M, int size) {
	struct spisok_soed* q, *save = NULL;
	for (int i = 0; i < size; i++) {
		spis[i].next = NULL;
		spis[i].vershina = i;
		for (int j = 0; j < size; j++) {
			if (M[i][j] == 1) {
				q = creation_element(j);

				if (spis[i].next == NULL) {
					spis[i].next = q;
					save = q;
				}
				else {
					save->next = q;
					save = q;
				}
			}
		}
	}
}

void review(int size) {
	struct spisok_soed* save;
	cout << "\n";
	for (int i = 0; i < size; i++) {
		save = spis[i].next;
		cout << "[" << spis[i].vershina << "]";
		while (save != NULL) {
			cout << " -> " << save->vershina;
			save = save->next;
		}
		cout << "\n";
	}
	cout << "\n";

}

void DFS(int v, int size, int** g, int* NUM)
{
	cout << v  << " ";
	NUM[v] = 1;
	for (int i = 0; i < size; i++) {
		if (g[v][i] == 1 && NUM[i] == 0) {
			DFS(i, size, g, NUM);
		}
	}
}

void DFS_spisok(int v, int size, int* NUM)
{
	struct spisok_soed* save = spis[v].next;
	cout << v << " ";
	NUM[v] = 1;
	while (save != NULL) {
		if (NUM[save->vershina] == 0){ 
			
			DFS_spisok(save->vershina, size,NUM );
		}
		save = save->next;
	}

}

void DFS_stec(int v, int size, int** g, bool* NUM) {

	
	NUM[v] = TRUE;
	s.push(v);
	while (!s.empty()) {
		v = s.top();
		s.pop();
		cout << v  << " ";
		for (int i = size; i > 0 ; i--) {
			if (g[v][i] == 1 && !NUM[i]) {
				NUM[i] = TRUE;
				s.push(i);
			}
		}
		
	}

}


int main() {
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	int** G, size, * NUM, *NUM_spisok, *connect_graf, vershina ;
	bool go = TRUE;
	bool* NUM_ne_rekurs;
	cout << " Матрица смежности \n \n Введите количество вершин графа: ";
	cin >> size;
	
	spis = new struct spisok_soed[size];
	connect_graf = new int[size];
	G = new int* [size]; // создаём двумерный массив 
	NUM = new int[size];
	NUM_spisok = new int[size];
	NUM_ne_rekurs = new bool[size];
	for (int i = 0; i < size; i++) {
		G[i] = new int[size];
		NUM[i] = 0;
		NUM_spisok[i] = 0;
		connect_graf[i] = 0;
		NUM_ne_rekurs[i] = FALSE;
	}


	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			if (i == j) { G[i][j] = 0; }
			else {
				G[i][j] = rand() % 2;
				G[j][i] = G[i][j];
			}
		}

	}


	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (G[i][j] == 1) { connect_graf[i]++; }
			cout << G[i][j] << " ";
		}
		cout << "\n";
	}

	cout << "\nВведите вершину с которой хотите начать обход: ";
	cin >> vershina;
	
	cout << "\nОбход в глубину списка\n";
	
	DFS(vershina, size, G, NUM);
	creation_spisok(G, size);
	review(size);
	
	cout << "\nОбход в глубину матрицы смежности\n";

	DFS_spisok(vershina, size, NUM_spisok);
	cout << "\n\nОбход в глубину без рекурсий\n";
	DFS_stec(vershina, size, G, NUM_ne_rekurs);
	cout << "\n";

	system("pause");
	return 0;
}
