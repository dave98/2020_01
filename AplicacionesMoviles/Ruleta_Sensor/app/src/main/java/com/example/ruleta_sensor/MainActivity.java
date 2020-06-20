package com.example.ruleta_sensor;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.view.animation.AccelerateDecelerateInterpolator;
import android.view.animation.RotateAnimation;
import android.widget.ImageView;
import android.widget.TextView;

import org.w3c.dom.Text;

import java.util.Random;

public class MainActivity extends AppCompatActivity {
    SensorManager sensorManager;
    Sensor sensor;
    SensorEventListener sensorEventListener;

    int angle = 300;
    ImageView ruleta;
    TextView texto;
    Random rand;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        sensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);
        sensor = sensorManager.getDefaultSensor(Sensor.TYPE_PROXIMITY);
        ruleta = (ImageView) findViewById(R.id.ruleta);
        texto = (TextView) findViewById(R.id.texto);

        if(sensor == null){
            finish();
        }
        else{
            sensorEventListener = new SensorEventListener() {
                @Override
                public void onSensorChanged(SensorEvent sensorEvent) {
                    if(sensorEvent.values[0] <= sensor.getMaximumRange()){
                        angle = new Random().nextInt(600);
                        texto.setText("Girando");

                        getWindow().getDecorView().setBackgroundColor(Color.BLUE);
                        RotateAnimation rotate = new RotateAnimation(0, angle, RotateAnimation.RELATIVE_TO_SELF, 0.5F, RotateAnimation.RELATIVE_TO_SELF, 0.5F);
                        rotate.setFillAfter(true);
                        rotate.setDuration(3600);
                        rotate.setInterpolator(new AccelerateDecelerateInterpolator());
                        ruleta.startAnimation(rotate);


                    }
                    else{
                        texto.setText("Detenido");
                        getWindow().getDecorView().setBackgroundColor(Color.WHITE);
                    }
                }

                @Override
                public void onAccuracyChanged(Sensor sensor, int i) {
                    // En base a la presicion
                }
            };
            start();
        }
    }

    public void start(){
        sensorManager.registerListener(sensorEventListener, sensor, 2000*1000);
    }


    public void stop(){
        sensorManager.unregisterListener(sensorEventListener);
    }

    @Override
    protected void onPause() {
        stop();
        super.onPause();
    }

    @Override
    protected void onResume() {
        start();
        super.onResume();
    }

}