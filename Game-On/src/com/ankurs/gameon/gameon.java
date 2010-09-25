package com.ankurs.gameon;

import java.util.List;

import android.app.Activity;
import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class gameon extends Activity implements OnClickListener{
	
	Worker w;
	public TextView infotext, debugtext;
	private SensorManager sm;
	private SensorEventListener mySensorEventListener = new SensorEventListener() {
		
		@Override
		public void onSensorChanged(SensorEvent event) {
			
			infotext.setText("");
			debugtext.setText("");
			if (((int)event.values[1]) > 5)
            {
				if (w != null)
				{
            		w.value1 = 1;
            		debugtext.append("Sensor Send 1\n");
				}
            }
            else if (((int)event.values[1]) < -5 )
            {
            	if (w != null)
				{
            		w.value1 = 2;
            		debugtext.append("Sensor Send 2\n");
				}
            }
            else
            {   
            	if (w != null)
				{
            		w.value1 = 3;
            		debugtext.append("Sensor Send 3\n");
				}
            }			
			
            if (((int)event.values[2]) > 65)
            {       
            	if (w != null)
				{
            		w.value2 = 4;
            		debugtext.append("Sensor Send 4\n");
				}
            }
            else if (((int)event.values[2]) < 35 )
            {
            	if (w != null)
				{
            		w.value2 = 5;
            		debugtext.append("Sensor Send 5\n");
				}
            }
            else
            {
            	if (w != null)
				{
            		w.value2 = 6;
            		debugtext.append("Sensor Send 6\n");
				}
            }            
            infotext.append("\nValue 1 ->"+event.values[1]);
            infotext.append("\nValue 2 ->"+event.values[2]);
            //pw.flush();                       
		}

		@Override
		public void onAccuracyChanged(Sensor arg0, int arg1) {
			// nothing to be done here
			
		}
	};
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        Button b = (Button)findViewById(R.id.ConnectButton);
        b.setOnClickListener(this);
        
        infotext = (TextView) findViewById(R.id.infotext);
        debugtext = (TextView) findViewById(R.id.debuginfo);
        infotext.setText("Whats up?");
		sm = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        List<Sensor> mySensors = sm.getSensorList(Sensor.TYPE_ORIENTATION);
        sm.registerListener(mySensorEventListener, mySensors.get(0), SensorManager.SENSOR_DELAY_GAME);
        w = null;
    }

	@Override
	public void onClick(View v) {
		if (v == findViewById(R.id.ConnectButton))
		{
			if (w == null)
	        {
				String ip = ((EditText)findViewById(R.id.IP)).getText().toString();
				String port = ((EditText)findViewById(R.id.Port)).getText().toString();
				try{
					w = new Worker(this, ip, Integer.parseInt(port));
					w.start();
				}
				catch(Exception e)
				{
					debugtext.setText(e.toString());
				}
	        }
		}
		else if (v == findViewById(R.id.ResetButton))
		{
			if (w != null)
			{
				w.running = false;
				w = null;
			}
		}				
	}
}