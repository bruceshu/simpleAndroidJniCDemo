package bruce.simple_android_jni_c_demo;

import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;

import java.lang.ref.WeakReference;

import bruce.simple_android_jni_c_demo.annotations.AccessedByNative;
import bruce.simple_android_jni_c_demo.annotations.CalledByNative;

/**
 * Created by shuh on 2018/12/11.
 */

public class TestDemo extends AbstractTestDemo{
    private final static String TAG = "bruce-android";

    private static final int MEDIA_NOP = 0;

    private static final int MEDIA_INFO = 200;

    @AccessedByNative
    private long mNativeTestDemo;

    private static EventHandler mEventHandler;

    private static volatile boolean mIsLibLoaded = false;
    public static void loadLibrariesOnce() {
        synchronized (TestDemo.class) {
            if (!mIsLibLoaded) {
                System.loadLibrary("sdl");
                System.loadLibrary("test");
                mIsLibLoaded = true;
            }
        }
    }

    private void initTestDemo() {
        loadLibrariesOnce();

        Looper looper;
        if ((looper = Looper.myLooper()) != null) {
            mEventHandler = new EventHandler(this, looper);
        } else if ((looper = Looper.getMainLooper()) != null) {
            mEventHandler = new EventHandler(this, looper);
        } else {
            mEventHandler = null;
        }

        _native_setup(new WeakReference<TestDemo>(this));
    }

    public TestDemo() {
        initTestDemo();
    }

    public void native_begin() {
        _native_begin();
    }

    public void native_end() {
        _native_end();
    }

    public void test_print() {
        Log.i(TAG, "test_print: hello bruce");
    }

    public void native_release() {
        _native_release();
    }

    @CalledByNative
    private static void postEventFromNative(Object weakThiz, int what, int arg1, int arg2, Object obj) {
        if (weakThiz == null)
            return;

        TestDemo test = (TestDemo) ((WeakReference) weakThiz).get();
        if (test == null) {
            return;
        }

        if (what == MEDIA_NOP) {
            test.test_print();
        }

        if (test.mEventHandler != null) {
            Message m = test.mEventHandler.obtainMessage(what, arg1, arg2, obj);
            test.mEventHandler.sendMessage(m);
        }
    }

    private static class EventHandler extends Handler {
        private final WeakReference<TestDemo> mTestDemo;
        public EventHandler(TestDemo test, Looper looper) {
            super(looper);
            mTestDemo = new WeakReference<TestDemo>(test);
        }

        @Override
        public void handleMessage(Message msg) {
            TestDemo test = mTestDemo.get();
            switch (msg.what) {
                case MEDIA_NOP:
                    test.notifyOnTest();
                    return;
                default:
                    Log.e(TAG, "Unknown message type " + msg.what);
            }
        }
    }

    private native void _native_setup(Object TestDemo_this);
    private native void _native_begin();
    private native void _native_end();
    private native void _native_release();
}
