package bruce_base.simple_android_jni_c_demo;

/**
 * Created by shuh on 2018/12/11.
 */

public class test {

    public void native_begin() {
        _native_begin();
    }

    private native void _native_begin();
}
