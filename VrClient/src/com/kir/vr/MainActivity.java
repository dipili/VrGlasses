package com.kir.vr;

import android.app.Activity;
import android.os.Bundle;
import org.json.JSONException;

import java.io.IOException;

public class MainActivity extends Activity
{

    private ConnectionManager connectionManager;

    /**
     * Called when the activity is first created.
     */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        connectionManager = new ConnectionManager();
        try
        {
            connectionManager.start();
        }
        catch (JSONException e)
        {
            e.printStackTrace();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
    }
}
