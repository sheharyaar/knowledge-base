# Traffic Control / Packet Filtering in Linux

## Tech Stack

- `eBPF` : extended Berkley Packet Filter
- `XDP` : eXpress Data Path
- `tc` : traffic-control

- `netfilter` ( need more info )

## Good Reading Resource :

#### Blogs

- [Tracing a packet journey using Linux tracepoints, perf and eBPF](https://blog.yadutaf.fr/2017/07/28/tracing-a-packet-journey-using-linux-tracepoints-perf-ebpf/)
- [eBPF Explorations](https://ragoragino.github.io/softwareengineering/miscellaneous/2021/03/06/ebpf-explorations.html)
- [Tracing the path of network traffic in Kubernetes](https://learnk8s.io/kubernetes-network-packets#the-container-network-interface-cni)

- Awesome EBPF - [github resource](https://github.com/zoidbergwill/awesome-ebpf)
- LinuxCon 2015 Linux Kernel Networking Walkthrough - [here](https://www.slideshare.net/ThomasGraf5/linuxcon-2015-linux-kernel-networking-walkthrough) { linux, kernel, networking }
- How to filter packets super fast: XDP & eBPF! - Julia Evans - [here](https://jvns.ca/blog/2017/04/07/xdp-bpf-tutorial/) { ebpf, xdp }
- The eXpress Data Path[here] - (https://blogs.igalia.com/dpino/2019/01/10/the-express-data-path/) { xdp. ebpf }
- Making the Kernel’s Networking Data Path Programmable with BPF and XDP - [here](http://schd.ws/hosted_files/ossna2017/da/BPFandXDP.pdf) { ebpf, xdp}
- Toward Flexible and Efficient In-Kernel Network Function Chaining with IOVisor - [here](http://hpsr2018.ieee-hpsr.org/files/2018/06/18-06-18-IOVisor-HPSR.pdf) : { ebpf }
- Cilium - Container Networking with BPF & XDP - [here](https://www.slideshare.net/ThomasGraf5/clium-container-networking-with-bpf-xdp)
{ ebpf, cilium, container }

## tc/BPF or XDP/BPF

Resource : https://liuhangbin.netlify.app/post/ebpf-and-xdp/


Key points : 

- tc/BPF works for **both** egress and ingress traffic. XDP/BPF works for ingress traffic
- tc/BPF does not require HW driver changes, XDP typically uses native driver mode for best performance
- XDP hook is earlier, hence faster performance
- tc has better packet mangling capability
- XDP is better for complete packet rewrites
- Offloaded tc/ebpf and Offloaded XDP offer similar performance advantage
