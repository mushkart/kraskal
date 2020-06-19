#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdio.h>

#include "Source.h"


typedef struct GRAPH {
	int** table;
	int v_num;
	int* e_values;
}Graph;

// Сортировка массива с величинами ребер по возрастанию
int* Insertion_Sort(int* arr, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (arr[i] < arr[j]) {
				int t = arr[i];
				arr[i] = arr[j];
				arr[j] = t;
			}
		}
	}

	return arr;
}

// Проверка на наличие эдемента в динамическом массиве размера V_NUM
int In(int* arr, int l, int x) {
	for (int i = 1; i < l; i++) {
		if (arr[i] == x) {
			return 1;
		}
	}
	return 0;
}

// Функция создает граф по веденным данным 
struct GRAPH Data_Input() {

	// Точки
	printf("Insert the number of graph dots\n");
	int v_num;
	scanf("%d", &v_num);
	printf("\n");

	// Таблица графа (пока с нулями)
	int** g = (int**)malloc(v_num * sizeof(int*));
	for (int i = 0; i < v_num; i++) {
		g[i] = (int*)malloc(v_num * sizeof(int));
		for (int j = 0; j < v_num; j++) {
			g[i][j] = 0;
		}
	}

	// Ребра
	printf("Insert the number of graph lines\n");
	int r_num;
	scanf("%d", &r_num);
	printf("\n");
	int* values = (int*)malloc(r_num * sizeof(int));

	// Заполнение таблицы графа и массива с ребрами
	for (int i = 0; i < r_num; i++) {
		int value, v1, v2;
		scanf("%d %d %d", &v1, &v2, &value);
		g[v1][v2] = value;
		g[v2][v1] = value;
		values[i] = value;
	}

	// Создание структуры графа
	Graph graph;
	graph.table = g;
	graph.v_num = v_num;
	graph.e_values = Insertion_Sort(values, r_num);

	printf("\n");

	return graph;

	free(g);
}

// Функция определяет, образуется ли в остовом дереве цикл если провести ребро s---f
int If_Cycle(Graph tree, int s, int f, int* used) {
	used[0]++;
	used[used[0]] = s;

	for (int nb = 0; nb < tree.v_num; nb++) {
		if (tree.table[s][nb] != 0) {
			if (tree.table[nb][f] != 0) {
				return 1;
			}
			if (In(used, tree.v_num, nb)==0) {
				return If_Cycle(tree, nb, f, used);
			}
		}
	}

	return 0;
}
 