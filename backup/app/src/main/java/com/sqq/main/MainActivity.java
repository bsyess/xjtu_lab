package com.sqq.main;

import android.app.Activity;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.RadioButton;
import android.widget.RadioGroup;

import com.sqq.entity.Data;
import com.sqq.fragment.Mine;
import com.sqq.fragment.MyInfoFragment;
import com.sqq.fragment.TranslateFragment;
import com.sqq.fragment.GameFragment;
import com.sqq.sendMail.SendMailUtil;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private RadioButton translateRadioButton;
    private RadioButton mineRadioButton;
    private RadioButton Game_Button;
    private RadioGroup bottomRadioGroup;

    private Fragment translateFragment;
    private Fragment mineFragment;
    private Fragment gameFragment;
    private FragmentManager fragmentManager;
    private FragmentTransaction fragmentTransaction;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // 拿到事务管理器并开始事务
        fragmentManager = getSupportFragmentManager();
        fragmentTransaction = fragmentManager.beginTransaction();

        // 初始化按钮
        mineRadioButton = findViewById(R.id.mine_bottom);
        translateRadioButton = findViewById(R.id.translate_bottom);
        Game_Button = findViewById(R.id.Game_Button);
        bottomRadioGroup = findViewById(R.id.bottom_rg);

        // 为按钮添加事件监听
        translateRadioButton.setOnClickListener(this);
        mineRadioButton.setOnClickListener(this);
        Game_Button.setOnClickListener(this);

        // 启动，默认选择第一个
        bottomRadioGroup.check(R.id.mine_bottom);
        translateFragment = new TranslateFragment();
        fragmentTransaction.replace(R.id.fragment,translateFragment);
        fragmentTransaction.commit();
    }

    @Override
    public void onClick(View v) {
        fragmentManager = getSupportFragmentManager();
        fragmentTransaction = fragmentManager.beginTransaction();

        switch(v.getId()){
            case R.id.translate_bottom:
                // 为了防止重叠，需要在显示之前移除其他的fragment
                System.out.println("翻译fragment");
                hideFragment(fragmentTransaction);
                translateFragment = new TranslateFragment();
                fragmentTransaction.replace(R.id.fragment,translateFragment);
                fragmentTransaction.commit();
                break;

            case R.id.mine_bottom:
                System.out.println("我的fragment");
                hideFragment(fragmentTransaction);
                if(Data.getA().equals("")){
                    mineFragment = new Mine();
                }else{
                    mineFragment = new MyInfoFragment();
                }
                fragmentTransaction.replace(R.id.fragment,mineFragment);
                fragmentTransaction.commit();
                break;

            case R.id.Game_Button:
                System.out.println("游戏fragment");
                hideFragment(fragmentTransaction);
                gameFragment = new GameFragment();
                fragmentTransaction.replace(R.id.fragment,gameFragment);
                fragmentTransaction.commit();
                break;

            default :
                break;
        }
    }

    // 去除所有的Fragment
    private void hideFragment(FragmentTransaction transaction) {
        if(mineFragment!=null){
            System.out.println("清除");
            transaction.remove(mineFragment);
        }
        if(translateFragment!=null){
            System.out.println("去除");
            transaction.remove(translateFragment);
        }
        if(gameFragment!=null){
            System.out.println("移除");
            transaction.remove(gameFragment);
        }
    }

}
