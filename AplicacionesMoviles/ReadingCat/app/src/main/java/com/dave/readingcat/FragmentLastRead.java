package com.dave.readingcat;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.dave.readingcat.entities.Article;
import com.dave.readingcat.entities.Book;
import com.dave.readingcat.fragment_adapters.AdapterLastRead;
import com.dave.readingcat.fragment_adapters.AdapterToRead;
import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import java.lang.reflect.Type;
import java.util.ArrayList;

public class FragmentLastRead extends Fragment {

    AdapterLastRead adapterLastRead;
    RecyclerView recyclerViewLastRead;
    ArrayList<Article> lastBookSharedPref = new ArrayList<>();

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_last_read, container, false);
        LoadData();

        recyclerViewLastRead = view.findViewById(R.id.recyclerView_LastRead);
        recyclerViewLastRead.setLayoutManager(new LinearLayoutManager(getContext()));

        adapterLastRead = new AdapterLastRead(getContext(), lastBookSharedPref);
        recyclerViewLastRead.setAdapter(adapterLastRead);

        adapterLastRead.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String book_name = lastBookSharedPref.get(recyclerViewLastRead.getChildAdapterPosition(v)).getArticle_name();
                String book_path = lastBookSharedPref.get(recyclerViewLastRead.getChildAdapterPosition(v)).getArticle_path();

                Intent intent = new Intent(getActivity(), Viewer_pdf.class);
                intent.putExtra("BOOK_NAME", book_name);
                intent.putExtra("BOOK_PATH", book_path);

                startActivity(intent);
            }
        });

        return view;
    }

    private void LoadData(){
        SharedPreferences sharedPreferences = this.getActivity().getSharedPreferences("shared_preferences", Context.MODE_PRIVATE); // LookHere: https://stackoverflow.com/questions/11741270/android-sharedpreferences-in-fragment
        Gson gson = new Gson();
        String json = sharedPreferences.getString("lastread_list", null);
        Type type = new TypeToken<ArrayList<Article>>(){}.getType();
        lastBookSharedPref = gson.fromJson(json, type);

        if(lastBookSharedPref == null){
            lastBookSharedPref = new ArrayList<>();
        }
    }
}
