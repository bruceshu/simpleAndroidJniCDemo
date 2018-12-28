package bruce.simple_android_jni_c_demo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "bruce-android";

    TestDemo mTestDemo = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        TestDemo.loadLibrariesOnce();

        mTestDemo = createTestDemo();

        mTestDemo.setOnTestListener(mTestListener);
        mTestDemo.native_begin();
        mTestDemo.native_end();
    }

    private TestDemo createTestDemo() {
        TestDemo mTest = new TestDemo();
        return mTest;
    }

    @Override
    public void onBackPressed() {
        mTestDemo.native_release();
    }

    ITestDemo.OnTestListener mTestListener = new ITestDemo.OnTestListener() {
        public void onTest(ITestDemo test) {
            Log.i(TAG, "onTest: receive test listener");
        }
    };
}
