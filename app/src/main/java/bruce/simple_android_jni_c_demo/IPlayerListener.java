package bruce.simple_android_jni_c_demo;

/**
 * Created by shuh on 2018/12/25.
 */

public interface IPlayerListener {

    void setOnOneListener(OnOneListener listener);

    interface OnOneListener {
        void onOneTest(IPlayerListener test);
    }
}
