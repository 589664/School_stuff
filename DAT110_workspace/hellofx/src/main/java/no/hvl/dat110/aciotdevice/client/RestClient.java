package no.hvl.dat110.aciotdevice.client;

import java.io.IOException;

import com.google.gson.Gson;

import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

public class RestClient {

	public RestClient() {
		// TODO Auto-generated constructor stub
	}

	private static String logpath = "/accessdevice/log";
	
	public static final MediaType JSON = MediaType.parse("application/json; charset=utf-8");

	public void doPostAccessEntry(String message) {

		// TODO: implement a HTTP POST on the service to post the message
		
		OkHttpClient client = new OkHttpClient();
		
		Request req = new Request.Builder()
				  .url("http://localhost:8080" + logpath)
				  .post(RequestBody.create(JSON,new Gson().toJson(new AccessMessage(message))))
				  .build();
		
		try {
			client.newCall(req).execute();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	private static String codepath = "/accessdevice/code";
	
	public AccessCode doGetAccessCode() {
		// TODO: implement a HTTP GET on the service to get current access code
		
		OkHttpClient client = new OkHttpClient();
		
		Request req = new Request.Builder()
				  .url("http://localhost:8080" + codepath)
				  .get()
				  .build();
		
		try {
			Response resp = client.newCall(req).execute();
			
			AccessCode ny = new AccessCode();
			ny.setAccesscode(new Gson().fromJson(resp.body().string(), int[].class));
			return ny;
			
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		
		return null;
	}
}
