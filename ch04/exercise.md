1. 从下至上分别是：链路层、网络层（IP）、传输层和应用层；TCP 和 UDP 在传输层使用协议不同。
2. 链路层负责两台计算机通过网络进行数据交换时的物理连接；IP 层负责解决网络传输中的路径选择问题。IP 层基于链路层
3. 每层协议栈负责处理网络传输中的一部分问题
4. 服务端调用 listen() 开始监听之后
5. listen() 调用之后创建连接请求队列，客户端和服务端完成 TCP 连接之后将对应 socketfd 放入连接请求队列中，等待服务端调用 accept() 取出 socketfd 进行通信
6. 通常客户端建立连接时只需要知道服务端的地址和端口，连接所使用的本地地址和端口没有要求；客户端在 connect() 时会自动分配 IP 地址和端口。
7. 略