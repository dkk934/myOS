## Global Descriptor Table (GDT):
The Global Descriptor Table (GDT) is a core memory management data structure used in Intel x86 and x86-64 computer architectures. It defines the characteristics of different memory areas (segments) during program execution, including their base addresses, sizes, and access privileges (such as read, write, and execute permissions).
### What is it?
A hardware-enforced database used by x86/x64 CPUs to define memory segment properties and access permissions.
### How does it work?
OS loads the table's location into the CPU's GDTR register during boot.Segment registers hold index pointers (selectors) pointing to table entries.CPU checks these entries on every memory access to verify size and permissions.
### Why do we need it?
The CPU requires it to transition into protected/long mode and enforce hardware-level security boundaries.
### Key Functionality
- Privilege isolation (separates kernel Ring 0 from user Ring 3).
- Memory protection (prevents user programs from modifying kernel memory).
- Mode switching (enables 64-bit execution and privilege transitions).


## Interrupt Descriptor Table (IDT) - (ISR)
### What is it?
An Interrupt Descriptor Table (IDT) is an x86/x64 database that maps specific hardware interrupts and software exceptions to their handling code, known as an Interrupt Service Routine (ISR).
### How does it work?

   1. Trigger: A hardware event (like a keyboard click) or an error (like division by zero) occurs.
   2. Lookup: The CPU looks up the event's unique number index inside the IDT.
   3. Execution: The entry directs the CPU to the exact memory address of the matching ISR.
   4. Return: The ISR runs, resolves the event, and passes control back to the interrupted program.

### Why do we need it?
Without the IDT and ISRs, the computer cannot react to real-time events (like mouse movements) or gracefully handle software crashes (like page faults), causing the system to freeze instantly.
### Key Functionality

* Asynchronous execution: Pauses normal programs instantly to process urgent hardware events.
* Crash prevention: Intercepts CPU errors (e.g., General Protection Faults) so the OS can kill the broken app instead of crashing entirely.
* Context saving: Automatically saves processor registers before running the ISR so the interrupted program can resume safely.

