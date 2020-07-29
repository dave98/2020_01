package com.dave.readingcat.fragments;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.dave.readingcat.R;
import com.dave.readingcat.Viewer_pdf;
import com.dave.readingcat.entities.Article;
import com.dave.readingcat.fragment_adapters.AdapterNotification;
import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import java.io.File;
import java.lang.reflect.Type;
import java.util.ArrayList;
import java.util.Collections;

import static com.dave.readingcat.Dashboard.enviroments_books;

public class FragmentNotifications extends Fragment {
    AdapterNotification adapterNotification;
    RecyclerView recyclerViewNotifications;
    ArrayList<Article> notificationsSharedPref = new ArrayList<>();

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_notifications, container, false);
        LoadData();

        recyclerViewNotifications = view.findViewById(R.id.recyclerView_Notification);
        recyclerViewNotifications.setLayoutManager(new LinearLayoutManager(getContext()));
        adapterNotification = new AdapterNotification(getContext(), notificationsSharedPref);
        recyclerViewNotifications.setAdapter(adapterNotification);

        adapterNotification.setOnClickListener(new View.OnClickListener() {
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
                        DeleteFromNotification((View) v.getParent().getParent());
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
        return view;
    }

    private void LoadData(){
        // Load data from enviroments_books to get those with "is_synch" is true.
        for(Article book : enviroments_books){
            if(book.getIs_synch()){ //Deleted books lost is_synch condition
                notificationsSharedPref.add(book);
            }
        }
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

    private void AddToFavorite(View v){
        if(notificationsSharedPref.get(recyclerViewNotifications.getChildAdapterPosition(v)).getIs_favorite()){
            notificationsSharedPref.get(recyclerViewNotifications.getChildAdapterPosition(v)).setIs_favorite(false);
            Toast.makeText(v.getContext(), "Se quitó de favoritos", Toast.LENGTH_SHORT).show();

            /*GLOBAL UPDATE*/
            int index = enviroments_books.indexOf(notificationsSharedPref.get(recyclerViewNotifications.getChildAdapterPosition(v)));
            if(index != -1){
                enviroments_books.get(index).setIs_favorite(false);
                SaveData();
            }
            else{ Toast.makeText(v.getContext(), "Error de sincronización en capa bilineal", Toast.LENGTH_SHORT).show(); }
        }
        else{
            notificationsSharedPref.get(recyclerViewNotifications.getChildAdapterPosition(v)).setIs_favorite(true);
            Toast.makeText(v.getContext(), "Se añadió a favoritos", Toast.LENGTH_SHORT).show();

            /*GLOBAL UPDATE*/
            int index = enviroments_books.indexOf(notificationsSharedPref.get(recyclerViewNotifications.getChildAdapterPosition(v)));
            if(index != -1){
                enviroments_books.get(index).setIs_favorite(true);
                SaveData();
            }
            else{ Toast.makeText(v.getContext(), "Error de sincronización en capa bilineal", Toast.LENGTH_SHORT).show(); }
        }

    }

    private void DeleteFromNotification(View v){
        if(!notificationsSharedPref.get(recyclerViewNotifications.getChildAdapterPosition(v)).getIs_synch()){
            Toast.makeText(v.getContext(), "Error inesperado al quitar de notificaciones", Toast.LENGTH_SHORT).show();
        }
        else{
            int pos = recyclerViewNotifications.getChildAdapterPosition(v);

            /*Actualizando el estado global*/
            int index = enviroments_books.indexOf(notificationsSharedPref.get(recyclerViewNotifications.getChildAdapterPosition(v)));
            if(index != -1){
                enviroments_books.get(index).setIs_synch(false);
                SaveData();
            }
            else{ Toast.makeText(v.getContext(), "Error de sincronización en capa bilineal", Toast.LENGTH_SHORT).show(); }

            /*Actualizando estado local*/
            notificationsSharedPref.remove(pos);
            adapterNotification.notifyItemRemoved(pos);
            Toast.makeText(v.getContext(), "Se quitó de notificaciones", Toast.LENGTH_SHORT).show();
        }
    }

    private void DeleteBook(View v){
        if(notificationsSharedPref.get(recyclerViewNotifications.getChildAdapterPosition(v)).getIs_deleted()){ // No debería pasar
            Toast.makeText(v.getContext(), "Error inesperado al eliminar", Toast.LENGTH_SHORT).show();
        }
        else{
            int pos = recyclerViewNotifications.getChildAdapterPosition(v);

            /*IMPORTANTE: Primero actualizar estado global*/
            int index = enviroments_books.indexOf(notificationsSharedPref.get(recyclerViewNotifications.getChildAdapterPosition(v)));
            if(index != -1){
                // Es importante quitar el resto de condiciones como Notificaciones y Favoritos
                enviroments_books.get(index).setIs_deleted(true);
                enviroments_books.get(index).setIs_synch(false);
                enviroments_books.get(index).setIs_favorite(false);
                SaveData();
            }
            else{ Toast.makeText(v.getContext(), "Error de sincronización en capa bilineal", Toast.LENGTH_SHORT).show(); }

            /*Ahora si procedemos con cambios locales*/
            notificationsSharedPref.remove(pos);
            adapterNotification.notifyItemRemoved(pos);
            Toast.makeText(v.getContext(), "Se ha movido a la papelera", Toast.LENGTH_SHORT).show();
        }

    }

    private void OpenBook(View v){
        String book_path = notificationsSharedPref.get(recyclerViewNotifications.getChildAdapterPosition(v)).getArticle_path();
        String book_name = (new File(book_path)).getName();

        //AddToLastRead(allBookSharedPref.get(recyclerViewAllBook.getChildAdapterPosition(v)));

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
