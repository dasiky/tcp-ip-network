all:server.exe client.exe

server.exe:hello_server_win.cxx
	g++ -o server.exe hello_server_win.cxx -lws2_32

client.exe:hello_client_win.cxx
	g++ -o client.exe hello_client_win.cxx -lws2_32