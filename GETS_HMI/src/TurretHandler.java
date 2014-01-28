/* ==================================================================================
 * File: TurretHandler.java
 * System: EOH HMI
 * Team: MUSCA
 * Course Info: CSE 423 Spring 2014
 * 
 * Author(s): William Murray
 * Email: wmurray919@gmail.com
 * ==================================================================================
 * Description: Handler class for the turret; Handles turret targeting and firing
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
 //== TODO: ==========================================================================>
 // [1] EVERYTHING :(
 //== END TODO: ======================================================================>

public class TurretHandler 
{
    // Define Instance Variables
    private boolean targeted;
    private int targetIndex;
    
    
    public TurretHandler()
    {
        targeted = false;
        targetIndex = -1;
    }
    
    void Target(int selectedIndex) 
    {
        // Set Targeted to true
        targeted = true;
        
        // Store the targetIndex
        targetIndex = selectedIndex;
        
        // Target the index
        
    }

    void fire() 
    {
        // After firing, retargeting is needed
        targeted = false;
        
        
    }
    
    boolean isTargeted() 
    {
        return targeted;
    }
    
    int getTargetIndex() 
    {
        return targetIndex;
    }
    
}
