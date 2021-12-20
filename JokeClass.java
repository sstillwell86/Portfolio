package taylormeans.finalproject;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class JokeClass extends MainActivity {
    Button goBack;
    public static TextView joke;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.joke);

        joke = (TextView)findViewById(R.id.textView);
        Button nextJoke = (Button)findViewById(R.id.nextJoke);
        nextJoke.setOnClickListener(new View.OnClickListener(){
            public void onClick(View v) {
                FetchJoke fetchJoke = new FetchJoke();
                fetchJoke.execute();
            }
        });

        goBack = (Button)findViewById(R.id.goBack);
        goBack.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Intent activityIntent = new Intent(getApplicationContext(), MainActivity.class);
                startActivity(activityIntent);
            }
        });
    }
}
