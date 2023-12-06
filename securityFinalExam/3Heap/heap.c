#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>

struct auth {
  char name[33];
  int auth;
} auth;

struct auth *authVar;
char *service;

int main(int argc, char **argv)
{
  char line[128];

  while(1) {
      printf("[ auth = %p, service = %p ]\n", authVar, service);

      if(fgets(line, sizeof(line), stdin) == NULL) break;

      if(strncmp(line, "auth ", 5) == 0) {
          authVar = malloc(sizeof(auth));
          memset(authVar, 0, sizeof(auth));
          if(strlen(line + 5) < 32) {
              printf("Its len [%d]\n", strlen(line + 5));
              strcpy(authVar->name, line + 5);
          }
      }
      if(strncmp(line, "reset", 5) == 0) {
          free(authVar);
      }
      if(strncmp(line, "service", 7) == 0) {
          service = strdup(line + 7);
          printf("Hello, lens [%d]\n", strlen(line + 7));
      }
      if(strncmp(line, "login", 5) == 0) {
          if(authVar->auth) {
              printf("you have logged in already!\n");
          } else {
              printf("please enter your password\n");
          }
      }
  }
 }
