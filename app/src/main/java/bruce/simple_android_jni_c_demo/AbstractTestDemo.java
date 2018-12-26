package bruce.simple_android_jni_c_demo;

/**
 * Created by shuh on 2018/12/25.
 */

public abstract class AbstractTestDemo implements ITestDemo {
    private OnTestListener mOnTestListener;

    public final void setOnTestListener(OnTestListener listener) {
        mOnTestListener = listener;
    }

    public void resetListeners() {
        mOnTestListener = null;
    }

    protected final void notifyOnTest() {
        if (mOnTestListener != null)
            mOnTestListener.onTest(this);
    }
}
