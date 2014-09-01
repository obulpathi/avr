/******************************************************************************
*
*   A song is defined by a table of notes. The first byte sets the tempo. A 
*   high byte will give a low tempo, and opposite. Each tone consists of two 
*   bytes. The first gives the length of the tone, the other gives the frequency. 
*   The frequencies for each tone are defined in the "sound.h". Timer0 controls 
*   the tempo and the length of each tone, while Timer1 with PWM gives the 
*   frequency. The second last byte is a "0" which indicates the end, and the
*   very last byte makes the song loop if it's "1", and not loop if it's "0".
*
******************************************************************************/

char TEXT_SONG1[]       = "Fur Elise";

int FurElise[] =   
       {
           3, 
           8,e2, 8,xd2, 8,e2, 8,xd2, 8,e2, 8,b1, 8,d2, 8,c2, 4,a1, 8,p, 
           8,c1, 8,e1, 8,a1, 4,b1, 8,p, 8,e1, 8,xg1, 8,b1, 4,c2, 8,p, 8,e1, 
           8,e2, 8,xd2, 8,e2, 8,xd2, 8,e2, 8,b1, 8,d2, 8,c2, 4,a1, 8,p, 8,c1, 
           8,e1, 8,a1, 4,b1, 8,p, 8,e1, 8,c2, 8,b1, 4,a1, 
           0, 1
       };


char TEXT_SONG2[]       = "Turkey march";

int Mozart[] = 
       {
           3, 
           16,xf1, 16,e1, 16,xd1, 16,e1, 4,g1, 16,a1, 16,g1, 16,xf1, 16,g1,
           4,b1, 16,c2, 16,b1, 16,xa1, 16,b1, 16,xf2, 16,e2, 16,xd2, 16,e2, 
           16,xf2, 16,e2, 16,xd2, 16,e2, 4,g2, 8,e2, 8,g2, 32,d2, 32,e2, 
           16,xf2, 8,e2, 8,d2, 8,e2, 32,d2, 32,e2, 16,xf2, 8,e2, 8,d2, 8,e2, 
           32,d2, 32,e2, 16,xf2, 8,e2, 8,d2, 8,xc2, 4,b1, 
           0, 1
       };

char TEXT_SONG3[]       = "Minuet";

int Minuet[] = 
       {
           2, 
           4,d2, 8,g1, 8,a1, 8,b1, 8,c2, 4,d2, 4,g1, 4,g1, 4,e2, 8,c2, 
           8,d2, 8,e2, 8,xf2, 4,g2, 4,g1, 4,g1, 4,c2, 8,d2, 8,c2, 8,b1, 
           8,a1, 4,b1, 8,c2, 8,b1, 8,a1, 8,g1, 4,xf1, 8,g1, 8,a1, 8,b1, 
           8,g1, 4,b1, 2,a1, 
           0, 1
       };


char TEXT_SONG4[]        = "Auld Lang Syne";

int AuldLangSyne[] = 
       {  
           3, 
           4,g2, 2,c3, 8,c3, 4,c3, 4,e3, 2,d3, 8,c3, 4,d3, 8,e3, 8,d3, 2,c3, 
           8,c3, 4,e3, 4,g3, 2,a3, 8,p, 4,a3, 2,g3, 8,e3, 4,e3, 4,c3, 2,d3, 
           8,c3, 4,d3, 8,e3, 8,d3, 2,c3, 8,a2, 4,a2, 4,g2, 2,c3, 4,p,
           0, 1
       };

char TEXT_SONG5[]      =   "Sirene1";

int Sirene1[] = 
       {
           0,
           32,400, 32,397, 32,394, 32,391, 32,388, 32,385, 32,382, 32,379,
           32,376, 32,373, 32,370, 32,367, 32,364, 32,361, 32,358, 32,355,
           32,352, 32,349, 32,346, 32,343, 32,340, 32,337, 32,334, 32,331, 
           32,328, 32,325, 32,322, 32,319, 32,316, 32,313, 32,310, 32,307, 
           32,304, 32,301, 32,298, 32,298, 32,301, 32,304, 32,307, 32,310, 
           32,313, 32,316, 32,319, 32,322, 32,325, 32,328, 32,331, 32,334, 
           32,337, 32,340, 32,343, 32,346, 32,349, 32,352, 32,355, 32,358, 
           32,361, 32,364, 32,367, 32,370, 32,373, 32,376, 32,379, 32,382, 
           32,385, 32,388, 32,391, 32,394, 32,397, 32,400,
           0, 1
       };

char TEXT_SONG6[]      =   "Sirene2";

int Sirene2[] = 
       {
           3, 
           4,c2, 4,g2, 
           0, 1
       };


char TEXT_SONG7[]      =   "Whistle";

int Whistle[] = 
       {
           0, 
           32,200, 32,195, 32,190, 32,185, 32,180, 32,175, 32,170, 32,165,  
           32,160, 32,155, 32,150, 32,145, 32,140, 32,135, 32,130, 32,125,              
           32,120, 32,115, 32,110, 32,105, 32,100, 8,p, 32,200, 32,195, 
           32,190, 32,185, 32,180, 32,175, 32,170, 32,165, 32,160, 32,155, 
           32,150, 32,145, 32,140, 32,135, 32,130, 32,125, 32,125, 32,130, 
           32,135, 32,140, 32,145, 32,150, 32,155, 32,160, 32,165, 32,170, 
           32,175, 32,180, 32,185, 32,190, 32,195, 32,200, 
           0, 0
       };



extern char gPlaying;      // global variable from "main.c"
static char Volume = 80;
static char Duration = 0;
static char Tone = 0;
static char Tempo;


/*****************************************************************************
*
*   Function name : Sound_Init
*
*   Returns :       None
*
*   Parameters :    None
*
*   Purpose :       Set up Timer1 with PWM
*
*****************************************************************************/
void Sound_Init(void)
{
   TCCR1A = (1<<COM1A1);// | (1<<COM1A0); // Set OC1A when upcounting, clear when downcounting
   TCCR1B = (1<<WGM13);        // Phase/Freq-correct PWM, top value = ICR1
   
   sbi(TCCR1B, CS10);             // start Timer1, prescaler(1)    
   
   OCR1AH = 0;     // Set a initial value in the OCR1A-register
   OCR1AL = Volume;     // This will adjust the volume on the buzzer, lower value => higher volume
   
   Timer0_RegisterCallbackFunction(Play_Tune);     // Timer/Counter0 keeps the right beat
}

/*****************************************************************************
*
*   Function name : Play_Tune
*
*   Returns :       None
*
*   Parameters :    None
*
*   Purpose :       Plays the song
*
*****************************************************************************/
void Play_Tune(void)
{
   int temp_hi;
   
   char loop;
   
   if(!Tone)
   {
       Duration = 0;   
       Tempo = *(pSong + 0);
       Tone = 1;   //Start the song from the beginning
   }
   
   if(!Tempo)
   {
       if(Duration)        // Check if the lenght of the tone has "expired"
       {   
           Duration--;
       }
       else if(*(pSong + Tone))    // If not the end of the song
       {
       
           Duration = ( DURATION_SEED / *(pSong + Tone) );  // store the duration
           
           Tone++;                     // point to the next tone in the Song-table        
               
           if( (*(pSong + Tone) == p) | (*(pSong + Tone) == P) ) // if pause
               cbi(TCCR1B, CS10);             // stop Timer1, prescaler(1)    
           else 
               sbi(TCCR1B, CS10);             // start Timer1, prescaler(1)  
               
           __disable_interrupt();
           
           temp_hi = *(pSong + Tone);      // read out the PWM-value

           temp_hi >>= 8;                  // move integer 8 bits to the rigth
               
           TCNT1H = 0;                     // reset TCNT1H/L
           TCNT1L = 0;
           
           ICR1H = temp_hi;                // load ICR1H/L
           ICR1L = *(pSong + Tone);        
           
           __enable_interrupt();
           
           Tone++;                     // point to the next tone in the Song-table
       }
       else    // the end of song
       {
           Tone++;         // point to the next tone in the Song-table        
           
           loop = *(pSong + Tone); // get the byte that tells if the song should loop or not
           
           if( loop )  
           {
               Tone = 1;
           }
           else        // if not looping the song
           {
               Tone = 0;
               gPlaying = FALSE;
               cbi(TCCR1B, 0);                     // stop Playing
               Timer0_RemoveCallbackFunction(Play_Tune);
               TCCR1A = 0;
               TCCR1B = 0;
               sbi(PORTB, 5);              // set OC1A high
           }
       }
       
       Tempo = *(pSong + 0);
   }
   else
       Tempo--;

}    
