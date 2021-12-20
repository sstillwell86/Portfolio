package taylormeans.finalproject;

import android.os.AsyncTask;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

//creates background process which gets weather data from API and populates CreateReportClass textView with weather data
public class FetchWeatherData extends AsyncTask<Void, Void, Void> {
    String weatherData = "";
    String city = "";
    String weatherDescription = "";
    String temperature = "";
    @Override
    protected Void doInBackground(Void... voids) {
        try {
            //creates URL, establishes connection with server, and creates a data stream
            URL weatherAPI = new URL( "http://api.openweathermap.org/data/2.5/weather?zip=" + MainActivity.zipcode + "&units=imperial&APPID=2c43a0a3259a296ef262030ef764bde1");
            HttpURLConnection weatherAPIConnection = (HttpURLConnection) weatherAPI.openConnection();
            InputStream weatherInputStream = weatherAPIConnection.getInputStream();
            BufferedReader weatherBufferedReader = new BufferedReader(new InputStreamReader(weatherInputStream));

            //reads data from buffer
            String line = "";
            while(line != null) {
                line = weatherBufferedReader.readLine();
                weatherData = weatherData + line;
            }

            //creates JSON object with weather data, parses select data into a string, and populates CreateReportClass textView with string
            JSONObject weatherDataJSON = new JSONObject(weatherData);
            JSONArray weatherJSONArray = weatherDataJSON.getJSONArray("weather");
            JSONObject weatherJSON = weatherJSONArray.getJSONObject(0);
            JSONObject temperatureJSON = weatherDataJSON.getJSONObject("main");
            temperature = temperatureJSON.getString("temp");
            weatherDescription = weatherJSON.getString("description");

            city = weatherDataJSON.getString("name");
        } catch (MalformedURLException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (JSONException e) {
            e.printStackTrace();
        }

        return null;
    }

    @Override
    protected void onPostExecute(Void aVoid) {
        super.onPostExecute(aVoid);
        if (weatherData == null || weatherData == "") {
            CreateReportClass.weather.setText("Error Retrieving Weather Data");
        }
        else {
            CreateReportClass.weather.setText(city + " " + weatherDescription + " " + temperature + "\u00B0");
        }
    }
}
