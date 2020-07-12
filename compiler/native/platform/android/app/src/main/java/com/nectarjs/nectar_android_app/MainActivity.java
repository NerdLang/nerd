package com.nectarjs.nectar_android_app;

import androidx.appcompat.app.AppCompatActivity;

import android.content.SharedPreferences;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.util.Log;
import android.webkit.JavascriptInterface;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class MainActivity extends AppCompatActivity
{
    private WebView mainWebView;

    // Used to load the 'native-lib' library on application startup.

    static
    {
        System.loadLibrary("native-lib");
    }

    private boolean isFirstLaunch() {
        // Restore preferences
        SharedPreferences settings = getSharedPreferences("NECTAR_APP_PREF", 0);
        boolean isFirstLaunch = settings.getBoolean("isFirstLaunch", true);
        return isFirstLaunch;
    }

    class NectarInterface {

        @JavascriptInterface
        public void fireEvent(final String event) {
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    callbackFromJNI(event);
                }
            });
        }
    }

    private void copyAssets() {
        AssetManager assetManager = getAssets();
        String[] files = null;
        try {
            files = assetManager.list("raw");
        } catch (IOException e) {
            Log.e("tag", "Failed to get asset file list.", e);
        }
        try
        {

        }catch (Exception e){}

        final File newFile = new File(getFilesDir() + "/raw");
        newFile.mkdir();

        if (files != null) for (String filename : files) {
            InputStream in = null;
            OutputStream out = null;
            try {
                in = assetManager.open("raw/" + filename);
                File outFile = new File(getFilesDir() + "/raw/", filename);
                Log.d("file:", getFilesDir() + "/raw/" + filename);
                out = new FileOutputStream(outFile);
                copyFile(in, out);
            } catch(IOException e) {
                Log.e("tag", "Failed to copy asset file: " + filename, e);
            }
            finally {
                if (in != null) {
                    try {
                        in.close();
                    } catch (IOException e) {
                        // NOOP
                    }
                }
                if (out != null) {
                    try {
                        out.close();
                    } catch (IOException e) {
                        // NOOP
                    }
                }
            }
        }
    }
    private void copyFile(InputStream in, OutputStream out) throws IOException {
        byte[] buffer = new byte[1024];
        int read;
        while((read = in.read(buffer)) != -1){
            out.write(buffer, 0, read);
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mainWebView = findViewById(R.id.WebView);
        mainWebView.setWebViewClient(new WebViewClient());
        WebSettings webSettings = mainWebView.getSettings();
        webSettings.setJavaScriptEnabled(true);
		webSettings.setDomStorageEnabled(true);
		webSettings.setDatabaseEnabled(true);
        mainWebView.addJavascriptInterface(new NectarInterface(), "Nectar");

        if (isFirstLaunch()) {
            copyAssets();
            SharedPreferences settings = getSharedPreferences("NECTAR_APP_PREF", 0);
            SharedPreferences.Editor editor = settings.edit();
            editor.putBoolean("isFirstLaunch", false);
            editor.commit();
        }

        Thread thread = new Thread(new Runnable(){
            @Override
            public void run(){
                serveFromJNI();
            }
        });
        thread.start();

        callFromJNI();
    }

    public void drawNectar(final String _str)
    {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                mainWebView.loadDataWithBaseURL("", _str, "text/html", "UTF-8", "");
            }
        });
    }

    public void navigateNectar(final String _str)
    {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Log.d("navigate", _str);
                mainWebView.loadUrl(_str);
            }
        });
    }

    public native void callFromJNI();
    public native void serveFromJNI();
    public native void callbackFromJNI(String _str);
}
