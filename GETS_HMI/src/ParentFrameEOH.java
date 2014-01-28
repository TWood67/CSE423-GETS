
/* ==================================================================================
 * File: ParentFrameEOH.java
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
 * || Will M || 1/27/14 || Created File                          ||
 * ----------------------------------------------------------------
 *
 * ==================================================================================*/

import java.awt.Dimension;
import java.awt.Toolkit;
import javax.imageio.ImageIO;
import javax.swing.JOptionPane;

public class ParentFrameEOH extends javax.swing.JFrame 
{

    // Instantiate Components
    private java.awt.Button btnFire;
    private java.awt.Button btnTarget;
    private java.awt.Button button9;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JLabel jLabel6;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel10;
    private javax.swing.JPanel jPanel11;
    private javax.swing.JPanel jPanel9;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JLabel lblInstruct;
    private javax.swing.JList lstSelections;
    private javax.swing.JProgressBar prgTemperature;
    private javax.swing.JSlider sldAltitude;
    private javax.swing.JToggleButton tgbEngines;
    private javax.swing.JTextField txtTemp;
    
    public TurretHandler turMan;
    public ThermoHandler thurmoMan;
    public CoptorHandler copMan;
    
    //===============================================================================>
    // Name: ParentFrameEOH
    // 
    // Input: NONE
    //
    // Output: NONE
    //
    // Description: Default Constructor
    //===============================================================================>
    public ParentFrameEOH() 
    {        
        // Set the frame location to the center of the screen
        Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
        this.setLocation((dim.width/2-this.getSize().width/2) - 390, (dim.height/2-this.getSize().height/2) - 150);
        
        // Initialize Components
        initComponents();
        
        turMan = new TurretHandler();
        thurmoMan = new ThermoHandler();
        copMan = new CoptorHandler();
        
        // Set the Application's Icon
        try{
        setIconImage(ImageIO.read(getClass().getClassLoader().getResource("Images/Icon.png")));
        } catch(Exception e) {}
        
        // Set engine controls to disabled by default
        sldAltitude.setEnabled(false);
    }

    //===============================================================================>
    // Name: initComponents
    // 
    // Input: NONE
    //
    // Output: NONE
    //
    // Description: Initializes Visable Components to default values
    //===============================================================================>
    @SuppressWarnings("unchecked")
    private void initComponents()
    {

        button9 = new java.awt.Button();
        jPanel1 = new javax.swing.JPanel();
        jPanel10 = new javax.swing.JPanel();
        sldAltitude = new javax.swing.JSlider();
        tgbEngines = new javax.swing.JToggleButton();
        jPanel9 = new javax.swing.JPanel();
        jLabel1 = new javax.swing.JLabel();
        lblInstruct = new javax.swing.JLabel();
        jPanel11 = new javax.swing.JPanel();
        jScrollPane1 = new javax.swing.JScrollPane();
        lstSelections = new javax.swing.JList();
        btnTarget = new java.awt.Button();
        btnFire = new java.awt.Button();
        jLabel3 = new javax.swing.JLabel();
        jLabel4 = new javax.swing.JLabel();
        jLabel5 = new javax.swing.JLabel();
        jLabel6 = new javax.swing.JLabel();
        prgTemperature = new javax.swing.JProgressBar();
        txtTemp = new javax.swing.JTextField();

        button9.setLabel("button1");
        button9.setPreferredSize(new java.awt.Dimension(70, 70));

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("GETS System EOH Demo");
        setBackground(new java.awt.Color(102, 102, 102));
        setMaximumSize(new java.awt.Dimension(780, 400));
        setMinimumSize(new java.awt.Dimension(780, 100));
        setPreferredSize(new java.awt.Dimension(780, 300));
        setResizable(false);

        jPanel1.setBackground(new java.awt.Color(102, 102, 102));
        jPanel1.setPreferredSize(new java.awt.Dimension(780, 293));

        jPanel10.setBackground(new java.awt.Color(51, 51, 51));
        jPanel10.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));

        sldAltitude.setValue(0);
        sldAltitude.addMouseListener(new java.awt.event.MouseAdapter() {
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

        javax.swing.GroupLayout jPanel10Layout = new javax.swing.GroupLayout(jPanel10);
        jPanel10.setLayout(jPanel10Layout);
        jPanel10Layout.setHorizontalGroup(
            jPanel10Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel10Layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(sldAltitude, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(tgbEngines)
                .addContainerGap())
        );
        jPanel10Layout.setVerticalGroup(
            jPanel10Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel10Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel10Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(sldAltitude, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(tgbEngines, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        jPanel9.setBackground(new java.awt.Color(51, 51, 51));
        jPanel9.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
        jPanel9.setMaximumSize(new java.awt.Dimension(32767, 200));

        jLabel1.setFont(new java.awt.Font("Franklin Gothic Medium", 1, 12)); // NOI18N
        jLabel1.setForeground(new java.awt.Color(255, 255, 255));
        jLabel1.setText("Instructions:");

        lblInstruct.setFont(new java.awt.Font("Franklin Gothic Medium", 0, 11)); // NOI18N
        lblInstruct.setForeground(new java.awt.Color(255, 255, 255));
        lblInstruct.setText("<HTML> In the top panelof this application<BR> are controls that correspond with <BR> the turret and thermo-array <BR> components, whilst the lower pannel<BR> controls the quadcopter.<BR><BR>  The progressbar and like textbox<BR> display the data recieved from the<BR> thermo-array.  The higher the value<BR> the higher the recorded temperature<BR> A user can also select a \"hotspot\" <BR> from the selection list and fire the <BR> turret towards the selected local. <BR><BR>  The Slide-bar in the bottom panel <BR> controls the altitude of the copter.</HTML>");

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
                    .addComponent(lblInstruct, javax.swing.GroupLayout.DEFAULT_SIZE, 180, Short.MAX_VALUE))
                .addContainerGap())
        );
        jPanel9Layout.setVerticalGroup(
            jPanel9Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel9Layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jLabel1)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(lblInstruct, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        jPanel11.setBackground(new java.awt.Color(51, 51, 51));
        jPanel11.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));

        lstSelections.setBackground(new java.awt.Color(240, 240, 240));
        lstSelections.setModel(new javax.swing.AbstractListModel() {
            String[] strings = { "Selection One", "Selection Two", "Selection Three", "Selection Four", "Selection Five", "Selection Six" };
            public int getSize() { return strings.length; }
            public Object getElementAt(int i) { return strings[i]; }
        });
        lstSelections.setSelectionBackground(new java.awt.Color(255, 153, 0));
        lstSelections.setVisibleRowCount(6);
        jScrollPane1.setViewportView(lstSelections);

        btnTarget.setLabel("Target");
        btnTarget.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnTargetActionPerformed(evt);
            }
        });

        btnFire.setLabel("Fire Turret");
        btnFire.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnFireActionPerformed(evt);
            }
        });

        jLabel3.setFont(new java.awt.Font("Franklin Gothic Medium", 1, 12)); // NOI18N
        jLabel3.setForeground(new java.awt.Color(255, 255, 255));
        jLabel3.setText("Note:");

        jLabel4.setFont(new java.awt.Font("Franklin Gothic Medium", 0, 11)); // NOI18N
        jLabel4.setForeground(new java.awt.Color(255, 255, 255));
        jLabel4.setText("Before firing the turret, wait for the booth");

        jLabel5.setFont(new java.awt.Font("Franklin Gothic Medium", 0, 11)); // NOI18N
        jLabel5.setForeground(new java.awt.Color(255, 255, 255));
        jLabel5.setText("operator to reload the turret and indicate");

        jLabel6.setFont(new java.awt.Font("Franklin Gothic Medium", 0, 11)); // NOI18N
        jLabel6.setForeground(new java.awt.Color(255, 255, 255));
        jLabel6.setText("that it is indeed safe to fire.");

        prgTemperature.setBackground(new java.awt.Color(0, 0, 0));
        prgTemperature.setForeground(new java.awt.Color(255, 102, 0));
        prgTemperature.setValue(30);

        txtTemp.setEditable(false);
        txtTemp.setBackground(new java.awt.Color(240, 240, 240));
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
                .addGroup(jPanel11Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanel11Layout.createSequentialGroup()
                        .addComponent(prgTemperature, javax.swing.GroupLayout.PREFERRED_SIZE, 420, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(18, 18, 18)
                        .addComponent(txtTemp, javax.swing.GroupLayout.DEFAULT_SIZE, 88, Short.MAX_VALUE)
                        .addContainerGap())
                    .addGroup(jPanel11Layout.createSequentialGroup()
                        .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 194, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addGroup(jPanel11Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addGroup(jPanel11Layout.createSequentialGroup()
                                .addComponent(btnTarget, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(btnFire, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addGroup(jPanel11Layout.createSequentialGroup()
                                .addGroup(jPanel11Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(jLabel3)
                                    .addGroup(jPanel11Layout.createSequentialGroup()
                                        .addGap(10, 10, 10)
                                        .addGroup(jPanel11Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                                            .addComponent(jLabel5)
                                            .addComponent(jLabel4)
                                            .addComponent(jLabel6, javax.swing.GroupLayout.Alignment.LEADING))))
                                .addGap(12, 12, 12)))
                        .addGap(50, 50, 50))))
        );
        jPanel11Layout.setVerticalGroup(
            jPanel11Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel11Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel11Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(prgTemperature, javax.swing.GroupLayout.PREFERRED_SIZE, 30, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(txtTemp, javax.swing.GroupLayout.PREFERRED_SIZE, 30, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGroup(jPanel11Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanel11Layout.createSequentialGroup()
                        .addGap(18, 18, 18)
                        .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 139, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(jPanel11Layout.createSequentialGroup()
                        .addGap(31, 31, 31)
                        .addComponent(jLabel3)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jLabel4)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jLabel5)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jLabel6)
                        .addGap(13, 13, 13)
                        .addGroup(jPanel11Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                            .addComponent(btnFire, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(btnTarget, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))))
                .addContainerGap(15, Short.MAX_VALUE))
        );

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jPanel9, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jPanel11, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(jPanel10, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap())
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(jPanel9, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addGroup(jPanel1Layout.createSequentialGroup()
                        .addComponent(jPanel11, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jPanel10, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addContainerGap(14, Short.MAX_VALUE))
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jPanel1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jPanel1, javax.swing.GroupLayout.PREFERRED_SIZE, 300, javax.swing.GroupLayout.PREFERRED_SIZE)
        );

        pack();
    }

    //===============================================================================>
    // Name: btnTargetActionPerformed
    // 
    // Input: evt<ActionEvent> = pointer to btn event
    //
    // Output: NONE
    //
    // Description: Sends a message to the turret to target the selected Cup
    //===============================================================================>
    private void btnTargetActionPerformed(java.awt.event.ActionEvent evt) 
    {
        // Check to ensure that a target selection has been made
        if(lstSelections.getSelectedIndex() != -1)
        {
            // Send the selection index to the TurretHandler
            turMan.Target(lstSelections.getSelectedIndex());
        }
        else // Notify user to select a target
        {
            JOptionPane.showMessageDialog(null, "No target has been selected.\nSelect one from the list.");
        }
       
    }

    //===============================================================================>
    // Name: btnFireActionPerformed
    // 
    // Input: evt<ActionEvent> = pointer to btn event
    //
    // Output: NONE
    //
    // Description: Sends a message to the turret to fire at the selected Cup
    //===============================================================================>
    private void btnFireActionPerformed(java.awt.event.ActionEvent evt) 
    {
        // Determine if a target has been identified
        if(turMan.isTargeted())
        {
            // Get Selected Target
            int index = turMan.getTargetIndex();
            
            // Notify user of target
            JOptionPane.showMessageDialog(null, "Firing on Target: " + index);
            
            // Tell TurretHandler to fire
            turMan.fire();
        }
        else // Notify user of failure to identify target
        {
            JOptionPane.showMessageDialog(null, "The turret has not yet been\ntargeted. Select a target\nbefore firing.");
        }
    }

    //===============================================================================>
    // Name: tgbEnginesActionPerformed
    // 
    // Input: evt<ActionEvent> = pointer to btn event
    //
    // Output: NONE
    //
    // Description: Sends a message to toggle the engines on the quadcopter
    //===============================================================================>
    private void tgbEnginesActionPerformed(java.awt.event.ActionEvent evt) 
    {
        // Check to see if this action is to enable or disable
        if(tgbEngines.isSelected())
        {
            // Button is attempted to be set to Enabled
            // Send message to the ThermoHandler to disable data transmission
            thurmoMan.enableThermoPolling();
            
            // Disable the turret and thermo controls
            btnFire.setEnabled(false);
            btnTarget.setEnabled(false);
            lstSelections.setEnabled(false);
            prgTemperature.setEnabled(false);
            txtTemp.setEnabled(false);
            txtTemp.setText("---.--");
            
            // Enable Engine Controls
            sldAltitude.setEnabled(true);
            
            // Tell the coptor to start motor
            copMan.enableMotors();
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
                copMan.setAltitude(0);
            }
            
            // Enable the other controls
            btnFire.setEnabled(true);
            btnTarget.setEnabled(true);
            lstSelections.setEnabled(true);
            prgTemperature.setEnabled(true);
            txtTemp.setEnabled(true);
            
            // Disable Engine controls
            sldAltitude.setEnabled(false);
            
            // Tell the ThermoHandler to enable data Rx and Tx
            thurmoMan.disableThermoPolling();
            
            // Tell the coptor to stop motors
            copMan.disableMotors();
            
        }
    }

    //===============================================================================>
    // Name: sldAltitudeMouseReleased
    // 
    // Input: evt<MouseEvent> = pointer to mouse event
    //
    // Output: NONE
    //
    // Description: Sends a message to the quadcopter to modify motor output
    //===============================================================================>
    private void sldAltitudeMouseReleased(java.awt.event.MouseEvent evt) 
    {
        copMan.setAltitude(sldAltitude.getValue());
    }

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
    // Name: sldAltitudeMouseReleased
    // 
    // Input: value<int> = temperature data
    //
    // Output: NONE
    //
    // Description: Updates the thermo progress bar and textbox
    //===============================================================================>
    public void processThermoRedraw(int value) 
    {
        //== TODO: ==================================================================>
        // [1] Format output to textBox
        // [2] Determine reasonable min and max bounds on prog bar
        // [3] update the value in the progress bar
        //== END TODO: ==============================================================>
    }
    
}
