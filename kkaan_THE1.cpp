#include <iostream>
#include <string>


using namespace std; 

void getInput(string activity,int& minutes, int& reps){

	cout<<activity;
	cin>>minutes>>reps;

}


void getliftInput(string activity,int& mins,int& reps,int& liftedweigt){
	cout<<activity;
	cin>>mins>>reps>>liftedweigt;
}

bool inputCheck(int weight,int liftkg,int lungemins,int lungereps,int pushmins,int pushreps,int pullmins,int pullreps,int liftmins,int liftreps){
	if (weight<30){
		cout<<"Weight out of range!"<<endl;
		return false;
	}
	if (liftkg<=0 || liftkg>35){
		cout<<"Lifted weight out of range!"<<endl;
		return false;
	}
	if (lungereps<0 || lungereps>50 || pushreps<0 || pullreps>50 || pullreps<0 || pullreps>50 || liftreps<0 || liftreps>50){
		cout<<"Reps out of range!"<<endl;
		return false;
	}
	if (lungemins<0 || lungemins>2000 || pushmins<0 || pushmins>2000 || pullmins<0 || pullmins>2000 || liftmins<0 || liftmins>2000){
		cout<<"Minute out of range!"<<endl;
		return false;
	}
	return true;
}


void calculateMET(int lungerep,double& METlunge,int pushrep, double& METpush,int pullrep,double& METpull){
	if (lungerep<15){
		METlunge=3;
	}
	else if (lungerep>=15&& lungerep<30){
		METlunge=6.5;
	}
	else if (lungerep>=30){
		METlunge=10.5;
	}
	if (pushrep<15){
		METpush=4;
	}
	else {
		METpush=7.5;
	}

	if (pullrep<25){
		METpull=5;
	}
	else  {
		METpull=9;
	}

}

void calculateWeightLiftMET(int weightkg,int weightrep,double& MET4){
	if (weightkg<5){
		if (weightrep<20){
			MET4=3;
		}
		else if (weightrep>=20 && weightrep<40){
			MET4=5.5;
		}
		else if (weightrep>=40){
			MET4=10;
		}
	}
	else if (weightkg>5 && weightkg<15){
		if(weightrep<20){
			MET4=4;
		}
		else if (weightrep>=20 && weightrep<40){
			MET4=7.5;
		}
		else if (weightrep>=40){
			MET4=12;
		}
	}
	else if (weightkg>=15){
		if (weightrep<20){
			MET4=5;
		}
		else if (weightrep>=20 && weightrep<40){
			MET4=9;
		}
		else if (weightrep>=40){
			MET4=13.5;
		}
	}
}
void displayResults(int weight,double METlunge,double METpush,double METpull,double METweightlift,double& totalcal,double goal,double& difference){


	if (goal==totalcal){
		cout<<"Congratulations! You have reached your goal!"<<endl;
	}
	else if (totalcal>goal){
		cout<<"You have surpassed your goal! You can eat something worth "<<totalcal-goal<<" calories :)"<<endl;
	}
	else if(goal>totalcal){
		cout<<"You did not reach your goal by "<<difference<<" calories."<<endl;
		cout<<"You need to do lunges "<<(difference)/((METlunge*3.5*weight)/200)<<" minutes more to reach your goal or,"<<endl;
		cout<<"You need to do push ups "<<(difference)/((METpush*3.5*weight)/200)<<" minutes more to reach your goal or,"<<endl;
		cout<<"You need to do pull ups "<<(difference)/((METpull*3.5*weight)/200)<<" minutes more to reach your goal or,"<<endl;
		cout<<"You need to do weight lifting "<<(difference)/((METweightlift*3.5*weight)/200)<<" minutes more to reach your goal."<<endl;
	}

}

void computeResults(int lungemins,int weight,double METlunge,int pushmins,double METpush,int pullmins,double METpull,int liftingmins,double METweightlift,double goal){

	double callunge=lungemins*(METlunge*3.5*weight)/200;
	double calpush=pushmins*(METpush*3.5*weight)/200;
	double calpull=pullmins*(METpull*3.5*weight)/200;
	double callifting=liftingmins*(METweightlift*3.5*weight)/200;
	double totalcal=callunge+calpush+calpull+callifting;
	double difference=goal-totalcal;

	cout<<"From lunges, you burned "<<callunge<<" calories."<<endl;
	cout<<"From push ups, you burned "<<calpush<<" calories."<<endl;
	cout<<"From pull ups, you burned "<<calpull<<" calories."<<endl;
	cout<<"From weight lifting, you burned "<<callifting<<" calories."<<endl;
	cout<<"You burned "<<totalcal<<" calories."<<endl;
	cout<<""<<endl;



	displayResults(weight,METlunge,METpush,METpull,METweightlift,totalcal,goal,difference);
}



int main(){

	string name;

	int weight=0;
	int lungemins=0;
	int lungereps=0;
	int pushmins=0;
	int pushreps=0;
	int pullmins=0;
	int pullreps=0;
	int liftmins=0;
	int liftreps=0;
	int liftkg=0;
	double METlunge=0;
	double METpush=0;
	double METpull=0;
	double METweightlift=0;
	double goal=0;
	double callunge=0;
	double calpush=0;
	double calpull=0;
	double callifting=0;
	double totalcal=0;
	double difference=0;

	cout<<"Please enter your name: ";
	cin>>name;

	cout<<"Welcome "<<name<<", please enter your weight(kg): ";
	cin>>weight;

	cout<<name<<", please enter minutes and repetitions in a week for the activities below."<<endl;

	getInput("Lunges: ",lungemins,lungereps);
	getInput("Push Ups: ",pushmins,pushreps);
	getInput("Pull Ups: ",pullmins,pullreps);



	cout<<name<<", please enter minutes, repetitions and lifted weight in a week for the activities below."<<endl;
	getliftInput("Weight Lifting: ",liftmins,liftreps,liftkg);


	cout<<name<<", please enter your weekly calorie burn goal: ";
	cin>>goal;

	if (inputCheck(weight,liftkg,lungemins,lungereps,pushmins,pushreps,pullmins,pullreps,liftmins,liftreps)==false){
		return 0;
	}

	calculateWeightLiftMET(liftkg,liftreps,METweightlift);

	calculateMET(lungereps,METlunge,pushreps,METpush,pullreps,METpull);

	computeResults(lungemins,weight,METlunge,pushmins,METpush,pullmins,METpull,liftmins,METweightlift,goal);

	return 0; 
}
