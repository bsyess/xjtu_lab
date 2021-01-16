package com.sqq.sendMail;

import static java.lang.String.valueOf;

public class CreateCode {

    private String code;

    private void createCode(){
        do{
            code=valueOf((int)(Math.random()*1000000));
        }while(code.length()!=6);
    }
    public CreateCode(){
        createCode();
    }

    public String getCode() {
        return code;
    }

}
