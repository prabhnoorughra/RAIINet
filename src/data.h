#ifndef DATA_H
#define DATA_H
#include "link.h"
#include <string>
#include <vector>


using namespace std;

class Data : public Link {
	int player;
	int strength;
	bool revealed;
	bool boosted;
	bool stunned;
	bool onFirewall;
	public:
		Data(int index, char symbol, int player, int strength, bool revealed = false, bool boosted = false, bool stunned = false, bool onFirewall = false);
		char getSymbol() const override;
		string getType() const override;
		int getPlayer() const override;
		int getStrength() const override;
		void setRevealed(bool reveal) override;
		bool getRevealed() const override;
		bool getBoosted() const override;
		bool getStunned() const override;
		string print() const override;

		void setBoosted(bool boost) override;
		void setStunned(bool stun) override;
		void setStrength(int x) override;

		bool getOnFirewall() const override;
		void setOnFirewall(bool onFirewall) override;
};


#endif
