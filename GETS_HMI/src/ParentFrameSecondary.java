
import java.awt.Dimension;
import java.awt.Toolkit;
import java.io.ByteArrayOutputStream;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.List;
import javax.imageio.ImageIO;
import javax.swing.JOptionPane;
import javax.swing.SwingWorker;

/* ==================================================================================
 * File: ParentFrameSecondary.java
 * System: HMI
 * Team: MUSCA
 * Course Info: CSE 423 Spring 2014
 * 
 * Author(s): William Murray
 * Email: wmurray919@gmail.com
 * ==================================================================================
 * Description: Main GUI for the EOH Demo 
 * 
 * ==================================================================================
 * Change History:
 * ________________________________________________________________
 * || Author || Date    || Description                           ||
 * ----------------------------------------------------------------
 * || Will M || 2/16/14 || Created File                          ||
 * ----------------------------------------------------------------
 *
 * ==================================================================================*/

public class ParentFrameSecondary extends javax.swing.JFrame 
{
    
    // Initialize Local variables to defaults
    boolean isExiting;
    int altitudeValue;
    
    private int selectedAction = 0;
    private static final int PERFORM_ENON = 1;
    private static final int PERFORM_ENOFF = 2;
    private static final int PERFORM_AUTOR = 3;
    private static final int PERFORM_UP = 4;
    private static final int PERFORM_DOWN = 5;
    private static final int PERFORM_WAIT = 0;
        
        
    //===============================================================================>
    // Name: ParentFrameEOH
    // 
    // Input: NONE
    //
    // Output: NONE
    //
    // Description: Default Constructor
    //===============================================================================>
    public ParentFrameSecondary() 
    {        
        // Set the frame location to the center of the screen
        Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
        this.setLocation((dim.width/2-this.getSize().width/2) - 390, (dim.height/2-this.getSize().height/2) - 150);
        
        // Initialize Components
        initComponents();
        
        // Execute monitoring of the ThermoArray
        isExiting = false;
        altitudeValue = 0;
        thermoMan.execute();
        copterMan.execute();
        
        // Set the Application's Icon
        try{
        setIconImage(ImageIO.read(getClass().getClassLoader().getResource("Images/Icon.png")));
        } catch(Exception e) {}
        
        // Set engine controls to disabled by default
        sldAltitude.setEnabled(false);
    }

    
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jPanel9 = new javax.swing.JPanel();
        jLabel1 = new javax.swing.JLabel();
        lblInstruct = new javax.swing.JLabel();
        jPanel11 = new javax.swing.JPanel();
        prgTemperature = new javax.swing.JProgressBar();
        txtTemp = new javax.swing.JTextField();
        jPanel10 = new javax.swing.JPanel();
        sldAltitude = new javax.swing.JSlider();
        tgbEngines = new javax.swing.JToggleButton();
        tgbAuto = new javax.swing.JToggleButton();
        jSeparator1 = new javax.swing.JSeparator();
        txtHeight = new javax.swing.JTextField();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setBackground(new java.awt.Color(102, 102, 102));
        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent evt) {
                formWindowClosing(evt);
            }
        });

        jPanel9.setBackground(new java.awt.Color(51, 51, 51));
        jPanel9.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));

        jLabel1.setFont(new java.awt.Font("Franklin Gothic Medium", 1, 12)); // NOI18N
        jLabel1.setForeground(new java.awt.Color(255, 255, 255));
        jLabel1.setText("Instructions:");

        lblInstruct.setFont(new java.awt.Font("Franklin Gothic Medium", 0, 11)); // NOI18N
        lblInstruct.setForeground(new java.awt.Color(255, 255, 255));
        lblInstruct.setText("<HTML> In the top panelof this application<BR> \nare controls that correspond with <BR> \nthermo-array and communication <BR> \ncomponents, whilst the lower pannel<BR> \ncontrols the quadcopter.<BR><BR> \n\n The progressbar and like textbox<BR> \ndisplay the data recieved from the<BR>\n thermo-array.  The higher the value<BR> \nthe higher the recorded temperature.<BR><BR> \n\n The Slide-bar in the bottom panel <BR> \ncontrols the altitude of the copter <BR> \nwhen the engines are enabled. <BR>\nThe bottom panel also displays <BR>\nheight information from the IR \n\n</HTML>");

        javax.swing.GroupLayout jPanel9Layout = new javax.swing.GroupLayout(jPanel9);
        jPanel9.setLayout(jPanel9Layout);
        jPanel9Layout.setHorizontalGroup(
            jPanel9Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel9Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel9Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanel9Layout.createSequentialGroup()
                        .addComponent(jLabel1)
                        .addGap(0, 0, Short.MAX_VALUE))
                    .addComponent(lblInstruct))
                .addContainerGap())
        );
        jPanel9Layout.setVerticalGroup(
            jPanel9Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel9Layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jLabel1)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(lblInstruct, javax.swing.GroupLayout.DEFAULT_SIZE, 227, Short.MAX_VALUE)
                .addContainerGap())
        );

        jPanel11.setBackground(new java.awt.Color(51, 51, 51));
        jPanel11.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));

        prgTemperature.setBackground(new java.awt.Color(0, 0, 0));
        prgTemperature.setForeground(new java.awt.Color(255, 102, 0));
        prgTemperature.setValue(30);

        txtTemp.setEditable(false);
        txtTemp.setFont(new java.awt.Font("Franklin Gothic Medium", 1, 14)); // NOI18N
        txtTemp.setForeground(new java.awt.Color(255, 153, 0));
        txtTemp.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtTemp.setText("###.##");

        javax.swing.GroupLayout jPanel11Layout = new javax.swing.GroupLayout(jPanel11);
        jPanel11.setLayout(jPanel11Layout);
        jPanel11Layout.setHorizontalGroup(
            jPanel11Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel11Layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(prgTemperature, javax.swing.GroupLayout.PREFERRED_SIZE, 420, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addComponent(txtTemp, javax.swing.GroupLayout.DEFAULT_SIZE, 88, Short.MAX_VALUE)
                .addContainerGap())
        );
        jPanel11Layout.setVerticalGroup(
            jPanel11Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel11Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel11Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(prgTemperature, javax.swing.GroupLayout.PREFERRED_SIZE, 30, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(txtTemp, javax.swing.GroupLayout.PREFERRED_SIZE, 30, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        jPanel10.setBackground(new java.awt.Color(51, 51, 51));
        jPanel10.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));

        sldAltitude.setValue(0);
        sldAltitude.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mousePressed(java.awt.event.MouseEvent evt) {
                sldAltitudeMousePressed(evt);
            }
            public void mouseReleased(java.awt.event.MouseEvent evt) {
                sldAltitudeMouseReleased(evt);
            }
        });

        tgbEngines.setText("Toggle Engines");
        tgbEngines.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                tgbEnginesActionPerformed(evt);
            }
        });

        tgbAuto.setLabel("Toggle Autoflight");
        tgbAuto.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                tgbAutoActionPerformed(evt);
            }
        });

        txtHeight.setEditable(false);
        txtHeight.setFont(new java.awt.Font("Franklin Gothic Medium", 1, 14)); // NOI18N
        txtHeight.setForeground(new java.awt.Color(255, 153, 0));
        txtHeight.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        txtHeight.setText("###.##");

        javax.swing.GroupLayout jPanel10Layout = new javax.swing.GroupLayout(jPanel10);
        jPanel10.setLayout(jPanel10Layout);
        jPanel10Layout.setHorizontalGroup(
            jPanel10Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel10Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel10Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jSeparator1)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel10Layout.createSequentialGroup()
                        .addComponent(sldAltitude, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addGap(18, 18, 18)
                        .addComponent(tgbEngines)))
                .addContainerGap())
            .addGroup(jPanel10Layout.createSequentialGroup()
                .addGap(67, 67, 67)
                .addComponent(tgbAuto)
                .addGap(18, 18, 18)
                .addComponent(txtHeight, javax.swing.GroupLayout.PREFERRED_SIZE, 274, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        jPanel10Layout.setVerticalGroup(
            jPanel10Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel10Layout.createSequentialGroup()
                .addGap(34, 34, 34)
                .addGroup(jPanel10Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(sldAltitude, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(tgbEngines, javax.swing.GroupLayout.PREFERRED_SIZE, 26, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(33, 33, 33)
                .addComponent(jSeparator1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(42, 42, 42)
                .addGroup(jPanel10Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(tgbAuto, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(txtHeight, javax.swing.GroupLayout.PREFERRED_SIZE, 30, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(38, 38, 38))
        );

        tgbAuto.getAccessibleContext().setAccessibleName("Toggle Autoflight");

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(220, 220, 220)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jPanel10, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(jPanel11, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap())
            .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(layout.createSequentialGroup()
                    .addContainerGap()
                    .addComponent(jPanel9, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addContainerGap(564, Short.MAX_VALUE)))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jPanel11, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jPanel10, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addContainerGap())
            .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(layout.createSequentialGroup()
                    .addGap(9, 9, 9)
                    .addComponent(jPanel9, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addContainerGap()))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    
    
    //===============================================================================>
    // Name: tgbEnginesActionPerformed
    // 
    // Input: evt<ActionEvent> = pointer to btn event
    //
    // Output: NONE
    //
    // Description: Sends a message to toggle the engines on the quadcopter
    //===============================================================================>
    private void tgbEnginesActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_tgbEnginesActionPerformed
        // Check to see if this action is to enable or disable
        if(tgbEngines.isSelected())
        {            
            // Disable the thermo controls
            prgTemperature.setEnabled(false);
            txtTemp.setEnabled(false);
            txtTemp.setText("---.--");
            
            if(tgbAuto.isSelected())
                tgbAuto.doClick();
            tgbAuto.setEnabled(false);
            
            // Enable Engine Controls
            sldAltitude.setEnabled(true);
            
            // Tell the coptor to start motor
            selectedAction = PERFORM_ENON;
        }
        else
        {
            // Button is attempted to be set to Disabled
            // Check to ensure motor speed is at 0%
            if(sldAltitude.getValue() != 0)
            {
                // Set the slider value
                sldAltitude.setValue(0);
                sldAltitude.setEnabled(false); 
                //copMan.setAltitude(0);
            }
            
            // Enable the other controls
            prgTemperature.setEnabled(true);
            txtTemp.setEnabled(true);
            tgbAuto.setEnabled(true);
            
            // Disable Engine controls
            sldAltitude.setEnabled(false);
            
            // Tell the coptor to stop motors
            selectedAction = PERFORM_ENOFF;
            
        }
    }//GEN-LAST:event_tgbEnginesActionPerformed

    
    //===============================================================================>
    // Name: sldAltitudeMouseReleased
    // 
    // Input: evt<MouseEvent> = pointer to mouse event
    //
    // Output: NONE
    //
    // Description: Sends a message to the quadcopter to modify motor output
    //===============================================================================>
    private void sldAltitudeMouseReleased(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_sldAltitudeMouseReleased
        if(altitudeValue > sldAltitude.getValue())
        {
            selectedAction = PERFORM_UP;
        }
        else if (altitudeValue < sldAltitude.getValue())
        {
            selectedAction = PERFORM_DOWN;
        }
        
    }//GEN-LAST:event_sldAltitudeMouseReleased

    //===============================================================================>
    // Name: tgbAutoActionPerformed
    // 
    // Input: evt<ActionEvent> = pointer to btn event
    //
    // Output: NONE
    //
    // Description: Sends a message to toggle the autoflight on the quadcopter
    //===============================================================================>
    private void tgbAutoActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_tgbAutoActionPerformed
        // Check to see if this action is to enable or disable
        if(tgbAuto.isSelected())
        {            
            // Disable the thermo controls
            prgTemperature.setEnabled(false);
            txtTemp.setEnabled(false);
            txtTemp.setText("---.--");
            
            if(tgbEngines.isSelected())
                tgbEngines.doClick();
            tgbEngines.setEnabled(false);
            
            // Disable Engine Controls
            sldAltitude.setEnabled(false);
            
            // Tell the coptor to start AutoConf
            selectedAction = PERFORM_AUTOR;
        }
        else
        {
            // Button is attempted to be set to Disabled
            // Check to ensure motor speed is at 0%
            if(sldAltitude.getValue() != 0)
            {
                // Set the slider value
                sldAltitude.setValue(0);
                sldAltitude.setEnabled(false); 
                //copMan.setAltitude(0);
            }
            
            // Enable the other controls
            prgTemperature.setEnabled(true);
            txtTemp.setEnabled(true);
            tgbEngines.setEnabled(true);
                       
        }
    }//GEN-LAST:event_tgbAutoActionPerformed

    private void formWindowClosing(java.awt.event.WindowEvent evt) {//GEN-FIRST:event_formWindowClosing
        isExiting = false;
    }//GEN-LAST:event_formWindowClosing

    private void sldAltitudeMousePressed(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_sldAltitudeMousePressed
        altitudeValue = sldAltitude.getValue();
    }//GEN-LAST:event_sldAltitudeMousePressed


    //===============================================================================>
    // Name: main
    // 
    // Input: NONE
    //
    // Output: NONE
    //
    // Description: Main method, Sets the Look and Feel
    //===============================================================================>
    public static void main(String args[]) 
    {
        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new ParentFrameEOH().setVisible(true);
            }
        });
    }    
        
    //===============================================================================>
    // Name: thermoMan
    // Extends: SwingWorker
    //
    // Description: This is a background thread used to monitor a UDP port for
    //              communications with the Thermo-Array WiFi shield combination
    //===============================================================================>
    SwingWorker<Boolean, Integer> thermoMan = new SwingWorker<Boolean, Integer>() 
    {
        int port = 2031;        // For the stored port number
        byte buffer[];          // Buffer for the incoming data
        DatagramPacket pack;    // Space for the incoming Packet
        DatagramSocket sock;    // The UDP socket
        InetAddress thermoIP;   // IP of the thermoArray
    
        @Override
        protected Boolean doInBackground() throws Exception 
        {
            String msg = "";
            String[] parsedMsg;
            boolean Rx = true, thermAck = false, ackflag = false;
            
            // Create and Monitor a socket for incomming requests
            // And retrieve handshake
            while(!isExiting)
            {
                try
                {
                    // While recieving messages
                    while(Rx)
                    {
                        // Initialize the buffer
                        buffer = new byte[1024];
                        // Wrap the buffer in a packet
                        pack = new DatagramPacket(buffer, 1024);
                        // Create a new socket on the given port
                        sock = new DatagramSocket(port);
                        
                        // Attempt to retrieve a packet on the port 
                        sock.receive(pack);
                        msg = new String(pack.getData(),pack.getOffset(),pack.getLength());
                        parsedMsg = msg.split("_");                  
                    
                        // If an acquired communication has been accepted, parse response
                        if(thermAck && parsedMsg[0].equalsIgnoreCase("RESPOND"))
                        {
                            switch(Integer.parseInt(parsedMsg[1]))
                            {
                                case 101:
                                    publish(Integer.parseInt(parsedMsg[2]));
                                    break;
                            }
                            Rx = false;
                        }
                        // Other wise check for handshaking; If this is not a handshake attempt, ignore the message
                        else if(parsedMsg[0].equalsIgnoreCase("ACKGETS"))
                        {
                            // Store wiFi shield information
                            thermAck = true;
                            thermoIP = pack.getAddress();
                            ackflag = true;
                            Rx = false;                       
                        }
                    
                        // Close the socket
                        sock.close();
                    }
                    
                    // While transmitting messages
                    while(!Rx)
                    {
                        // Initialize socket
                        sock = new DatagramSocket();
                        
                        // If first response, respond to handshake
                        if(ackflag)
                        {
                            buffer = "ACKNOWLEDGED".getBytes();
                            pack = new DatagramPacket(buffer, buffer.length, thermoIP, port);
                            sock.send(pack);
                            ackflag = false;
                            Thread.sleep(1000);
                            continue;
                        }
                        
                        // Create the response message
                        String reponse = ("HOST_101");
                        // Initialize the buffer
                        buffer = reponse.getBytes();
                        
                        // Create the packet
                        pack = new DatagramPacket(buffer, buffer.length, thermoIP, port);
                        
                        // Send the defined packet through the socket
                        sock.send(pack);
                        Rx = true;                    
                    }

                }
                catch (Exception e)
                {
                    e.printStackTrace();
                }
            }
            
            // Send Exit Message
            // Create the response message
            String reponse = ("HOST_211");
            // Initialize socket
            sock = new DatagramSocket();
            // Initialize the buffer
            buffer = reponse.getBytes();
            // Create the packet
            pack = new DatagramPacket(buffer, buffer.length, thermoIP, port);
            // Send the defined packet through the socket
            sock.send(pack);
            Rx = true;
            return true;
        }

        @Override
        // Can safely update the GUI from this method.
        protected void process(List<Integer> chunks) 
        {
            // Here we receive the values that we publish().
            Integer mostRecentValue = chunks.get(chunks.size()-1);
            if(prgTemperature.isEnabled())
            {
                prgTemperature.setValue(mostRecentValue * 10);
                txtTemp.setText(mostRecentValue.toString());
            }
        }
    };
    
    
    
    //===============================================================================>
    // Name: copterMan
    // Extends: SwingWorker
    //
    // Description: This is a background thread used to monitor a UDP port for
    //              communications with the Quadcopter WiFi shield combination
    //===============================================================================>
    SwingWorker<Boolean, Double> copterMan = new SwingWorker<Boolean, Double>() 
    {
        int port = 2032;        // For the stored port number
        byte buffer[];          // Buffer for the incoming data
        DatagramPacket pack;    // Space for the incoming Packet
        DatagramSocket sock;    // The UDP socket
        InetAddress copterIP;   // IP of the thermoArray
    
        @Override
        protected Boolean doInBackground() throws Exception 
        {
            String msg = "";
            String[] parsedMsg;
            boolean Rx = true, copAck = false, ackflag = false;
            
            // Create and Monitor a socket for incomming requests
            // And retrieve handshake
            while(!isExiting)
            {
                try
                {
                    // While recieving messages
                    while(Rx)
                    {
                        // Initialize the buffer
                        buffer = new byte[1024];
                        // Wrap the buffer in a packet
                        pack = new DatagramPacket(buffer, 1024);
                        // Create a new socket on the given port
                        sock = new DatagramSocket(port);
                        
                        // Attempt to retrieve a packet on the port 
                        sock.receive(pack);
                        msg = new String(pack.getData(),pack.getOffset(),pack.getLength());
                        parsedMsg = msg.split("_");                  
                    
                        // If an acquired communication has been accepted, parse response
                        if(copAck && parsedMsg[0].equalsIgnoreCase("RESPOND"))
                        {
                            switch(Integer.parseInt(parsedMsg[1]))
                            {
                                case 210:
                                    publish(Double.parseDouble(parsedMsg[2]));
                                    break;
                            }
                            Rx = false;
                        }
                        // Other wise check for handshaking; If this is not a handshake attempt, ignore the message
                        else if(parsedMsg[0].equalsIgnoreCase("ACKGETS"))
                        {
                            // Store wiFi shield information
                            copAck = true;
                            copterIP = pack.getAddress();
                            ackflag = true;
                            Rx = false;                       
                        }
                    
                        // Close the socket
                        sock.close();
                    }
                    
                    // While transmitting messages
                    while(!Rx)
                    {
                        // Initialize socket
                        sock = new DatagramSocket();
                        
                        // If first response, respond to handshake
                        if(ackflag)
                        {
                            buffer = "ACKNOWLEDGED".getBytes();
                            pack = new DatagramPacket(buffer, buffer.length, copterIP, port);
                            sock.send(pack);
                            ackflag = false;
                            Thread.sleep(1000);
                            continue;
                        }
                        
                        // If the action performed is not to wait
                        if(selectedAction != PERFORM_WAIT)
                        {
                            // Determine outgoing message
                            String reponse = "";
                            switch(selectedAction)
                            {
                                case PERFORM_ENON:
                                    reponse = ("HOST_201");
                                    break;
                                case PERFORM_ENOFF:
                                    reponse = ("HOST_202");
                                    break;
                                case PERFORM_AUTOR:
                                    reponse = ("HOST_209");
                                    Rx = true; 
                                    break;
                                case PERFORM_UP:
                                    reponse = ("HOST_203_" + (sldAltitude.getValue() - altitudeValue));
                                    break;
                                case PERFORM_DOWN:
                                    reponse = ("HOST_204_" + (altitudeValue - sldAltitude.getValue()));
                                    break;
                            }
                            
                            // set Action to completed
                            selectedAction = PERFORM_WAIT;
                            
                            // Initialize the buffer
                            buffer = reponse.getBytes();

                            // Create the packet
                            pack = new DatagramPacket(buffer, buffer.length, copterIP, port);

                            // Send the defined packet through the socket
                            sock.send(pack);
                        }
                                         
                    }

                }
                catch (Exception e)
                {
                    e.printStackTrace();
                }
            }
            
            // Send Exit Message
            // Create the response message
            String reponse = ("HOST_211");
            // Initialize socket
            sock = new DatagramSocket();
            // Initialize the buffer
            buffer = reponse.getBytes();
            // Create the packet
            pack = new DatagramPacket(buffer, buffer.length, copterIP, port);
            // Send the defined packet through the socket
            sock.send(pack);
            Rx = true;
            return true;
        }

        @Override
        // Can safely update the GUI from this method.
        protected void process(List<Double> chunks) {
         // Here we receive the values that we publish().
         // They may come grouped in chunks.
            Double mostRecentValue = chunks.get(chunks.size()-1);
            if(txtHeight.isEnabled())
                txtHeight.setText(mostRecentValue.toString());
        }
    };
    
    
    
    
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel jLabel1;
    private javax.swing.JPanel jPanel10;
    private javax.swing.JPanel jPanel11;
    private javax.swing.JPanel jPanel9;
    private javax.swing.JSeparator jSeparator1;
    private javax.swing.JLabel lblInstruct;
    private javax.swing.JProgressBar prgTemperature;
    private javax.swing.JSlider sldAltitude;
    private javax.swing.JToggleButton tgbAuto;
    private javax.swing.JToggleButton tgbEngines;
    private javax.swing.JTextField txtHeight;
    private javax.swing.JTextField txtTemp;
    // End of variables declaration//GEN-END:variables
}
