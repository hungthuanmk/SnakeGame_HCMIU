#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

/**
    Play .wav sound file.
    @param dir directory of file name
    @param repeat repeated playing
*/
void playSound(char* dir, bool repeat = false);

/**
    Stop all playing sound.
*/
void stopSound();

#endif // SOUND_H_INCLUDED
