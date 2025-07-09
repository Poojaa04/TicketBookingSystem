#include<iostream>
#include<fstream>
#include "../external/json.hpp"
#include "../entities/train.hpp"

using namespace std;
using json = nlohmann::json;

template<typename T>
class FileIO{
     private:
     const string filename = "db.json";

     public:
     void saveToFile(T entity){
          json j;
          ifstream file(filename);

          if(file.is_open()){
               file>>j;
               file.close();
          }

          json entityJson = {
               {"trainId",entity.trainId},
               {"name",entity.name},
               {"source",entity.source},
               {"destination",entity.destination},
               {"time",entity.time}
          };

          j.push_back(entityJson);

          ofstream outFile(filename);
          outFile << j.dump(4);
          outFile.close();
     }

     vector<T> readFromFile(){
          vector<T> entities;
          ifstream file(filename);

          if(!file.is_open()){
               return entities;
          }

          json j;
          file >> j;
          file.close();

          for(const auto& item :j){
               T entity;
               entity.trainId = item["trainId"];
               entity.name = item["name"];
               entity.source=item["destination"];
               entity.destination = item["destination"];
               entity.time = item["time"];

               entity.seats.clear();
        for (const auto& rowJson : item["seats"]) {
            vector<User> row;
            for (const auto& userJson : rowJson) {
                User user;
                user.userId = userJson["userId"];
                user.name = userJson["name"];
                user.aadharCard = userJson["aadharCard"];
                row.push_back(user);
            }
            entity.seats.push_back(row);
           }
               entities.push_back(entity);
          }

          return entities;
     }
};

template class FileIO<Vehicle>;
template class FileIO<Train>;