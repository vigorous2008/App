package cn.iviking.app.jni;

/**
 * Created by wangzhongqiang on 2017/10/17.
 */

public class Detector {
    static {
       System.loadLibrary("watermark");
    }

    /**
     * 用于测试
     * @return 返回字符串 "IVIKING"
     */
    public native String getString();

    /**
     * @param audioData 音频PCM数据
     * @param sf 采样率
     * @param length 数据长度
     * @param p2 扩展参数
     * @param p3 扩展参数
     * @return 返回音频数据中提取出的水印
     */

    public native byte[] getSymbol(byte[] audioData, long sf, long length, String p2,String p3);
}
