#include "minishell.h"
// void handler_sigquit(int sig)
// {
//   printf("Ctrl + 3");
// }

int signal_gen(int i)
{

  static int j;
  if(i == 1)
    j = 1;
  else if((i + j) % 2 == 0)
        j = 2;
  return j;
}

void handle_sigint(int sig)
{
  struct termios term;

  term.c_ispeed = 0;
  if(sig == SIGINT && signal_gen(1) == 1)
  {
	printf("\n");
    rl_on_new_line();
    rl_replace_line("" , 0);
	rl_redisplay();
  }
   if(sig == SIGINT && signal_gen(2) == 2)
  {
    puts("here");
    tcsetattr(STDIN_FILENO,TCSANOW,&term);
    printf("\n");
    exit(0);
  } 
  
}