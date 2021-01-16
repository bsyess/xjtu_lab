package com.sqq.SQL;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteStatement;

import com.sqq.entity.User;
import com.sqq.entity.Word;

import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class DatabaseManager<T> {

    private DBHelper dbHelper;
    private static DatabaseManager instance = null;
    private SQLiteDatabase sqLiteDatabase;

    // 构造上下文方法
    private DatabaseManager(Context context) {
        dbHelper = new DBHelper(context);
        sqLiteDatabase = dbHelper.getWritableDatabase();
    }

    // 获取本类对象的实例
    public static final DatabaseManager getInstance(Context context) {
        if(instance == null) {
            if(context == null) {
                throw new RuntimeException("Context is null.");
            }
            instance = new DatabaseManager(context);
        }
        return  instance;
    }

    // 关闭数据库
    public void close() {
        if(sqLiteDatabase.isOpen()) {
            sqLiteDatabase.close();
            sqLiteDatabase = null;
        }
        if(dbHelper != null) {
            dbHelper.close();
            dbHelper = null;
        }
        if(instance != null) {
            instance = null;
        }
    }

    // 执行一条sql语句
    public void execSql(String sql) {
        if(sqLiteDatabase.isOpen()) {
            sqLiteDatabase.execSQL(sql);
        }
        else {
            throw new RuntimeException("The DataBase has already closed");
        }
    }

    // sql执行查询操作的sql语句
    public Cursor queryData2Cursor(String sql, String[] selectionArgs)throws Exception {
        Cursor cursor = null;
        if(sqLiteDatabase.isOpen()) {
            cursor = sqLiteDatabase.rawQuery(sql, selectionArgs);
        } else {
            throw  new RuntimeException("The DataBase has already closed");
        }
        return cursor;
    }

    // 查询表中数据总条数
    public int getDataCounts(String table)throws Exception {
        Cursor cursor = null;
        int counts = 0;
        if(sqLiteDatabase.isOpen()) {
            cursor = queryData2Cursor("select * from " + table, null);
            if(cursor != null && cursor.moveToFirst()) {
                counts = cursor.getCount();
            }
        } else {
            throw  new RuntimeException("The DataBase has already closed");
        }
        return counts;
    }

    // 删除表中所有数据
    public void clearAllData(String table)throws Exception {
        if(sqLiteDatabase.isOpen()) {
            execSql("delete from" + table);
        } else {
            throw  new RuntimeException("The DataBase has already closed");
        }
    }

    // 插入数据
    public long insertDataBysql(String sql, String[] bindArgs)throws Exception {
        long id = 0;
        if(sqLiteDatabase.isOpen()) {
            SQLiteStatement sqLiteStatement = sqLiteDatabase.compileStatement(sql);
            if(bindArgs != null) {
                int size  = bindArgs.length;
                for(int i = 0; i < size; i ++) {
                    sqLiteStatement.bindString(i+1, bindArgs[i]);
                }
                id = sqLiteStatement.executeInsert();
                sqLiteStatement.close();
            }
        } else {
            throw  new RuntimeException("The DataBase has already closed");
        }
        return id;
    }

    /**
     * 插入数据
     * @param table
     * @param values 数据
     * @return 返回插入的ID，返回0，则插入失败
     * @throws Exception
     */
    public long insertData(String table, ContentValues values)throws Exception {
        long id = 0;
        if(sqLiteDatabase.isOpen()) {
            id = sqLiteDatabase.insertOrThrow(table, null, values);
        } else {
            throw  new RuntimeException("The DataBase has already closed");
        }
        return id;
    }

    /**
     * 批量插入数据
     * @param table
     * @param list 数据源
     * @param args 数据键名 Key
     * @return
     * @throws Exception
     */
    public long insertBatchData(String table, List<Map<String, Object>> list, String[] args)
        throws Exception {
        long insertNum = 0;
        sqLiteDatabase.beginTransaction();
        ContentValues contentValues = new ContentValues();
        for(int i=0;i<list.size();i++) {
            for(int j=0;j<args.length;j++) {
                contentValues.put(args[j], list.get(i).get(args[j]).toString());
            }
            long id = insertData(table, contentValues);
            if(id > 0) {
                insertNum++;
            }
        }
        sqLiteDatabase.setTransactionSuccessful();
        sqLiteDatabase.endTransaction();
        return insertNum;
    }

    /**
     * 更新数据
     * @param table
     * @param values 需要更新的数据
     * @param whereClause 表示sql语句中条件部分的语句
     * @param whereArgs 表示占位符的值
     * @return
     * @throws Exception
     */
    public int updateData(String table, ContentValues values,
                          String whereClause, String[] whereArgs)throws Exception {
        int rowsNum = 0;
        if(sqLiteDatabase.isOpen()) {
            rowsNum = sqLiteDatabase.update(table, values, whereClause, whereArgs);
        } else {
            throw  new RuntimeException("The DataBase has already closed");
        }
        return rowsNum;
    }

    /**
     * 删除数据
     * @param sql
     * @param bindArgs sql语句中的参数，参数的顺序对应占位符的顺序
     * @throws Exception
     */
    public void deleteDataBysql(String sql, String[] bindArgs)throws Exception {
        if(sqLiteDatabase.isOpen()) {
            SQLiteStatement sqLiteStatement = sqLiteDatabase.compileStatement(sql);
            if(bindArgs != null) {
                int size = bindArgs.length;
                for(int i=0;i<size;i++) {
                    sqLiteStatement.bindString(i+1, bindArgs[i]);
                }
                sqLiteStatement.execute();
                sqLiteStatement.close();
            }
        } else {
            throw  new RuntimeException("The DataBase has already closed");
        }
    }

    /**
     * 删除数据
     * @param table
     * @param whereClause sql中的条件语句部分
     * @param whereArgs 占位符的值
     * @return
     * @throws Exception
     */
    public long deleteData(String table, String whereClause,
                           String[] whereArgs)throws Exception {
        long rowsNum = 0;
        if(sqLiteDatabase.isOpen()) {
            rowsNum = sqLiteDatabase.delete(table, whereClause, whereArgs);
        } else {
            throw  new RuntimeException("The DataBase has already closed");
        }
        return rowsNum;
    }

    /**
     * @param table
     * @param columns 查询需要返回的列的字段
     * @param selection SQL语句中的条件语句
     * @param selectionArgs 占位符的值
     * @param groupBy 表示分组，可以为null
     * @param having sql语句中的having，可以为null
     * @param orderBy 表示结果排序，可以为null
     * @return
     * @throws Exception
     */
    // select columns from table where column = selection
    public Cursor queryData(String table, String[] columns,
                            String selection, String[] selectionArgs,
                            String groupBy, String having, String orderBy) throws Exception {
        return queryData(table, columns, selection, selectionArgs, groupBy, having, orderBy,null);
    }

    /**
     * @param table
     * @param columns
     * @param selection
     * @param selectionArgs
     * @param groupBy
     * @param having
     * @param orderBy
     * @param limit 表示分页
     * @return
     * @throws Exception
     */
    public Cursor queryData(String table, String[] columns,
                            String selection, String[] selectionArgs,
                            String groupBy, String having, String orderBy,
                            String limit)throws Exception {
        return queryData(false,table,columns,selection,selectionArgs,groupBy,having,orderBy,limit);
    }

    /**
     * @param distinct 为真表示希望每一行唯一
     * @param table
     * @param columns 查询需要返回的列的字段
     * @param selection
     * @param selectionArgs
     * @param groupBy
     * @param having
     * @param orderBy
     * @param limit
     * @return
     * @throws Exception
     */
    public Cursor queryData(boolean distinct, String table,
                            String[] columns, String selection,
                            String[] selectionArgs, String groupBy,
                            String having,String orderBy,String limit)throws Exception {
        return queryData(null,distinct,table,columns,selection,selectionArgs,groupBy,having,orderBy,limit);
    }

    /**
     * @param cursorFactory 游标工厂
     * @param distinct 为真表示希望每一行唯一
     * @param table
     * @param columns 查询需要返回的列的字段
     * @param selection sql语句中的条件语句
     * @param selectionArgs 占位符的值
     * @param groupBy
     * @param having
     * @param orderBy
     * @param limit 表示分页
     * @return
     * @throws Exception
     */
    public Cursor queryData(SQLiteDatabase.CursorFactory cursorFactory, boolean distinct,
                            String table, String[] columns, String selection,
                            String[] selectionArgs, String groupBy,
                            String having, String orderBy, String limit)throws Exception {
        Cursor cursor = null;
        if(sqLiteDatabase.isOpen()) {
            cursor = sqLiteDatabase.queryWithFactory(cursorFactory, distinct, table,
                    columns, selection, selectionArgs, groupBy, having, orderBy, limit);
        } else {
            throw new RuntimeException("The database has already closed!");
        }
        return cursor;
    }

    /**
     *
     * @param sql
     * @param selectionArgs 查询条件
     * @param object JavaBean对象
     * @return
     * @throws Exception
     */
    public List<Map<String, String>> query2List(String sql, String[] selectionArgs,
                                                Object object)throws Exception {
        List<Map<String, String>> list = new ArrayList<>();
        if(sqLiteDatabase.isOpen()) {
            Cursor cursor = null;
            cursor = queryData2Cursor(sql, selectionArgs);
            Field[] fields;
            HashMap<String, String> map;
            if(cursor != null && cursor.getCount() > 0) {
                while (cursor.moveToNext()) {
                    map = new HashMap<>();
                    fields = object.getClass().getDeclaredFields();
                    for(int i=0;i<fields.length;i++) {
                        /*
                         * 1通过key，即列名，得到所在的列索引
                         * 2通过所在行及所在列的索引，得到唯一确定的值
                         * 3将值与键封装到MAP集合中，此条数据读取完毕
                         */
                        map.put(fields[i].getName(),
                                cursor.getString(cursor.getColumnIndex(fields[i].getName())));
                    }
                    list.add(map);
                }
                cursor.close();
            }
        } else {
            throw new RuntimeException("The database has already closed!");
        }
        return list;
    }

    // 查询userName是否存在
    public boolean selectUserName(String userName) {
        Cursor c = sqLiteDatabase.rawQuery("select * from user_info where username = ? ",
                new String[]{userName});
        while(c.moveToNext()){

            return false;
        }
        return true;
    }

    public void insertInfo(User user) {
        sqLiteDatabase.execSQL("insert into user_info values(?,?,?) ",
                new Object[]{user.getUserName(),user.getPwd(),user.getEmail()});
    }

    public boolean checkLogin(User user) {
        Cursor c = sqLiteDatabase.rawQuery("select * from user_info where username = ? and password = ? ",
                new String[]{user.getUserName(),user.getPwd()});
        while(c.getCount()>0){
            c.close();
            return true;
        }
        c.close();
        return false;
    }

    public User selectEmail(String userName) {

        User user = new User();

        Cursor c = sqLiteDatabase.rawQuery("select * from user_info where username = ? ",
                new String[]{userName});
        while(c.moveToNext()){
            user.setEmail(c.getString(2));

        }
        return user;
    }

    public void updatePwd(User user) {
//        ContentValues values = new ContentValues();;
//        values.put("password",user.getPwd());
//
//        try {
//            sqLiteDatabase.update("user_info",values,"username=?",new String[]{
//                    user.getUserName()});
//            System.out.println("修改成");
//
//        } catch (Exception e) {
//            System.out.println("修改失败");
//            e.printStackTrace();
//        }


        sqLiteDatabase.execSQL("update user_info set password=? where username = ?",
                new Object[]{ user.getPwd(),user.getUserName()});
        System.out.println(user.getPwd()+"2222222222"+user.getUserName());
    }

    public void insertWord(Word word) {
        sqLiteDatabase.execSQL("insert into word_info(username,word,translation) values(?,?,?) ",
                new Object[]{word.getUserName(),word.getWord(),word.getTranslation()});
        System.out.println("++++++++++++++++++++++++");
    }

    public List<Word> selectWord(String a) {
        List<Word> list;

        Cursor cursor = sqLiteDatabase.rawQuery("select * from word_info where username = ? ",
                new String[]{a});

        list = new ArrayList<>();
        while(cursor.moveToNext()){
            Word word = new Word();
            word.setWord(cursor.getString(cursor.getColumnIndex("word")));
            word.setTranslation(cursor.getString(cursor.getColumnIndex("translation")));
            System.out.println(word.getWord()+word.getTranslation());
            list.add(word);
        }
        cursor.close();
        return list;
    }

    public void deleteWord(Word word) {
        sqLiteDatabase.execSQL("delete from word_info where word=? and translation=?",
                new Object[]{word.getWord(),word.getTranslation()});
    }

}
