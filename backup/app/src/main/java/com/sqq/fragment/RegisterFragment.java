package com.sqq.fragment;

import android.os.Bundle;
import android.os.CountDownTimer;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.sqq.MD5.md5Password;
import com.sqq.SQL.DatabaseManager;
import com.sqq.entity.User;
import com.sqq.main.R;
import com.sqq.sendMail.CreateCode;
import com.sqq.sendMail.SendMailUtil;

public class RegisterFragment extends Fragment {
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.register_fragment, container,false);
        return view;
    }

    private Button btnRegister;
    private Button btnSendCode;
    private EditText editUserName;
    private EditText editPwd;
    private EditText editConfirmPwd;
    private EditText editEmail;
    private EditText editCode;
    private TimeCount time;
    private String code;

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        btnRegister = getActivity().findViewById(R.id.register_btn_sure);
        btnSendCode = getActivity().findViewById(R.id.register_btn_send);

        editUserName = getActivity().findViewById(R.id.edit_name);
        editPwd = getActivity().findViewById(R.id.edit_pwd_old);
        editConfirmPwd = getActivity().findViewById(R.id.edit_pwd_new);
        editEmail = getActivity().findViewById(R.id.edit_email);
        editCode = getActivity().findViewById(R.id.identifying_code);

        time = new TimeCount(60000, 1000,btnSendCode);

        // 发送验证码
        btnSendCode.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String pwd = editPwd.getText().toString();
                String confirmPwd = editConfirmPwd.getText().toString();
                if(pwd.equals(confirmPwd)){
                    String email = editEmail.getText().toString();
                    if(email==null||email.length()==0) {
                        Toast.makeText(getActivity(), "邮箱不能为空", Toast.LENGTH_SHORT).show();
                    }
                    else{
                        code = new CreateCode().getCode();
                        new SendMailUtil(email, code);
                        time.start();
                    }
                }else{
                    Toast.makeText(getActivity(),"两次密码输入不一致",Toast.LENGTH_SHORT).show();
                }
            }
        });

        // 注册
        btnRegister.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String inputCode = editCode.getText().toString();
                if(inputCode.equals(code)){
                    User user= new User();
                    user.setUserName(editUserName.getText().toString());
                    user.setPwd(new md5Password(editPwd.getText().toString()).getPwd());
                    user.setEmail(editEmail.getText().toString());

                    DatabaseManager databaseManager= DatabaseManager.getInstance(getActivity());

                    //如果存在用户名则返回false
                    boolean b = databaseManager.selectUserName(user.getUserName());
                    databaseManager.close();
                    if(b){
                        databaseManager = DatabaseManager.getInstance(getActivity());
                        databaseManager.insertInfo(user);
                        Toast.makeText(getActivity(),"注册成功",Toast.LENGTH_SHORT).show();
                        getFragmentManager().beginTransaction().addToBackStack(null).replace(R.id.fragment,new Mine()).commit();
                    }else{
                        Toast.makeText(getActivity(),"已存在该用户",Toast.LENGTH_SHORT).show();
                    }
                }else{
                    Toast.makeText(getActivity(),"验证码输入错误",Toast.LENGTH_SHORT).show();
                }
            }
        });
    }

    // 自定义倒计时类
    class TimeCount extends CountDownTimer {
        private Button btn;
        public TimeCount(long millisInFuture, long countDownInterval,Button btn) {

            super(millisInFuture, countDownInterval);//参数依次为总时长,和计时的时间间隔
            this.btn = btn;
        }

        @Override
        public void onFinish() {//计时完毕时触发
            btn.setText("重新验证");
            btn.setClickable(true);
        }

        @Override
        public void onTick(long millisUntilFinished){//计时过程显示
            btn.setClickable(false);
            btn.setText(millisUntilFinished /1000+"秒");
        }
    }

}
