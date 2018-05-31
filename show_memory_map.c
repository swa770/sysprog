/* Display the virtual adress of 
 * Code, Data, Heap, Shared Lib, Stack, Kernel
 */

#include <stdio.h>
#include <stdlib.h>

int global_int = 0;
int uninit_global_int;

int main(){
    static int a = 0;
    static int b;

    // Code
    printf("main = 0x%08x", &main);
    // Data
    // Init
    printf("global_int = 0x%08x", &global_int);
    printf("a = 0x%08x", &a);
    // UnInit
    printf("uninit_global_int = 0x%08x", &uninit_global_int);
    printf("a = 0x%08x", &b);
    // Heap
    char *heap = (char*)malloc(100);
    printf("heap = 0x%08x", heap);
    // Shared Lib
    // Stack
    // Kernel
}
