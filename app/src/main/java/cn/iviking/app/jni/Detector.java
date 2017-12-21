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
     * @param audioData PCM数据buff，注意，不能有WAVE头信息
     * @param length pcm数据的长度，单位是BYTE
     * @param sf 采样率，必须为48000或44100
     * @param jBitsPerSample 采样深度，必须为16
     * @param p3 扩展参数
     * @return 返回音频数据中提取出的水印
     */

    public native byte[] getSymbol(byte[] audioData, long length, long sf, long jBitsPerSample,String p3);
}
