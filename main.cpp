#include <iostream>
#include <getopt.h>
#include "m5_data.h"
#include "read_csv.h"

int main(int argc, char* argv[])
{
    std::string fname = "AssetLog.csv";
    int c_opts;
    static struct option long_options[] = 
    {
        {"read",required_argument,0,'r'},
        {0,0,0,0}
    };
    int option_index = 0;
    c_opts = getopt_long(argc,argv,"r:",long_options,&option_index);
    if(c_opts == -1){
        std::cout << "[ERROR] getopt_long failed to read the options list" << '\n';;
        exit(-1);
    }
    m5Tracker m5t;
    std::vector<m5Data> data;
    data = read_csv(fname);
    switch(c_opts){
        case 0:
            if (long_options[option_index].flag != 0) break;
            std::cout << "option " << long_options[option_index].name;
                if (optarg) std::cout << " with arg " << optarg;
                std::cout << '\n';
            break;
        case 'r':
            for(auto i : data){
                if(i.propNum == optarg) m5t.TrackNewLoc(i);
            }
            m5t.GetHistory();
            break;
    }
}
