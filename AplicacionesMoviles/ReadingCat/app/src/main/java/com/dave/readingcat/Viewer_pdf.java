package com.dave.readingcat;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.Toast;

import com.github.barteksc.pdfviewer.PDFView;

import java.io.File;

public class Viewer_pdf extends AppCompatActivity {

    PDFView opened_book;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_viewer_pdf);

        String book_name = getIntent().getStringExtra("BOOK_NAME");
        String book_path = getIntent().getStringExtra("BOOK_PATH");

        opened_book = (PDFView)findViewById(R.id.pdf_book);
        opened_book.fromFile(new File(book_path)).load();
    }
}