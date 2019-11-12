#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

void print_arr(int *arr, size_t len) {
  int i = 0;

  for(; i < len; i++) {
    printf("\trandom %d: %d\n", i, *arr++);
  }
  printf("\n");
}

int my_open(char *filename, int flag) {
  int ans = open(filename, flag);
  if(ans < 0) printf("error %d: %s\n", errno, strerror(errno));
  return ans;
}

int my_new_file_open(char *filename, int flag, int permissions) {
  int ans = open(filename, flag, permissions);
  if(ans < 0) ans = my_open(filename, O_WRONLY);
  return ans;
}

int my_read(int file, int *buffer, int size) {
  int ans = read(file, buffer, size);
  if(ans < 0) printf("error %d: %s\n", errno, strerror(errno));
  return ans;
}

int my_write(int file, int *buffer, int size) {
  int ans = write(file, buffer, size);
  if(ans < 0) printf("error %d: %s\n", errno, strerror(errno));
  return ans;
}

int main() {
  int devrandom = my_open("/dev/random", O_RDONLY);
  int newfile = my_new_file_open("newRand", O_CREAT | O_EXCL | O_WRONLY, 0644);
  int newfile_read = my_open("newRand", O_RDONLY);
  int randarr1[10];
  int randarr2[10];

  //read(randfile, randarr1, 10 * sizeof(int));
  printf("Generating random numbers:\n");
  my_read(devrandom, randarr1, 10 * sizeof(int));
  print_arr(randarr1, 10);

  printf("Writing numbers to file...\n\n");
  my_write(newfile, randarr1, 10 * sizeof(int));

  printf("Verification that written values were the same:\n");
  my_read(newfile_read, randarr2, 10 * sizeof(int));
  print_arr(randarr2, 10);

  close(devrandom);
  close(newfile);
  close(newfile_read);
  return 0;
}
