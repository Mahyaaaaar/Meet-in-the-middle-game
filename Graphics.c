#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
//#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
//#include <allegro5/allegro_audio.h>
//#include <allegro5/allegro_acodec.h>

//motaghayer haye bazi
int i, j, dice, win1 = 0, win2 = 0, sw = 1, turn = 5;
int Player11 = 1, Player12 = 1, Player21 = 81, Player22 = 81;
int LimitCard, CloseCard, CoefCard, AgainCard;
int CorrFirst1, CorrEnd1, CorrFirst2, CorrEnd2;
char gamestate[20];
int mousex, mousey, x, y;
bool asked;


//mokhtasat avalie mohre ha:
float xp21 = 755, xp22 = 720;
float yp21 = 70, yp22 = 70;
float xp11 = 425, xp12 = 390;
float yp11 = 500, yp12 = 500;


ALLEGRO_BITMAP * bitmap_intro = NULL;
ALLEGRO_BITMAP * bitmap_welcome = NULL;
ALLEGRO_BITMAP * bitmap_menu = NULL;
ALLEGRO_BITMAP * bitmap_board = NULL;

ALLEGRO_BITMAP * bitmap_player11 = NULL;
ALLEGRO_BITMAP * bitmap_player12 = NULL;
ALLEGRO_BITMAP * bitmap_player21 = NULL;
ALLEGRO_BITMAP * bitmap_player22 = NULL;
ALLEGRO_BITMAP * bitmap_dice1 = NULL;
ALLEGRO_BITMAP * bitmap_dice2 = NULL;
ALLEGRO_BITMAP * bitmap_dice3 = NULL;
ALLEGRO_BITMAP * bitmap_dice4 = NULL;
ALLEGRO_BITMAP * bitmap_dice5 = NULL;
ALLEGRO_BITMAP * bitmap_dice6 = NULL;

ALLEGRO_BITMAP * bitmap_turn2 = NULL;
ALLEGRO_BITMAP * bitmap_turn1 = NULL;
ALLEGRO_BITMAP * bitmap_asker = NULL;


ALLEGRO_KEYBOARD_STATE ks;



void must_init(bool test, const char *description)
{
	if (test) return;

	printf("couldn't initialize %s\n", description);
	exit(1);
}




int DiceRand() {
	int x, temp[500], j, k;
	//srand(time(NULL));

	for (int i = 0; i < 500; i++) {
		temp[i] = rand() % 6 - 2;
		if (temp[i] == 0) temp[i] = (-3);
	}
	j = rand() % 500;
	k = rand() % 500;
	if (temp[j] > temp[k]) {
		return temp[j];
	}
	else return temp[k];
}

int suptaghsim(int number, int x) {
	if (number%x != 0) return number / x + 1;
	else	return number / x;
}




int random_number(int min_num, int max_num)//tabe digari baraye bedast avardan adad random
{
	int result = 0, low_num = 0, hi_num = 0;

	if (min_num < max_num)
	{
		low_num = min_num;
		hi_num = max_num + 1; // include max_num in output
	}
	else {
		low_num = max_num + 1; // include max_num in output
		hi_num = min_num;
	}

	srand(time(NULL));
	result = (rand() % (hi_num - low_num)) + low_num;
	return result;
}

void doingturn(int turn, int dice) { //turn1:11  turn2:12   turn3:21   turn4:22
	if (win1 == 0 && turn == 1) {
		Player11 += dice;
		if (Player11 < 1 || Player11>81) {//yani az safhe nazane birun
			Player11 -= dice;
		}
		if (Player11 == 41)
			win1++;
		if (Player11 == Player21) {
			Player21 = 81;
			printf("Player11 Hit Player21\n");
		}
		else if (Player11 == Player22) {
			Player22 = 82;
			printf("Player11 Hit Player22\n");
		}
	}//Player11
	else if (win1 == 0 && turn == 2) {

		Player12 += dice;//porseshe kodam mohre anjam nashod!!
		if (Player12 < 1 || Player12>81) {
			Player12 -= dice;
		}
		if (Player12 == 41)
			win1++;
		if (Player12 == Player21) {
			Player21 = 82;
			printf("Player12 Hit Player21\n");
		}
		else if (Player12 == Player22) {
			Player22 = 82;
			printf("Player12 Hit Player22\n");
		}
	}//Player21
	else if (win2 == 0 && turn == 3) {//player 2 starting turn:

		Player21 -= dice;//porseshe kodam mohre anjam nashod!!
		if (Player21 < 1 || Player21>81) {
			Player21 += dice;
		}
		if (Player21 == 41)			win2++;
		if (Player21 == Player11) {
			Player11 = 0;
			printf("Player21 Hit Player11\n");
		}
		else if (Player21 == Player12) {
			Player22 = 0;
			printf("Player21 Hit Player12\n");
		}
	}//Player21
	else if (turn == 4) {
		Player22 -= dice;//porseshe kodam mohre anjam nashod!!
		if (Player22 < 1 || Player22>81) {
			Player22 += dice;
		}
		if (Player22 == 41)
			win2++;
		if (Player22 == Player11) {
			Player11 = 0;
			printf("Player22 Hit Player11\n");
		}
		else if (Player22 == Player12) {
			Player12 = 0;
			printf("Player22 Hit Player12\n");
		}
	}//Player22

}





void dicetoal(int dice) { //applying dice changes to allegro display

	time_t time1;
	time1 = time(NULL);
	if (dice == -1) al_draw_bitmap(bitmap_dice1, 150, 300, 0);
	else if (dice == -2) al_draw_bitmap(bitmap_dice2, 150, 300, 0);
	else if (dice == -3) al_draw_bitmap(bitmap_dice3, 150, 300, 0);
	else if (dice == 1) al_draw_bitmap(bitmap_dice4, 150, 300, 0);
	else if (dice == 2) al_draw_bitmap(bitmap_dice5, 150, 300, 0);
	else if (dice == 3) al_draw_bitmap(bitmap_dice6, 150, 300, 0);

	if (turn == 1) {
		al_draw_bitmap(bitmap_turn1, 20, 20, 0);
	}

	else if (turn == 3) {
		al_draw_bitmap(bitmap_turn2, 20, 20, 0);
	}
	al_flip_display();
	while (1) { if (time(NULL) - time1 >= 2) break; }
}




int turner() {   //switching the turns
	if (turn == 1 || turn == 2) {
		turn = 6;
	}

	else if (turn == 3 || turn == 4) {
		turn = 5;
	}
	return turn;
}
int evenchecker(int number) {//1 for even ....0 for odd
	if (number % 2 == 0) return 1;
	else return 0;

}
void playercoordinates() {
	//p11
	if (evenchecker(suptaghsim(Player11, 9)) == 1) {
		if (Player11 % 9 != 0) xp11 = 757 - ((Player11 % 9) - 1) * 45.7;
		else xp11 = 757 - 8 * 45.7;
	}
	else
	{
		if (Player11 % 9 != 0) xp11 = 390 + ((Player11 % 9) - 1) * 45.7;
		else xp11 = 390 + 8 * 45.7;
	}
	yp11 = 458 - (suptaghsim(Player11, 9) - 1) * 45.7;
	//p12
	if (evenchecker(suptaghsim(Player12, 9)) == 1) {
		if (Player12 % 9 != 0) xp12 = 757 - ((Player12 % 9) - 1) * 45.7;
		else xp12 = 757 - 8 * 45.7;
	}
	else
	{
		if (Player12 % 9 != 0) xp12 = 390 + ((Player12 % 9) - 1) * 45.7;
		else xp12 = 390 + 8 * 45.7;
	}
	yp12 = 458 - (suptaghsim(Player12, 9) - 1) * 45.7;




	//p21
	if (evenchecker(suptaghsim(Player21, 9)) == 0) {
		if (Player21 % 9 != 0) xp21 = 757 - (9 - (Player21 % 9)) * 45.7;
		else xp21 = 757;
	}
	else
	{
		if (Player21 % 9 != 0) xp21 = 390 + (9 - (Player21 % 9)) * 45.7;
		else xp21 = 390;
	}


	yp21 = 113 + (9 - suptaghsim(Player21, 9)) * 45.7;
	//p22
	if (evenchecker(suptaghsim(Player22, 9)) == 0) {
		if (Player22 % 9 != 0) xp22 = 757 - (9 - (Player22 % 9)) * 45.7;
		else xp22 = 757;
	}
	else
	{
		if (Player22 % 9 != 0) xp22 = 390 + (9 - (Player22 % 9)) * 45.7;
		else xp22 = 390;
	}


	yp22 = 113 + (9 - suptaghsim(Player22, 9)) * 45.7;

}
/*
void choosetoturn() {//ask player which object to move using mouse

	time_t time1;
	time1 = time(NULL);
	al_load_bitmap(bitmap_asker, 50, 300, 0);
	al_flip_display();
	while (1) { if (time(NULL) - time1 >= 2) break; }
	if (turn == 1) {
		if ((x - xp11 < 80 && y - yp11 < 80) || (x - xp11 > -80 && y - yp11 > -80)) turn = 1;
		else if ((x - xp12 < 80 && y - yp12 < 80) || (x - xp12 > -80 && y - yp12 > -80)) turn = 2;
	}
	else if (turn == 3) {
		if ((x - xp21 < 80 && y - yp21 < 80) || (x - xp21 > -80 && y - yp21 > -80)) turn = 3;
		else if ((x - xp22 < 80 && y - yp22 < 80) || (x - xp22 > -80 && y - yp22 > -80)) turn = 4;
	}
	//strcpy(gamestate, "gaming");
}*/
void choosetoturn() {
	while (!strcmp(gamestate, "asking")) {
		//printf("in choose to turn function   %d\n ",turn);
		al_get_keyboard_state(&ks);
		if (al_key_down(&ks, ALLEGRO_KEY_ESCAPE)) strcpy(gamestate, "closing");
		if (turn == 5) {
			if (al_key_down(&ks, ALLEGRO_KEY_1)) {
				turn = 1;
				strcpy(gamestate, "gaming");
			}
			else if (al_key_down(&ks, ALLEGRO_KEY_2)) {
				turn = 2;
				strcpy(gamestate, "gaming");
			}
		}
		else if (turn == 6) {
			if (al_key_down(&ks, ALLEGRO_KEY_1)) {
				turn = 3;
				strcpy(gamestate, "gaming");
			}
			else if (al_key_down(&ks, ALLEGRO_KEY_2)) {
				turn = 4;
				strcpy(gamestate, "gaming");
			}
		}
	}
}


int main()
{



	CorrFirst1 = random_number(1, 40);//nasb rahro ha
	CorrEnd1 = random_number(81, 42);
	CorrFirst2 = random_number(81, 42);
	CorrEnd2 = random_number(1, 40);
	//end*/

	must_init(al_init(), "allegro");
	must_init(al_install_keyboard(), "keyboard");

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
	must_init(timer, "timer");

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	must_init(queue, "queue");

	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

	ALLEGRO_DISPLAY* disp = al_create_display(900, 600);
	must_init(disp, "display");

	ALLEGRO_FONT* font = al_create_builtin_font();
	must_init(font, "font");


	//must_init(al_install_audio(), "audio");
	//must_init(al_init_acodec_addon(), "audio codecs");
	//must_init(al_reserve_samples(16), "reserve samples");
	//must_init(al_init_primitives_addon(), "primitives");
	must_init(al_init_image_addon(), "images");
	must_init(al_install_mouse(), "mouse");

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	//loading images:
	al_init_image_addon();
	bitmap_intro = al_load_bitmap("1start.mit.png");
	bitmap_welcome = al_load_bitmap("start.welcome.png");
	bitmap_menu = al_load_bitmap("menu.jpg");
	bitmap_board = al_load_bitmap("boardexample.png");
	bitmap_player11 = al_load_bitmap("orginal.blue.png");
	bitmap_player12 = bitmap_player11;
	bitmap_player21 = al_load_bitmap("orginal.red.png");
	bitmap_player22 = bitmap_player21;
	bitmap_dice1 = al_load_bitmap("minus1.png");
	bitmap_dice2 = al_load_bitmap("minus2.png");
	bitmap_dice3 = al_load_bitmap("minus3.png");
	bitmap_dice4 = al_load_bitmap("plus1.png");
	bitmap_dice5 = al_load_bitmap("plus2.png");
	bitmap_dice6 = al_load_bitmap("plus3.png");
	bitmap_turn1 = al_load_bitmap("turn1.png");
	bitmap_turn2 = al_load_bitmap("turn2.png");

	bitmap_asker = al_load_bitmap("asker.png");

	//checking sources:
	assert(bitmap_welcome != NULL);
	assert(bitmap_intro != NULL);
	assert(bitmap_menu != NULL);
	assert(bitmap_board != NULL);
	assert(bitmap_player11 != NULL);
	assert(bitmap_player22 != NULL);
	assert(bitmap_asker != NULL);
	assert(bitmap_dice1 != NULL);
	assert(bitmap_dice2 != NULL);
	assert(bitmap_dice3 != NULL);
	assert(bitmap_dice4 != NULL);
	assert(bitmap_dice5 != NULL);
	assert(bitmap_dice6 != NULL);
	assert(bitmap_turn1 != NULL);
	assert(bitmap_turn2 != NULL);

	time_t time1;
	time1 = time(NULL);

	bool done = false;
	bool redraw = true;


#define KEY_SEEN     1                      //setting up keyboard 
#define KEY_RELEASED 2

	unsigned char key[ALLEGRO_KEY_MAX];
	memset(key, 0, sizeof(key));
	ALLEGRO_EVENT event;

	int sw1 = 0, sw_gm_intro = 0, sw_gm_menu = 0, sw2 = 0;

	al_clear_to_color(al_map_rgb(200, 200, 0));
	strcpy(gamestate, "gameintro");
	al_draw_bitmap(bitmap_welcome, 0, 0, 0);                 //welcome & Game intro
	al_flip_display();

	al_start_timer(timer);
	while (1) { if (time(NULL) - time1 >= 2) break; }

	al_draw_text(font, al_map_rgb(20, 400, 0), 420, 500, 20, "PRESS Enter to continue");

	bool ejaze = false;

	al_wait_for_event(queue, &event);
	mousex = event.mouse.x;
	mousey = event.mouse.y;
	while (1)
	{
		al_wait_for_event(queue, &event);
		switch (event.type)
		{

		case ALLEGRO_EVENT_KEY_CHAR:
			//if (event.keyboard.keycode != ALLEGRO_KEY_ENTER) sw1 = 1;


			//if (!strcmp(gamestate, "gaming") && event.keyboard.keycode != ALLEGRO_KEY_SPACE) ejaze = true; ;
		case ALLEGRO_EVENT_TIMER:

			// game logic goes here:
			al_get_keyboard_state(&ks);

			if (!strcmp(gamestate, "gameintro") && al_key_down(&ks, ALLEGRO_KEY_ENTER)) strcpy(gamestate, "gamemenu");

			if ((!strcmp(gamestate, "gaming")|| !strcmp(gamestate, "asking")) && al_key_down(&ks, ALLEGRO_KEY_SPACE)) {
				ejaze = true;
			}

			if (!strcmp(gamestate, "asking") && sw2 &&ejaze) {
				dice = DiceRand();
				printf("hi dice is %d", dice);
				dicetoal(dice);
			}
			if (!strcmp(gamestate, "asking") && sw2 && ejaze) {
				printf("going in choose to turn func");
				choosetoturn();
				printf("getting out of choose to turn func");
			}

			if ((!strcmp(gamestate, "gaming")) && ejaze&&sw2) {


				doingturn(turn, dice);
				sw2 = 1;//eslah shavad!!!!!!!!!!!!!!!
				redraw = true;
				ejaze = false;
				turner();
				strcpy(gamestate, "asking");
				break;

			}

			if (al_key_down(&ks, ALLEGRO_KEY_ESCAPE)||!strcmp(gamestate,"closing"))
				done = true;
		case ALLEGRO_EVENT_KEY_DOWN:
			key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
			break;
		case ALLEGRO_EVENT_KEY_UP:
			key[event.keyboard.keycode] &= KEY_RELEASED;
			break;

		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			done = true;
			break;
		case ALLEGRO_EVENT_MOUSE_AXES:
			mousex = event.mouse.x;
			mousey = event.mouse.y;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			if (event.mouse.button & 1 && !strcmp(gamestate, "gamemenu") && mousey < 281 && mousey>245 && mousex > 55 && mousex < 285) strcpy(gamestate, "asking");
			/*
			if (event.mouse.button & 1 && !strcmp(gamestate, "asking")) {
				x = mousex;
				y = mousey;
				strcpy(gamestate, "gaming");
				printf("HIIIIIIIIII");
			}*/
		}


		if (al_is_event_queue_empty(queue) && !strcmp(gamestate, "gamemenu"))//game menu
		{
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_bitmap(bitmap_menu, 0, 0, 0);
			time1 = time(NULL);
			al_draw_text(font, al_map_rgb(200, 200, 0), 20, 460, 20, "This is BETA version,so you'll be redirected \n to the GAME BOARD");
			al_flip_display();
			//while (1) { if (time(NULL) - time1 >= 2) break; }
			//strcpy(gamestate, "gaming");// bayad sharte entekhabe mode ro bezarim
			//if (event.mouse.button & 1) strcpy(gamestate, "gaming");

		}
		if (redraw && al_is_event_queue_empty(queue) && (!strcmp(gamestate, "gaming") || !strcmp(gamestate, "asking"))) //game board
		{
			playercoordinates();
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_bitmap(bitmap_board, 0, 0, 0);
			//applying players coordinates
			al_draw_bitmap(bitmap_player12, xp12, yp12, 0);
			al_draw_bitmap(bitmap_player11, xp11, yp11, 0);
			al_draw_bitmap(bitmap_player22, xp22, yp22, 0);
			al_draw_bitmap(bitmap_player21, xp21, yp21, 0);

			al_load_bitmap(bitmap_asker, 0, 0, 0);
			al_draw_textf(font, al_map_rgb(200, 200, 0), 20, 200, 20, "x21= %f     y21= %f   player21= %d", xp21, yp21, Player21);
			al_draw_textf(font, al_map_rgb(200, 200, 0), 20, 230, 20, "x11= %f     y11= %f   player11= %d", xp11, yp11, Player11);
			al_draw_textf(font, al_map_rgb(200, 200, 0), 20, 250, 20, "x=%d     y=%d", x, y);

			al_draw_textf(font, al_map_rgb(200, 200, 0), 0, 20, 20, "state= %s  dice %d ", gamestate, dice);
			//al_draw_textf(font, al_map_rgb(200, 200, 0), 0, 50, 20, "turn= %d ", turn);
		//	al_draw_textf(font, al_map_rgb(200, 200, 0), 120, 430, 20, "mouse x:%d mouse y:%d", mousex, mousey);
			sw2 = 1;

			al_flip_display();
		}
		if (redraw && al_is_event_queue_empty(queue) && (!strcmp(gamestate, "gaming") || !strcmp(gamestate, "asking"))) {
			// printing how game is going on
			printf("player11=%d player12=%d player21=%d player22=%d \n", Player11, Player12, Player21, Player22);
			printf("dice = %d    turn=%d    state=%s\n", dice, turn,gamestate);
			printf("end\n\n");
		}

		if (done)
			break;

	}

	al_destroy_font(font);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	al_destroy_bitmap(bitmap_welcome);
	al_destroy_bitmap(bitmap_intro);
	al_destroy_bitmap(bitmap_board);
	return 0;
}