package com.dave.readingcat.entities;

import java.io.File;
import java.util.Date;
import java.util.Objects;

public class Article implements Comparable<Article> {
    private String article_path;
    private Boolean is_favorite;
    private Boolean is_deleted;
    private Boolean is_synch;

    public Article() {}
    public Article(String article_path) {
        this.article_path = article_path;
        this.is_favorite = false;
        this.is_deleted = false;
        this.is_synch = false;
    }

    public String getArticle_path() {
        return article_path;
    }

    public void setArticle_path(String article_path) {
        this.article_path = article_path;
    }

    public Boolean getIs_favorite() {
        return is_favorite;
    }

    public void setIs_favorite(Boolean is_favorite) {
        this.is_favorite = is_favorite;
    }

    public Boolean getIs_deleted() {
        return is_deleted;
    }

    public void setIs_deleted(Boolean is_deleted) {
        this.is_deleted = is_deleted;
    }

    public Boolean getIs_synch() {
        return is_synch;
    }

    public void setIs_synch(Boolean is_synch) {
        this.is_synch = is_synch;
    }

    @Override
    public boolean equals(Object o){
        if(o == this) return true;
        if(!(o instanceof Article)){
            return false;
        }
        Article article = (Article)o;
        return Objects.equals(this.getArticle_path(), article.getArticle_path());
    }

    @Override
    public int hashCode(){
        return Objects.hash(article_path);
    }

    @Override
    public int compareTo(Article o) {
        Date temp_here = new Date( new File(this.getArticle_path()).lastModified() );
        Date temp_there = new Date( new File(o.getArticle_path()).lastModified() );
        return temp_here.compareTo(temp_there);
    }
}
