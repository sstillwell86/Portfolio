package taylormeans.finalproject;

import androidx.appcompat.app.AppCompatActivity;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {
    private Context context = this;
    public static String zipcode = "";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button createButton = (Button)findViewById(R.id.createButton);
        createButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                //prompts user for zipcode which is needed to fetch weather data
                final AlertDialog.Builder inputAlert = new AlertDialog.Builder(context);
                inputAlert.setTitle("Zip Code:");
                inputAlert.setMessage("Enter Zip Code");
                final EditText userInput = new EditText(context);
                inputAlert.setView(userInput);
                inputAlert.setPositiveButton("Submit", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        zipcode = userInput.getText().toString();
                        Intent activityIntent = new Intent(getApplicationContext(), CreateReportClass.class);

                        //creates background process that retrieves weather data and sets CreateReports textView to weather data
                        FetchWeatherData fetch = new FetchWeatherData();
                        fetch.execute();

                        startActivity(activityIntent);
                    }
                });
                inputAlert.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.dismiss();
                    }
                });
                AlertDialog alertDialog = inputAlert.create();
                alertDialog.show();
            }
        });

        Button viewButton = (Button)findViewById(R.id.viewButton);
        viewButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Intent activity2Intent = new Intent(getApplicationContext(), ListViewActivity.class);
                startActivity(activity2Intent);
            }
        });

        Button jokeButton = (Button)findViewById(R.id.jokeButton);
        jokeButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Intent activity3Intent = new Intent(getApplicationContext(), JokeClass.class);
                FetchJoke fetchJoke = new FetchJoke();
                fetchJoke.execute();
                startActivity(activity3Intent);
            }
        });
    }
}
