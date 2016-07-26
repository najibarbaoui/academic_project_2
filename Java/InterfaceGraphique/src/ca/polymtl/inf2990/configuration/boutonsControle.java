/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ca.polymtl.inf2990.configuration;
import javax.swing.JButton;
/**
 *
 * @author mapoug
 */
public class boutonsControle {
    boutonsControle(){
    
    }
    public void setLabel(JButton j, String s ){
    if(s.compareTo(" ")== 0){
        s= "Espace";
    }
        j.setText(s);
    
    }
    public char getSetLabel(JButton b){
        char old;
        if(b.getText().compareTo("Espace")== 0)
        {
            old = ' ';
        }
    else{
      old= b.getText().toCharArray()[0];       
        }
    return old;
    }
    private String selected;
}
