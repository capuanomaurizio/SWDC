
import java.awt.event.*;
import java.awt.Dimension;
import javax.swing.*;

public class SWDCDashboardView extends JFrame implements ActionListener{

    private JButton emptyContainer;
    private JButton restoreContainer;
    private JButton checkState;
    private JTextField fillingPerc;
    private JTextField temperature;

    private SWDCController controller;

    public SWDCDashboardView(){
        super(".:: Smart Waste Disposal Container ::.");
        setSize(600, 150);

        JPanel mainPanel = new JPanel();
        mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));
        mainPanel.add(Box.createRigidArea(new Dimension(0,20)));

        JPanel statePanel = new JPanel();
		statePanel.setLayout(new BoxLayout(statePanel, BoxLayout.LINE_AXIS));

		fillingPerc = new JTextField("--");
		fillingPerc.setEditable(false);
		fillingPerc.setPreferredSize(new Dimension(50,15));
		statePanel.add(new JLabel("Filling percentage:"));
		statePanel.add(fillingPerc);

		temperature = new JTextField("--");
		temperature.setEditable(false);
		temperature.setPreferredSize(new Dimension(50,15));
		statePanel.add(new JLabel("Waste temperature:"));
		statePanel.add(temperature);
		
		mainPanel.add(statePanel);
		mainPanel.add(Box.createRigidArea(new Dimension(0,20)));
		mainPanel.setPreferredSize(new Dimension(200,20));

		JPanel buttonsPanel = new JPanel();
		emptyContainer = new JButton("Empty container");
		emptyContainer.setEnabled(true);
		emptyContainer.addActionListener(this);
        restoreContainer = new JButton("Restore container");
		restoreContainer.setEnabled(true);
		restoreContainer.addActionListener(this);
        checkState = new JButton("Check state");
		checkState.setEnabled(true);
		checkState.addActionListener(this);

		buttonsPanel.setLayout(new BoxLayout(buttonsPanel, BoxLayout.X_AXIS));	    
		buttonsPanel.add(emptyContainer);
        buttonsPanel.add(restoreContainer);
        buttonsPanel.add(checkState);
		
		mainPanel.add(buttonsPanel);
		mainPanel.add(Box.createRigidArea(new Dimension(0,20)));
		setContentPane(mainPanel);	
		
		addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent ev){
				System.exit(-1);
			}
		});
    }

    public void setController(SWDCController controller) {
        this.controller = controller;
    }

    public void updateFillingPerc(int perc){
		SwingUtilities.invokeLater(() -> {
			fillingPerc.setText(Integer.toString(perc)+"%"); 
		});
	}

	public void updateTemperature(int temp){
		SwingUtilities.invokeLater(() -> {
			temperature.setText(Integer.toString(temp)+"°C");
		});
	}
	
	public void enableEmpty() {
		SwingUtilities.invokeLater(() -> {
			emptyContainer.setEnabled(true);
		});
	}

    public void enableRestore() {
		SwingUtilities.invokeLater(() -> {
			restoreContainer.setEnabled(true);
		});
	}

    public void enableCheck() {
		SwingUtilities.invokeLater(() -> {
			checkState.setEnabled(true);
		});
	}

    @Override
    public void actionPerformed(ActionEvent e) {
        try {
            if (e.getSource() == emptyContainer){
                controller.emptyContainer();
            } else if (e.getSource() == restoreContainer) {
                controller.restoreContainer();
            } else if (e.getSource() == checkState) {
                controller.checkContainerState();
            }
            emptyContainer.setEnabled(false);
            restoreContainer.setEnabled(false);
            checkState.setEnabled(false);
        } catch (Exception ex){
            ex.printStackTrace();
        }
    }

}
