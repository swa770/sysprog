# sysprog
System Programming Work

# BufferOverFlow

13. Memory Map
source: http://www.hackerschool.org/Sub_Html/HS_University/BOF/essential/PDF_Files/13.pdf

<Memory Range>
  32 bit CPU:
    binary: 0 ~ 11111111111111111111111111111111
    decimal: 0 ~ 4294967295 (= 4GB) 
    hexadecimal: 0x0 ~ 0xFFFFFFFF
  
  Notes:
   - 32bit CPU cannot use memory more than 4GB
   - Even though RAM size is less than 4GB, this memory map remains the same by using memory management techniques called "Virtual Memory", "Paging", and "Swapping"
   
 <Memory Map>
  
 User Memory vs Kern
 0x00000000 -------------------------------------- 0xFFFFFFFF
                                                  |Kernel Memory (1GB)   
   
  
  
