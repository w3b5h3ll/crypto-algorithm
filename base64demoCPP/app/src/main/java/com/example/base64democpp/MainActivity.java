package com.example.base64democpp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Base64;
import android.util.Log;
import android.widget.TextView;

import com.example.base64democpp.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'base64democpp' library on application startup.
    static {
        System.loadLibrary("base64democpp");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
//        tv.setText(stringFromJNI());
        tv.setText(stringFromBase64());
//        stringFromJNI();

////        Base64编码解码
//        String data = "w3b5h3ll";
//        String encodeString = Base64.encodeToString(data.getBytes(), Base64.DEFAULT);
//        byte[] decodeByte = Base64.decode(encodeString, Base64.DEFAULT);
//        String decodeString = new String(decodeByte);
//        Log.i("base64demo", "data: " + data + " >> " + encodeString);
//        Log.i("base64demo", "decodeString: " + decodeString);
    }

    /**
     * A native method that is implemented by the 'base64democpp' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native String stringFromBase64();

    public native String stringFromJNIAdd(String str1, String str2);
}