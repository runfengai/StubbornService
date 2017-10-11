package com.jarry.lsn20;

import android.app.Service;
import android.content.Intent;
import android.os.Build;
import android.os.IBinder;
import android.os.Process;
import android.util.Log;

public class MyService extends Service {
    public MyService() {
    }

    public static final String TAG = "tuch";

    @Override
    public void onCreate() {
        super.onCreate();
        Watcher watcher = new Watcher();
        Log.e(TAG, "Process.myUid()=" + Process.myUid());
        watcher.createWatcher(Process.myUid(), Build.VERSION.SDK_INT);
    }

    @Override
    public IBinder onBind(Intent intent) {
        throw new UnsupportedOperationException("Not yet implemented");
    }
}
