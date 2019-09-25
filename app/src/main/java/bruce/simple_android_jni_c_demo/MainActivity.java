package bruce.simple_android_jni_c_demo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "bruce-android";

    Player mTestDemo = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Player.loadLibrariesOnce();

        mTestDemo = createTestDemo();

        mTestDemo.setOnOneListener(mTestListener);
        mTestDemo.prepare();
        mTestDemo.sendMessageBegin();
        mTestDemo.sendMessageEnd();
    }

    private Player createTestDemo() {
        Player mTest = new Player();
        return mTest;
    }

    @Override
    public void onBackPressed() {
        Log.d(TAG, "onBackPressed: ");
        super.onBackPressed();
    }

    @Override
    protected void onDestroy() {
        mTestDemo.native_release();
        super.onDestroy();
    }

    IPlayerListener.OnOneListener mTestListener = new IPlayerListener.OnOneListener() {
        public void onOneTest(IPlayerListener test) {
            Log.i(TAG, "onTest: receive test listener");
        }
    };
}
