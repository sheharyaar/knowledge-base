# Linux Kernel and Userspace


I/O and Filesystems - [visit here](./io-fs/)
- Types of Files and devices
- Types of I/O : Blocking and Non Blocking
- Kernel I/O
- Userspace I/O
- VFS and Linux Storage Stack

Networking - [visit here](./networking/)
- Network I/O
- Network Buffers
- Traffic Control using eBPF andd XDP
- New technologies used in Linux forr Networking

Virtualisation - [visit here](./virtualisation/)
- HyperVisors
- Containers
- Namespaces
- Cgroups

Processes - [visit here](./processes/)
- Threading and Thread Pools
- Scheduling
- Systemd

EBPF and Observability - [visit here](./ebpf/)

## Learning Resources

Linux System Programming by Rorbert Love - [download here](./linux-system-programming-robert-love.pdf) \
The Linux Programming Interface by Michael Kerrisk - [download here](./tlpi.pdf)  \
LWN Articles - [visit here](https://lwn.net/Kernel/Index/)

# Solutions to The Linux Programming Interface (TLPI)

- Chapter 1-3 do not contain coding exercises

- Solutions are available folder-wise

- Solutions use syscalls (open, read, etc.) for various IO operations instead of File IO (fopen, fread, .etc) in C.
