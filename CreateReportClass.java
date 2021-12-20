package taylormeans.finalproject;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.os.Bundle;
import android.provider.MediaStore;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;
import java.io.ByteArrayOutputStream;
import java.util.List;

public class CreateReportClass extends MainActivity {
    private Context context = this;
    public static EditText detailsOfReport;
    public static TextView weather;
    // GUI variables
    Button goBack, takePhoto, saveCreate;
    public static ImageView photoOfIncident;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.create_report);

        // Action of back button
        goBack = findViewById(R.id.goBack);
        goBack.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Intent intent = new Intent(getApplicationContext(), MainActivity.class);
                startActivity(intent);
            }
        });

        weather = findViewById(R.id.weather);

        // Get photo from view
        photoOfIncident = findViewById(R.id.photoOfIncident);
        // Action of photo button
        takePhoto = findViewById(R.id.takePhoto);
        takePhoto.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Intent intent2 = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
                startActivityForResult(intent2, 100);
            }
        });

        // Get details from view
        detailsOfReport = findViewById(R.id.detailsOfReport);

        // action of the save button opens the popup
        saveCreate = findViewById(R.id.saveCreate);
        saveCreate.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //creates AlertDialog popup
                final AlertDialog.Builder inputAlert = new AlertDialog.Builder(context);
                inputAlert.setTitle("Title:");
                inputAlert.setMessage("Enter Report Title");
                final EditText userInput = new EditText(context);
                inputAlert.setView(userInput);
                inputAlert.setPositiveButton("Submit", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        //creates a report object
                        final ReportClass report = new ReportClass();
                        //gets the database from memory
                        final Database db = new Database(getApplicationContext());
                        //creates list of all reports to determine what next reports number should be
                        List<ReportClass> reports = db.allReports();
                        //sets report id in database as the number of reports currently in database + 1
                        report.setId(reports.size()+1);
                        //puts title user entered into report object
                        report.setFileName(userInput.getText().toString());
                        // puts details from textview into report object
                        report.setDetails(detailsOfReport.getText().toString());
                        // puts weather data into report object
                        report.setWeatherStr(weather.getText().toString());
                        //get bitmap from ImageView, convert to byte array to send to DB
                        if (photoOfIncident.getDrawable() == null) {
                            byte[] photo = {0,1,0,1,0};
                            report.setPhoto(photo);
                        }
                        else {
                            Bitmap bitmap = ((BitmapDrawable) photoOfIncident.getDrawable()).getBitmap();
                            ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
                            bitmap.compress(Bitmap.CompressFormat.PNG, 0, outputStream);
                            report.setPhoto(outputStream.toByteArray());
                        }
                        if (reports.contains(report)) {
                            final AlertDialog.Builder overwriteAlert = new AlertDialog.Builder(context);
                            overwriteAlert.setTitle("Confirm Report Edit");
                            overwriteAlert.setMessage("Modify Existing Report?");
                            overwriteAlert.setPositiveButton("Confirm", new DialogInterface.OnClickListener() {
                                @Override
                                public void onClick(DialogInterface dialogInterface, int i) {
                                    db.updateReport(report);
                                }
                            });
                            overwriteAlert.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                                @Override
                                public void onClick(DialogInterface dialog, int which) {
                                    dialog.dismiss();
                                }
                            });
                        }
                        else {
                            db.addReport(report);
                            // if data saved, show toast to use that Report was saved successfully
                            if (db.getReport(reports.size()+1) != null) {
                                Toast.makeText(getApplicationContext(), "Report Saved", Toast.LENGTH_SHORT).show();
                                // When save is complete, dismiss popup and go back to home screen
                                Intent goHome = new Intent(getApplicationContext(), MainActivity.class);
                                startActivity(goHome);
                            } else {
                                // otherwise, show toast that says there was an error in saving
                                Toast.makeText(getApplicationContext(), "Error", Toast.LENGTH_SHORT).show();
                                Intent goHome = new Intent(getApplicationContext(), MainActivity.class);
                                startActivity(goHome);
                            }
                        }
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
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        Bitmap bitmap = (Bitmap)data.getExtras().get("data");
        photoOfIncident.setImageBitmap(bitmap);
    }
}