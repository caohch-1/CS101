#include <iostream>
#include <vector>

using namespace std;
vector<vector<int>> dis_mat; // 距离矩阵
int vertex_num; // 城市数量
int pop_size = 30; // 种群规模
int max_generation = 100; // 进化代数
vector<vector<int> > population; // 由各个访问城市序列组成的种群
vector<int> best_individual; //最优种群个体代表的城市排列
double transform_probability = 0.8;//交叉概率
double mutation_probability = 0.5;//变异概率
double best_solution = 1.79769e+308;

// 产生随机城市顺序 初始化种群
void initialize_population() {
    srand((int) time(nullptr) + rand()); // 随机数种子
    vector<int> sort_vector;
    for (int i = 1; i <= vertex_num; ++i) {
        sort_vector.emplace_back(i);
    }
    for (int i = 0; i < pop_size; ++i) {
        vector<int> temp = sort_vector;
        int cnt = 0;
        while (cnt < vertex_num * 2) {
            int first = rand() % vertex_num;
            int second = rand() % vertex_num;
            while (first == second) {
                second = rand() % vertex_num;
            }
            swap(temp[first], temp[second]);
            cnt++;
        }
        population.emplace_back(temp);
    }
}

// 计算个体的适应度值, 即该序列cost
double caculate_individual_distance(vector<int> individual) {
    double distance = 0.0;
    for (unsigned int i = 1; i < individual.size(); ++i) {
        distance += dis_mat[individual[i] - 1][individual[i - 1] - 1];
    }
    // 终点返回起点
    distance += dis_mat[individual[vertex_num - 1] - 1][individual[0] - 1];
    return distance * 1.0;
}

// 轮盘赌选择种群
void choose_individuals() {
    vector<double> individuals_fitness;
    vector<double> accumulate_probability;
    double population_fitness = 0;
    for (int i = 0; i < pop_size; ++i) {
        double cur_distance = caculate_individual_distance(population[i]);
        // 根据当前个体与当前代数下最优个体的适应度值的大小进行比较，对最优个体进行更新
        if (cur_distance < best_solution) {
            best_solution = cur_distance;
            best_individual = population[i];
        }
        double cur_fitness = 1.0 / cur_distance;
        individuals_fitness.emplace_back(cur_fitness);
        population_fitness += cur_fitness;
    }

    for (int i = 0; i < pop_size; ++i) {
        double probability = individuals_fitness[i] / population_fitness;
        // 轮盘赌法计算累积概率，对[0,1]进行划分
        if (i != 0) accumulate_probability.emplace_back(accumulate_probability[i - 1] + probability);
        else accumulate_probability.emplace_back(probability);
    }
    srand((int) time(nullptr) + rand());
    vector<vector<int> > newPopulation;
    for (int i = 0; i < pop_size; ++i) {
        // 生成0到1的随机数，落在哪个区间就选择哪个个体，重复pop_size次
        double randomly = rand() % 10000 * 0.0001;
        for (int j = 0; j < pop_size; ++j) {
            if (randomly < accumulate_probability[j]) {
                newPopulation.emplace_back(population[j]);
                break;
            }
        }
    }
    population.clear();
    population = newPopulation;
}

// 变异, 在城市序列中调换两个城市的顺序
void individual_mutation() {
    srand((int) time(nullptr) + rand());
    for (unsigned int i = 0; i < pop_size; ++i) {
        srand((int) time(nullptr) + rand());
        int start_index = rand() % vertex_num;
        int end_index = rand() % vertex_num;
        while (start_index >= end_index) {
            start_index = rand() % vertex_num;
            end_index = rand() % vertex_num;
        }

        double randomly = rand() % 10000 * 0.0001;
        if (randomly < mutation_probability) {
            // 基因位的交换
            swap(population[i][start_index], population[i][end_index]);
        }
    }
}

// 交叉
void individuals_transform() {
    srand((int) time(0) + rand());
    //使用内交叉法
    for (int i = 0; i < pop_size; i++) {
        double start_num = rand() % vertex_num;
        double end_num = rand() % vertex_num;
        int start_index = 1;
        int end_index = vertex_num - 1;
        for (int j = 0; j < vertex_num; j++) {
            if (population[i][j] == start_num) {
                start_index = j;
                break;
            }
        }
        //变异概率
        double transform1 = rand() % 10000 * 0.0001;
        if (transform1 < transform_probability) {
            end_num = rand() % vertex_num;
            while (start_num == end_num) {
                end_num = rand() % vertex_num;
            }
            for (int j = 0; j < vertex_num; j++) {
                if (population[i][j] == end_num) {
                    end_index = j;
                    break;
                }
            }
        }
            //likely crossover
        else {
            int other = rand() % pop_size;
            while (other == i) {
                other = rand() % pop_size;
            }
            for (int j = 0; j < vertex_num; j++) {
                if (population[other][j] == start_num) {
                    if (j == vertex_num - 1) {
                        end_num = population[other][j - 1];
                    } else {
                        end_num = population[other][j + 1];
                    }
                    break;
                }
            }
            for (int j = 0; j < vertex_num; j++) {
                if (population[i][j] == end_num) {
                    end_index = j;
                    break;
                }
            }
        }
        if (start_index > end_index) {
            int temp = start_index;
            start_index = end_index;
            end_index = temp;
        }

        //reverse the vertexs in individual between start_index and end_index
        vector<int> reverse;
        for (int j = start_index + 1; j <= end_index; j++) {
            reverse.emplace_back(population[i][j]);
        }
        int reverse_index = reverse.size() - 1;
        for (int j = start_index + 1; j <= end_index; j++) {
            population[i][j] = reverse[reverse_index];
            reverse_index--;
        }
    }
}


int main() {
    scanf("%d", &vertex_num);
    dis_mat.resize(vertex_num);
    for (int i = 0; i < vertex_num; ++i) {
        dis_mat[i].resize(vertex_num);
    }

    for (int i = 0; i < vertex_num; ++i) {
        for (int j = 0; j < vertex_num; ++j) {
            scanf("%d", &dis_mat[i][j]);
        }
    }

    initialize_population();
    for (int i = 0; i < max_generation; ++i) {
        choose_individuals();
        individual_mutation();
        individuals_transform();
    }
    vector<int> result = best_individual;
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}