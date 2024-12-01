import javax.swing.SwingUtilities;

public class SWDCDashboard {
    static SWDCDashboardView dashboard = null;
    static HistoryView history = null;

    public static void main(String[] args) {
        try {
            SwingUtilities.invokeAndWait(() -> {
                dashboard = new SWDCDashboardView();
                history = new HistoryView();
            });
        } catch (Exception e) {
            e.printStackTrace();
        }
        String port = "COM3";
        SWDCController controller = new SWDCController(port, dashboard, history);
        dashboard.setController(controller);
        SwingUtilities.invokeLater(() -> {
            dashboard.setVisible(true);
            history.setVisible(true);
        });
    }
}
