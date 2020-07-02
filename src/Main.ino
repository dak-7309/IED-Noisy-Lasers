const int velocity=100;

// Chord mapping
int C_maj[]={36,40,43};
int C_min[]={36,39,43};
int C_sharp_maj[]={37,41,44};
int C_sharp_min[]={37,40,44};
int D_maj[]={38,42,45};
int D_min[]={38,41,45};
int D_sharp_maj[]={39,43,46};
int D_sharp_min[]={39,42,46};
int E_maj[] ={40,44,47};
int E_min[]={40,43,47};
int F_maj[]={41,45,36};
int F_min[]={41,44,36};
int F_sharp_maj[]={42,46,37};
int F_sharp_min[]={42,45,37};
int G_maj[]={43,47,38};
int G_min[]={43,46,38};
int G_sharp_maj[]={44,36,39};
int G_sharp_min[]={44,47,39};
int A_maj[]={45,37,40};
int A_min[]={45,36,40};
int A_sharp_maj[]={46,38,41};
int A_sharp_min[]={46,37,41};
int B_maj[]={47,39,42};
int B_min[]={47,38,42};

// For percussion instrument
int noteon_per=153;
int noteoff_per=137;
int program_change_per=201;
int instrument_per=10;
int note_map_per[]={50,55,60};

//For other instruments
int noteon_pi=144;
int noteoff_pi=128;
int program_change_pi=192;
int instrument_pi_list[]={1,26};
int no_ins=2;
int instrument_pi_index=0;
int no_chord_map=3;
int chord_map_index=0;
int chord_map_pi[3][4]={{A_sharp_min,C_min,E_maj,G_sharp_maj},{E_maj,B_min,D_min,F_sharp_maj},{E_min,C_maj,G_maj,D_maj}};







// Threshold value for laser detection
int light_value=300;

// Set intitial status of lasers 0 for sound off and 1 for sound on
int status_pi[]={0,0,0,0};
int status_per[]={0,0,0,0};
int status_change_map=0;
int status_change_ins=0;

//Set timer for each laser
unsigned long timer_per[]={0,0,0};
unsigned long timer_pi[]={0,0,0,0};

// Set the laser being processed: 0,1,2,3 pi chords ,, 4 for chords change ,, 5 instrument change ,, 6,7,8 per_notes
int laser=1;


void setup() {
  // Set baud rate
  Serial.begin(9600);
}

void loop() {
  // Set instrument
  send_midi_signal(program_change_per,instrument_per);
  send_midi_signal(program_change_pi,instrument_pi_list[instrument_pi_index]);
  if(laser<4)
  {
    if(ldr_stat(laser)==1)
    {
      if(status_pi[laser]==0)
      {
        status_pi[laser]=1;
        start_chord(chord_map_pi[chord_map_index][laser],noteon_pi,velocity);      
      }
    }
    else
    {
      if(status_pi[laser]==1)
      {
        status_pi[laser]=0;
        stop_chord(chord_map_pi[chord_map_index][laser],noteoff_pi,velocity);
      }
    }
  }
  else if(laser>5)
  {
    if(ldr_stat(laser)==1)
    {
      if(status_per[laser-6]==0)
      {
        status_per[laser-6]=1;
        send_midi_signal(noteon_per,note_map_per[laser-6],velocity);
        delay(20);      
      }
    }
    else
    {
      if(status_per[laser-6]==1)
      {
        status_per[laser-6]=0;
        send_midi_signal(noteoff_per,note_map_per[laser-6],velocity);
        delay(20);
      }
    }
  }
  else if(laser==5)
  {
    if(ldr_stat(laser)==1)
    {
      if(status_change_ins==0)
      {
        instrument_pi_index=(instrument_pi_index+1)%no_ins;
        status_change_ins=1;   
      }
    }
    else
    {
      status_change_ins=0;
    }    
  }
  else if(laser==4)
  {
    if(ldr_stat(laser)==1)
    {
      if(status_change_map==0)
      {
        for(int i=0;i<4;i++)
        {
          if(status_pi[i]==1)
          {
            status_pi[i]=0;
            stop_chord(chord_map_pi[chord_map_index][i],noteon_pi,velocity);
          }
        }
        chord_map_index=(chord_map_index+1)%no_chord_map;
        status_change_map=1;
      }
    }
    else
    {
      status_change_map=0;
    }
  }
  laser=(laser+1)%9;
  delay(20);  
}
 // Get the status of the ldr 0 if beam intact else 1
int ldr_stat(int ldr)
{
  if(analogRead(54+ldr)>light_value)
  {
    return 0;
  }
  return 1;   
}

void send_midi_signal(int command,int note,int velocity)
{
  Serial.write(command);
  Serial.write(note);
  Serial.write(velocity);
}
void send_midi_signal(int command,int ins)
{
  Serial.write(command);
  Serial.write(ins);
}
void start_chord(int chord[],int noteON,int velocity)
{
  // Start each note of the chord
  for(int i=0;i<3;i++)
  {
    send_midi_signal(noteON,chord[i],velocity);
  }
  delay(20);
}
void stop_chord(int chord[],int noteOFF,int velocity)
{
  // Stop each note of the chord
  for(int i=0;i<3;i++)
  {
    send_midi_signal(noteOFF,chord[i],velocity);
  }
  delay(20);
}
