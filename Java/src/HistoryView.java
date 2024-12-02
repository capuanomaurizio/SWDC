import java.util.Date;

import javax.swing.*;

class HistoryView extends JFrame  {

	private JTextArea log;

	public HistoryView(){
		super("");
		setSize(800,600);
		this.setLocation(25, 200);

		JPanel mainPanel = new JPanel();
		log = new JTextArea(30,50);
		log.setEditable(false);
		JScrollPane scrollPane = new JScrollPane(log);
		mainPanel.add(scrollPane);
		this.getContentPane().add(mainPanel);
	}

	public void log(String msg){
		SwingUtilities.invokeLater(() -> {
			String date = new Date().toString();
			log.append("["+date+"] "+ msg +"\n");
		});
	}
}
