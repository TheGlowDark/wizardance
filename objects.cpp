#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;



class Obj {
protected:
	sf::Texture texture;
	sf::RectangleShape hitbox;
	sf::Vector2f coord;
public:
	sf::Vector2f getposition() {
		return coord;
	}
	sf::RectangleShape getsprite() {
		return hitbox;
	}
	void setx(float x1) {
		coord.x = x1;
		hitbox.setPosition(coord);
	}
	void sety(float y1) {
		coord.y = y1;
		hitbox.setPosition(coord);
	}

	void setxy(float x1, float y1) {
		coord.y = y1;
		coord.x = x1;
		hitbox.setPosition(coord);
	}

	void setrec(sf::RectangleShape rec) {
		hitbox = rec;
	}


	sf::RectangleShape getrec() {
		return hitbox;
	}

	//void setsprite(sf::Texture a) {
	//	sprite.setTexture(a);
	//}

	//void setsprite(sf::Sprite s ) {
	//	sprite = s;
	//}


};


class Player : public Obj {
public:
	Player() {};



};

class Arrow : public Obj {
private:
	sf::Text text;
	float speed;

	int number;

	short status = 0;
	//sf::Texture pressed;
	//sf::Texture not_pressed;

	//sf::Texture arrows_control;
	//sf::Sprite arrows_sprite;

	//sf::Vector2f coord;

	//sf::Texture unmatch;
	//sf::Texture correct;
	//sf::Texture miss;

	//sf::Sprite current; 

public:
	Arrow() {};

	//Arrow(sf::Texture un, sf::Texture c, sf::Texture m) {
	//	unmatch = un;
	//	correct = c;
	//	miss = m;
	//}

	//void set_p2_controls(sf::Texture a) {
	//	arrows_control = a;
	//}


	void settext(sf::Font x, string y = "w") {
		text.setFont(x);
		text.setString(y);
		text.setCharacterSize(30);
	}
	sf::Text gettext() {
		return text;
	}

	//void set_arrow(int x) {
	//	current.setTexture(unmatch);
	//	current.setTextureRect(sf::IntRect(x * 71, 0, (x + 1) * 71, 71));
	//}


	void set_number(int x) {
		number = x;
	}
	int get_number() {
		return number;
	}

	void set_speed(float x) {
		this->speed = x;
	}
	void correct() {
		this->status = 1;
	}

	void miss() {
		this->status = 2;
	}
	


	sf::IntRect getp2_texture_rec() {
		sf::IntRect intr(number * 71, status * 71, (number + 1) * 71, (status + 1) * 71);
		//arrows_sprite.setPosition(coord);
	//	arrows_sprite(sf::IntRect(number * 71, status * 71, (number + 1) * 71, (status + 1) * 71));
		return intr;
	}

	short get_status() {
		return this->status;
	}

	void set_color(sf::Color x) {
		text.setFillColor(x);
	}


	void spawn(float x, float y){
		coord.x = x;
		coord.y = y;
		hitbox.setPosition(x, y);
		//rec.setPosition(x, y);
		//text.setPosition(x, y);
		//arrows_sprite.setPosition(coord);
	};

	void move() {
		coord.x -= speed;
		hitbox.setPosition(coord);
		//text.setPosition(coord);
	//	arrows_sprite.setPosition(coord);
	//	
	// sprite.setPosition(coord);
	}


};