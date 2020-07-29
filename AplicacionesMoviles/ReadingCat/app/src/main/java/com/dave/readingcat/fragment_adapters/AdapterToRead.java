package com.dave.readingcat.fragment_adapters;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.dave.readingcat.R;
import com.dave.readingcat.entities.Book;

import org.w3c.dom.Text;

import java.util.ArrayList;

public class AdapterToRead extends RecyclerView.Adapter<AdapterToRead.ViewHolder> implements View.OnClickListener{

    LayoutInflater inflater;
    ArrayList<Book> model;
    private View.OnClickListener listener;

    public AdapterToRead(Context _context, ArrayList<Book> _model){
        this.inflater = LayoutInflater.from(_context);
        this.model = _model;
    }

    @NonNull
    @Override
    public ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = inflater.inflate(R.layout.card_to_list, parent, false);
        view.setOnClickListener(this);
        return new ViewHolder(view);
    }

    public void setOnClickListener(View.OnClickListener _listener){
        this.listener = _listener;
    }

    @Override
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        String book_name = model.get(position).getBook_name();
        String book_date = model.get(position).getBook_date();
        int book_image = model.get(position).getBook_image();

        holder.book_name.setText(book_name);
        holder.book_date.setText(book_date);
        holder.book_image.setImageResource(book_image);
    }

    @Override
    public int getItemCount() {
        return model.size();
    }

    @Override
    public void onClick(View v) {
        if(listener != null){
            listener.onClick(v);
        }
    }

    public class ViewHolder extends RecyclerView.ViewHolder{
        TextView book_name;
        TextView book_date;
        ImageView book_image;

        public ViewHolder(@NonNull View itemView) {
            super(itemView);
            book_name = (TextView) itemView.findViewById(R.id.card_filename);
            book_date = (TextView) itemView.findViewById(R.id.card_desc);
            book_image = (ImageView) itemView.findViewById(R.id.card_thumbnail);
        }
    }

}
