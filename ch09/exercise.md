1.  
   * a, Time-wait 状态在发起断开连接的一方发生
   * c，与连接建立过程无关
2. 传输大文件时，不使用 Nagle 算法也会让输出缓冲区占满，开启 Nagle 反而会因为需要等待上一个数据包的 ACK 而变慢