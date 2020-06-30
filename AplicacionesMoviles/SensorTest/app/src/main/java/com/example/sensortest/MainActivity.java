package com.example.sensortest;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.Random;

public class MainActivity extends AppCompatActivity {
    SensorManager sensorManager;
    Sensor sensor1;

    SensorEventListener sensorEventListener1;
    TextView val1;
    TextView val1_ans;

    ImageView image;

    Float x_axis = 0.f;
    Float y_axis = 0.f;
    Float z_axis = 0.f;

    int dice_to = 0;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        sensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);
        sensor1 = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);

        val1 = (TextView) findViewById(R.id.sensor_1);
        val1_ans = (TextView) findViewById(R.id.sensor_1_val);
        image = (ImageView) findViewById(R.id.dice_id);

        if (sensor1 == null) {
            finish();
        } else {
            sensorEventListener1 = new SensorEventListener() {
                @Override
                public void onSensorChanged(SensorEvent sensorEvent) {
                    Float temp = Math.abs(x_axis - sensorEvent.values[0]) + Math.abs(y_axis - sensorEvent.values[1]) + Math.abs(z_axis - sensorEvent.values[2]);

                    val1.setText("Resultados");
                    val1_ans.setText(temp.toString());


                    if(temp >= 15.0){
                        dice_to = new Random().nextInt(5);
                        switch (dice_to){
                            case 0:
                                image.setImageResource(R.drawable.dice_0);
                                break;
                            case 1:
                                image.setImageResource(R.drawable.dice_1);
                                break;
                            case 2:
                                image.setImageResource(R.drawable.dice_2);
                                break;
                            case 3:
                                image.setImageResource(R.drawable.dice_3);
                                break;
                            case 4:
                                image.setImageResource(R.drawable.dice_4);
                                break;
                            case 5:
                                image.setImageResource(R.drawable.dice_5);
                                break;
                            default:
                                image.setImageResource(R.drawable.dice_1);
                                break;
                        }
                    }

                    x_axis = sensorEvent.values[0];
                    y_axis = sensorEvent.values[1];
                    z_axis = sensorEvent.values[2];

                }

                @Override
                public void onAccuracyChanged(Sensor sensor, int i) {
                }
            };
        }

    }

    public void start(){
        sensorManager.registerListener(sensorEventListener1, sensor1, 2000*1000);
    }

    public void stop(){
        sensorManager.unregisterListener(sensorEventListener1);
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