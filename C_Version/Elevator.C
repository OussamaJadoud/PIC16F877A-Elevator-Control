void interrupt(){   // routine d'interruption
     if(INTCON.INTF==1){ // interruption sur RB0
                         PORTD.F0=1;
                         PORTD.F1=1;      // arreter les moteurs
                        do{ 
                            PORTA.F2 =1;
                            delay_ms(1000);
                            PORTA.F2=0;
                            delay_ms(1000);
                           }while(PORTA.F3 ==0);  // clignoter la LED d'urgence tant que le bouton de reprise de fonctionnement est non pressé
                           
                        while(PORTB.F4==0 && PORTB.F5==0){
                            PORTD.F1=0;
                                           }; //  faire Descendre la ascenseur jusqu a le niveau le plus proche
                        PORTD.F1 = 1;
                        if(PORTB.F4 ==1 ) PORTC = 0b00000001;
                        if(PORTB.F5 ==1 ) PORTC = 0b00000010;
     INTCON.INTF=0 ; // Remettre le flag à zero pour que la prochaine interruption soit detectable 
     }

     
     
     if(INTCON.TMR0IF==1){    // Interruption sur TIMER0
                              PORTD.F0=1;
                              PORTD.F1=1;      // arreter les moteurs
                               do{
                                  PORTA.F0 =1;
                                  delay_ms(1000);
                                  PORTA.F0=0;
                                  delay_ms(1000);
                             }while(PORTA.F3 ==0);  // clignoter la LED de diagnostique tant que le bouton de reprise de fonctionnement est non pressé
                             PORTA.F0=0;
     TMR0 = 253 ; // reinitialiser le TMR0 pour avoir le meme comptage avant chaque interruption ( pour 253, 3 utilisations avant overflow )   
     INTCON.TMR0IF=0 ; // Remettre le flag à zero pour que la prochaine interruption soit detectable
     }
     }
     
     
void main(){

TRISB=0XFF;   // PORTB en entrée ( boutons et capteurs )
TRISD = 0;    // PORTD en sortie ( KM1 et KM2 )
PORTD = 0b00000011; // initialisation du PORTD ( Moteurs arretes ; Relais activé à l'état basse 0 logique )
TRISC = 0b11110000; // SEGEMENT 7 sur les 4 premiers bits = sorties - Boutons sur RC4--RC7 = entrées
ADCON1= 0x07;     // Tous les Pins AN en Digital
ADCON0 = 0;
TRISA =0b00011000;  // en sortie sauf pour RA3 BOUTON De reprise & RA4 horloge exterieure du TMR0
INTCON =0b10110000; // Autorisation des interruptions GIE ==1 - TMR0IE ==1 - INTIE ==1
OPTION_REG = 0b01101000;   // RB0 et RA4 sur front montant avec RA4 sans prescalaire ( prescalaire donné au WDT )
TMR0 = 253;    // initialisation du TMR0 apres 3 utilisations (par exemple) on va appeler du diagnostique

while(1){  // loop infinie -- partie operative

if(PORTB.F4==1){             // ascenseur à l'étage 1

                PORTC = 0b00000001;              // affichage de numero d'etage sur SEG7
                if(PORTB.F1 ==1 || PORTC.F7 ==1);          // rien faire si l etage 1 est appelé
                if(PORTB.F2 ==1 || PORTC.F6 ==1 || PORTC.F5 ==1){
                            do {
                            PORTD.F0=0;
                            }while(PORTB.F5==0);        // faire monter l'ascenseur jusqu'à  l'etage 2
                            PORTD.F0=1;
                                               }
                if(PORTB.F3 ==1 || PORTC.F4 ==1){
                            while(PORTB.F6==0){
                            PORTD.F0=0;
                                        }             // faire monter l'ascenseur jusqu'à  l'etage 3
                            PORTD.F0=1;}}
                                        

if(PORTB.F5==1){            // ascenseur à l'étage 2
                PORTC = 0b00000010;            // affichage de numero d'etage sur SEG7
                if(PORTB.F2 ==1 || PORTC.F6 ==1 || PORTC.F5 ==1);     // rien faire si l etage 2 est appelé
                if(PORTB.F1 ==1 || PORTC.F7 ==1){
                            while(PORTB.F4==0){
                            PORTD.F1=0;
                                               }  // faire descendre l'ascenseur jusqu'à  l'etage 1
                            PORTD.F1=1;
                                               }
                if(PORTB.F3 ==1 || PORTC.F4 ==1){
                            while(PORTB.F6==0){
                            PORTD.F0=0;
                                        }      // faire monter l'ascenseur jusqu'à  l'etage 3
                            PORTD.F0=1;
                            } }


if(PORTB.F6==1){          // ascenseur à l'étage 3
                PORTC = 0b00000011;         // affichage de numero d'etage sur SEG7
                if(PORTB.F3 ==1 || PORTC.F4 ==1);           // rien faire si l etage 3 est appelé
                if(PORTB.F1 ==1 || PORTC.F7 ==1){
                            while(PORTB.F4==0){
                            PORTD.F1=0;
                                               }            // faire descendre l'ascenseur jusqu'à  l'etage 1
                            PORTD.F1=1;
                                               }
                if(PORTB.F2 ==1 || PORTC.F6 ==1 || PORTC.F5 ==1){
                            while(PORTB.F5==0){
                            PORTD.F1=0;
                                        }                  // faire descendre l'ascenseur jusqu'à  l'etage 2
                            PORTD.F1=1; }  }

};
}
