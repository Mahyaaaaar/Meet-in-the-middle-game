#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
//#include <allegro5/allegro_audio.h>
//#include <allegro5/allegro_acodec.h>

//motaghayer haye bazi
int i, dice, win1, win2, Sw_shown_once, turn;
int Player11, Player12, Player21, Player22;
int LimitCard1, CloseCard1, x2Card1, AgainCard1;
int LimitCard2, CloseCard2, x2Card2, AgainCard2;
int Corr11, Corr12, Corr21, Corr22;
char gamestate[20];
int mousex, mousey;
bool ejaze;

//pieces first coordinate:
float xp21, xp22;
float yp21, yp22;
float xp11, xp12;
float yp11, yp12;

// coordinate of corridors
float xcorr1f, xcorr1e, ycorr1f, ycorr1e;
float xcorr2f, xcorr2e, ycorr2f, ycorr2e;

//Bitmaps
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
ALLEGRO_BITMAP * bitmap_corridor = NULL;
ALLEGRO_BITMAP * bitmap_closeask = NULL;
ALLEGRO_BITMAP * bitmap_asker2 = NULL;
ALLEGRO_BITMAP * bitmap_asker3 = NULL;
ALLEGRO_BITMAP * bitmap_asker4 = NULL;
ALLEGRO_BITMAP * bitmap_asklimit = NULL;
ALLEGRO_BITMAP * bitmap_which = NULL;
ALLEGRO_BITMAP * bitmap_info = NULL;


ALLEGRO_KEYBOARD_STATE ks;


void SaveGame() {

	FILE* updateFile;

	updateFile = fopen("savegame.txt", "wb");

	fprintf(updateFile, "%d\n", turn);

	fprintf(updateFile, "%d\n", Player11);

	fprintf(updateFile, "%d\n", Player12);

	fprintf(updateFile, "%d\n", Player21);

	fprintf(updateFile, "%d\n", Player22);

	fprintf(updateFile, "%d\n", LimitCard1);

	fprintf(updateFile, "%d\n", CloseCard1);

	fprintf(updateFile, "%d\n", x2Card1);

	fprintf(updateFile, "%d\n", AgainCard1);

	fprintf(updateFile, "%d\n", LimitCard2);

	fprintf(updateFile, "%d\n", CloseCard2);

	fprintf(updateFile, "%d\n", x2Card2);

	fprintf(updateFile, "%d\n", AgainCard2);

	fprintf(updateFile, "%d\n", Corr11);

	fprintf(updateFile, "%d\n", Corr12);

	fprintf(updateFile, "%d\n", Corr21);

	fprintf(updateFile, "%d\n", Corr22);



	fclose(updateFile);

}
void LoadGame() {

	FILE* inFile;

	inFile = fopen("savegame.txt", "r");

	fscanf(inFile, "%d\n", &turn);

	fscanf(inFile, "%d\n", &Player11);

	fscanf(inFile, "%d\n", &Player12);

	fscanf(inFile, "%d\n", &Player21);

	fscanf(inFile, "%d\n", &Player22);

	fscanf(inFile, "%d\n", &LimitCard1);

	fscanf(inFile, "%d\n", &CloseCard1);

	fscanf(inFile, "%d\n", &x2Card1);

	fscanf(inFile, "%d\n", &AgainCard1);

	fscanf(inFile, "%d\n", &LimitCard2);

	fscanf(inFile, "%d\n", &CloseCard2);

	fscanf(inFile, "%d\n", &x2Card2);

	fscanf(inFile, "%d\n", &AgainCard2);

	fscanf(inFile, "%d\n", &Corr11);

	fscanf(inFile, "%d\n", &Corr12);

	fscanf(inFile, "%d\n", &Corr21);

	fscanf(inFile, "%d\n", &Corr22);



	fclose(inFile);

}
void must_init(bool test, const char *description)
{
	if (test) return;

	printf("couldn't initialize %s\n", description);
	exit(1);
}
int evenchecker(int number) {//1 for even ....0 for odd
	if (number % 2 == 0) return 1;
	else return 0;

}
int suptaghsim(int number, int x) {
	if (number%x != 0) return number / x + 1;
	else	return number / x;
}
int random_number(int min_num, int max_num)//tabe digari baraye bedast avardan adad random
{
	int array[500];
	for (i = 0; i < 500; i++) {
		array[i] = rand() % (max_num - min_num);
		array[i] += min_num;
	}
	i = rand() % 500;
	return(array[i]);

	/*
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

	result = (a % (hi_num - low_num)) + low_num;*/
}
int DiceRand() {
	srand(time(0));
	int x, temp[500], j, k;
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

int corrcoordinate(int temp, float *x, float *y) { //finding corridor coordinate to apply graphics
												   ///////////
												   // corridor 1 first
	if (evenchecker(suptaghsim(temp, 9)) == 1) {
		if (temp % 9 != 0) *x = 748 - ((temp % 9) - 1) * 45.5;
		else *x = 757 - 8 * 45.7;
	}
	else
	{
		if (temp % 9 != 0) *x = 383 + ((temp % 9) - 1) * 45.5;
		else *x = 383 + 8 * 45.7;
	}
	*y = 453 - (suptaghsim(temp, 9) - 1) * 43.05;

}

void gm_defaults() {
	win1 = 0, win2 = 0, Sw_shown_once = 0, turn = 5;
	Player11 = 1, Player12 = 1, Player21 = 81, Player22 = 81;
	LimitCard1 = 1, CloseCard1 = 1, x2Card1 = 1, AgainCard1 = 1;
	LimitCard2 = 1, CloseCard2 = 1, x2Card2 = 1, AgainCard2 = 1;
	ejaze = false;
	//nasb rahro ha
	Corr11 = random_number(2, 40);
	Corr12 = random_number(42, 81);
	Corr21 = random_number(42, 81);
	Corr22 = random_number(2, 40);

	corrcoordinate(Corr11, &xcorr1f, &ycorr1f);
	corrcoordinate(Corr21, &xcorr2f, &ycorr2f);
	corrcoordinate(Corr12, &xcorr1e, &ycorr1e);
	corrcoordinate(Corr22, &xcorr2e, &ycorr2e);
	//pieces first coordinate:
	xp21 = 755, xp22 = 720;
	yp21 = 70, yp22 = 70;
	xp11 = 425, xp12 = 390;
	yp11 = 500, yp12 = 500;

}


void playercoordinates() {// finding the exact pieces position
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
	yp11 = 458 - (suptaghsim(Player11, 9) - 1) * 43.2;
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
	yp12 = 458 - (suptaghsim(Player12, 9) - 1) * 43.2;




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


	yp21 = 113 + (9 - suptaghsim(Player21, 9)) * 43.5;
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


	yp22 = 113 + (9 - suptaghsim(Player22, 9)) * 43.5;

}
void refreshboard() {
	///////////////////////////////////////////////////////////////////////////////////////////
	ALLEGRO_FONT* font1 = al_load_font("sanfrancisco.otf", 40, 0);
	playercoordinates();
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap(bitmap_board, 0, 0, 0);
	//applying players coordinates
	al_draw_bitmap(bitmap_player12, xp12, yp12, 0);
	al_draw_bitmap(bitmap_player11, xp11, yp11, 0);
	al_draw_bitmap(bitmap_player22, xp22, yp22, 0);
	al_draw_bitmap(bitmap_player21, xp21, yp21, 0);

	//corridors
	al_draw_bitmap(bitmap_corridor, xcorr1f, ycorr1f, 0);
	al_draw_bitmap(bitmap_corridor, xcorr1e, ycorr1e, 0);
	al_draw_bitmap(bitmap_corridor, xcorr2e, ycorr2e, 0);
	al_draw_bitmap(bitmap_corridor, xcorr2f, ycorr2f, 0);


	//al_draw_textf(font1, al_map_rgb(200, 200, 0), 0, 20, 20, "state= %s  dice %d ", gamestate, dice);
	Sw_shown_once = 1;

	al_flip_display();

}

void doingturn(int turn, int dice) { //turn1:11  turn2:12   turn3:21   turn4:22
	if (win1 == 0 && turn == 1) {
		Player11 += dice;
		if (Player11 < 1) {//yani az safhe nazane birun
			Player11 = 1;
		}
		else if (Player11 > 81) {
			Player11 = 81;
		}
		if (Player11 == 41)
			win1++;
		if (Player11 == Player21) {
			Player21 = 81;
		}
		else if (Player11 == Player22) {
			Player22 = 82;
		}
	}//Player11
	else if (win1 == 0 && turn == 2) {

		Player12 += dice;
		if (Player12 < 1) {//yani az safhe nazane birun
			Player12 = 1;
		}
		else if (Player12 > 81) {
			Player12 = 81;
		}
		if (Player12 == 41)
			win1++;
		if (Player12 == Player21) {
			Player21 = 82;
		}
		else if (Player12 == Player22) {
			Player22 = 82;
		}
	}//Player21
	else if (win2 == 0 && turn == 3) {//player 2 starting turn:

		Player21 -= dice;
		if (Player21 < 1) {//yani az safhe nazane birun
			Player21 = 1;
		}
		else if (Player21 > 81) {
			Player21 = 81;
		}
		if (Player21 == 41)			win2++;
		if (Player21 == Player11) {
			Player11 = 0;
		}
		else if (Player21 == Player12) {
			Player22 = 0;
		}
	}//Player21
	else if (turn == 4) {
		Player22 -= dice;
		if (Player22 < 1) {//yani az safhe nazane birun
			Player22 = 1;
		}
		else if (Player22 > 81) {
			Player22 = 81;
		}
		if (Player22 == 41)
			win2++;
		if (Player22 == Player11) {
			Player11 = 0;
		}
		else if (Player22 == Player12) {
			Player12 = 0;
		}
	}//Player22

}

int checkwinner() {
	if (win1 > 0) {
		strcpy(gamestate, "playerwon");
		return 1;
	}
	else if (win2 > 0) {
		strcpy(gamestate, "playerwon");
		return 2;
	}
	return 0;
}


void dicetoal(int dice) { //applying dice changes to allegro display

	time_t time1;
	time1 = time(NULL);
	ALLEGRO_FONT* font1 = al_create_builtin_font();
	if (dice == -1) al_draw_bitmap(bitmap_dice1, 130, 400, 0);
	else if (dice == -2) al_draw_bitmap(bitmap_dice2, 130, 400, 0);
	else if (dice == -3) al_draw_bitmap(bitmap_dice3, 130, 400, 0);
	else if (dice == 1) al_draw_bitmap(bitmap_dice4, 130, 400, 0);
	else if (dice == 2) al_draw_bitmap(bitmap_dice5, 130, 400, 0);
	else if (dice == 3) al_draw_bitmap(bitmap_dice6, 130, 400, 0);

	if (turn == 1 || turn == 2 || turn == 5) {
		al_draw_bitmap(bitmap_turn1, 30, 20, 0);
	}

	else if (turn == 3 || turn == 4 || turn == 6) {
		al_draw_bitmap(bitmap_turn2, 30, 20, 0);
	}
	if (turn == 1 || turn == 2 || turn == 5) {
		al_draw_text(font1, al_map_rgb(200, 160, 150), xp11, yp11, 20, "1");

		al_draw_text(font1, al_map_rgb(200, 160, 150), xp12, yp12, 20, "2");
	}
	if (turn == 3 || turn == 4 || turn == 6) {
		al_draw_text(font1, al_map_rgb(200, 160, 150), xp21, yp21, 20, "1");

		al_draw_text(font1, al_map_rgb(200, 160, 150), xp22, yp22, 20, "2");
	}
	if ((turn == 5 && x2Card1 > 0 && AgainCard1) || (turn == 6 && x2Card2 > 0 && AgainCard2 > 0)) al_draw_bitmap(bitmap_asker3, 80, 150, 0);//player has both cards
	else if ((turn == 5 && x2Card1 > 0) || (turn == 6 && x2Card2 > 0)) al_draw_bitmap(bitmap_asker2, 80, 150, 0);//player has just 2x card
	else if ((turn == 5 && AgainCard1) || (turn == 6 && AgainCard2 > 0)) al_draw_bitmap(bitmap_asker4, 80, 150, 0);//player has just again card
	else al_draw_bitmap(bitmap_asker, 80, 150, 0);//there is no card for player
	al_flip_display();
}

int closethedoor() {//applying close luckycard function
	if ((turn == 1 || turn == 2) && CloseCard1 > 0) {
		al_draw_bitmap(bitmap_closeask, 300, 100, 0);
		al_flip_display();
		while (1) {
			al_get_keyboard_state(&ks);
			if (al_key_down(&ks, ALLEGRO_KEY_Y)) {
				return 1;
				CloseCard1--;
			}
			else if (al_key_down(&ks, ALLEGRO_KEY_N))  return 0;
		}
	}
	if ((turn == 3 || turn == 4) && CloseCard2 > 0) {
		al_draw_bitmap(bitmap_closeask, 300, 100, 0);
		al_flip_display();
		while (1) {
			al_get_keyboard_state(&ks);
			if (al_key_down(&ks, ALLEGRO_KEY_Y)) {
				return 1;
				CloseCard2--;
			}
			else if (al_key_down(&ks, ALLEGRO_KEY_N))  return 0;
		}
	}
}
int limiter() {//aplying limit luckycard function   0:player not using limit card      1:the next turn has been cangee successfully
	ALLEGRO_FONT* font1 = al_create_builtin_font();
	if (((turn == 1 || turn == 2) && LimitCard1 > 0) || ((turn == 3 || turn == 4) && LimitCard2 > 0)) al_draw_bitmap(bitmap_asklimit, 80, 150, 0);
	al_flip_display();
	if (((turn == 1 || turn == 2) && LimitCard1 > 0) || ((turn == 3 || turn == 4) && LimitCard2 > 0)) {
		while (true) {
			al_get_keyboard_state(&ks);
			if (al_key_down(&ks, ALLEGRO_KEY_N)) return 0;
			else if (al_key_down(&ks, ALLEGRO_KEY_Y)) {
				al_draw_bitmap(bitmap_which, 80, 150, 0);
				if (turn == 3 || turn == 4) {
					al_draw_text(font1, al_map_rgb(200, 160, 150), xp11, yp11, 20, "1");
					al_draw_text(font1, al_map_rgb(200, 160, 150), xp12, yp12, 20, "2");
				}
				else if (turn == 1 || turn == 2) {
					al_draw_text(font1, al_map_rgb(200, 160, 150), xp21, yp21, 20, "1");
					al_draw_text(font1, al_map_rgb(200, 160, 150), xp22, yp22, 20, "2");
				}
				al_flip_display();
				while (true) {
					al_get_keyboard_state(&ks);
					if ((turn == 1 || turn == 2) && LimitCard1 > 0 && al_key_down(&ks, ALLEGRO_KEY_1)) {
						turn = 4;
						LimitCard1--;
						return 1;
					}
					else if ((turn == 1 || turn == 2) && LimitCard1 > 0 && al_key_down(&ks, ALLEGRO_KEY_2)) {
						turn = 3;
						LimitCard1--;
						return 1;
					}
					else if ((turn == 3 || turn == 4) && LimitCard2 > 0 && al_key_down(&ks, ALLEGRO_KEY_1)) {
						turn = 2;
						LimitCard2--;
						return 1;
					}
					else if ((turn == 3 || turn == 4) && LimitCard2 > 0 && al_key_down(&ks, ALLEGRO_KEY_2)) {
						turn = 1;
						LimitCard2--;
						return 1;
					}
				}
			}
		}
	}
}


int turner() {   //switching the turns(considering limitation)
	if (!limiter()) {//checking limit function
		if (turn == 1 || turn == 2) {
			turn = 6;
			strcpy(gamestate, "asking");
		}

		else if (turn == 3 || turn == 4) {
			turn = 5;
			strcpy(gamestate, "asking");
		}
	}
	return turn;
}
int turn_to_pl_name() {
	if (turn == 1) return &Player11;
	if (turn == 2) return &Player12;
	if (turn == 3) return &Player21;
	if (turn == 4) return &Player22;
}

void corridors(int *playerpos) {//applying corridor function if available
	// bug= agar karbar bere dakhel corridor va daste baad harkat nade
	// debugged..
	time_t time1;
	time1 = time(NULL);
	int a = random_number(1, 2);
	if (*playerpos == Corr11 || *playerpos == Corr22) {
		if (closethedoor() == 1) {
			refreshboard();
			return 0;
		}
		refreshboard();
		if (a == 1) *playerpos = Corr12;
		else *playerpos = Corr21;
		while (true) { if (time(NULL) - time1 > 1.5) break; }
	}
	else if (*playerpos == Corr21 || *playerpos == Corr12) {
		if (closethedoor() == 1) {
			refreshboard();
			return 0;
		}refreshboard();
		if (a == 1) *playerpos = Corr11;
		else *playerpos = Corr22;
		while (true) {
			if (time(NULL) - time1 > 1.5) break;
		}
	}
}

/*
void applyable_turn() {

	if (Player11 + dice < 1 && turn == 5 && Player12 + dice >= 1) turn = 2;
	else if (Player12 + dice < 1 && turn == 5 && Player11 + dice >= 1) turn = 1;

	else if (Player21 - dice > 81 && turn == 6 && Player22 - dice <= 81) turn = 4;
	else if (Player22 - dice > 81 && turn == 6 && Player21 - dice <= 81) turn = 3;
}
*/
void choosetoturn() {
	int sw_justonetime = 1;
	//applyable_turn();
	ALLEGRO_FONT* font = al_create_builtin_font();
	while (!strcmp(gamestate, "asking")) {
		al_get_keyboard_state(&ks);
		if (al_key_down(&ks, ALLEGRO_KEY_ESCAPE)) {
			strcpy(gamestate, "closing");
			break;
		}
		if (al_key_down(&ks, ALLEGRO_KEY_TAB) && (turn == 5 || turn == 1 || turn == 2) && AgainCard1 > 0) {
			AgainCard1--;
			break;
		}
		if (al_key_down(&ks, ALLEGRO_KEY_TAB) && (turn == 6 || turn == 3 || turn == 4) && AgainCard2 > 0) {
			AgainCard2--;
			break;
		}
		if ((al_key_down(&ks, ALLEGRO_KEY_LSHIFT) || al_key_down(&ks, ALLEGRO_KEY_RSHIFT)) && (turn == 6 || turn == 3 || turn == 4) && x2Card2 > 0 && sw_justonetime) {
			dice *= 2;
			sw_justonetime = 0;
			x2Card2--;
			al_draw_bitmap(bitmap_which, 80, 150, 0);
			al_flip_display();
		}
		else if ((al_key_down(&ks, ALLEGRO_KEY_LSHIFT) || al_key_down(&ks, ALLEGRO_KEY_RSHIFT)) && (turn == 5 || turn == 1 || turn == 2) && x2Card1 > 0 && sw_justonetime) {
			dice *= 2;
			sw_justonetime = 0;
			x2Card1--;
			al_draw_bitmap(bitmap_which, 80, 150, 0);
			al_flip_display();
		}
		if (turn == 5) {//which piece
			if (al_key_down(&ks, ALLEGRO_KEY_1)) {
				turn = 1;
				strcpy(gamestate, "gaming");
			}
			else if (al_key_down(&ks, ALLEGRO_KEY_2)) {
				turn = 2;
				strcpy(gamestate, "gaming");
			}
		}
		else if (turn == 6) {//which piece
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
	srand(time(NULL));
	gm_defaults();

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


	al_init_font_addon();

	al_init_ttf_addon();
	ALLEGRO_FONT* font = al_create_builtin_font();
	must_init(font, "font");
	ALLEGRO_FONT* font1 = al_load_font("arial.ttf", 25, 0);
	must_init(font, "font1");
	ALLEGRO_FONT* font2 = al_load_font("arial.ttf", 60, 0);
	must_init(font, "font2");


	//must_init(al_install_audio(), "audio");
	//must_init(al_init_acodec_addon(), "audio codecs");
	//must_init(al_reserve_samples(16), "reserve samples");
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
	bitmap_board = al_load_bitmap("boardexample.png");//the main game board
	bitmap_player11 = al_load_bitmap("orginal.blue.png");//pieces
	bitmap_player12 = bitmap_player11;
	bitmap_player21 = al_load_bitmap("orginal.red.png");
	bitmap_player22 = bitmap_player21;
	bitmap_dice1 = al_load_bitmap("minus1.png");//dice
	bitmap_dice2 = al_load_bitmap("minus2.png");
	bitmap_dice3 = al_load_bitmap("minus3.png");
	bitmap_dice4 = al_load_bitmap("plus1.png");
	bitmap_dice5 = al_load_bitmap("plus2.png");
	bitmap_dice6 = al_load_bitmap("plus3.png");
	bitmap_turn1 = al_load_bitmap("turn1.png");
	bitmap_turn2 = al_load_bitmap("turn2.png");
	bitmap_asker = al_load_bitmap("asker.png");
	bitmap_asker2 = al_load_bitmap("asker2.png");
	bitmap_asker3 = al_load_bitmap("asker3.png");
	bitmap_asker4 = al_load_bitmap("asker4.png");
	bitmap_closeask = al_load_bitmap("askclose.png");
	bitmap_corridor = al_load_bitmap("Corridor.png");
	bitmap_asklimit = al_load_bitmap("limitask.png");
	bitmap_which = al_load_bitmap("which.png");

	bitmap_info = al_load_bitmap("info.png");

	//checking sources:
	assert(bitmap_welcome != NULL);
	assert(bitmap_intro != NULL);
	assert(bitmap_menu != NULL);
	assert(bitmap_board != NULL);
	assert(bitmap_player11 != NULL);
	assert(bitmap_player22 != NULL);
	assert(bitmap_asker != NULL);
	assert(bitmap_asker2 != NULL);
	assert(bitmap_asker3 != NULL);
	assert(bitmap_asker4 != NULL);
	assert(bitmap_dice1 != NULL);
	assert(bitmap_dice2 != NULL);
	assert(bitmap_dice3 != NULL);
	assert(bitmap_dice4 != NULL);
	assert(bitmap_dice5 != NULL);
	assert(bitmap_dice6 != NULL);
	assert(bitmap_turn1 != NULL);
	assert(bitmap_turn2 != NULL);
	assert(bitmap_corridor != NULL);
	assert(bitmap_closeask != NULL);
	assert(bitmap_asklimit != NULL);
	assert(bitmap_which != NULL);
	assert(bitmap_info != NULL);

	time_t time1;
	time1 = time(NULL);

	bool done = false;
	bool redraw = true;


#define KEY_SEEN     1                      //setting up keyboard 
#define KEY_RELEASED 2

	unsigned char key[ALLEGRO_KEY_MAX];
	memset(key, 0, sizeof(key));
	ALLEGRO_EVENT event;

	int sw1 = 0, sw_gm_intro = 0, sw_gm_menu = 0;
	Sw_shown_once = 0;
	al_clear_to_color(al_map_rgb(200, 200, 0));
	strcpy(gamestate, "gameintro");
	al_draw_bitmap(bitmap_welcome, 0, 0, 0);                 //welcome & Game intro


	al_start_timer(timer);
	al_draw_textf(font1, al_map_rgb(200, 160, 150), 310, 500, 0, "Press 'Enter' to continue");
	al_flip_display();
	while (1) { if (time(NULL) - time1 >= 0.5) break; }





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

			if ((!strcmp(gamestate, "gaming") || !strcmp(gamestate, "asking")) && al_key_down(&ks, ALLEGRO_KEY_SPACE)) {//starting next player turn
				ejaze = true;
			}

			if (Sw_shown_once && ejaze) {//dice function applying
				dice = DiceRand();
				dicetoal(dice);
			}
			if (!strcmp(gamestate, "asking") && ejaze) {//asking player to move which mohre
				choosetoturn();
			}
			checkwinner();
			if (!strcmp(gamestate, "playerwon")) {//means that somebody won
				time1 = time(NULL);
				if (checkwinner() == 1)
				{
					al_clear_to_color(al_map_rgb(100, 100, 100));
					al_draw_text(font2, al_map_rgb(200, 200, 0), 20, 250, 20, "Congratulation Player 1!! , You WON!!");
					al_flip_display();
					while (time(NULL) - time1 < 3) {}
					strcpy(gamestate, "gamemenu");
				}
				else if (checkwinner() == 2)
				{
					al_clear_to_color(al_map_rgb(100, 100, 100));
					al_draw_text(font2, al_map_rgb(200, 200, 0), 20, 250, 20, "Congratulation Player 2!! , You WON!!");
					al_flip_display();
					while (time(NULL) - time1 < 3) {}
					strcpy(gamestate, "gamemenu");
				}
				gm_defaults();

			}
			if ((!strcmp(gamestate, "gaming")) && ejaze && Sw_shown_once) {//the main game logics


				doingturn(turn, dice);
				refreshboard();
				corridors(turn_to_pl_name());
				Sw_shown_once = 1;//eslah shavad!!!!!!!!!!!!!!!
				redraw = true;
				ejaze = false;
				turner();
				break;

			}
			if (!strcmp(gamestate, "loadgame")) {//loading game
				gm_defaults();
				LoadGame();

				corrcoordinate(Corr11, &xcorr1f, &ycorr1f);
				corrcoordinate(Corr21, &xcorr2f, &ycorr2f);
				corrcoordinate(Corr12, &xcorr1e, &ycorr1e);
				corrcoordinate(Corr22, &xcorr2e, &ycorr2e);
				strcpy(gamestate, "asking");
			}
			if (!strcmp(gamestate, "savegame")) {//saving game
				SaveGame();
				strcpy(gamestate, "gamemenu");
			}

			if (al_key_down(&ks, ALLEGRO_KEY_ESCAPE) || !strcmp(gamestate, "closing"))
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
			if (event.mouse.button & 1 && !strcmp(gamestate, "gamemenu") && mousey < 281 && mousey>245 && mousex > 55 && mousex < 285) {
				gm_defaults();
				strcpy(gamestate, "asking");
			}

			if (event.mouse.button & 1 && (!strcmp(gamestate, "gaming") || !strcmp(gamestate, "asking")) && mousey < 80 && mousey>20 && mousex > 820 && mousex < 870)strcpy(gamestate, "savegame");
			if (event.mouse.button & 1 && (!strcmp(gamestate, "gaming") || !strcmp(gamestate, "asking")) && mousey < 135 && mousey>90 && mousex > 820 && mousex < 870)strcpy(gamestate, "gamemenu");
			if (event.mouse.button & 1 && (!strcmp(gamestate, "gamemenu")) && mousey < 345 && mousey>315 && mousex > 53 && mousex < 300)strcpy(gamestate, "loadgame");
			if (event.mouse.button & 1 && (!strcmp(gamestate, "gamemenu")) && mousey < 470 && mousey>440 && mousex > 53 && mousex < 150) {
				time1 = time(NULL);
				al_draw_bitmap(bitmap_info, 0, 0, 0);
				al_flip_display();
				while (true) {
					if (time(NULL) - time1 > 6) break;
				}
			}
		}/*
		if ((!strcmp(gamestate, "gamemenu") || !strcmp(gamestate, "asking"))) {
			al_draw_textf(font, al_map_rgb(200, 200, 0), 20, 520, 20, "x= %d    y =%d", mousex, mousey);
			al_flip_display();
		}*/
		if (!strcmp(gamestate, "gamemenu"))//game menu
		{
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_bitmap(bitmap_menu, 0, 0, 0);
			time1 = time(NULL);
			//al_draw_text(font1, al_map_rgb(200, 200, 0), 20, 460, 20, "This is BETA version,The only available option is new game");
			al_flip_display();

		}
		if (redraw && al_is_event_queue_empty(queue) && (!strcmp(gamestate, "gaming") || !strcmp(gamestate, "asking"))) //game board
		{
			refreshboard();
		}

		if (done) break;

	}

	al_destroy_font(font);
	al_destroy_font(font1);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	al_destroy_bitmap(bitmap_welcome);
	al_destroy_bitmap(bitmap_intro);
	al_destroy_bitmap(bitmap_board);
	al_destroy_bitmap(bitmap_welcome);
	al_destroy_bitmap(bitmap_intro);
	al_destroy_bitmap(bitmap_menu);
	al_destroy_bitmap(bitmap_board);
	al_destroy_bitmap(bitmap_player11);
	al_destroy_bitmap(bitmap_player22);
	al_destroy_bitmap(bitmap_asker);
	al_destroy_bitmap(bitmap_asker2);
	al_destroy_bitmap(bitmap_asker3);
	al_destroy_bitmap(bitmap_asker4);
	al_destroy_bitmap(bitmap_dice1);
	al_destroy_bitmap(bitmap_dice2);
	al_destroy_bitmap(bitmap_dice3);
	al_destroy_bitmap(bitmap_dice4);
	al_destroy_bitmap(bitmap_dice5);
	al_destroy_bitmap(bitmap_dice6);
	al_destroy_bitmap(bitmap_turn1);
	al_destroy_bitmap(bitmap_turn2);
	al_destroy_bitmap(bitmap_corridor);
	al_destroy_bitmap(bitmap_closeask);
	al_destroy_bitmap(bitmap_asklimit);
	al_destroy_bitmap(bitmap_which);
	return 0;
}