#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


int main()
{
  	unsigned char  attr[1024]={'\0'};
    	unsigned long  phys_addr;
	int fd;
	printf("this is used to read phys_addr \n");
    	if ((fd  = open("/sys/class/udmabuf/udmabuf0/phys_addr", O_RDONLY)) != -1) {
        	read(fd, attr, 16);
        	sscanf(attr, "%x", &phys_addr);
		printf("phys addr is %s\n",attr);
		printf("phys_addr is %x\n",phys_addr);
        	close(fd);
    	}
	return 0;
}
