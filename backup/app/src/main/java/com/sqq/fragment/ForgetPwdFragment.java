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

public class ForgetPwdFragment extends Fragment {
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        View view = inflater.inflate(R.layout.forgetpwd_fragment, container,false);

        return view;
    }

    private Button btnSendCode;
    private Button btnSure;

    private EditText editUsername;
    private EditText editCode;
    private EditText editPwd;
    private EditText editConfirmPwd;

    private String code;
    private TimeCount time;
    private User user;

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);

        btnSendCode = getActivity().findViewById(R.id.register_btn_send);
        btnSure = getActivity().findViewById(R.id.btn_sure);
        editUsername = getActivity().findViewById(R.id.edit_email);
        editPwd = getActivity().findViewById(R.id.edit_pwd_new);
        editConfirmPwd = getActivity().findViewById(R.id.edit_pwd_check);
        editCode = getActivity().findViewById(R.id.identifying_code);

        time = new TimeCount(60000,
                1000,btnSendCode);
        btnSendCode.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                user = new User();
                user.setUserName(editUsername.getText().toString());

                DatabaseManager databaseManager = DatabaseManager.getInstance(getActivity());

                //如果存在用户名则返回false
                boolean b = databaseManager.selectUserName(user.getUserName());

                if(!b){
                    user = databaseManager.selectEmail(user.getUserName());
                    databaseManager.close();
                    code = new CreateCode().getCode();
                    new SendMailUtil(user.getEmail(),code);
                    time.start();
                }else{
                    databaseManager.close();
                    Toast.makeText(getActivity(),"用户名不存在",Toast.LENGTH_SHORT).show();
                }

            }
        });

        btnSure.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String pwd = editPwd.getText().toString();
                String confirmPwd = editConfirmPwd.getText().toString();
                System.out.println(pwd+"==============="+confirmPwd);
                String inputCode = editCode.getText().toString();
                if(inputCode.equals(code)){
                    if(pwd.equals(confirmPwd)){
                        user.setUserName(editUsername.getText().toString());
                        user.setPwd(new md5Password(pwd).getPwd());
                        System.out.println(user.getPwd()+"+11111");
                        DatabaseManager databaseManager = DatabaseManager.getInstance(getActivity());
                        databaseManager.updatePwd(user);
                        databaseManager.close();
                        System.out.println(user.getPwd()+"33333333333333333333");
                        Toast.makeText(getActivity(),"修改成功",Toast.LENGTH_SHORT).show();
                        getFragmentManager().beginTransaction().addToBackStack(null).replace(R.id.fragment,new Mine()).commit();

                    }else{
                        Toast.makeText(getActivity(),"两次输入密码不一致",Toast.LENGTH_SHORT).show();
                    }

                } else{
                    Toast.makeText(getActivity(),"验证码错误",Toast.LENGTH_SHORT).show();
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
