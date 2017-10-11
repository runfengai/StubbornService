# StubbornService
ndk实现守护进程，仿杀死率较高.
原理是通过fork子进程，并用子进程检测其父进程的pid是否为1，即检测ppid是否为1，如果为1表示父进程变为init进程，即原父进程被杀死，此时通过am命令重启服务即可。完成进程守护。
由于有些设备厂商禁掉了am的功能，导致重启可能会失效。
使用方式如下：
1.运行apk
    会生成2个进程，可以通过
    adb shell
    ps|grep jarry.lsn20
u0_a70    30536 127   530644 19964 ffffffff 4003df24 S com.jarry.lsn20
u0_a70    30557 30536 0      0     c013431c 00000000 Z com.jarry.lsn20
查看到有2个进程（父、子）
2.尝试杀死父进程，测试是否重启成功。
    (1)通过命令行：kill -9 30536
    发现通过 ps|grep jarry.lsn20
    apk重启成功：
root@android:/ # ps|grep jarry.lsn20
u0_a70    30536 127   530644 19964 ffffffff 4003df24 S com.jarry.lsn20
u0_a70    30557 30536 0      0     c013431c 00000000 Z com.jarry.lsn20
root@android:/ # kill -9 30536
root@android:/ # ps|grep jarry.lsn20
1|root@android:/ # ps|grep jarry.lsn20
u0_a70    21429 127   473104 18472 ffffffff 4003df24 S com.jarry.lsn20
u0_a70    21453 21429 0      0     c013431c 00000000 Z com.jarry.lsn20


