#include <string>
#include "m5_data.h"
#include "csv.h"

#ifndef READ_CSV_H
#define READ_CSV_H

//class EditCsv
//{
//    public:
std::vector<m5Data> read_csv(std::string filename)
{
    std::vector<m5Data> vect_m5d;
    io::CSVReader<8> in(filename);
    in.read_header(io::ignore_extra_column,"Property Number", "Description", 
                   "Source Location", "Destination Location", "Source Name",
                   "Source Date", "Destination Name", "Destination Date");
    std::string propNum, desc, srcLoc, destLoc, srcName, srcDate, destName, destDate;
    while(in.read_row(propNum, desc, srcLoc, destLoc, srcName, srcDate, destName, destDate)){
        m5Data m5d;
        m5d.propNum = propNum;
        m5d.description = desc;
        m5d.sourceLoc = srcLoc;
        m5d.destLoc = destLoc;
        m5d.sourceSign.Name = srcName;
        m5d.sourceSign.Date = srcDate;
        m5d.destSign.Name = destName;
        m5d.destSign.Date = destDate;
        vect_m5d.push_back(m5d);
    }
    return vect_m5d;
}
#endif
