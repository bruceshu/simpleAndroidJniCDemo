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

public class Player extends AbstractPlayerListener{
    private final static String TAG = "bruce-android";

    private static final int MEDIA_NOP = 0;
    private static final int MEDIA_INFO = 200;

    @AccessedByNative
    private long mNativeTestDemo;

    private static EventHandler mEventHandler;

    private static volatile boolean mIsLibLoaded = false;
    private static void loadLibrariesOnce() {
        synchronized (Player.class) {
            if (!mIsLibLoaded) {
                System.loadLibrary("sdl");
                System.loadLibrary("test");
                mIsLibLoaded = true;
            }
        }
    }

    private void initPlayer() {
        loadLibrariesOnce();

        Looper looper;
        if ((looper = Looper.myLooper()) != null) {
            Log.d(TAG, "initTestDemo: Looper.myLooper()：" + Looper.myLooper());
            mEventHandler = new EventHandler(this, looper);
        } else if ((looper = Looper.getMainLooper()) != null) {
            Log.d(TAG, "initTestDemo: Looper.getMainLooper():" + Looper.getMainLooper());
            mEventHandler = new EventHandler(this, looper);
        } else {
            mEventHandler = null;
        }

        _native_setup(new WeakReference<Player>(this));
    }

    public Player() {
        initPlayer();
    }

    public void native_release() {
        resetListeners();
        _native_release();
    }

    public void prepare() {
        _prepare();
    }
    public void start() {
        _start();
    }

    public void pause() {
        _pause();
    }

    public void stop() {
        _stop();
    }

    public void setVolume(int left, int right) {
        _setVolume(left, right);
    }

    public void setMute() {
        _setVolume(0, 0);
    }


    public void resetListeners() {
        super.resetListeners();
    }

    @CalledByNative
    private static void postEventFromNative(Object weakThiz, int what, int arg1, int arg2, Object obj) {
        if (weakThiz == null)
            return;

        Player player = (Player) ((WeakReference) weakThiz).get();
        if (player == null) {
            return;
        }

        if (player.mEventHandler != null) {
            Message m = player.mEventHandler.obtainMessage(what, arg1, arg2, obj);
            player.mEventHandler.sendMessage(m);
        }
    }

    private static class EventHandler extends Handler {
        private final WeakReference<Player> mPlayer;
        public EventHandler(Player player, Looper looper) {
            super(looper);
            mPlayer = new WeakReference<Player>(player);
        }

        @Override
        public void handleMessage(Message msg) {
            Player player = mPlayer.get();
            switch (msg.what) {
                case MEDIA_NOP:
                    Log.d(TAG, "handleMessage: MEDIA_NOP=" + MEDIA_NOP);
                    player.notifyOnTest();
                    break;
                case MEDIA_INFO:
                    Log.d(TAG, "handleMessage: MEDIA_INFO" + MEDIA_INFO);
                    break;
                default:
                    Log.e(TAG, "Unknown message type " + msg.what);
            }
        }
    }

    private native void _native_setup(Object Player_this);
    private native void _native_release();
    private native void _prepare();
    private native void _start();
    private native void _pause();
    private native void _stop();
    private native void _setVolume(int left, int right);
}
