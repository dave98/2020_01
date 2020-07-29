package com.dave.readingcat.entities;

public class Book {
    private String book_name;
    private String book_date;
    private int book_image; // Mnajando identificador de las imagenes

    public Book(){}
    public Book(String book_name, String book_date, int book_image) {
        this.book_name = book_name;
        this.book_date = book_date;
        this.book_image = book_image;
    }

    public String getBook_name() {
        return book_name;
    }

    public void setBook_name(String book_name) {
        this.book_name = book_name;
    }

    public String getBook_date() {
        return book_date;
    }

    public void setBook_date(String book_date) {
        this.book_date = book_date;
    }

    public int getBook_image() {
        return book_image;
    }

    public void setBook_image(int book_image) {
        this.book_image = book_image;
    }
}


