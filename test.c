#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#include <netdb.h>
#include <time.h>

int sockUDP = -1;
int sockTCP = -1;
struct sockaddr_in adr;
char buf[65000];

int main (int argc, char * argv[]) {

  sockUDP = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockUDP < 0) {
    perror("socket UDP");
    exit(EXIT_FAILURE);
  }

  unsigned int len = sizeof(adr);
  adr.sin_addr.s_addr = INADDR_ANY;
  adr.sin_port = 0;
  adr.sin_family = AF_INET;
  if (bind(sockUDP, (struct sockaddr*)&adr, len) < 0) {
    perror("bind UDP");
    exit(EXIT_FAILURE);
  }  

  if (getsockname(sockUDP, (struct sockaddr*)&adr, &len) < 0) {
    perror("getsockname");
    exit(EXIT_FAILURE);
  }
  printf("Attente de connexion sur %s : %d\n",inet_ntoa(adr.sin_addr), ntohs(adr.sin_port));

  int opt = 1; 
  int ret = setsockopt(sockUDP, SOL_IP, IP_PKTINFO, &opt, sizeof opt);
  if (ret < 0) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  char tmp[100];
  struct cmsghdr *pcmsg;
  struct msghdr msg;
  struct sockaddr_in from;
  bzero(&msg, sizeof msg);
  msg.msg_name = &from;
  msg.msg_namelen = sizeof(from);
  msg.msg_control = tmp;
  msg.msg_controllen = sizeof(tmp);
  struct iovec io;
  io.iov_base = buf;
  io.iov_len = 65000;
  msg.msg_iov = &io;
  msg.msg_iovlen=1;
  len = recvmsg(sockUDP, &msg, 0);
  printf("len=%d data=%s\n",len,buf);
  for (pcmsg = CMSG_FIRSTHDR(&msg);
       pcmsg != NULL;
       pcmsg = CMSG_NXTHDR(&msg,pcmsg)) {
    if ((pcmsg->cmsg_level == SOL_IP) &&
	(pcmsg->cmsg_type == IP_PKTINFO)) {
      struct in_pktinfo *i = (struct in_pktinfo *) CMSG_DATA(pcmsg);
      adr.sin_addr = i->ipi_addr;
      break;
    }
  }
  printf("Connexion recue de %s: %d\n",inet_ntoa(from.sin_addr), ntohs(from.sin_port));
  printf("Connexion recue sur %s: %d\n",inet_ntoa(adr.sin_addr), ntohs(adr.sin_port));
  
  close(sockUDP);
  return 0;
}

