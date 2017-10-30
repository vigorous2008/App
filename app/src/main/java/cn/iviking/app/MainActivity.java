package cn.iviking.app;

import android.content.res.Resources;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.text.method.ScrollingMovementMethod;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.util.Log;


import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.IOException;
import java.io.PipedInputStream;
import java.io.PipedOutputStream;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Date;
import java.util.Timer;
import java.util.TimerTask;


import android.content.Context;
import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import cn.iviking.app.jni.Detector;
import cn.iviking.app.audio.IvikingAudio;
public class MainActivity extends AppCompatActivity {
    PipedInputStream in;
    boolean isRecord;
    IvikingAudio mm ;
    Button button ;
    int off = 0;
    TextView tv ;
    Handler handler;
    Timer timer ;

    /**
     * @param savedInstanceState
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

       button = (Button)findViewById(R.id.startButton);
       tv = (TextView)findViewById(R.id.tv);
        tv.setMovementMethod(ScrollingMovementMethod.getInstance());
       // byte[] data = new byte[1024*1024];
       /* InputStream inStream = getResources().openRawResource(R.raw.watermark);
        Log.i("AAAA","读音频文件");
        ByteArrayOutputStream swapStream = new ByteArrayOutputStream();
        byte[] buff = new byte[100];
        int rc = 0;
        try {
            while ((rc = inStream.read(buff, 0, 100)) > 0) {
                swapStream.write(buff, 0, rc);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        byte[] audioData = swapStream.toByteArray();
        Log.i("AAAA",String.format("pcm length %d",audioData.length) );
       byte[] byteArr = new Detector().getSymbol(audioData,44100,audioData.length,"0","0");
        String mark = "";
        for(int a=0;a<byteArr.length;a++){
            Log.i("watermark in char",String.format(" %c",byteArr[a]));
            mark+= String.format(" %c",byteArr[a]);
        }
        Log.i("mark String",mark);
        tv.setText(mark);*/
        Log.i("AAAA","00000000000---0000000000");
        handler = new Handler(){
            @Override
            public void handleMessage(Message msg){
                String text = msg.getData().getCharSequence("Data").toString();
                Log.i("CallBack: ",text);
                //tv.setText(msg.getData().getCharSequence("Data"))    ;
                tv.append(text+"\n");
            }
        };
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
    public void onClick_Event(View v){
        if (isRecord){
            isRecord = false;
            button.setText("START");
           // mm.stopRecord();
           // timer.cancel();
        }else{
            isRecord = true;
            button.setText("STOP");
            StartRecord();
        }
    }
    private void startRecord() {
        in = new PipedInputStream();
        final DateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        new Thread(new Runnable() {

            @Override
            public void run() {
                try {
                    mm = new IvikingAudio(MainActivity.this, in);
                    mm.StartAudioData();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }).start();

        int len = 0;
        int pos = 0;
        final int BUFFER_SIZE = 44100*2*3;
        byte[] data = new byte[BUFFER_SIZE];

        while (true){
            try{
                if(pos+len<BUFFER_SIZE){
                    len =in.read(data,pos+len,in.available());
                    pos = pos +len;
                    Log.i("data from mic",String.valueOf(len));
                }else{
                    byte[] markArr = new Detector().getSymbol(data,44100,data.length,"3","4");
                    String hols="";
                    Log.i("watermark from MIC",new String(markArr));
                    for(int a=0;a<markArr.length;a++){
                        Log.i("watermark in char",String.format(" %c",markArr[a]));
                        hols+= String.format(" %c",markArr[a]);
                    }

                    // tv.setText(df.format(new Date())+" "+mark);
                    Message msg = new Message();
                    msg.setTarget(handler);
                    Bundle mBundle = new Bundle();
                    mBundle.putString("Data", df.format(new Date())+hols);//压入数据
                    msg.setData(mBundle);
                    handler.sendMessage(msg);
                    pos = 0;
                    data = new byte[BUFFER_SIZE];
                }

            }catch (Exception e){
                e.printStackTrace();
            }

        }
     }
    public void StartRecord() {
        final DateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        final DateFormat dfHHMMSS = new SimpleDateFormat("yyyyMMddHHmmss");

        new Thread() {
            @Override
            public void run() {
                super.run();
                Log.i("开始录音"," ");
                //采集率
                int frequency = 44100;
                //格式
                int channelConfiguration = AudioFormat.CHANNEL_IN_MONO;
                //16Bit
                int audioEncoding = AudioFormat.ENCODING_PCM_16BIT;
                //生成PCM文件
                String path = Environment.getExternalStorageDirectory().getAbsolutePath()+"/iviking/";
                //path+"/iviking"
                try {
                    File rootPath = new File(path);
                    if(!rootPath.exists()){
                        rootPath.mkdir();
                    }
                    String timeStr = dfHHMMSS.format(new Date());
                    String audioFile = path+timeStr+"audio.wav";
                    String markFile = path+timeStr+"audio.txt";

                    Log.i("recorder: ",audioFile);
                    FileOutputStream fos = new FileOutputStream(new File(audioFile));
                   // FileOutputStream markFos = new FileOutputStream(new File(markFile));
                    FileWriter writer = new FileWriter(new File(markFile));
                    //输出流
//                    int bufferSize = AudioRecord.getMinBufferSize(frequency, channelConfiguration, audioEncoding);
                    int time = 5;
                    int bufferSize = time * frequency * 2;
                    Log.i("bufferSize:" , String.valueOf(bufferSize));
                    AudioRecord audioRecord = new AudioRecord(MediaRecorder.AudioSource.MIC, frequency, channelConfiguration, audioEncoding, bufferSize);
                    byte[] buffer = new byte[bufferSize];
                    audioRecord.startRecording();
                    Log.i("开始","");
                    long t1,t2,t3,t4;
                    while (isRecord) {
                        String hols = "";
                        int bufferReadResult = audioRecord.read(buffer, 0, bufferSize);
//                        logD("buffer:" + new String(buffer));
                      //  Log.i("buffer size %d",String.valueOf(buffer.length));
                        Log.i("提交检测  buffer size ",String.format("%d",buffer.length));
                        t1 = System.currentTimeMillis();
                        byte[] markArr = new Detector().getSymbol(buffer, frequency, buffer.length, "", "");
                        for(int a=0;a<markArr.length;a++){
                            //Log.i("watermark in char",String.format(" %c",markArr[a]));
                            hols+= String.format("%c",markArr[a]);
                        }
                        t2 = System.currentTimeMillis();

                        fos.write(buffer);
                        t3 = System.currentTimeMillis();
                        String retStr = String.format("%s 【%s】秒音频数据 watermark in char 【%s】 检测耗时【%s】毫秒 写文件耗时【%s】 \n",df.format(new Date()),time,hols,String.valueOf((t2-t1)),String.valueOf((t3-t2)));
                        Log.i("",retStr);
                        writer.write(retStr);
                        writer.flush();

                        Message msg = new Message();
                        msg.setTarget(handler);
                        Bundle mBundle = new Bundle();
                        mBundle.putString("Data", df.format(new Date())+"  "+hols);//压入数据
                        msg.setData(mBundle);
                        handler.sendMessage(msg);
                    }

//            }
                    audioRecord.stop();
                    fos.flush();
                    fos.close();
                } catch (Throwable t) {
                    String message = t.getMessage();
                    Log.i("录音失败 :" , message);
                }
            }
        }.start();
    }
    }
