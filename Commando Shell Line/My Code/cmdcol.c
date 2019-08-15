#include <stdio.h>
#include "commando.h"

// cmdcol.c: functions related to cmdcol_t collections of commands.

void cmdcol_add(cmdcol_t *col, cmd_t *cmd){
		if(col->size == MAX_CMDS){
			printf("error, no more space in array");
		}else{
			col->cmd[col->size] = cmd;
			col->size ++;
		}
}
// Add the given cmd to the col structure. Update the cmd[] array and
// size field. Report an error if adding would cause size to exceed
// MAX_CMDS, the maximum number commands supported

void cmdcol_print(cmdcol_t *col){
	printf("%-4s #%-8s %4s %10s %4s %-s\n","JOB","PID","STAT","STR_STAT","OUTB","COMMAND");
	int argv_num = 0;
	int job_num = 0;
	while(job_num < col->size){
		char Commands[ARG_MAX] = "";
		argv_num = 0;
		while(col->cmd[job_num]->argv[argv_num] != NULL && argv_num < ARG_MAX){
			if(argv_num == 0){
				strcpy(Commands,col->cmd[job_num]->argv[argv_num]);
				strcat(Commands," ");
				argv_num++;
			}else{
				strcat(Commands,col->cmd[job_num]->argv[argv_num]);
				strcat(Commands," ");
				argv_num++;
			}
		}
		printf("%-4d #%-8d %4d %10s %4d %-s\n", job_num, col->cmd[job_num]->pid, col->cmd[job_num]->status, col->cmd[job_num]->str_status, col->cmd[job_num]->output_size, Commands);
		job_num++;
	}
}
// Print all cmd elements in the given col structure.  The format of
// the table is
//
// JOB  #PID      STAT   STR_STAT OUTB COMMAND
// 0    #17434       0    EXIT(0) 2239 ls -l -a -F
// 1    #17435       0    EXIT(0) 3936 gcc --help
// 2    #17436      -1        RUN   -1 sleep 2
// 3    #17437       0    EXIT(0)  921 cat Makefile
//
// Widths of the fields and justification are as follows
//
// JOB  #PID      STAT   STR_STAT OUTB COMMAND
// 1234  12345678 1234 1234567890 1234 Remaining
// left  left    right      right rigt left
// int   int       int     string  int string
//
// The final field should be the contents of cmd->argv[] with a space
// between each element of the array.

void cmdcol_update_state(cmdcol_t *col, int block){
	for(int i =0;i<col->size;i++){
		if(col->cmd[i] != NULL) cmd_update_state(col->cmd[i],block);
	}
}
// Update each cmd in col by calling cmd_update_state() which is also
// passed the block argument (either NOBLOCK or DOBLOCK)

void cmdcol_freeall(cmdcol_t *col){
	int i =0;
	while(col->cmd[i] !=NULL){
		cmd_free(col->cmd[i]);
		i++;}
}
// Call cmd_free() on all of the constituent cmd_t's.
