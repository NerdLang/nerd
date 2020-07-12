package com.nectarjs.nectar_android_app;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.util.Log;
import android.webkit.JavascriptInterface;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;

public class MainActivity extends AppCompatActivity
{
    private WebView mainWebView;

    // Used to load the 'native-lib' library on application startup.

    static
    {
        System.loadLibrary("native-lib");
    }

    private String checkVersion() {
        // Restore preferences
        SharedPreferences settings = getSharedPreferences("NECTAR_APP_PREF", 0);
        String version = settings.getString("version", "");
        return version;
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

    private void copyAssets(String base) {
        Log.d("Copying:", base);
        AssetManager assetManager = getAssets();
        String[] files = null;
        try {
            files = assetManager.list(base);
        } catch (IOException e) {
            Log.e("tag", "Failed to get asset file list.", e);
        }
        try
        {

        }catch (Exception e){}

        final File newFile = new File(getFilesDir() + "/" + base);
        newFile.mkdir();

        if (files != null) for (String filename : files)
        {
            File isDir = new File(base + "/" + filename);
            if (!isDir.exists()) {
                copyAssets(base + "/" + filename);
            }
            else {
                InputStream in = null;
                OutputStream out = null;
                try {
                    in = assetManager.open(base + "/" + filename);
                    File outFile = new File(getFilesDir() + "/" + base + "/", filename);
                    Log.d("file:", getFilesDir() + "/" + base + "/" + filename);
                    out = new FileOutputStream(outFile);
                    copyFile(in, out);
                } catch(Exception e) {
                    Log.e("tag", "Failed to copy asset file: " + filename, e);
                } finally {
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
    }
    private synchronized void copyFile(InputStream in, OutputStream out) throws IOException {
        byte[] buffer = new byte[1024];
        int read;
        while((read = in.read(buffer)) != -1){
            out.write(buffer, 0, read);
        }
    }

    public static String loadAssetFile(Context context, String fileName) {
        try {
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(context.getAssets().open(fileName)));
            StringBuilder out= new StringBuilder();
            String eachline = bufferedReader.readLine();
            while (eachline != null) {
                out.append(eachline);
                eachline = bufferedReader.readLine();
            }
            return out.toString();
        } catch (IOException e) {
            Log.e("Load Asset File",e.toString());
        }
        return null;
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
        mainWebView.addJavascriptInterface(new NectarInterface(), "Nectar");

        String _version = loadAssetFile(this, "raw/version.txt");
        Log.d("Version", checkVersion() + " : " + _version);
        if (!checkVersion().equals(_version)) {
            copyAssets("raw");
            SharedPreferences settings = getSharedPreferences("NECTAR_APP_PREF", 0);
            SharedPreferences.Editor editor = settings.edit();
            editor.putString("version", _version);
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
