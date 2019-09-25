package bruce.simple_android_jni_c_demo;

/**
 * Created by shuh on 2018/12/25.
 */

public abstract class AbstractPlayerListener implements IPlayerListener {
    private OnOneListener mOnOneListener;

    public final void setOnOneListener(OnOneListener listener) {
        mOnOneListener = listener;
    }

    public void resetListeners() {
        mOnOneListener = null;
    }

    protected final void notifyOnTest() {
        if (mOnOneListener != null)
            mOnOneListener.onOneTest(this);
    }
}
