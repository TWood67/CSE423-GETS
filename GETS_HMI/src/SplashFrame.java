/* ==================================================================================
 * File: SplashFrame.java
 * System: HMI
 * Team: MUSCA
 * Course Info: CSE 423 Spring 2014
 * 
 * Author(s): William Murray
 * Email: wmurray919@gmail.com
 * ==================================================================================
 * Description: Splash screen for the GETS HMI * 
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

import java.awt.Graphics;  
import java.awt.Image;  
import java.awt.Toolkit;  
import javax.imageio.ImageIO;
import javax.swing.JPanel;  

public class SplashFrame extends javax.swing.JFrame 
{
    
    // Instantiate Components
    private javax.swing.JLabel btnLaunch;
    private javax.swing.JLabel lblStatus;
    private javax.swing.JPanel splashBack;
    private javax.swing.JProgressBar pbStatus;

    //===============================================================================>
    // Name: SplashFrame
    // 
    // Input: NONE
    //
    // Output: NONE
    //
    // Description: Default Constructor
    //===============================================================================>
    public SplashFrame() 
    {      
        // Set the Application's Icon:
        try{
        setIconImage(ImageIO.read(getClass().getClassLoader().getResource("Images/Icon.png")));
        } catch(Exception e) {}
        
        //Set the Splash Screen location to the center of the screen
        Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
        this.setLocation((dim.width/2-this.getSize().width/2) - 300, (dim.height/2-this.getSize().height/2) - 106);

        // Remove Frame Decorations
        setUndecorated(true);
        initComponents();
        
        // Disable the Launch Button
        btnLaunch.setVisible(false);

        // Perform Necessary Allocations and Update Status Bar
        pbStatus.setValue(25);
        
        pbStatus.setValue(50);
        /* Insert Allocations Here */
        
        // Loading Complete Show Launch Button
        pbStatus.setValue(100);
        btnLaunch.setVisible(true); 
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
        splashBack = 
        new JPanel() {  
            public void paintComponent(Graphics g) {  
                Image img = Toolkit.getDefaultToolkit().getImage(  
                    SplashFrame.class.getResource("/Images/SplashFinal.png"));  
                g.drawImage(img, 0, 0, this.getWidth(), this.getHeight(), this);  
            }  
        };  
        
        pbStatus = new javax.swing.JProgressBar();
        lblStatus = new javax.swing.JLabel();
        btnLaunch = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setMaximumSize(new java.awt.Dimension(600, 211));
        setPreferredSize(new java.awt.Dimension(600, 211));
        setResizable(false);

        pbStatus.setBackground(new java.awt.Color(153, 153, 153));
        pbStatus.setForeground(new java.awt.Color(255, 102, 0));
        pbStatus.setValue(25);

        lblStatus.setFont(new java.awt.Font("Franklin Gothic Medium", 0, 11)); // NOI18N
        lblStatus.setForeground(new java.awt.Color(255, 255, 255));
        lblStatus.setText("Release 1.2 EOH Edition");
        lblStatus.setAlignmentY(0.3F);

        btnLaunch.setIcon(new javax.swing.ImageIcon(getClass().getResource("/Images/LaunchActive.png"))); // NOI18N
        btnLaunch.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseExited(java.awt.event.MouseEvent evt) {
                btnLaunchMouseExited(evt);
            }
            public void mouseEntered(java.awt.event.MouseEvent evt) {
                btnLaunchMouseEntered(evt);
            }
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                btnLaunchMouseClicked(evt);
            }
        });

        javax.swing.GroupLayout splashBackLayout = new javax.swing.GroupLayout(splashBack);
        splashBack.setLayout(splashBackLayout);
        splashBackLayout.setHorizontalGroup(
            splashBackLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(splashBackLayout.createSequentialGroup()
                .addGap(181, 181, 181)
                .addGroup(splashBackLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(splashBackLayout.createSequentialGroup()
                        .addComponent(pbStatus, javax.swing.GroupLayout.PREFERRED_SIZE, 196, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addContainerGap(223, Short.MAX_VALUE))
                    .addGroup(splashBackLayout.createSequentialGroup()
                        .addComponent(lblStatus)
                        .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))))
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, splashBackLayout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(btnLaunch)
                .addGap(22, 22, 22))
        );
        splashBackLayout.setVerticalGroup(
            splashBackLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, splashBackLayout.createSequentialGroup()
                .addContainerGap(130, Short.MAX_VALUE)
                .addComponent(btnLaunch)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(lblStatus)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(pbStatus, javax.swing.GroupLayout.PREFERRED_SIZE, 10, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18))
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(splashBack, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(splashBack, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );

        pack();
    }

    
    //===============================================================================>
    // Name: btnLaunchMouseEntered
    // 
    // Input: evt<MouseEvent> = pointer to mouse event
    //
    // Output: NONE
    //
    // Description: Changes the Launch Button's appearance on mouseover
    //===============================================================================>
    private void btnLaunchMouseEntered(java.awt.event.MouseEvent evt) 
    {
        btnLaunch.setIcon(new javax.swing.ImageIcon(getClass().getResource("/Images/LaunchOver.png")));
    }

    //===============================================================================>
    // Name: btnLaunchMouseExited
    // 
    // Input: evt<MouseEvent> = pointer to mouse event
    //
    // Output: NONE
    //
    // Description: Changes the Launch Button's appearance on mouse exit
    //===============================================================================>
    private void btnLaunchMouseExited(java.awt.event.MouseEvent evt) 
    {
        btnLaunch.setIcon(new javax.swing.ImageIcon(getClass().getResource("/Images/LaunchActive.png")));
    }

    //===============================================================================>
    // Name: btnLaunchMouseClicked
    // 
    // Input: evt<MouseEvent> = pointer to mouse event
    //
    // Output: NONE
    //
    // Description: Closes the splash screen and opens program
    //===============================================================================>
    private void btnLaunchMouseClicked(java.awt.event.MouseEvent evt) 
    {
        //this.dispatchEvent(new WindowEvent(this, WindowEvent.WINDOW_CLOSING));
        ParentFrameEOH mainFrame = new ParentFrameEOH();
        mainFrame.setVisible(true);
        this.setVisible(false);
        
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
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(SplashFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(SplashFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(SplashFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(SplashFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        
        // Create and display the form 
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new SplashFrame().setVisible(true);
            }
        });
    }
}
