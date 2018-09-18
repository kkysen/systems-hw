#include "head.h"

char * read_story() {
  struct stat sb;
  stat("story", &sb);
  int fd;
  if ( (fd = open("story", O_RDONLY)) == -1 ) {
    printf("stackTrace: program not yet initialized, do ./control -c\n");
    exit(1);
  }
  int size = sb.st_size;
  char *s = calloc(1, size+1);
  read(fd, s, size);
  return s;
}

int main(int argc, char **argv) {
  int semid, shmid, fd;
  if (argc < 2) {
    printf("stackTrace: not enough arguments provided\n");
    return 1;
  }
  else if (!strcmp(argv[1], "-c")) {
    semid = semget(SEMKEY, 1, IPC_CREAT | IPC_EXCL | 0644);
    if (semid) {
      printf("semaphore created: %d\n", semid);
      union semun su;
      su.val = 1;
      semctl(semid, 0, SETVAL, su);
      shmid = shmget(SHMKEY, sizeof(int), IPC_CREAT | 0644);
      printf("shared memory created.\n");
      fd = open("story", O_CREAT | O_TRUNC, 0644);
      close(fd);
      printf("story file created (story)\n");
    }
    else {
      printf("semaphore already exists\n");
    }
  }
  else if (!strcmp(argv[1], "-v")) {
    char *story = read_story();
    printf("The story:\n\n%s\n", story);
    free(story);
  }
  else if (!strcmp(argv[1], "-r")) {
    if ( (semid = semget( SEMKEY, 1, 0)) == -1 ) {
      printf("stackTrace: program not yet initialized, do ./control -c\n");
      exit(1);
    }
    printf("waiting for access\n");
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_flg = SEM_UNDO;
    sb.sem_op = -1;
    semop( semid, &sb, 1 );
    semid = semget(SEMKEY, 1, 0);
    printf("semaphore removed: %d\n", semctl(semid, 0, IPC_RMID));
    shmid = shmget(SHMKEY, sizeof(int), 0);
    shmctl(shmid, IPC_RMID, 0);
    printf("shared memory removed\n");
    char *story = read_story();
    printf("The story:\n\n%s\n", story);
    free(story);
    remove("story");
  }
  else {
    printf("stackTrace: flag %s not recognized\n", argv[1]);
    return 1;
  }
  return 0;
}
