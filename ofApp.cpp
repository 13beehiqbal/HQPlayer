#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	HQplayer = new HQPlayer();
	listplay= new ofTrueTypeFont();
	searchedSong=NULL;
	min=max=0,searchedIndex=0;
	listplay->loadFont("LSANS.TTF",12);
	HQplayer->player->loadSound("E:\\Music\\Aitebar.mp3");
	ofSetCircleResolution(120);
	red = 233; blue = 233; green = 233;
	hideGUI = false;
	bdrawGrid = false;
	bdrawPadding = false;
	textInput = NULL;
	img = new ofImage();
	img->loadImage("1.jpg");

	nBandsToGet = 128;

	// the fft needs to be smoothed out, so we create an array of floats
	// for that purpose:
	fftSmoothed = new float[nBandsToGet];
	for (int i = 0; i < nBandsToGet; i++){
		fftSmoothed[i] = 0;
	}

	setGUI();
	song* readSong= new song();
	ifstream infile("playlist.txt");
	if(!infile)
		cout<<"Couldn't load the Playlist file"<<endl;
	else
	{
		while(!infile.eof())	
		{

			infile>>(*readSong);
			if(!infile.good())
				break;
			song* newSong=new song(readSong->count,readSong->get_name(),readSong->get_directory());
			HQplayer->get_playlist()->append(newSong);
			HQplayer->insert_trie(newSong);

		}
	}
	infile.close();
	infile.open("favourites.txt");
	if(!infile)
		cout<<"Couldn't load the Favourites file"<<endl;
	else
	{
		while(!infile.eof())	
		{

			infile>>(*readSong);
			if(!infile.good())
				break;
			song* newSong=new song(readSong->count,readSong->get_name(),readSong->get_directory());
			HQplayer->get_favourites()->append(newSong);
		}
	}
	infile.close();
	int count=HQplayer->get_playlist()->count;
	mostPlayed= new Heap(count);
	HQplayer->get_playlist()->move_to_start();
	for(int i=0;i<count;i++)
	{
		mostPlayed->insert(HQplayer->get_playlist()->get_song());
		HQplayer->get_playlist()->next();
	}
	HQplayer->get_playlist()->move_to_start();

	//gui3->loadSettings("gui3Settings.xml");
}

//--------------------------------------------------------------
void ofApp::update(){
	track->setValue(HQplayer->get_position()*100);
	if(track->getValue()<=100.0&&track->getValue()>=99.0){
		current->setLabel(HQplayer->next());
	}
	mostPlayed->sort();
	if(selection==1)
		playlist=HQplayer->display(min,max);
	else if (selection==2)
		playlist=HQplayer->display_favourites(min,max);
	else if (selection==3)
		playlist=HQplayer->get_recent()->display(min,max);
	else if (selection==4)
		playlist=mostPlayed->display(min,max);
	else if (selection==5)
		playlist=mostPlayed->neverdisplay(min,max);
	else if (selection ==6)
		playlist= HQplayer->get_trie()->display(textInput1->getTextString(),min,max);
	current->setLabel(HQplayer->current_song);
	range->setMax(HQplayer->get_playlist()->count);
	// update the sound playing system:
	ofSoundUpdate();	
	// (5) grab the fft, and put in into a "smoothed" array,
	//		by taking maximums, as peaks and then smoothing downward
	float * val = ofSoundGetSpectrum(nBandsToGet);		// request 128 values for fft
	for (int i = 0;i < nBandsToGet; i++){

		// let the smoothed calue sink to zero:
		fftSmoothed[i] *= 0.96f;

		// take the max, either the smoothed or the incoming:
		if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];

	}


}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(red, green, blue, 255);
	ofPushStyle();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	//ofSetColor(255,255,255,100);
	img->draw(ofGetWidth()/2,ofGetHeight()/2);


	equalizer0->setValue(fftSmoothed[0] * 100);
	equalizer1->setValue(fftSmoothed[5] * 300);
	equalizer2->setValue(fftSmoothed[10] * 300);
	equalizer3->setValue(fftSmoothed[15] * 500);
	equalizer4->setValue(fftSmoothed[20] * 500);
	equalizer5->setValue(fftSmoothed[25] * 700);
	equalizer6->setValue(fftSmoothed[30] * 700);
	equalizer7->setValue(fftSmoothed[35] * 700);
	equalizer8->setValue(fftSmoothed[40] * 700);
	equalizer9->setValue(fftSmoothed[53] * 1000);
	equalizer10->setValue(fftSmoothed[61] * 1000);
	equalizer11->setValue(fftSmoothed[68] * 1000);
	equalizer12->setValue(fftSmoothed[74] * 1000);
	equalizer13->setValue(fftSmoothed[80] * 1000);
	beats->setValue(fftSmoothed[0] * 80);




	listplay->drawString(playlist,0,20);
	if(bdrawGrid)
	{
		ofSetColor(255, 255, 255, 25);
		drawGrid(8,8);
	}

	ofPopStyle();

	ofSetRectMode(OF_RECTMODE_CENTER);
}

void ofApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.getName();
	int kind = e.getKind();
	cout << "got event from: " << name << endl;

	if(name == "ADD")
	{

		ofxUITextInput *is = (ofxUITextInput *) e.widget;
		ofDirectory dir(is->getTextString());
		dir.allowExt("mp3");
		int num = dir.listDir();
		for(unsigned int i=0;i<num;i++)
		{
			song* newSong=new song(0,dir.getName(i),dir.getPath(i));
			HQplayer->get_playlist()->append(newSong);
			HQplayer->insert_trie(newSong);
		}
	}
	else if(name == "Stop")
	{
		HQplayer->set_stop();
	}
	else if(name == "Pause")
	{
		HQplayer->set_pause();
	}
	else if(name == "SEARCH")
	{
		ofxUITextInput* input = (ofxUITextInput*)e.getButton();
		searchedIndex = ofToInt(input->getTextString());
		if (selection==2)
			searchedSong=HQplayer->get_favourites()->search(searchedIndex);
		else if (selection==3)
			searchedSong=HQplayer->get_recent()->search(searchedIndex);
		else if (selection==4)
			searchedSong=mostPlayed->search(searchedIndex);
		else if (selection==5)
			searchedSong=mostPlayed->neversearch(searchedIndex);
		else
			searchedSong=HQplayer->search(searchedIndex);

		deleteSearch->setVisible(true);
		markfavSearch->setVisible(true);
		queueSearch->setVisible(true);
		playSearch->setVisible(true);
	}
	else if(name == "SEARCH 2")
	{
		ofxUITextInput* input = (ofxUITextInput*)e.getButton();
		searchedSong=HQplayer->search(input->getTextString());
		deleteSearch->setVisible(true);
		markfavSearch->setVisible(true);
		queueSearch->setVisible(true);
		playSearch->setVisible(true);
		selection =6;
	}
	else if(name == "Play")
	{
		HQplayer->play_from_start();
	}
	else if(name == "Mute")
	{
		HQplayer->mute();
	}
	else if(name == "Next")
	{

		current->setLabel(HQplayer->next());
	}
	else if(name == "Previous")
	{

		HQplayer->previous();
	}
	else if(name == "Shuffle")
	{
		HQplayer->shuffle();
	}

	else if(name == "Repeat one")
	{
		HQplayer->repeat_one();
	}
	else if(name == "Repeat all")
	{
		HQplayer->repeat_all();
	}
	else if(name == "No repeat")
	{
		HQplayer->no_repeat();
	}
	else if(name == "Playlist")
	{
		selection=1;
	}
	else if(name == "Track")
	{
		ofxUISlider* sli = (ofxUISlider*) e.widget;
		HQplayer->set_position(sli->getValue()/100);
	}
	else if(name == "Volume")
	{
		ofxUIRotarySlider *vol = (ofxUIRotarySlider *) e.widget;
		float n=(float) vol->getValue()/100;
		HQplayer->set_volume(n); 
	}
	else if(name == "Fav")
	{
		HQplayer->mark_favourite(searchedSong);
		deleteSearch->setVisible(false);
		markfavSearch->setVisible(false);
		queueSearch->setVisible(false);
		playSearch->setVisible(false);

	}
	else if(name == "Favourites")
	{
		selection=2;
	}
	else if(name == "Recently Played")
	{
		selection =3;
	}
	else if(name == "Most Played")
	{
		selection=4;
	}
	else if(name == "Never Played")
	{
		selection=5;
	}
	else if(name == "Playlist Scroll")
	{
		ofxUIRangeSlider* scroll = (ofxUIRangeSlider *) e.widget;
		min=(int) scroll->getValueLow();
		max=(int) scroll->getValueHigh();
	}
	else if(name == "Play Searched")
	{
		HQplayer->play(searchedSong);
		deleteSearch->setVisible(false);
		markfavSearch->setVisible(false);
		queueSearch->setVisible(false);
		playSearch->setVisible(false);
	}
	else if(name == "Queue Searched")
	{
		HQplayer->queue_song(searchedSong);
		deleteSearch->setVisible(false);
		markfavSearch->setVisible(false);
		queueSearch->setVisible(false);
		playSearch->setVisible(false);

	}
	else if(name == "Delete Searched")
	{
		HQplayer->delete_song(searchedIndex,searchedSong);
		deleteSearch->setVisible(false);
		markfavSearch->setVisible(false);
		queueSearch->setVisible(false);
		playSearch->setVisible(false);

	}
	else if(name == "TEXT INPUT")
	{
		ofxUITextInput *ti = (ofxUITextInput *) e.widget;
		if(ti->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_ENTER)
		{
			cout << "ON ENTER: ";
		}
		else if(ti->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_FOCUS)
		{
			cout << "ON FOCUS: ";
		}
		else if(ti->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_UNFOCUS)
		{
			cout << "ON BLUR: ";
		}
		string output = ti->getTextString();
		cout << output << endl;
	}

	//HQplayer->no_repeat();
}

//--------------------------------------------------------------
void ofApp::exit()
{

	gui3->saveSettings("gui3Settings.xml");
	ofstream outfile("playlist.txt");
	if(!outfile)
		cout<<"Couldn't load the Playlist file"<<endl;
	else
	{
		HQplayer->get_playlist()->move_to_start();
		for(int i=0;i<HQplayer->get_playlist()->count;i++)	
		{
			outfile<<(*HQplayer->get_playlist()->get_song());
			HQplayer->get_playlist()->next();
		}
	}
	outfile.close();

	outfile.open("favourites.txt");
	if(!outfile)
		cout<<"Couldn't load the favourites file"<<endl;
	else
	{
		HQplayer->get_favourites()->move_to_start();
		for(int i=0;i<HQplayer->get_favourites()->get_count();i++)	
		{
			outfile<<(*HQplayer->get_favourites()->get_data());
			HQplayer->get_favourites()->next();
		}
	}
	outfile.close();

	delete HQplayer;
	delete listplay;
	delete gui3;
	delete img;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key)
	{

	case ']':
		{
			HQplayer->next();
			break;
		}
	case '[':
		{
			HQplayer->previous();
			break;
		}


	case '`':
		{
			ofToggleFullscreen();
			break;
		}
	case '.':
		{
			HQplayer->shuffle();
			break;
		}
	default:
		break;
	}
}

void ofApp::drawGrid(float x, float y)
{
	float w = ofGetWidth();
	float h = ofGetHeight();

	for(int i = 0; i < h; i+=y)
	{
		ofLine(0,i,w,i);
	}

	for(int j = 0; j < w; j+=x)
	{
		ofLine(j,0,j,h);
	}
}


void ofApp::setGUI()
{
	gui3 = new ofxUISuperCanvas("HQ MEDIA PLAYER");
	gui3->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	textInput2=gui3->addTextInput("ADD", "Add Song");
	textInput2->setTriggerOnClick(false);
	textInput2->setAutoClear(true);
	textInput2->setAutoUnfocus(true);
	gui3->addSpacer(150,0)->setColorBack(ofxUIColor(red, green, blue, 255));
	textInput = gui3->addTextInput("SEARCH", "Search by song number");
	textInput->setTriggerOnClick(false);
	textInput->setAutoClear(true);
	textInput->setAutoUnfocus(true); 
	textInput->setOnlyNumericInput(true);
	textInput1=gui3->addTextInput("SEARCH 2", "Search by song name");
	textInput1->setTriggerOnClick(false);
	textInput1->setAutoClear(true);
	textInput1->setAutoUnfocus(true); 
	gui3->setWidgetFontSize(OFX_UI_FONT_MEDIUM);
	gui3->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);

	gui3->addSpacer();

	vector<string> names;
	names.push_back("No repeat");
	names.push_back("Repeat all");
	names.push_back("Repeat one");
	gui3->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	gui3->addRadio("LOOPING", names, OFX_UI_ORIENTATION_HORIZONTAL);
	gui3->addSpacer(200,0);
	markfavSearch=gui3->addToggle("Fav",false);
	markfavSearch->setVisible(false);
	gui3->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
	gui3->addRotarySlider("Volume", 0.0, 100.0, 10.0,100,0.0,0.0,1);
	gui3->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	equalizer0=gui3->addSlider("0", 0.0, 255.0, 150, 34, 200);
	gui3->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	equalizer1=gui3->addSlider("1", 0.0, 250.0, 150, 34, 200);
	equalizer2=gui3->addSlider("2", 0.0, 250.0, 150, 34, 200);
	equalizer3=gui3->addSlider("3", 0.0, 250.0, 150, 34, 200);
	equalizer4=gui3->addSlider("4", 0.0, 250.0, 150, 34, 200);
	equalizer5=gui3->addSlider("5", 0.0, 250.0, 150, 34, 200);
	equalizer6=gui3->addSlider("6", 0.0, 250.0, 150, 34, 200);
	equalizer7=gui3->addSlider("7", 0.0, 250.0, 150, 34, 200);
	equalizer8=gui3->addSlider("8", 0.0, 250.0, 150, 34, 200);
	equalizer9=gui3->addSlider("9", 0.0, 250.0, 150, 34, 200);
	equalizer10=gui3->addSlider("10", 0.0, 250.0, 150, 34, 200);
	equalizer11=gui3->addSlider("11", 0.0, 250.0, 150, 34, 200);
	equalizer12=gui3->addSlider("12", 0.0, 250.0, 150, 34, 200);
	equalizer13=gui3->addSlider("13", 0.0, 250.0, 150, 34, 200);
	beats= gui3->addCircleSlider("Beats",0,250.0,150);

	gui3->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
	gui3->setWidgetFontSize(OFX_UI_FONT_SMALL);
	gui3->addLabelButton("Playlist",false);
	gui3->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	current= gui3->addLabel("Current", "Song Title", OFX_UI_FONT_SMALL);
	gui3->addSpacer(482,0);
	queueSearch=gui3->addLabelButton("Queue Searched",false);
	queueSearch->setVisible(false);
	gui3->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
	gui3->addLabelButton("Favourites",false);
	gui3->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	track=gui3->addSlider("Track",0.0,100.0,0.0,550,5);
	playSearch=gui3->addLabelButton("Play Searched",false);
	playSearch->setVisible(false);
	gui3->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
	gui3->addLabelButton("Recently Played",false);
	gui3->setWidgetFontSize(OFX_UI_FONT_SMALL);
	gui3->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	gui3->addSpacer(50,0);
	gui3->addImageButton("Shuffle","F:\\Downloads\\of_v0.8.4_vs_release\\of_v0.8.4_vs_release\\apps\\myApps\\HQMediaPlayer\\src\\shuffle.png",true,60.0,60.0);
	gui3->addImageButton("Stop","F:\\Downloads\\of_v0.8.4_vs_release\\of_v0.8.4_vs_release\\apps\\myApps\\HQMediaPlayer\\src\\stop.png",true,60.0,60.0);
	gui3->addImageButton("Previous","F:\\Downloads\\of_v0.8.4_vs_release\\of_v0.8.4_vs_release\\apps\\myApps\\HQMediaPlayer\\src\\previous.png",true,60.0,60.0);
	gui3->addImageButton("Play","F:\\Downloads\\of_v0.8.4_vs_release\\of_v0.8.4_vs_release\\apps\\myApps\\HQMediaPlayer\\src\\play.png",true,60.0,60.0);
	gui3->addImageButton("Next","F:\\Downloads\\of_v0.8.4_vs_release\\of_v0.8.4_vs_release\\apps\\myApps\\HQMediaPlayer\\src\\next.png",true,60.0,60.0);
	gui3->addImageToggle("Pause","F:\\Downloads\\of_v0.8.4_vs_release\\of_v0.8.4_vs_release\\apps\\myApps\\HQMediaPlayer\\src\\pause.png",true,60.0,60.0);
	gui3->addImageButton("Mute","F:\\Downloads\\of_v0.8.4_vs_release\\of_v0.8.4_vs_release\\apps\\myApps\\HQMediaPlayer\\src\\mute.png",true,60.0,60.0);
	gui3->addSpacer(32,0);
	deleteSearch=gui3->addLabelButton("Delete Searched",false);
	deleteSearch->setVisible(false);
	gui3->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
	gui3->addLabelButton("Most Played",false);
	gui3->addLabelButton("Never Played",false);

	range=gui3->addRangeSlider("Playlist Scroll",0.0,1000.0,0.0,100.0,950,12);
	range->setLabelPrecision(100);

	gui3->setDrawPadding(false);
	gui3->setGlobalButtonDimension(OFX_UI_GLOBAL_BUTTON_DIMENSION);
	gui3->setPosition(212*2, 0);
	gui3->autoSizeToFitWidgets();

	ofAddListener(gui3->newGUIEvent,this,&ofApp::guiEvent);
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
