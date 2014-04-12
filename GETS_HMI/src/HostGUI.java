
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Toolkit;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;
import javax.swing.SwingWorker;
import javax.swing.Timer;
import javax.swing.text.Style;
import javax.swing.text.StyleConstants;
import javax.swing.text.StyledDocument;

/* ==================================================================================
 * File: ParentFrameSecondary.java
 * System: HMI
 * Team: MUSCA
 * Course Info: CSE 423 Spring 2014
 * 
 * Author(s): William Murray
 * Email: wmurray919@gmail.com
 * ==================================================================================
 * Description: Main GUI for the final scope deliverable
 * 
 * ==================================================================================
 * Protocol Overvieew:
 * 
 *      HOST_202 = Begin Launch Sequence
 *      HOST_201 = Begin Landing Sequence
 *      HOST_998 = Sec Warning; IP or Port broadcast changed, init kill timer
 *      HOST_999 = Emergency Kill Sequence
 *
 * ==================================================================================*/


public class HostGUI extends javax.swing.JFrame 
{
    // Connection Variables
    public int UDP_PORT = 2390;
    public String TARGET_IP = "192.168.1.10";
    byte dataBuffer[];           
    DatagramPacket UDPpacket;   
    DatagramSocket UDPsocket; 
    
    // Message Constants
    public static final int UDP_TYPE = 0;
    public static final int ALERT_TYPE = 1;
    public static final int GENERIC_TYPE = 2;
    
    // Instance Variables
    StyledDocument doc;
    Style flowPaneStyle;
    boolean isExiting, bTakeOff, bisKilled, bisNew;
    int height = 470;
    
    

    //===============================================================================>
    // Name: HostGUI
    // 
    // Input: NONE
    //
    // Output: NONE
    //
    // Description: Default Constructor
    //===============================================================================>
    public HostGUI() 
    {
        // Set the frame location to the center of the screen
        Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
        this.setLocation((dim.width/2-this.getSize().width/2) - 390, (dim.height/2-this.getSize().height/2) - 150);
        
        // Initialize Components
        initComponents();
        txtPort.setText(UDP_PORT +"");
        txtNetwork.setText(TARGET_IP +"");
        
        // Set the Application's Icon
        try{
        setIconImage(ImageIO.read(getClass().getClassLoader().getResource("Images/Icon.png")));
        } catch(Exception e) {}
        
        // Instantiate textPanel modifiers
        doc = txtUDPStat.getStyledDocument();
        flowPaneStyle = txtUDPStat.addStyle("", null);
        
        // Start the quadcopter animation process
        //animationPanel.setLayout(null);
        isExiting = false;
        bTakeOff = false;
        bisKilled = false;
        bisNew = false;
        imgCopter.setVisible(false);
        
        animationManager.execute();
    }

    
    
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jPanel1 = new javax.swing.JPanel();
        jScrollPane2 = new javax.swing.JScrollPane();
        txtUDPStat = new javax.swing.JTextPane();
        jLabel7 = new javax.swing.JLabel();
        txtNetwork = new javax.swing.JTextField();
        jLabel8 = new javax.swing.JLabel();
        txtPort = new javax.swing.JTextField();
        btnNetUpdate = new javax.swing.JButton();
        jPanel2 = new javax.swing.JPanel();
        jLabel1 = new javax.swing.JLabel();
        jLabel2 = new javax.swing.JLabel();
        jLabel3 = new javax.swing.JLabel();
        jLabel4 = new javax.swing.JLabel();
        txtMot1 = new javax.swing.JTextField();
        txtMot2 = new javax.swing.JTextField();
        txtMot3 = new javax.swing.JTextField();
        txtMot4 = new javax.swing.JTextField();
        jLabel5 = new javax.swing.JLabel();
        txtHeight = new javax.swing.JTextField();
        jSeparator1 = new javax.swing.JSeparator();
        jPanel3 = new javax.swing.JPanel();
        jLabel6 = new javax.swing.JLabel();
        tglMotors = new javax.swing.JToggleButton();
        jSeparator2 = new javax.swing.JSeparator();
        btnAdvanced = new javax.swing.JButton();
        btnKill = new javax.swing.JButton();
        btnForward = new javax.swing.JButton();
        btnBackward = new javax.swing.JButton();
        btnLeft = new javax.swing.JButton();
        btnRight = new javax.swing.JButton();
        sldHeight = new javax.swing.JSlider();
        animationPanel = new javax.swing.JPanel();
        imgCopter = new javax.swing.JLabel();
        jLabel10 = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("GETS Host And Control System");
        setResizable(false);

        jPanel1.setBorder(javax.swing.BorderFactory.createTitledBorder("UDP Flow Monitor"));

        txtUDPStat.setEditable(false);
        txtUDPStat.setBackground(new java.awt.Color(227, 227, 227));
        txtUDPStat.setSelectedTextColor(new java.awt.Color(227, 227, 227));
        jScrollPane2.setViewportView(txtUDPStat);

        jLabel7.setText("Target Network Address:");

        txtNetwork.setBackground(new java.awt.Color(227, 227, 227));
        txtNetwork.setText("0.0");
        txtNetwork.addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyPressed(java.awt.event.KeyEvent evt) {
                txtNetworkKeyPressed(evt);
            }
        });

        jLabel8.setText("Port:");

        txtPort.setBackground(new java.awt.Color(227, 227, 227));
        txtPort.setText("0.0");
        txtPort.addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyPressed(java.awt.event.KeyEvent evt) {
                txtPortKeyPressed(evt);
            }
        });

        btnNetUpdate.setText("Update");
        btnNetUpdate.setEnabled(false);
        btnNetUpdate.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnNetUpdateActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jScrollPane2)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGap(2, 2, 2)
                .addComponent(jLabel7)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(txtNetwork, javax.swing.GroupLayout.PREFERRED_SIZE, 140, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(jLabel8)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(txtPort)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(btnNetUpdate))
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addComponent(jScrollPane2, javax.swing.GroupLayout.DEFAULT_SIZE, 178, Short.MAX_VALUE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel7)
                    .addComponent(txtNetwork, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jLabel8)
                    .addComponent(txtPort, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btnNetUpdate)))
        );

        jPanel2.setBorder(javax.swing.BorderFactory.createTitledBorder("Quad-coptor Status"));

        jLabel1.setText("Motor Speed [1]:");

        jLabel2.setText("Motor Speed [2]:");

        jLabel3.setText("Motor Speed [3]:");

        jLabel4.setText("Motor Speed [4]:");

        txtMot1.setEditable(false);
        txtMot1.setBackground(new java.awt.Color(227, 227, 227));
        txtMot1.setText("0.0");

        txtMot2.setEditable(false);
        txtMot2.setBackground(new java.awt.Color(227, 227, 227));
        txtMot2.setText("0.0");

        txtMot3.setEditable(false);
        txtMot3.setBackground(new java.awt.Color(227, 227, 227));
        txtMot3.setText("0.0");

        txtMot4.setEditable(false);
        txtMot4.setBackground(new java.awt.Color(227, 227, 227));
        txtMot4.setText("0.0");

        jLabel5.setText("Appx. Height:");

        txtHeight.setEditable(false);
        txtHeight.setBackground(new java.awt.Color(227, 227, 227));
        txtHeight.setText("0.0");

        javax.swing.GroupLayout jPanel2Layout = new javax.swing.GroupLayout(jPanel2);
        jPanel2.setLayout(jPanel2Layout);
        jPanel2Layout.setHorizontalGroup(
            jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel2Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jSeparator1)
                    .addGroup(jPanel2Layout.createSequentialGroup()
                        .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addGroup(jPanel2Layout.createSequentialGroup()
                                .addComponent(jLabel2)
                                .addGap(18, 18, 18)
                                .addComponent(txtMot2))
                            .addGroup(jPanel2Layout.createSequentialGroup()
                                .addComponent(jLabel3)
                                .addGap(18, 18, 18)
                                .addComponent(txtMot3))
                            .addGroup(jPanel2Layout.createSequentialGroup()
                                .addComponent(jLabel4)
                                .addGap(18, 18, 18)
                                .addComponent(txtMot4))
                            .addGroup(jPanel2Layout.createSequentialGroup()
                                .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(jLabel1)
                                    .addComponent(jLabel5))
                                .addGap(18, 18, 18)
                                .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(txtHeight, javax.swing.GroupLayout.PREFERRED_SIZE, 80, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(txtMot1, javax.swing.GroupLayout.PREFERRED_SIZE, 80, javax.swing.GroupLayout.PREFERRED_SIZE))))
                        .addGap(0, 0, Short.MAX_VALUE)))
                .addContainerGap())
        );
        jPanel2Layout.setVerticalGroup(
            jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel2Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel5)
                    .addComponent(txtHeight, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(jSeparator1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel1)
                    .addComponent(txtMot1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel2)
                    .addComponent(txtMot2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel3)
                    .addComponent(txtMot3, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel4)
                    .addComponent(txtMot4, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap())
        );

        jPanel3.setBorder(javax.swing.BorderFactory.createTitledBorder("Functional Controls"));

        jLabel6.setText("Motor Control: ");

        tglMotors.setText("Launch Quad-coptor");
        tglMotors.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                tglMotorsActionPerformed(evt);
            }
        });

        btnAdvanced.setText("Advanced Controls");
        btnAdvanced.setEnabled(false);

        btnKill.setBackground(new java.awt.Color(198, 102, 102));
        btnKill.setText("Emergency Kill");
        btnKill.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnKillActionPerformed(evt);
            }
        });

        btnForward.setText("Forward");
        btnForward.setEnabled(false);

        btnBackward.setText("Backward");
        btnBackward.setEnabled(false);

        btnLeft.setText("Left");
        btnLeft.setEnabled(false);

        btnRight.setText("Right");
        btnRight.setEnabled(false);

        sldHeight.setOrientation(javax.swing.JSlider.VERTICAL);
        sldHeight.setEnabled(false);

        javax.swing.GroupLayout jPanel3Layout = new javax.swing.GroupLayout(jPanel3);
        jPanel3.setLayout(jPanel3Layout);
        jPanel3Layout.setHorizontalGroup(
            jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel3Layout.createSequentialGroup()
                .addComponent(btnKill, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(btnAdvanced, javax.swing.GroupLayout.PREFERRED_SIZE, 132, javax.swing.GroupLayout.PREFERRED_SIZE))
            .addGroup(jPanel3Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanel3Layout.createSequentialGroup()
                        .addGroup(jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                            .addGroup(jPanel3Layout.createSequentialGroup()
                                .addComponent(jLabel6)
                                .addGap(34, 34, 34)
                                .addComponent(tglMotors))
                            .addGroup(jPanel3Layout.createSequentialGroup()
                                .addGroup(jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addGroup(jPanel3Layout.createSequentialGroup()
                                        .addComponent(btnLeft, javax.swing.GroupLayout.PREFERRED_SIZE, 65, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addGap(29, 29, 29)
                                        .addComponent(btnRight, javax.swing.GroupLayout.PREFERRED_SIZE, 65, javax.swing.GroupLayout.PREFERRED_SIZE))
                                    .addGroup(jPanel3Layout.createSequentialGroup()
                                        .addGap(32, 32, 32)
                                        .addGroup(jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                            .addComponent(btnBackward, javax.swing.GroupLayout.PREFERRED_SIZE, 88, javax.swing.GroupLayout.PREFERRED_SIZE)
                                            .addComponent(btnForward, javax.swing.GroupLayout.PREFERRED_SIZE, 88, javax.swing.GroupLayout.PREFERRED_SIZE))))
                                .addGap(33, 33, 33)
                                .addComponent(sldHeight, javax.swing.GroupLayout.PREFERRED_SIZE, 24, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(22, 22, 22)))
                        .addGap(0, 0, Short.MAX_VALUE))
                    .addComponent(jSeparator2))
                .addContainerGap())
        );
        jPanel3Layout.setVerticalGroup(
            jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel3Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel6)
                    .addComponent(tglMotors))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(jSeparator2, javax.swing.GroupLayout.PREFERRED_SIZE, 2, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addGroup(jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addGroup(jPanel3Layout.createSequentialGroup()
                        .addComponent(btnForward)
                        .addGap(9, 9, 9)
                        .addGroup(jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(btnLeft)
                            .addComponent(btnRight))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(btnBackward))
                    .addComponent(sldHeight, javax.swing.GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE))
                .addGap(23, 23, 23)
                .addGroup(jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(btnAdvanced)
                    .addComponent(btnKill)))
        );

        animationPanel.setBorder(javax.swing.BorderFactory.createTitledBorder(""));

        imgCopter.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        imgCopter.setIcon(new javax.swing.ImageIcon(getClass().getResource("/Images/quadcopter.jpg"))); // NOI18N
        imgCopter.setVerticalAlignment(javax.swing.SwingConstants.TOP);

        jLabel10.setIcon(new javax.swing.ImageIcon(getClass().getResource("/Images/platform.jpg"))); // NOI18N
        jLabel10.setToolTipText("");

        javax.swing.GroupLayout animationPanelLayout = new javax.swing.GroupLayout(animationPanel);
        animationPanel.setLayout(animationPanelLayout);
        animationPanelLayout.setHorizontalGroup(
            animationPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(imgCopter)
            .addComponent(jLabel10)
        );
        animationPanelLayout.setVerticalGroup(
            animationPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(animationPanelLayout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(imgCopter, javax.swing.GroupLayout.PREFERRED_SIZE, 32, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(133, 133, 133)
                .addComponent(jLabel10))
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(jPanel1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(jPanel2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(jPanel3, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(animationPanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addGap(3, 3, 3)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(jPanel2, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(jPanel3, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                        .addGap(11, 11, 11)
                        .addComponent(jPanel1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                    .addGroup(layout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(animationPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    
    private boolean txUDP(String command)
    {
        boolean result = false;
        
        try 
        {
            UDPsocket = new DatagramSocket();
            dataBuffer = command.getBytes();
            UDPpacket = new DatagramPacket(dataBuffer, dataBuffer.length, InetAddress.getByName(TARGET_IP), UDP_PORT);
            UDPsocket.send(UDPpacket);
            result = true;
        } 
        catch (Exception ex) 
        {
            result = false;
        }
        
        return result;
    }
    
    private void postMessage(String msg, int msgType)
    {
        switch(msgType)
        {
            case UDP_TYPE: StyleConstants.setForeground(flowPaneStyle, Color.black);
                break;
            case ALERT_TYPE: StyleConstants.setForeground(flowPaneStyle, Color.red);
                break;
            case GENERIC_TYPE: StyleConstants.setForeground(flowPaneStyle, Color.blue);
                break;
        }
        
        try { doc.insertString(doc.getLength(), msg + "\n", flowPaneStyle); }
        catch (Exception e){}
    }
    
    private void resetControls()
    {
        tglMotors.setText("Launch Quad-copter");
        tglMotors.setSelected(false);
        
        txtHeight.setText("0.0");
        txtMot1.setText("0.0");
        txtMot2.setText("0.0");
        txtMot3.setText("0.0");
        txtMot4.setText("0.0");
    }
    
    private void tglMotorsActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_tglMotorsActionPerformed
        // Send the Launch or Land command depending on button state
        
        
        if(tglMotors.isSelected())
        {
            // Send Launch Instruction of UDP
            boolean res = txUDP("HOST_201");
            bTakeOff = true;
            bisKilled = false;
            bisNew = false;
            if(res)
            {
                // Update the button state
                tglMotors.setText("  Land Quad-copter  ");
                
                // Notfy user of success
                postMessage("[" + TARGET_IP + ":" + UDP_PORT + "] UDP Packet Successfully Broadcasted: HOST_201" ,UDP_TYPE);
            }
            else
            {
                // Notfy user of Failure
                postMessage("ERROR IN SENDING UDP Packet: HOST_201" ,ALERT_TYPE);
            }
        }
        else
        {
            // Send Launch Instruction of UDP
            boolean res = txUDP("HOST_202");
            bTakeOff = false;
            if(res)
            {
                // Update the button state
                tglMotors.setText("Launch Quad-copter");
                
                // Notfy user of success
                postMessage("[" + TARGET_IP + ":" + UDP_PORT + "] UDP Packet Successfully Broadcasted: HOST_202" ,UDP_TYPE);
            }
            else
            {
                // Notfy user of Failure
                postMessage("ERROR IN SENDING UDP Packet: HOST_202" ,ALERT_TYPE);
            }
        }
        
        
    }//GEN-LAST:event_tglMotorsActionPerformed

    private void btnKillActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnKillActionPerformed
        
        boolean res = false;
        bisKilled = true;
        // Send KILL Instruction of UDP
        for(int i = 0; i < 10; i++)
            res = txUDP("HOST_999");

        if(res)
            // Notfy user of success
            postMessage("[" + TARGET_IP + ":" + UDP_PORT + "] UDP Packet Successfully Broadcasted: HOST_999" ,UDP_TYPE);
        else
            postMessage("ERROR IN SENDING KILL COMMAND: HOST999" ,ALERT_TYPE);  
        
        resetControls();
        
    }//GEN-LAST:event_btnKillActionPerformed

    private void btnNetUpdateActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnNetUpdateActionPerformed
        btnNetUpdate.setEnabled(false);
        
        // Send Kill timer to old IP for security
        for(int i = 0; i < 10; i++)
            txUDP("HOST_998");
        postMessage("\nUDP HOST_998 Broadcasted To: " + TARGET_IP + ":" + UDP_PORT,UDP_TYPE);
        postMessage("HOST_998: Emergency Kill Timer",UDP_TYPE);
        postMessage("To prevent runaway-coptor scenario, the device at this\n"
                + "address will be killed in 5 seconds unless a new command\n"
                + "is recieved within said 5 seconds.\n",UDP_TYPE);
        
        resetControls();
        bisNew = true;
        imgCopter.setIcon(new javax.swing.ImageIcon(getClass().getResource("/Images/quadcopter.jpg")));
        
        // Update the network values
        UDP_PORT = Integer.parseInt(txtPort.getText());
        TARGET_IP = txtNetwork.getText();
        postMessage("UDP Port Updated: " + UDP_PORT,GENERIC_TYPE);
        postMessage("Target IP Address Updated: " + TARGET_IP,GENERIC_TYPE);
        
    }//GEN-LAST:event_btnNetUpdateActionPerformed

    private void txtPortKeyPressed(java.awt.event.KeyEvent evt) {//GEN-FIRST:event_txtPortKeyPressed
        btnNetUpdate.setEnabled(true);
    }//GEN-LAST:event_txtPortKeyPressed

    private void txtNetworkKeyPressed(java.awt.event.KeyEvent evt) {//GEN-FIRST:event_txtNetworkKeyPressed
        btnNetUpdate.setEnabled(true);
    }//GEN-LAST:event_txtNetworkKeyPressed

    
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
        // Set the look and feel
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (Exception ex) {} 

        // Create and display the form 
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new HostGUI().setVisible(true);
            }
        });
    }
    
    private void formWindowClosing(java.awt.event.WindowEvent evt) {                                   
        isExiting = true;
    } 
    
    SwingWorker<Boolean, Integer> animationManager = new SwingWorker<Boolean, Integer>() 
    {           
        int maxHeight = 470;
        int hoverHeight = 350;
        boolean init = true;
        
        @Override
        protected Boolean doInBackground() throws Exception 
        {
            publish(0);
            while(!isExiting)
            {
                if(init)
                {
                    publish(0);
                }
                else if(bisKilled)
                {
                    publish(7);
                }
                else if(bisNew)
                {
                    publish(8);
                }
                else if(bTakeOff)
                {
                    
                    if(hoverHeight < height)
                    {
                        Thread.sleep(40);
                        publish(1);
                        Thread.sleep(50);
                        publish(5);
                        Thread.sleep(40);
                        publish(2);
                        Thread.sleep(50);
                        publish(5);
                        Thread.sleep(40);
                        publish(3);
                        Thread.sleep(50);
                        publish(5);
                        Thread.sleep(40);
                        publish(4);
                        Thread.sleep(50);
                        publish(5);
                    }
                    else
                    {
                        Thread.sleep(40);
                        publish(1);
                        Thread.sleep(40);
                        publish(2);
                        Thread.sleep(40);
                        publish(3);
                        Thread.sleep(40);
                        publish(4);
                    }
                }
                else if(height + 5 < maxHeight)
                {
                    Thread.sleep(40);
                    publish(1);
                    Thread.sleep(50);
                    publish(6);
                    Thread.sleep(40);
                    publish(2);
                    Thread.sleep(50);
                    publish(6);
                    Thread.sleep(40);
                    publish(3);
                    Thread.sleep(50);
                    publish(6);
                    Thread.sleep(40);
                    publish(4);
                    Thread.sleep(50);
                    publish(6);
                }
                else
                {
                    Thread.sleep(5);
                }
            }
            return true;
        }

        @Override
        // Can safely update the GUI from this method.
        protected void process(List<Integer> chunks) {
         
            Integer command = chunks.get(chunks.size()-1);
            if(command == 0)
            {
                imgCopter.setVisible(true);
                imgCopter.setIcon(new javax.swing.ImageIcon(getClass().getResource("/Images/quadcopter.jpg")));
                imgCopter.setLocation(10, height);
                init = false;
            }
            else if(command == 1)
            {
                imgCopter.setIcon(new javax.swing.ImageIcon(getClass().getResource("/Images/quadcopter.jpg")));
            }
            else if(command == 2)
            {
               imgCopter.setIcon(new javax.swing.ImageIcon(getClass().getResource("/Images/quadcopter2.jpg")));
            }
            else if(command == 3)
            {
               imgCopter.setIcon(new javax.swing.ImageIcon(getClass().getResource("/Images/quadcopter3.jpg")));
            }
            else if(command == 4)
            {
               imgCopter.setIcon(new javax.swing.ImageIcon(getClass().getResource("/Images/quadcopter4.jpg")));
            }
            else if(command == 5)
            {
               height -= 5;
               imgCopter.setLocation(10, height);
            }
            else if(command == 6)
            {
                height +=5;
               imgCopter.setLocation(10, height);
            }
            else if(command == 7)
            {
                height = 470;
               imgCopter.setLocation(10, height);
               imgCopter.setIcon(new javax.swing.ImageIcon(getClass().getResource("/Images/quadcopter5.jpg")));
            }
            else if(command == 8)
            {
                height = 470;
               imgCopter.setLocation(10, height);
               imgCopter.setIcon(new javax.swing.ImageIcon(getClass().getResource("/Images/quadcopter.jpg")));
            }
        }
    };
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JPanel animationPanel;
    private javax.swing.JButton btnAdvanced;
    private javax.swing.JButton btnBackward;
    private javax.swing.JButton btnForward;
    private javax.swing.JButton btnKill;
    private javax.swing.JButton btnLeft;
    private javax.swing.JButton btnNetUpdate;
    private javax.swing.JButton btnRight;
    private javax.swing.JLabel imgCopter;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel10;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JLabel jLabel6;
    private javax.swing.JLabel jLabel7;
    private javax.swing.JLabel jLabel8;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JPanel jPanel3;
    private javax.swing.JScrollPane jScrollPane2;
    private javax.swing.JSeparator jSeparator1;
    private javax.swing.JSeparator jSeparator2;
    private javax.swing.JSlider sldHeight;
    private javax.swing.JToggleButton tglMotors;
    private javax.swing.JTextField txtHeight;
    private javax.swing.JTextField txtMot1;
    private javax.swing.JTextField txtMot2;
    private javax.swing.JTextField txtMot3;
    private javax.swing.JTextField txtMot4;
    private javax.swing.JTextField txtNetwork;
    private javax.swing.JTextField txtPort;
    private javax.swing.JTextPane txtUDPStat;
    // End of variables declaration//GEN-END:variables
}
