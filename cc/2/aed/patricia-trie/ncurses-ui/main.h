#ifndef _MAIN_H
#define _MAIN_H 1

#include <tree.hh>
#include "interface.h"

class Program {

	private:
		Interface * interface;
		Tree * tree;

	public:
		Program (string fn);
		~Program ();

		void run ();
};

#endif /* _MAIN_H */
