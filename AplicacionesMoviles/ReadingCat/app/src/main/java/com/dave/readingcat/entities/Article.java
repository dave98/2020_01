package com.dave.readingcat.entities;

import java.util.Objects;

public class Article {
    private String article_name;
    private String article_path;

    public Article() {}
    public Article(String article_name, String article_path) {
        this.article_name = article_name;
        this.article_path = article_path;
    }

    public String getArticle_name() {
        return article_name;
    }

    public void setArticle_name(String article_name) {
        this.article_name = article_name;
    }

    public String getArticle_path() {
        return article_path;
    }

    public void setArticle_path(String article_path) {
        this.article_path = article_path;
    }

    @Override
    public boolean equals(Object o){
        if(o == this) return true;
        if(!(o instanceof Article)){
            return false;
        }
        Article article = (Article)o;
        return Objects.equals(this.getArticle_name(), article.getArticle_name()) &&
                Objects.equals(this.getArticle_path(), article.getArticle_path());
    }

    @Override
    public int hashCode(){
        return Objects.hash(article_name, article_path);
    }
}
