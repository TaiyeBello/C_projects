#include "blather.h"
#include <sys/select.h>

client_t *server_get_client(server_t *server, int idx){
	if(idx > server->n_clients){
		return NULL;
	}else{
		return &server->client[idx];
	}
}
void server_start(server_t *server, char *server_name, int perms){
	char server_name_join[MAXPATH + 5];
	int fd;

	sprintf(server_name_join, "%s.fifo", server_name);
	remove(server_name_join);
	mkfifo(server_name_join,0666);
	fd = open(server_name_join, perms);
	strcpy(server->server_name,server_name);
	server->join_fd = fd;
}
void server_shutdown(server_t *server){
	char server_name_join[MAXPATH + 5];

	close(server->join_fd);	
	sprintf(server_name_join, "%s.fifo", server->server_name);
	unlink(server_name_join);
	mesg_t message;
	mesg_kind_t message_kind = BL_SHUTDOWN;
	message.kind = message_kind;
	server_broadcast(server, &message);

	for(int i = 0; i < server->n_clients; i++){
		server_remove_client(server,i);
	}
}
int server_add_client(server_t *server, join_t *join){
	if(server->n_clients == MAXCLIENTS){
		return 1;
	}else{
		client_t client;

		stpcpy(client.name,join->name);
		strcpy(client.to_client_fname, join->to_client_fname);
		stpcpy(client.to_server_fname, join->to_server_fname);
		client.to_client_fd = open(join->to_client_fname,O_RDWR);
		client.to_server_fd = open(join->to_server_fname,O_RDWR);
		client.data_ready = 0;
		server->client[server->n_clients] = client;
		server->n_clients ++;
		return 0;
	}
}
int server_remove_client(server_t *server, int idx){
	client_t client = server->client[idx];
	remove(client.to_client_fname);
	remove(client.to_server_fname);
	close(client.to_client_fd);
	close(client.to_server_fd);

	for(int i = idx; i < server->n_clients; i++){
		server->client[idx] = server->client[idx+1];
	}
	server->n_clients --;
	return 0;
}
int server_broadcast(server_t *server, mesg_t *mesg){
	for(int i = 0; i < server->n_clients; i++){
		write(server->client[i].to_client_fd, mesg, sizeof(mesg_t));
	}
	return 0;
}
void server_check_sources(server_t *server){
	int maxfd = 0;
	fd_set read_set;

	FD_ZERO(&read_set);

	for(int i = 0; i < server->n_clients; i++){
		client_t client = server->client[i];
		FD_SET(client.to_server_fd, &read_set);
		maxfd = maxfd < client.to_server_fd ? client.to_server_fd : maxfd;
	}

	FD_SET(server->join_fd, &read_set);
	maxfd = maxfd < server->join_fd ? server->join_fd : maxfd;

	select(maxfd + 1,&read_set,NULL,NULL,NULL);

	if(FD_ISSET(server->join_fd, &read_set)){
		server->join_ready =1;
	}

	for(int i = 0; i < server->n_clients; i++){ 
		client_t client = server->client[i];
		if(FD_ISSET(client.to_server_fd, &read_set)){
			server->client[i].data_ready = 1;
		}
	}
}
int server_join_ready(server_t *server){
	return server->join_ready;
}
int server_handle_join(server_t *server){
	if(server->join_ready == 1){
		join_t join_req;
		mesg_t message;

		read(server->join_fd, &join_req,sizeof(join_t));
		strcpy(message.name,join_req.name);
		message.kind = BL_JOINED;
		server_add_client(server,&join_req);
		server_broadcast(server,&message);
		server->join_ready = 0;
	}
	return 0;
}
int server_client_ready(server_t *server, int idx){
	return server->client[idx].data_ready;
}
int server_handle_client(server_t *server, int idx){
	if(server_client_ready(server,idx) == 1){
		mesg_t message;
		read(server->client[idx].to_server_fd, &message, sizeof(mesg_t));
		if(message.kind == BL_MESG){
			server_broadcast(server,&message);
			server->client[idx].data_ready = 0;
		}
		if(message.kind == BL_DEPARTED){
			server_broadcast(server,&message);
			server->client[idx].data_ready = 0;
			server_remove_client(server,idx);
		}
	}
	return 0;
}
