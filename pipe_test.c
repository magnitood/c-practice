#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int pipe_fd[2];
	pipe(pipe_fd);

	int ret = fork();

	switch(ret) {
		case -1:
		{
			exit(EXIT_FAILURE);
			break;
		}

		case 0: // child
		{
			sleep(5);
			char buf[] = "This is a string";
			write(pipe_fd[1], buf, sizeof(buf));
			break;
		}

		default: // parent
		{
			char read_buf[256];
			read(pipe_fd[0], read_buf, sizeof(read_buf));
			printf("%s\n", read_buf);

			break;
		}
	}

	return 0;
}
