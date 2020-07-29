package com.dave.readingcat.fragments;

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
import com.dave.readingcat.entities.Book;
import com.dave.readingcat.fragment_adapters.AdapterToRead;

import java.util.ArrayList;

public class FragmentToRead extends Fragment {

    AdapterToRead adapterToRead;
    RecyclerView recyclerViewToRead;
    ArrayList<Book> listBook;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        //return inflater.inflate(R.layout.fragment_to_read, container, false);
        View view = inflater.inflate(R.layout.fragment_to_read, container, false);
        recyclerViewToRead = view.findViewById(R.id.recyclerView);
        listBook = new ArrayList<>();
        list_load();
        show_data();
        return  view;
    }
    public void list_load(){
        listBook.add(new Book("book1", "book_1_date", R.drawable.ic_garbage ));
        listBook.add(new Book("book2", "book_2_date", R.drawable.ic_garbage ));
        listBook.add(new Book("book3", "book_3_date", R.drawable.ic_garbage ));
        listBook.add(new Book("book4", "book_4_date", R.drawable.ic_garbage ));
        listBook.add(new Book("book5", "book_5_date", R.drawable.ic_garbage ));
        listBook.add(new Book("book6", "book_6_date", R.drawable.ic_garbage ));
    }

    public void show_data(){
        recyclerViewToRead.setLayoutManager((new LinearLayoutManager(getContext()))); // In activity it would have been "this", but for fragments is "getContext()"
        adapterToRead = new AdapterToRead(getContext(), listBook);
        recyclerViewToRead.setAdapter(adapterToRead);

        adapterToRead.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String book_name = listBook.get(recyclerViewToRead.getChildAdapterPosition(v)).getBook_name();
                Toast.makeText(getContext(), "Seleccion: " + book_name, Toast.LENGTH_SHORT).show();
            }
        });
    }
}
