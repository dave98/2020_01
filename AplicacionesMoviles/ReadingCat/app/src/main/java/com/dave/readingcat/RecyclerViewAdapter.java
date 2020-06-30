package com.dave.readingcat;

import android.content.Context;
import android.net.Uri;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.bumptech.glide.Glide;

public class RecyclerViewAdapter extends RecyclerView.Adapter<RecyclerView.ViewHolder> {

    private Context mContext;

    RecyclerViewAdapter(Context mContext){
        this.mContext = mContext;
    }

    @NonNull
    @Override
    public RecyclerView.ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.file_to_list, parent, false);
        return new FileLayoutHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull RecyclerView.ViewHolder holder, int position) {
        ((FileLayoutHolder)holder).file_title_thumbnail.setText(AcceptedExtension.allBookListed.get(position).getName());
        //Load thumbnail using glid library
        Uri uri = Uri.fromFile(AcceptedExtension.allBookListed.get(position));
        Glide.with(mContext)
                .load(uri).thumbnail(0.1f).into(((FileLayoutHolder)holder).file_thumbnail);
    }

    @Override
    public int getItemCount() {
        return AcceptedExtension.allBookListed.size();
    }

    class FileLayoutHolder extends RecyclerView.ViewHolder{

        ImageView file_thumbnail;
        TextView file_title_thumbnail;
        ImageButton file_delete;

        public FileLayoutHolder(@NonNull View itemView) {
            super(itemView);

            file_thumbnail = itemView.findViewById(R.id.file_thumbnail);
            file_title_thumbnail = itemView.findViewById(R.id.file_title_thumbnail);
            file_delete = itemView.findViewById(R.id.file_delete);
        }
    }

}
