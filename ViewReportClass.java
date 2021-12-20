package taylormeans.finalproject;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;

public class ViewReportClass extends MainActivity {
    public static EditText detailsOfReport;
    public static TextView weather;
    public static ImageView photoOfIncident;
    Button goBack;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.view_report);
        weather = findViewById(R.id.weather);
        photoOfIncident = findViewById(R.id.photoOfIncident);
        detailsOfReport = findViewById(R.id.detailsOfReport);
        weather.setText(ListViewActivity.weather);
        detailsOfReport.setText(ListViewActivity.details);
        photoOfIncident.setImageBitmap(ListViewActivity.photo);
        goBack = findViewById(R.id.goBack);
        goBack.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Intent intent = new Intent(getApplicationContext(), ListViewActivity.class);
                startActivity(intent);
            }
        });
    }
}
