#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char** argv){

	struct data_send{       //structure qui va accueillir les données à envoyer
		long arg1;
		char op;
		long arg2;
		long result;
	}data_send;

	struct data_send donnee;
	int s;
	int sock_name;
	int sock_accept;
	struct sockaddr_in server;
	int test=sizeof(server);
	int test2 = sizeof(server);

	s = socket(AF_INET, SOCK_STREAM, 0);  //on obtient la socket
	if (s < 0){perror("erreur socket");}
	printf("sleep 1\n");	

	
	server.sin_family = AF_INET;				//on définit l'addresse sur laquelle se connecter
	server.sin_port = htons(1025);
	server.sin_addr.s_addr = inet_addr("192.168.1.164");

	if(bind(s, (struct sockaddr*)&server, sizeof(server))<0)
		perror("bind impossible");
	printf("sleep 1\n");

	
	if(listen(s, 3)<0)				//on écoute le réseau et attend des clients
		perror("listen impossible");
	printf("Balance ton flow\n");
	

	while(1){
		sock_accept = accept(s, (struct sockaddr*)&server, &test2);
		if(sock_accept < 0) {perror("non accepté");}
		if (fork() == 0){   //fils
			int l=1;
			while(l>0){
				l=read(sock_accept, &donnee, sizeof(donnee));
				printf("donnée lue\n");
				printf("%ld\n", donnee.arg1);
				printf("%c\n", donnee.op);
				printf("%ld\n", donnee.arg2);

				switch(donnee.op){       //on calcule le resultat
					case '+':
						donnee.result = donnee.arg1 + donnee.arg2;
						break;
					case '-':
						donnee.result = donnee.arg1 - donnee.arg2;
						break;
					case '*':
						donnee.result = donnee.arg1 * donnee.arg2;
						break;
					case '/':
						donnee.result = donnee.arg1 / donnee.arg2;
						break;
				}
							
				if(write(sock_accept, &donnee, sizeof(donnee))<0) //on envoi le message
					perror("peux pas écrire");
			}

			close(sock_accept);	
			break; // on ne fait pas d'accept...
		}

		else{  //père
		close(sock_accept);
		}
	}
	close(s);
}
