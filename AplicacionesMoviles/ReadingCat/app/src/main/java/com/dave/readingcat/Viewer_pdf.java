package com.dave.readingcat;

import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.util.Log;
import android.view.WindowManager;
import android.widget.TextView;
import android.widget.Toast;

import com.dave.readingcat.entities.Article;
import com.github.barteksc.pdfviewer.PDFView;
import com.github.barteksc.pdfviewer.listener.OnLoadCompleteListener;
import com.github.barteksc.pdfviewer.listener.OnPageChangeListener;
import com.github.barteksc.pdfviewer.scroll.DefaultScrollHandle;
import com.google.gson.Gson;
import com.shockwave.pdfium.PdfDocument;


import java.io.File;
import java.util.List;

import static com.dave.readingcat.Dashboard.enviroments_books;

public class Viewer_pdf extends AppCompatActivity implements OnPageChangeListener, OnLoadCompleteListener {
    private static final String TAG = MainActivity.class.getSimpleName();

    PDFView opened_book;
    TextView pdfTitle;
    TextView pdfPages;
    Integer pageNumber = 0;
    Integer pageTotal = 0;
    String book_name;
    String book_path;

    int enviroment_index;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.activity_viewer_pdf);

        book_name = getIntent().getStringExtra("BOOK_NAME");
        book_path = getIntent().getStringExtra("BOOK_PATH");
        opened_book = (PDFView) findViewById(R.id.pdf_book);
        pdfTitle = (TextView) findViewById(R.id.tv_header);
        pdfPages = (TextView) findViewById(R.id.tv_footer);

        Article temp_art = new Article();
        temp_art.setArticle_path(book_path);

        enviroment_index = enviroments_books.indexOf(temp_art);
        if (enviroment_index == -1) {
            Toast.makeText(this, "No se ubico el archivo", Toast.LENGTH_SHORT).show();
            pageNumber = 0;
        } else {
            pageNumber = enviroments_books.get(enviroment_index).getCurrent_page();
        }

        pdfTitle.setText(book_name);

        //Taken from: https://stackoverflow.com/questions/9666030/display-pdf-file-inside-my-android-application
        opened_book.fromFile(new File(book_path))
                .defaultPage(pageNumber)
                .enableSwipe(true)
                .swipeHorizontal(false)
                .onPageChange(this)
                .enableAnnotationRendering(true)
                .onLoad(this)
                .scrollHandle(new DefaultScrollHandle( this))
                .load();
    }

    @Override
    public void onPageChanged(int page, int pageCount) {
        pageNumber = page;
        pageTotal = pageCount;
        setTitle(String.format("%s %s / %s", book_name, page + 1, pageCount));
        pdfPages.setText((page + 1) + "/" + pageCount);
    }

    @Override
    public void loadComplete(int nbPages) {
        PdfDocument.Meta meta = opened_book.getDocumentMeta();
        printBookmarksTree(opened_book.getTableOfContents(), "-");
    }

    public void printBookmarksTree(List<PdfDocument.Bookmark> tree, String sep) {
        for (PdfDocument.Bookmark b : tree) {

            Log.e(TAG, String.format("%s %s, p %d", sep, b.getTitle(), b.getPageIdx()));

            if (b.hasChildren()) {
                printBookmarksTree(b.getChildren(), sep + "-");
            }
        }
    }

    @Override
    public void onBackPressed() {
        if (enviroment_index != -1) {
            enviroments_books.get(enviroment_index).setCurrent_page(pageNumber);
            enviroments_books.get(enviroment_index).setTotal_pages(pageTotal);
            SaveData();
        }
        String stringToPassBack = book_path;
        Intent intent = new Intent();
        intent.putExtra("local_updated_path", stringToPassBack);
        setResult(RESULT_OK, intent);

        //super.onBackPressed();
        finish();
    }

    private void SaveData() {
        SharedPreferences sharedPreferences = getSharedPreferences("shared_preferences", Context.MODE_PRIVATE);
        SharedPreferences.Editor editor = sharedPreferences.edit();
        Gson gson = new Gson();
        String json = gson.toJson(enviroments_books);
        editor.putString("allbooks_list", json);
        editor.apply();
    }
}