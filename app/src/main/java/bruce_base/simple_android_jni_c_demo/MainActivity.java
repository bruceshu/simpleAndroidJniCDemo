package bruce_base.simple_android_jni_c_demo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity {
    test mtest;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        test.loadLibrariesOnce();
        mtest.native_begin();
    }
}
