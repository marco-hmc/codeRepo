## Chapter 1: Introduction to the x86 architecture and about our OS

**Specifications:**

* Code in C++
* x86, 32 bit architecture
* Boot with Grub
* Kind of modular system for drivers
* Kind of UNIX style
* Multitasking
* ELF executable in userland
* Modules (accessible in userland using /dev/...) :
    * IDE disks
    * DOS partitions
    * Clock
    * EXT2 (read only)
    * Boch VBE
* Userland :
    * API Posix
    * LibC
    * "Can" run a shell or some executables (e.g., lua)
