#include <string>
#include <forward_list>

#ifndef M5_DATA_H
#define M5_DATA_H

typedef struct {//_entity{
    std::string Name;
    std::string Date;
    // T digSig
} entity;
typedef struct {//_m5Data {
    std::string propNum;
    std::string description;
    std::string serialNum;
    std::string sourceLoc;
    std::string destLoc;
    entity sourceSign;
    entity destSign;
} m5Data;//, *ptr_m5Data;
class m5Tracker{
private:
    std::forward_list<m5Data> flM5List;
public:
    m5Tracker()
    {
    }
    void TrackNewLoc(m5Data m5d)
    {
        flM5List.push_front(m5d);
    }
    void GetHistory()
    {
         for(;!flM5List.empty(); flM5List.pop_front()){
             m5Data m5d = flM5List.front();
             std::cout << "Entry: \n";
             std::cout << "Property Number: " << m5d.propNum << '\n';
             std::cout << "Description: " << m5d.description << '\n';
             std::cout << "Serial Numbers: " << m5d.serialNum << '\n';
             std::cout << "Old Location: " << m5d.sourceLoc << '\n';
             std::cout << "New Location: " << m5d.destLoc << '\n';
             std::cout << "Old Owner: " << m5d.sourceSign.Name << '\n';
             std::cout << "    Date Signed: " << m5d.sourceSign.Date << '\n';
             std::cout << "New Owner: " << m5d.destSign.Name << '\n';
             std::cout << "    Date Signed: " << m5d.destSign.Date << '\n';
         }
    }
};
#endif
