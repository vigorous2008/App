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
       // outstream.connect(instream);
        instream.connect(outstream);
    }
    public void StartAudioData(){//得到录音数据
        Log.i("audio:","开始录音......");
        int frequency = 44100;
        //int channelConfiguration = AudioFormat.CHANNEL_CONFIGURATION_STEREO;
          int channelConfiguration = AudioFormat.CHANNEL_IN_MONO;
        int audioEncoding = AudioFormat.ENCODING_PCM_16BIT;
        int buffersize = AudioRecord.getMinBufferSize(frequency, channelConfiguration, audioEncoding);
        audioRecord = new AudioRecord(MediaRecorder.AudioSource.MIC,
                frequency, channelConfiguration, audioEncoding, buffersize);
        Log.i("audio:","开始录音......bufferSize:"+buffersize);
        byte[]buffer  = new byte[buffersize];
        audioRecord.startRecording();//开始录音
        isRecording = true;
        //int bufferReadSize = 1024;
        while (isRecording){
            int bufferReadResult = audioRecord.read(buffer, 0, buffer.length);
            Log.i("audio:","录音机.读取数据字节数...bufferReadResult:"+bufferReadResult);
            try {
                outstream.write(buffer, 0, buffer.length);
            } catch (IOException e) {
                Log.e("audio:","录音出错了");
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
            Log.e("audio ",e.getMessage());
           // e.printStackTrace();
        }
    }

}
