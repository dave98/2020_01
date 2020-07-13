package com.dave.readingcat;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
//import androidx.recyclerview.widget.LinearLayoutManager;
//import androidx.recyclerview.widget.RecyclerView;

public class FragmentLastRead extends Fragment {

    View root_view;
    //private RecyclerView recyclerView;
    //private RecyclerViewAdapter recyclerViewAdapter;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        //17:53
        //root_view = inflater.inflate(R.layout.fragment_last_read, container, false);
        //recyclerView = root_view.findViewById(R.id.recyclerView);
        //recyclerView.setLayoutManager(new LinearLayoutManager(root_view.getContext()));

        //recyclerView.setHasFixedSize(true);
        //recyclerView.setItemViewCacheSize(20);
        //recyclerView.setDrawingCacheEnabled(true);
        //recyclerView.setDrawingCacheQuality(View.DRAWING_CACHE_QUALITY_HIGH);
        //recyclerView.setNestedScrollingEnabled(false);

        //recyclerViewAdapter = new RecyclerViewAdapter(root_view.getContext());
        //recyclerView.setAdapter(recyclerViewAdapter);
        //return  root_view;
        return inflater.inflate(R.layout.fragment_last_read, container, false);
    }
}
