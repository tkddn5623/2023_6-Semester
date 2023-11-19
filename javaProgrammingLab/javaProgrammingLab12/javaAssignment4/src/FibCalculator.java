public class FibCalculator {
    private int series_first;
    private int series_second;

    FibCalculator(int first, int second) {
        setSeries_first(first);
        setSeries_second(second);
    }

    public int getSeries(int length) {
    return 0;
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
