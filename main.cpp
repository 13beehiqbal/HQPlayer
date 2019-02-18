#include"ofApp.h"

int main()
{
	try{
		ofSetupOpenGL(1366,768,OF_WINDOW);			// <-------- setup the GL context

		// this kicks off the running of HQ Media Player
		ofRunApp(new ofApp());
		return 0;
	}
	catch (int n){
		if (n == -1){
			cout << "Extension not valid" << endl;
		}
		if (n == -2){
			cout << "This number is not in the middle" << endl;
		}

	}
}

//========================================================================
