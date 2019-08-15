#include <stdio.h>
#include "commando.h"


cmd_t *cmd_new(char *argv[]) {
	cmd_t *new_struct = malloc(sizeof(cmd_t));
	//new_struct->argv = sizeof(strdup(	argv))
	int i = 0;
	while(i < ARG_MAX){
		new_struct->argv[i] = 0;
		i+=1;
	}
	i=0;
	while (argv[i] != NULL) {
		//new_struct->argv[i] = malloc(sizeof(strdup(argv[i])));
		new_struct->argv[i] = strdup(argv[i]);
		i++;
	}
	argv[i] = NULL;

	strcpy(new_struct->name,new_struct->argv[0]);
	new_struct->pid = -1;
	new_struct->out_pipe[0] = -1; //*new_struct.out_pipe=sumething
	new_struct->out_pipe[1] = -1;
	new_struct->finished = 0;
	new_struct->status = -1;
	snprintf(new_struct->str_status, BUFSIZE, "INIT");
	new_struct->output = NULL;
	new_struct->output_size = -1;

  return new_struct;
}

void cmd_free(cmd_t *cmd) {
  if(cmd->output != NULL){
		free(cmd->output);
  }
	int i = 0;
	while(cmd->argv[i]!=NULL){
		free(cmd->argv[i]);
		i+=1;
	}
  free(cmd);
}
void cmd_start(cmd_t *cmd){

	int pipe_result = pipe(cmd->out_pipe);
	if(pipe_result == -1){
		printf("error\n");
	}
	int pid = fork();
	snprintf(cmd->str_status, BUFSIZE, "RUN");

	if(pid == 0){
		dup2(cmd->out_pipe[PWRITE],STDOUT_FILENO);
		execvp(cmd->name,cmd->argv);
	}
		cmd->pid = pid;
		//cmd->out_pipe[PREAD] = par_child_pipe[PREAD];
		//cmd->out_pipe[PWRITE] = par_child_pipe[PWRITE];


}

void cmd_update_state(cmd_t *cmd, int block){
  if(cmd->finished == 1){
		return;
  }
	int status;
	int pid = waitpid(cmd->pid, &status, block);
	if (pid == 0) return;
	if (pid == -1) _exit(-1);
	if(WIFEXITED(status)){
		cmd->finished=1;
		cmd->status = WEXITSTATUS(status);
		sprintf(cmd->str_status,"EXIT(%d)",WEXITSTATUS(status));
		close(cmd->out_pipe[PWRITE]);
		cmd_fetch_output(cmd);
		printf("@!!! %s[#%d]: %s\n",cmd->name,cmd->pid,cmd->str_status);
	}
}
// If the finished flag is 1, does nothing. Otherwise, updates the
// state of cmd.  Uses waitpid() and the pid field of command to wait
// selectively for the given process. Passes block (one of DOBLOCK or
// NOBLOCK) to waitpid() to cause either non-blocking or blocking
// waits.  Uses the macro WIFEXITED to check the returned status for
// whether the command has exited. If so, sets the finished field to 1
// and sets the cmd->status field to the exit status of the cmd using
// the WEXITSTATUS macro. Calls cmd_fetch_output() to fill up the
// output buffer for later printing.
//
// When a command finishes (the first time), prints a status update
// message of the form
//
// @!!! ls[#17331]: EXIT(0)
//
// which includes the command name, PID, and exit status.

char *read_all(int fd, int *nread){
  size_t buffsize = 1024;
  char *buff = malloc(buffsize);
  ssize_t pos = read(fd, buff, buffsize);

  while(pos >= buffsize){
	  buff = realloc(buff, buffsize*2);
	  buffsize *= 2;
	  pos += read(fd, buff+pos, buffsize-pos);
  }
  *(nread) = pos;
  *(buff+pos) = '\0';
  return buff;

}
// Reads all input from the open file descriptor fd. Stores the
// results in a dynamically allocated buffer which may need to grow as
// more data is read.  Uses an efficient growth scheme such as
// doubling the size of the buffer when additional space is
// needed. Uses realloc() for resizing.  When no data is left in fd,
// sets the integer pointed to by nread to the number of bytes read
// and return a pointer to the allocated buffer. Ensures the return
// string is null-terminated. Does not call close() on the fd as this
// is done elsewhere.

void cmd_fetch_output(cmd_t *cmd){
	if(cmd->finished == 0){
		printf("%s[#%d] not finished yet\n",cmd->name,cmd->pid);
	}
	else{
		cmd->output = read_all(cmd->out_pipe[PREAD], &cmd->output_size);
		close(cmd->out_pipe[PREAD]);
	}
}
// If cmd->finished is zero, prints an error message with the format
//
// ls[#12341] not finished yet
//
// Otherwise retrieves output from the cmd->out_pipe and fills
// cmd->output setting cmd->output_size to number of bytes in
// output. Makes use of read_all() to efficiently capture
// output. Closes the pipe associated with the command after reading
// all input.

void cmd_print_output(cmd_t *cmd){
	if(cmd->output != NULL){
		printf("%s",cmd->output);
	}else{
		printf("%s[#%d] output not ready\n",cmd->name,cmd->pid);
	}
}
// Prints the output of the cmd contained in the output field if it is
// non-null. Prints the error message
//
// ls[#17251] : output not ready
//
// if output is NULL. The message includes the command name and PID.
