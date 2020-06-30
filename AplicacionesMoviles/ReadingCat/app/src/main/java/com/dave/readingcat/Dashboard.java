package com.dave.readingcat;

import androidx.annotation.NonNull;
import androidx.appcompat.app.ActionBarDrawerToggle;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.core.view.GravityCompat;
import androidx.drawerlayout.widget.DrawerLayout;

import android.os.Bundle;
import android.view.MenuItem;
import android.view.WindowManager;

import com.google.android.material.navigation.NavigationView;

public class Dashboard extends AppCompatActivity implements NavigationView.OnNavigationItemSelectedListener {
    private DrawerLayout drawerLayout;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.activity_dashboard);

        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        drawerLayout = findViewById(R.id.drawer_layout);

        // Seleccionar fragmentos:
        // Taken from: https://www.youtube.com/watch?v=bjYstsO1PgI
        NavigationView navigationView = findViewById(R.id.nav_view);
        navigationView.setNavigationItemSelectedListener(this); // Or we can create a New Interface

        //Manejo del navegador izquierdo. Utilizando clase heredada
        //Taken from: https://www.youtube.com/watch?v=zYVEMCiDcmY
        ActionBarDrawerToggle actionBarDrawerToggle = new ActionBarDrawerToggle(this, drawerLayout, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close);
        drawerLayout.addDrawerListener(actionBarDrawerToggle);
        actionBarDrawerToggle.syncState();

        //First item is selected by default
        if(savedInstanceState == null) { // To ensure only the first time, fix rotation
            getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container, new FragmentAllBooks()).commit();
            navigationView.setCheckedItem(R.id.nav_all_books_and_docs);
        }
    }

    @Override
    public boolean onNavigationItemSelected(@NonNull MenuItem menuItem) {
        switch (menuItem.getItemId()){
            case R.id.nav_all_books_and_docs:
                getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container, new FragmentAllBooks()).commit();
                break;
            case R.id.nav_last_read:
                getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container, new FragmentLastRead()).commit();
                break;
            case R.id.nav_to_read:
                getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container, new FragmentToRead()).commit();
                break;
            case R.id.nav_favorite:
                getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container, new FragmentFavorite()).commit();
                break;
            case R.id.nav_book_collection:
                getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container, new FragmentBookCollections()).commit();
                break;
            case R.id.nav_garbage:
                getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container, new FragmentGarbage()).commit();
                break;
            case R.id.nav_notifications:
                getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container, new FragmentNotifications()).commit();
                break;
            case R.id.nav_configuration:
                getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container, new FragmentConfiguration()).commit();
                break;
            case R.id.nav_update:
                getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container, new FragmentUpdate()).commit();
                break;
            case R.id.nav_programmer:
                getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container, new FragmentProgrammer()).commit();
                break;
        }
        drawerLayout.closeDrawer(GravityCompat.START);
        return true;
    }

    // Take care if the drawer_layout is open when user press back. In tha case it closes the drawer, otherwise it just go back.
    @Override
    public void onBackPressed(){
        // If the drawer come from the right just put end
        if(drawerLayout.isDrawerOpen(GravityCompat.START)){
            drawerLayout.closeDrawer(GravityCompat.START);
        }else{
            super.onBackPressed();
        }

    }


}
