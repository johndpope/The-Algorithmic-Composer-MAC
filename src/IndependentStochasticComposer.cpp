//
//  IndependentStochasticComposer.cpp
//  The_Algorithmic_Composer
//
//  Created by Laura Sirvent Collado on 09/06/14.
//
//

#include "IndependentStochasticComposer.h"
#include "Randomize.h"
#include "Note.h"
#include "Silence.h"
#include "Scales.h"

using namespace std;

IndependentStochasticComposer::IndependentStochasticComposer(Distribution *d){
	
	distribution = d;
}

std::vector<Figure *> IndependentStochasticComposer::compose(bool infinite, int meter, int pattern, int stems){
	
	std::vector<Figure *> fragment;
	float counter = 0.0;
	float total = (float)meter / (float)pattern;
	bool f;
	Type t;
	float duration;
	
	for(int i = 0; i < stems; i++){
		
		while(counter < total){
			
			f = Randomize::getRandomFigure();
			//f = true;
			
			t = (Type)mapValue(distribution->getValue(), 0, 12);
			
			duration = Figure::typeToDuration(t);
			//cout<<"duration: "<<duration<<endl;
			
			while(counter + duration > total){
				
				float difference = total - counter;
				
				if(Figure::durationToType(difference) == SixtyFourth)
					t = SixtyFourth;
				else
					t = (Type)mapValue(distribution->getValue(), 0, 12);
				
				duration = Figure::typeToDuration(t);
				//cout<<"duration: "<<duration<<" counter: "<<counter<<" +: "<<counter+duration<<" total: "<<total<<endl;
			}
			counter += duration;
			
			if(f){ //Note
				
				int tone = mapValue(distribution->getValue(), 0, 5);
				int octave = 4;
				
				int pitch = 10*(octave + 2) + Scales::Pentatonic[tone];
				//pitch = mapValue(distribution->getValue(), 0, 127);
				
				
				int velocity = mapValue(distribution->getValue(), 0, 100);
				Note * note = new Note(t, pitch, velocity);
				fragment.push_back(note);
			}
			else{ //Silence
				Silence * silence = new Silence(t);
				fragment.push_back(silence);
			}
		}
		counter = 0.0;
	}
	
	return fragment;
}

int IndependentStochasticComposer::mapValue(float value, int min, int max){
	
	int returnValue = (value * (max - min)) + min;
	return returnValue;
}