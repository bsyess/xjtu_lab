package com.sqq.fragment;

import android.content.SharedPreferences;
import android.preference.PreferenceManager;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.os.Bundle;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.sqq.MD5.md5Password;
import com.sqq.SQL.DatabaseManager;
import com.sqq.entity.Data;
import com.sqq.entity.User;
import com.sqq.main.R;


public class Mine extends Fragment {
    private EditText et_userName;
    private EditText et_password;
    private ImageView iv_usernameClear;
    private ImageView iv_pwdClear;

    private CheckBox cb_checkbox;
    private TextView forget_pwd;

    private Button btn_login;
    private Button btn_register;

    private SharedPreferences preferences;
    private SharedPreferences.Editor editor;

    private FragmentManager fragmentManager;
    private FragmentTransaction fragmentTransaction;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        return inflater.inflate(R.layout.mine_fragment, container,false);
    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);

        preferences = PreferenceManager.getDefaultSharedPreferences(getActivity());

        et_userName = getActivity().findViewById(R.id.et_userName);
        et_password = getActivity().findViewById(R.id.et_password);
        iv_usernameClear = getActivity().findViewById(R.id.iv_usernameClear);
        iv_pwdClear = getActivity().findViewById(R.id.iv_pwdClear);
        cb_checkbox = getActivity().findViewById(R.id.cb_checkbox);
        forget_pwd = getActivity().findViewById(R.id.forget_pwd);
        btn_login = getActivity().findViewById(R.id.btn_login);
        btn_register = getActivity().findViewById(R.id.btn_register);
        init();

        // 拿到事务管理器并开始事务
        fragmentManager = getFragmentManager();
        fragmentTransaction = fragmentManager.beginTransaction();

        boolean isRemember = preferences.getBoolean("rememberPassword",false);
        if(isRemember){
            //将账号和密码都设置到文本中
            String account = preferences.getString("account","");
            String password = preferences.getString("password","");
            et_userName.setText(account);
            et_password.setText(password);
        }

        // 找回密码
        forget_pwd.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                fragmentTransaction.addToBackStack(null).replace(R.id.fragment,new ForgetPwdFragment()).commit();
            }
        });

        // 注册
        btn_register.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                getFragmentManager().beginTransaction().addToBackStack(null)
                        .replace(R.id.fragment,new RegisterFragment()).commit();
            }
        });

        // 登陆
        btn_login.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String account = et_userName.getText().toString();
                String password = et_password.getText().toString();
                User user = new User();
                user.setUserName(account);
                user.setPwd(new md5Password(password).getPwd());
                DatabaseManager databaseManager = DatabaseManager.getInstance(getActivity());
                boolean b = databaseManager.checkLogin(user);
                if(b){
                    editor = preferences.edit();
                    if(cb_checkbox.isChecked()){
                        editor.putBoolean("rememberPassword",true);
                        editor.putString("account",account);
                        editor.putString("password",password);
                    }else{
                        editor.clear();
                    }
                    editor.apply();
                    Data.setA(account);
                    fragmentTransaction.addToBackStack(null).replace(R.id.fragment,new MyInfoFragment()).commit();
                }else{
                    Toast.makeText(getActivity(),"登录失败",Toast.LENGTH_SHORT).show();
                }
            }
        });
    }

    private void init() {
        EditTextClearTools.addClearListener(et_userName,iv_usernameClear);
        EditTextClearTools.addClearListener(et_password,iv_pwdClear);
    }

}


