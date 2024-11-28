public class HistoryPoller extends Thread {

	SerialChannel channel;
	SWDCDashboardView dashboard;
	HistoryView history;
	
	// static final String PLANT_PREFIX 	=  "cw:";
	// static final String LOG_PREFIX 	=  "lo:";
	// static final String MSG_STATE 		= "st:";
	
	// static final String[] stateNames = {"Idle", "Checking-In", "Checking-Out","Ready for Washing", "Washing", "In maintenance" }; 
	
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
                } 
				dashboard.enableEmpty();
				dashboard.enableRestore();
				dashboard.enableCheck();
				/*if (msg.startsWith(PLANT_PREFIX)){
					String cmd = msg.substring(PLANT_PREFIX.length()); 
					// logger.log("new command: "+cmd);				
					
					if (cmd.startsWith(MSG_STATE)){
						try {
							String args = cmd.substring(MSG_STATE.length()); 
							
							String[] elems = args.split(":");
							if (elems.length >= 2) {
								int fillingPerc = Integer.parseInt(elems[0]);
								int temperature = Integer.parseInt(elems[1]);
		
								dashboard.updateFillingPerc(fillingPerc);
								dashboard.updateTemperature(temperature);
							}
						} catch (Exception e) {
							e.printStackTrace();
							System.err.println("Error in msg: " + cmd);
						}
					}
				} else if (msg.startsWith(LOG_PREFIX)){
					this.history.log(msg.substring(LOG_PREFIX.length()));
				}*/
			} catch (Exception e){
				e.printStackTrace();
			}
		}
	}

}
