package cn.iviking.app.audio;

/**
 * Created by wangzhongqiang on 2017/10/19.
 */



import java.io.IOException;
import java.io.PipedInputStream;
import java.io.PipedOutputStream;

import android.content.Context;
import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.util.Log;

/*
 * To getaudio or play audio
 * */
public class IvikingAudio {
    private AudioRecord audioRecord;
    private Context context;
    private boolean isRecording = false ;
    private PipedOutputStream outstream ;//利用管道传输数据
    public IvikingAudio(Context context , PipedInputStream instream) throws IOException {
        this.context  = context;
        //初始化管道流 用于向外传输数据
        outstream = new PipedOutputStream();
        outstream.connect(instream);
    }
    public void StartAudioData(){//得到录音数据
        Log.d("audio:","开始录音......");
        int frequency = 48000;
        //int channelConfiguration = AudioFormat.CHANNEL_CONFIGURATION_STEREO;
          int channelConfiguration = AudioFormat.CHANNEL_IN_MONO;
        int audioEncoding = AudioFormat.ENCODING_PCM_16BIT;
        int buffersize = AudioRecord.getMinBufferSize(frequency, channelConfiguration, audioEncoding);
        audioRecord = new AudioRecord(MediaRecorder.AudioSource.MIC,
                frequency, channelConfiguration, audioEncoding, buffersize);
        byte[]buffer  = new byte[buffersize];
        audioRecord.startRecording();//开始录音
        isRecording = true;
        int bufferReadSize = 1024;
        while (isRecording){
            audioRecord.read(buffer, 0, bufferReadSize);
            try {
                outstream.write(buffer, 0, bufferReadSize);
            } catch (IOException e) {
                Log.d("audio:","录音出错了");
                e.printStackTrace();
            }
        }
    }
    public void stopRecord(){//停止录音
        isRecording = false;
        audioRecord.stop();
        try {
            outstream.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
