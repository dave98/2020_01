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
import com.dave.readingcat.fragment_adapters.AdapterGarbage;
import com.google.gson.Gson;

import java.io.File;
import java.util.ArrayList;

import static com.dave.readingcat.Dashboard.enviroments_books;

public class FragmentGarbage extends Fragment {

    AdapterGarbage adapterGarbage;
    RecyclerView recyclerViewGarbage;
    ArrayList<Article> garbageBookSharedPref = new ArrayList<>();

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_garbage, container, false);
        LoadData();

        recyclerViewGarbage = view.findViewById(R.id.recyclerView_Garbage);
        recyclerViewGarbage.setLayoutManager(new LinearLayoutManager(getContext()));
        adapterGarbage = new AdapterGarbage(getContext(), garbageBookSharedPref);
        recyclerViewGarbage.setAdapter(adapterGarbage);

        adapterGarbage.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int id = v.getId();
                switch (id){
                    case R.id.card_garbage:
                        DeleteFromDeleted((View) v.getParent().getParent());
                        break;
                    default:
                        OpenBook(v);
                        break;
                }
            }
        });

        return view;
    }
    // Carga todos los datos de enviroments_books(Dashboard) en allBookSharedPref con exepcion de los eliminados
    private void LoadData(){
        for(Article book : enviroments_books){
            if(book.getIs_deleted()){
                garbageBookSharedPref.add(book);
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

    private void DeleteFromDeleted(View v){
        if(!garbageBookSharedPref.get(recyclerViewGarbage.getChildAdapterPosition(v)).getIs_deleted()){
            Toast.makeText(v.getContext(), "Error inesperado al quitar de elimados", Toast.LENGTH_SHORT).show();
        }
        else{
            int pos = recyclerViewGarbage.getChildAdapterPosition(v);

            /*Actualizando el estado global*/
            int index = enviroments_books.indexOf(garbageBookSharedPref.get(recyclerViewGarbage.getChildAdapterPosition(v)));
            if(index != -1){
                enviroments_books.get(index).setIs_deleted(false);
                SaveData();
            }
            else{ Toast.makeText(v.getContext(), "Error de sincronización en capa bilineal", Toast.LENGTH_SHORT).show(); }

            /*Actualizando estado local*/
            garbageBookSharedPref.remove(pos);
            adapterGarbage.notifyItemRemoved(pos);
            Toast.makeText(v.getContext(), "Se quitó de la papelera", Toast.LENGTH_SHORT).show();
        }
    }

    private void OpenBook(View v){
        String book_path = garbageBookSharedPref.get(recyclerViewGarbage.getChildAdapterPosition(v)).getArticle_path();
        String book_name = (new File(book_path)).getName();

        Intent intent = new Intent(getActivity(), Viewer_pdf.class);
        intent.putExtra("BOOK_NAME", book_name);
        intent.putExtra("BOOK_PATH", book_path);
        startActivity(intent);
    }



}
