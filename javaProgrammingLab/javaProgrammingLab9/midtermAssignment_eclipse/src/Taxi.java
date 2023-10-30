public class Taxi extends PublicTransport {
	private double farePerKm;
	private double distance;

	public Taxi(String model, double baseFare, double farePerKm, double distance) {
		super(model, baseFare);
		setFarePerKm(farePerKm);
		setDistance(distance);
		calculatePayment();
	}

	public void calculatePayment() {
		setTotalFare(getBaseFare() + getFarePerKm() * getDistance());
	}

	public double getFarePerKm() {
		return farePerKm;
	}

	public void setFarePerKm(double farePerKm) {
		this.farePerKm = farePerKm;
	}

	public double getDistance() {
		return distance;
	}

	public void setDistance(double distance) {
		this.distance = distance;
	}

}
