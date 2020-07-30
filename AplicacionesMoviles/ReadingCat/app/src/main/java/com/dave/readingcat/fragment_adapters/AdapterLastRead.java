package com.dave.readingcat.fragment_adapters;

import android.content.Context;
import android.graphics.Color;
import android.net.Uri;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.appcompat.widget.ViewUtils;
import androidx.recyclerview.widget.RecyclerView;

import com.bumptech.glide.Glide;
import com.dave.readingcat.R;
import com.dave.readingcat.entities.Article;

import java.io.File;
import java.util.ArrayList;
import java.util.Date;

public class AdapterLastRead extends RecyclerView.Adapter<AdapterLastRead.ViewHolder> implements View.OnClickListener{

    LayoutInflater inflater;
    ArrayList<Article> arcticles_lastread;
    private Context mcontext;
    private View.OnClickListener listener;


    public AdapterLastRead(Context _context, ArrayList<Article> _arcticles_lastread){
        this.inflater = LayoutInflater.from(_context);
        this.arcticles_lastread = _arcticles_lastread;
        this.mcontext = _context;
    }

    @NonNull
    @Override
    public AdapterLastRead.ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = inflater.inflate(R.layout.card_to_list, parent, false);
        view.setOnClickListener(this);
        return new ViewHolder(view);
    }

    public void setOnClickListener(View.OnClickListener _listener){this.listener = _listener;}

    @Override
    public void onBindViewHolder(@NonNull AdapterLastRead.ViewHolder holder, int position) {
        File data_dir = new File(arcticles_lastread.get(position).getArticle_path());
        Date file_date = new Date((data_dir.lastModified()));

        holder.book_name.setText(data_dir.getName());
        holder.book_date.setText(file_date.toString());
        holder.book_size.setText(String.valueOf(data_dir.length()/1024) + " Kb"); // Tamaño del Archivo

        /*
        Uri uri = Uri.fromFile(data_dir);
        Glide.with(this.mcontext)
                .load(uri).thumbnail(0.1f).into(holder.book_image);
        */
        if(arcticles_lastread.get(position).getIs_favorite()){ holder.book_favorite.setColorFilter(Color.BLACK); }
        else{ holder.book_favorite.setColorFilter(Color.GRAY); }

        if(arcticles_lastread.get(position).getIs_synch()){ holder.book_notification.setColorFilter(Color.BLACK); }
        else{ holder.book_notification.setColorFilter(Color.GRAY); }

        if(arcticles_lastread.get(position).getIs_deleted()){ holder.book_garbage.setColorFilter(Color.BLACK); }
        else{ holder.book_garbage.setColorFilter(Color.GRAY); }


        holder.book_favorite.setOnClickListener(this);
        holder.book_collection.setOnClickListener(this);
        holder.book_notification.setOnClickListener(this);
        holder.book_garbage.setOnClickListener(this);
    }

    @Override
    public int getItemCount() {
        return arcticles_lastread.size();
    }

    @Override
    public void onClick(View v) {
        if(this.listener != null){
            listener.onClick(v);
        }
    }

    public class ViewHolder extends RecyclerView.ViewHolder{
        ImageView book_image;
        TextView book_name;
        TextView book_date;
        TextView book_size;

        ImageButton book_favorite;
        ImageButton book_collection;
        ImageButton book_notification;
        ImageButton book_garbage;

        public ViewHolder(@NonNull View itemView) {
            super(itemView);
            book_image = (ImageView) itemView.findViewById(R.id.card_thumbnail);
            book_name = (TextView) itemView.findViewById(R.id.card_filename);
            book_date = (TextView) itemView.findViewById(R.id.card_desc);
            book_size = (TextView) itemView.findViewById(R.id.card_desc_2);

            book_favorite = (ImageButton) itemView.findViewById(R.id.card_addfavorite);
            book_collection = (ImageButton) itemView.findViewById(R.id.card_bookcollection);
            book_notification = (ImageButton) itemView.findViewById(R.id.card_notifications);
            book_garbage = (ImageButton) itemView.findViewById(R.id.card_garbage);
        }
    }

}
