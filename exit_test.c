#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void test_exit_code(const char *cmd, int expected_code)
{
	pid_t pid;
	int status;

	printf("Test: echo \"%s\" | ./minishell\n", cmd);
	pid = fork();
	if (pid == 0)
	{
		// Redirige l'entrée standard depuis une pipe
		int pipefd[2];
		pipe(pipefd);
		write(pipefd[1], cmd, strlen(cmd));
		write(pipefd[1], "\n", 1);
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);

		execl("./minishell", "./minishell", NULL);
		perror("exec");
		exit(1);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			int code = WEXITSTATUS(status);
			printf("  → Exit code: %d (%s)\n\n", code,
				(code == expected_code) ? "OK" : "FAIL");
		}
		else
			printf("  → Abnormal termination\n\n");
	}
}

int main(void)
{
	test_exit_code("exit", 0);           // doit quitter avec le code actuel
	test_exit_code("exit 0", 0);         // quitte avec 0
	test_exit_code("exit 42", 42);       // quitte avec 42
	test_exit_code("exit salut", 255);   // erreur num → 255
	test_exit_code("exit 1 2", 1);       // erreur : trop d'arguments → pas d'exit

	return (0);
}
