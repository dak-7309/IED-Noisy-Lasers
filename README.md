# LaserHarp
A musical harp made of lasers where sound is produced when you run your hand through the lasers. It is an interactive and captivating way of playing music. Each different laser beam is mapped to different chords so that even beginners can play complex sounds. Further, the harp can also play sounds of a percussion instrument and hence can imitate a wide variety of instruments. Internally the harp uses an Arduino that is attached to multiple LDRs. Each laser beam is focused on one particular LDR. Whenever the path of a laser is broken, the corresponding LDR notes the change in the light intensity and hence the Arduino sends the corresponding MIDI signal to play the required sound.

## Prerequisites
1. **Arduino Mega**
2. **LDRs**
3. **Lasers**
4. **MIDI Controller**

## Getting Started
The source code provided is for the configuration of 8 lasers and 8 LDRs attached to an Arduino Mega. You can edit the source code to meet your needs.
### Setup
1. Attach all the lasers, LDRs, Arduino on a frame
2. Focus all the lasers on the corresponding LDR and set the light threshold in the code
3. Upload the code on the Arduino
4. Connect the arduino to a MIDI Controller that will play the required sound. By default the code is set to write on the         Serial communication line.
5. Power all the components and Play

## Creators
1. Ayaan Kakkar
2. Shashwat Aggarwal
3. Samik Prakash
4. Daksh Thapar

## Website
https://samikprakash.wixsite.com/noisyboiz/
