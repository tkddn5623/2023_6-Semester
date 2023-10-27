public class Bus extends PublicTransport {
	private Station station;

	public Bus(String model, double baseFare, double farePerStation, int nStations) {
		super(model, baseFare);
		setStation(new Station(farePerStation, nStations));
		calculatePayment();
	}

	public void calculatePayment() {
		if (getnStations() > 5)
			setTotalFare(getBaseFare() + getFarePerStation() * (getnStations() - 5));
		else
			setTotalFare(getBaseFare());
	}

	public double getFarePerStation() {
		return station.getFarePerStation();
	}

	public int getnStations() {
		return station.getnStations();
	}

	public void setStation(Station station) {
		this.station = station;
	}

}
