#ifndef GENERAL_PRINT_FUNCTIONS_H_INCLUDED
#define GENERAL_PRINT_FUNCTIONS_H_INCLUDED

#include "Neighbor.h"
#include "City_Graph.h"
#include <algorithm>

using namespace std;

class GeneralPrintFunctions
{
public:
    //Print function to print headings and heading with content
    static void PrintBox(const string& heading, const string& content, bool error)
    {
        string identifier = error ? "!" : "*";

        //making sure it is even number
        int header_size = heading.size() + heading.size() % 2;
        int content_size = content.size() + content.size() % 2;

        int box_content_size = max(header_size, content_size);
        int side_banner_size = 5;
        string border_line = identifier;
        string empty_line = identifier;
        for (int i = 0; i < side_banner_size + box_content_size + side_banner_size; i++)
        {
            border_line.append(identifier);
            empty_line.append(" ");
        }
        border_line.append(identifier);
        empty_line.append(identifier);

        cout << endl << endl;
        cout << border_line << endl;
        cout << empty_line << endl;
        cout << identifier;
        for (int i = 0; i < side_banner_size + (box_content_size - header_size) / 2; i++) cout << " ";
        cout << heading << (heading.size() % 2 == 1 ? " " : "");
        for (int i = 0; i < side_banner_size + (box_content_size - header_size) / 2; i++) cout << " ";
        cout << identifier << endl;
        cout << empty_line << endl;
        if (content.size() > 0)
        {
            cout << identifier;
            for (int i = 0; i < side_banner_size + (box_content_size - content_size) / 2; i++) cout << " ";
            cout << content << (content.size() % 2 == 1 ? " " : "");;
            for (int i = 0; i < side_banner_size + (box_content_size - content_size) / 2; i++) cout << " ";
            cout << identifier << endl;
            cout << empty_line << endl;
        }
        cout << border_line << endl;
        cout << endl;
    }

    static void PrintBox(const string& heading, const string& content)
    {
        PrintBox(heading, content, false);
    }

    static void PrintBox(const string& heading)
    {
        PrintBox(heading, "", false);
    }

    static void PrintErrorBox(const string& heading, const string& content)
    {
        PrintBox(heading, content, true);
    }

    //Print function to print all city distances and paths to origin city
    static void PrintAllCityDistanceAndPathsToOrigin(const vector<Neighbor>& closed_set)
    {
        int city_count = 0;
        for (Neighbor city : closed_set)
        {
            //print city and distance to origin
            ++city_count;
            if (city.nearest_neighbor_index >= 0)
                printf("%2d  (%2d |%2d)", city_count, city.index, city.distance);
            else
            {
                printf("%2d  (origin)\n", city_count);
                continue;
            }

            //print shortest path to origin city
            int cities_in_path = 0;
            Neighbor nearest_city = city;
            do
            {
                if (cities_in_path != 0 && cities_in_path % 6 == 0)
                    cout << " ->\n\t    ";
                for (Neighbor next_city : closed_set)
                    if (next_city.index == nearest_city.nearest_neighbor_index)
                    {
                        nearest_city = next_city;
                        break;
                    }
                cout << " -> ";
                if (nearest_city.nearest_neighbor_index >= 0)
                    printf("(%2d |%2d)", nearest_city.index, nearest_city.distance);
                else
                    printf("(origin)");
                cities_in_path++;
            } while (nearest_city.nearest_neighbor_index >= 0);

            cout << endl;
        }
        cout << "\nconnected cities " << closed_set.size();
        //no endl here so be sure to print something and end line or just end line
    }

    //Print function to print all city distances and paths to origin city
    static void PrintMSTPathsToOrigin(const vector<Neighbor>& closed_set)
    {
        Neighbor origin_city = closed_set.front();

        list<Neighbor> open_set;

        //push all MST nodes to open_set
        for (Neighbor city : closed_set)
            open_set.push_back(city);

        //list to store MST branches
        list<list<Neighbor>> MST_Branches;

        //list of removed city indices
        list<int> removed_city_indices;

        //find the longest branch, remove it from openset and move it to MST_Branches
        while (open_set.size() != 0)
        {
            int max_cities_in_path = -1;
            int max_cities_in_path_leaf_city_index = -1;
            for (Neighbor city : open_set)
            {
                int cities_in_path = 0;
                Neighbor nearest_city = city;
                do
                {
                    for (Neighbor next_city : open_set)
                        if (next_city.index == nearest_city.nearest_neighbor_index)
                        {
                            nearest_city = next_city;
                            break;
                        }
                    cities_in_path++;
                } while (nearest_city.nearest_neighbor_index >= 0 && count(removed_city_indices.begin(), removed_city_indices.end(), nearest_city.nearest_neighbor_index) == 0);
                if (cities_in_path > max_cities_in_path)
                {
                    max_cities_in_path = cities_in_path;
                    max_cities_in_path_leaf_city_index = city.index;
                }
            }
            //remove this path and add to MST_Branches
            list<Neighbor> branch;
            do
            {
                for (auto iterator = open_set.begin(); iterator != open_set.end(); iterator++)
                {
                    if (iterator->index == max_cities_in_path_leaf_city_index)
                    {
                        //remove this
                        branch.push_back(*iterator);
                        removed_city_indices.push_back(iterator->index);
                        max_cities_in_path_leaf_city_index = iterator->nearest_neighbor_index;
                        open_set.erase(iterator);
                        break;
                    }
                }
            } while (max_cities_in_path_leaf_city_index >= 0 && count(removed_city_indices.begin(), removed_city_indices.end(), max_cities_in_path_leaf_city_index) == 0);
            MST_Branches.push_back(branch);
        }

        int branch_count = 0;
        for (list<Neighbor> branch : MST_Branches)
        {
            ++branch_count;
            printf("   %2d    ", branch_count);
            
            //print shortest path to origin city
            int cities_in_path = 1;
            int nearest_neighbor_index = -1;
            for(Neighbor city : branch)
            {
                if (city.nearest_neighbor_index >= 0)
                    printf("(%2d |%2d) -> ", city.index, city.distance);
                else
                    printf("(origin)");
                nearest_neighbor_index = city.nearest_neighbor_index;
                if (cities_in_path != 0 && cities_in_path % 6 == 0 && nearest_neighbor_index != -1)
                    cout << "\n\t\t  -> ";
                cities_in_path++;
            }
            if(nearest_neighbor_index != -1)
                if(nearest_neighbor_index > 0)
                    printf("(%2d )", nearest_neighbor_index);
                else
                    printf("(origin)");
            cout << endl;
        }
        cout << "\nconnected cities " << closed_set.size();
        //no endl here so be sure to print something and end line or just end line
    }

    //Print function to print contents of open set priority queue
    template <typename T>
    static void PrintOpenSet(T p)
    {
        T q = p;
        cout << "Open Set: ";
        while (!q.empty())
        {
            cout << '\t' << static_cast<Neighbor>(q.top()).distance;
            q.pop();
        }
        cout << endl;
    }

    static void PrintCityGraphMatrix(const CityGraph* city_graph_ptr, bool print_connectivity_matrix)
    {
        cout << (print_connectivity_matrix ? "Connectivity Matrix:\n\n" : "Distance Matrix:\n\n");
        
        int pages = city_graph_ptr->size_ / city_graph_ptr->kmax_print_columns_to_show_per_page_;
        for (int p = 0; p <= pages; p++)
        {
            cout << "Cities:\t";
            for (int i = p * city_graph_ptr->kmax_print_columns_to_show_per_page_; i < min(city_graph_ptr->size_, (p + 1) * city_graph_ptr->kmax_print_columns_to_show_per_page_); i++)
                printf("|  %2d\t", i);
            cout << endl << "--------";
            for (int i = p * city_graph_ptr->kmax_print_columns_to_show_per_page_; i < min(city_graph_ptr->size_, (p + 1) * city_graph_ptr->kmax_print_columns_to_show_per_page_); i++)
                cout << "|-------";
            cout << endl;
            for (int i = 0; i < city_graph_ptr->size_; i++)
            {
                cout << "   " << i << "\t";
                for (int j = p * city_graph_ptr->kmax_print_columns_to_show_per_page_; j < min(city_graph_ptr->size_, (p + 1) * city_graph_ptr->kmax_print_columns_to_show_per_page_); j++)
                {
                    cout << "|  ";
                    if (i == j)
                        printf(" -");
                    else if (city_graph_ptr->city_connectivity_matrix_[i][j])
                        if (print_connectivity_matrix)
                            cout << " E";
                        else
                            printf("%2d", city_graph_ptr->city_distance_matrix_[i][j]);
                    cout << "\t";
                }
                cout << endl;
            }
            cout << endl;
        }
    }
};

#endif // !GENERAL_PRINT_FUNCTIONS_H_INCLUDED
