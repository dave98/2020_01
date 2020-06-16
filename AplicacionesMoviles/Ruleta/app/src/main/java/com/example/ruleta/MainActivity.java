package com.example.ruleta;

import androidx.appcompat.app.AppCompatActivity;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import java.util.Random;

public class MainActivity extends AppCompatActivity {

    RelativeLayout r1;
    TextView texto;
    SensorManager sm;
    Sensor sensor;
    ImageView ruleta;
    Random rand;
    boolean restart = false;
    int angle;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ruleta = (ImageView) findViewById(R.id.ruleta);
        texto = (TextView) findViewById(R.id.text);
        sm = (SensorManager) getSystemService(SENSOR_SERVICE);
        sensor = sm.getDefaultSensor(Sensor.TYPE_PROXIMITY);
        sm.registerListener((SensorEventListener) this, sensor, SensorManager.SENSOR_DELAY_NORMAL);
        rand = new Random();
    }

    public void onSensorChanged(SensorEvent sensorEvent){

    }
}