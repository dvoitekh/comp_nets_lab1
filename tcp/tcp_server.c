#include "../things.h"

int main() {
  bool data_buff_bool[DATA_NUM_BOOL];
  int data_buff_int[DATA_NUM_INT];
  int i, j;
  int tcp_sock;
  int curr_sock;
  fd_set fds;
  struct timeval time_val;
  struct sockaddr_in saddr_in;
  tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
  saddr_in.sin_family = AF_INET;
  saddr_in.sin_addr.s_addr = INADDR_ANY;
  saddr_in.sin_port = htons(PORT);
  bind(tcp_sock, (struct sockaddr *) &saddr_in, sizeof(saddr_in));
  listen(tcp_sock, 1);

  while(1) {
    curr_sock = accept(tcp_sock, NULL, 0);
    FD_ZERO(&fds);
    FD_SET(curr_sock, &fds);
    time_val.tv_sec = TIV_SEC;
    time_val.tv_usec = 0;

    if(select(curr_sock + 1, &fds, NULL, NULL, &time_val) > 0) {
      clock_t begin = clock();
      i = read(curr_sock, data_buff_bool, sizeof(bool) * DATA_NUM_BOOL);
      j = read(curr_sock, data_buff_int, sizeof(int) * DATA_NUM_INT);
      clock_t end = clock();
      double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
      printf("Number of recived bytes = %d\n", i);
      for(i = 0; i < DATA_NUM_BOOL; i++) {
        printf("num - %d -> value - %d\n", i + 1, data_buff_bool[i]);
      }
      for(i = 0; i < DATA_NUM_INT; i++) {
        printf("num - %d -> value - %d\n", i + 1, data_buff_int[i]);
      }
      printf("Time = %f.\n", time_spent);
    }
    close(curr_sock);
  }

  close(tcp_sock);
  return 0;
}
