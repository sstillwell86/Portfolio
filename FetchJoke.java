package taylormeans.finalproject;

import android.os.AsyncTask;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URL;

import javax.net.ssl.HttpsURLConnection;

public class FetchJoke extends AsyncTask<Void, Void, Void> {
    String joke = "";

    @Override
    protected Void doInBackground(Void... voids) {
        try {
            URL jokeAPI = new URL("https://icanhazdadjoke.com/");
            HttpsURLConnection jokeAPIConnection = (HttpsURLConnection)jokeAPI.openConnection();
            jokeAPIConnection.addRequestProperty("Accept", "application/json");
            InputStream jokeInputStream = jokeAPIConnection.getInputStream();
            BufferedReader jokeBufferedReader = new BufferedReader(new InputStreamReader(jokeInputStream));

            //reads data from buffer
            String line = "";
            while(line != null) {
                line = jokeBufferedReader.readLine();
                joke = joke + line;
            }
            JSONObject jokeJSON = new JSONObject(joke);
            joke = jokeJSON.getString("joke");
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
        JokeClass.joke.setText(joke);
    }
}
