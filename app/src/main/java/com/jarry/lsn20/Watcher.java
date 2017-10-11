package com.jarry.lsn20;

/**
 * Created by zhengxr on 2017/10/11.
 */

public class Watcher {
    static {
        System.loadLibrary("native-lib");
    }


    public native void createWatcher(int uId);
}
