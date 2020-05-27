package com.nectarjs.nectarinterrop;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.webkit.JavascriptInterface;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;

public class MainActivity extends AppCompatActivity
{
    private WebView mainWebView;

    // Used to load the 'native-lib' library on application startup.

    static
    {
        System.loadLibrary("native-lib");
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


    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mainWebView = findViewById(R.id.WebView);
        mainWebView.setWebViewClient(new WebViewClient());
        WebSettings webSettings = mainWebView.getSettings();
        webSettings.setJavaScriptEnabled(true);
        mainWebView.addJavascriptInterface(new NectarInterface(), "Nectar");

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

    public native void callFromJNI();
    public native void callbackFromJNI(String _str);
}
