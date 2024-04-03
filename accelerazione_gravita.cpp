/*
    c++ -o accelerazione_gravita accelerazione_gravita.cpp `root-config --glibs --cflags`
    ./accelerazione_gravita dati.txt
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#include "TF1.h"
#include "TH1F.h"
#include "TGraphErrors.h"
#include "TFitResult.h"
#include "TCanvas.h"
#include "TApplication.h"

#include "statisticheT.h"

using namespace std ;

double parabola (double * x, double * par) {
    return 0.5 * par[0] * pow (x[0], 2) + x[0] * par[1];
}

double test (double v, double o, double s_v, double s_o) {
    double num = abs (o - v) ;
    double den = sqrt (pow (s_o, 2) + pow (s_v, 2)) ;
    return num / den ;
}

double media_p (vector<double> const & campione, vector<double> const & campione_err) {
    double sumN = 0. ;
    double sumD = 0. ;
    for (int i = 0 ; i < campione.size () ; i++) {
        sumN += ( campione.at (i) / pow (campione_err.at (i), 2)) ;
        sumD += ( 1 / pow (campione_err.at (i), 2)) ;
    }
    return sumN / sumD ;
}

double sigma_p (vector<double> const & campione_err) {
    double sum = 0. ;
    for (int i = 0 ; i < campione_err.size () ; i++)
        sum += ( 1 / pow (campione_err.at (i), 2)) ;
    return 1 / sqrt (sum) ;
}

int main (int argc, char ** argv) {
    if (argc < 3) {
        cout << "usage: " << argv[0] << " dati.txt " << endl ;
        exit (1) ;
    }
    
    // leggo il file dei dati
    
    ifstream file_dati ;
    file_dati.open (argv[1]) ;
    
    //vector<double> v_t1 ;
    vector<double> v_t2 ;
    vector<double> v_t3 ;
    vector<double> v_t4 ;
    
    while (true) {
        //double evento1 ;
        double evento2 ;
        double evento3 ;
        double evento4 ;
        
        //file_dati >> evento1 ;
        file_dati >> evento2 ;
        file_dati >> evento3 ;
        file_dati >> evento4 ;
        
        if (file_dati.eof () == true) break ;
        
        //v_t1.push_back (evento1 * pow (10, -6)) ;
        v_t2.push_back (evento2 * pow (10, -6)) ;
        v_t3.push_back (evento3 * pow (10, -6)) ;
        v_t4.push_back (evento4 * pow (10, -6)) ;
    }
    
    file_dati.close () ;
    
    ifstream file_dati2;
    file_dati2.open (argv[2]) ;
    
    //vector<double> v_t5 ;
    vector<double> v_t6 ;
    vector<double> v_t7 ;
    vector<double> v_t8 ;
    
    while (true) {
        //double evento5 ;
        double evento6 ;
        double evento7 ;
        double evento8 ;
        
        //file_dati2 >> evento5 ;
        file_dati2 >> evento6 ;
        file_dati2 >> evento7 ;
        file_dati2 >> evento8 ;
        
        if (file_dati2.eof () == true) break ;
        
        //v_t5.push_back (evento5 * pow (10, -6)) ;
        v_t6.push_back (evento6 * pow (10, -6)) ;
        v_t7.push_back (evento7 * pow (10, -6)) ;
        v_t8.push_back (evento8 * pow (10, -6)) ;
    }
    
    file_dati2.close () ;
 /*   
    ifstream file_dati3 ;
    file_dati3.open (argv[3]) ;
    
    //vector<double> v_t9 ;
    vector<double> v_t10 ;
    vector<double> v_t11 ;
    vector<double> v_t12 ;
    
    while (true) {
        //double evento9 ;
        double evento10 ;
        double evento11 ;
        double evento12 ;
        
        //file_dati3 >> evento9 ;
        file_dati3 >> evento10 ;
        file_dati3 >> evento11 ;
        file_dati3 >> evento12 ;
        
        if (file_dati3.eof () == true) break ;
        
        //v_t9.push_back (evento9 * pow (10, -6)) ;
        v_t10.push_back (evento10 * pow (10, -6)) ;
        v_t11.push_back (evento11 * pow (10, -6)) ;
        v_t12.push_back (evento12 * pow (10, -6)) ;
    }
  
    file_dati3.close () ;
  */  
    /*for (int i = 0 ; i < v_t1.size () ; i++)
    {
        cout << v_t1.at (i) << "\t" << v_t2.at (i) << "\t" << v_t3.at (i) << "\t" << v_t4.at (i) << "\t" << v_t5.at (i) << "\t" << v_t6.at (i) << "\t" << v_t7.at (i) << "\t" << v_t8.at (i) << endl ;
    }*/
    
    cout << "numero misure: " << v_t2.size () << "\n\n" ;
    cout << "numero misure: " << v_t6.size () << "\n\n" ;
    //cout << "numero misure: " << v_t10.size () << "\n\n" ;
    
    
    double g = 9.80665 ; // accelerazione di gravità
    
    // distanze
    
    // 1
    //vector<double> y   = {0., 0.038, 0.157, 0.266, 0.400} ;
    //vector<double> y_s = {0., 0.00282, 0.00282, 0.00282, 0.00282} ;
    
    // 2
    //vector<double> y   = {0., 0.083, 0.192, 0.311, 0.442} ;
    //vector<double> y_s = {0., 0.00282, 0.00282, 0.00282, 0.00282} ;
    
    // 1+2
    vector<double> y   = { 0.109, 0.228, 0.359, 0.08, 0.209, 0.303} ;
    vector<double> y_s = { 0.00282, 0.00282, 0.00282, 0.00282, 0.00282, 0.00282} ;
    
    // calcolo media e deviazione standard per ogni ti
    
    vector<double> media_t = {//media (v_t1),
                              media (v_t2),
                              media (v_t3),
                              media (v_t4),
                              //media (v_t5),
                              media (v_t6),
                              media (v_t7),
                              media (v_t8)};
                              //media (v_t9),
                              //media (v_t10),
                              //media (v_t11),
                              //media (v_t12)} ;
    vector<double> dev_st_t = {//sigma (v_t1),
                               sigma (v_t2),
                               sigma (v_t3),
                               sigma (v_t4),
                               //sigma (v_t5),
                               sigma (v_t6),
                               sigma (v_t7),
                               sigma (v_t8)};
                               //sigma (v_t9),
                               //sigma (v_t10),
                               //sigma (v_t11),
                               //sigma (v_t12)} ;
    
    cout << "tempo \terrore \tpercentuale" << endl ;
    for (int i = 0 ; i < media_t.size () ; i++) {
        cout << media_t.at (i) << "\t" << dev_st_t.at (i) << "\t" << dev_st_t.at (i) / media_t.at (i) * 100 <<  endl ;
    }
    
    // disegno il tGraph
    
    TGraphErrors g_acc (media_t.size (), &media_t[0], &y[0], &dev_st_t[0], &y_s[0]) ;
    g_acc.SetMarkerStyle (4) ;
    g_acc.SetMarkerColor (kRed) ;
    g_acc.GetHistogram ()->GetXaxis ()->SetTitle ("t [s]") ;
    g_acc.GetHistogram ()->GetYaxis ()->SetTitle ("y [m]") ;
    g_acc.GetHistogram ()->GetYaxis ()->SetRangeUser (-0.05, 0.5) ;
    g_acc.GetHistogram ()->SetTitle ("FIT accelerazione di gravita'") ;
    
    TF1 f_acc ("f_acc", parabola, -1, 1, 2) ;
    f_acc.SetLineColor (kBlue) ;
    f_acc.SetParameter (0, g) ;
    
    // eseguo il fit
    
    cout << "\nFIT accelerazione di gravita'\n" << endl ;
    TFitResultPtr fit_result = g_acc.Fit (&f_acc, "S") ;
        
    cout << "\np_value: " << fit_result->Status () << endl ;
    cout << "par[0] =    " << f_acc.GetParameter (0) << " +- " << f_acc.GetParError (0) << endl ;
        
    cout << "\nprobabilità associata a Q2: " << fit_result->Prob () << endl ;
    cout << "valore di Q2:               " << fit_result->Chi2 () << endl ;
    cout << "valore di Q2 ridotto:       " << fit_result->Chi2 () / fit_result->Ndf () << endl ;
    cout << "gradi di libertà:           " << fit_result->Ndf () << "\n\n" ;
    
    // compatibilità con il valore atteso
    
    cout << "compatibilita' par[0] = g: " << test (g, f_acc.GetParameter (0), 0, f_acc.GetParError (0)) << endl ;
    cout << "errore percentuale g: " << f_acc.GetParError (0) / f_acc.GetParameter (0) * 100 << "\n\n" ;
    
    // stampo il grafico
    
    TApplication theApp ("theApp", &argc, argv);
    
    TCanvas c ("g_acc", "accelerazione") ;
    g_acc.Draw ("AP") ;
    c.Print ("accelerazione.pdf", "pdf") ;
    
    theApp.Run () ;
    
    return 0 ;
}
