#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(int argc, char *argv[])
{
  char str[20] = {0,};
  int fd = open("/a", O_RDWR | O_CREATE);
  write(fd, "hell", 4);
  lseek(fd, 3, SEEK_CUR);
  write(fd, "orld", 4);
  lseek(fd, 4, SEEK_SET);
  write(fd, "o w", 3);
  lseek(fd, 0, SEEK_END);
  write(fd, "!", 2);
  lseek(fd, 0, SEEK_SET);
  read(fd, str, 13);
  printf(1, "%s\n", str);
  exit();
}
