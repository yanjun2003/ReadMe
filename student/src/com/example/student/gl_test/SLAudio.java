package com.example.student.gl_test;

import com.example.student.*;

import android.app.Activity;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.Spinner;
import android.widget.Toast;
import android.widget.SeekBar.OnSeekBarChangeListener;

public class SLAudio extends Activity {

    //static final String TAG = "NativeAudio";

    static final int CLIP_NONE = 0;
    static final int CLIP_HELLO = 1;
    static final int CLIP_ANDROID = 2;
    static final int CLIP_SAWTOOTH = 3;
    static final int CLIP_PLAYBACK = 4;

    static String URI;
    static AssetManager assetManager;

    static boolean isPlayingAsset = false;
    static boolean isPlayingUri = false;

    static int numChannelsUri = 0;

    /** Called when the activity is first created. */
    @Override
    protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        setContentView(R.layout.activity_slaudio);

        assetManager = getAssets();

        // initialize native audio system

        SL_createEngine();
        SL_createBufferQueueAudioPlayer();

        // initialize URI spinner
        Spinner uriSpinner = (Spinner) findViewById(R.id.uri_spinner);
        ArrayAdapter<CharSequence> uriAdapter = ArrayAdapter.createFromResource(
                this, R.array.uri_spinner_array, android.R.layout.simple_spinner_item);
        uriAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        uriSpinner.setAdapter(uriAdapter);
        uriSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {

            public void onItemSelected(AdapterView<?> parent, View view, int pos, long id) {
                URI = parent.getItemAtPosition(pos).toString();
            }

            @SuppressWarnings("rawtypes")
			public void onNothingSelected(AdapterView parent) {
                URI = null;
            }

        });

        // initialize button click handlers

        ((Button) findViewById(R.id.hello)).setOnClickListener(new OnClickListener() {
            public void onClick(View view) {
                // ignore the return value
                SL_selectClip(CLIP_HELLO, 5);
            }
        });

        ((Button) findViewById(R.id.android)).setOnClickListener(new OnClickListener() {
            public void onClick(View view) {
                // ignore the return value
                SL_selectClip(CLIP_ANDROID, 7);
            }
        });

        ((Button) findViewById(R.id.sawtooth)).setOnClickListener(new OnClickListener() {
            public void onClick(View view) {
                // ignore the return value
                SL_selectClip(CLIP_SAWTOOTH, 1);
            }
        });

        ((Button) findViewById(R.id.reverb)).setOnClickListener(new OnClickListener() {
            boolean enabled = false;
            public void onClick(View view) {
                enabled = !enabled;
                if (!SL_enableReverb(enabled)) {
                    enabled = !enabled;
                }
            }
        });

        ((Button) findViewById(R.id.embedded_soundtrack)).setOnClickListener(new OnClickListener() {
            boolean created = false;
            public void onClick(View view) {
                if (!created) {
                    created = SL_createAssetAudioPlayer(assetManager, "background.mp3");
                }
                if (created) {
                    isPlayingAsset = !isPlayingAsset;
                    SL_setPlayingAssetAudioPlayer(isPlayingAsset);
                }
            }
        });

        ((Button) findViewById(R.id.uri_soundtrack)).setOnClickListener(new OnClickListener() {
            boolean created = false;
            public void onClick(View view) {
                if (!created && URI != null) {
                    created = SL_createUriAudioPlayer(URI);
                }
             }
        });

        ((Button) findViewById(R.id.pause_uri)).setOnClickListener(new OnClickListener() {
            public void onClick(View view) {
                SL_setPlayingUriAudioPlayer(false);
             }
        });

        ((Button) findViewById(R.id.play_uri)).setOnClickListener(new OnClickListener() {
            public void onClick(View view) {
                SL_setPlayingUriAudioPlayer(true);
             }
        });

        ((Button) findViewById(R.id.loop_uri)).setOnClickListener(new OnClickListener() {
            boolean isLooping = false;
            public void onClick(View view) {
                isLooping = !isLooping;
                SL_setLoopingUriAudioPlayer(isLooping);
             }
        });

        ((Button) findViewById(R.id.mute_left_uri)).setOnClickListener(new OnClickListener() {
            boolean muted = false;
            public void onClick(View view) {
                muted = !muted;
                SL_setChannelMuteUriAudioPlayer(0, muted);
             }
        });

        ((Button) findViewById(R.id.mute_right_uri)).setOnClickListener(new OnClickListener() {
            boolean muted = false;
            public void onClick(View view) {
                muted = !muted;
                SL_setChannelMuteUriAudioPlayer(1, muted);
             }
        });

        ((Button) findViewById(R.id.solo_left_uri)).setOnClickListener(new OnClickListener() {
            boolean soloed = false;
            public void onClick(View view) {
                soloed = !soloed;
                SL_setChannelSoloUriAudioPlayer(0, soloed);
             }
        });

        ((Button) findViewById(R.id.solo_right_uri)).setOnClickListener(new OnClickListener() {
            boolean soloed = false;
            public void onClick(View view) {
                soloed = !soloed;
                SL_setChannelSoloUriAudioPlayer(1, soloed);
             }
        });

        ((Button) findViewById(R.id.mute_uri)).setOnClickListener(new OnClickListener() {
            boolean muted = false;
            public void onClick(View view) {
                muted = !muted;
                SL_setMuteUriAudioPlayer(muted);
             }
        });

        ((Button) findViewById(R.id.enable_stereo_position_uri)).setOnClickListener(
                new OnClickListener() {
            boolean enabled = false;
            public void onClick(View view) {
                enabled = !enabled;
                SL_enableStereoPositionUriAudioPlayer(enabled);
             }
        });

        ((Button) findViewById(R.id.channels_uri)).setOnClickListener(new OnClickListener() {
            public void onClick(View view) {
                if (numChannelsUri == 0) {
                    numChannelsUri = SL_getNumChannelsUriAudioPlayer();
                }
                Toast.makeText(SLAudio.this, "Channels: " + numChannelsUri,
                        Toast.LENGTH_SHORT).show();
             }
        });

        ((SeekBar) findViewById(R.id.volume_uri)).setOnSeekBarChangeListener(
                new OnSeekBarChangeListener() {
            int lastProgress = 100;
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                assert progress >= 0 && progress <= 100;
                lastProgress = progress;
            }
            public void onStartTrackingTouch(SeekBar seekBar) {
            }
            public void onStopTrackingTouch(SeekBar seekBar) {
                int attenuation = 100 - lastProgress;
                int millibel = attenuation * -50;
                SL_setVolumeUriAudioPlayer(millibel);
            }
        });

        ((SeekBar) findViewById(R.id.pan_uri)).setOnSeekBarChangeListener(
                new OnSeekBarChangeListener() {
            int lastProgress = 100;
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                assert progress >= 0 && progress <= 100;
                lastProgress = progress;
            }
            public void onStartTrackingTouch(SeekBar seekBar) {
            }
            public void onStopTrackingTouch(SeekBar seekBar) {
                int permille = (lastProgress - 50) * 20;
                SL_setStereoPositionUriAudioPlayer(permille);
            }
        });

        ((Button) findViewById(R.id.record)).setOnClickListener(new OnClickListener() {
            boolean created = false;
            public void onClick(View view) {
                if (!created) {
                    created = SL_createAudioRecorder();
                }
                if (created) {
                    SL_startRecording();
                }
            }
        });

        ((Button) findViewById(R.id.playback)).setOnClickListener(new OnClickListener() {
            public void onClick(View view) {
                // ignore the return value
                SL_selectClip(CLIP_PLAYBACK, 3);
            }
        });

    }

    /** Called when the activity is about to be destroyed. */
    @Override
    protected void onPause()
    {
        // turn off all audio
        SL_selectClip(CLIP_NONE, 0);
        isPlayingAsset = false;
        SL_setPlayingAssetAudioPlayer(false);
        isPlayingUri = false;
        SL_setPlayingUriAudioPlayer(false);
        super.onPause();
    }

    /** Called when the activity is about to be destroyed. */
    @Override
    protected void onDestroy()
    {
        SL_shutdown();
        super.onDestroy();
    }

    /** Native methods, implemented in jni folder */
    public static native void SL_createEngine();
    public static native void SL_createBufferQueueAudioPlayer();
    public static native boolean SL_createAssetAudioPlayer(AssetManager assetManager, String filename);
    // true == PLAYING, false == PAUSED
    public static native void SL_setPlayingAssetAudioPlayer(boolean isPlaying);
    public static native boolean SL_createUriAudioPlayer(String uri);
    public static native void SL_setPlayingUriAudioPlayer(boolean isPlaying);
    public static native void SL_setLoopingUriAudioPlayer(boolean isLooping);
    public static native void SL_setChannelMuteUriAudioPlayer(int chan, boolean mute);
    public static native void SL_setChannelSoloUriAudioPlayer(int chan, boolean solo);
    public static native int SL_getNumChannelsUriAudioPlayer();
    public static native void SL_setVolumeUriAudioPlayer(int millibel);
    public static native void SL_setMuteUriAudioPlayer(boolean mute);
    public static native void SL_enableStereoPositionUriAudioPlayer(boolean enable);
    public static native void SL_setStereoPositionUriAudioPlayer(int permille);
    public static native boolean SL_selectClip(int which, int count);
    public static native boolean SL_enableReverb(boolean enabled);
    public static native boolean SL_createAudioRecorder();
    public static native void SL_startRecording();
    public static native void SL_shutdown();


}
