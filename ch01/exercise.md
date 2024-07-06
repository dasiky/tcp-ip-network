1. 将网络通信的动作封装为可以被程序调用的 API； socket 在英文中有“插座”或“插孔”的意思，比喻计算机网络中的通信就像电器的连接，通过“插座”来连接和传输电流。
1. listen 让 socket 处于可以接受连接的状态，实际接受连接由 accept 完成。
1. 因为在 linux 中将 socket 也看作是一种文件，所以可以直接使用文件的 I/O 函数；windows 系统下区分文件 I/O 和 socket I/O，使用 socket 特有的函数来进行读写。
1. 服务端要分配一个地址，因为客户端在建立连接时需要知道服务端地址才能进行连接；使用 bind 函数。
1. 对于 socket 来说，linux 使用文件描述符来标识一个 socket，windows 下则用句柄来标识一个 socket。在需要使用 socket 的函数中，linux 将 socket 对应的文件描述符传入来对 socket 进行操作，windows 则传入句柄。
1.  
1. 