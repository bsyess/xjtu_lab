package com.sqq.fragment;

import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.text.TextUtils;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;
import com.sqq.SQL.DatabaseManager;
import com.sqq.entity.Data;
import com.sqq.entity.Word;
import com.sqq.main.R;
import com.squareup.okhttp.OkHttpClient;
import com.squareup.okhttp.Request;
import com.squareup.okhttp.Response;

import java.io.UnsupportedEncodingException;
import java.lang.reflect.Type;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.List;
import java.util.Random;

public class TranslateFragment extends Fragment {
    private EditText need_translation_text;
    private Spinner need_translation_spinner;
    private TextView wait_translation_text;
    private TextView push_word_text;
    private Spinner wait_translation_spinner;
    private Button translation_button;
    private Button collect_button;
    private Button push_word_button;
    private Button look_translation_button;
    private List<Word> wordList;
    private int wordIndex;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.translate_fragment, container,false);
        return view;
    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);

        wait_translation_spinner=getActivity().findViewById(R.id.wait_translation_spinner);
        wait_translation_text=getActivity().findViewById(R.id.wait_translation_text);
        need_translation_spinner=getActivity().findViewById(R.id.need_translation_spinner);
        need_translation_text=getActivity().findViewById(R.id.need_translation_text);
        push_word_text=getActivity().findViewById(R.id.push_word_text);

        translation_button=getActivity().findViewById(R.id.translation_button);
        collect_button=getActivity().findViewById(R.id.collect_button);
        push_word_button=getActivity().findViewById(R.id.push_word_button);
        look_translation_button=getActivity().findViewById(R.id.look_translation_button);
        translation_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String q=need_translation_text.getText().toString();
                translate(q);
            }
        });
        collect_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(Data.getA().equals("")){
                    Toast.makeText(getActivity(),"请先登录",Toast.LENGTH_SHORT).show();
                }
                else{
                    //进行收藏
                    Word word=new Word();
                    word.setUserName(Data.getA());
                    //存放顺序为先英文后中文
                    long s=need_translation_spinner.getSelectedItemId();
                    if (s==0) {
                        word.setWord(need_translation_text.getText().toString());
                        word.setTranslation(wait_translation_text.getText().toString());
                    }
                    else {
                        word.setWord(wait_translation_text.getText().toString());
                        word.setTranslation(need_translation_text.getText().toString());
                    }
                    DatabaseManager databaseManager=DatabaseManager.getInstance(getActivity());
                    wordList = databaseManager.selectWord(Data.getA());
                    boolean flag=false;
                    for(int i=0;i<wordList.size();i++)
                    {
                        if(wordList.get(i).getWord().equals(word.getWord()) || word.getWord().equals(""))
                        {
                            flag=true;
                            break;
                        }
                    }
                    if(flag)
                        Toast.makeText(getActivity(),"已收藏",Toast.LENGTH_SHORT).show();
                    else
                    {
                        databaseManager.insertWord(word);
                        Toast.makeText(getActivity(),"收藏成功",Toast.LENGTH_SHORT).show();
                    }

                }
            }
        });
        push_word_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String username = Data.getA();
                if(username.equals("")){
                    Toast.makeText(getActivity(),"请先登录",Toast.LENGTH_SHORT).show();
                }else {
                    DatabaseManager databaseManager = DatabaseManager.getInstance(getActivity());
                    wordList = databaseManager.selectWord(Data.getA());
                    // 从用户的收藏单词中随机选择一个
                    Random random = new Random();
                    wordIndex = random.nextInt(wordList.size());
                    String word = wordList.get(wordIndex).getWord();
                    push_word_text.setText(word);
                }
            }
        });
        look_translation_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String username = Data.getA();
                if(username.equals("")){
                    Toast.makeText(getActivity(),"请先登录",Toast.LENGTH_SHORT).show();
                }else {
                    DatabaseManager databaseManager = DatabaseManager.getInstance(getActivity());
                    wordList = databaseManager.selectWord(Data.getA());
                    String wordTranslation = wordList.get(wordIndex).getTranslation();
                    push_word_text.setText(wordTranslation);
                }
            }
        });
    }

    @NonNull
    public static String md5(String string) {
        if (TextUtils.isEmpty(string)) {
            return "";
        }
        MessageDigest md5 = null;
        try {
            md5 = MessageDigest.getInstance("MD5");
            byte[] bytes = md5.digest(string.getBytes());
            StringBuilder result = new StringBuilder();
            for (byte b : bytes) {
                String temp = Integer.toHexString(b & 0xff);
                if (temp.length() == 1) {
                    temp = "0" + temp;
                }
                result.append(temp);
            }
            return result.toString();
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
        return "";
    }
    public String urlEncodeUTF8(String source) {
        String result = source;
        try {
            result = java.net.URLEncoder.encode(source, "utf-8");
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
        return result;
    }
    public void translate(String source) {
        if(source.isEmpty())
            return;
        long s1=need_translation_spinner.getSelectedItemId();//s1为被翻译的语种，s2为需要翻译的语种
        long s2=wait_translation_spinner.getSelectedItemId();
        String from=null;
        String to=null;
        if(s1==0) {
            boolean flag=test1(source);
            from="en";
            to="zh";
            if(!flag) {
                wait_translation_text.setText("请输入正确的英文");
                return;
            }
        }
        else if(s1==1) {
            boolean flag=test2(source);
            from="zh";
            to="en";
            if(!flag) {
                wait_translation_text.setText("请输入正确的中文");
                return;
            }
        }
        if(s1==s2) {
            wait_translation_text.setText(source);
            return;
        }

        String appid="20181204000243056";
        String secretKey ="UVtQDQzcPW3kVxHfFEDU";
        String salt="";
        for(int i=0;i<10;i++){
            salt+=String.valueOf((int)(Math.random()*10));
        }
        String sign=appid+source+salt+secretKey;
        String requestUrl="http://api.fanyi.baidu.com/api/trans/vip/translate";
        String s=md5(sign);
        // 对参数source的值进行urlEncode utf-8编码
        final String requestUrl1=requestUrl+"?appid="+appid+"&q="+urlEncodeUTF8(source)+"&from="+from+"&to="+to+"&salt="+salt+"&sign="+s;
        Log.i("requestUrl",requestUrl1);

        new Thread(){
            @Override
            public void run(){
                OkHttpClient client = new OkHttpClient();
                Request request = new Request.Builder()
                        .url(requestUrl1)
                        .get()
                        .build();
                try{
                    Response response = client.newCall(request).execute();
                    Gson gson = new Gson();
                    Type type = new TypeToken<TranslateResult>() {}.getType();
                    final TranslateResult json = gson.fromJson(response.body().string(), type);
                    wait_translation_text.setText(json.getTrans_result().get(0).getDst());
                    Log.i("json------", json.getTrans_result().get(0).getDst());
                }catch (Exception e){
                    Log.i("json------", e.getMessage()+"/"+e.getCause());
                }
            }
        }.start();
    }

    public boolean test1(String s) {
        int chr;
        boolean flag=true;
        for(int i =s.length();--i>=0;) {
            chr=s.charAt(i);
            if((chr>=65&&chr<=90)||(chr>=97&&chr<=122)||chr==32)
                continue;
            else
                flag=false;
        }
        return flag;
    }
    public boolean test2(String s) {
        int chr;
        boolean flag=true;
        for(int i =s.length();--i>=0;) {
            chr=s.charAt(i);
            if((chr>=65&&chr<=90)||(chr>=97&&chr<=122)||chr==32){
                flag=false;
                break;
            }
        }
        return flag;
    }
}


