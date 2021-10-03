#include <avr/io.h>
#include <util/delay.h>
#include <assert.h>
#include <stdio.h>

#include "lcd.h"


#define DEBUG_BAUD 9600

#define NOSE_OFFSET 5

void draw_outline(void);
void draw_happy(void);
void draw_sad(void);

void color_pallet();

void draw_happy_eyes1(void);
void draw_happy_eyes2(void);

void draw_angry_eye_black(void);
void draw_angry_eye_red(void);

void draw_sad_eye1(void);
void draw_sad_eye2(void);

void draw_glasses1(void);
void draw_glasses2(void);

void draw_neutral_eye(void);
void draw_neutral_tongue(void);

void read_serial(void);


int uputchar1(char c, FILE *stream) {
	if (c == '\n') uputchar1('\r', stream);
	while (!(UCSR1A & _BV(UDRE1)));
	UDR1 = c;
	return c;
}

int ugetchar1(FILE *stream) {
	while(!(UCSR1A & _BV(RXC1)));
	return UDR1;
}

void init_debug_uart1(void) {
	/* Configure UART0 baud rate, one start bit, 8-bit, no parity and one stop bit */
	UBRR1H = (F_CPU/(DEBUG_BAUD*16L)-1) >> 8;
	UBRR1L = (F_CPU/(DEBUG_BAUD*16L)-1);
	UCSR1B = _BV(RXEN1) | _BV(TXEN1);
	UCSR1C = _BV(UCSZ10) | _BV(UCSZ11);

	/* Setup new streams for input and output */
	static FILE uout = FDEV_SETUP_STREAM(uputchar1, NULL, _FDEV_SETUP_WRITE);
	static FILE uin = FDEV_SETUP_STREAM(NULL, ugetchar1, _FDEV_SETUP_READ);

	/* Redirect all standard streams to UART1 */
	stdout = &uout;
	stderr = &uout;
	stdin = &uin;
}




uint8_t cur_face = 0;



int main() {

    init_lcd();

    init_debug_uart1();


    set_orientation(North);
    clear_screen();

    printf("Hello World!");
    
    



    while(1) {

        read_serial();

        if(cur_face == 0) {
            clear_screen();
        }
        else if(cur_face == 1) {
            draw_outline();
            draw_happy_eyes1();
            draw_happy();

            _delay_ms(600);

            draw_outline();
            draw_happy_eyes2();
            draw_sad();

            _delay_ms(600);
        }
        else if(cur_face == 2) {
            
        }
        else if(cur_face == 3) {
            
        }
        else if(cur_face == 4) {
            
        }
        else if(cur_face == 5) {
            
        }
        else if(cur_face == 6) {
            
        }
        else if(cur_face == 7) {
            
        }
        else if(cur_face == 8) {
            
        }
        else if(cur_face == 9) {
            
        }

        _delay_ms(100);
    }






    while(1) {
        draw_outline();
        draw_happy();
        draw_glasses1();
        _delay_ms(600);

        draw_glasses2();
        _delay_ms(600);
    }

    
/*
    while(1) {
        draw_outline();
        draw_sad();
        draw_sad_eye1();
        _delay_ms(600);

        draw_outline();
        draw_sad();
        draw_sad_eye2();
        _delay_ms(600);
    }*/
    
/*
    while(1) {
        draw_outline();

        draw_happy_eyes1();
        draw_happy();
        _delay_ms(600);


        draw_outline();

        draw_happy_eyes2();
        draw_sad();
        _delay_ms(600);
    }*/
}




void draw_outline() {
    rectangle r;

    //main face white rectangle
    r.top = 80;
    r.bottom = 200;
    r.left = 40;
    r.right = 200;

    fill_rectangle(r, WHITE);

    //main face black rectangle
    r.top = 82;
    r.bottom = 198;
    r.left = 42;
    r.right = 198;

    //fill_rectangle(r, BLACK);



    //left ear white rectangle
    r.top = 50;
    r.bottom = 80;
    r.left = 40;
    r.right = 70;

    fill_rectangle(r, WHITE);

    //left ear black rectangle
    r.top = 52;
    r.bottom = 80;
    r.left = 42;
    r.right = 68;

    fill_rectangle(r, MAGENTA);



    //right ear white rectangle
    r.top = 50;
    r.bottom = 80;
    r.left = 170;
    r.right = 200;

    fill_rectangle(r, WHITE);

    //right ear black rectangle
    r.top = 52;
    r.bottom = 80;
    r.left = 172;
    r.right = 198;

    fill_rectangle(r, MAGENTA);



    //collar red
    r.top = 200;
    r.bottom = 220;
    r.left = 70;
    r.right = 170;

    fill_rectangle(r, RED);

    //bell
    r.top = 200;
    r.bottom = 220;
    r.left = 110;
    r.right = 130;

    fill_rectangle(r, YELLOW);

    //bell middle
    r.top = 210;
    r.bottom = 220;
    r.left = 118;
    r.right = 122;

    fill_rectangle(r, BLACK);


    int nose_offset = 5;
    //nose outline
    r.top = 140;
    r.bottom = 150;
    r.left = 110 - nose_offset;
    r.right = 130 - nose_offset;

    fill_rectangle(r, BLACK);

    //nose centre
    r.top = 143;
    r.bottom = 147;
    r.left = 113 - nose_offset;
    r.right = 127 - nose_offset;

    fill_rectangle(r, MAGENTA);


    //nose drop down
    r.top = 150;
    r.bottom = 170;
    r.left = 118 - nose_offset;
    r.right = 122 - nose_offset;

    fill_rectangle(r, BLACK);

    //middle mouth
    r.top = 170;
    r.bottom = 174;
    r.left = 80 - nose_offset;
    r.right = 160 - nose_offset;

    fill_rectangle(r, BLACK);
}


void draw_happy() {
    rectangle r;

    //happy mouth left
    r.top = 150;
    r.bottom = 170;
    r.left = 80 - NOSE_OFFSET;
    r.right = 84 - NOSE_OFFSET;

    fill_rectangle(r, BLACK);

    //happy mouth right
    r.top = 150;
    r.bottom = 170;
    r.left = 156 - NOSE_OFFSET;
    r.right = 160 - NOSE_OFFSET;

    fill_rectangle(r, BLACK);
}

void draw_sad() {
    rectangle r;

    //sad mouth left
    r.top = 174;
    r.bottom = 189;
    r.left = 80 - NOSE_OFFSET;
    r.right = 84 - NOSE_OFFSET;

    fill_rectangle(r, BLACK);

    //sad mouth right
    r.top = 174;
    r.bottom = 189;
    r.left = 156 - NOSE_OFFSET;
    r.right = 160 - NOSE_OFFSET;

    fill_rectangle(r, BLACK);
}



void color_pallet() {
    rectangle r;

    r.top = 0;
    r.bottom = 80;
    r.left = 0;
    r.right = 120;

    fill_rectangle(r, WHITE);

    r.top = 80;
    r.bottom = 160;
    r.left = 0;
    r.right = 120;

    fill_rectangle(r, BLACK);
        
    r.top = 160;
    r.bottom = 240;
    r.left = 0;
    r.right = 120;

    fill_rectangle(r, BLUE);

    r.top = 240;
    r.bottom = 319;
    r.left = 0;
    r.right = 120;

    fill_rectangle(r, GREEN);




    r.top = 0;
    r.bottom = 80;
    r.left = 120;
    r.right = 240;

    fill_rectangle(r,CYAN);

    r.top = 80;
    r.bottom = 160;
    r.left = 120;
    r.right = 240;

    fill_rectangle(r, MAGENTA);
        
    r.top = 160;
    r.bottom = 240;
    r.left = 120;
    r.right = 240;

    fill_rectangle(r, RED);

    r.top = 240;
    r.bottom = 319;
    r.left = 120;
    r.right = 240;

    fill_rectangle(r, YELLOW); 
    
    
}


void draw_happy_eyes1() {
    rectangle r;

    //left eye space
    r.top = 100;
    r.bottom = 130;
    r.left = 60 - NOSE_OFFSET;
    r.right = 100 - NOSE_OFFSET;

    fill_rectangle(r, BLACK);

    //right eye space
    r.top = 100;
    r.bottom = 130;
    r.left = 140 - NOSE_OFFSET;
    r.right = 180 - NOSE_OFFSET;

    fill_rectangle(r, BLACK);



    //left eye inside
    r.top = 104;
    r.bottom = 126;
    r.left = 64 - NOSE_OFFSET;
    r.right = 96 - NOSE_OFFSET;

    fill_rectangle(r, WHITE);

    //right eye inside
    r.top = 104;
    r.bottom = 126;
    r.left = 144 - NOSE_OFFSET;
    r.right = 176 - NOSE_OFFSET;

    fill_rectangle(r, WHITE);



    //left iris outline
    r.top = 100;
    r.bottom = 120;
    r.left = 60 - NOSE_OFFSET;
    r.right = 80 - NOSE_OFFSET;

    fill_rectangle(r, BLACK);

    //right iris outline
    r.top = 100;
    r.bottom = 120;
    r.left = 140 - NOSE_OFFSET;
    r.right = 160 - NOSE_OFFSET;

    fill_rectangle(r,BLACK);

    //left iris fill
    r.top = 107;
    r.bottom = 113;
    r.left = 65 - NOSE_OFFSET;
    r.right = 75 - NOSE_OFFSET;

    fill_rectangle(r, CYAN);

    //right iris fill
    r.top = 107;
    r.bottom = 113;
    r.left = 145 - NOSE_OFFSET;
    r.right = 155 - NOSE_OFFSET;

    fill_rectangle(r,GREEN);

}

void draw_happy_eyes2() {
    rectangle r;

    //left eye space
    r.top = 100;
    r.bottom = 130;
    r.left = 60 - NOSE_OFFSET;
    r.right = 100 - NOSE_OFFSET;

    fill_rectangle(r, BLACK);

    //right eye space
    r.top = 100;
    r.bottom = 130;
    r.left = 140 - NOSE_OFFSET;
    r.right = 180 - NOSE_OFFSET;

    fill_rectangle(r, BLACK);



    //left eye inside
    r.top = 104;
    r.bottom = 126;
    r.left = 64 - NOSE_OFFSET;
    r.right = 96 - NOSE_OFFSET;

    fill_rectangle(r, WHITE);

    //right eye inside
    r.top = 104;
    r.bottom = 126;
    r.left = 144 - NOSE_OFFSET;
    r.right = 176 - NOSE_OFFSET;

    fill_rectangle(r, WHITE);



    //left iris outline
    r.top = 100;
    r.bottom = 120;
    r.left = 80 - NOSE_OFFSET;
    r.right = 100 - NOSE_OFFSET;

    fill_rectangle(r, BLACK);

    //right iris outline
    r.top = 100;
    r.bottom = 120;
    r.left = 160 - NOSE_OFFSET;
    r.right = 180 - NOSE_OFFSET;

    fill_rectangle(r,BLACK);

    //left iris fill
    r.top = 107;
    r.bottom = 113;
    r.left = 85 - NOSE_OFFSET;
    r.right = 95 - NOSE_OFFSET;

    fill_rectangle(r, CYAN);

    //right iris fill
    r.top = 107;
    r.bottom = 113;
    r.left = 165 - NOSE_OFFSET;
    r.right = 175 - NOSE_OFFSET;

    fill_rectangle(r,GREEN);

}



void draw_angry_eye_black() {
    rectangle r;

    //left eye space
    r.top = 100;
    r.bottom = 130;
    r.left = 60 - NOSE_OFFSET;
    r.right = 100 - NOSE_OFFSET;

    fill_rectangle(r, WHITE);

    //right eye space
    r.top = 100;
    r.bottom = 130;
    r.left = 140 - NOSE_OFFSET;
    r.right = 180 - NOSE_OFFSET;

    fill_rectangle(r, WHITE);


    //angry eye left
    r.top = 100;
    r.bottom = 105;
    r.left = 60 - NOSE_OFFSET;
    r.right = 80 - NOSE_OFFSET;

    fill_rectangle(r, BLACK);

    r.top = 105;
    r.bottom = 110;
    r.left = 70 - NOSE_OFFSET;
    r.right = 90 - NOSE_OFFSET;

    fill_rectangle(r, BLACK);

    r.top = 110;
    r.bottom = 115;
    r.left = 80 - NOSE_OFFSET;
    r.right = 100 - NOSE_OFFSET;

    fill_rectangle(r, BLACK);



    //angry eye right
    r.top = 100;
    r.bottom = 105;
    r.left = 160 - NOSE_OFFSET;
    r.right = 180 - NOSE_OFFSET;

    fill_rectangle(r, BLACK);

    r.top = 105;
    r.bottom = 110;
    r.left = 150 - NOSE_OFFSET;
    r.right = 170 - NOSE_OFFSET;

    fill_rectangle(r, BLACK);

    r.top = 110;
    r.bottom = 115;
    r.left = 140 - NOSE_OFFSET;
    r.right = 160 - NOSE_OFFSET;

    fill_rectangle(r, BLACK);
}

void draw_angry_eye_red() {
    rectangle r;

    //left eye space
    r.top = 100;
    r.bottom = 130;
    r.left = 60 - NOSE_OFFSET;
    r.right = 100 - NOSE_OFFSET;

    fill_rectangle(r, WHITE);

    //right eye space
    r.top = 100;
    r.bottom = 130;
    r.left = 140 - NOSE_OFFSET;
    r.right = 180 - NOSE_OFFSET;

    fill_rectangle(r, WHITE);


    //angry eye left
    r.top = 100;
    r.bottom = 105;
    r.left = 60 - NOSE_OFFSET;
    r.right = 80 - NOSE_OFFSET;

    fill_rectangle(r, RED);

    r.top = 105;
    r.bottom = 110;
    r.left = 70 - NOSE_OFFSET;
    r.right = 90 - NOSE_OFFSET;

    fill_rectangle(r, RED);

    r.top = 110;
    r.bottom = 115;
    r.left = 80 - NOSE_OFFSET;
    r.right = 100 - NOSE_OFFSET;

    fill_rectangle(r, RED);



    //angry eye right
    r.top = 100;
    r.bottom = 105;
    r.left = 160 - NOSE_OFFSET;
    r.right = 180 - NOSE_OFFSET;

    fill_rectangle(r, RED);

    r.top = 105;
    r.bottom = 110;
    r.left = 150 - NOSE_OFFSET;
    r.right = 170 - NOSE_OFFSET;

    fill_rectangle(r, RED);

    r.top = 110;
    r.bottom = 115;
    r.left = 140 - NOSE_OFFSET;
    r.right = 160 - NOSE_OFFSET;

    fill_rectangle(r, RED);
}





void draw_sad_eye1() {
    rectangle r;

    //left eye space
    r.top = 100;
    r.bottom = 130;
    r.left = 60 - NOSE_OFFSET;
    r.right = 100 - NOSE_OFFSET;

    fill_rectangle(r, WHITE);

    //right eye space
    r.top = 100;
    r.bottom = 130;
    r.left = 140 - NOSE_OFFSET;
    r.right = 180 - NOSE_OFFSET;

    fill_rectangle(r, WHITE);


    //sad eye left
    r.top = 110;
    r.bottom = 115;
    r.left = 60 - NOSE_OFFSET;
    r.right = 80 - NOSE_OFFSET;

    fill_rectangle(r, BLACK);

    r.top = 105;
    r.bottom = 110;
    r.left = 70 - NOSE_OFFSET;
    r.right = 90 - NOSE_OFFSET;

    fill_rectangle(r, BLACK);

    r.top = 100;
    r.bottom = 105;
    r.left = 80 - NOSE_OFFSET;
    r.right = 100 - NOSE_OFFSET;

    fill_rectangle(r, BLACK);



    //sad eye right
    r.top = 110;
    r.bottom = 115;
    r.left = 160 - NOSE_OFFSET;
    r.right = 180 - NOSE_OFFSET;

    fill_rectangle(r, BLACK);

    r.top = 105;
    r.bottom = 110;
    r.left = 150 - NOSE_OFFSET;
    r.right = 170 - NOSE_OFFSET;

    fill_rectangle(r, BLACK);

    r.top = 100;
    r.bottom = 105;
    r.left = 140 - NOSE_OFFSET;
    r.right = 160 - NOSE_OFFSET;

    fill_rectangle(r, BLACK);


    //left tear
    r.top = 110;
    r.bottom = 130;
    r.left = 80 - NOSE_OFFSET;
    r.right = 85 - NOSE_OFFSET;

    fill_rectangle(r, BLUE);

    //right tear
    r.top = 130;
    r.bottom = 150;
    r.left = 155 - NOSE_OFFSET;
    r.right = 160 - NOSE_OFFSET;

    fill_rectangle(r, BLUE);
}

void draw_sad_eye2() {
    rectangle r;

    //left eye space
    r.top = 100;
    r.bottom = 130;
    r.left = 60 - NOSE_OFFSET;
    r.right = 100 - NOSE_OFFSET;

    fill_rectangle(r, WHITE);

    //right eye space
    r.top = 100;
    r.bottom = 130;
    r.left = 140 - NOSE_OFFSET;
    r.right = 180 - NOSE_OFFSET;

    fill_rectangle(r, WHITE);


    //sad eye left
    r.top = 110;
    r.bottom = 115;
    r.left = 60 - NOSE_OFFSET;
    r.right = 80 - NOSE_OFFSET;

    fill_rectangle(r, BLACK);

    r.top = 105;
    r.bottom = 110;
    r.left = 70 - NOSE_OFFSET;
    r.right = 90 - NOSE_OFFSET;

    fill_rectangle(r, BLACK);

    r.top = 100;
    r.bottom = 105;
    r.left = 80 - NOSE_OFFSET;
    r.right = 100 - NOSE_OFFSET;

    fill_rectangle(r, BLACK);



    //sad eye right
    r.top = 110;
    r.bottom = 115;
    r.left = 160 - NOSE_OFFSET;
    r.right = 180 - NOSE_OFFSET;

    fill_rectangle(r, BLACK);

    r.top = 105;
    r.bottom = 110;
    r.left = 150 - NOSE_OFFSET;
    r.right = 170 - NOSE_OFFSET;

    fill_rectangle(r, BLACK);

    r.top = 100;
    r.bottom = 105;
    r.left = 140 - NOSE_OFFSET;
    r.right = 160 - NOSE_OFFSET;

    fill_rectangle(r, BLACK);


    //left tear
    r.top = 130;
    r.bottom = 150;
    r.left = 80 - NOSE_OFFSET;
    r.right = 85 - NOSE_OFFSET;

    fill_rectangle(r, BLUE);

    //right tear
    r.top = 110;
    r.bottom = 130;
    r.left = 155 - NOSE_OFFSET;
    r.right = 160 - NOSE_OFFSET;

    fill_rectangle(r, BLUE);
}




void draw_glasses1() {
    rectangle r;

    //left glass holder
    r.top = 110;
    r.bottom = 115;
    r.left = 40;
    r.right = 70;

    fill_rectangle(r, BLACK);

    //right glass holder
    r.top = 110;
    r.bottom = 115;
    r.left = 150;
    r.right = 200;

    fill_rectangle(r, BLACK);



    //left glass top
    r.top = 105;
    r.bottom = 125;
    r.left = 65;
    r.right = 100;

    fill_rectangle(r, BLACK);

    //left glass bottom
    r.top = 125;
    r.bottom = 130;
    r.left = 70;
    r.right = 95;

    fill_rectangle(r, BLACK);


    //right glass top
    r.top = 105;
    r.bottom = 125;
    r.left = 130;
    r.right = 165;

    fill_rectangle(r, BLACK);

    //right glass bottom
    r.top = 125;
    r.bottom = 130;
    r.left = 135;
    r.right = 160;

    fill_rectangle(r, BLACK);

    //glass support
    r.top = 115;
    r.bottom = 120;
    r.left = 100;
    r.right = 135;

    fill_rectangle(r, BLACK);



    //left glass glare 1
    r.top = 123;
    r.bottom = 125;
    r.left = 75;
    r.right = 85;

    fill_rectangle(r, WHITE);

    //right glass glare 1
    r.top = 123;
    r.bottom = 125;
    r.left = 140;
    r.right = 150;

    fill_rectangle(r, WHITE);


    //left glass glare 2
    r.top = 121;
    r.bottom = 123;
    r.left = 71;
    r.right = 75;

    fill_rectangle(r, WHITE);

    //right glass glare 2
    r.top = 121;
    r.bottom = 123;
    r.left = 136;
    r.right = 140;

    fill_rectangle(r, WHITE);
}



void draw_glasses2() {
    rectangle r;

    //left glass holder
    r.top = 110;
    r.bottom = 115;
    r.left = 40;
    r.right = 70;

    fill_rectangle(r, BLACK);

    //right glass holder
    r.top = 110;
    r.bottom = 115;
    r.left = 150;
    r.right = 200;

    fill_rectangle(r, BLACK);



    //left glass top
    r.top = 105;
    r.bottom = 125;
    r.left = 65;
    r.right = 100;

    fill_rectangle(r, BLACK);

    //left glass bottom
    r.top = 125;
    r.bottom = 130;
    r.left = 70;
    r.right = 95;

    fill_rectangle(r, BLACK);


    //right glass top
    r.top = 105;
    r.bottom = 125;
    r.left = 130;
    r.right = 165;

    fill_rectangle(r, BLACK);

    //right glass bottom
    r.top = 125;
    r.bottom = 130;
    r.left = 135;
    r.right = 160;

    fill_rectangle(r, BLACK);

    //glass support
    r.top = 115;
    r.bottom = 120;
    r.left = 100;
    r.right = 135;

    fill_rectangle(r, BLACK);



    //left glass glare 1
    r.top = 123;
    r.bottom = 125;
    r.left = 80;
    r.right = 90;

    fill_rectangle(r, WHITE);

    //right glass glare 1
    r.top = 123;
    r.bottom = 125;
    r.left = 145;
    r.right = 155;

    fill_rectangle(r, WHITE);


    //left glass glare 2
    r.top = 121;
    r.bottom = 123;
    r.left = 76;
    r.right = 80;

    fill_rectangle(r, WHITE);

    //right glass glare 2
    r.top = 121;
    r.bottom = 123;
    r.left = 141;
    r.right = 145;

    fill_rectangle(r, WHITE);
}



void read_serial() {


    //char c = getchar0();
    char c = getchar();
    printf("%d\n", c);


    if(c == '0') {
        cur_face = 0;
        printf("Blank Screen");
    }
    else if(c == '1') {
        cur_face = 1;
        printf("Face 1");
    }
    else if(c == '2') {
        cur_face = 2;
    }
    else if(c == '3') {
        cur_face = 3;
    }
    else if(c == '4') {
        cur_face = 4;
    }
    else if(c == '5') {
        cur_face = 5;
    }
    else if(c == '6') {
        cur_face = 6;
    }
    else if(c == '7') {
        cur_face = 7;
    }
    else if(c == '8') {
        cur_face = 8;
    }
    else if(c == '9') {
        cur_face = 9;
    }
}