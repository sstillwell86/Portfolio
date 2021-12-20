package taylormeans.finalproject;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;
import java.util.ArrayList;
import java.util.List;

public class ListViewActivity extends AppCompatActivity {
    private Database db;
    public static String weather;
    public static String details;
    public static Bitmap photo;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list_view);

        Button goBack = findViewById(R.id.goBack);
        goBack.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Intent intent = new Intent(getApplicationContext(), MainActivity.class);
                startActivity(intent);
            }
        });

        this.arrayAdapterListView();
    }

    // This method use an ArrayAdapter to add data in ListView.
    private void arrayAdapterListView()
    {
        setTitle("List of Reports");
        db = new Database(getApplicationContext());
        List<String> dataList = new ArrayList<>();
        for (int i=0;i < db.allReports().size(); i++) {
            dataList.add(db.getReport(i+1).toString());
        }

        ListView listView = (ListView)findViewById(R.id.reports);
        ArrayAdapter<String> arrayAdapter = new ArrayAdapter<>(this, android.R.layout.simple_list_item_single_choice, dataList);
        listView.setAdapter(arrayAdapter);

        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int index, long l) {
                Object clickItemObj = adapterView.getAdapter().getItem(index);
                Toast.makeText(ListViewActivity.this, "You clicked " + clickItemObj.toString(), Toast.LENGTH_SHORT).show();
                Intent activityIntent = new Intent(getApplicationContext(), ViewReportClass.class);
                weather = db.getReport(index+1).getWeatherStr();
                details = db.getReport(index+1).getDetails();
                photo = BitmapFactory.decodeByteArray(db.getReport(index+1).getPhoto(), 0, db.getReport(index+1).getPhoto().length);
                startActivity(activityIntent);
            }
        });
    }
}