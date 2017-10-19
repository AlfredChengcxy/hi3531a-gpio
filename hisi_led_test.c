#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>


// ./hisi_led_test on
// ./hisi_led_test off


int main(int argc, char *argv[])
{
	int fd;
	int val = 1;
	
	fd = open("/dev/hisi_led", O_RDWR);
	if(fd < 0)
	{
		printf("Can't open /dev/hisi_led !\n");
	}
	
	if (argc != 2)
	{
		printf("Usage :\n");
		printf("%s <on|off>\n", argv[0]);
		
		close(fd);
		
		return 0;
	}

	if (strcmp(argv[1], "on") == 0)
	{
		val = 1;
	}
	else if(strcmp(argv[1], "off") == 0)
	{
		val = 0;
	}
	else
	{
		printf("Usage :\n");
		printf("%s <on|off>\n", argv[0]);
		
		close(fd);
		
		return 0;	
	}
	
	write(fd, &val, 4);
	
	close(fd);
	
	return 0;
}
