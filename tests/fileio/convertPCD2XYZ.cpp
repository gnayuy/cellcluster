// convert PCD (.pcd) to XYZ (.off) data
//
// compilation: g++ -o convertPCD2XYZ convertPCD2XYZ.cpp
//

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

class Node
{
public:
    Node(){ n=0; x=y=z=0; intensity=0;}
    ~Node(){}
    
public:
    void copy(Node node){x = node.x; y = node.y; z = node.z; n = node.n; intensity = node.intensity;}
    
public:
    float x,y,z;
    int n;
    float intensity;
};


int main(int argc, char* argv[])
{
    // convertPCD2XYZ input.pcd output.xyz
    if(argc<3)
    {
        cout<<"usage: convertPCD2XYZ input.pcd output.xyz"<<endl;
        return -1;
    }
    
    // read input
    ifstream input(argv[1]);
    
    long npoints = -1;
    string line;
    vector<Node> nodeList;
    if (input.is_open())
    {
        while ( getline (input,line) )
        {
            if(strstr(line.c_str(),"#"))
            {
                cout << " skip comments" << endl;
            }
            else if(strstr(line.c_str(),"VERSION"))
            {
                // VERSION
            }
            else if(strstr(line.c_str(),"FIELDS"))
            {
                // FIELDS
            }
            else if(strstr(line.c_str(),"SIZE"))
            {
                // SIZE
            }
            else if(strstr(line.c_str(),"TYPE"))
            {
                // TYPE
            }
            else if(strstr(line.c_str(),"COUNT"))
            {
                // COUNT
            }
            else if(strstr(line.c_str(),"WIDTH"))
            {
                // WIDTH
            }
            else if(strstr(line.c_str(),"HEIGHT"))
            {
                // HEIGHT
            }
            else if(strstr(line.c_str(),"VIEWPOINT"))
            {
                // VIEWPOINT
            }
            else if(strstr(line.c_str(),"POINTS"))
            {
                // POINTS
                istringstream iss(line);
                
                if(iss.fail() || iss.eof())
                    continue;
                
                string points;
                iss >> points; // "POINTS"
                iss >> npoints;
                
            }
            else if(strstr(line.c_str(),"DATA"))
            {
                // DATA
            }
            else
            {
                istringstream iss(line);
                
                if(iss.fail() || iss.eof())
                    continue;
                
                Node node;
                
                iss >> node.x;
                iss >> node.y;
                iss >> node.z;
                
                nodeList.push_back(node);
            }
        }
        input.close();
    }
    else
    {
        cout << "Unable to open file"<<argv[1]<<endl;
    }
    
    long n = nodeList.size();
    
    //
    cout<<"Test: ... "<<n<<" = "<<npoints<<endl;
    
    // save output
    ofstream output(argv[2]);
    
    //
    float distx, disty, distz;
    
    distx = 0.5*(504100 - 103.53);
    disty = 0.5*(51627 - 289.57);
    distz = 0.5*(87856 - 4326.4);
    
    // .off
    output << "OFF\n";
    output << n << " 0 0 \n";
    output << endl;
    
    if (output.is_open())
    {
        for(int i=0; i<n; i++)
        {
            nodeList[i].x = distx * (nodeList[i].x + 1);
            nodeList[i].y = disty * (nodeList[i].y + 1);
            nodeList[i].z = distz * (nodeList[i].z + 1);
            
            output << nodeList[i].x << " " << nodeList[i].y << " " << nodeList[i].z << endl;
        }
        output.close();
    }
    else
    {
        cout << "Unable to open file"<<argv[2]<<endl;
    }
    
    //
    return 0;
}