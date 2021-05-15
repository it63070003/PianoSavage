#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>

//Help Mode()
int helpMode(){
    char c[2];
    printf(
"██╗  ██╗███████╗██╗     ██████╗ \n"
"██║  ██║██╔════╝██║     ██╔══██╗\n"
"███████║█████╗  ██║     ██████╔╝\n"
"██╔══██║██╔══╝  ██║     ██╔═══╝ \n"
"██║  ██║███████╗███████╗██║     \n"
"╚═╝  ╚═╝╚══════╝╚══════╝╚═╝     \n"
);
    printf("1.Play Mode\n"
           "Type in Note+Octave Time\n"
           "Ex.C#3 500  (note C#, octave 3, time 500ms)\n"
           "Note: C C#/Db D D#/Eb E F F#/Gb G G#/Ab A A#/Bb B\n"
           "Octave: 3 4 5\n"
           "Time: >= 0 (millisecond)\n"
           "\n\n2.Chords Mode\n"
           "Type in Chords\n"
           "Ex.C#m (C sharp minor)\n"
           "   Bb  (B flat major)\n"
           "Chords:C C#/Db D D#/Eb E F F#/Gb G G#/Ab A A#/Bb B\n"
           "Minors:m (add m to the last letter)\n"
           "\n\nPress '=' Go to Menu\t'-' Go to Exit\n");
    scanf("%s", &c);
    if(c[0] == '='){
        return 0;
    }
    else if(c[0] == '-'){
        return 1;
    }

}

//Play Mode
int playMode(){
    printf("██████╗ ██╗      █████╗ ██╗   ██╗\n"
           "██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝\n"
           "██████╔╝██║     ███████║ ╚████╔╝ \n"
           "██╔═══╝ ██║     ██╔══██║  ╚██╔╝  \n"
           "██║     ███████╗██║  ██║   ██║   \n"
           "╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   \n");
    char music[100000];
    int stop=0;
    int sharp=0;
    int state=0;
    int note=0;
    int time=0;
    int octave=0;
    char ram[50];
    char ram2[2];
    float freq[12][3] = {{130.8,261.6,523.3},{138.6,277.2,554.4},{146.8,293.7,587.3},{155.6,311.1,622.3},{164.8,329.6,659.3},{174.6,349.2,698.5},{185.0,370.0,740.0},{196.0,392.0,784.0},{207.7,415.3,830.6},{220.0,440.0,880.0},{233.1,466.2,932.3},{246.9,493.9,987.8}};
    strcpy(ram,"");
    strcpy(ram2,"");
    while(TRUE){
        printf("Enter Note:");
        scanf(" %[^\n]s",&music);
        for(int i=0;i<strlen(music)+1;i++){
            if(music[i] == '\0'){
                stop = 1;
            }
            if(music[i] == ' ' || music[i] == '\0'){
                //Sharp
                if(state != 1 && strlen(ram)>2){
                    sharp = 1;
                }
                else if(state != 1){
                    sharp = 0;
                }
                if(state == 0){
                    //note
                    if(ram[0] == 'C' && !sharp){
                        note = 0;
                    }
                    else if((ram[0] == 'C' && sharp) || (ram[0] == 'D' && ram[1] == 'b')){
                        note = 1;
                    }
                    else if(ram[0] == 'D' && !sharp){
                        note = 2;
                    }
                    else if((ram[0] == 'D' && sharp) || (ram[0] == 'E' && ram[1] == 'b')){
                        note = 3;
                    }
                    else if(ram[0] == 'E' && !sharp){
                        note = 4;
                    }
                    else if(ram[0] == 'F' && !sharp){
                        note = 5;
                    }
                    else if((ram[0] == 'F' && sharp) || (ram[0] == 'G' && ram[1] == 'b')){
                        note = 6;
                    }
                    else if(ram[0] == 'G' && !sharp){
                        note = 7;
                    }
                    else if((ram[0] == 'G' && sharp) || (ram[0] == 'A' && ram[1] == 'b')){
                        note = 8;
                    }
                    else if(ram[0] == 'A' && !sharp){
                        note = 9;
                    }
                    else if((ram[0] == 'A' && sharp) || (ram[0] == 'B' && ram[1] == 'b')){
                        note = 10;
                    }
                    else if(ram[0] == 'B' && !sharp){
                        note = 11;
                    }
                    else if(ram[0] == '-'){
                        return 1;
                    }
                    else if(ram[0] == '='){
                        return 0;
                    }
                    else{
                        printf("Error\n");
                        return 0;
                    }
                    //octave
                    ram2[0] = ram[strlen(ram)-1];
                    ram2[1] = '\0';
                    octave = atoi(ram2)-3;

                    strcpy(ram2,"");
                    state = abs(state-1);
                }
                else if(state == 1){
                    time = atoi(ram);
                    Beep(freq[note][octave],time);
                    state = abs(state-1);
                }
                strcpy(ram,"");
            }
            else{
                ram2[0] = music[i];
                ram2[1] = '\0';
                strcat(ram,ram2);
                strcpy(ram2,"");
            }
        }
        printf("Song Ended♪♫\n");
        printf("Press '=' Go to Menu\t'-' Go to Exit\n");
    }
     
}

//Chord Mode
int chordMode(){
    char chord[4];
    printf(" ██████╗██╗  ██╗ ██████╗ ██████╗ ██████╗ ███████╗\n"
           "██╔════╝██║  ██║██╔═══██╗██╔══██╗██╔══██╗██╔════╝\n"
           "██║     ███████║██║   ██║██████╔╝██║  ██║███████╗\n"
           "██║     ██╔══██║██║   ██║██╔══██╗██║  ██║╚════██║\n"
           "╚██████╗██║  ██║╚██████╔╝██║  ██║██████╔╝███████║\n"
           "╚═════╝╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═╝╚═════╝ ╚══════╝ \n");
    while (TRUE)
    {   
        printf("Press '=' Go to Menu\t'-' Go to Exit\n");
        printf("Chord:");
        scanf("%s",&chord);
        if(strcmp("=",chord) == 0){
            //Menu
            return 0;
        }
        else if(strcmp("-",chord) == 0){
            //Exit
            return 1;
        }
        else if(strcmp("C",chord) == 0){
            //Chord C
            printf(" ___________________________________________\n"
                   "|██|░|▓|░|█|░|██|▓▓|░|█|░|▓▓|██|░|█|░|█|░|██|\n"
                   "|██|░|▓|░|█|░|██|▓▓|░|█|░|▓▓|██|░|█|░|█|░|██|\n"
                   "|██|░|▓|░|█|░|██|▓▓|░|█|░|▓▓|██|░|█|░|█|░|██|\n"
                   "|██|░|▓|░|█|░|██|▓▓|░|█|░|▓▓|██|░|█|░|█|░|██|\n"
                   "|███|▓▓▓|███|███|▓▓▓|███|▓▓▓|███|███|███|███|\n"
                   "|███|▓▓▓|███|███|▓▓▓|███|▓▓▓|███|███|███|███|\n"
                   "|███|▓▓▓|███|███|▓▓▓|███|▓▓▓|███|███|███|███|\n");
        }
        else if(strcmp("C#",chord) == 0 || strcmp("Db",chord) == 0){
            //Chord C#
            printf(" ___________________________________________\n"
                   "|██|░|█|▓|█|░|██|██|▓|█|░|██|▓▓|░|█|░|█|░|██|\n"
                   "|██|░|█|▓|█|░|██|██|▓|█|░|██|▓▓|░|█|░|█|░|██|\n"
                   "|██|░|█|▓|█|░|██|██|▓|█|░|██|▓▓|░|█|░|█|░|██|\n"
                   "|██|░|█|▓|█|░|██|██|▓|█|░|██|▓▓|░|█|░|█|░|██|\n"
                   "|███|███|███|███|███|███|███|▓▓▓|███|███|███|\n"
                   "|███|███|███|███|███|███|███|▓▓▓|███|███|███|\n"
                   "|███|███|███|███|███|███|███|▓▓▓|███|███|███|\n");
        }
        else if(strcmp("D",chord) == 0){
            //Chord D
            printf(" ___________________________________________\n"
                   "|██|▓|█|░|▓|░|██|██|░|▓|░|██|██|░|█|░|█|░|██|\n"
                   "|██|▓|█|░|▓|░|██|██|░|▓|░|██|██|░|█|░|█|░|██|\n"
                   "|██|▓|█|░|▓|░|██|██|░|▓|░|██|██|░|█|░|█|░|██|\n"
                   "|██|▓|█|░|▓|░|██|██|░|▓|░|██|██|░|█|░|█|░|██|\n"
                   "|███|███|▓▓▓|███|███|▓▓▓|███|███|███|███|███|\n"
                   "|███|███|▓▓▓|███|███|▓▓▓|███|███|███|███|███|\n"
                   "|███|███|▓▓▓|███|███|▓▓▓|███|███|███|███|███|\n");
        }
        else if(strcmp("Eb",chord) == 0 || strcmp("D#",chord) == 0){
            //Chord Eb
            printf(" ___________________________________________\n"
                    "|██|░|▓|░|█|▓|██|██|░|█|▓|██|██|░|█|░|█|░|██|\n"
                    "|██|░|▓|░|█|▓|██|██|░|█|▓|██|██|░|█|░|█|░|██|\n"
                    "|██|░|▓|░|█|▓|██|██|░|█|▓|██|██|░|█|░|█|░|██|\n"
                    "|██|░|▓|░|█|▓|██|██|░|█|▓|██|██|░|█|░|█|░|██|\n"
                    "|███|▓▓▓|███|███|███|███|███|███|███|███|███|\n"
                    "|███|▓▓▓|███|███|███|███|███|███|███|███|███|\n"
                    "|███|▓▓▓|███|███|███|███|███|███|███|███|███|\n");
        }
        else if(strcmp("E",chord) == 0){
            //Chord E
            printf(" ___________________________________________\n"
                   "|██|░|█|▓|█|░|▓▓|██|░|█|░|▓▓|██|░|█|░|█|░|██|\n"
                   "|██|░|█|▓|█|░|▓▓|██|░|█|░|▓▓|██|░|█|░|█|░|██|\n"
                   "|██|░|█|▓|█|░|▓▓|██|░|█|░|▓▓|██|░|█|░|█|░|██|\n"
                   "|██|░|█|▓|█|░|▓▓|██|░|█|░|▓▓|██|░|█|░|█|░|██|\n"
                   "|███|███|███|▓▓▓|███|███|▓▓▓|███|███|███|███|\n"
                   "|███|███|███|▓▓▓|███|███|▓▓▓|███|███|███|███|\n"
                   "|███|███|███|▓▓▓|███|███|▓▓▓|███|███|███|███|\n");
        }
        else if(strcmp("F",chord) == 0){
            //Chord F
            printf(" ___________________________________________\n"
                   "|██|░|█|░|▓|░|██|▓▓|░|█|░|██|▓▓|░|█|░|█|░|██|\n"
                   "|██|░|█|░|▓|░|██|▓▓|░|█|░|██|▓▓|░|█|░|█|░|██|\n"
                   "|██|░|█|░|▓|░|██|▓▓|░|█|░|██|▓▓|░|█|░|█|░|██|\n"
                   "|██|░|█|░|▓|░|██|▓▓|░|█|░|██|▓▓|░|█|░|█|░|██|\n"
                   "|███|███|▓▓▓|███|▓▓▓|███|███|▓▓▓|███|███|███|\n"
                   "|███|███|▓▓▓|███|▓▓▓|███|███|▓▓▓|███|███|███|\n"
                   "|███|███|▓▓▓|███|▓▓▓|███|███|▓▓▓|███|███|███|\n");
        }
        else if(strcmp("Gb",chord) == 0 || strcmp("F#",chord) == 0){
            //Chord F#
            printf(" ___________________________________________\n"
                "|██|▓|█|░|█|▓|██|██|▓|█|░|██|██|░|█|░|█|░|██|\n"
                "|██|▓|█|░|█|▓|██|██|▓|█|░|██|██|░|█|░|█|░|██|\n"
                "|██|▓|█|░|█|▓|██|██|▓|█|░|██|██|░|█|░|█|░|██|\n"
                "|██|▓|█|░|█|▓|██|██|▓|█|░|██|██|░|█|░|█|░|██|\n"
                "|███|███|███|███|███|███|███|███|███|███|███|\n"
                "|███|███|███|███|███|███|███|███|███|███|███|\n"
                "|███|███|███|███|███|███|███|███|███|███|███|\n");
        }
        else if(strcmp("G",chord) == 0){
            //Chord G
            printf(" ___________________________________________\n"
                "|██|░|▓|░|█|░|▓▓|██|░|▓|░|██|██|░|█|░|█|░|██|\n"
                "|██|░|▓|░|█|░|▓▓|██|░|▓|░|██|██|░|█|░|█|░|██|\n"
                "|██|░|▓|░|█|░|▓▓|██|░|▓|░|██|██|░|█|░|█|░|██|\n"
                "|██|░|▓|░|█|░|▓▓|██|░|▓|░|██|██|░|█|░|█|░|██|\n"
                "|███|▓▓▓|███|▓▓▓|███|▓▓▓|███|███|███|███|███|\n"
                "|███|▓▓▓|███|▓▓▓|███|▓▓▓|███|███|███|███|███|\n"
                "|███|▓▓▓|███|▓▓▓|███|▓▓▓|███|███|███|███|███|\n");
        }
        else if(strcmp("G#",chord) == 0 || strcmp("Ab",chord) == 0){
            //Chord Ab
            printf(" ___________________________________________\n"
                "|██|░|█|▓|█|░|██|▓▓|░|█|▓|██|██|░|█|░|█|░|██|\n"
                "|██|░|█|▓|█|░|██|▓▓|░|█|▓|██|██|░|█|░|█|░|██|\n"
                "|██|░|█|▓|█|░|██|▓▓|░|█|▓|██|██|░|█|░|█|░|██|\n"
                "|██|░|█|▓|█|░|██|▓▓|░|█|▓|██|██|░|█|░|█|░|██|\n"
                "|███|███|███|███|▓▓▓|███|███|███|███|███|███|\n"
                "|███|███|███|███|▓▓▓|███|███|███|███|███|███|\n"
                "|███|███|███|███|▓▓▓|███|███|███|███|███|███|\n");
        }
        else if(strcmp("A",chord) == 0){
            //Chord A
            printf(" ___________________________________________\n"
                "|██|░|█|░|▓|░|██|██|▓|█|░|▓▓|██|░|█|░|█|░|██|\n"
                "|██|░|█|░|▓|░|██|██|▓|█|░|▓▓|██|░|█|░|█|░|██|\n"
                "|██|░|█|░|▓|░|██|██|▓|█|░|▓▓|██|░|█|░|█|░|██|\n"
                "|██|░|█|░|▓|░|██|██|▓|█|░|▓▓|██|░|█|░|█|░|██|\n"
                "|███|███|▓▓▓|███|███|███|▓▓▓|███|███|███|███|\n"
                "|███|███|▓▓▓|███|███|███|▓▓▓|███|███|███|███|\n"
                "|███|███|▓▓▓|███|███|███|▓▓▓|███|███|███|███|\n");
        }
        else if(strcmp("A#",chord) == 0 || strcmp("Bb",chord) == 0){
            //Chord Bb
            printf(" ___________________________________________\n"
                "|██|░|█|░|█|▓|██|██|░|▓|░|██|▓▓|░|█|░|█|░|██|\n"
                "|██|░|█|░|█|▓|██|██|░|▓|░|██|▓▓|░|█|░|█|░|██|\n"
                "|██|░|█|░|█|▓|██|██|░|▓|░|██|▓▓|░|█|░|█|░|██|\n"
                "|██|░|█|░|█|▓|██|██|░|▓|░|██|▓▓|░|█|░|█|░|██|\n"
                "|███|███|███|███|███|▓▓▓|███|▓▓▓|███|███|███|\n"
                "|███|███|███|███|███|▓▓▓|███|▓▓▓|███|███|███|\n"
                "|███|███|███|███|███|▓▓▓|███|▓▓▓|███|███|███|\n");
        }
        else if(strcmp("B",chord) == 0){
            //Chord B
            printf(" ___________________________________________\n"
                "|██|▓|█|░|█|░|▓▓|██|░|█|▓|██|██|░|█|░|█|░|██|\n"
                "|██|▓|█|░|█|░|▓▓|██|░|█|▓|██|██|░|█|░|█|░|██|\n"
                "|██|▓|█|░|█|░|▓▓|██|░|█|▓|██|██|░|█|░|█|░|██|\n"
                "|██|▓|█|░|█|░|▓▓|██|░|█|▓|██|██|░|█|░|█|░|██|\n"
                "|███|███|███|▓▓▓|███|███|███|███|███|███|███|\n"
                "|███|███|███|▓▓▓|███|███|███|███|███|███|███|\n"
                "|███|███|███|▓▓▓|███|███|███|███|███|███|███|\n");
        }
        else if(strcmp("Cm",chord) == 0){
            //Chord C minor
            printf(" ___________________________________________\n"
                   "|██|░|▓|░|█|░|██|▓▓|░|█|▓|██|██|░|█|░|█|░|██|\n"
                   "|██|░|▓|░|█|░|██|▓▓|░|█|▓|██|██|░|█|░|█|░|██|\n"
                   "|██|░|▓|░|█|░|██|▓▓|░|█|▓|██|██|░|█|░|█|░|██|\n"
                   "|██|░|▓|░|█|░|██|▓▓|░|█|▓|██|██|░|█|░|█|░|██|\n"
                   "|███|▓▓▓|███|███|▓▓▓|███|███|███|███|███|███|\n"
                   "|███|▓▓▓|███|███|▓▓▓|███|███|███|███|███|███|\n"
                   "|███|▓▓▓|███|███|▓▓▓|███|███|███|███|███|███|\n");
        }
        else if(strcmp("C#m",chord) == 0 || strcmp("Dbm",chord) == 0){
            //Chord C# minor
            printf(" ___________________________________________\n"
                   "|██|░|█|▓|█|░|██|██|▓|█|░|▓▓|██|░|█|░|█|░|██|\n"
                   "|██|░|█|▓|█|░|██|██|▓|█|░|▓▓|██|░|█|░|█|░|██|\n"
                   "|██|░|█|▓|█|░|██|██|▓|█|░|▓▓|██|░|█|░|█|░|██|\n"
                   "|██|░|█|▓|█|░|██|██|▓|█|░|▓▓|██|░|█|░|█|░|██|\n"
                   "|███|███|███|███|███|███|▓▓▓|███|███|███|███|\n"
                   "|███|███|███|███|███|███|▓▓▓|███|███|███|███|\n"
                   "|███|███|███|███|███|███|▓▓▓|███|███|███|███|\n");
        }
        else if(strcmp("Dm",chord) == 0){
            //Chord D minor
            printf(" ___________________________________________\n"
                "|██|░|█|░|▓|░|██|██|░|▓|░|██|▓▓|░|█|░|█|░|██|\n"
                "|██|░|█|░|▓|░|██|██|░|▓|░|██|▓▓|░|█|░|█|░|██|\n"
                "|██|░|█|░|▓|░|██|██|░|▓|░|██|▓▓|░|█|░|█|░|██|\n"
                "|██|░|█|░|▓|░|██|██|░|▓|░|██|▓▓|░|█|░|█|░|██|\n"
                "|███|███|▓▓▓|███|███|▓▓▓|███|▓▓▓|███|███|███|\n"
                "|███|███|▓▓▓|███|███|▓▓▓|███|▓▓▓|███|███|███|\n"
                "|███|███|▓▓▓|███|███|▓▓▓|███|▓▓▓|███|███|███|\n");
        }
        else if(strcmp("D#m",chord) == 0 || strcmp("Ebm",chord) == 0){
            //Chord Eb minor
            printf(" ___________________________________________\n"
                "|██|▓|█|░|█|▓|██|██|░|█|▓|██|██|░|█|░|█|░|██|\n"
                "|██|▓|█|░|█|▓|██|██|░|█|▓|██|██|░|█|░|█|░|██|\n"
                "|██|▓|█|░|█|▓|██|██|░|█|▓|██|██|░|█|░|█|░|██|\n"
                "|██|▓|█|░|█|▓|██|██|░|█|▓|██|██|░|█|░|█|░|██|\n"
                "|███|███|███|███|███|███|███|███|███|███|███|\n"
                "|███|███|███|███|███|███|███|███|███|███|███|\n"
                "|███|███|███|███|███|███|███|███|███|███|███|\n");
        }
        else if(strcmp("Em",chord) == 0){
            //Chord E minor
            printf(" ___________________________________________\n"
                "|██|░|▓|░|█|░|▓▓|██|░|█|░|▓▓|██|░|█|░|█|░|██|\n"
                "|██|░|▓|░|█|░|▓▓|██|░|█|░|▓▓|██|░|█|░|█|░|██|\n"
                "|██|░|▓|░|█|░|▓▓|██|░|█|░|▓▓|██|░|█|░|█|░|██|\n"
                "|██|░|▓|░|█|░|▓▓|██|░|█|░|▓▓|██|░|█|░|█|░|██|\n"
                "|███|▓▓▓|███|▓▓▓|███|███|▓▓▓|███|███|███|███|\n"
                "|███|▓▓▓|███|▓▓▓|███|███|▓▓▓|███|███|███|███|\n"
                "|███|▓▓▓|███|▓▓▓|███|███|▓▓▓|███|███|███|███|\n");
        }
        else if(strcmp("Fm",chord) == 0){
            //Chord F minor
            printf(" ___________________________________________\n"
                "|██|░|█|▓|█|░|██|▓▓|░|█|░|██|▓▓|░|█|░|█|░|██|\n"
                "|██|░|█|▓|█|░|██|▓▓|░|█|░|██|▓▓|░|█|░|█|░|██|\n"
                "|██|░|█|▓|█|░|██|▓▓|░|█|░|██|▓▓|░|█|░|█|░|██|\n"
                "|██|░|█|▓|█|░|██|▓▓|░|█|░|██|▓▓|░|█|░|█|░|██|\n"
                "|███|███|███|███|▓▓▓|███|███|▓▓▓|███|███|███|\n"
                "|███|███|███|███|▓▓▓|███|███|▓▓▓|███|███|███|\n"
                "|███|███|███|███|▓▓▓|███|███|▓▓▓|███|███|███|\n");
        }
       else if(strcmp("Gbm",chord) == 0 || strcmp("F#m",chord) == 0){
            //Chord F#m
            printf(" ___________________________________________\n"
                   "|██|▓|█|░|▓|░|██|██|▓|█|░|██|██|░|█|░|█|░|██|\n"
                   "|██|▓|█|░|▓|░|██|██|▓|█|░|██|██|░|█|░|█|░|██|\n"
                   "|██|▓|█|░|▓|░|██|██|▓|█|░|██|██|░|█|░|█|░|██|\n"
                   "|██|▓|█|░|▓|░|██|██|▓|█|░|██|██|░|█|░|█|░|██|\n"
                   "|███|███|▓▓▓|███|███|███|███|███|███|███|███|\n"
                   "|███|███|▓▓▓|███|███|███|███|███|███|███|███|\n"
                   "|███|███|▓▓▓|███|███|███|███|███|███|███|███|\n");
       }
        else if(strcmp("Gm",chord) == 0){
            //Chord Gm
            printf(" ___________________________________________\n"
                "|██|░|▓|░|█|▓|██|██|░|▓|░|██|██|░|█|░|█|░|██|\n"
                "|██|░|▓|░|█|▓|██|██|░|▓|░|██|██|░|█|░|█|░|██|\n"
                "|██|░|▓|░|█|▓|██|██|░|▓|░|██|██|░|█|░|█|░|██|\n"
                "|██|░|▓|░|█|▓|██|██|░|▓|░|██|██|░|█|░|█|░|██|\n"
                "|███|▓▓▓|███|███|███|▓▓▓|███|███|███|███|███|\n"
                "|███|▓▓▓|███|███|███|▓▓▓|███|███|███|███|███|\n"
                "|███|▓▓▓|███|███|███|▓▓▓|███|███|███|███|███|\n");
        }
        else if(strcmp("G#m",chord) == 0 || strcmp("Abm",chord) == 0){
            //Chord Abm
            printf(" ___________________________________________\n"
                "|██|░|█|▓|█|░|▓▓|██|░|█|▓|██|██|░|█|░|█|░|██|\n"
                "|██|░|█|▓|█|░|▓▓|██|░|█|▓|██|██|░|█|░|█|░|██|\n"
                "|██|░|█|▓|█|░|▓▓|██|░|█|▓|██|██|░|█|░|█|░|██|\n"
                "|██|░|█|▓|█|░|▓▓|██|░|█|▓|██|██|░|█|░|█|░|██|\n"
                "|███|███|███|▓▓▓|███|███|███|███|███|███|███|\n"
                "|███|███|███|▓▓▓|███|███|███|███|███|███|███|\n"
                "|███|███|███|▓▓▓|███|███|███|███|███|███|███|\n");
        }
        else if(strcmp("Am",chord) == 0){
            //Chord Am
            printf(" ___________________________________________\n"
                "|██|░|▓|░|█|░|██|▓▓|░|█|░|▓▓|██|░|█|░|█|░|██|\n"
                "|██|░|▓|░|█|░|██|▓▓|░|█|░|▓▓|██|░|█|░|█|░|██|\n"
                "|██|░|▓|░|█|░|██|▓▓|░|█|░|▓▓|██|░|█|░|█|░|██|\n"
                "|██|░|▓|░|█|░|██|▓▓|░|█|░|▓▓|██|░|█|░|█|░|██|\n"
                "|███|▓▓▓|███|███|▓▓▓|███|▓▓▓|███|███|███|███|\n"
                "|███|▓▓▓|███|███|▓▓▓|███|▓▓▓|███|███|███|███|\n"
                "|███|▓▓▓|███|███|▓▓▓|███|▓▓▓|███|███|███|███|\n");
        }
        else if(strcmp("A#m",chord) == 0 || strcmp("Bbm",chord) == 0){
            //Chord Bbm
            printf(" ___________________________________________\n"
                "|██|░|█|░|█|▓|██|██|▓|█|░|██|▓▓|░|█|░|█|░|██|\n"
                "|██|░|█|░|█|▓|██|██|▓|█|░|██|▓▓|░|█|░|█|░|██|\n"
                "|██|░|█|░|█|▓|██|██|▓|█|░|██|▓▓|░|█|░|█|░|██|\n"
                "|██|░|█|░|█|▓|██|██|▓|█|░|██|▓▓|░|█|░|█|░|██|\n"
                "|███|███|███|███|███|███|███|▓▓▓|███|███|███|\n"
                "|███|███|███|███|███|███|███|▓▓▓|███|███|███|\n"
                "|███|███|███|███|███|███|███|▓▓▓|███|███|███|\n");
        }
        else if(strcmp("Bm",chord) == 0){
            //Chord Bm
            printf(" ___________________________________________\n"
                "|██|▓|█|░|█|░|▓▓|██|░|▓|░|██|██|░|█|░|█|░|██|\n"
                "|██|▓|█|░|█|░|▓▓|██|░|▓|░|██|██|░|█|░|█|░|██|\n"
                "|██|▓|█|░|█|░|▓▓|██|░|▓|░|██|██|░|█|░|█|░|██|\n"
                "|██|▓|█|░|█|░|▓▓|██|░|▓|░|██|██|░|█|░|█|░|██|\n"
                "|███|███|███|▓▓▓|███|▓▓▓|███|███|███|███|███|\n"
                "|███|███|███|▓▓▓|███|▓▓▓|███|███|███|███|███|\n"
                "|███|███|███|▓▓▓|███|▓▓▓|███|███|███|███|███|\n");
        }



    }
}

int main()
{
    int end = 0;
    int mode = 0;
    while(end != 1){
        printf(
" ██▓███   ██▓ ▄▄▄       ███▄    █  ▒█████       ██████  ▄▄▄    ██▒   █▓ ▄▄▄        ▄████ ▓█████ \n"
"▓██░  ██▒▓██▒▒████▄     ██ ▀█   █ ▒██▒  ██▒   ▒██    ▒ ▒████▄ ▓██░   █▒▒████▄     ██▒ ▀█▒▓█   ▀ \n"
"▓██░ ██▓▒▒██▒▒██  ▀█▄  ▓██  ▀█ ██▒▒██░  ██▒   ░ ▓██▄   ▒██  ▀█▄▓██  █▒░▒██  ▀█▄  ▒██░▄▄▄░▒███   \n"
"▒██▄█▓▒ ▒░██░░██▄▄▄▄██ ▓██▒  ▐▌██▒▒██   ██░     ▒   ██▒░██▄▄▄▄██▒██ █░░░██▄▄▄▄██ ░▓█  ██▓▒▓█  ▄ \n"
"▒██▒ ░  ░░██░ ▓█   ▓██▒▒██░   ▓██░░ ████▓▒░   ▒██████▒▒ ▓█   ▓██▒▒▀█░   ▓█   ▓██▒░▒▓███▀▒░▒████▒\n"
"▒▓▒░ ░  ░░▓   ▒▒   ▓▒█░░ ▒░   ▒ ▒ ░ ▒░▒░▒░    ▒ ▒▓▒ ▒ ░ ▒▒   ▓▒█░░ ▐░   ▒▒   ▓▒█░ ░▒   ▒ ░░ ▒░ ░\n"
"░▒ ░      ▒ ░  ▒   ▒▒ ░░ ░░   ░ ▒░  ░ ▒ ▒░    ░ ░▒  ░ ░  ▒   ▒▒ ░░ ░░    ▒   ▒▒ ░  ░   ░  ░ ░  ░\n"
"░░        ▒ ░  ░   ▒      ░   ░ ░ ░ ░ ░ ▒     ░  ░  ░    ░   ▒     ░░    ░   ▒   ░ ░   ░    ░   \n"
"          ░        ░  ░         ░     ░ ░           ░        ░  ░   ░        ░  ░      ░    ░  ░\n"
"                                                                   ░                            \n");
        printf("Select Mode\n"
               "1.Play Mode\n"
               "2.Chords Mode\n"
               "3.Help\n"
               "4.Exit\n"
               "Type in number to choose mode\n"
               "Choose Mode:");
        scanf("%i",&mode);
        if(mode == 1){
            end = playMode();
        }
        else if(mode == 2){
            end = chordMode();
        }
        else if(mode == 3){
            end = helpMode();
        }
        else if(mode == 4){
            end = 1;
        }
    }
    
    return 0;
}
