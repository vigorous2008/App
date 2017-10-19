package cn.iviking.app.jni;

/**
 * Created by wangzhongqiang on 2017/10/17.
 */

public class JNIUtils {
    static {
       System.loadLibrary("watermark");
//        System.loadLibrary("FFTW");
    }

    //java调C中的方法都需要用native声明且方法名必须和c的方法名一样
    public native String getString();

    //java调C中的方法都需要用native声明且方法名必须和c的方法名一样
    public native String getSymbol(byte[] data, String sf, String p1, String p2,String p3);
}
