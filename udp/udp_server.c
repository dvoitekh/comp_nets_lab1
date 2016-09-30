#include "../things.h"

int main() {
  bool data_buff_bool[DATA_NUM_BOOL];
  int data_buff_int[DATA_NUM_INT];
  int i, j;
  int udp_sock;
  fd_set fds;
  struct timeval time_val;
  struct sockaddr_in saddr_in;
  udp_sock = socket(PF_INET,SOCK_DGRAM,0);
  saddr_in.sin_family = AF_INET;
  saddr_in.sin_addr.s_addr = INADDR_ANY;
  saddr_in.sin_port = htons(PORT);
  bind(udp_sock, (struct sockaddr *) &saddr_in, sizeof(saddr_in));

  while(1) {
    FD_ZERO(&fds);
    FD_SET(udp_sock, &fds);
    time_val.tv_usec = 0;
    time_val.tv_sec = TIV_SEC;

    if(select(udp_sock + 1, &fds, NULL, NULL, &time_val) > 0) {
      clock_t begin = clock();
      i = recvfrom(udp_sock, data_buff_bool, sizeof(bool) * DATA_NUM_BOOL, 0, NULL, NULL);
      j = recvfrom(udp_sock, data_buff_int, sizeof(int) * DATA_NUM_INT, 0, NULL, NULL);
      clock_t end = clock();
      double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
      printf("Number of recived bytes = %d.\n", i+j);
      for(i = 0; i < DATA_NUM_BOOL; i++) {
        printf("num - %d -> value - %d\n", i + 1, data_buff_bool[i]);
      }
      for(i = 0; i < DATA_NUM_INT; i++) {
        printf("num - %d -> value - %d\n", i + 1, data_buff_int[i]);
      }
      printf("Time = %f.\n", time_spent);
    }
  }

  close(udp_sock);
  return 0;
}
