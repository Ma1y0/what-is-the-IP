#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  struct addrinfo hint, *res;
  char ipstr[INET6_ADDRSTRLEN];

  // Validates arguments
  if (argc != 2) {
    fprintf(stderr, "USAGE: whatIsTheeIP hostname\n");

    return 1;
  }

  // Sets hints
  memset(&hint, 0, sizeof(hint)); // Makes sure that hint is empty -- Why is shouldn't be empty?
  hint.ai_family = AF_UNSPEC; // IPv4 or IPv6
  hint.ai_socktype = SOCK_STREAM; // TCP

  int result;
  if ((result = getaddrinfo(argv[1], NULL, &hint, &res)) != 0) {
    fprintf(stderr, "getaddrinfo ERROR: %s\n", gai_strerror(result));

    return 2;
  }

  printf("IP adresses of %s\n\n", argv[1]);

  while (res != NULL) {
    void *addr;
    char *ipver;

    if (res->ai_family == AF_INET) {
      // IPv4
      struct sockaddr_in *ipv4 = (struct sockaddr_in *)res->ai_addr;
      addr = &(ipv4->sin_addr);
      ipver = "IPv4";
    } else {
      // IPv6
      struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)res->ai_addr;
      addr = &(ipv6->sin6_addr);
      ipver = "IPv6";
    }

    inet_ntop(res->ai_family, addr, ipstr, sizeof(ipstr));
    printf("%s: %s\n", ipver, ipstr);

    res = res->ai_next;
  }

  freeaddrinfo(res);

  return 0;
}
