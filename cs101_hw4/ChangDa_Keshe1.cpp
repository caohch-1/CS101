#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;
int vertex_num=6;
int pop_size;			                                //��Ⱥ��ģ
double transform_probability = 0.4;	//Ⱦɫ�彻�����
double tubian_probability=0.1;          //Ⱦɫ��������
vector<vector<int> > population;		//�ɸ������и���������ɵ���Ⱥ
double cur_best_distance=9999999;	    //��ǰ���������ž���
vector<int> cur_best_individual;		    //��ǰ�����¾�����̵ĳ�������
double best_solution=99999999;			//���д������̾���
vector<int> best_individual;                //���д������������Ⱥ�������ĳ�������
int d[6][6]={{0,15,20,12,8,6},
{15,0,17,9,11,24},
{20,17,0,19,13,8},
{12,9,19,0,17,6},
{8,11,13,17,0,8},
{6,24,8,6,8,0}};//���о������

double caculate_individual_distance(vector <int> individual){
	double distance=0.0;
	for (unsigned int i = 1; i < individual.size(); i++){
		double edge_length = d[individual[i]-1][individual[i-1]-1];
		distance += edge_length;
	}
	distance=distance+d[individual[5]-1][individual[0]-1];
	return distance * 1.0;
}
//�Ȳ���123456789����
void initialize_population(){
	srand((int)time(0) + rand());
	vector <int> sort_vector;
	for (int i = 1; i <= 6; i++){
		sort_vector.push_back(i);
	}
	for (int i = 0; i < pop_size; i++){
		vector <int> temp = sort_vector;
		int cnt = 0;
		while (cnt < vertex_num*2){
			int first = rand()% vertex_num;
			int second = rand()% vertex_num;
			while (first == second){
				second = rand()% vertex_num;
			}
			int exchange = temp[first];
			temp[first] = temp[second];
			temp[second] = exchange;
			cnt ++;
		}
		population.push_back(temp);
	}
	cout<<endl;
	cout<<"��Ⱥ��ʼ�����"<<endl;
}


void choose_individuals(){
	vector <double> individuals_fitness;
	vector <double> accumulate_probability;
    double population_fitness = 0;
	for (int i = 0; i < pop_size; i++){
		double cur_distance = caculate_individual_distance(population[i]);
		if (cur_distance < best_solution){
			best_solution = cur_distance;
			best_individual = population[i];
		}
		double cur_fitness = 1.0 / cur_distance;
		individuals_fitness.push_back(cur_fitness);
		population_fitness += cur_fitness;
	}
	for (int i = 0; i < pop_size; i++){
		double probability = individuals_fitness[i] / population_fitness;
		if (i != 0){
			accumulate_probability.push_back(accumulate_probability[i-1] + probability);
		}
		else{
			accumulate_probability.push_back(probability);
		}
	}
	srand((int)time(0) + rand());
	vector <vector<int> > newPopulation;
	for (int i = 0; i < pop_size; i++){
		double randomly = rand()%10000 * 0.0001;
        for (int j = 0; j < pop_size; j++){
            if (randomly < accumulate_probability[j]){
					newPopulation.push_back(population[j]);
					break;
				}
			}
    }
	population.clear();
	population = newPopulation;
}



////ͻ�����
void individual_tubian(){
    srand((int)time(0) + rand());
	for (unsigned int i = 0; i < pop_size; i++){
                srand((int)time(0) + rand());
                int start_index=rand()%6 ;
                int end_index=rand()%6;
            while (start_index>= end_index){
                start_index=rand()%6;
                end_index=rand()%6;
            }
            int t=0;
            double randomly = rand()%10000 * 0.0001;
            if(randomly<tubian_probability){
			t=population[i][start_index];
            population[i][start_index]=population[i][end_index];
            population[i][start_index]=t;
            }//���߽�������λ��֮�����������
      }
}



///�������
void individuals_transform(){
    srand((int)time(0) + rand());
	for (unsigned int i = 0; i < pop_size; i++){
                srand((int)time(0) + rand());
                int start_index=rand()%6 ;
                int end_index=rand()%6;
            while (start_index>= end_index){
                start_index=rand()%6;
                end_index=rand()%6;
            }
            int t=0;
            double randomly = rand()%10000 * 0.0001;
            if(randomly<tubian_probability){
			t=population[i][start_index];
            population[i][start_index]=population[i][end_index];
            population[i][start_index]=t;
            }//���߽�������λ��֮�����������
      }
    /*
	srand((int)time(0) + rand());
	//ʹ���ڽ��淨
	for (int i = 0; i < pop_size; i++){
		double start_num = rand()%6;
		double end_num=rand()%6;
		int start_index=1;
		int end_index=5;
		for (int j = 0; j < vertex_num; j++){
			if (population[i][j] == start_num){
				start_index = j;
				break;
			}
		}
		//�������
		double transform1 = rand()%10000 * 0.0001;
		if (transform1 < transform_probability){
			end_num = rand()%6;
			while (start_num == end_num){
				end_num = rand()%6;
			}
			for (int j = 0; j < vertex_num; j++){
				if (population[i][j] == end_num){
					end_index = j;
					break;
				}
			}
		}
		//likely crossover
		else{
			int other = rand() % pop_size;
			while (other == i){
				other = rand() % pop_size;
			}
			for (int j = 0; j < vertex_num; j++){
				if (population[other][j] == start_num){
					if (j == vertex_num - 1){
						end_num = population[other][j-1];
					}
					else{
						end_num = population[other][j+1];
					}
					break;
				}
			}
			for (int j = 0; j < vertex_num; j++){
				if (population[i][j] == end_num){
					end_index = j;
					break;
				}
			}
		}
		if (start_index > end_index){
			int temp = start_index;
			start_index = end_index;
			end_index = temp;
		}
		//reverse the vertexs in individual between start_index and end_index
		vector <int> reverse;
		for (int j = start_index + 1; j <= end_index; j++){
			reverse.push_back(population[i][j]);
		}
		int reverse_index = reverse.size() - 1;
		for (int j = start_index + 1; j <= end_index; j++){
			population[i][j] = reverse[reverse_index];
			reverse_index --;
		}
	}*/
}

int main(){
	int max_generation;
	cout << "please input the size of population (e.g.: 300): ";
	cin >> pop_size;
	cout <<	endl;
	cout << "please input the number of generation (e.g.: 10000): ";
	cin >> max_generation;
	cout <<	endl;
    initialize_population();
    ofstream output;
    //output.open("���\\5.txt");
	int generation = 0;
	while (generation < max_generation){
        choose_individuals();
        individual_tubian();
        individuals_transform();
		cout <<"the best in current generation: "<<best_solution<< endl;
        output <<generation << " "<<best_solution<< endl;
		generation ++;
	}
	vector <int> result = best_individual;
	for (int i = 0; i < result.size(); i++){
		cout << result[i]<<" ";
	}
	cout<<endl;
    system("pause");
}
