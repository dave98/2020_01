package com.dave.readingcat;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.dave.readingcat.entities.Article;
import com.dave.readingcat.fragment_adapters.AdapterAllBooks;
import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import java.lang.reflect.Type;
import java.util.ArrayList;
import java.util.Collections;

public class FragmentAllBooks extends Fragment{

    AdapterAllBooks adapterAllBooks;
    RecyclerView recyclerViewAllBook;
    ArrayList<Article> allBookSharedPref = new ArrayList<>();


    @Override
    public void onCreate(Bundle savedInstanceState){
        super .onCreate(savedInstanceState);
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        final View view = inflater.inflate(R.layout.fragment_all_books_and_doc, container, false);
        LoadData();

        recyclerViewAllBook = view.findViewById(R.id.recyclerView_AllBooks);
        recyclerViewAllBook.setLayoutManager(new LinearLayoutManager(getContext()));
        adapterAllBooks = new AdapterAllBooks(getContext(), allBookSharedPref);
        recyclerViewAllBook.setAdapter(adapterAllBooks);

        adapterAllBooks.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int id = v.getId();
                switch (id){
                    case R.id.card_addfavorite:;
                        AddToFavoriteBook((View) v.getParent().getParent()); // RelativeLayout|LinearLayout|RecyclerView
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
        String json = sharedPreferences.getString("allbooks_list", null);
        Type type = new TypeToken<ArrayList<Article>>(){}.getType();
        allBookSharedPref = gson.fromJson(json, type);

        if(allBookSharedPref == null){
            allBookSharedPref = new ArrayList<>();
        }
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

    private void AddToFavoriteBook(View v){
        Article new_article = allBookSharedPref.get(recyclerViewAllBook.getChildAdapterPosition(v));
        SharedPreferences sharedPreferences = this.getActivity().getSharedPreferences("shared_preferences", Context.MODE_PRIVATE);
        Gson gson = new Gson();
        String json_favorite = sharedPreferences.getString("favorite_list", null);
        Type type = new TypeToken<ArrayList<Article>>(){}.getType();
        ArrayList<Article> tempFavorite = gson.fromJson(json_favorite, type);
        if(tempFavorite== null){ tempFavorite = new ArrayList<>(); }

        int is_article_listed = tempFavorite.indexOf(new_article);
        if(is_article_listed != -1){
            Collections.swap(tempFavorite, is_article_listed, 0);
            Toast.makeText(v.getContext(), "Ya está en favoritos", Toast.LENGTH_SHORT).show();
        }
        else {
            tempFavorite.add(0, new_article);
            Toast.makeText(v.getContext(), "Se añadió a favoritos", Toast.LENGTH_SHORT).show();
        }

        SharedPreferences.Editor editor_favorite = sharedPreferences.edit();
        String json = gson.toJson(tempFavorite);
        editor_favorite.putString("favorite_list", json);
        editor_favorite.apply();
    }

    private void OpenBook(View v){
        String book_name = allBookSharedPref.get(recyclerViewAllBook.getChildAdapterPosition(v)).getArticle_name();
        String book_path = allBookSharedPref.get(recyclerViewAllBook.getChildAdapterPosition(v)).getArticle_path();

        AddToLastRead(allBookSharedPref.get(recyclerViewAllBook.getChildAdapterPosition(v)));

        Intent intent = new Intent(getActivity(), Viewer_pdf.class);
        intent.putExtra("BOOK_NAME", book_name);
        intent.putExtra("BOOK_PATH", book_path);
        startActivity(intent);
    }

}
