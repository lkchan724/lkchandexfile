package com.lkchan.dexfile;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import java.io.File;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("lkchandexfile");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);


        File file = new File("/mnt/sdcard/app-debug.apk");
        if (file.exists() && file.canRead()) {
            tv.setText(getApkdexInfo(file.getAbsolutePath()));
        } else {
            tv.setText("no apk file !!!");
        }
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */

    public native String getApkdexInfo(String path);
}
