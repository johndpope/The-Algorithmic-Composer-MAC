#include "App.h"
#include "IndependentStochasticComposer.h"
#include "Figure.h"
#include "Scales.h"

#include <vector>
#include <string>
#include <sstream>

using namespace std;

//--------------------------------------------------------------
ofxTonicSynth App::synth = ofxTonicSynth();
ofxUITextArea * App::currentFigureLabel = NULL;
ofxUIScrollableCanvas * App::resultsGui = NULL;

void App::setup(){
    
	uniform = new UniformDistribution();
	
	linear = new LinearDistribution();
	linear->setDirection(Down);
	
	triangular = new TriangularDistribution();
	//triangular->setMean(0.9);
	triangular->setTriangleBase(1.0);
	
	exponential = new ExponentialDistribution();
	//exponential->setLambda(1.0);
	
	gauss = new GaussianDistribution();
	gauss->setMu(0.5);
	gauss->setSpread(10);
	
	cauchy = new CauchyDistribution();
	cauchy->setAlpha(10);
	
	beta = new BetaDistribution();
	beta->setB(1);
	beta->setA(50);
	
	weibull = new WeibullDistribution();
	weibull->setT(0.5);
	weibull->setS(0.1);
	
	poisson = new PoissonDistribution();
	
	composer = new IndependentStochasticComposer(uniform);
	//std::vector<Figure *> result = composer->compose(false, 2, 4, 10);
	
	player = new Player(60);
	
	initGUI();
	initSynth();
	
	//player->play(result);
	

}

//--------------------------------------------------------------
void App::update(){

	if(!player->isAllPlayed())
		player->update();
	else
		synth.setParameter("volume", 0);
}

//--------------------------------------------------------------
void App::draw(){
	
	backgroundColor = ofColor(red, green, blue);
    ofBackground(backgroundColor);
	
	musicNotesFont.drawString("`ACDGF", 400, 600);
}

//--------------------------------------------------------------
void App::keyPressed(int key){

}

//--------------------------------------------------------------
void App::keyReleased(int key){

}

//--------------------------------------------------------------
void App::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void App::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void App::mousePressed(int x, int y, int button){
	if(button == 2)
    {
        styleGUI->setPosition(x, y);
        styleGUI->setVisible(true);
        return;
    }
    
    if(!styleGUI->isHit(x, y))
    {
        styleGUI->setVisible(false);
    }
}

//--------------------------------------------------------------
void App::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void App::windowResized(int w, int h){

}

//--------------------------------------------------------------
void App::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void App::dragEvent(ofDragInfo dragInfo){

}

void App::audioRequested (float * output, int bufferSize, int nChannels){
	synth.fillBufferOfFloats(output, bufferSize, nChannels);
}

void App::exit(){
    
}

void App::guiEvent(ofxUIEventArgs &e){
	
	string name = e.getName();
	int kind = e.getKind();
	IndependentStochasticComposer * c = dynamic_cast<IndependentStochasticComposer *>(composer);
	
	
	if(name == "Uniform"){
		c->setDistribution(uniform);
		setValuesForGraph(uniform);
		triangularDistGUI->setVisible(false);
		linearDistGUI->setVisible(false);
		exponentialDistGUI->setVisible(false);
		gaussDistGUI->setVisible(false);
		cauchyDistGUI->setVisible(false);
		betaDistGUI->setVisible(false);
		weibullDistGUI->setVisible(false);
		poissonDistGUI->setVisible(false);
	}
	
	
	else if(name == "Linear"){
		c->setDistribution(linear);
		setValuesForGraph(linear);
		triangularDistGUI->setVisible(false);
		linearDistGUI->setVisible(true);
		exponentialDistGUI->setVisible(false);
		gaussDistGUI->setVisible(false);
		cauchyDistGUI->setVisible(false);
		betaDistGUI->setVisible(false);
		weibullDistGUI->setVisible(false);
		poissonDistGUI->setVisible(false);
	}
	else if(name == "Up"){
		linear->setDirection(Up);
		setValuesForGraph(linear);
	}
	else if(name == "Down"){
		linear->setDirection(Down);
		setValuesForGraph(linear);
	}
	
	
	else if(name == "Triangular"){
		c->setDistribution(triangular);
		setValuesForGraph(triangular);
		triangularDistGUI->setVisible(true);
		linearDistGUI->setVisible(false);
		exponentialDistGUI->setVisible(false);
		gaussDistGUI->setVisible(false);
		cauchyDistGUI->setVisible(false);
		betaDistGUI->setVisible(false);
		weibullDistGUI->setVisible(false);
		poissonDistGUI->setVisible(false);
	}
	else if(name == "Triangle Base"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		triangular->setTriangleBase(slider->getValue());
		setValuesForGraph(triangular);
	}
	
	
	
	else if(name == "Exponential"){
		c->setDistribution(exponential);
		setValuesForGraph(exponential);
		triangularDistGUI->setVisible(false);
		linearDistGUI->setVisible(false);
		exponentialDistGUI->setVisible(true);
		gaussDistGUI->setVisible(false);
		cauchyDistGUI->setVisible(false);
		betaDistGUI->setVisible(false);
		weibullDistGUI->setVisible(false);
		poissonDistGUI->setVisible(false);
	}
	else if (name == "Lambda"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		exponential->setLambda(slider->getValue());
		setValuesForGraph(exponential);
	}
	
	
	else if(name == "Gaussian"){
		c->setDistribution(gauss);
		setValuesForGraph(gauss);
		triangularDistGUI->setVisible(false);
		linearDistGUI->setVisible(false);
		exponentialDistGUI->setVisible(false);
		gaussDistGUI->setVisible(true);
		cauchyDistGUI->setVisible(false);
		betaDistGUI->setVisible(false);
		weibullDistGUI->setVisible(false);
		poissonDistGUI->setVisible(false);
	}
	else if (name == "Sigma"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		gauss->setSigma(slider->getValue());
		setValuesForGraph(gauss);
	}
	else if (name == "Mu"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		gauss->setMu(slider->getValue());
		setValuesForGraph(gauss);
	}
	
	
	else if(name == "Cauchy"){
		c->setDistribution(cauchy);
		setValuesForGraph(cauchy);
		triangularDistGUI->setVisible(false);
		linearDistGUI->setVisible(false);
		exponentialDistGUI->setVisible(false);
		gaussDistGUI->setVisible(false);
		cauchyDistGUI->setVisible(true);
		betaDistGUI->setVisible(false);
		weibullDistGUI->setVisible(false);
		poissonDistGUI->setVisible(false);
	}
	else if (name == "Alpha"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		cauchy->setAlpha(slider->getValue());
		setValuesForGraph(cauchy);
	}
	
	
	else if(name == "Beta"){
		c->setDistribution(beta);
		setValuesForGraph(beta);
		triangularDistGUI->setVisible(false);
		linearDistGUI->setVisible(false);
		exponentialDistGUI->setVisible(false);
		gaussDistGUI->setVisible(false);
		cauchyDistGUI->setVisible(false);
		betaDistGUI->setVisible(true);
		weibullDistGUI->setVisible(false);
		poissonDistGUI->setVisible(false);
	}
	else if (name == "A"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		beta->setA(slider->getValue());
		setValuesForGraph(beta);
	}
	else if (name == "B"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		beta->setB(slider->getValue());
		setValuesForGraph(beta);
	}
	
	else if(name == "Weibull"){
		c->setDistribution(weibull);
		setValuesForGraph(weibull);
		triangularDistGUI->setVisible(false);
		linearDistGUI->setVisible(false);
		exponentialDistGUI->setVisible(false);
		gaussDistGUI->setVisible(false);
		cauchyDistGUI->setVisible(false);
		betaDistGUI->setVisible(false);
		weibullDistGUI->setVisible(true);
		poissonDistGUI->setVisible(false);
	}
	else if (name == "T"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		weibull->setT(slider->getValue());
		setValuesForGraph(weibull);
	}
	else if (name == "S"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		weibull->setS(slider->getValue());
		setValuesForGraph(weibull);
	}
	
	else if(name == "Poisson"){
		c->setDistribution(poisson);
		setValuesForGraph(poisson);
		triangularDistGUI->setVisible(false);
		linearDistGUI->setVisible(false);
		exponentialDistGUI->setVisible(false);
		gaussDistGUI->setVisible(false);
		cauchyDistGUI->setVisible(false);
		betaDistGUI->setVisible(false);
		weibullDistGUI->setVisible(false);
		poissonDistGUI->setVisible(true);
	}
	else if (name == "lambda"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		poisson->setv(slider->getValue());
		setValuesForGraph(poisson);
	}
	
	else if(name == "COMPOSE"){
		composition.clear();
		composition = c->compose();
		resultsGui->removeWidgets();
	}
	else if(name == "PLAY" && composition.size() > 0 && !player->isPlaying()){
		player->play(composition);
	}
	
	else if(name == "TEMPO"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		player->setTempo((int)slider->getValue());
	}
	
	else if(name == "THEME"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();

		gui1->setTheme((int)slider->getValue());
		gui2->setTheme((int)slider->getValue());
		generalGUI->setTheme((int)slider->getValue());
		resultsGui->setTheme((int)slider->getValue());
		distributionGUI->setTheme((int)slider->getValue());
		triangularDistGUI->setTheme((int)slider->getValue());
		linearDistGUI->setTheme((int)slider->getValue());
		exponentialDistGUI->setTheme((int)slider->getValue());
		gaussDistGUI->setTheme((int)slider->getValue());
		cauchyDistGUI->setTheme((int)slider->getValue());
		betaDistGUI->setTheme((int)slider->getValue());
		weibullDistGUI->setTheme((int)slider->getValue());
		poissonDistGUI->setTheme((int)slider->getValue());
		styleGUI->setTheme((int)slider->getValue());
		
	}
	
	else if(name == "Octaves"){
		ofxUIRangeSlider *slider = (ofxUIRangeSlider *) e.widget;
		c->setOctaves((int)slider->getValueLow(), (int)slider->getValueHigh());
	}
	
	else if(name == "Stems"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		c->setStems((int)slider->getValue());
	}
	else if (name == "Meter"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		c->setMeter((int)slider->getValue());
	}
	else if (name == "Pattern"){
		ofxUISlider *slider = (ofxUISlider *) e.getSlider();
		c->setPattern((int)slider->getValue());
	}
	else if(name == "Notes"){
		ofxUIToggle * toggle = e.getToggle();
		if(toggle->getValue())
			c->setWantSilences(false);
	}
	else if(name == "Notes + Silences"){
		ofxUIToggle * toggle = e.getToggle();
		if(toggle->getValue())
			c->setWantSilences(true);
	}
	else if(kind == OFX_UI_WIDGET_TOGGLE)
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
		
		if(toggle->getParent()->getName() == "Scale"){
			
			bool found = false;
			int count = 0;
			while(!found && count < 38){
				if (name == NamesOfScales[count]) {
					found = true;
				}
				else count++;
			}
		}
		else if (toggle->getParent()->getName() == "Meter"){
			int meter = atoi(name.c_str());
			c->setMeter(meter);
		}
		else if(toggle->getParent()->getName() == "Pattern"){
			int meter = atoi(name.c_str());
			c->setPattern(meter);
		}

    }
	

}

void App::setMidiNote(int note){
	synth.setParameter("midiNumber", note);
}

void App::setIsSilence(bool t){
	if(t == false)
		synth.setParameter("volume", 1);
	else
		synth.setParameter("volume", 0);
}

void App::setVolume(float volume){
	//synth.setParameter("volume", volume);
}

void App::setCurrentFigure(Figure *f){
		
	
	resultsGui->addTextArea("text", "\n", OFX_UI_FONT_SMALL);
	resultsGui->addTextArea("text", f->getDescription(), OFX_UI_FONT_SMALL);
	
	
}

void App::initSynth(){
	
	//SYNTH SETTINGS
	
	ofSoundStreamSetup(2, 0, this, 44100, 256, 4);
	
	ControlGenerator midiNote = synth.addParameter("midiNumber");
	
	ControlGenerator volume = synth.addParameter("volume");
	synth.setParameter("volume", 1);
	
	ControlGenerator noteFreq =  ControlMidiToFreq().input(midiNote);
	
	// create a new oscillator which we'll use for the actual audio signal
	SineWave tone = SineWave();
	// create a sine wave we'll use for some vibrato
	SineWave vibratoOsc = SineWave();
	vibratoOsc.freq(10);
	
	// you can use the regular arithmatic operators on Generators and their subclasses (SineWave extends Generator)
	Generator frequency = noteFreq + (vibratoOsc * noteFreq * 0.01);
	
	// plug that frequency generator into the frequency slot of the main audio-producing sine wave
	tone.freq(noteFreq);
	
	// Partials
	SineWave firstPartial = SineWave().freq(noteFreq * 2);
	SineWave secondPartial = SineWave().freq(noteFreq * 3);
	
	// set the synth's final output generator
	synth.setOutputGen( (tone + firstPartial + secondPartial) * ADSR(0.3f, 0.0f, 0.1f, 0.6f).trigger(volume).legato(1));
}

void App::initGUI(){
	
	red = 156;     blue = 248;    green = 214;
	backgroundColor = ofColor(red, green, blue);
	
	musicNotesFont.loadFont("GUI/LASSUS.TTF", 100, false);
	
    ofBackground(backgroundColor);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofEnableSmoothing();

	ofSetColor(0,0,0);
	
	styleGUI = new ofxUICanvas();
	styleGUI->setFont("GUI/Lekton-Regular.ttf");
	styleGUI->addLabel("CONTEXTUAL MENU");
    styleGUI->addSpacer();
    styleGUI->addFPSSlider("FPS");
    styleGUI->addSpacer();
	styleGUI->addSlider("THEME", 0.0, 42.0, 1.0);
	styleGUI->addSpacer();
    styleGUI->addSlider("RED", 0.0, 255.0, &red);
    styleGUI->addSlider("GREEN", 0.0, 255.0, &green);
    styleGUI->addSlider("BLUE", 0.0, 255.0, &blue);
	styleGUI->setVisible(false);
	ofAddListener(styleGUI->newGUIEvent,this,&App::guiEvent);
	
	//
	
	generalGUI = new ofxUICanvas();
	generalGUI->setFont("GUI/Lekton-Regular.ttf");
	
	generalGUI->setPosition(980, 0);
	generalGUI->setWidth(300);
	generalGUI->setHeight(120);
	
	generalGUI->addLabelButton("COMPOSE", false);
	generalGUI->addLabelButton("PLAY", false);
	generalGUI->addSlider("TEMPO", 1, 200, 60);
	generalGUI->addSpacer(300, 10);
	generalGUI->addLabel("RESULTS", OFX_UI_FONT_LARGE);
	generalGUI->addSpacer();
	ofAddListener(generalGUI->newGUIEvent, this, &App::guiEvent);
	
	
	/////////////
	
	
	vector<float> distribution;
	for (int i = 0; i < 10; i++) {
		distribution.push_back(0.0);
	}
	distributionGUI = new ofxUICanvas();
	distributionGUI->setFont("GUI/Lekton-Regular.ttf");
	distributionGUI->setPosition(210, 0);
	distributionGUI->addLabel("DISTRIBUTION", OFX_UI_FONT_LARGE);
	distributionGUI->addLabel("Based on 1000 samples", OFX_UI_FONT_SMALL);
	mg = distributionGUI->addMovingGraph("distribution", distribution, 10, 0.0, 25.0, 50);
	distributionGUI->addSpacer();
	distributionGUI->autoSizeToFitWidgets();
	//distributionGUI->setVisible(false);
	
	
	///////////
	
	gui1 = new ofxUICanvas();
	gui1->setFont("GUI/Lekton-Regular.ttf");
	gui1->setHeight(360);
	gui1->setPosition(0, 0);
	
	
	gui1->addLabel("STOCHASTIC COMPOSER", OFX_UI_FONT_LARGE);
	gui1->addSpacer();
	
	
	gui1->addLabel("DISTRIBUTION");
	
	vector<string> distributions;
	distributions.push_back("Uniform");
	distributions.push_back("Linear");
	distributions.push_back("Triangular");
	distributions.push_back("Exponential");
	distributions.push_back("Gaussian");
	distributions.push_back("Cauchy");
	distributions.push_back("Beta");
	distributions.push_back("Weibull");
	distributions.push_back("Poisson");
	
	ofxUIRadio * dis = gui1->addRadio("Distribution", distributions);
	dis->getToggles()[0]->setValue(true);
	setValuesForGraph(uniform);
	
	gui1->addSpacer();
	
	gui1->addLabel("MUSICAL PARAMETERS");
	gui1->addRangeSlider("Octaves", 0, 10, 2, 4);
	gui1->addSlider("Stems", 1, 20, 1);
	gui1->addSpacer(210, 3);
	
	vector<string> meter;
	meter.push_back("2"); meter.push_back("3"); meter.push_back("4");
	
	gui1->addLabel("Meter", OFX_UI_FONT_SMALL);
	ofxUIRadio * mR = gui1->addRadio("Meter", meter, OFX_UI_ORIENTATION_HORIZONTAL);
	mR->getToggles()[0]->setValue(true);
	
	vector<string> pattern;
	pattern.push_back("1"); pattern.push_back("2"); pattern.push_back("4"); pattern.push_back("8"); pattern.push_back("16");
	
	gui1->addLabel("Pattern", OFX_UI_FONT_SMALL);
	ofxUIRadio * pR = gui1->addRadio("Pattern", pattern, OFX_UI_ORIENTATION_HORIZONTAL);
	pR->getToggles()[2]->setValue(true);

	gui1->addSpacer(210, 3);
	vector<string> figures;
	figures.push_back("Notes");
	figures.push_back("Notes + Silences");
	ofxUIRadio * figuresRadio = gui1->addRadio("Figures", figures);
	figuresRadio->getToggles()[1]->setValue(true);
	
	gui1->addSpacer(210, 3);
	gui1->addLabel("Scale", OFX_UI_FONT_SMALL);
	gui1->autoSizeToFitWidgets();
	gui1->setWidth(210);
	
	ofAddListener(gui1->newGUIEvent, this, &App::guiEvent);

	
	//////////////////
	
	
	gui2 = new ofxUIScrollableCanvas(0,0,ofGetWidth(),ofGetHeight());
	
	gui2->setScrollAreaToScreen();
    gui2->setScrollableDirections(false, true);
	gui2->setFont("GUI/Lekton-Regular.ttf");
	gui2->setPosition(0, 471);
	
	
	vector<string> scales(NamesOfScales, NamesOfScales + sizeof(NamesOfScales) / sizeof(string));
	scaleRadioButtons = gui2->addRadio("Scale", scales);
	scaleRadioButtons->getToggles()[0]->setValue(true);
	
	gui2->autoSizeToFitWidgets();
	gui2->setWidth(210);
	gui2->getRect()->setWidth(ofGetWidth());
	ofAddListener(gui2->newGUIEvent, this, &App::guiEvent);

	
	///////////////
	
	
	string textString = "1. Select distribution \n\n3. Select Scale \n\n2. Press COMPOSE \n\n3. Press PLAY";
		
	resultsGui = new ofxUIScrollableCanvas(0,0,ofGetWidth(),ofGetHeight());
	resultsGui->setFont("GUI/Lekton-Regular.ttf");
	resultsGui->setScrollAreaToScreen();
    resultsGui->setScrollableDirections(false, true);
	
	resultsGui->setPosition(980, 120);
	resultsGui->setHeight(640);
	resultsGui->setWidth(300);
	ofAddListener(resultsGui->newGUIEvent, this, &App::guiEvent);
	//currentFigureLabel = resultsGui->addTextArea("textarea", textString, OFX_UI_FONT_MEDIUM);
	
		
	/////////////
	
	
	linearDistGUI = new ofxUICanvas();
	linearDistGUI->setFont("GUI/Lekton-Regular.ttf");
	linearDistGUI->setPosition(210, 113);
	linearDistGUI->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	vector<string> op1;
	op1.push_back("Up");
	op1.push_back("Down");
	linearDistGUI->addRadio("Direction", op1);
	linearDistGUI->autoSizeToFitWidgets();
	linearDistGUI->setWidth(211);
	linearDistGUI->setVisible(false);
	ofAddListener(linearDistGUI->newGUIEvent, this, &App::guiEvent);
	
	
	triangularDistGUI = new ofxUICanvas();
	triangularDistGUI->setFont("GUI/Lekton-Regular.ttf");
	triangularDistGUI->setPosition(210, 113);
	triangularDistGUI->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	triangularDistGUI->addSlider("Triangle Base", 0.01, 1.0, 1.0);
	triangularDistGUI->autoSizeToFitWidgets();
	triangularDistGUI->setWidth(211);
	triangularDistGUI->setVisible(false);
	ofAddListener(triangularDistGUI->newGUIEvent, this, &App::guiEvent);
	
	
	
	exponentialDistGUI = new ofxUICanvas();
	exponentialDistGUI->setFont("GUI/Lekton-Regular.ttf");
	exponentialDistGUI->setPosition(210, 113);
	exponentialDistGUI->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	exponentialDistGUI->addSlider("Lambda", 0.5, 10.0, 1.0);
	exponentialDistGUI->autoSizeToFitWidgets();
	exponentialDistGUI->setWidth(211);
	exponentialDistGUI->setVisible(false);
	ofAddListener(exponentialDistGUI->newGUIEvent, this, &App::guiEvent);
	
	
	gaussDistGUI = new ofxUICanvas();
	gaussDistGUI->setFont("GUI/Lekton-Regular.ttf");
	gaussDistGUI->setPosition(210, 113);
	gaussDistGUI->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	gaussDistGUI->addSlider("Sigma", 0.1, 10.0, 0.15);
	gaussDistGUI->addSlider("Mu", -1.5, 1.5, 0.5);
	gaussDistGUI->autoSizeToFitWidgets();
	gaussDistGUI->setWidth(211);
	gaussDistGUI->setVisible(false);
	ofAddListener(gaussDistGUI->newGUIEvent, this, &App::guiEvent);
	
	
	cauchyDistGUI = new ofxUICanvas();
	cauchyDistGUI->setFont("GUI/Lekton-Regular.ttf");
	cauchyDistGUI->setPosition(210, 113);
	cauchyDistGUI->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	cauchyDistGUI->addSlider("Alpha", 0.1, 2.5, 1.0);
	cauchyDistGUI->autoSizeToFitWidgets();
	cauchyDistGUI->setWidth(211);
	cauchyDistGUI->setVisible(false);
	ofAddListener(cauchyDistGUI->newGUIEvent, this, &App::guiEvent);
	
	
	betaDistGUI = new ofxUICanvas();
	betaDistGUI->setFont("GUI/Lekton-Regular.ttf");
	betaDistGUI->setPosition(210, 113);
	betaDistGUI->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	betaDistGUI->addSlider("A", 0.1, 4.0, 0.5);
	betaDistGUI->addSlider("B", 0.1, 4.0, 0.5);
	betaDistGUI->autoSizeToFitWidgets();
	betaDistGUI->setWidth(211);
	betaDistGUI->setVisible(false);
	ofAddListener(betaDistGUI->newGUIEvent, this, &App::guiEvent);
	
	
	weibullDistGUI = new ofxUICanvas();
	weibullDistGUI->setFont("GUI/Lekton-Regular.ttf");
	weibullDistGUI->setPosition(210, 113);
	weibullDistGUI->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	weibullDistGUI->addSlider("T", 0.1, 10.0, 1.0);
	weibullDistGUI->addSlider("S", 0.1, 3.0, 1.0);
	weibullDistGUI->autoSizeToFitWidgets();
	weibullDistGUI->setWidth(211);
	weibullDistGUI->setVisible(false);
	ofAddListener(weibullDistGUI->newGUIEvent, this, &App::guiEvent);
	
	
	poissonDistGUI = new ofxUICanvas();
	poissonDistGUI->setFont("GUI/Lekton-Regular.ttf");
	poissonDistGUI->setPosition(210, 113);
	poissonDistGUI->addLabel("OPTIONS", OFX_UI_FONT_LARGE);
	poissonDistGUI->addSlider("lambda", 0.1, 100.0, 100.0);
	poissonDistGUI->autoSizeToFitWidgets();
	poissonDistGUI->setWidth(211);
	poissonDistGUI->setVisible(false);
	ofAddListener(poissonDistGUI->newGUIEvent, this, &App::guiEvent);
	
}


void App::setValuesForGraph(Distribution * d){
	
	vector<float> values = d->getValuesForGraphic(1000);
	
	float max = 0.0;
	for(int i = 0; i < values.size(); i++){
		if(values[i] > max)
			max = values[i];
	}
	
	mg->setBuffer(values);
	mg->setMax(max + 5);
	
}
