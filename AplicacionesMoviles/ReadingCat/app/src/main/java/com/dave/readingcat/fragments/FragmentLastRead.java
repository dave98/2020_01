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

import com.dave.readingcat.R;
import com.dave.readingcat.Viewer_pdf;
import com.dave.readingcat.entities.Article;
import com.dave.readingcat.entities.Book;
import com.dave.readingcat.fragment_adapters.AdapterLastRead;
import com.dave.readingcat.fragment_adapters.AdapterToRead;
import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import java.io.File;
import java.lang.reflect.Type;
import java.util.ArrayList;

import static com.dave.readingcat.Dashboard.enviroments_books;
import static com.dave.readingcat.Dashboard.last_read_stack;

public class FragmentLastRead extends Fragment {
    AdapterLastRead adapterLastRead;
    RecyclerView recyclerViewLastRead;
    ArrayList<Article> lastBookSharedPref = new ArrayList<>();

    EditText editText;
    private static final int READER_ACTIVITY_VALUE_TOKEN = 0;
    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        final View view = inflater.inflate(R.layout.fragment_last_read, container, false);
        LoadData();

        recyclerViewLastRead = view.findViewById(R.id.recyclerView_LastRead);
        recyclerViewLastRead.setLayoutManager(new LinearLayoutManager(getContext()));
        adapterLastRead = new AdapterLastRead(getContext(), lastBookSharedPref);
        recyclerViewLastRead.setAdapter(adapterLastRead);
        editText = view.findViewById(R.id.edittext_LastRead);

        adapterLastRead.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int id = v.getId();
                switch (id) {
                    case R.id.card_addfavorite:
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
        return view;
    }

    private void filter(String text){
        ArrayList<Article> filteredList = new ArrayList<>();

        for(Article article : lastBookSharedPref){
            if(new File(article.getArticle_path()).getName().toLowerCase().contains(text.toLowerCase())){
                filteredList.add(article);
            }
        }
        adapterLastRead.filterList(filteredList);
    }

    private void LoadData(){
        for(Article book : last_read_stack){
            int index = enviroments_books.indexOf(book);
            if(index != -1){
                if(!enviroments_books.get(index).getIs_deleted()){
                    lastBookSharedPref.add(enviroments_books.get(index));
                }
            }
        }
    }

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

    private void AddToFavorite(View v){
        int index = enviroments_books.indexOf(lastBookSharedPref.get(recyclerViewLastRead.getChildAdapterPosition(v)));
        if(index == -1){ // Todos los libros en lastread deben estar en los libros de ambiente.
            Toast.makeText(v.getContext(), "Error de sincronización bilineal", Toast.LENGTH_SHORT).show();
        }
        else{
            if( !enviroments_books.get(index).getIs_favorite()){
                lastBookSharedPref.get(recyclerViewLastRead.getChildAdapterPosition(v)).setIs_favorite(true); // LocalUpdate
                enviroments_books.get(index).setIs_favorite(true); // GlobalUpdate

                Toast.makeText(v.getContext(), "Se añadió a favoritos", Toast.LENGTH_SHORT).show();
                SaveData();
                SaveLastReadData();
            }
            else{
                lastBookSharedPref.get(recyclerViewLastRead.getChildAdapterPosition(v)).setIs_favorite(false);
                enviroments_books.get(index).setIs_favorite(false); // GlobalUpdate

                Toast.makeText(v.getContext(), "Se quitó de favoritos", Toast.LENGTH_SHORT).show();
                SaveData();
                SaveLastReadData();
            }
        }
        adapterLastRead.notifyItemChanged(recyclerViewLastRead.getChildAdapterPosition(v));
    }

    private void AddToNotification(View v){
        int index = enviroments_books.indexOf(lastBookSharedPref.get(recyclerViewLastRead.getChildAdapterPosition(v)));
        if(index == -1){ // Todos los libros en lastread deben estar en los libros de ambiente.
            Toast.makeText(v.getContext(), "Error de sincronización bilineal", Toast.LENGTH_SHORT).show();
        }
        else{
            if( !enviroments_books.get(index).getIs_synch()){
                lastBookSharedPref.get(recyclerViewLastRead.getChildAdapterPosition(v)).setIs_synch(true); // LocalUpdate
                enviroments_books.get(index).setIs_synch(true); // GlobalUpdate

                Toast.makeText(v.getContext(), "Se añadió a notificaciones", Toast.LENGTH_SHORT).show();
                SaveData();
                SaveLastReadData();
            }
            else{
                lastBookSharedPref.get(recyclerViewLastRead.getChildAdapterPosition(v)).setIs_synch(false);
                enviroments_books.get(index).setIs_synch(false); // GlobalUpdate

                Toast.makeText(v.getContext(), "Se quitó de notificaciones", Toast.LENGTH_SHORT).show();
                SaveData();
                SaveLastReadData();
            }
        }
        adapterLastRead.notifyItemChanged(recyclerViewLastRead.getChildAdapterPosition(v));
    }

    private void DeleteBook(View v){

        int index = enviroments_books.indexOf(lastBookSharedPref.get(recyclerViewLastRead.getChildAdapterPosition(v)));
        int last_index = last_read_stack.indexOf(lastBookSharedPref.get(recyclerViewLastRead.getChildAdapterPosition(v)));

        if(index == -1 || last_index == -1){
            Toast.makeText(v.getContext(), "Error de sincronización bilineal", Toast.LENGTH_SHORT).show();
        }
        else {
            if(enviroments_books.get(index).getIs_deleted()){
                Toast.makeText(v.getContext(), "Error inesperado al eliminar", Toast.LENGTH_SHORT).show();
            }
            else{
                int local_pos = recyclerViewLastRead.getChildAdapterPosition(v);
                // Es importante quitar el resto de condiciones como Notificaciones y Favoritos
                enviroments_books.get(index).setIs_deleted(true);
                enviroments_books.get(index).setIs_synch(false);
                enviroments_books.get(index).setIs_favorite(false);
                last_read_stack.remove(last_index);

                SaveData();
                SaveLastReadData();

                /*Cambios locales*/
                lastBookSharedPref.remove(local_pos);
                adapterLastRead.notifyItemRemoved(local_pos);
                Toast.makeText(v.getContext(), "Se ha movido a la papelera", Toast.LENGTH_SHORT).show();
            }
        }
    }

    private void OpenBook(View v){
        String book_path = lastBookSharedPref.get(recyclerViewLastRead.getChildAdapterPosition(v)).getArticle_path();
        String book_name = (new File(book_path)).getName();

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

                int temp_index = lastBookSharedPref.indexOf(temp_art);
                if(temp_index == -1){ Toast.makeText(getContext(), "Imposible actualizar token", Toast.LENGTH_SHORT).show();}
                else{
                    adapterLastRead.notifyDataSetChanged();
                }
            }
        }
    }
}
