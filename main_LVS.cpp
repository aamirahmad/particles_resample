#include <stdio.h>
#include <string.h>
// #include <file.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <numeric>
#include <math.h>       /* isnan, sqrt */
#include "gnuplot-iostream.h"
#include <cmath>
#include <boost/tuple/tuple.hpp>

using namespace std;

int main(int argc, char** argv )
{
    
    if (__cplusplus == 201703L) std::cout << "C++17\n";
    else if (__cplusplus == 201402L) std::cout << "C++14\n";
    else if (__cplusplus == 201103L) std::cout << "C++11\n";
    else if (__cplusplus == 199711L) std::cout << "C++98\n";
    else std::cout << "pre-standard C++\n";    
    


    int n,i=0,N;
    //float random[n];
    cout << "Enter number of random numbers\n";
    cin >> n;
    int random[n];
    N=n;
  
    // print n random numbers using rand function
    cout << "Random numbers between 0 to 1000\n";
    while(n--){
        random[i] = rand()%1000 + 1.0;
        cout << random[i] << " ";
        i++;
    }
     

	Gnuplot gp;
    std::vector<boost::tuple<double, double, double, double> > particles, particles_resampled;
    float weights[N],cumulative_weight[N];
    float weight, sumOfWeights=0;
    float selector;
    
    
    
    for(i=0; i<N; i++)
    {
        weight = (float) rand()/(float)RAND_MAX;
		particles.push_back(boost::make_tuple(
			 random[i],0,0, weight
		));    
		weights[i] = weight;          
        sumOfWeights+=weight;
    }
    
    cout << endl <<"Normalized weights" << " ";
    for(i=0; i<N; i++)
    {
        weights[i]=weights[i]/sumOfWeights;
        cout << weights[i] << " ";
    }
    
    cumulative_weight[0] = weights[0];
    
    printf("we are here\n");
    cout << endl << "Cumulative weights = " << " ";
    for(i=1; i<N; i++)
    {
		cumulative_weight[i] = cumulative_weight[i-1] + weights[i];
        cout << cumulative_weight[i] << " ";
    }
    cout << endl;
    
    


	// Don't forget to put "\n" at the end of each line!
	gp << "set xrange [0:1000]\nset yrange [0:2]\n";
	gp << "plot '-' with vectors title 'particles'\n";   
    gp.send1d(particles);
    
    int selectedParticleIndex = 0;
    sleep(10);
    
    for(int j=0; j<50; j++)
    {
        sleep(1);
        gp << "plot '-' with vectors title 'particles'\n";  
        gp.send1d(particles);        
        sleep(1);
        
        selector = (float) rand()/(float)RAND_MAX;
        selector = selector*(1/(float)N - 0) + 0;
        //cout << endl <<"selector = " << selector << endl;
        float c = weights[0];
        int k=0; 
        float u=0;
        for(i=0; i<N; i++)
        {
            u = selector + i*(1/(float)N);
            while(u>c)
            {
                k++;
                c = c + weights[k];
            }
            selectedParticleIndex = k;

            
            particles_resampled.push_back(boost::make_tuple(
                get<0>(particles[selectedParticleIndex]),0.1,0, 0.1+sumOfWeights*weights[selectedParticleIndex]
            ));    
        }   
        
        gp << "plot '-' with vectors title 'particles', '-' with vectors title 'resampled particles LVS' lc 4\n";
        gp.send1d(particles);
        gp.send1d(particles_resampled);   
        
        
        particles.clear();
        sumOfWeights=0;
        
        for(i=0; i<N; i++)
        {
            particles.push_back(boost::make_tuple(
                get<0>(particles_resampled[i]),0,0, get<3>(particles_resampled[i])-0.1
            ));    
            weights[i] = get<3>(particles_resampled[i])-0.1;          
            sumOfWeights = sumOfWeights + get<3>(particles_resampled[i])-0.1;
        }
        
        cout << endl <<"Normalized weights" << " ";
        for(i=0; i<N; i++)
        {
            weights[i]=weights[i]/sumOfWeights;
            cout << weights[i] << " ";
        }
        
        cumulative_weight[0] = weights[0];
        
        printf("we are here\n");
        cout << endl << "Cumulative weights = " << " ";
        for(i=1; i<N; i++)
        {
            cumulative_weight[i] = cumulative_weight[i-1] + weights[i];
            cout << cumulative_weight[i] << " ";
        }
        cout << endl;        
        
        particles_resampled.clear();
        
        
     }
    
    
    


    return 0;
} 
