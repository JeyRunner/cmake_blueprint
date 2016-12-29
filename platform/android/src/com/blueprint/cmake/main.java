package com.blueprint.cmake;

import android.app.Activity;
import android.util.Log;
import android.os.Bundle;

public class main extends Activity
{
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        Log.i("GO", "start app");

        // load libs
        System.loadLibrary("bluePrintCmake");

        setContentView(R.layout.main);
    }
}
