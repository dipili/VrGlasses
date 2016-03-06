package com.kir.vr;

import android.os.AsyncTask;
import android.os.Build;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.*;
import java.util.Timer;
import java.util.TimerTask;

/**
 * Created by kuzia on 24.02.2016.
 */
public class ConnectionManager
{
    private static final int DESKTOP_WAITER_PORT = 12345;
    private static final int PERIOD = 5 * 1000;
    private static final int LISTENING_PORT = 8664;
    private Timer timer;
    private DatagramSocket spammingSocket;

    public void start() throws IOException, JSONException
    {
        if (timer != null)
            throw new RuntimeException("Attempt to start connection manager twice.");

        AsyncTask serverTask = new AsyncTask()
        {
            @Override
            protected Object doInBackground(Object[] params)
            {
                ServerSocket listeningSocket;
                try
                {
                    listeningSocket = new ServerSocket();
                    listeningSocket.bind(new InetSocketAddress(LISTENING_PORT));
                    Socket clientSocket = listeningSocket.accept();
                    InputStream inputStream = clientSocket.getInputStream();
                    BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));

                    String inputLine;
                    StringBuffer buffer = new StringBuffer();
                    while ((inputLine = reader.readLine()) != null)
                        buffer.append(inputLine);

                    System.out.println(buffer);
                }
                catch (IOException e)
                {
                    e.printStackTrace();
                }
                return null;
            }
        };
//        serverTask.execute();

        spammingSocket = new DatagramSocket();
        spammingSocket.setBroadcast(true);

        timer = new Timer();
        timer.scheduleAtFixedRate(new BroadcastTask(), PERIOD, PERIOD);
    }

    public void stop()
    {
        timer.cancel();
        timer = null;
    }

    private class BroadcastTask extends TimerTask
    {

        private final DatagramPacket pack;

        BroadcastTask() throws JSONException
        {
            JSONObject dataObject = new JSONObject();
            dataObject.put("model", Build.MODEL);
            dataObject.put("id", Build.ID);
            dataObject.put("port", LISTENING_PORT);
//            dataObject.put("host", spammingSocket.getLocalSocketAddress().toString());

            byte[] data = dataObject.toString().getBytes();
            try
            {
                pack = new DatagramPacket(data,
                                          data.length,
                                          InetAddress.getByName("255.255.255.255"),
                                          DESKTOP_WAITER_PORT);
            }
            catch (UnknownHostException e)
            {
                throw new RuntimeException();
            }
        }

        @Override
        public void run()
        {
            try
            {
                spammingSocket.send(pack);
            }
            catch (IOException e)
            {
                e.printStackTrace(); // TODO message
            }
        }
    }
}
