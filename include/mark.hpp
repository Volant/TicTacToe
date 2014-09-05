#ifndef __MARK_H__
#define __MARK_H__

#include "point.hpp"

class Mark {

private:
	char type;

public:
	Mark() {};
	Mark(char type) {
		this->type = type;
	}

	void Draw (float xs, float ys, float xe, float ye);
	void Draw (float x, float y, float r);

	~Mark() {};
};

#endif
