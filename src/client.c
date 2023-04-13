#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE 256

// Global Variables
int socket_id;
int port;
// END Global Variables

// Function prototypes
int connectToSocket(char* host);
void printUsage();
// END prototypes list

int connectToSocket(char* host) {
  struct hostent *hp;
  struct sockaddr_in sin;
  /* translate host name into peer's IP address */
  hp = gethostbyname(host);
  if (!hp) {
    fprintf(stderr, "client: unknown host: %s\n", host);
    exit(1);
  }

  /* build address data structure */
  bzero((char *)&sin, sizeof(sin));
  sin.sin_family = AF_INET;
  bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length);
  sin.sin_port = htons(port);

  /* active open */
  if ((socket_id = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    perror("client: socket error");
    exit(1);
  }
  if (connect(socket_id, (struct sockaddr *)&sin, sizeof(sin)) < 0)
  {
    perror("client: connect error");
    close(socket_id);
    exit(1);
  }
  return socket_id;
}

void printUsage(){
  fprintf(stderr, "usage: client <server-hostname> <portnum>\n");
  fprintf(stderr, "  Ex: client localhost 12345\n");
  fprintf(stderr, "    Connect to a server running on the localhost at port 12345\n");
}

int main(int argc, char * argv[])
{
  char *host;
  char buf[MAX_LINE];
  int len;

  // Read in Command Line Args
  if (argc == 3) {
    host = argv[1];
    port = atoi(argv[2]);
  } else {
    printUsage();
    exit(1);
  }

  connectToSocket(host);

  /* main loop: get and send lines of text */
  while (fgets(buf, sizeof(buf), stdin)) {
    buf[MAX_LINE-1] = '\0';
    len = strlen(buf) + 1;
    send(socket_id, buf, len, 0);
  }
}