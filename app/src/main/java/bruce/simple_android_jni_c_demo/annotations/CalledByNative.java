package bruce.simple_android_jni_c_demo.annotations;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

/**
 * Created by shuh on 2018/12/28.
 */
@Target(ElementType.METHOD)
@Retention(RetentionPolicy.CLASS)
public @interface CalledByNative {
}
