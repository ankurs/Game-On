package com.ankurs.gameon;

import java.io.*;
import java.net.InetAddress;
import java.net.Socket;

/**
 * @author ankur shrivastava
 *
 */
public class Worker extends Thread {

	private PrintWriter pw;
	private gameon obj;
	private Socket sock;
	public String ip;
	public int port;
	public int value1;
	public int value2;
	public boolean running;
	
	public Worker(gameon g, String ip, int port)
	{
		obj = g;
		this.ip = ip;
		this.port = port;
		this.value1 = 3;
		this.value2 = 6;
		this.running = true;
	}
	
	public void run()
	{
		try{
			pw = null;
			sock = new Socket(InetAddress.getByName(ip), port);
			sock.setTcpNoDelay(true);
			pw = new PrintWriter(new OutputStreamWriter(sock.getOutputStream()));
			pw.flush();
		}
		catch(Exception e)
		{
			if (obj.debugtext != null)
			{
				obj.debugtext.setText(e.toString());
			}
		}

		while (running)
		{
			try{
				Thread.sleep(300);
				if (value1 != 0)
				{
					if (pw == null)
						break;
					pw.write((byte)value1);
					pw.flush();
					value1 = 0;
				}
				if (value2 != 0)
				{
					if (pw == null)
						break;
					pw.write((byte)value2);
					pw.flush();
					value2 = 0;
				}				
			}
			catch(Exception e)
			{
				obj.debugtext.setText(e.toString());
			}
		}
	}
}
