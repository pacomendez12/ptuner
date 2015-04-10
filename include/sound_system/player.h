/*
 * This class has a virtual method that needs to be implemented
 * in a subclass because it's dependent of the system used for 
 * reproducing sounds
 */

#ifndef PLAYER_H
#define PLAYER_H
class Player{
	public:
		Player();
		Player(int rate, int depth);
		/*Destructor is called when the tuner finish or when is 
		 * changed the sound system.
		 **/
		~Player();
		int virtual setStream(void * buff, int size) = 0;

		/*It stops any pending transaction*/
		void virtual stop() = 0;

};

#endif
