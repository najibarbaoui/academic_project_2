/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ca.polymtl.inf2990.configuration;

import java.util.Observable;

/**
 *
 * @author mapoug
 */
public class configuration extends Observable {
    
    private char[] touches ={'w','a','s','d',' ','8','4','5','6','0'};
    private int dureePartie = 60;
    private int nbVieSspatiales=10;
    private boolean mDebug =false;
    private boolean aAsteroid= false;
    private boolean changMode=false;
    private boolean eclairage=false;
    private boolean identCible=false;
    private boolean cDepart=false;
    private boolean zPass=false;
    private boolean aPortails=false;
    
    public void setConfiguration(configuration c){
      for(int i=0; i<10;i++)
      {
        touches[i] = c.gettouches()[i];
      }
      
     dureePartie = c.getDureePartie();
     nbVieSspatiales= c.getnbVieSspatiales();
     mDebug = c.getmDebug();
     aAsteroid= c.getaAsteroid();
     changMode= c.getchangMode();
     eclairage=c.geteclairage();
     identCible=c.getidentCible();
     cDepart=c.getcDepart();
    zPass=c.getzPass();
     aPortails=c.getaPortails();
    
    }
    public void setnbVieSspatiales(int nb){
    nbVieSspatiales= nb;
    }
    public int getnbVieSspatiales(){
    return nbVieSspatiales;
    }
    public void setDureePartie(int d){
        dureePartie = d;
    }
    public int getDureePartie(){
    return dureePartie;}
   
    public void setmDebug(boolean b){
        mDebug = b;
    }
    public void setaAsteroid(boolean b){
        aAsteroid = b;
    }
    public void setchangMode(boolean b){
        changMode = b;
    }
    public void seteclairage(boolean b){
        eclairage = b;
    }
    public void setidentCible(boolean b){
        identCible = b;
    }
    public void setcDepart(boolean b){
        cDepart = b;
    }
    public void setzPass(boolean b){
    zPass = b;
    }
    public void setaPortails(boolean b){
    aPortails = b;
    }
   public boolean getmDebug(){
   return mDebug;
   }
   public boolean getaAsteroid(){
   return aAsteroid;
   }
   public boolean getchangMode(){
   return changMode;
   }
   public boolean geteclairage(){
   return eclairage;
   }
   public boolean getidentCible(){
   return identCible;
   }
   public boolean getcDepart(){
   return cDepart;
   }
   public boolean getzPass(){
   return zPass;
   }
   public boolean getaPortails(){
   return aPortails;
   }
    public boolean dejaUtiliser(char c){
        for(int i=0; i<10;i++){
            if(touches[i]==c)
                return true;
        }
        return false;
    }
 
    public void changeValue(char oldControle, char newControle){
       newControle= Character.toLowerCase(newControle);
        
        for(int i = 0; i<10;i++){
        if(touches[i]==oldControle){
            touches[i]= newControle;
        }
        }
        
        setChanged();
        notifyObservers();
            
    }
    public void reinitialiserJoueur1(){
        touches[0]='w';
        touches[1]='a';
        touches[2]='s';
        touches[3]='d';
        touches[4]=' ';
        setChanged();
    notifyObservers();
    
    }
    public void reinitialiserJoueur2(){
    touches[5]= '8';
    touches[6]='4';
    touches[7]='5';
    touches[8]='6';
    touches[9]='0';
        
          setChanged();
    notifyObservers();
  
    }
    public char[] gettouches(){
    return touches;
    }
}

