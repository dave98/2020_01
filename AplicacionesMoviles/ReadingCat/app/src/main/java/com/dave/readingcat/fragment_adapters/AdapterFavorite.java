package com.dave.readingcat.fragment_adapters;

import android.content.Context;
import android.graphics.Color;
import android.net.Uri;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.bumptech.glide.Glide;
import com.dave.readingcat.R;
import com.dave.readingcat.entities.Article;

import java.io.File;
import java.util.ArrayList;
import java.util.Date;

public class AdapterFavorite extends RecyclerView.Adapter<AdapterFavorite.ViewHolder> implements View.OnClickListener {
    LayoutInflater inflater;
    ArrayList<Article> articles_in;
    private Context mContext;
    private View.OnClickListener listener;

    public AdapterFavorite(Context _context, ArrayList<Article> _articles_in){
        this.inflater = LayoutInflater.from(_context);
        this.articles_in = _articles_in;
        this.mContext = _context;
    }

    @Override
    public void onClick(View v) {
        if (listener != null) {
            listener.onClick(v);
        }
    }

    public void setOnClickListener(View.OnClickListener _listener) {
        this.listener = _listener;
    }


    @NonNull
    @Override
    public AdapterFavorite.ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = inflater.inflate(R.layout.card_to_list, parent, false);
        view.setOnClickListener(this);
        return new ViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull AdapterFavorite.ViewHolder holder, int position) {
        File data_dir = new File(articles_in.get(position).getArticle_path());
        Date file_date = new Date((data_dir.lastModified()));

        holder.book_name.setText(data_dir.getName());
        holder.book_date.setText(file_date.toString());                               // Fecha de ultima modificación
        holder.book_size.setText(String.valueOf(data_dir.length() / 1024) + " Kb");     // Tamaño del Archivo

        if(articles_in.get(position).getTotal_pages() == 0){
            holder.book_progress.setText("Aún no se ha leído");
            holder.book_progress_bar.setProgress(0);
        }
        else{
            int total = articles_in.get(position).getTotal_pages();
            int read_at = articles_in.get(position).getCurrent_page();
            holder.book_progress.setText("En progreso: " + (read_at+1) + " de " + total);
            holder.book_progress_bar.setMax(total);
            holder.book_progress_bar.setProgress(read_at+1);
        }

        /*
        Uri uri = Uri.fromFile(data_dir); // Getting thumbnail
        Glide.with(this.mContext)
                .load(uri).thumbnail(0.1f).into(holder.book_image);
        */

        if(articles_in.get(position).getIs_favorite()){ holder.book_favorite.setColorFilter(Color.BLACK); }
        else{ holder.book_favorite.setColorFilter(Color.GRAY); }

        if(articles_in.get(position).getIs_synch()){ holder.book_notification.setColorFilter(Color.BLACK); }
        else{ holder.book_notification.setColorFilter(Color.GRAY); }

        if(articles_in.get(position).getIs_deleted()){ holder.book_garbage.setColorFilter(Color.BLACK); }
        else{ holder.book_garbage.setColorFilter(Color.GRAY); }


        holder.book_favorite.setOnClickListener(this);
        holder.book_collection.setOnClickListener(this);
        holder.book_notification.setOnClickListener(this);
        holder.book_garbage.setOnClickListener(this);
    }

    @Override
    public int getItemCount() { return articles_in.size(); }

    public class ViewHolder extends RecyclerView.ViewHolder{
        ImageView book_image;
        TextView book_name;
        TextView book_date;
        TextView book_size;
        TextView book_progress;
        ProgressBar book_progress_bar;

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
            book_progress = (TextView) itemView.findViewById(R.id.card_desc_3);
            book_progress_bar = (ProgressBar) itemView.findViewById(R.id.card_progress_bar);

            book_favorite = (ImageButton) itemView.findViewById(R.id.card_addfavorite);
            book_collection = (ImageButton) itemView.findViewById(R.id.card_bookcollection);
            book_notification = (ImageButton) itemView.findViewById(R.id.card_notifications);
            book_garbage = (ImageButton) itemView.findViewById(R.id.card_garbage);
        }
    }

    public void filterList(ArrayList<Article> filteredList){
        articles_in = filteredList;
        notifyDataSetChanged();
    }

}
