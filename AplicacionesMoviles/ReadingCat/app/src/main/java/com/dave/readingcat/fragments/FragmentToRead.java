package com.dave.readingcat.fragments;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.bumptech.glide.load.model.ModelLoader;
import com.dave.readingcat.R;
import com.dave.readingcat.Viewer_pdf;
import com.dave.readingcat.entities.Article;
import com.dave.readingcat.entities.Book;
import com.dave.readingcat.fragment_adapters.AdapterToRead;
import com.google.gson.Gson;

import java.io.File;
import java.util.ArrayList;
import java.util.Collections;

import static com.dave.readingcat.Dashboard.enviroments_books;
import static com.dave.readingcat.Dashboard.last_read_stack;

public class FragmentToRead extends Fragment {
    AdapterToRead adapterToRead;
    RecyclerView recyclerViewToRead;
    ArrayList<Article> toReadSharedPref = new ArrayList<>();

    EditText editText;
    private static final int READER_ACTIVITY_VALUE_TOKEN = 0;
    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_to_read, container, false);
        LoadData();

        recyclerViewToRead = view.findViewById(R.id.recyclerViewToRead);
        recyclerViewToRead.setLayoutManager(new LinearLayoutManager(getContext()));
        adapterToRead = new AdapterToRead(getContext(), toReadSharedPref);
        recyclerViewToRead.setAdapter(adapterToRead);
        editText = view.findViewById(R.id.edittext_ToRead);

        adapterToRead.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int id = v.getId();
                switch (id){
                    case R.id.card_addfavorite:;
                        AddToFavorite((View) v.getParent().getParent());
                        break;
                    case R.id.card_bookcollection:
                        Toast.makeText(v.getContext(), "Collection", Toast.LENGTH_SHORT).show();
                        break;
                    case R.id.card_notifications:
                        AddToNotification((View) v.getParent().getParent());
                        break;
                    case R.id.card_garbage:
                        DeleteBook((View) v.getParent().getParent());
                        break;
                    default:
                        OpenBook(v);
                        break;
                }
            }
        });

        editText.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {

            }

            @Override
            public void afterTextChanged(Editable s) {
                filter(s.toString());
            }
        });
        return  view;
    }

    private void filter(String text){
        ArrayList<Article> filteredList = new ArrayList<>();

        for(Article article : toReadSharedPref){
            if(new File(article.getArticle_path()).getName().toLowerCase().contains(text.toLowerCase())){
                filteredList.add(article);
            }
        }
        adapterToRead.filterList(filteredList);
    }


    private void LoadData(){
        for(Article book : enviroments_books){
            if(!book.getIs_deleted()){
                toReadSharedPref.add(book);
            }
        }
        Collections.sort(toReadSharedPref);
        Collections.reverse(toReadSharedPref);
    }

    // (Actualiza) Guarda todos los datos de enviroments_books en shared_preferences:allbook_list
    private void SaveData(){
        SharedPreferences sharedPreferences = this.getActivity().getSharedPreferences("shared_preferences", Context.MODE_PRIVATE);
        SharedPreferences.Editor editor = sharedPreferences.edit();
        Gson gson = new Gson();
        String json = gson.toJson(enviroments_books);
        editor.putString("allbooks_list", json);
        editor.apply();
    }

    private void SaveLastReadData(){
        SharedPreferences sharedPreferences = this.getActivity().getSharedPreferences("shared_preferences", Context.MODE_PRIVATE);
        SharedPreferences.Editor editor = sharedPreferences.edit();
        Gson gson = new Gson();
        String json = gson.toJson(last_read_stack);
        editor.putString("lastread_list", json);
        editor.apply();
    }

    private void AddToLastRead(View v){
        // A last read solo añadire una copia BARATA del articulo leido
        int index = last_read_stack.indexOf(toReadSharedPref.get(recyclerViewToRead.getChildAdapterPosition(v)));
        if(index != -1){ //Si esta en el stack de last_read
            Collections.swap(last_read_stack, index, 0);
        }
        else{
            last_read_stack.add(0, toReadSharedPref.get(recyclerViewToRead.getChildAdapterPosition(v)));
        }
        SaveLastReadData();
    }

    private void AddToFavorite(View v){
        if(toReadSharedPref.get(recyclerViewToRead.getChildAdapterPosition(v)).getIs_favorite()){
            toReadSharedPref.get(recyclerViewToRead.getChildAdapterPosition(v)).setIs_favorite(false);
            Toast.makeText(v.getContext(), "Se quitó de favoritos", Toast.LENGTH_SHORT).show();

            /*GLOBAL UPDATE*/
            int index = enviroments_books.indexOf(toReadSharedPref.get(recyclerViewToRead.getChildAdapterPosition(v)));
            if(index != -1){
                enviroments_books.get(index).setIs_favorite(false);
                SaveData();
            }
            else{ Toast.makeText(v.getContext(), "Error de sincronización en capa bilineal", Toast.LENGTH_SHORT).show(); }
        }
        else{
            toReadSharedPref.get(recyclerViewToRead.getChildAdapterPosition(v)).setIs_favorite(true);
            Toast.makeText(v.getContext(), "Se añadió a favoritos", Toast.LENGTH_SHORT).show();

            /*GLOBAL UPDATE*/
            int index = enviroments_books.indexOf(toReadSharedPref.get(recyclerViewToRead.getChildAdapterPosition(v)));
            if(index != -1){
                enviroments_books.get(index).setIs_favorite(true);
                SaveData();
            }
            else{ Toast.makeText(v.getContext(), "Error de sincronización en capa bilineal", Toast.LENGTH_SHORT).show(); }
        }
        adapterToRead.notifyItemChanged(recyclerViewToRead.getChildAdapterPosition(v));
    }

    private void AddToNotification(View v){
        if(toReadSharedPref.get(recyclerViewToRead.getChildAdapterPosition(v)).getIs_synch()){
            toReadSharedPref.get(recyclerViewToRead.getChildAdapterPosition(v)).setIs_synch(false);
            Toast.makeText(v.getContext(), "Se quitó de notificaciones", Toast.LENGTH_SHORT).show();

            /*GLOBAL UPDATE*/
            int index = enviroments_books.indexOf(toReadSharedPref.get(recyclerViewToRead.getChildAdapterPosition(v)));
            if(index != -1){
                enviroments_books.get(index).setIs_synch(false);
                SaveData();
            }
            else{ Toast.makeText(v.getContext(), "Error de sincronización en capa bilineal", Toast.LENGTH_SHORT).show(); }
        }
        else{
            toReadSharedPref.get(recyclerViewToRead.getChildAdapterPosition(v)).setIs_synch(false);
            Toast.makeText(v.getContext(), "Se añadió a notificaciones", Toast.LENGTH_SHORT).show();

            /*GLOBAL UPDATE*/
            int index = enviroments_books.indexOf(toReadSharedPref.get(recyclerViewToRead.getChildAdapterPosition(v)));
            if(index != -1){
                enviroments_books.get(index).setIs_synch(true);
                SaveData();
            }
            else{ Toast.makeText(v.getContext(), "Error de sincronización en capa bilineal", Toast.LENGTH_SHORT).show(); }
        }
        adapterToRead.notifyItemChanged(recyclerViewToRead.getChildAdapterPosition(v));
    }

    private void DeleteBook(View v){
        if(toReadSharedPref.get(recyclerViewToRead.getChildAdapterPosition(v)).getIs_deleted()){ // No debería pasar
            Toast.makeText(v.getContext(), "Error inesperado al eliminar", Toast.LENGTH_SHORT).show();
        }
        else{
            int pos = recyclerViewToRead.getChildAdapterPosition(v);

            /*IMPORTANTE: Primero actualizar estado global*/
            int index = enviroments_books.indexOf(toReadSharedPref.get(recyclerViewToRead.getChildAdapterPosition(v)));
            if(index != -1){
                // Es importante quitar el resto de condiciones como Notificaciones y Favoritos
                enviroments_books.get(index).setIs_deleted(true);
                enviroments_books.get(index).setIs_synch(false);
                enviroments_books.get(index).setIs_favorite(false);
                SaveData();

                // LastReadStack puede contener una referencia a este dato, es necesario quitarlo
                int index_for_last = last_read_stack.indexOf(toReadSharedPref.get(recyclerViewToRead.getChildAdapterPosition(v)));
                if(index_for_last != -1){
                    last_read_stack.remove(index_for_last);
                    SaveLastReadData();
                }
            }
            else{ Toast.makeText(v.getContext(), "Error de sincronización en capa bilineal", Toast.LENGTH_SHORT).show(); }

            /*Ahora si procedemos con cambios locales*/
            toReadSharedPref.remove(pos);
            adapterToRead.notifyItemRemoved(pos);
            Toast.makeText(v.getContext(), "Se ha movido a la papelera", Toast.LENGTH_SHORT).show();
        }
    }

    private void OpenBook(View v){
        String book_path = toReadSharedPref.get(recyclerViewToRead.getChildAdapterPosition(v)).getArticle_path();
        String book_name = (new File(book_path)).getName();

        AddToLastRead(v);

        Intent intent = new Intent(getActivity(), Viewer_pdf.class);
        intent.putExtra("BOOK_NAME", book_name);
        intent.putExtra("BOOK_PATH", book_path);
        startActivityForResult(intent, READER_ACTIVITY_VALUE_TOKEN);
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if(resultCode == Activity.RESULT_OK){
            if(requestCode == READER_ACTIVITY_VALUE_TOKEN && data!=null){
                /*Information received*/
                String returnedString = data.getStringExtra("local_updated_path");

                Article temp_art = new Article();
                temp_art.setArticle_path(returnedString);

                int temp_index = toReadSharedPref.indexOf(temp_art);
                if(temp_index == -1){ Toast.makeText(getContext(), "Imposible actualizar token", Toast.LENGTH_SHORT).show();}
                else{
                    adapterToRead.notifyDataSetChanged();
                }
            }
        }
    }
}

