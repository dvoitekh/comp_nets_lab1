# comp_nets_lab1
2 client-server apps based on TCP and UDP sockets respectively. Client sends 2 arrays(boolean and integer) to Server wich process them.

##How to run
Enter either `tcp` or `udp` folder

Compile `server` and `client` apps, for example:
```bash
gcc tcp_client.c -o client
gcc tcp_server.c -o server
```
Run `server` and `client` apps in separate tabs of your terminal:
```bash
./client # in one tab
./server # in another tab
```
