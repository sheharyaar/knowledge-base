# Knowledge Base

I/O and Filesystems - [visit here](./io/)
- Types of Files and devices
- Types of I/O : Blocking and Non Blocking
- Kernel I/O
- Userspace I/O
- VFS and Linux Storage Stack

Networking - [visit here](./network/)
- Linux Networking Stack - [here](./network/LINUX.md)
- Traffic Control (BPF, XDP, tc, netfilter) - [here](./network/TC.md)
- QUIC Protocol - [here](./network/QUIC.md)

Virtualisation - [visit here](./virtualisation/)
- HyperVisors
- Containers (cgroups, namespaces, capabilities, docker) - [here](./virtualisation/CONTAINERS.md)
- Seccomp

Performance Tooling - [visit here](./performance/)
- Threading and Thread Pools
- Scheduling

Linux Core - 
- DBus, systemd, init

Cloud - [visit here](./cloud/)
- Kubernetes (all yamls types) - [here](./cloud/kubernetes/)
- Mesh, CNCF stuff

Big Data - [visit here](./data/)
- Apache Family (hadoop, cassandra, etc.)

EBPF and Observability - [visit here](./ebpf/)

## Learning Resources

Linux System Programming by Rorbert Love - [download here](./linux-system-programming-robert-love.pdf) \
The Linux Programming Interface by Michael Kerrisk - [download here](./tlpi.pdf)  \
LWN Articles - [visit here](https://lwn.net/Kernel/Index/)

# Solutions to The Linux Programming Interface (TLPI)

- Chapter 1-3 do not contain coding exercises

- Solutions are available folder-wise - [here](./TLPI-Solutions/)

- Solutions use syscalls (open, read, etc.) for various IO operations instead of File IO (fopen, fread, .etc) in C.
