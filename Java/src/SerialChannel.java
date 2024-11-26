import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

import jssc.SerialPort;
import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;

public class SerialChannel implements SerialPortEventListener{

    private SerialPort serialPort;
    private BlockingQueue<String> queue;
    private StringBuffer currentMessage = new StringBuffer("");

    public SerialChannel(String port, int bauds){
        queue = new ArrayBlockingQueue<String>(50);
        try {
			serialPort = new SerialPort(port);
			serialPort.openPort();
			serialPort.setParams(bauds, SerialPort.DATABITS_8, SerialPort.STOPBITS_1, SerialPort.PARITY_NONE);
			serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN | SerialPort.FLOWCONTROL_RTSCTS_OUT);	
			serialPort.addEventListener(this);
		} catch (Exception e) {
			e.printStackTrace();
		}
    }

    public void sendMessage(String msg) {
        char[] array = (msg+"\n").toCharArray();
        byte[] bytes = new byte[array.length];
        for (int i = 0; i < array.length; i++){
            bytes[i] = (byte) array[i];
        }
        try {
            synchronized (serialPort) {
                serialPort.writeBytes(bytes);
            }
        } catch(Exception e){
            e.printStackTrace();
        }
    }

    public String receiveMessage() throws InterruptedException {
        return queue.take();
    }

    public boolean isMsgAvailable() {
        return !queue.isEmpty();
    }

    public void close() {
        try {
            if (serialPort != null) {
                serialPort.removeEventListener();
                serialPort.closePort();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void serialEvent(SerialPortEvent event) {
        /* if there are bytes received in the input buffer */
        if (event.isRXCHAR()) {
            try {
                    String msg = serialPort.readString(event.getEventValue());
                    msg = msg.replaceAll("\r", "");
                    currentMessage.append(msg);
                    
                    boolean goAhead = true;
                    while(goAhead) {
                        String msg2 = currentMessage.toString();
                        int index = msg2.indexOf("\n");
                        if (index >= 0) {
                            queue.put(msg2.substring(0, index));
                            currentMessage = new StringBuffer("");
                            if (index + 1 < msg2.length()) {
                                currentMessage.append(msg2.substring(index + 1)); 
                            }
                        } else {
                            goAhead = false;
                        }
                    }
                    
            } catch (Exception e) {
                e.printStackTrace();
                System.out.println("Error in receiving string from COM-port: " + e);
            }
        }
    }

}