#include <sys/types.h>     /* key_t  */
#include <sys/ipc.h>       /* ftok   */
#include <sys/sem.h>       /* semget, semctl, semop */
#include <sys/stat.h>      /* stat, struct stat  */
#include <stdlib.h>        /* malloc */
#include <stdio.h>         /* perror, printf */
#include <errno.h>         /* errno */

#define PRJVAL  1

key_t cle(char *pathKey, int prj)
{
  key_t k;
  struct stat buf;

  // Q: rajouter ici l'appel � la fonction ftok(), et mettez la valeur de retour dans la variable retourn�e par la fonction 
  // --
  k = ftok(pathKey,prj);

  if (k==-1) perror("ftok");

/* Si fichier renomme ou deplace (dans le meme systeme),  */
/* la cle reste valide, sinon invalide                    */

  if (stat(pathKey, &buf)==-1) perror("stat");
  else printf("cle %d (dec) %x (hex) inode %x\n", k,k,(int)buf.st_ino);

  return k;
}

// fonction qui cr�e l'ensemble de s�maphores

int semCreat(char *pathKey, int nbSem, int val)
{
  int semid;
  key_t key;
  
  // Q: il faut r�cup�rer la cl� cr�ee dans la variable key -> appel � la fonction ftok
  //--
  key = ftok(pathKey,PRJVAL);
  
  if (key==-1) return -1;

  // appel � la fonction semget() et mettre la valeur de retour dans la variable semid
  //--
  semid = semget(key,nbSem,IPC_CREAT|0600);

  if (semid!=-1) {
                 unsigned short *values;

                 values=(unsigned short*)malloc(sizeof(unsigned short)*nbSem);
                 if (values!=NULL)
                 {
                  int s;
                  for (s=0; s<nbSem; s++) values[s]=val;
				  // le tableau values contient l'ensemble des valeur avec lesquels on veut initialiser les s�maphores
				  // faite un appel � la fonction semclt() pour initialiser les s�maphore avec les valeurs se trouvant dans le tableau values
				  // utilisez l'op�ration SETALL
				  // --
		  semctl(semid,s,SETALL);

                  free(values);
                 }
                 else
                 {
                  exit(-1);
                 }
  }
                  
  return semid;
}

int main(int argc,char ** argv)
{
 int nbSem, val;
 int semid;

 struct stat buf;
 
 if (argc!=4) { fprintf(stderr,"Usage: %s nomFichier nbSem val\n",argv[0]);
                return 1;
 }

 if (stat(argv[1],&buf)==-1) {
   fprintf(stderr,"%s n'est pas une reference!\n",argv[1]);
   return 1;
 }

 if (sscanf(argv[2],"%d",&nbSem)!=1) {
   fprintf(stderr,"%s n'est pas un entier!\n",argv[2]);
   return 1;
 }
 if (sscanf(argv[3],"%d",&val)!=1) {
   fprintf(stderr,"%s n'est pas un entier!\n",argv[3]);
   return 1;
 }
 // faire appel � la fonction semCreat avec comme argument le nom de fichier, le nombre de s�maphore et la valeur d'initialisation
 //-- 
 semCreat(argv[1],nbSem,val);
 if (semid==-1)
 {
  fprintf(stderr,"Erreur lors de la creation\n");
  return 1;
 }
 
 printf("semid obtenu:%d\n",semid);

 return 0;
}
