1. 因为 UDP 不需要保证数据的可靠性，缺少流控制机制
2. b c e
3. IP的作用是让UDP数据包准确传送到目标主机，UDP让包最终交给目标主机的某一套接字
4. 数据量小且需要频繁连接时
5. 在第一次使用 sendto() 函数时会给 UDP socket 分配 IP 和端口号
6. UDP socket 调用 connect 之后并不会实际建立连接，好处是可以直接使用 write 和 read 函数，不必调用相对来说更麻烦的 sendto 和 recvfrom 函数(对于建立连接的 IP 端口)
7. 略

