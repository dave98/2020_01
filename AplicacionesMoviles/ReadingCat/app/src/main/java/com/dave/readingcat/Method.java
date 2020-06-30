package com.dave.readingcat;

import java.io.File;

public class Method {
    public static void load_Directory_Files(File directory){
        File[] fileList = directory.listFiles();
        if(fileList != null && fileList.length > 0){
            for(int i = 0; i < fileList.length; i++){
                if(fileList[i].isDirectory()){
                    load_Directory_Files(fileList[i]);
                }
                else{
                    String name = fileList[i].getName().toLowerCase();
                    for(String extension: AcceptedExtension.bookExtension){
                        if(name.endsWith(extension)){
                            AcceptedExtension.allBookListed.add(fileList[i]);
                            break;
                        }
                    }
                }
            }
        }
    }
}
