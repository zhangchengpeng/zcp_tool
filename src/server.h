#ifndef __SERVER_H_
#define __SERVER_H_

int init_signal();
int init_pid_file();
void force_exit();
int fork_child();

#endif