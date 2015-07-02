/* vim: set ts=4 sw=4: */

#include <unistd.h>
#include <stdio.h>
#include <termios.h>

int
mygetch()
{
	int c;
	int fd = STDIN_FILENO;
	struct termios velha, nova;

	if (tcgetattr(fd, &velha) < 0) {
		perror("tcgetattr");
		return -1;
	}

	nova = velha;
	nova.c_lflag &= ~ICANON;
	nova.c_lflag = ECHOE;

	if (tcsetattr(fd, TCSANOW, &nova) < 0) {
		perror("tcsetattr");
		return -1;
	}

	setbuf(stdin, NULL);
	read(STDIN_FILENO, &c, 1);
	tcsetattr(fd, TCSANOW, &velha);

	return c;
}
