# BufferOverFlow Notes
## Basics of Buffer and Memory in C
### What is buffer?

Buffer is temporary memory storage on physical storage such as registers, cache and virtual memory. It is used to hold data when data is moved one place(process) to other places(processes).

Ex) variable used as buffer
```
int main(void) {
    char buffer[20];
    printf("Type your name:");
    gets(buffer);
    printf("Hello, %s", name);
    return 0;
}
```

## Memory Map
### What is range of memory addresses?

Assume that we have 32 bit CPU. Then, range of possible memory addresses would be   
> binary: 0 ~ 11111111111111111111111111111111  
> decimal: 0 ~ 4294967295 (= 4GB)  
> hexadecimal: 0x0 ~ 0xFFFFFFFF    
 
Therefore, **32bit CPU can utilize memory addresses no more than 4GB.**
 
 ### How Memory is used?
 
 > 0x00000000 ------------------------------------------------------- 0xFFFFFFFF  
 > | User Memory(3GB) | Kernel Memory(1GB) |  
 > | Code | Init Data | Uninit Data | Heap | Shared Library | Stack | Kernel Memory(1GB) |  
 > | **Free** | Code | ... | Heap | **Free(L)** | Shared Library | **Free(L)** | Stack | Kernel Memory(1GB) |  
 
**Code**: Store machine language that CPU can interpret  
**Data** (Init and Uninit): Store variables such as global variables and static variables  
**Heap**: Dynamic Memory  
**Shared Library**: Third Party Packages etc  
**Stack**: function args, return address, local variables, shell environment variables, etc  
**Free**: Empty Memory  
**Free(L)**: Large Empty Memory  

**Even though size of RAM is less than 4GB, this memory map remains the same by using memory management techniques called "Virtual Memory", "Paging", and "Swapping"**
   
Check [show_memory_map.c](https://github.com/swa770/sysprog/blob/master/bof/show_memory_map.c) to see the virtual address

## Few things about Stack in Memory Map
#### Size
Stack Datasize == Program Register Size. For 32-bit CPU, size of each stack data is 4 bytes
#### How Stack Grows
Opposite to Heap, Stack grows from high to low memory addresses.

> | 0x00000000 ------------------------------------------------------- 0xFFFFFFFF |   
> | ... | Heap **--- Grow --->** | Shared Library | **<--- Grow ---** Stack | ... |  

Why?
  1. to prevent stack from invading Kernel Area
  2. As head and stack grows toward each other, memory can be utilized efficiently
