package org.libsdl.app;

import java.io.*;
import java.text.SimpleDateFormat;
import java.util.Calendar;

public class MLog
{
    public static boolean isAppend = false;
    public static boolean isLogging = true;

    public static void info(String info){

        if(!isLogging){
            return;
        }

        try {
            File file = new File("/storage/emulated/0/log.txt");

            if(!file.exists()){
                file.createNewFile();
            }

            BufferedWriter bw = new BufferedWriter(new FileWriter(file, isAppend));
            SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss ");
            String date = sdf.format(Calendar.getInstance().getTime());
            bw.write(date+"<j> "+info+"\r\n");
            bw.flush();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}
