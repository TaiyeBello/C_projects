#include "blather.h"
#include <pthread.h>

simpio_t simpio_actual;
simpio_t *simpio = &simpio_actual;

client_t client_actual;
client_t *client = &client_actual;

pthread_t user_thread;
pthread_t server_thread;

void *user_helper(){
	mesg_t message;
	while(!simpio->end_of_input){
		simpio_reset(simpio);
		iprintf(simpio, "");
		while(!simpio->line_ready && !simpio->end_of_input){
			simpio_get_char(simpio);	
		}
		if (simpio->line_ready == 1){
			message.kind = BL_MESG;
			strcpy(message.name, client->name);
			strcpy(message.body, simpio->buf);
			write(client->to_server_fd,&message, sizeof(mesg_t));
		}
	}
	pthread_cancel(server_thread);

	message.kind = BL_DEPARTED;
	strcpy(message.name, client->name);
	strcpy(message.body,"");
	write(client->to_server_fd,&message, sizeof(mesg_t));
	
	//pthread_cancel(server_thread);
	return NULL;
}
void *server_helper(){
	mesg_t message;
	while(1){
		read(client->to_client_fd,&message, sizeof(mesg_t));
		if(message.kind == BL_MESG){
			iprintf(simpio,"[%s] : %s\n",message.name,message.body);
		}
		else if(message.kind == BL_JOINED){
			iprintf(simpio,"-- %s JOINED --\n",message.name);
		}
		else if(message.kind == BL_DEPARTED){
			iprintf(simpio,"-- %s DEPARTED --\n",message.name);
		}
		else {
			iprintf(simpio,"!!! server is shutting down !!!\n");
			break;
		}
	}
	pthread_cancel(user_thread);
	return NULL;
}
int main(int argc, char **argv){
	strcpy(client->name,argv[2]);
	
	sprintf(client->to_client_fname, "%d.fifo",getpid());
	sprintf(client->to_server_fname, "%d1.fifo",getpid());
	mkfifo(client->to_client_fname,0666);
	mkfifo(client->to_server_fname,0666);
	client->to_client_fd = open(client->to_client_fname,O_RDWR);
	client->to_server_fd = open(client->to_server_fname,O_RDWR);
	
	join_t join_req;
	strcpy(join_req.name, client->name);
	strcpy(join_req.to_client_fname,client->to_client_fname);
	strcpy(join_req.to_server_fname,client->to_server_fname);
	
	char server_name[MAXNAME];
	int server_fd;
	sprintf(server_name, "%s.fifo",argv[1]);
	server_fd = open(server_name,O_WRONLY);
	write(server_fd,&join_req,sizeof(join_req));
	
	char prompt[MAXNAME];
	snprintf(prompt, MAXNAME, "%s>> ",argv[2]);
	simpio_set_prompt(simpio,prompt);
	simpio_reset(simpio);
	simpio_noncanonical_terminal_mode();
	
	pthread_create(&user_thread,NULL,user_helper,NULL);
	pthread_create(&server_thread,NULL,server_helper,NULL);
	pthread_join(user_thread, NULL);
	pthread_join(server_thread, NULL);
  
	simpio_reset_terminal_mode();
	printf("\n");                 
	return 0;
}
