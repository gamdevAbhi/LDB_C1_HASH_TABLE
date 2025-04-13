#include <iostream>
#include <unordered_map>
#include <string>

std::unordered_map<std::string, int> player_map;

int main()
{
    int input = 1, score = 0;
    std::string player = "";
    
    std::cout << "add player -> 1\n" << "remove player -> 2\n" << "get player score -> 3\n" <<
    "get all players and their score -> 4\n" << "exit -> less than or equal 0" << std::endl;

    while(input > 0)
    {
        std::cout << "input : ";
        std::cin >> input;

        if(input <= 0) continue;

        if(input < 4)
        {
            std::cout << "player : ";
            std::cin.ignore();
            std::getline(std::cin, player);
        }
        
        switch(input)
        {
            case 1 :
            std::cout << "score : ";
            std::cin >> score;

            if(!player_map.try_emplace(player, score).second)
            {
                std::cerr << "player is already exist" << std::endl; 
            }
            
            break;

            case 2 :
            if(player_map.find(player) != player_map.end()) player_map.erase(player);
            else std::cerr << "player is not exist" << std::endl;
            break;

            case 3 :
            if(player_map.find(player) != player_map.end())
            {
                std::cout << "score : " << (*player_map.find(player)).second << std::endl;
            }
            else std::cerr << "player is not exist" << std::endl;
            break;

            case 4 :
            for(std::pair<std::string, int> pair : player_map)
            {
                std::cout << "player : " << pair.first << " score : " << pair.second << std::endl; 
            }
            break;

            default:
            std::cerr << "input is not valid";
            break;
        } 
    }

    return 0;
}