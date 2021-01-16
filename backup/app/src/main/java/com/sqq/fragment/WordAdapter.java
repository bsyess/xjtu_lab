package com.sqq.fragment;

import android.content.Context;
import android.widget.ArrayAdapter;

import com.sqq.entity.Word;

import java.util.List;

public class WordAdapter extends ArrayAdapter {
    private final int resourceId;

    public WordAdapter(Context context, int textViewResourceId, List<Word> objects) {
        super(context,  textViewResourceId, objects);
        resourceId = textViewResourceId;
    }

}
