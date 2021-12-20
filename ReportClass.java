package taylormeans.finalproject;

public class ReportClass {
    private int id;
    private String fileName;
    private String details;
    private String weatherStr;
    private byte[] photo;

    public ReportClass() {

    }

    public ReportClass(int id, String fileName, String details, String weatherStr, byte[] photo) {
        this.id = id;
        this.fileName = fileName;
        this.details = details;
        this.weatherStr = weatherStr;
        this.photo = photo;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getFileName() {
        return fileName;
    }

    public void setFileName(String fileName) {
        this.fileName = fileName;
    }

    public String getDetails() {
        return details;
    }

    public void setDetails(String details) {
        this.details = details;
    }

    public String getWeatherStr() {
        return weatherStr;
    }

    public void setWeatherStr(String weatherStr) {
        this.weatherStr = weatherStr;
    }

    public byte[] getPhoto() {
        return photo;
    }

    public void setPhoto(byte[] photo) {
        this.photo = photo;
    }

    @Override
    public String toString() {
        return fileName + " - " + details + " - " + weatherStr + " cm";
    }
}
