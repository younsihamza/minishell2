#include "minishell.h"
void handler_sigquit(int sig)
{
  printf("Ctrl + 3 %d", sig);
}

int signal_gen(int i)
{


  static int j;
  if(i == 0)
    j = 0;
  else if(i == 1)
        j = 1;
 else
      return j;
  return j;
}

void signal_catch(int sig)
{
  if(sig == SIGINT)
  {
    printf("\n");
  }
}

void handle_sigint(int sig)
{

  if(sig == SIGINT && rrr == 0)
  {
    printf("\n");
    rl_on_new_line();
    rl_replace_line("" , 0);
	  rl_redisplay();
  } 
  else if (sig == SIGINT && rrr == 1)
      write(1,  "\n", 1);
  else if(sig == SIGQUIT && rrr == 1)
      write(1,  "Quit\n", 5);
}