package com.dave.readingcat;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

public class FragmentAllBooks extends Fragment implements View.OnClickListener{
    private Button book_button;
    View rootView;

    @Override
    public void onCreate(Bundle savedInstanceState){
        super .onCreate(savedInstanceState);
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        rootView = inflater.inflate(R.layout.fragment_all_books_and_doc, container, false);
        book_button = (Button) rootView.findViewById(R.id.all_book_buttom);
        book_button.setOnClickListener(this);
        return rootView;
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.all_book_buttom:
                Toast.makeText(rootView.getContext(), "All books fragment", Toast.LENGTH_SHORT).show();
                break;
        }
    }
}
