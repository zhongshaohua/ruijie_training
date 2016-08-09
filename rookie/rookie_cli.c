#include <app/cli/cli_transtion.h>
#include <stdio.h>
#include <pthread.h>
#include <app/cli/cli_transtion.h>
#undef ALTERNATE
#define ALTERNATE no_alt
#include "rookie_cli.h"
//#include "hash.c"

void exec_rookie_route_algorithm_cmd(struct_command_data_block *pcdb)
{
    cli_printf("exec_rookie_route_algorithm_cmd\n");
}

void exec_rookie_route_add_cmd(struct_command_data_block *pcdb)
{

}

void exec_rookie_route_agetime_cmd(struct_command_data_block *pcdb)
{

}
APPEND_POINT(exec_rookie_append, exec_rookie);

void cli_rookie_init()
{
    if (cli_add_command(PARSE_ADD_EXEC_TOP_CMD, &TNAME(exec_rookie_append), "exec rookie") )
	printf("add commad\n");
    else 
        printf("add command failed\n");
    return;
}

extern void cli_rookie_init();

static void *cli_thread_func(void *arg)
{
    /* 创建一个伪线程管理器 */
    struct rg_thread_master *master;
    struct rg_thread thread;
    int rv;
    prctl(PR_SET_NAME, (unsigned long)"rookie");
    pthread_detach(pthread_self());
    
    master = rg_thread_master_create();
    if (master == NULL) {
        printf("dbg_master is NULL, rg_thread_master_create ERROR !!!");
        return NULL;
    }

    /* CLI客户端初始化函数 */
    rv = cli_client_init("rookie", master);
    if (rv < 0) {
        printf("cli_client_init error\n");
        return NULL;
    }

    cli_rookie_init();
   // printf("rooke init finisheddddddd\n");
    rv = cli_client_ready();
    if (rv != 0) {
        printf("cli_client_ready error\n");
        return NULL;
    }

    while (rg_thread_fetch(master, &thread)) {
        rg_thread_call(&thread);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    int ret;
    pthread_t cli_thread;

    printf("run echo server!\r\n");
    daemon(1, 1);

    /* CLI init */
    ret = pthread_create(&cli_thread, NULL, cli_thread_func, NULL);
    if (ret != 0) {
        exit(1);
    }
    pthread_detach(cli_thread);

    /* to do */
    while (1) {
        ;
    }

    return 0;
}