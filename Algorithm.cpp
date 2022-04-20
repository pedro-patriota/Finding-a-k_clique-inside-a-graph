#include <iostream>
#include <string>
using namespace std;


struct logic_vertex{
    int inter_conections = 0; // stores the quantity of edges in each vertex inside the selected array
    int id;
};
struct agent_struct{
    string k_clique = "";
    int is_read = 0; // If the agent is already read
    int* num_conections; // stores the quantity of edges in each vertex

};



void insert_value(int** table[],int agent, int line, string str_values_in_line, agent_struct conections_per_agent[]){
    for (int column = 0; column < str_values_in_line.size(); column ++){ // Gets each digit of the matrix
        string temp;
        temp += str_values_in_line[column];
        int value  =  stoi(temp); // Make each digit an integer
        table[agent][line][column] = value; // stores it
        conections_per_agent[agent].num_conections[line] += value; // Add it in the num_conections of the given vertex
        conections_per_agent[agent].num_conections[column] += value;

    }
}

int recursive (int** table[], int agent ,int arr[], int size, int result, int num_vertex){
    int temp_arr[num_vertex]; 
    int temp_result = 0;
    int line = arr[size -1];
    if (size > 1){ // checks if the array has more than one vertex
        for (int i = 0; i <= size -2; i++){
            int column = arr[i];
            if (table[agent][line][column] == 1){
                temp_arr[temp_result] = column; // Reduces the new array to the vertex that had some conections with the previous array
                temp_result += 1; // saves the temporary number of conections in the largest vertex
            }
        }
        return recursive(table, agent, temp_arr, temp_result, result + temp_result, num_vertex);

    }
    else{
    return result; // total amount of conections among the largest vertex with the other vertex, recursively
    }
}


string find_k_clique(int k_clique,int num_vertexs, int agent, int**table[], agent_struct connections_per_agent[]){
    logic_vertex* aux_arr = new logic_vertex[num_vertexs];

    int size = 0;
    for (int i =0; i < num_vertexs;i++){
        if (connections_per_agent[agent].num_conections[i] >= k_clique -1){ // selects the vertexs that had the number of conections larger than k_clique-1
            aux_arr[size].id = i; // stores the selected vertexs
            size +=1;
            
        }
    }

    int correct_conections = (k_clique*(k_clique-1))/2; // the number of conections inside the clique
    
    for (int j = size -1; j > 0; j--){ // goes through the aux_arr getting the largest vertex and comparing if it has conections with the other ones
        int line = aux_arr[j].id;
        int recursive_arr[num_vertexs];
        for (int m = 0; m <= j-1; m++){
            int column = aux_arr[m].id;

            if (table[agent][line][column] == 1){
                recursive_arr[aux_arr[j].inter_conections] = column;  // Adds the possible selected array into the recursive array
                aux_arr[j].inter_conections += 1;
                
            }
        }
        if (aux_arr[j].inter_conections >= k_clique -1){ // if it does make more than k_clique -1 conections, so it is a possible pivot
            int value = recursive(table, agent, recursive_arr, aux_arr[j].inter_conections, 0, num_vertexs);
            
            if (value + aux_arr[j].inter_conections >= correct_conections){ // If the pivot and its recursive array have more than the necessary number of conections
                string answer;
                for (int i =0; i < aux_arr[j].inter_conections; i++ ){
                    answer +=  to_string(recursive_arr[i]) + " "; // answer
                }
                answer += to_string(aux_arr[j].id);
                
                return answer; // returns answer
            }
        }
    }
}


int main(){
    string my_input;
    int num_agents, vertexs, k_size, num_try;
    int  x_agent, y_agent;
    cin >> num_agents;
    cin >> vertexs;
    cin >> k_size;
    cin >> num_try;
    "Gets the input data";

    int** table[num_agents];
    agent_struct* aux_table = new agent_struct[num_agents];
    
    for (int i = 0; i < num_agents; i++){  // Creates a matrix for each agent
        aux_table[i].num_conections = new int[vertexs];
        table[i] = new int* [vertexs];
        for (int j = 0; j <  vertexs; j++){
            table[i][j] = new int[vertexs];
        }
        
    }
    
    

    for (int i =0; i <  num_try; i++){
        cin >> x_agent;
        cin >> y_agent;
        cin.ignore();

        string input;
    
        if (aux_table[x_agent].is_read == 0){ // Calculates the k_clique only once
            aux_table[x_agent].is_read = 1;
            
            for (int j = 0; j < vertexs -1; j++){
                getline(cin, input);
                insert_value(table, x_agent, j +1, input, aux_table); // Inserts each line inside the matrix
            }
            aux_table[x_agent].k_clique = find_k_clique(k_size, vertexs, x_agent, table, aux_table);
            
            
            
        }
        
        if (aux_table[y_agent].is_read == 0){ // Calculates the k_clique only once
            aux_table[y_agent].is_read = 1;
            
            for (int j = 0; j < vertexs -1; j++){
                getline(cin, input);
                insert_value(table, y_agent, j +1, input, aux_table); // Inserts each line inside the matrix
                
            }
            aux_table[y_agent].k_clique = find_k_clique(k_size, vertexs, y_agent, table, aux_table);
        }
        
        if (aux_table[x_agent].k_clique == aux_table[y_agent].k_clique){ // Checks if x_agent and y_agent have the same k_clique
            cout << "SUCC " << aux_table[x_agent].k_clique << "\n";
        }
        else{
            cout << "FAIL\n"; // If they are not the same
        }
        
        
    }
   
    delete[]aux_table; // Deletes each pointer
    delete[]**table;

    return 0;
}
