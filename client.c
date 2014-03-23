#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>


void main(int argc, char** argv){

	struct data_send{       //structure qui va accueillir les données à envoyer
		long arg1;
		char op;
		long arg2;
		long result;
	}data_send;

	struct data_send donnee;
	donnee.arg1 = 1;
	donnee.arg2 = 2;
	donnee.op = '+';
	int s;
	struct sockaddr_in server;

	
	s = socket(AF_INET, SOCK_STREAM, 0);  //on obtient la socket
	if (s < 0){perror("erreur socket");}
	//sleep(2);

	
	server.sin_family = AF_INET;
	server.sin_port = htons(1025);
	server.sin_addr.s_addr = inet_addr("192.168.1.164");

	
	if(connect(s, (struct sockaddr*)&server, sizeof(server))<0) //on connecte
		perror("connection failed");
	printf("test1\n");
	if(write(s, &donnee, sizeof(donnee))<0) //on envoie le message
		perror("You shall not pass");
	printf("test2\n");
	
	if(read(s, &donnee, sizeof(donnee))<0)  //on lit le resultat
		perror("Apprends a lire");
		
	printf("%ld\n", donnee.result);


	close(s);
}
