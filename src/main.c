#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int get_neighboors_qty(bool** data, size_t m, size_t n, int i_i, int j_i);
bool** generate_matrix(size_t m, size_t n);
void free_subptr(void** data, size_t n);

void field_input(bool** data, size_t m, size_t n);
void field_output(bool** data, size_t m, size_t n);
void field_update(bool** data, bool** data2, size_t m, size_t n);

int main(void) {
    size_t n, m;
    scanf("%ld %ld", &m, &n);
    bool** field_1 = generate_matrix(m, n);
    bool** field_2 = generate_matrix(m, n);
    field_input(field_1, m, n);
    int steps = 0;
    scanf("%d", &steps);
    for(int i = 0; i <= steps; i++) {
        printf("\n---\nframe: %d\n---\n", i);
        if (i % 2 == 0) {
            field_output(field_1, m, n);
        }
        else {
            field_output(field_2, m, n);
        }
        field_update(field_1, field_2, m, n);
    }
    
    free_subptr((void**)field_1, (size_t)(n));
    free(field_1);
    free_subptr((void**)field_2, (size_t)(n));
    free(field_2);
    return 0;
}

bool** generate_matrix(size_t m, size_t n) {
    bool** columns = (bool**)malloc(n * sizeof(bool*));
    for (int i = 0; i < n; i++) {
        columns[i] = (bool*)malloc(m);
    }
    return columns;
}

void free_subptr(void** data, size_t n) {
    for (int i = 0; i < n; i++) {
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

void field_update(bool** data, bool** data2, size_t m, size_t n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int neighboors_qty = get_neighboors_qty(data, m, n, i, j);
            if(neighboors_qty >= 3 && data[i][j] == false) {
                data2[i][j] = true;
            }
            if(neighboors_qty < 2 && data[i][j] == true) {
                data2[i][j] = false;
            }
            if(neighboors_qty >= 2 && data[i][j] == true) {
                data2[i][j] = true;
            }
        }
    }
}

int get_neighboors_qty(bool** data, size_t m, size_t n, int i_i, int j_i) {
    int neighboors_qty = 0;
    for(int i = i_i - 1; i <= i_i + 1; i++) {
        for(int j = j_i - 1; j <= j_i + 1; j++) {
            int i_norm = (i + n) % n, j_norm = (j + m) % m;
            if(i == i_i && j_i == j) continue;
            if(data[i_norm][j_norm] == 1) neighboors_qty++;
        }
    }
    return neighboors_qty;
}
