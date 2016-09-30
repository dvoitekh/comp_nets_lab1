#include "../things.h"

int main() {
  bool data_buff_bool[DATA_NUM_BOOL];
  int data_buff_int[DATA_NUM_INT];
  int i, j;
  int udp_sock;
  fd_set fds;
  struct timeval time_val;
  struct sockaddr_in saddr_in;
  struct in_addr in_a;
  saddr_in.sin_family = AF_INET;
  saddr_in.sin_port = htons(PORT);
  inet_aton(IP_ADDR, &in_a);
  saddr_in.sin_addr = in_a;
  udp_sock = socket(PF_INET, SOCK_DGRAM, 0);
  FD_ZERO(&fds);
  FD_SET(udp_sock, &fds);
  time_val.tv_sec = TIV_SEC;
  time_val.tv_usec = 0;
  bool bool_array[2] = {true, false};
  for(i = 0; i < DATA_NUM_BOOL; i++) {
    data_buff_bool[i] = bool_array[rand() % 2];
  }
  for(i = 0; i < DATA_NUM_INT; i++) {
    data_buff_int[i] = rand() % 100;
  }

  if(select(udp_sock + 1, NULL, &fds, NULL, &time_val) > 0) {
    clock_t begin = clock();
    i = sendto(udp_sock, data_buff_bool, sizeof(bool) * DATA_NUM_BOOL, 0, (struct sockaddr *)&saddr_in, sizeof(saddr_in));
    j = sendto(udp_sock, data_buff_int, sizeof(int) * DATA_NUM_INT, 0, (struct sockaddr *)&saddr_in, sizeof(saddr_in));
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Number of send bytes = %d.\n", i+j);
    printf("Time = %f.\n", time_spent);
  }

  close(udp_sock);
  return 0;
}
