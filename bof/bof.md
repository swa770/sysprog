# BufferOverFlow Notes
## Memory Map
### What is range of memory addresses?

Assume that we have 32 bit CPU. Then, range of possible memory addresses would be   
    binary: 0 ~ 11111111111111111111111111111111
    decimal: 0 ~ 4294967295 (= 4GB)  
    hexadecimal: 0x0 ~ 0xFFFFFFFF  
 
Therefore, **32bit CPU can utilize memory addresses no more than 4GB.**
 
 ### How Memory is used?
 
 0x00000000 ------------------------------------------------------- 0xFFFFFFFF  
 |                        User Memory(3GB)                          |Kernel Memory (1GB)  
 0x00000000 ------------------------------------------------------- 0xFFFFFFFF  
 | Code | Init Data | Uninit Data | Heap | Shared Library | Stack   |Kernel Memory (1GB)  
 0x00000000 ------------------------------------------------------- 0xFFFFFFFF  
 |**Free**| Code ... | Heap |**Free(L)**| Shared Library |**Free(L)**| Stack |Kernel Memory (1GB)  
 
Code: Store machine language that CPU can interpret
Data (Init and Uninit): Store variables such as global variables and static variables
Heap: Dynamic Memory
Shared Library: Third Party Packages etc
Stack: function args, return address, local variables, shell environment variables, etc
Free: Empty Memory
Free(L): Large Empty Memory

Even though size of RAM is less than 4GB, this memory map remains the same by using memory management techniques called "Virtual Memory", "Paging", and "Swapping"
   
* use show_memory_map.c to actually see the virtual address
