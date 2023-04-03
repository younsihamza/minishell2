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
  struct stat st;
  char  *fd = ttyname(STDIN_FILENO);
  int file = open(fd,O_RDONLY, 644);
  printf("%s", fd);
  if(fstat(file, &st) == -1)
    perror("fstat error");
  if(sig == SIGINT && a != 2)
  {
    printf("\n");
    rl_on_new_line();
    rl_replace_line("" , 0);
	  rl_redisplay();
  } 
  else if (sig == SIGINT && a == 2)
      write(1,  "\n", 1);
  else if (sig == SIGQUIT)
  {
      printf("%lld", st.st_size);
      printf("here");
  }
  else if(sig == SIGQUIT && a == 2)
      write(1,  "Quit\n", 5);
}