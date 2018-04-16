#include <sys/types.h>     /* key_t  */
#include <sys/ipc.h>       /* ftok   */
#include <sys/sem.h>       /* semget, semctl, semop */
#include <sys/stat.h>      /* stat, struct stat  */
#include <stdlib.h>        /* malloc */
#include <stdio.h>         /* perror, printf */
#include <errno.h>         /* errno */

#define PRJVAL  1

int P(int semid, int noSem){
	while()
}

int V(int semid, int noSem){
	while()
}


int main(){
	key = ftok(pathKey,PRJVAL);
	semget(
	semctl(semid,nbSem,RMID);
	return 0;
}
