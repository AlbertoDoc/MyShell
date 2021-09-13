#ifndef SYSTEMFUNCTIONS_H
#define SYSTEMFUNCTIONS_H

void startProcess(char *argv[], int argc);
void waitProcess();
void killProcess(pid_t pid);
void runProcess(char *argv[], int argc);

#endif
