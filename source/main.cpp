/**
****************************************************************************************
* @author: PND
* @date: 2023-04-17
* @file: main.c
* @brief: mtce
*****************************************************************************************
**/
#include <stdio.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#include "app.h"
#include "app_dbg.h"

static int bRun = true;

void exit_handler(int signal)
{
    bRun = false;
    APP_PRINT("Exit app");
    app_stop();
}

int main(void)
{
    signal(SIGINT, exit_handler);
    signal(SIGQUIT, exit_handler);
    signal(SIGTERM, exit_handler);
    signal(SIGKILL, exit_handler);

    int ret;

    ret = app_init();
    if (ret != 0)
    {
        APP_ERR("init app failed");
        bRun = false;
    }

    ret = app_start();
    if (ret != 0)
    {
        APP_ERR("start app failed");
        bRun = false;
    }

    while (bRun)
    {

        usleep(1000);
    }

    app_release();
    APP_PRINT("Realse main success\n");

    return 0;
}
