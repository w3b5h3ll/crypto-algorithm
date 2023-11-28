package com.example.mysqlite;

import android.content.Context;
//import android.database.sqlite.SQLiteDatabase;
//import android.database.sqlite.SQLiteOpenHelper;
import android.widget.Toast;

import net.zetetic.database.sqlcipher.SQLiteDatabase;

System.loadLibrary("sqlcipher");
SQLiteDatabase database = SQLiteDatabase.openOrCreateDatabase(databaseFile, password, null, null, null);

import androidx.annotation.Nullable;

public class MyDatabaseHelper extends SQLiteOpenHelper {
    private final String createBook = "create table Book(" + "id integer primary key autoincrement," + "author text," + "price real," + "pages integer," + "name text)";

    private final Context mContext;

    public MyDatabaseHelper(@Nullable Context context, @Nullable String name, @Nullable SQLiteDatabase.CursorFactory factory, int version) {
        super(context, name, factory, version);
        mContext = context;
    }


    @Override
    public void onCreate(SQLiteDatabase sqLiteDatabase) {
        sqLiteDatabase.execSQL(createBook);
        Toast.makeText(mContext, "Create succeeded", Toast.LENGTH_SHORT).show();

    }

    @Override
    public void onUpgrade(SQLiteDatabase sqLiteDatabase, int i, int i1) {

    }
}
