#ifndef FIREWALL_H
#define FIREWALL_H
#include <string>
#include <vector>
#include "link.h"

using namespace std;

class Firewall : public Link {
	int player;

	public:
		Firewall(int index, int player);
		Firewall(int index, char symbol);

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
