#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <strings.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netdb.h>

#define RECV_SIZE 2048

void error(const char *msg){
  perror(msg);
  exit(0);
}

int main(int argc, char *argv[]){
  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[RECV_SIZE];
  if (argc < 3){
    fprintf(stderr, "usage %s hostname port\n", argv[0]);
    exit(0);
  }
  portno = atoi(argv[2]);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    error("ERROR opening socket");
  server = gethostbyname(argv[1]);
  if(server == NULL){
    fprintf(stderr, "ERROR, no such host\n");
    exit(0);
  }
  bzero((char*) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char*)server->h_addr,
        (char*)&serv_addr.sin_addr.s_addr,
        server->h_length);
  serv_addr.sin_port = htons(portno);
  if(connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    error("ERROR connecting");
  
  printf("Please enter the message: ");
  bzero(buffer, RECV_SIZE);
  fgets(buffer, RECV_SIZE-1, stdin);  
  n = write(sockfd, buffer, strlen(buffer));
  if (n<0)
    error("ERROR writing to socket");
  printf("%s\n", buffer);

  printf("Please enter the message: ");
  bzero(buffer, RECV_SIZE);
  fgets(buffer, RECV_SIZE-1, stdin);  
  n = write(sockfd, buffer, strlen(buffer));
  if (n<0)
    error("ERROR writing to socket");
  printf("%s\n", buffer);
  
  bzero(buffer, RECV_SIZE);
  n = read(sockfd, buffer, RECV_SIZE);
  if (n<0)
    error("ERROR reading from socket");
  // PROCESSING INCOMING FILE
  if (n > 4){
    printf("Message Size: %d\nMap X: %d\nMap Y: %d\nMap W: %d\nMap H: %d\n",
           n, buffer[0], buffer[1], buffer[2], buffer[3]);
    for (int i = 4; i < n; i++){
      printf("\x1b[%dm%c\x1b[0m",31+buffer[i]%7, buffer[i]+48);
      if((i-4)%buffer[2] == buffer[2]-1)
        printf("\n");
    }
  }
  
  printf("Please enter the message: ");
  bzero(buffer, RECV_SIZE);
  fgets(buffer, RECV_SIZE-1, stdin);  
  n = write(sockfd, buffer, strlen(buffer));
  if (n<0)
    error("ERROR reading from socket");
  printf("%s\n", buffer);

  close(sockfd);

  return 0;
}
