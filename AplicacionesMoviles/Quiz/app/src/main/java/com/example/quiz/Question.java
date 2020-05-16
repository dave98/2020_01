package com.example.quiz;

public class Question {
    private int mTextResId;
    private  boolean mAnswerTrue;

    public Question(int TextResId, boolean answerTrue){
        mTextResId = TextResId;
        mAnswerTrue = answerTrue;
    }

    public int getTextResId(){
        return mTextResId;
    }
    public void setTextResId(int TextResId){
        mTextResId = TextResId;
    }
    public boolean isAnswerTrue(){
        return mAnswerTrue;
    }
    public void setAnswerTrue(boolean answerTrue){
        mAnswerTrue = answerTrue;
    }
}
