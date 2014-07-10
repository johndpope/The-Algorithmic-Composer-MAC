//
//  RandomWalkComposer.h
//  the_algorithmic_composer
//
//  Created by Raúl Ibarra Díez on 09/07/14.
//
//

#ifndef __the_algorithmic_composer__RandomWalkComposer__
#define __the_algorithmic_composer__RandomWalkComposer__

#include <iostream>
#include "Composer.h"
#include "Figure.h"
#include <string>
#include <vector>

using namespace std;

enum Boundary{
    Reflecting, Elastic, Absorbing
};

class RandomWalkComposer : public Composer {

public:
    RandomWalkComposer();
    ~RandomWalkComposer();
    std::vector<Figure *> compose(bool infinite = false);
    
    void setBoundary(Boundary b){ boundary = b; }
    void setMaxPitch(int m){ maxPitch = m; }
    void setMinPitch(int m){ minPitch = m; }
    void setStartingPitch(int s){ startingPitch = s; }
	void setScale(int s){ scale = s; }
    
private:
    Boundary boundary;
    int minPitch;
    int maxPitch;
    int startingPitch;
	bool direction;
    int scale;
	
    // Random durations Vs. User defined durations (very simple) Vs. Durations templates
    
};

#endif /* defined(__the_algorithmic_composer__RandomWalkComposer__) */
