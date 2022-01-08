#include <cstdio>

const int MAX_RAW = 10000;
const int MAX_COL = 20000;

int main() {
    int my_array[MAX_RAW][MAX_COL];
    for (int i = 0; i < MAX_RAW; ++i) {
        for (int j = 0; j < MAX_COL; ++j) {
            my_array[i][j] = 0;
        }
    }
    // for (int j = 0; j < MAX_COL; ++j) {
    //     for (int i = 0; i < MAX_RAW; ++i) {
    //         my_array[i][j] = 0;
    //     }
    // }
    return 0;
}