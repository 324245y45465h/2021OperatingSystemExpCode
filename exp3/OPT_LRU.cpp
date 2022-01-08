#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

const int PAGE_SIZE = 10;
const int PAGE_FRAMES_MAX = 8;
const int PROC_SIZE = PAGE_SIZE * 240;
const int REQ_TIMES = 200;
// 0: OPT
// 1: LRU
const int ALG_OPT = 0;
const int ALG_LRU = 1;

int changePageCnt = 0;
int A[PROC_SIZE];
int yekuang[PAGE_FRAMES_MAX][PAGE_SIZE];
int yebiao[PAGE_FRAMES_MAX];
int reqSeq[REQ_TIMES];
int lru[PAGE_FRAMES_MAX];

void getRandReq() {
    for (int i = 0; i < REQ_TIMES; ++i) {
        reqSeq[i] = rand() % 2400;
    }
}

bool isInYebiao(int yekuanghao) {
    for (int i = 0; i < PAGE_FRAMES_MAX; ++i) {
        if (yebiao[i] == yekuanghao) return true;
    }
    return false;
}

void changePage(int yekuanghao, int reqID, int opt) {
    int startAddr = yekuanghao * PAGE_SIZE;
    int changePageNum;

    if (opt == 0) {
        int used[PAGE_FRAMES_MAX];
        memset(used, 0, sizeof(used));
        for (int i = reqID + 1; i < REQ_TIMES; ++i) {
            int ykh_tmp = reqSeq[i] / PAGE_SIZE;
            int cntTmp = PAGE_FRAMES_MAX;
            bool flg = 0;
            for (int j = 0; j < PAGE_FRAMES_MAX; ++j) {
                if (ykh_tmp == yebiao[j]) {
                    cntTmp--;
                    used[j] = 1;
                    if (cntTmp == 1) {
                        flg = 1;
                    }
                    break;
                }
            }
            if (flg) break;
        }
        for (int j = 0; j < PAGE_FRAMES_MAX; ++j) {
            if (used[j] == 0) {
                changePageNum = j;
            }
        }
    } else if (opt == 1) {
        int zuijinshiyong = REQ_TIMES;
        for (int i = 0; i < PAGE_FRAMES_MAX; ++i) {
            if (lru[i] < zuijinshiyong) {
                zuijinshiyong = lru[i];
                changePageNum = i;
            }
        }
    }

    yebiao[changePageNum] = yekuanghao;
    for (int i = startAddr, j = 0; i <= PAGE_SIZE + startAddr, j < PAGE_SIZE;
         ++i, ++j) {
        yekuang[changePageNum][j] = A[i];
    }
}

void printReqAns(int req) {
    int page = req / PAGE_SIZE;
    int pianyi = req % PAGE_SIZE;
    for (int i = 0; i < PAGE_FRAMES_MAX; ++i) {
        if (yebiao[i] == page) {
            printf("%d\t", yekuang[i][pianyi]);
        }
    }
}

int main() {
    srand(time(0));
    for (int i = 0; i < PAGE_FRAMES_MAX; ++i) yebiao[i] = -1;
    memset(lru, 0, sizeof(lru));
    getRandReq();
    for (int i = 0; i < PROC_SIZE; ++i) A[i] = rand();

    for (int i = 0; i < REQ_TIMES; ++i) {
        int req = reqSeq[i];
        // printf("req == %d\t", req);
        if (!isInYebiao(req / PAGE_SIZE)) {
            changePageCnt++;
            changePage(req / PAGE_SIZE, i, ALG_OPT);
        }
        // printReqAns(req);
        // putchar('\n');

        // for (int i = 0; i < PAGE_FRAMES_MAX; ++i) {
        //     printf("yebiao[%d] == %d\n", i, yebiao[i]);
        // }
    }
    printf("changePageCnt == %d\n", changePageCnt);

    memset(yebiao, -1, sizeof(yebiao));
    memset(yekuang, 0, sizeof(yekuang));
    changePageCnt = 0;
    for (int i = 0; i < REQ_TIMES; ++i) {
        int req = reqSeq[i];
        // printf("req == %d\t", req);
        if (!isInYebiao(req / PAGE_SIZE)) {
            changePageCnt++;
            changePage(req / PAGE_SIZE, i, ALG_LRU);
        }
        // printReqAns(req);
        // putchar('\n');
        lru[req / PAGE_SIZE] = i;

        // for (int i = 0; i < PAGE_FRAMES_MAX; ++i) {
        //     printf("yebiao[%d] == %d\n", i, yebiao[i]);
        // }
    }

    printf("changePageCnt == %d\n", changePageCnt);
    return 0;
}