package cn.iviking.app;

import android.content.res.Resources;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.util.Log;


import java.io.ByteArrayOutputStream;
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

import cn.iviking.app.jni.JNIUtils;
import cn.iviking.app.audio.IvikingAudio;
public class MainActivity extends AppCompatActivity {
    PipedInputStream in;
    boolean isRrcord;
    IvikingAudio mm ;
    Button button ;
    int off = 0;
    TextView tv ;
    Handler handler;
    Timer timer ;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

       button = (Button)findViewById(R.id.startButton);
       tv = (TextView)findViewById(R.id.tv);
       // byte[] data = new byte[1024*1024];
        /*InputStream inStream = getResources().openRawResource(R.raw.watermark);
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
        byte[] data = swapStream.toByteArray();
        String path = Environment.getExternalStorageDirectory().getAbsolutePath();
        Log.i("AAAA path=",path);
        Log.i("AAAA",String.format("pcm length %d",data.length) );
        byte[] byteArr = new JNIUtils().getSymbol(data,"44100",data.length,"3","4");
        String mark = "";
        for(int a=0;a<byteArr.length;a++){
            Log.i("watermark in bit",String.valueOf(byteArr[a]));
            mark+= String.format(" %x",byteArr[a]);
        }

        Log.i("mark String",mark);

        tv.setText(mark);*/
        tv.setText(new JNIUtils().getString());
        Log.i("AAAA","00000000000---0000000000");
        handler = new Handler(){
            @Override
            public void handleMessage(Message msg){
                Log.i("CallBack: ",msg.getData().getCharSequence("Data").toString());
                tv.setText(msg.getData().getCharSequence("Data"))    ;
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
        if (isRrcord){
            isRrcord = false;
            button.setText("START");
            mm.stopRecord();
            timer.cancel();
        }else{
            isRrcord = true;
            button.setText("STOP");
            startRecord();
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
                    byte[] markArr = new JNIUtils().getSymbol(data,"44100",data.length,"3","4");
                    String hols="";
                    Log.i("watermark from MIC",new String(markArr));
                    for(int a=0;a<markArr.length;a++){
                        Log.i("watermark in bit",String.valueOf(markArr[a]));
                        hols+= String.format(" %x",markArr[a]);
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
    }
