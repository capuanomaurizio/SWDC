public class HistoryPoller extends Thread {

	SerialChannel channel;
	SWDCDashboardView dashboard;
	HistoryView history;

	public HistoryPoller(SerialChannel channel, SWDCDashboardView dashboard, HistoryView history) {
		this.dashboard = dashboard;
		this.history = history;
		this.channel = channel;
	}
	
	public void run(){
		while (true){
			try {
				String message = channel.receiveMessage();
                String[] elems = message.split(":");
                if (elems.length >= 2) {
                    int fillingPerc = Integer.parseInt(elems[0]);
                    int temperature = Integer.parseInt(elems[1]);
                    this.history.log("PREVIOUS VALUES: filling percentage: "+fillingPerc+"%   temperature: "+temperature+"°C");
                    dashboard.updateFillingPerc(fillingPerc);
                    dashboard.updateTemperature(temperature);
					dashboard.enableCheck();
                } else if (message.equals("emptied")) {
					dashboard.enableEmpty();
				} else if (message.equals("restored")) {
					dashboard.enableRestore();
				}
			} catch (Exception e){
				e.printStackTrace();
			}
		}
	}

}
