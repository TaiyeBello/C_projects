#include "commando.h"

int main(int argc, char const *argv[]) {
  char* dont_delete_me =
    "COMMANDO COMMANDS\n"
    "help               : show this message\n"
    "exit               : exit the program\n"
    "list               : list all jobs that have been started giving information on each\n"
    "pause nanos secs   : pause for the given number of nanseconds and seconds\n"
    "output-for int     : print the output for given job number\n"
    "wait-for int       : wait until the given job number finishes\n"
    "wait-all           : wait for all jobs to finish\n"
    "command arg1 ...   : non-built-in is run as a job";

  char* help = "COMMANDO COMMANDS\nhelp               : show this message\nexit               : exit the program\nlist               : list all jobs that have been started giving information on each\npause nanos secs   : pause for the given number of nanseconds and seconds\noutput-for int     : print the output for given job number\noutput-all         : print output for all jobs\nwait-for int       : wait until the given job number finishes\nwait-all           : wait for all jobs to finish\ncommand arg1 ...   : non-built-in is run as a job";

  setvbuf(stdout, NULL, _IONBF, 0); // Turn off output buffering
  int eof = 0;
  int check_echo=-99;
  if(argc > 1){
    check_echo = strcmp(argv[1],"--echo");
  }

  char* check_env = getenv("COMMANDO_ECHO");
  cmdcol_t* col = (cmdcol_t*)malloc(sizeof(cmdcol_t));

  while(eof == 0){
    printf("@> ");
    if(check_env != NULL || check_echo == 0){
      char* stream = (char*)malloc(MAX_LINE*sizeof(char));
      char* resp = fgets(stream,MAX_LINE,stdin);
      char** tokens= malloc(sizeof(char*)*ARG_MAX);
      int* num_tokens = malloc(sizeof(int*));
      if(resp == NULL){
        printf("\nEnd of input");
        break;
      }
      parse_into_tokens(stream,tokens,num_tokens);
      if(strcmp(stream, "\n")){
        for(int i=0;i<*num_tokens-1;i+=1){
          printf("%s ",tokens[i] );
        }
        printf("%s\n",tokens[*num_tokens-1]);
      }

      if(*num_tokens>0){
        if(!strcmp(tokens[0],"exit\n")) {
            printf("End of input");
            break;
        }
        else if(!strcmp(tokens[0],"help")){
          printf("%s\n",help);
        }
        else if(!strcmp(tokens[0],"exit")){
          eof=1;
        }
        else if(!strcmp(tokens[0],"list")){
          cmdcol_print(col);
        }
        else if(!strcmp(tokens[0],"pause")){
          pause_for(atol(tokens[1]),atoi(tokens[2]));
        }
        else if(!strcmp(tokens[0],"output-for")){
          cmd_fetch_output(col->cmd[atoi(tokens[1])]);
        }
        else if(!strcmp(tokens[0],"wait-for")){
          cmd_update_state(col->cmd[atoi(tokens[1])],1);
        }
        else if(!strcmp(tokens[0],"wait-all")){
          cmdcol_update_state(col,1);
        }
        else{
          cmd_t* new_cmd =cmd_new(tokens);
          cmdcol_add(col,new_cmd);
          cmd_start(new_cmd);
        }
      }else printf("\n");
    }
    else{
      char* stream = (char*)malloc(MAX_LINE*sizeof(char));
      char* resp = fgets(stream,MAX_LINE,stdin);

      int* num_tokens = malloc(sizeof(int*));
      char** tokens= malloc(sizeof(char*)*ARG_MAX);
      parse_into_tokens(stream,tokens,num_tokens);

      if(resp == NULL){
        printf("\nEnd of input");
        break;
      }

      if(*num_tokens>0){
        if(!strcmp(tokens[0],"exit\n")) {
            printf("End of input");
            break;
        }
        else if(!strcmp(tokens[0],"help")){
          printf("%s\n",help);
        }
        else if(!strcmp(tokens[0],"exit")){
          eof=1;
        }
        else if(!strcmp(tokens[0],"list")){
          cmdcol_print(col);
        }
        else if(!strcmp(tokens[0],"pause")){
          pause_for(atol(tokens[1]),atoi(tokens[2]));
        }
        else if(!strcmp(tokens[0],"output-for")){
          cmd_fetch_output(col->cmd[atoi(tokens[1])]);
        }
        else if(!strcmp(tokens[0],"wait-for")){
          cmd_update_state(col->cmd[atoi(tokens[1])],1);
        }
        else if(!strcmp(tokens[0],"wait-all")){
          cmdcol_update_state(col,1);
        }
        else{
          cmd_t* new_cmd =cmd_new(tokens);
          cmd_start(new_cmd);

          cmdcol_add(col,new_cmd);
        }
      }else printf("\n");
    }
  }


}
