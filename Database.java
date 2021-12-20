package taylormeans.finalproject;

import java.util.LinkedList;
import java.util.List;
import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class Database extends SQLiteOpenHelper {

    private static final int DATABASE_VERSION = 1;
    private static final String KEY_ID = "id";
    private static final String DATABASE_NAME = "ReportsDB";
    private static final String TABLE_NAME = "Reports";
    private static final String KEY_FILENAME = "filename";
    private static final String KEY_DETAILS = "details";
    private static final String KEY_WEATHER = "weather";
    private static final String KEY_PHOTO = "photo";
    private static final String[] COLUMNS = {KEY_ID, KEY_FILENAME, KEY_DETAILS, KEY_WEATHER,
            KEY_PHOTO };

    public Database(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        String CREATION_TABLE = "CREATE TABLE Reports ( "
                + "id INTEGER PRIMARY KEY AUTOINCREMENT, " + "filename TEXT, "
                + "details TEXT, " + "weather TEXT, " + "photo BLOB )";
        db.execSQL(CREATION_TABLE);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_NAME);
        this.onCreate(db);
    }

    public void deleteOne(ReportClass report) {
        // Get reference to writable DB
        SQLiteDatabase db = this.getWritableDatabase();
        db.delete(TABLE_NAME, "id = ?", new String[] { String.valueOf(report.getId()) });
        db.close();
    }

    public ReportClass getReport(int id) {
        SQLiteDatabase db = this.getReadableDatabase();
        Cursor cursor = db.query(TABLE_NAME, // a. table
                COLUMNS, // b. column names
                " id = ?", // c. selections
                new String[] { String.valueOf(id) }, // d. selections args
                null, // e. group by
                null, // f. having
                null, // g. order by
                null); // h. limit
        if (cursor != null) {
            cursor.moveToFirst();
        }
        ReportClass report = new ReportClass();
        report.setId(Integer.parseInt(cursor.getString(0)));
        report.setFileName(cursor.getString(1));
        report.setDetails(cursor.getString(2));
        report.setWeatherStr(cursor.getString(3));
        report.setPhoto(cursor.getBlob(4));
        return report;
    }

    public List<ReportClass> allReports() {
        List<ReportClass> reports = new LinkedList<ReportClass>();
        String query = "SELECT  * FROM " + TABLE_NAME;
        SQLiteDatabase db = this.getWritableDatabase();
        Cursor cursor = db.rawQuery(query, null);
        ReportClass report = null;
        if (cursor.moveToFirst()) {
            do {
                report = new ReportClass();
                report.setId(Integer.parseInt(cursor.getString(0)));
                report.setFileName(cursor.getString(1));
                report.setDetails(cursor.getString(2));
                report.setWeatherStr(cursor.getString(3));
                report.setPhoto(cursor.getBlob(4));
                reports.add(report);
            } while (cursor.moveToNext());
        }
        return reports;
    }

    public void addReport(ReportClass report) {
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues values = new ContentValues();
        values.put(KEY_FILENAME, report.getFileName());
        values.put(KEY_DETAILS, report.getDetails());
        values.put(KEY_WEATHER, report.getWeatherStr());
        values.put(KEY_PHOTO, report.getPhoto());
        // insert
        db.insert(TABLE_NAME,null, values);
        db.close();
    }

    public int updateReport(ReportClass report) {
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues values = new ContentValues();
        values.put(KEY_FILENAME, report.getFileName());
        values.put(KEY_DETAILS, report.getDetails());
        values.put(KEY_WEATHER, report.getWeatherStr());
        values.put(KEY_PHOTO, report.getPhoto());
        int i = db.update(TABLE_NAME, // table
                values, // column/value
                "id = ?", // selections
                new String[] { String.valueOf(report.getFileName()) });
        db.close();
        return i;
    }
}