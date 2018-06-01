# Process Management
### Intro
> Process requires kernel resources such as CPU, Memoery, Devices, Files, and other resources to be run.  
> So, multiple processes compete for these resources. It is kernel's role to  
> schedule, allocate, and withdraw its resources efficiently and
> processes use system call to request resources they need  
> There are two types of process, system process and user process. 
> System process is created by kernel to manage the system and gets higher priority for resource scheduling

### 1.1 Process Status  
* Running: CPU resource is allocated to the process  
* Ready: scheduled by kernel. Ready to start the process when CPU is available  
* Blocked: currently using other devices (I/O or Receiving Message. CPU is not necessary)  

### 1.2 Status Change

    Ready  ------ (Scheduled) ------>  Running  
           <--- (Time Slice Burst) ---    |    
                                          |  
      ^                                   |  
      |                                   |  
     (I/O Completion)                     |  
      |                                   |  
      |                                   |  
    Blocked  <----------(I/O request) ----     
    
    
 ### 1.3 Status In Detail

* TASK_RUNNING (Running)
 * user-mode running:
 * kernel-mode running: 
* TASK_RUNNING (Ready):
* TASK_INTERRUPTIBLE (Blocked):
* TASK_UNINTERRUPTIBLE (Blocked):
* EXIT_ZOMBIE:
* TASK_STOPPED:
* EXIT_DEAD:
* TASK_DEAD:

### 2.1 Context and Process Control Block

* Context: Minimal set of data about the state of process that must be saved to allow a task to be interrupted, and later continued from the same point.
* Process Control Block(PCB):

Context includes...
* Basic Process Info
**This information is already stored and managed by virtual memory system**

>Text, Data, Heap, Stack, ...

* Kernel Info 
**This information (Process Info) must be stored at PCB (task_struct in Linux)**

>Registers: general registers and special-purpose registers such as program counter, stack pointer, cpu-status register, virtual memory page table, etc
Process ID or Process Group ID
User and Security
Process status
Priority, Schedule Policy
Parent, Child, Sibling Process Info
Program Info
Memory Info
OpenFile info
Signal Info
Time Slice
Timer
Sync Info
IPC
        
2.2 Context Switch
    A context switch is the process of storing the state of a process or of a thread,
    so that it can be restored and execution resumed from the same point later.
    This allows multiple processes to share a single CPU, and is an essential feature of a multitasking operating system.




3. System Programming
