public class Station {
	private double farePerStation;
	private int nStations;

	public Station(double farePerStation, int nStations) {
		setFarePerStation(farePerStation);
		setnStations(nStations);
	}

	public double getFarePerStation() {
		return farePerStation;
	}

	public void setFarePerStation(double farePerStation) {
		this.farePerStation = farePerStation;
	}

	public int getnStations() {
		return nStations;
	}

	public void setnStations(int nStations) {
		this.nStations = nStations;
	}
}
