#include "blather.h"
#include <signal.h>

server_t server;

void handle_SIG(){
	server_shutdown(&server);
	exit(0);
}

int main(int argc, char **argv){
	struct sigaction my_sa = {};
	sigemptyset(&my_sa.sa_mask);               
	my_sa.sa_flags = SA_RESTART;               

	my_sa.sa_handler = handle_SIG;         
	sigaction(SIGTERM, &my_sa, NULL);          

	my_sa.sa_handler = handle_SIG;          
	sigaction(SIGINT,  &my_sa, NULL); 
  
	server_start(&server, argv[1], O_RDWR);
	while(1){
		server_check_sources(&server);	
		if(server_join_ready(&server) == 1){
			server_handle_join(&server);
		}
		for(int i = 0; i < server.n_clients; i ++){
			if(server_client_ready(&server,i) == 1){
				server_handle_client(&server,i);
			}
		}
	}
	         
}
