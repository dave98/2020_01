package com.dave.readingcat.fragment_adapters;

import android.content.Context;
import android.media.Image;
import android.net.Uri;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.bumptech.glide.Glide;
import com.dave.readingcat.AcceptedExtension;
import com.dave.readingcat.R;
import com.dave.readingcat.entities.Article;

import java.io.File;
import java.util.ArrayList;
import java.util.Date;

public class AdapterAllBooks extends RecyclerView.Adapter<AdapterAllBooks.ViewHolder> implements View.OnClickListener {

    LayoutInflater inflater;
    ArrayList<Article> articles_in;
    private Context mContext;
    private View.OnClickListener listener;

    public AdapterAllBooks(Context _context, ArrayList<Article> _articles_in) {
        this.inflater = LayoutInflater.from(_context);
        this.articles_in = _articles_in;
        this.mContext = _context;
    }

    @NonNull
    @Override
    public AdapterAllBooks.ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = inflater.inflate(R.layout.card_to_list, parent, false);
        view.setOnClickListener(this);
        return new ViewHolder(view);
    }

    public void setOnClickListener(View.OnClickListener _listener) {
        this.listener = _listener;
    }

    @Override
    public void onBindViewHolder(@NonNull AdapterAllBooks.ViewHolder holder, final int position) {
        File data_dir = new File(articles_in.get(position).getArticle_path());
        Date file_date = new Date((data_dir.lastModified()));

        holder.book_name.setText(articles_in.get(position).getArticle_name());
        holder.book_date.setText(file_date.toString());                               // Fecha de ultima modificación
        holder.book_size.setText(String.valueOf(data_dir.length() / 1024) + " Kb");     // Tamaño del Archivo

        /*
        Uri uri = Uri.fromFile(data_dir); // Getting thumbnail
        Glide.with(this.mContext)
                .load(uri).thumbnail(0.1f).into(holder.book_image);
        */

        holder.book_favorite.setOnClickListener(this);
        holder.book_collection.setOnClickListener(this);
        holder.book_notification.setOnClickListener(this);
        holder.book_garbage.setOnClickListener(this);
    }

    @Override
    public int getItemCount() {
        return articles_in.size();
    }

    @Override
    public void onClick(View v) {
        if (listener != null) {
            listener.onClick(v);
        }
    }

    public class ViewHolder extends RecyclerView.ViewHolder {
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
