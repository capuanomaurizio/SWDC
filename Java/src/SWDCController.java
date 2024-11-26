
public class SWDCController {

    static final String EMPTY_MESSAGE = "empty";
    static final String RESTORE_MESSAGE = "restore";
    static final String CHECK_MESSAGE = "check";

    SerialChannel channel;
    SWDCDashboardView dashboard;
    HistoryView history;

    public SWDCController(String port, SWDCDashboardView dashboard, HistoryView history){
        this.dashboard = dashboard;
        this.history = history;

        channel = new SerialChannel(port, 115200);
        new HistoryPoller(channel, dashboard, history).start();

        /* Waiting Arduino rebooting */
		
		System.out.println("Waiting Arduino for rebooting...");		
		try {
            Thread.sleep(4000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
		System.out.println("Ready.");		
    }

    public void emptyContainer() {
        channel.sendMessage(EMPTY_MESSAGE);
    }

    public void restoreContainer() {
        channel.sendMessage(RESTORE_MESSAGE);
    }

    public void checkContainerState(){
        channel.sendMessage(CHECK_MESSAGE);
    }

}
