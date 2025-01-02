#ifndef LINK_H
#define LINK_H
#include <string>
#include <vector>
#include <memory>


using namespace std;

class Link {
	public:
		int index;
	protected:
		char symbol;
		string type;
	public:
		char fire;
	public:
		virtual ~Link() = default;
		Link(int index, char symbol, string type, char fire = 'x');
		virtual char getSymbol() const = 0;
		virtual string getType() const = 0;
		virtual int getPlayer() const = 0;
		virtual int getStrength() const = 0;
		virtual void setRevealed(bool reveal) = 0;
		virtual bool getRevealed() const = 0;
		virtual bool getBoosted() const = 0;
		virtual bool getStunned() const = 0;
		virtual string print() const = 0;
		
		virtual void setBoosted(bool boost) = 0;
		virtual void setStunned(bool stun) = 0;
		virtual void setStrength(int x) = 0;

		virtual bool getOnFirewall() const = 0;
		virtual void setOnFirewall(bool onFirewall) = 0;

};


#endif
