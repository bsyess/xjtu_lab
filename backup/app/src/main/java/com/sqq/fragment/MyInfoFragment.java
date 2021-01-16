package com.sqq.fragment;

import android.content.DialogInterface;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.support.v7.app.AlertDialog;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.TextView;
import android.widget.Toast;

import com.sqq.SQL.DatabaseManager;
import com.sqq.entity.Data;
import com.sqq.entity.Word;
import com.sqq.main.R;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MyInfoFragment extends Fragment {
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.activity_list, container,false);
        return view;
    }

    private Button btn_return;
    private Button btn_count;
    private Button btn_delete;
    private Button btn_cancel;
    private Button btn_choose;
    private CheckBox check_box;

    private FragmentManager fragmentManager;
    private FragmentTransaction fragmentTransaction;

    private TextView mTvusername;
    private ListView mListview;
    private List<Word> list;

    List<Map<String,Object>> listItems;
    Map<String, Object> map;

    private SimpleAdapter simpleAdapter;

    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);

        btn_return = getActivity().findViewById(R.id.btn_return);
        btn_count = getActivity().findViewById(R.id.btn_count);
        btn_delete = getActivity().findViewById(R.id.btn_delete);
        btn_cancel = getActivity().findViewById(R.id.btn_cancel);
        btn_choose = getActivity().findViewById(R.id.btn_choose);
        mTvusername = getActivity().findViewById(R.id.tv_username);
        mListview = getActivity().findViewById(R.id.mList);

        // 拿到事务管理器并开始事务
        fragmentManager = getFragmentManager();
        fragmentTransaction = fragmentManager.beginTransaction();

        btn_return.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Data.setA("");
                getFragmentManager().beginTransaction().addToBackStack(null)
                        .replace(R.id.fragment,new Mine()).commit();
            }
        });

        init();

        btn_count.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v) {
                AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
                builder.setMessage("共收藏了" + (mListview.getCount()-1) + "个单词");
                builder.setNegativeButton("关闭", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {

                    }
                });
                builder.show();
            }
        });

        btn_delete.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int selected = 0;
                for (int i = 1; i < mListview.getCount(); i++) {
                    check_box = (CheckBox) mListview.getChildAt(i).findViewById(R.id.cb_select);
                    if (check_box.isChecked())
                        selected++;
                }
                if (selected == 0)
                    Toast.makeText(getActivity(),"未选中单词",Toast.LENGTH_SHORT).show();
                else{
                    AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());

                    builder.setTitle("删除");
                    builder.setMessage("确认删除？");

                    builder.setPositiveButton("确认", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            for (int i = 1; i < mListview.getCount(); i++) {
                                check_box = (CheckBox) mListview.getChildAt(i).findViewById(R.id.cb_select);
                                if (check_box.isChecked()){
                                    Word word = list.get(i-1);
                                    list.remove(i-1);
                                    DatabaseManager databaseManager = DatabaseManager.getInstance(getActivity());
                                    databaseManager.deleteWord(word);
                                    databaseManager.close();
                                }
                            }
                            init();
                        }
                    });
                    builder.setNegativeButton("取消", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {

                        }
                    });

                    builder.show();
                }
            }
        });

        btn_cancel.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                for (int i = 0; i < mListview.getCount(); i++) {
                    check_box = (CheckBox) mListview.getChildAt(i).findViewById(R.id.cb_select);
                    check_box.setChecked(false);
                }
            }
        });

        btn_choose.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                for (int i = 0; i < mListview.getCount(); i++) {
                    check_box = (CheckBox) mListview.getChildAt(i).findViewById(R.id.cb_select);
                    check_box.setChecked(true);
                }
            }
        });
    }

    private void init(){
        int number = 1;
        String username = Data.getA();
        System.out.println(username);
        mTvusername.setText(username);
        DatabaseManager databaseManager = DatabaseManager.getInstance(getActivity());
        list = databaseManager.selectWord(Data.getA());
        listItems=new ArrayList<Map<String, Object>>();
        map = new HashMap<String,Object>();
        map.put("number","No.");
        map.put("word","Word");
        map.put("translation","Translation");
        listItems.add(map);
        for(Word word:list){
            map = new HashMap<String,Object>();
            map.put("number",number);
            map.put("word",word.getWord());
            map.put("translation",word.getTranslation());
            listItems.add(map);
            number++;
        }
        simpleAdapter = new SimpleAdapter(getActivity(),listItems,R.layout.word_item,
                new String[] {"number","word","translation"},new int[]{R.id.tv_number,R.id.tv_word,R.id.tv_translation});
        mListview.setAdapter(simpleAdapter);
    }

}
