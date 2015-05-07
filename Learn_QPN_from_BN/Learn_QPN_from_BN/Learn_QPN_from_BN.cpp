// Learn_QPN_from_BN.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "meta_qpn_controller.h"
#include "plMt19937.h"
#include "pilgrim\general\pmBayesianNetwork.h"
#include "pilgrim\general\pmCSVDataSet.h"
#include "qpn_learner.h"


plMt19937 plMt19937::generator_;

using namespace std;
using namespace PILGRIM;

int _tmain(int argc, _TCHAR* argv[])
{
// Variable definitions
vector<string> adr_labels;
adr_labels.push_back("seul");
adr_labels.push_back("un_parmi_n");
adr_labels.push_back("non");

plLabelType labels(adr_labels);

plSymbol Spam("Spam", PL_BINARY_TYPE);
plSymbol Adress("Adress", labels);
plSymbol Viagra("Viagra", PL_BINARY_TYPE);
plSymbol Polytech("Polytech", PL_BINARY_TYPE);
plSymbol Felicitation("Felicitation", PL_BINARY_TYPE);

// Probability table of Spam
plProbValue tableSpam[] = {0.8, 0.2};
plProbTable P_Spam(Spam, tableSpam);

// Probability table of Adress, which depends on Spam
plProbValue tableAdress_knowing_Spam[] = {
	0.02, 0.2, 0.78,
	0.78, 0.2, 0.02
	};
plDistributionTable P_Adress(Adress, Spam, tableAdress_knowing_Spam);

// Probability table of Viagra, which depends on Spam
plProbValue tableViagra_knowing_Spam[] = {
	0.999, 0.001, 
	0.9, 0.1
	};
plDistributionTable P_Viagra(Viagra, Spam, tableViagra_knowing_Spam);

// Probability table of Polytech, which depends on Spam
plProbValue tablePolytech_knowing_Spam[] = {
	0.7, 0.3, 
	0.99, 0.01
	};
plDistributionTable P_Polytech(Polytech, Spam, tablePolytech_knowing_Spam);

// Probability table of Felicitation, which depends on Spam
plProbValue tableFelicitation_knowing_spam[] = {
	0.99, 0.01,
	0.7, 0.3
	};
plDistributionTable P_Felicitation(Felicitation, Spam, tableFelicitation_knowing_spam);

// Joint distribution
plJointDistribution jdSpam(Spam^Adress^Viagra^Polytech^Felicitation, P_Spam*P_Adress*P_Viagra*P_Polytech*P_Felicitation);

// Creation of Bayesian network
pmBayesianNetwork bnSpam(jdSpam);


qpn_learner learner = qpn_learner(&bnSpam);
learner.learn();
meta_qpn_controller qpn;

return 0;
}

