// main.cpp
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <algorithm>
#include <fstream>
#include <windows.h>
#include <sstream>
#include "functs.cpp"
#include <iostream>
#include "objects.cpp"
#include <chrono>



using namespace std;

int getrandom() {
	return rand() % 4;
}


struct audio {
	sf::Sound music;
	vector<double> keys;

	audio(sf::Sound a, vector<double> v) {
		music = a;
		keys = v;
	}
};

sf::Sprite arrows_coord(Arrow a, sf::Sprite this_arrow) {
	this_arrow.setTextureRect(sf::IntRect(a.get_number() * 71, a.get_status() * 71, 71, 71));
	this_arrow.setPosition(a.getsprite().getPosition());
	return this_arrow;
}

//struct score_txt{
//	sf::Text score_text;
//	int 
//
//};





int main()
{

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "wizardance", sf::Style::Fullscreen);
	window.setFramerateLimit(60);
	sf::RectangleShape line(sf::Vector2f(4000, 5));
	line.setPosition(-10, 700);

	int wwightx = 1920;
	int wwighty = 1080;


	sf::Event event;

	sf::Font font;
	font.loadFromFile("assets/fonts/arcade.TTF");


	//boombox

	sf::Sprite boombox;;

	vector<string> b_textures_string = { "assets/textures/boombox.png", "assets/textures/boombox1.png", "assets/textures/boombox2.png" };

	vector<sf::Texture> boombox_texture(b_textures_string.size());

	for (int i = 0; i < boombox_texture.size(); i++) {
		boombox_texture[i].loadFromFile(b_textures_string[i]);
	}


	boombox.setTexture(boombox_texture[0]);

	boombox.setScale(0.3, 0.3);

	boombox.setPosition(wwightx / 2 - boombox.getGlobalBounds().width / 2, 700 - boombox.getGlobalBounds().height + 20);


	//факелы

	sf::Sprite torch1, torch2;
	//sf::Texture torch_texture;


	//torch_texture.loadFromFile("assets/textures/torch.png");
	vector<string> t_textures_string = { "assets/textures/torch.png", "assets/textures/torch2.png", "assets/textures/torch3.png" };

	
	vector<sf::Texture> torch_texture(t_textures_string.size());
	for (int i = 0; i < torch_texture.size(); i++) {
		torch_texture[i].loadFromFile(t_textures_string[i]);
	}
		


	torch1.setTexture(torch_texture[0]);
	torch2.setTexture(torch_texture[1]);


	torch1.setScale(0.2, 0.2);
	torch2.setScale(0.2, 0.2);

	torch1.setPosition(300, 350);
	torch2.setPosition(wwightx - 300 - torch2.getGlobalBounds().width, 350);


	Functs cur_functs;
	//for(int i = 0; i < 100; i++ )
	//	cout << cur_functs.getrandom();



	//vector<sf::Vector2f> stringp2;
	//for (int i = 0; i < 3; i++) {
	//	sf::Vector2f v(71, 71 * (i + 1));
	//	stringp2.push_back(v);
	//}

	string stringp1 = "wasd";


	sf::Text t1;
	t1.setFont(font);
	//t1.setString("w");
	t1.setCharacterSize(71);

	sf::Texture t2_texture_arrows;

	//vector<sf::Color> colors = {sf::Color::Magenta};



	t2_texture_arrows.loadFromFile("assets/textures/arrows.png");


	sf::Sprite arrow_sign;
	arrow_sign.setTexture(t2_texture_arrows);



	//sf::Sprite t2_not_pressed;
	//sf::Texture t2_texture;
	//t2_texture.loadFromFile("p2_arrows.png");
	//t2_not_pressed.setTexture(t2_texture);

	//sf::Sprite t2_correct;
	//sf::Texture t2_texture_correct;
	//t2_texture_correct.loadFromFile("p2_arrows_correct.png");
	//t2_correct.setTexture(t2_texture_correct);

	//sf::Sprite t2_miss;
	//sf::Texture t2_texture_miss;
	//t2_texture_miss.loadFromFile("p2_arrows_miss.png");
	//t2_miss.setTexture(t2_texture_miss);

	

	//sf::Text t2;
	//t2.setFont(font);
	//t2.setString("w");
	//t2.setCharacterSize(71);


	//a.settext(font, "W");
	//a.set_speed(speed);
	//a.setxy(500, 500);

	//сканеры------------------------------------------------------------------

	sf::Sprite rp1;
	sf::Texture rp1_texture, rp1_clicked_texture, rp2_clicked_texture;
	rp1_texture.loadFromFile("assets/textures/optic_white.png");
	rp1.setTexture(rp1_texture);


	int wxleft = window.getPosition().x;
	int wyleft = window.getPosition().y;

	int wyright = 0;
	int wxright = wwightx;


	rp1.setPosition(wxleft + 150, wyleft + 210);
	rp1_clicked_texture.loadFromFile("assets/textures/optic_purple.png");
	rp2_clicked_texture.loadFromFile("assets/textures/optic_yellow.png");


	//sf::RectangleShape rp2(sf::Vector2f(71, 71));
	//rp2.setFillColor(sf::Color::White);
	//rp2.setPosition(1650, 200);

	sf::Sprite rp2;
	//sf::Texture rp1_texture;
	//rp1_texture.loadFromFile("assets/textures/the_eye.png");
	rp2.setTexture(rp1_texture);
	rp2.setPosition(wxright - rp1.getPosition().x - 50, wyright + 210);

	//текст для сканеров-----------------------------------------------------


	vector<string> accuracy_text = {"bad", "okay", "good", "perfect", "miss"};

	//sf::Text accuracy1;
	//accuracy1.setFont(font);
	//accuracy1.setCharacterSize(50);
	//accuracy1.setPosition(sf::Vector2f(rp1.getGlobalBounds().left - 50, rp1.getGlobalBounds().top));

	
	sf::Text accuracy2;
	accuracy2.setFont(font);
	accuracy2.setCharacterSize(50);
	accuracy2.setPosition(sf::Vector2f(rp2.getGlobalBounds().width - 50, rp2.getGlobalBounds().top));

	vector<sf::Text>accuracy1_vector;
	vector<sf::Text>accuracy2_vector;


	//игрок 1--------------------------------------------------------

	int skin1_timer = 0;
	sf::Sprite player1;
	sf::Texture player1_texture, player1_dance, player1_attack;
	player1_texture.loadFromFile("assets/textures/purplewizard.png");
	player1_attack.loadFromFile("assets/textures/purpleattack.png");
	player1.setTexture(player1_texture);
	player1_dance.loadFromFile("assets/textures/purpledance.png");
	player1.setPosition(rp1.getPosition().x + 50, rp1.getPosition().y);
	player1.setScale(0.7, 0.7);
	bool is_purple_dance = false;

	//игрок 2-------------------------------------------------------------------

	int skin2_timer = 0;
	sf::Sprite player2;
	sf::Texture player2_texture, player2_dance, player2_attack;
	player2_texture.loadFromFile("assets/textures/yellowwizard.png");
	player2_attack.loadFromFile("assets/textures/yellowattack.png");

	player2.setTexture(player2_texture);
	player2_dance.loadFromFile("assets/textures/yellowdance.png");
	//player2.setPosition(wxright - 200, wyright - 500);
	bool is_yellow_dance = false;
	player2.setScale(0.7, 0.7);
	player2.setPosition(rp2.getPosition().x + 50 - player2.getGlobalBounds().width, rp2.getPosition().y);

	//win----------------------------------------------
	short win = 0;
	sf::RectangleShape p2_win(sf::Vector2f(1150, 298));
	p2_win.setFillColor(sf::Color::Yellow);
	p2_win.setPosition(-68, player2.getGlobalBounds().top + 181);


	sf::RectangleShape p1_win(sf::Vector2f(1150, 298));
	p1_win.setFillColor(sf::Color::Magenta);
	p1_win.setPosition(player1.getGlobalBounds().left + player1.getGlobalBounds().width, player1.getGlobalBounds().top + 181);

	sf::Text draw_text;
	draw_text.setFont(font);
	draw_text.setString("Draw!");
	draw_text.setCharacterSize(200);
	draw_text.setPosition(wwightx / 2 - draw_text.getGlobalBounds().width / 2, 700 - draw_text.getGlobalBounds().height - 300);

	sf::Text win_text;
	win_text.setFont(font);
	win_text.setFillColor(sf::Color::Black);
	win_text.setCharacterSize(150);




	//cout << rp2.getTextureRect().width;

	//---------------------------------------------------------------------


	//меню----------------------------------------------------------------------

	sf::RectangleShape menu_phone(sf::Vector2f(wwightx, wwighty));
	menu_phone.setFillColor(sf::Color::Black);
	window.draw(menu_phone);
	sf::Texture title_texture;
	title_texture.loadFromFile("assets/textures/title.png");
	sf::Sprite menu_title;
	menu_title.setTexture(title_texture);
	menu_title.setPosition(sf::Vector2f(wwightx / 2 - menu_title.getGlobalBounds().width / 2, 200));

	sf::Sound menutheme;
	sf::SoundBuffer menubuf;
	menubuf.loadFromFile("assets/music/menu_theme.wav");
	menutheme.setBuffer(menubuf);


	sf::Sound start_sound;
	sf::SoundBuffer start_sound_buf;
	start_sound_buf.loadFromFile("assets/music/start_sound.wav");
	start_sound.setBuffer(start_sound_buf);
	start_sound.setVolume(200);


	sf::Text menu_text;
	menu_text.setFont(font);
	menu_text.setString("Press any key");
	menu_text.setCharacterSize(60);
	int menu_text_animation = 0;
	menu_text.setPosition(sf::Vector2f(wwightx / 2 - menu_text.getGlobalBounds().width / 2, 600));


	bool is_menu = true;



	//звуки--------------------------------------------------------------------

	//sf::SoundBuffer hit_buffer;
	//sf::Sound hit;
	//hit_buffer.loadFromFile("assets/music/hit.wav");
	//hit.setBuffer(hit_buffer);
	//hit.setVolume(30);



	sf::SoundBuffer countbuf;
	sf::Sound count;
	countbuf.loadFromFile("assets/music/count.wav");
	count.setBuffer(countbuf);

	sf::SoundBuffer beginbuf;
	sf::Sound beginsound;
	beginbuf.loadFromFile("assets/music/begin.wav");
	beginsound.setBuffer(beginbuf);
	beginsound.setVolume(30);

	//музыка----------------------------------------------------------------------------


	sf::SoundBuffer buffer;
	buffer.loadFromFile("assets/music/crimewave.wav");
	sf::Sound snd;
	snd.setBuffer(buffer);
	int start_music = 8 * 60;

	int spawn = 110;


	vector<double> crimewave = {0.06, 0.3, 0.816, 1.561, 1.68, 2.059, 2.554, 2.801, 3.305, 3.553, 4.050, 4.548, 4.821, 6.037, 6.291, 6.536, 6.819,
		7.17, 7.52, 8.021, 8.767, 8.975, 9.409, 9.648, 10.10, 10.506, 10.987, 11.502, 12, 12.991, 13.489, 13.756, 14.244, 14.499, 14.975, 
		15.23, 15.479, 15.728, 15.97, 16.221, 16.714, 17.218, 17.473, 17.952, 18.45, 18.705, 19.196, 19.457, 19.942, 20.445, 20.704, 21.939,
		22.305, 22.577, 22.718, 23.433, 23.923, 24.733, 25.174, 25.528, 25.914, 26.41, 26.906, 27.402, 27.893, 28.897, 29.394, 29.664, 30.154,
		30.407, 30.888, 31.133, 31.376, 31.631, 31.874, 32.616, 33.115, 33.371, 33.864, 34.357, 34.621, 35.102, 35.362, 35.854, 37.843, 38.119,
		38.355, 38.614, 38.839, 39.333, 39.822, 40.569, 41.061, 41.444, 41.818, 42.307, 42.803, 43.292, 43.797, 44.789, 45.29, 45.576, 46.048,
		46.293, 47.044, 47.274, 47.521, 47.781, 48.015, 48.513, 49.018, 49.272, 49.76, 50.284, 50.524, 51.007, 51.267, 51.754, 52.251, 52.518,
		52.787, 53.744, 54, 54.271, 54.514, 54.724, 55.224, 55.721, 56.473, 56.953, 57.347, 57.713, 58.205, 58.709, 59.204, 59.7, 60.698, 61.195,
		61.463, 61.955, 62.189, 62.687, 62.939, 63.185, 63.437, 63.810, 64.183, 64.459, 64.674, 64.949, 65.299, 65.803, 66.172, 66.541,
		66.915, 67.285, 67.909, 68.282, 68.666, 68.902, 69.274, 69.775, 70.145, 70.519, 70.89, 71.263, 71.766, 72.131, 72.614, 72.998, 73.252, 
		73.752, 74.124, 74.623, 75.238, 75.85, 76.236, 76.612, 76.848, 77.221, 77.727, 78.1, 78.602, 78.975, 79.217, 79.59, 79.957, 80.393, 
		81.066, 81.443, 81.708, 82.557, 83.061, 83.321, 83.687, 84.060, 84.429, 84.686, 85.176, 85.547, 85.809, 86.178, 86.419, 
		86.798, 87.042, 87.287, 87.54, 87.792, 88.313, 88.786, 89.018, 89.31, 89.777, 90.154, 90.396, 90.552, 90.771, 91.012, 91.265,
		91.407, 91.634, 92.019, 92.383, 92.635, 92.89, 93.255, 93.619, 93.882, 94.133, 94.375, 94.504, 94.748, 94.993, 95.376, 95.746, 95.992, 
		96.125, 96.365, 96.62, 96.992, 97.359, 97.857, 98.109, 98.358, 98.689, 98.969, 99.221, 99.596, 99.972, 100.216, 100.585, 100.831, 101.080,
		101.367, 101.842, 102.208, 102.454, 102.706, 102.957, 103.439, 103.692, 104.191, 104.691, 104.939, 105.423, 105.927, 106.188, 106.668,
		106.931, 107.425, 107.912, 108.162, 109.404, 109.662, 109.917, 110.158, 110.399, 110.902, 111.401, 112.141, 112.631, 113.012, 113.383,
		113.881, 114.373, 114.874, 115.369, 116.366, 116.865, 117.114, 117.61, 117.856, 118.348, 118.604, 118.847, 119.095, 119.35, 119.599,
		120.093, 120.596, 120.844, 121.333, 121.859, 122.106, 122.579, 122.837, 123.317, 123.83, 124.094, 124.362, 125.318, 125.572, 125.844,
		126.098, 126.331, 126.806, 127.302, 128.04, 128.548, 128.915, 129.292, 129.772, 130.275, 130.776, 131.274, 132.267, 132.768, 133.034, 
		133.519, 133.9, 134.237, 134.506, 134.76, 135.009

	};
//	crimewave.push_back(999);
	crimewave.push_back(999);
	for (int i = 0; i < crimewave.size(); i++) {
		crimewave[i] *= 60;
		crimewave[i] += start_music;
		crimewave[i] -= spawn;
	//crimewave[i] +;

	}


	audio crimewave_song(snd, crimewave);


	//------------------------------------------------------------------------

	//счет


	int score1_timer = 0, score2_timer = 0;


	//игрок 1
	sf::String A = "score ";
	sf::Text score1;

	//sf::String P1 = "P1";
	sf::Text P1;

	P1.setFont(font);
	P1.setString("P1");
	P1.setFillColor(sf::Color::Magenta);
	P1.setPosition(rp1.getPosition().x + 15, rp1.getPosition().y - 100);
	P1.setCharacterSize(60);


	score1.setFont(font);

	score1.setPosition(P1.getPosition().x + 250, P1.getPosition().y);
	score1.setCharacterSize(60);
	score1.setFillColor(sf::Color::Magenta);

	//----------------------------------------------------

	//игрок 2
	sf::String B = "score ";
	sf::Text score2;

	//sf::String P2 = "P2";
	sf::Text P2;

	P2.setFont(font);
	P2.setString("P2");
	P2.setFillColor(sf::Color::Yellow);
	P2.setPosition(rp2.getPosition().x + 15 - 10, rp2.getPosition().y - 100);
	P2.setCharacterSize(60);


	score2.setFont(font);

	score2.setCharacterSize(60);
	score1.setString(A + '0');
	score2.setString(A + '0');
	score2.setPosition(P2.getPosition().x - 250 - score2.getGlobalBounds().width, P2.getPosition().y);
	score2.setFillColor(sf::Color::Yellow);
	//begin_анимация ------------------------------------------------------


	//3...............2............1.........begin

	sf::Text begin_text;
	begin_text.setFont(font);
	begin_text.setCharacterSize(200);
	vector<string> begin = { "3", "2", "1", "begin" };






	//-----------------------------------------------------------------

	//vector<Arrow> press1;
	//vector<Arrow> press2;



	vector < sf::Color> status1 = {sf::Color::White, sf::Color::Magenta, sf::Color::Red};
	vector < sf::Color> status2 = { sf::Color::White, sf::Color::Yellow, sf::Color::Red};



	bool restart = true;
	//int num1 = -1, int num1 = -1;
	while(restart){

		vector<Arrow> arrows1;
		vector<Arrow> arrows2;
		//timers
		bool restart = false;
		bool is_over = false;

		int speed = 5;
		int timer = 0;

		int ind = 0;

		boombox.setTexture(boombox_texture[0]);

		int sc1 = 0, sc2 = 0;

		int torch_timer = 0, change = 30;

		int music_begin = start_music, boombox_timer = 0;


		//short st1, st2;

		//int spawn_rate = 0;

		bool first = false;
		auto start_time = std::chrono::steady_clock::now();
		auto end_time = std::chrono::steady_clock::now();

		//cout << window.getSize().x << " " << window.getSize().y << " ";

		int num1 = 0;
		int num2 = 0;

		//cout << rp2.getGlobalBounds().height << " " << rp2.getGlobalBounds().width << "\n";

		menutheme.getLoop();



		while (window.isOpen() and !restart)
		{
			if (is_menu) {
				if (!menutheme.getStatus())
					menutheme.play();
				menu_text_animation++;
			}
			if (!is_menu) {
				timer++;

				//spawn_rate++;

			switch (timer) {
				case 60:
					begin_text.setString(begin[0]);
					count.play();
					break;
				case 120:
					begin_text.setString(begin[1]);
					//count.play();
					break;
				case 200:
					begin_text.setString(begin[2]);
					//count.play();
					break;
				case 300:
					begin_text.setString(begin[3]);
					beginsound.play();
					break;
				}

				if (timer < start_music - 60) {
					begin_text.setPosition(wwightx / 2 - begin_text.getGlobalBounds().width / 2, 300);
				}


				if (timer == start_music) {
					crimewave_song.music.play();

				}


				//if (ind == crimewave_song.keys.size()) {
				//	ind = 0;
				//}
				double seconds;
				if (!first) {
					end_time = std::chrono::steady_clock::now();
				}
				auto elapsed_ns = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
				//cout << elapsed_ns.count() * 60;

				if (!crimewave_song.keys.empty() and timer >= (crimewave_song.keys[ind]) and !is_over) {
					int y = getrandom();
					//движения первого игрока
					Arrow ar1;
					sf::RectangleShape rec1(sf::Vector2f(71, 71));
					rec1.setFillColor(sf::Color::Blue);
					ar1.setrec(rec1);
					//spawn = 0;

					ar1.set_number(y);
					ar1.set_speed(speed);
					ar1.setxy(rp1.getPosition().x + 550, 200);
					arrows1.push_back(ar1);
					//status1.push_back(sf::Color::White);
					//	press1.push_back(ar1);
						//
					//cout << "!" << arrows1[0].getposition().x << "\n";

					//движения второго игрока
					Arrow ar2;
					//	ar2.settext(font);

					sf::RectangleShape rec2(sf::Vector2f(71, 71));
					rec2.setFillColor(sf::Color::Blue);
					ar2.setrec(rec2);


					ar2.set_number(y);
					//ar2.set_p2_controls(t2_texture);
					ar2.set_speed(speed * -1);
					ar2.setxy(rp2.getPosition().x - 550, 210);
					//ar2.
					arrows2.push_back(ar2);
					//status2.push_back(sf::Color::White);
					//	press2.push_back(ar2);
						//
						//timer = 0;
					ind++;
				}
				start_time = std::chrono::steady_clock::now();
				//spawn++;

				if (arrows1.size() == 0)
					num1 == -1;
				if (arrows2.size() == 0)
					num2 == -1;


				for (int i = 0; i < arrows1.size(); i++) {
					//	press1[i].move();
					arrows1[i].move();
					window.draw(arrows1[i].getrec());
				}
				//	if (arrows1[i].getposition().x == rp1.getPosition().x) {
				//		cout << spawn_rate << " ";
				//	}
				if (arrows1.size() > 0) {
					if (arrows1[0].getposition().x < rp1.getPosition().x - 100) {
						arrows1.erase(arrows1.begin());
						num1--;
						//	press1.erase(press1.begin() + i);
					}
				}

				for (int i = 0; i < arrows2.size(); i++) {
					arrows2[i].move();
					window.draw(arrows2[i].getrec());
				}
				//press2[i].move();
			//press2.erase(press2.begin() + i);
				if (arrows2.size() > 0) {
					if (arrows2[0].getposition().x > rp2.getPosition().x + 100) {
						arrows2.erase(arrows2.begin());
						num2--;
					}
				}
				//if (s == 60) {
				//	sc++;
				//	std::ostringstream points1;
				//	points1 << sc;
				//	score1.setString(A + points1.str());
				//	//s = 0;
				//}

				//if (s == 60) {
				//	//sc++;
				//	std::ostringstream points2;
				//	points2 << sc;
				//	score2.setString(B + points2.str());
				//	s = 0;
				//}








				//счетчики для анимации
				if (skin1_timer > 0)
					skin1_timer--;


				if (skin1_timer == 0) {
					player1.setTexture(player1_texture);
				}

				if (skin2_timer > 0)
					skin2_timer--;


				if (skin2_timer == 0) {
					player2.setTexture(player2_texture);
				}




				if (score1_timer > 0) {
					score1_timer--;
				}

				if (score1_timer == 0) {
					rp1.setTexture(rp1_texture);
				}

				if (score2_timer > 0) {
					score2_timer--;
				}

				if (score2_timer == 0) {
					rp2.setTexture(rp1_texture);
				}

				torch_timer++;
				boombox_timer++;
				if (music_begin > 0)
					music_begin--;

				if (boombox_timer == change and music_begin == 0) {
					boombox.setTexture(boombox_texture[2]);
				}

				if (torch_timer == change * 2 and music_begin == 0) {
					boombox.setTexture(boombox_texture[1]);
					boombox_timer = 0;
				}


				if (torch_timer == change) {
					torch1.setTexture(torch_texture[1]);
					torch2.setTexture(torch_texture[2]);
				}

				if (torch_timer == change * 2) {
					torch1.setTexture(torch_texture[2]);
					torch2.setTexture(torch_texture[0]);
				}

				if (torch_timer == change * 3) {
					torch1.setTexture(torch_texture[0]);
					torch2.setTexture(torch_texture[1]);
					torch_timer = 0;
				}



			}
			std::ostringstream points1;
			points1 << sc1;
			std::ostringstream points2;
			points2 << sc2;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed) window.close();
				if (event.key.code == sf::Keyboard::Escape) window.close();
				if (event.type == sf::Event::KeyPressed)
				{
					if (is_menu) {
						start_sound.play();
						is_menu = false;
						menutheme.stop();
						break;
					}
					if (is_over) {

					}
					else {
						if (event.key.code == sf::Keyboard::R) {
							restart = true;
							crimewave_song.music.stop();
						}
						if (!is_over and num1 != -1 and score1_timer == 0 and (event.key.code == sf::Keyboard::W or event.key.code == sf::Keyboard::A or event.key.code == sf::Keyboard::S or event.key.code == sf::Keyboard::D)) {
							int accur1 = -1;
							bool correct1 = false;
							std::ostringstream points1;


							sf::Text accuracy1;
							accuracy1.setFont(font);
							accuracy1.setCharacterSize(50);
							accuracy1.setPosition(sf::Vector2f(rp1.getGlobalBounds().left, rp1.getGlobalBounds().top + rp1.getGlobalBounds().height));
							//	cout << arrows1.size() << " " << num1 << "\n";

								//for (int i = 0; i < arrows2.size() and arrows2[i].get_status() == 0; i++) {
								//	num1 = i;
								//}
							if (num1 < arrows1.size() and !arrows1.empty() and arrows1[num1].get_status() == 0) {
								//if (!arrows1.empty())
								accur1 = abs(rp1.getPosition().x - arrows1[num1].getposition().x);
								if (accur1 < 65 and accur1 >= 0) {
									int numt1 = arrows1[num1].get_number();
									switch (numt1) {
									case (0):
										if (event.key.code == sf::Keyboard::W)
											correct1 = true;
										break;
									case (1):
										if (event.key.code == sf::Keyboard::A)
											correct1 = true;
										break;
									case (2):
										if (event.key.code == sf::Keyboard::S)
											correct1 = true;
										break;
									case (3):
										if (event.key.code == sf::Keyboard::D)
											correct1 = true;
										break;
									}
									if (correct1 == true) {
										int score1_plus = 100 - accur1;
										sc1 += score1_plus; // прибавление

										if (score1_plus >= 90) {
											accuracy1.setString(accuracy_text[3]);
										}
										else if (score1_plus <= 30) {
											accuracy1.setString(accuracy_text[0]);
										}
										else if (score1_plus > 30 and score1_plus <= 60)
											accuracy1.setString(accuracy_text[1]);
										else if (score1_plus > 60 and score1_plus < 90) {
											accuracy1.setString(accuracy_text[2]);
										}
										accuracy1_vector.push_back(accuracy1);
										arrows1[num1].correct();
										player1.setTexture(player1_dance);
										//	is_purple_dance = true;
									}
									if (correct1 == false) {
										sc1 -= 100;
										arrows1[num1].miss();
										accuracy1.setString(accuracy_text[4]);
										accuracy1_vector.push_back(accuracy1);
									}
								}
								//if (accur1 >= 65 and accur1 < 130) {
								//	sc1 -= 100; // вычитание при промахе
								//	arrows1[num1].miss();
								//}
								else if (accur1 >= 65) {
									accuracy1.setString(accuracy_text[4]);
									accuracy1_vector.push_back(accuracy1);
									sc1 -= 100; // вычитание при промахе
								}

							}
							else {
								sc1 -= 100;
								accuracy1.setString(accuracy_text[4]);
								accuracy1_vector.push_back(accuracy1);
							}

							points1 << sc1;
							score1.setString(A + points1.str());

							rp1.setTexture(rp1_clicked_texture);
							score1_timer = 5;
							skin1_timer = 10;
						}
						if (!is_over and num1 != -1 and score2_timer == 0 and (event.key.code == sf::Keyboard::Right or event.key.code == sf::Keyboard::Up or event.key.code == sf::Keyboard::Left or event.key.code == sf::Keyboard::Down)) {
							int accur2 = -1;
							bool correct2 = false;
							std::ostringstream points2;

							sf::Text accuracy2;
							accuracy2.setFont(font);
							accuracy2.setCharacterSize(50);
							accuracy2.setPosition(sf::Vector2f(rp2.getGlobalBounds().left, rp2.getGlobalBounds().top + rp2.getGlobalBounds().height));

							//	cout << arrows2.size() << " " << num2 << "\n";
								//for (int i = 0; i < arrows2.size() and arrows2[i].get_status() == 0; i++) {
								//	num2 = i;
								//}
							if (num2 < arrows2.size() and !arrows2.empty() and arrows2[num2].get_status() == 0) {
								//	if (!arrows2.empty())
								accur2 = abs(rp2.getPosition().x - arrows2[num2].getposition().x);
								if (accur2 < 65 and accur2 >= 0) {
									int numt2 = arrows2[num2].get_number();
									switch (numt2) {
									case (0):
										if (event.key.code == sf::Keyboard::Up)
											correct2 = true;
										break;
									case (1):
										if (event.key.code == sf::Keyboard::Left)
											correct2 = true;
										break;
									case (2):
										if (event.key.code == sf::Keyboard::Down)
											correct2 = true;
										break;
									case (3):
										if (event.key.code == sf::Keyboard::Right)
											correct2 = true;
										break;
									}
									if (correct2 == true) {
										int score2_plus = 100 - accur2;
										sc2 += score2_plus; // прибавление
										if (score2_plus > 90) {
											accuracy2.setString(accuracy_text[3]);
										}
										else if (score2_plus <= 30) {
											accuracy2.setString(accuracy_text[0]);
										}
										else if (score2_plus > 30 and score2_plus <= 60)
											accuracy2.setString(accuracy_text[1]);
										else if (score2_plus > 60 and score2_plus <= 90) {
											accuracy2.setString(accuracy_text[2]);
										}
										//	hit.play();
										arrows2[num2].correct();
										player2.setTexture(player2_dance);
										//is_yellow_dance = true;
									}
									if (correct2 == false) {
										sc2 -= 100;
										arrows2[num2].miss();
										accuracy2.setString(accuracy_text[4]);
										accuracy2_vector.push_back(accuracy2);
									}
								}
								//if (accur2 >= 65 and accur2 < 130) {
								//	sc2 -= 100; // вычитание при промахе
								//	arrows2[num2].miss();
								//}
								else if (accur2 >= 65) {
									sc1 -= 100;
									accuracy2.setString(accuracy_text[4]);
									accuracy2_vector.push_back(accuracy2);
								}
							}
							else {
								sc2 -= 100;
								accuracy2.setString(accuracy_text[4]);
								accuracy2_vector.push_back(accuracy2);
							}
							points2 << sc1;
							score2.setString(B + points2.str());

							rp2.setTexture(rp2_clicked_texture);
							score2_timer = 5;
							skin2_timer = 10;
							accuracy2_vector.push_back(accuracy2);
						}
					}
				}
			}

			// Выполняем необходимые действия по отрисовке
			window.clear();
			if (!is_menu) {
				window.draw(line);
				window.draw(torch1);
				window.draw(torch2);



				//cout << arrows.size();
				//случай бездействия
				for (int i = 0; i < arrows1.size(); i++) {
					std::ostringstream points1;
					t1.setString(stringp1[arrows1[i].get_number()]);
					t1.setFillColor(status1[arrows1[i].get_status()]);
					t1.setPosition(arrows1[i].getposition());

					if (arrows1[i].getposition().x < rp1.getPosition().x) {
						if (arrows1[i].get_status() == 0) {
							arrows1[i].miss();
							sc1 -= 100;
						}
						//if (arrows1[num1 + 1].get_status() == 0)
						//	num1++;
					}
					if (arrows1[i].getposition().x == rp1.getPosition().x - speed) {
						num1++;
						//	cout << num1 << " ";
					}
					if (arrows1.empty()) {
						num1 = -1;
					}
					//window.draw(arrows1[i].getsprite());
					//t1.setFillColor();

					string curtext = "";

					window.draw(t1);

					/*points1 << sc1;
					t1.setFillColor(status1[arrows1[i].get_status()]);
					window.draw(t1);*/
				}
				for (int i = 0; i < arrows2.size(); i++) {
					std::ostringstream points2;
					//t2.setString(stringp2[arrows2[i].get_number()]);

					//t2.setPosition(arrows2[i].getposition());
					if (arrows2[i].getposition().x > rp2.getPosition().x) {
						if (arrows2[i].get_status() == 0) {
							arrows2[i].miss();
							sc2 -= 100;
						}
						//if (arrows2[num2 + 1].get_status() == 0)
						//	num2++;
					}
					if (arrows2[i].getposition().x == rp2.getPosition().x + speed)
						num2++;
					if (arrows2.empty()) {
						num2 = -1;
					}
					points2 << sc2;
					//t2.setFillColor(status2[arrows2[i].get_status()]);

				//	window.draw(arrows2[i].getsprite());
					sf::Sprite s2 = arrows_coord(arrows2[i], arrow_sign);
					window.draw(s2);



					/*	sf::Sprite t2_imposter;
						t2_imposter.setTextureRect(arrows2[i].getp2_texture_rec());
						t2_imposter.setPosition(arrows2[i].getposition());
						window.draw(t2_imposter);*/
				}
				//cout << crimewave.size() << "\n";
				//if (timer >= crimewave_song.keys[crimewave_song.keys.size() - 2] + 60 * 5)
				score1.setString(A + points1.str());
				score2.setString(B + points2.str());
				window.draw(rp1);
				window.draw(rp2);
				window.draw(score1);
				window.draw(score2);
				window.draw(boombox);
				window.draw(P1);
				window.draw(P2);
				window.draw(player2);
				window.draw(player1);
				if (timer >= crimewave_song.keys[crimewave_song.keys.size() - 2] + 5 * 60 and !is_over) {
					boombox.setTexture(boombox_texture[0]);
					if (sc2 > sc1) {
						win_text.setString("P2 wins!");
						win_text.setPosition(sf::Vector2f(p2_win.getGlobalBounds().left + p2_win.getGlobalBounds().width / 2, p2_win.getGlobalBounds().top + win_text.getGlobalBounds().height / 2));
						player2.setTexture(player2_attack);
						window.draw(p2_win);
						window.draw(win_text);
						window.draw(player2);
					}
					if (sc1 > sc2) {
						win_text.setString("P1 wins!");
						win_text.setPosition(sf::Vector2f(p1_win.getGlobalBounds().left + p1_win.getGlobalBounds().width / 4, p1_win.getGlobalBounds().top + win_text.getGlobalBounds().height / 2));
						player1.setTexture(player1_attack);
						window.draw(p1_win);
						window.draw(win_text);
						window.draw(player1);
					}
					else if(sc1 == sc2)
						window.draw(draw_text);
				}

				//window.draw(a.gettext());
				if (timer < start_music - 120 and timer >= 60 and !restart) {
					window.draw(begin_text);
				}
			}

			for (int i = 0; i < accuracy1_vector.size(); i++) {
				window.draw(accuracy1_vector[i]);
				//int yposition1 = accuracy1_vector[i].getGlobalBounds().top - 5;
				accuracy1_vector[i].move(0, 7);
				if (accuracy1_vector[i].getGlobalBounds().top > rp1.getGlobalBounds().top + 250) {
					accuracy1_vector.erase(accuracy1_vector.begin() + i);
				}
			}

			for (int i = 0; i < accuracy2_vector.size(); i++) {
				window.draw(accuracy2_vector[i]);
				accuracy2_vector[i].move(0, 7);
				//accuracy2_vector[i].setPosition(sf::Vector2f(accuracy2_vector[i].getGlobalBounds().left, yposition2));
				if (accuracy2_vector[i].getGlobalBounds().top > rp2.getGlobalBounds().top + 250) {
					accuracy2_vector.erase(accuracy2_vector.begin() + i);
				}
			}

			if (is_menu) {
				window.draw(menu_phone);
				window.draw(menu_title);
				if (menu_text_animation <= 50) {
					window.draw(menu_text);
				}
				else if (menu_text_animation == 80)
					menu_text_animation = 0;
			}
			window.display();
		}

	//	cout << restart;

	}

	return 0;
}
