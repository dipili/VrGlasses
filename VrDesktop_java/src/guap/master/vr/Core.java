package guap.master.vr;

import javax.media.*;
import javax.media.control.FormatControl;
import javax.media.control.TrackControl;
import javax.media.format.AudioFormat;
import javax.media.format.UnsupportedFormatException;
import javax.media.format.VideoFormat;
import javax.media.protocol.ContentDescriptor;
import javax.media.protocol.DataSource;
import javax.media.rtp.SessionManager;
import java.io.IOException;
import java.util.Vector;

/**
 * Created by kuzia on 16.03.2016 at 23:25
 */
public class Core
{
    Core()
    {
// First, we'll need a DataSource that captures live audio:

        VideoFormat format = new VideoFormat(VideoFormat.H263);

        Vector devices = CaptureDeviceManager.getDeviceList(format);

        CaptureDeviceInfo di = null;
        if (devices.size() > 0)
        {
            di = (CaptureDeviceInfo) devices.elementAt(0);
        }
        else
        {
            // exit if we could not find the relevant capture device.
            System.exit(-1);
        }
        // Create a processor for this capture device & exit if we
        // cannot create it
        Processor processor;
        try
        {
            processor = Manager.createProcessor(di.getLocator());
        }
        catch (IOException | NoProcessorException e)
        {
            System.exit(-1);
            return;
        }

        // at this point, we have succesfully created the processor.
        // Realize it and block until it is configured.

        processor.configure();

        // block until it has been configured

        processor.setContentDescriptor(new ContentDescriptor(ContentDescriptor.RAW));

        TrackControl track[] = processor.getTrackControls();

        boolean encodingOk = false;

        // Go through the tracks and try to program one of them to
        // output ULAW_RTP data.
        for (int i = 0; i < track.length; i++)
        {
            if (!encodingOk && track[i] != null)
            {

                if (((FormatControl) track[i]).
                        setFormat(new AudioFormat(AudioFormat.ULAW_RTP, 8000, 8, 1)) == null)
                {

                    track[i].setEnabled(false);
                }
                else
                {
                    encodingOk = true;
                }
            }
            else
            {
                // we could not set this track to gsm, so disable it
                track[i].setEnabled(false);
            }
        }
        // Realize it and block until it is realized.
        processor.realize();

        // block until realized.
        // get the output datasource of the processor  and exit
        // if we fail

        DataSource ds = null;

        try
        {
            ds = processor.getDataOutput();
        }
        catch (NotRealizedError e)
        {
            System.exit(-1);
        }

        // Create a SessionManager and hand over the
        // datasource for SendStream creation.

        SessionManager rtpsm = new com.sun.media.rtp.RTPSessionMgr();

        // The session manager then needs to be initialized and started:
        // rtpsm.initSession(...);
        // rtpsm.startSession(...);

        try
        {
            rtpsm.createSendStream(ds, 0);
        }
        catch (IOException | UnsupportedFormatException e)
        {
            e.printStackTrace();
        }
    }

    public void start()
    {

    }
}
