#include <iostream>
#include <string>
#include <vector>
#include "Neighbor.h"

using namespace std;

//Print function to print headings and heading with content
static void PrintBox(const string& heading, const string& content, bool error)
{
    string identifier = error ? "!" : "*";

    //making sure it is even number
    int headerSize = heading.size() + heading.size() % 2;
    int contentSize = content.size() + content.size() % 2;

    int boxContentSize = max(headerSize, contentSize);
    int sideBannerSize = 5;
    string borderLine = identifier;
    string emptyLine = identifier;
    for (int i = 0; i < sideBannerSize + boxContentSize + sideBannerSize; i++)
    {
        borderLine.append(identifier);
        emptyLine.append(" ");
    }
    borderLine.append(identifier);
    emptyLine.append(identifier);

    cout << endl << endl;
    cout << borderLine << endl;
    cout << emptyLine << endl;
    cout << identifier;
    for (int i = 0; i < sideBannerSize + (boxContentSize - headerSize) / 2; i++) cout << " ";
    cout << heading << (heading.size() % 2 == 1 ? " " : "");
    for (int i = 0; i < sideBannerSize + (boxContentSize - headerSize) / 2; i++) cout << " ";
    cout << identifier << endl;
    cout << emptyLine << endl;
    if (content.size() > 0)
    {
        cout << identifier;
        for (int i = 0; i < sideBannerSize + (boxContentSize - contentSize) / 2; i++) cout << " ";
        cout << content << (content.size() % 2 == 1 ? " " : "");;
        for (int i = 0; i < sideBannerSize + (boxContentSize - contentSize) / 2; i++) cout << " ";
        cout << identifier << endl;
        cout << emptyLine << endl;
    }
    cout << borderLine << endl;
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

//Print function to print all city distances to origin city and shortest paths to origin city
static void PrintAllCityDistanceAndPathsToOrigin(const string& heading, const vector<Neighbor>& closed_set, const float& avg_dist_)
{
    PrintBox(heading, "");

    cout << "##  ( City # | Shortest distance to origin city )  ->  Shortest Path" << endl;

    int cityCount = -1;
    for (Neighbor city : closed_set)
    {
        //print city and distance to origin
        ++cityCount;
        if (city.nearest_neighbor_index >= 0)
            printf("%2d  ( %3d | %2d )", cityCount, city.index, city.distance);
        else
        {
            printf("%2d  (  origin  )\n", cityCount);
            continue;
        }

        //print shortest path to origin city
        Neighbor nearest_city = city;
        do
        {
            for (Neighbor next_city : closed_set)
                if (next_city.index == nearest_city.nearest_neighbor_index)
                {
                    nearest_city = next_city;
                    break;
                }
            cout << "  ->  ";
            if (nearest_city.nearest_neighbor_index >= 0)
                printf("( %3d | %2d )", nearest_city.index, nearest_city.distance);
            else
                printf("(  origin  )");
        } while (nearest_city.nearest_neighbor_index >= 0);

        cout << endl;
    }
    cout << "\nconnected cities " << closed_set.size();
    printf(" | avg path length %0.2f\n\n", avg_dist_);
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