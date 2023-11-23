import javax.swing.*;
import java.util.ArrayList;

public class FibCalculator extends SwingWorker<ArrayList<String>, String> {
    private int series_first;
    private int series_second;

    FibCalculator(int first, int second) {
        setSeries_first(first);
        setSeries_second(second);
    }

    public ArrayList<String> doInBackground(int length) {
        ArrayList<String> list = new ArrayList<String>();
        int last = getSeries_second();
        publish(Integer.toString(getSeries_first()));
        publish(Integer.toString(last));
        for (int i = 0; i < length - 2; i++) {

        }
        return list;
    }

    public void setSeries_first(int series_first) {
        this.series_first = series_first;
    }

    public void setSeries_second(int series_second) {
        this.series_second = series_second;
    }

    private int getSeries_first() {
        return series_first;
    }

    private int getSeries_second() {
        return series_second;
    }

}
