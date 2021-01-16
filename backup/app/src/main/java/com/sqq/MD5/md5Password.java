package com.sqq.MD5;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class md5Password {

    public static void main(String[] args) {
        System.out.println(new md5Password("123456").getPwd());
    }

    public String getPwd() {
        return pwd;
    }

    private String pwd;

    public md5Password(String pwd){
        this.pwd = pwd;
        md5();
    }

    private void md5() {
        try {
            //得到信息摘要
            MessageDigest digest = MessageDigest.getInstance("md5");

            byte[] result = digest.digest(pwd.getBytes());
            StringBuffer buffer = new StringBuffer();

            //把每一个byte做一个与运算 0xff
            for(byte b:result){
                int number = b&0xff;//加盐
                String str = Integer.toHexString(number);
                if(str.length()==1){
                    buffer.append("0");
                }
                buffer.append(str);
            }
            pwd = buffer.toString();
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
            pwd = "";
        }
    }
}
