all:server.exe client.exe

server.exe:tcp_server_win.cxx
	g++ -o server.exe tcp_server_win.cxx -lws2_32

client.exe:tcp_client_win.cxx
	g++ -o client.exe tcp_client_win.cxx -lws2_32