#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int get_neighboors_qty(bool* point);
void print_matrix(bool** matrix);
bool** generate_matrix(size_t m, size_t n);
void free_subptr(void** data);
void field_input(bool** data, size_t m, size_t n);
void field_output(bool** data, size_t m, size_t n);

int main(void) {
    size_t n, m;
    scanf("%ld %ld", &m, &n);
    bool** matrix = generate_matrix(m, n);
    field_input(matrix, m, n);
    field_output(matrix, m, n);
    free_subptr((void**)matrix);
    free(matrix);
    return 0;
}

bool** generate_matrix(size_t m, size_t n) {
    bool** columns = (bool**)malloc(m * n);
    for (int i = 0; i < n; i++) {
        columns[i] = (bool*)malloc(m);
    }
    return columns;
}

void free_subptr(void** data) {
    size_t size = sizeof(data) / sizeof(data[0]);
    for (int i = 0; i < size; i++) {
        free(data[i]);
    }
}

void field_input(bool** data, size_t m, size_t n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &data[i][j]);
        }
    }
}

void field_output(bool** data, size_t m, size_t n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", data[i][j]);
        }
        printf("\n");
    }
}
