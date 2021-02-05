#ifndef LOADING_H
#define LOADING_H

extern LTexture image1[4];

bool loading()
{
	bool success = true;
	
	if( !image1[0].loadFromFile("../data/images/bg.png")){printf("Failed!\n");success = false;}
	
	return success;
}

#endif // LOADING_H

