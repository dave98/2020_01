package com.dave.readingcat;

import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.pdf.PdfRenderer;
import android.os.ParcelFileDescriptor;

import androidx.annotation.Nullable;

import com.squareup.picasso.Picasso;
import com.squareup.picasso.Request;
import com.squareup.picasso.RequestHandler;

import java.io.File;
import java.io.IOException;

public class PdfRequestHandler extends RequestHandler {
    public static String SCHEME_PDF = "pdf";

    @Override
    public boolean canHandleRequest(Request data) {
        String scheme = data.uri.getScheme();
        return (SCHEME_PDF.equals(scheme));
    }

    @Override
    public Result load(Request data, int networkPolicy) throws IOException {
        ParcelFileDescriptor fileDescriptor = ParcelFileDescriptor.open(new File(data.uri.getPath()), ParcelFileDescriptor.MODE_READ_ONLY);
        PdfRenderer renderer = new PdfRenderer(fileDescriptor);
        final int pageCount = renderer.getPageCount();

        System.out.println("-----> PAGES IN <----: " + pageCount + " with " + data.uri.getPath());

        if(pageCount > 0){
            PdfRenderer.Page page = renderer.openPage(0);
            Bitmap bitmap = Bitmap.createBitmap(page.getWidth(), page.getHeight(), Bitmap.Config.ARGB_8888);
            Canvas canvas = new Canvas(bitmap);
            canvas.drawColor(Color.WHITE);
            canvas.drawBitmap(bitmap, 0, 0, null);
            page.render(bitmap, null, null, PdfRenderer.Page.RENDER_MODE_FOR_DISPLAY);
            page.close();
            return new Result(bitmap, Picasso.LoadedFrom.DISK);
        }
        else{
            Bitmap bitmap = Bitmap.createBitmap(75, 75, Bitmap.Config.ARGB_8888);
            Canvas canvas = new Canvas(bitmap);
            canvas.drawColor(Color.BLACK);
            canvas.drawBitmap(bitmap, 0, 0, null);
            return new Result(bitmap, Picasso.LoadedFrom.DISK);
        }


    }
}
