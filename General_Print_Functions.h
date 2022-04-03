#ifndef GENERAL_PRINT_FUNCTIONS_H_
#define GENERAL_PRINT_FUNCTIONS_H_

#include <algorithm>
#include <chrono>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "Neighbor.h"

class GeneralPrintFunctions
{
public:

    template<typename T>
    static std::string FormatSmallNumber(const char* formatter, T number, int size)
    {
        char char_arr[20];
        snprintf(char_arr, size+1, formatter, number);
        return std::string(char_arr);
    }

    static std::string FormatThousandSeparators(std::string input_str)
    {
        int digits = static_cast<int>(input_str.size());
        int counter = 1;
        reverse(input_str.begin(), input_str.end());
        while (digits > 3 * counter)
        {
            input_str.insert(3 * counter + counter - 1, ",");
            counter++;
        }
        input_str.resize(15, ' ');
        reverse(input_str.begin(), input_str.end());
        return input_str;
    }

    static std::string CalculateTimeTaken(std::string description, std::chrono::high_resolution_clock::time_point t0, std::chrono::high_resolution_clock::time_point t1)
    {
        description.resize(50, ' ');
        description += ":";
        auto time_span = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);
        double time_difference = static_cast<double>(time_span.count());
        const int digits_in_time = 15;
        char time_difference_char_arr[digits_in_time];
        snprintf(time_difference_char_arr, digits_in_time, "%.0f", time_difference);
        std::string time_difference_string(time_difference_char_arr);
        return description + FormatThousandSeparators(time_difference_string) + " microseconds";
    }

    //Print function to print headings and heading with content_string
    static void PrintBox(const std::string& heading, std::vector<std::string>* content_vector_ptr, bool error)
    {
        std::string identifier = error ? "!" : "*";

        //making sure heading and content_string is an even number
        int header_size = static_cast<int>(heading.size() + heading.size() % 2);
        
        int largest_content_string_size = 0;
        if (content_vector_ptr != NULL)
            for (auto content_string : *content_vector_ptr)
                if (static_cast<int>(content_string.size()) > largest_content_string_size)
                    largest_content_string_size = static_cast<int>(content_string.size());
        
        int content_box_size = std::max(header_size, (largest_content_string_size + largest_content_string_size % 2));
        int side_banner_size = 5;
        std::string border_line = identifier;
        std::string empty_line = identifier;
        for (int i = 0; i < side_banner_size + content_box_size + side_banner_size; i++)
        {
            border_line.append(identifier);
            empty_line.append(" ");
        }
        border_line.append(identifier);
        empty_line.append(identifier);

        std::cout << "\n\n";
        std::cout << border_line << '\n';
        std::cout << empty_line << '\n';
        std::cout << identifier;
        for (int i = 0; i < side_banner_size + (content_box_size - header_size) / 2; i++) std::cout << " ";
        std::cout << heading << (heading.size() % 2 == 1 ? " " : "");
        for (int i = 0; i < side_banner_size + (content_box_size - header_size) / 2; i++) std::cout << " ";
        std::cout << identifier << '\n';
        std::cout << empty_line << '\n';
        if (content_vector_ptr != NULL)
        {
            for (auto content_string : *content_vector_ptr)
            {
                std::cout << identifier;
                for (int i = 0; i < side_banner_size + (content_box_size - static_cast<int>(content_string.size())) / 2; i++) std::cout << " ";
                std::cout << content_string << (content_string.size() % 2 == 1 ? " " : "");;
                for (int i = 0; i < side_banner_size + (content_box_size - static_cast<int>(content_string.size())) / 2; i++) std::cout << " ";
                std::cout << identifier << '\n';
                std::cout << empty_line << '\n';
            }
        }
        std::cout << border_line << "\n\n";
    }

    static void PrintBox(const std::string& heading, std::vector<std::string> *content_vector_ptr)
    {
        PrintBox(heading, content_vector_ptr, false);
    }

    static void PrintBox(const std::string& heading, const std::string& content)
    {
        std::vector<std::string> content_vector { content };
        PrintBox(heading, &content_vector, false);
    }

    static void PrintBox(const std::string& heading)
    {
        PrintBox(heading, NULL, false);
    }

    static void PrintErrorBox(const std::string& heading, const std::string& content)
    {
        std::vector<std::string> content_vector{ content };
        PrintBox(heading, &content_vector, true);
        std::cout << std::flush;    //flushing output similar to cerr as this is error message
    }

    static const int kMaxPrintCitiesToShowPerRow = 6;

    //Print function to print all city distances and paths to origin city
    static void PrintAllCityDistanceAndPathsToOrigin(const std::vector<Neighbor>& closed_set)
    {
        std::cout << '\n';
        int city_count = 0;
        for (Neighbor city : closed_set)
        {
            //print city and distance to origin
            ++city_count;
            std::cout << GeneralPrintFunctions::FormatSmallNumber<int>("%2d", city_count, 2);
            std::cout << "  " << city;
            
            if (city.nearest_neighbor_id == Neighbor::kNullId)    //already at origin so there is no path ahead
            {
                std::cout << '\n';
                continue;
            }

            //print shortest path to origin city
            int cities_in_path = 0;
            Neighbor nearest_city = city;
            do
            {
                if (cities_in_path != 0 && cities_in_path % kMaxPrintCitiesToShowPerRow == 0)
                    std::cout << " ->\n\t    ";

                for (Neighbor city : closed_set)
                {
                    if (city.id == nearest_city.nearest_neighbor_id)
                    {
                        nearest_city = city;
                        break;
                    }
                }

                std::cout << " -> " << nearest_city;

                cities_in_path++;
            } while (nearest_city.nearest_neighbor_id > Neighbor::kNullId);

            std::cout << '\n';
        }

        std::cout << "\nconnected cities " << closed_set.size();
        //no std::endl here so be sure to print something and end line or just end line
    }

    //Print function to print all city distances and paths to origin city
    static void PrintMSTPathsToOrigin(const std::vector<Neighbor>& closed_set)
    {
        std::cout << '\n';

        std::list<Neighbor> open_set;

        //push all MST nodes to open_set
        for (Neighbor city : closed_set)
            open_set.push_back(city);

        //list to store MST branches
        std::list<std::list<Neighbor>> MST_Branches;

        //list of removed city indices
        std::list<int> removed_city_ids;

        //find the longest branch, remove it from openset and move it to MST_Branches
        while (open_set.size() != 0)
        {
            int max_cities_in_branch = -1;
            
            int branch_leaf_city_id = Neighbor::kNullId;

            for (Neighbor &city : open_set)
            {
                int cities_in_path = 0;
                Neighbor nearest_city = city;
                do
                {
                    for (Neighbor &next_city : open_set)
                    {
                        if (next_city.id == nearest_city.nearest_neighbor_id)
                        {
                            nearest_city = next_city;
                            break;
                        }
                    }
                    cities_in_path++;
                } while (nearest_city.nearest_neighbor_id >= 0 && count(removed_city_ids.begin(), removed_city_ids.end(), nearest_city.nearest_neighbor_id) == 0);

                if (cities_in_path > max_cities_in_branch)
                {
                    max_cities_in_branch = cities_in_path;
                    branch_leaf_city_id = city.id;
                }
            }
            //remove this path and add to MST_Branches
            std::list<Neighbor> branch;
            do
            {
                for (auto iterator = open_set.begin(); iterator != open_set.end(); iterator++)
                {
                    if (iterator->id == branch_leaf_city_id)
                    {
                        //remove this
                        branch.push_back(*iterator);
                        removed_city_ids.push_back(iterator->id);
                        branch_leaf_city_id = iterator->nearest_neighbor_id;
                        open_set.erase(iterator);
                        break;
                    }
                }
            } while (branch_leaf_city_id >= 0 && count(removed_city_ids.begin(), removed_city_ids.end(), branch_leaf_city_id) == 0);

            MST_Branches.push_back(branch);
        }

        int branch_count = 0;
        for (std::list<Neighbor> branch : MST_Branches)
        {
            ++branch_count;
            std::cout << "   " << GeneralPrintFunctions::FormatSmallNumber<int>("%2d", branch_count, 2) << "    ";
            
            //print shortest path to origin city
            int cities_in_path = 1;
            int nearest_neighbor_id = Neighbor::kNullId;
            for(Neighbor &city : branch)
            {
                std::cout << city;
                
                if (city.nearest_neighbor_id > Neighbor::kNullId)
                    std::cout << " -> ";

                nearest_neighbor_id = city.nearest_neighbor_id;
                
                if (cities_in_path != 0 && cities_in_path % kMaxPrintCitiesToShowPerRow == 0 && nearest_neighbor_id != Neighbor::kNullId)
                    std::cout << "\n\t\t  -> ";

                cities_in_path++;
            }
            if (nearest_neighbor_id != Neighbor::kNullId)
            {
                if (nearest_neighbor_id > Neighbor::kOriginCityId)
                    std::cout << "(" << GeneralPrintFunctions::FormatSmallNumber<int>("%2d", nearest_neighbor_id, 2) << " )";
                else
                    std::cout << Neighbor(Neighbor::kOriginCityId, 0);
            }
            std::cout << '\n';
        }
        std::cout << "\nconnected cities " << closed_set.size();
        //no std::endl here so be sure to print something and end line or just end line
    }

};

#endif // !GENERAL_PRINT_FUNCTIONS_H_