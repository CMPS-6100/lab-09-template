#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_PENDING  5
#define MAX_LINE     256

// Global Variables
int passive_open_socket;
int port;
// END Global Variables

// Function prototypes
int performPassiveOpen(struct sockaddr_in* sin);
void printUsage();
// END prototypes list

int performPassiveOpen(struct sockaddr_in* sin) {
  /* build address data structure */
  bzero((char *)sin, sizeof(*sin));
  sin->sin_family = AF_INET;
  sin->sin_addr.s_addr = INADDR_ANY;
  sin->sin_port = htons(port);

  /* setup passive open */
  if ((passive_open_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    perror("server: socket error");
    exit(1);
  }
  if ((bind(passive_open_socket, (struct sockaddr *)sin, sizeof(*sin))) < 0) {
    perror("server: bind error");
    exit(1);
  }
  listen(passive_open_socket, MAX_PENDING);
}

void printUsage(){
  fprintf(stderr, "Usage: server <portnum>\n");
  fprintf(stderr, "  Ex: server 12345\n");
  fprintf(stderr, "    Start the server connected to port 12345\n");
}

int main(int argc, char* argv[])
{
  struct sockaddr_in sin;
  char buf[MAX_LINE];
  int buf_len, addr_len;
  int new_s;

  // Read in port number
  if(argc == 2) {
    port = atoi(argv[1]);
  } else {
    printUsage();
    exit(1);
  }

  performPassiveOpen(&sin);

 /* wait for connection, then receive and print text */
  while(1) {
    if ((new_s = accept(passive_open_socket, (struct sockaddr *)&sin, &addr_len)) < 0) {
      perror("server: accept error");
      exit(1);
    }
    while (buf_len = recv(new_s, buf, sizeof(buf), 0))
      fputs(buf, stdout);
    close(new_s);
  }
}
