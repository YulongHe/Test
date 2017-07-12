/**
* @brief: this copy.c used to copy file.realize copy(1)
*
* @param: oldfile newfile(which file u want to copy)
*
* @return: 0 is success
*
* @log: yulong -20170711 first edit
**/
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

#define BUF_SIZE 1024
int main(int argc, char *argv[])
{
    int InputFd, OutputFd, OpenFlags;
    mode_t filePerms; //file para
    int numRead;
    char buf[BUF_SIZE];
	char buffer[20];
	int curr=0;

	if(argc != 3 || strcmp(argv[1], "--help") == 0 ) //test num of arg
		printf("ERROR parm!\n");
	/* test stdinput data  */
	if((numRead = read(STDIN_FILENO, buffer, 10)) == -1)//read std input data to buffer
		printf("read errror!\n");
	buffer[numRead] = '\0'; //end of string.must add by ourself
	printf("the input data is %s\n", buffer);

	/* test fd file descriptor naming rule. so close 0(std input) at first */
	if(close(STDIN_FILENO) == -1)
		printf("close STDIN_FILENO ERROR!\n");

	/*open input and output file*/
	InputFd = open(argv[1], O_RDONLY); //Ö»¶Á´ò¿ª
    if(InputFd == -1)
        printf("opening file %s error!\n", argv[1]);
    printf("InputFd is %d\n", InputFd);
   
    OpenFlags = O_CREAT | O_WRONLY | O_TRUNC;//if file not exiting so creat,otherwise clear it
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                   S_IROTH | S_IWOTH; /* RW-RW-RW--*/
    OutputFd = open(argv[2], OpenFlags, filePerms); //creat a new file
    if(OutputFd == -1){
        printf("opening  file %s error!\n", argv[2]);
    }              
	printf("OutputFd is %d\n", OutputFd);
    
    /* transfer data until we encounter end of input or an error */
    while((numRead = read(InputFd, buf, BUF_SIZE))>0)                    
    {
        if(write(OutputFd, buf, numRead) != numRead)
            printf("Fatal error, can't write whole buffer\n");    
    }
    if(numRead == -1)
        printf("error read\n");
	
	if(close(InputFd) == -1) //close a file descriptor
	    printf("close input error\n");
    if(close(OutputFd) == -1) 
        printf("close output error\n");
        
	InputFd = open("new_1.c", O_WRONLY|O_CREAT| O_APPEND, \
			S_IRUSR, S_IWUSR);

	write(InputFd, "test", 5);
    //exit(0);        	  
	curr=lseek(InputFd, 2, SEEK_END);
	printf("curr is %d\n", curr);
	
	if(close(InputFd) == -1)
		printf("close new_1.c error\n");
}	
