package bruce.simple_android_jni_c_demo;

/**
 * Created by shuh on 2018/12/25.
 */

public interface ITestDemo {

    void setOnTestListener(OnTestListener listener);

    interface OnTestListener {
        void onTest(ITestDemo test);
    }
}
