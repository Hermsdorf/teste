#include<iostream>
#include<vector>
#include<string>
#include<fstream>

#define LINE 1
#define TRIANGLE 2
#define QUADRANGLE 3
#define TETRAHEDRON 4
#define HEXAHEDRON 5

using namespace std;

int main()
{

    int ElementType[11] = {0,2,3,4,4,8,6,5,3,6,9};

    int n_elements = 0;
    int new_id = 1;
    string line;
    ifstream file;
    ofstream file_out;
    vector<int> data;
    data.reserve(10);
    
    

    file.open("esfera_box.msh", ios::in);
    if(!file.is_open())
    {
        cout << "Unable to open file" << endl;
        //return 0;
    }

    file_out.open("out.txt", ios::out);
    if(!file_out.is_open())
    {
        cout << "Unable to open file" << endl;
        //return 0;
    }

    getline(file,line); //$MeshFormat
    if(line != "$MeshFormat")
    {
        cout << "Invalid file format" << endl;
        //return 0;
    }
    file_out << line << endl;

    while(line != "$EndNodes")
    {
        getline(file,line);
        file_out << line << endl;
    }

    

    /*-----------Elements-----------*/

    getline(file,line); // $Elements;
    file_out << line << endl;
    cout << line << endl;
    if(line != "$Elements")
    {
        cout << "Invalid file format" << endl;
        //return 0;
    }
    file >> n_elements; getline(file,line);

    int d=0;
    for(int i=0; i<n_elements; i++)
    {
        file >> d ; data.push_back(d);//elements[i].ID() d0
        file >> d ; data.push_back(d);//elements[i].Type() d1
        if(d !=15)
        {
            file >> d ; data.push_back(d); //elements[i].Tag() d2
            for(int j=0; j<data[2]; j++)
            {
                file >> d ; data.push_back(d); //elements[i].tag
            }
            for(int j=0; j<ElementType[data[1]]; j++)
            {
                file >> d ; data.push_back(d); //elements[i].nodes[j] d4
            }

            data[0] = new_id ++; //elements[i].ID() d0

            for(int k = 0; k < data.size(); k++)
            {
                file_out << data[k] << " ";
            }
            file_out << endl;
            
        }        
        data.clear();
        getline(file,line);
        
    }
    getline(file,line); // $EndElements
    file_out << line << endl;

    file.close();
    file_out.close();
    cout << "Total Elements: " << new_id << endl;   
    return 0;

}