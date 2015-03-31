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
		virtual int initSoundSystem() = 0;
		virtual int finishSoundSystem() = 0;

		void setParameters(int rate, int depth);

	private:
		int buffer_size;
		int rate;
		int depth;

};

#endif
