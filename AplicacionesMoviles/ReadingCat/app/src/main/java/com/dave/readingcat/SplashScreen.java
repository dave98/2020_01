package com.dave.readingcat;

import androidx.appcompat.app.AppCompatActivity;

import android.app.ActivityOptions;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.Handler;
import android.util.Pair;
import android.view.View;
import android.view.WindowManager;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.ImageView;
import android.widget.TextView;

import com.dave.readingcat.entities.Article;
import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import java.io.File;
import java.lang.reflect.Type;
import java.util.ArrayList;

public class  SplashScreen extends AppCompatActivity {

    private static int SPLASH_SCREEN = 5000;
    //Variables
    Animation topAnim, bottomAnim;
    ImageView image;
    TextView logo, slogan;

    private File storage;
    private String[] allPath;

    ArrayList<Article> allBookSharedPref = new ArrayList<>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.activity_splash_screen);

        //Animations
        topAnim = AnimationUtils.loadAnimation(this, R.anim.top_animation);
        bottomAnim = AnimationUtils.loadAnimation(this, R.anim.botton_animation);

        //Hooks
        image = findViewById(R.id.imageView);
        logo = findViewById(R.id.appName);
        slogan = findViewById(R.id.appSlogan);

        image.setAnimation(topAnim);
        logo.setAnimation(bottomAnim);
        slogan.setAnimation(bottomAnim);

        //Loading Data Taken From https://www.youtube.com/watch?v=TQg98mQL2hs
        allPath = StorageUtil.getStorageDirectories(this);
        for(String path : allPath){
            storage = new File(path);
            Method.load_Directory_Files(storage);
        }
        SaveData();  // HERE: Convert all in "allBookListed" to Articles and save in SharedPrefences

        //After SPLASH_SCREEN time, we go to the next activity
        //Transition animation taken from: https://www.youtube.com/watch?v=C_TEugAIMHA
        new Handler().postDelayed(new Runnable() {
            @Override
            public void run() {
                Intent intent = new Intent(SplashScreen.this, Login.class);
                Pair[] pairs = new Pair[2];
                pairs[0] = new Pair<View, String>(image, "t_logo_image"); // Review in activity_splash_screen.xml and activity_login.xml to find
                pairs[1] = new Pair<View, String>(logo, "t_logo_text");   // the ones that are being animated

                ActivityOptions options = ActivityOptions.makeSceneTransitionAnimation(SplashScreen.this, pairs); // Careful with android version
                startActivity(intent, options.toBundle());
                //finish();
            }
        }, SPLASH_SCREEN);
    }

    private void SaveData(){
        // Create articles from raw examination
        for(File f : AcceptedExtension.allBookListed){
            Article article = new Article(f.getName(), f.getPath());
            allBookSharedPref.add(article);
        }

        SharedPreferences sharedPreferences = getSharedPreferences("shared_preferences", MODE_PRIVATE);
        SharedPreferences.Editor editor = sharedPreferences.edit();
        Gson gson = new Gson();
        String json = gson.toJson(allBookSharedPref);
        editor.putString("allbooks_list", json);
        editor.apply();
    }

    private void LoadData(){
        SharedPreferences sharedPreferences = getSharedPreferences("shared_preferences", MODE_PRIVATE);
        Gson gson = new Gson();
        String json = sharedPreferences.getString("allbooks_list", null);
        Type type = new TypeToken<ArrayList<Article>>(){}.getType();
        allBookSharedPref = gson.fromJson(json, type);

        if(allBookSharedPref == null){
            allBookSharedPref = new ArrayList<>();
        }
    }
}
