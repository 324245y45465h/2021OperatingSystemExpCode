#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>

void getMemAddr(unsigned long virAddr) {
    // 调用API获取页面大小
    int pageSize = getpagesize();

    // 提取出虚拟页号与虚拟页内偏移
    unsigned long virPageIndex = virAddr / pageSize;
    unsigned long virPageOffset = virAddr % pageSize;

    // 打开本进程对应的pagemap文件
    FILE* fp = fopen("/proc/self/pagemap", "rb");
    if (fp == nullptr) {
        printf("fail to open pagemap\n");
        return;
    }

    // 每一项记录8个字节
    unsigned long pagemapFileOffset = virPageIndex * 8ul;

    // 找到并读取对应记录
    unsigned long long info;
    fseek(fp, pagemapFileOffset, SEEK_SET);
    fread(&info, 8ul, 1, fp);
    fclose(fp);

    // 拆分记录信息
    // 对应页是否在内存中
    if ((info >> 63) & 1) {
        printf("当前页在内存中\n");
    } else {
        printf("当前页不在内存中\n");
    }

    unsigned long long phyPageIndex = ((1ull << 55) - 1) & info;
    printf("物理页号: %#x\n");

    unsigned long long phyAddr = phyPageIndex * pageSize + virPageOffset;
    printf("物理地址: %#x\n", phyAddr);
}

int main() {
    int a;
    int pid = fork();

    if (pid) {
        getMemAddr((unsigned long)&a);
    } else {
        getMemAddr((unsigned long)&a);
    }
    return 0;
}