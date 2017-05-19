// convert locations (x y z i f) to xyz/pcd data
//
// compilation: g++ -o convertRAW2XYZ convertRAW2XYZ.cpp
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
    // convertRAW2XYZ input.txt output.xyz
    if(argc<3)
    {
        cout<<"usage: convertRAW2XYZ input.txt output.xyz"<<endl;
        return -1;
    }
    
    // read input
    ifstream input(argv[1]);
    
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
            else
            {
                istringstream iss(line);
                
                if(iss.fail() || iss.eof())
                    continue;
                
                Node node;
                
                iss >> node.x;
                iss >> node.y;
                iss >> node.z;
                
                iss >> node.intensity;
                
                iss >> node.n;
                
                nodeList.push_back(node);
            }
        }
        input.close();
    }
    else
    {
        cout << "Unable to open file"<<argv[1]<<endl;
    }
    
    int n = nodeList.size();
    
    // statistics
    Node mean, min, max;
    
    for(int i=0; i<n; i++)
    {
        mean.intensity += nodeList[i].intensity;
        
        mean.x += nodeList[i].x;
        mean.y += nodeList[i].y;
        mean.z += nodeList[i].z;
        
        mean.n += nodeList[i].n;
        
        
        if(i==0)
        {
            min.copy(nodeList[i]);
            max.copy(nodeList[i]);
        }
        else
        {
            if(min.intensity > nodeList[i].intensity)
                min.intensity = nodeList[i].intensity;
            
            if(min.x > nodeList[i].x)
                min.x = nodeList[i].x;
            
            if(min.y > nodeList[i].y)
                min.y = nodeList[i].y;
            
            if(min.z > nodeList[i].z)
                min.z = nodeList[i].z;
            
            if(min.n > nodeList[i].n)
                min.n = nodeList[i].n;
            
            if(max.intensity < nodeList[i].intensity)
                max.intensity = nodeList[i].intensity;
            
            if(max.x < nodeList[i].x)
                max.x = nodeList[i].x;
            
            if(max.y < nodeList[i].y)
                max.y = nodeList[i].y;
            
            if(max.z < nodeList[i].z)
                max.z = nodeList[i].z;
            
            if(max.n < nodeList[i].n)
                max.n = nodeList[i].n;
        }
    }
    
    mean.intensity /= n;
    
    mean.x /= n;
    mean.y /= n;
    mean.z /= n;
    
    mean.n /= n;
    
    cout << "mean "<<mean.intensity << " " << mean.x << " " << mean.y << " " << mean.z << " " << mean.n <<endl;
    
    cout << "min "<<min.intensity << " " << min.x << " " << min.y << " " << min.z << " " << min.n <<endl;
    
    cout << "max "<<max.intensity << " " << max.x << " " << max.y << " " << max.z << " " << max.n <<endl;
    
    
    Node stddev;
    
    for(int i=0; i<n; i++)
    {
        stddev.intensity += (nodeList[i].intensity - mean.intensity) * (nodeList[i].intensity - mean.intensity);
        
        stddev.x += (nodeList[i].x - mean.x) * (nodeList[i].x - mean.x);
        stddev.y += (nodeList[i].y - mean.y) * (nodeList[i].y - mean.y);
        stddev.z += (nodeList[i].z - mean.z) * (nodeList[i].z - mean.z);
        
        stddev.n += (nodeList[i].n - mean.n) * (nodeList[i].n - mean.n);
    }
    
    stddev.intensity = sqrt( stddev.intensity / n);
    
    stddev.x = sqrt( stddev.x / n);
    stddev.y = sqrt( stddev.y / n);
    stddev.z = sqrt( stddev.z / n);
    
    stddev.n = sqrt( stddev.n / n);
    
    cout << "stddev "<<stddev.intensity << " " << stddev.x << " " << stddev.y << " " << stddev.z << " " << stddev.n <<endl;
    
    // save output
    ofstream output(argv[2]);
    
    string suffix = "pcd";
    
    if(argc > 3)
        suffix = argv[3];
    
    if(suffix == "pcd")
    {
        // .pcd
        output << "# .PCD v0.7 - Point Cloud Data file format\n";
        output << "VERSION 0.7\n";
        output << "FIELDS x y z\n";
        output << "SIZE 4 4 4\n";
        output << "TYPE F F F\n";
        output << "COUNT 1 1 1\n";
        output << "WIDTH "<<n<<"\n";
        output << "HEIGHT 1\n";
        output << "VIEWPOINT 0 0 0 1 0 0 0\n";
        output << "POINTS "<<n<<"\n";
        output << "DATA ascii\n";
        
        if (output.is_open())
        {
            for(int i=0; i<n; i++)
            {
                float dist = max.x - min.x;
                nodeList[i].x = 2 * nodeList[i].x / dist - 1;
                
                dist = max.y - min.y;
                nodeList[i].y = 2 * nodeList[i].y / dist - 1;
                
                dist = max.z - min.z;
                nodeList[i].z = 2 * nodeList[i].z / dist - 1;
                
                output << nodeList[i].x << " " << nodeList[i].y << " " << nodeList[i].z << endl;
            }
            output.close();
        }
        else
        {
            cout << "Unable to open file"<<argv[2]<<endl;
        }

        
    }
    else
    {
        // .off
        output << "OFF\n";
        output << n << " 0 0 \n";
        output << endl;
        
        if (output.is_open())
        {
            for(int i=0; i<n; i++)
            {
                output << nodeList[i].x - min.x << " " << nodeList[i].y - min.y << " " << nodeList[i].z - min.z << endl;
            }
            output.close();
        }
        else
        {
            cout << "Unable to open file"<<argv[2]<<endl;
        }

    }
    
    //
    return 0;
}