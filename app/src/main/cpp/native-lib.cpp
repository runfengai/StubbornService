#include <jni.h>
#include <string>
#include <signal.h>
#include "native-lib.h"

int user_id;
int sdk_version;

//子进程变成僵尸进程会调用这个方法
void sig_handler(int sino) {
//
    int status;
//    阻塞式函数
    LOGE("等待死亡信号");
    wait(&status);

    LOGE("创建进程");
    create_child();

}

extern "C"
JNIEXPORT void JNICALL
Java_com_jarry_lsn20_Watcher_createWatcher(JNIEnv *env, jobject instance, jint userId, jint sdk) {
//    父进程
    user_id = userId;
    sdk_version = sdk;

//    //为了防止子进程被弄成僵尸进程，如果没有重启生效，可以开放此段代码    1
//    struct sigaction sa;
//    sa.sa_flags = 0;
//    sa.sa_handler = sig_handler;
//    sigaction(SIGCHLD, &sa, NULL);
    create_child();
}

void create_child() {

    pid_t pid = fork();
//
    if (pid < 0) {

    } else if (pid > 0) {
//父进程
    } else if (pid == 0) {
        LOGE("子进程开启 ");
//        开启线程轮询
        child_start_monitor();
    }

}

//相当于java  run方法
void *thread_rt(void *data) {
    pid_t pid;
    while ((pid = getppid()) != 1) {
        sleep(2);
        LOGE("循环 %d ", pid);
    }
//    父进程等于1  apk被干掉了
    LOGE("重启父进程");
    if (sdk_version < 17)
        execlp("am", "am", "startservice",
               "com.jarry.lsn20/com.jarry.lsn20.MyService", (char *) NULL);
    else
        execlp("am", "am", "startservice", "--user", user_id,
               "com.jarry.lsn20/com.jarry.lsn20.MyService", (char *) NULL);
}

void child_start_monitor() {
    pthread_t tid;
    pthread_create(&tid, NULL, thread_rt, NULL);
}
