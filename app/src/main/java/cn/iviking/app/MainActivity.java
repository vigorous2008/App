package cn.iviking.app;

import android.content.res.Resources;
import android.os.Bundle;
import android.os.Environment;
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
import java.util.Arrays;

import cn.iviking.app.jni.JNIUtils;
import cn.iviking.app.audio.IvikingAudio;
public class MainActivity extends AppCompatActivity {
    PipedInputStream in;
    boolean isRrcord;
    IvikingAudio mm ;
    Button button ;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        /*Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);*/

       /* FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });*/
       button = (Button)findViewById(R.id.startButton);
        TextView tv = (TextView)findViewById(R.id.tv);
       // byte[] data = new byte[1024*1024];
        InputStream inStream = getResources().openRawResource(R.raw.watermark);
        Log.d("AAAA","读音频文件");
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
        Log.d("AAAA path=",path);
        Log.d("AAAA",String.format("pcm length %d",data.length) );
        byte[] dataNoMeta = Arrays.copyOfRange(data,48,data.length-1);
        tv.setText(new JNIUtils().getSymbol(dataNoMeta,"48000",dataNoMeta.length,"3","4")+"  || "+new JNIUtils().getString());
        Log.d("AAAA","00000000000---0000000000");
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
        }else{
            isRrcord = true;
            button.setText("STOP");
            startRecord();
        }
    }
    private void startRecord() {
        in = new PipedInputStream();
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

     }
    }
