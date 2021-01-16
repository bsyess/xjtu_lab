package com.sqq.SQL;

import android.content.Context;
import android.database.DatabaseErrorHandler;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

public class DBHelper extends SQLiteOpenHelper {

    // 数据库名称
    private static final String DATABASE_NAME = "zzs.db";
    // 数据库版本号
    private static final int DATABASE_VERSION = 5;
    // 创建表,用户信息表和用户单词表
    public static final String TABLE_USERINFO = "user_info";
    public static final String TABLE_WORDINFO = "word_info";
    // 创建用户信息表,建表语句
    private static final String CREATE_USERINFO_SQL  = "CREATE TABLE "
            + TABLE_USERINFO
            + " (username text primary key,"
            + " password text,"
            + " email text);";


    // 用户单词表
    private static final String CREATE_WORDINFO_SQL = "CREATE TABLE "
            + TABLE_WORDINFO
            + " (_id Integer ,"
            + " username text,"
            + " word text unique,"
            + " translation text);";


    public DBHelper (Context context) {
        this(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    // factory,用于查询时返回Cursor的子类对象;或者传入null使用默认的factory构造
    public DBHelper(Context context, String name, SQLiteDatabase.CursorFactory factory, int version) {
        super(context, name, factory, version);
    }

    public DBHelper(Context context, String name, SQLiteDatabase.CursorFactory factory, int version, DatabaseErrorHandler errorHandler) {
        super(context, name, factory, version, errorHandler);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL(CREATE_USERINFO_SQL);
        db.execSQL(CREATE_WORDINFO_SQL);
        Log.d("1","数据库已建立");
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        if(newVersion > oldVersion) {
            db.execSQL("DROP TABLE IF EXISTS " + TABLE_USERINFO);
            db.execSQL("DROP TABLE IF EXISTS " + TABLE_WORDINFO);
            onCreate(db);
        }
    }

}
