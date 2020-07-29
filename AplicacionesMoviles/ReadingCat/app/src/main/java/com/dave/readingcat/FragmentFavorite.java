package com.dave.readingcat;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Adapter;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.dave.readingcat.entities.Article;
import com.dave.readingcat.fragment_adapters.AdapterFavorite;
import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import java.lang.reflect.Type;
import java.util.ArrayList;
import java.util.Collections;

public class FragmentFavorite extends Fragment {
    AdapterFavorite adapterFavorite;
    RecyclerView recyclerViewFavorite;
    ArrayList<Article> favoriteBookSharedPref = new ArrayList<>();

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_favorite, container, false);
        LoadData();

        recyclerViewFavorite = view.findViewById(R.id.recyclerView_Favorite);
        recyclerViewFavorite.setLayoutManager(new LinearLayoutManager(getContext()));
        adapterFavorite = new AdapterFavorite(getContext(), favoriteBookSharedPref);
        recyclerViewFavorite.setAdapter(adapterFavorite);

        adapterFavorite.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int id = v.getId();
                switch (id) {
                    case R.id.card_addfavorite:
                        Toast.makeText(v.getContext(), "Se ha quitado  de favoritos", Toast.LENGTH_SHORT).show();
                        break;
                    case R.id.card_bookcollection:
                        Toast.makeText(v.getContext(), "Collection", Toast.LENGTH_SHORT).show();
                        break;
                    case R.id.card_notifications:
                        Toast.makeText(v.getContext(), "Notification", Toast.LENGTH_SHORT).show();
                        break;
                    case R.id.card_garbage:
                        Toast.makeText(v.getContext(), "Garbage", Toast.LENGTH_SHORT).show();
                        break;
                    default:
                        OpenBook(v);
                        break;
                }
            }
        });

        return view;
    }

    private void LoadData(){
        SharedPreferences sharedPreferences = this.getActivity().getSharedPreferences("shared_preferences", Context.MODE_PRIVATE); // LookHere: https://stackoverflow.com/questions/11741270/android-sharedpreferences-in-fragment
        Gson gson = new Gson();
        String json = sharedPreferences.getString("favorite_list", null);
        Type type = new TypeToken<ArrayList<Article>>(){}.getType();
        favoriteBookSharedPref = gson.fromJson(json, type);

        if(favoriteBookSharedPref == null){
            favoriteBookSharedPref = new ArrayList<>();
        }
    }

    private void OpenBook(View v){
        String book_name = favoriteBookSharedPref.get(recyclerViewFavorite.getChildAdapterPosition(v)).getArticle_name();
        String book_path = favoriteBookSharedPref.get(recyclerViewFavorite.getChildAdapterPosition(v)).getArticle_path();

        AddToLastRead(favoriteBookSharedPref.get(recyclerViewFavorite.getChildAdapterPosition(v)));

        Intent intent = new Intent(getActivity(), Viewer_pdf.class);
        intent.putExtra("BOOK_NAME", book_name);
        intent.putExtra("BOOK_PATH", book_path);
        startActivity(intent);
    }

    private void AddToLastRead(Article new_article){ // WARNING: Inefficient implementation - Fast prototype
        SharedPreferences sharedPreferences = this.getActivity().getSharedPreferences("shared_preferences", Context.MODE_PRIVATE);
        Gson gson = new Gson();
        String json_lastread = sharedPreferences.getString("lastread_list", null);
        Type type = new TypeToken<ArrayList<Article>>(){}.getType();
        ArrayList<Article> tempLastRead = gson.fromJson(json_lastread, type);

        if(tempLastRead == null){
            tempLastRead = new ArrayList<>();
        }

        int is_article_listed = tempLastRead.indexOf(new_article);
        if(is_article_listed != -1){
            Collections.swap(tempLastRead, is_article_listed, 0);
        }
        else {
            tempLastRead.add(0, new_article);
        }

        SharedPreferences.Editor editor = sharedPreferences.edit();
        String json = gson.toJson(tempLastRead);
        editor.putString("lastread_list", json);
        editor.apply();
    }


}
