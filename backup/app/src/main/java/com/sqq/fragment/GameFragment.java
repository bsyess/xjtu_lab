package com.sqq.fragment;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v7.app.AlertDialog;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.sqq.main.R;

import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.RadioButton;
import android.widget.RadioGroup;

import android.support.annotation.Nullable;

public class GameFragment extends Fragment {

    private RadioGroup radioGroup1;
    private RadioGroup radioGroup2;
    private RadioButton g1_radio1;
    private RadioButton g1_radio2;
    private RadioButton g1_radio3;
    private RadioButton g2_radio1;
    private RadioButton g2_radio2;
    private RadioButton g2_radio3;
    private Button buttonOk;
    private EditText editText1;
    private EditText editText2;

    private String str_result1 = "石头";
    private String str_result2 = "石头";

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.caiquan_game, container,false);
        return view;
    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);

        FindView();

        radioGroup1.setOnCheckedChangeListener(new _RadioGroupListener1());
        radioGroup2.setOnCheckedChangeListener(new _RadioGroupListener2());
        buttonOk.setOnClickListener(new _ButtonClickListener());
    }

    private void FindView(){
        radioGroup1 = getActivity().findViewById(R.id.L6_radioGroup1);
        radioGroup2 = getActivity().findViewById(R.id.L6_radioGroup2);
        g1_radio1 = getActivity().findViewById(R.id.L6_g1_radiobt1);
        g1_radio2 = getActivity().findViewById(R.id.L6_g1_radiobt2);
        g1_radio3 = getActivity().findViewById(R.id.L6_g1_radiobt3);
        g2_radio1 = getActivity().findViewById(R.id.L6_g2_radiobt1);
        g2_radio2 = getActivity().findViewById(R.id.L6_g2_radiobt2);
        g2_radio3 = getActivity().findViewById(R.id.L6_g2_radiobt3);
        buttonOk = getActivity().findViewById(R.id.L6_buttonOK);
        editText1 = getActivity().findViewById(R.id.L6_edit1);
        editText2 = getActivity().findViewById(R.id.L6_edit2);

        //默认选择一个，不然在没有选择的情况下会闪退
        g1_radio1.setChecked(true);
        g2_radio1.setChecked(true);
    }

    class _RadioGroupListener1 implements RadioGroup.OnCheckedChangeListener{
        @Override
        public void onCheckedChanged(RadioGroup group, int checkedId) {
            if(g1_radio1.isChecked())
                str_result1 = "石头";
            else if(g1_radio2.isChecked())
                str_result1 = "剪刀";
            else if(g1_radio3.isChecked())
                str_result1 = "布";
        }
    }

    class _RadioGroupListener2 implements RadioGroup.OnCheckedChangeListener{
        @Override
        public void onCheckedChanged(RadioGroup group, int checkedId) {
            if(g2_radio1.isChecked())
                str_result2 = "石头";
            else if(g2_radio2.isChecked())
                str_result2 = "剪刀";
            else if(g2_radio3.isChecked())
                str_result2 = "布";
        }
    }

    class _ButtonClickListener implements View.OnClickListener {
        @Override
        public void onClick(View v) {
            String result = null;
            if (str_result1 == "石头") {
                if (str_result2 == "石头")
                    result = "平手！";
                else if (str_result2 == "剪刀")
                    result = "A赢了！";
                else if (str_result2 == "布")
                    result = "B赢了！";
            } else if (str_result1 == "剪刀") {
                if (str_result2 == "石头")
                    result = "B赢了！";
                else if (str_result2 == "剪刀")
                    result = "平手！";
                else if (str_result2 == "布")
                    result = "A赢了！";

            } else if (str_result1 == "布") {
                if (str_result2 == "石头")
                    result = "A赢了！";
                else if (str_result2 == "剪刀")
                    result = "B赢了！";
                else if (str_result2 == "布")
                    result = "平手！";
            }

            String UserA = editText1.getText().toString();
            String UserB = editText2.getText().toString();
            String winner = "";
            System.out.println("UserName = " + UserA + ",UserNameB = " + UserB + ",winner = " + winner);

            if (UserA.length() == 0 || UserB.length() == 0) {
                System.out.println("还没有输入姓名");
                Toast.makeText(getActivity(), "请输入姓名", Toast.LENGTH_LONG).show();
            }
            else {
                if (result.contains("A"))
                    winner = UserA + " 赢了";
                else if (result.contains("B"))
                    winner = UserB + "赢了";
                else
                    winner = "平手！";
                Toast.makeText(getActivity(), winner, Toast.LENGTH_LONG).show();
                AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
                builder.setTitle("winner");
                builder.setMessage(winner);
                builder.show();
            }
        }
    }
}
