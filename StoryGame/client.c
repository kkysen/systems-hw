#include "head.h"

int main() {
  int fd, semid, shmid;
  if ( (semid = semget( SEMKEY, 1, 0)) == -1 ) {
    printf("error: program not yet initialized, do ./control -c\n");
    exit(1);
  }
  printf("waiting for access\n");
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1;
  semop( semid, &sb, 1 );
  printf("successfully entered\n");
  fd = open("story", O_APPEND | O_RDWR);
  shmid = shmget( SHMKEY, sizeof(int), 0);
  int *size = shmat( shmid, 0, 0 );
  char *story = (char *)calloc(1, *size + 1);
  lseek(fd, -1 * *size, SEEK_END);
  read(fd, story, *size);
  printf("The last addition:\n\n%s\n", story);
  char line[1024];
  printf("Enter your own addition: ");
  fgets( line, sizeof(line), stdin );
  *size = strlen(line);
  lseek( fd, 0, SEEK_END );
  write( fd, line, strlen(line) );
  shmdt(size);
  sb.sem_op = 1;
  semop( semid, &sb, 1 );
  free(story);
  return 0;
}
