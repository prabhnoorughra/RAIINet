#ifndef EMPTY_H
#define EMPTY_H
#include <string>
#include <vector>
#include "link.h"

using namespace std;

class Empty : public Link {

	public:
		Empty(int index);
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
