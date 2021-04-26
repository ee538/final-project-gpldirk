#include <iostream>
#include "src/lib/trojanmap.h"
#include "src/lib/ncurses_wrapper.h"
#include <ncurses.h>
#include <string.h>


int main() {
  NCursesWrapper ncurses_wrapper;
  initscr();  // Start curses mode
  clear();  // clear screen
  keypad(stdscr, TRUE);  // read keyboard
  cbreak(); 
 
  start_color(); // Start color
  // Initialize some color pairs (foreground, background)
  init_pair(1,COLOR_RED,COLOR_BLACK);
  init_pair(2,COLOR_GREEN,COLOR_BLACK);
  init_pair(3,COLOR_YELLOW,COLOR_BLACK);
  init_pair(4,COLOR_BLUE,COLOR_BLACK);
  init_pair(5,COLOR_MAGENTA,COLOR_BLACK);
  init_pair(6,COLOR_CYAN,COLOR_BLACK);
  init_pair(7,COLOR_WHITE,COLOR_BLACK);

  // get the row and col of screen
  int row, col;
  getmaxyx(stdscr, row, col);
  attrset(A_BOLD);

  TrojanMap map;
  map.CreateGraphFromCSVFile();
  // map.PrintMenu();

  while(true) {
    std::vector<std::string> menu = {
      "                       EE599 - Trojan Map                     ",
      "**************************************************************",
      "* Select the function you want to execute.                    ",
      "* 1. Autocomplete                                             ",
      "* 2. Find the position                                        ",
      "* 3. CalculateShortestPath                                    ",
      "* 4. Travelling salesman problem                              ",
      "* 5. Cycle Detection                                          ",
      "* 6. Topological Sort                                         ",
      "* 7. Exit                                                     ",
      "**************************************************************",
    };
    int i = 0;
    for (i = 0; i < menu.size(); i++) {
      if (i >= 3 && i <= 9) {
        attrset(COLOR_PAIR(i - 2));
      }
      mvprintw(i, (col - menu[i].length()) / 2, "%s", menu[i].c_str());
    }
    attrset(COLOR_PAIR(1)|A_BOLD);

    std::string line = "              Please select 1 - 7: ";
    mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());
    
    char number = getch();  // Wait for user input for number
    clear();
    switch (number) {
      case '1': {
        menu = {
          "**************************************************************",
          "* 1. Autocomplete                                             ",
          "**************************************************************",
        };
        i = 0;
        for (i = 0; i < menu.size(); i++) {
          mvprintw(i, (col - menu[i].length()) / 2, "%s", menu[i].c_str());
        }

        line = "Please input a partial location: ";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());

        char temp[100];
        getstr(temp);
        std::string input(temp);

        auto start = std::chrono::high_resolution_clock::now();
        auto results = map.Autocomplete(input);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        clear();
        i = 0;
        line = "*************************Results******************************";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());

        if (results.size() != 0) {
          for (auto x: results) {
            mvprintw(i++, (col - x.length()) / 2, "%s", x.c_str());
          }
        } else {
          line = "No matched locations.";
          mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());
        }

        line = "**************************************************************";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());
        
        line = "Time taken by function: " + std::to_string(duration.count()) + " microseconds";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());

        line = "Press any key to continue.";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());
        getch();
        break;
      };
      case '2': {
        menu = {
          "**************************************************************",
          "* 2. Find the position                                        ",
          "**************************************************************",
        };
        i = 0;
        for (i = 0; i < menu.size(); i++) {
          mvprintw(i, (col - menu[i].length()) / 2, "%s", menu[i].c_str());
        }

        line = "Please input a location: ";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());

        char temp[100];
        getstr(temp);
        std::string input(temp);
        auto start = std::chrono::high_resolution_clock::now();
        auto results = map.GetPosition(input);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        clear();
        i = 0;
        line = "*************************Results******************************";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());

        if (results.first != -1) {
          line = "Latitude: " + std::to_string(results.first);
          mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());

          line = "Longitude: " + std::to_string(results.second);
          mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());

          map.PlotPoint(results.first, results.second);
        } else {
          line = "No matched locations.";
          mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());
        }
        line = "**************************************************************";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());
        
        line = "Time taken by function: " + std::to_string(duration.count()) + " microseconds";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());

        line = "Press any key to continue.";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());
        getch();
        break;
      };
      case '3': {
        menu = {
          "**************************************************************",
          "* 3. CalculateShortestPath                                    ",
          "**************************************************************",
        };
        i = 0;
        for (i = 0; i < menu.size(); i++) {
          mvprintw(i, (col - menu[i].length()) / 2, "%s", menu[i].c_str());
        }

        line = "Please input the start location: ";
        mvprintw(i++, col / 3, "%s", line.c_str());
        char temp[100];
        getstr(temp);
        std::string input1(temp);
    
        line = "Please input the destination: ";
        mvprintw(i++, col / 3, "%s", line.c_str());
        getstr(temp);
        std::string input2(temp);

        i++;
        menu = {
            "Please select the id of shortest path algorithms: ",
            "1 - Dijkstra",
            "2 - Bellman Ford (default)",
            "",
        };
        for (int j = 0; j < menu.size(); j++) {
          mvprintw(i++, col / 3, "%s", menu[j].c_str());
        }

        getstr(temp);
        std::string input3(temp);

        auto start = std::chrono::high_resolution_clock::now();
        std::vector<std::string> results;
        if (input3 == "1") {
          results = map.CalculateShortestPath_Dijkstra(input1, input2);
        } else {
          results = map.CalculateShortestPath_Bellman_Ford(input1, input2);
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        clear();
        i = 0;
        line = "*************************Results******************************";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());
    
        if (results.size() != 0) {
          for (auto x : results) {
            mvprintw(i++, (col - x.length()) / 2, "%s", x.c_str());
          }

          line = "The distance of the path is: " + std::to_string(map.CalculatePathLength(results)) + " miles";
          mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());
          map.PlotPath(results);
        } else {
          line = "No route from the start point to the destination.";
          mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());
        }

        line = "**************************************************************\n";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());
        line = "Time taken by function: " + std::to_string(duration.count()) + " microseconds";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());

        line = "Press any key to continue.";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());
        getch();
        break;
      };
      case '4': {
        menu = {
          "**************************************************************",
          "* 4. Travelling salesman problem                              ",
          "**************************************************************",
          "In this task, we will select N random points on the map and you need to find the path to travel these points and back to the start point.",
          "",
        };
        i = 0;
        for (i = 0; i < menu.size(); i++) {
          mvprintw(i, (col - menu[i].length()) / 2, "%s", menu[i].c_str());
        }

        line = "Please input the number of the places: ";
        mvprintw(i++, col / 3, "%s", line.c_str());

        char temp[100];
        getstr(temp);
        std::string input(temp);
        int num = std::stoi(input);

        std::vector<std::string> keys;
        for (auto x : map.data) { 
          keys.push_back(x.first);
        }
        std::vector<std::string> locations;
        srand(time(NULL));
        for (int j = 0; j < num; j++)
          locations.push_back(keys[rand() % keys.size()]);
        map.PlotPoints(locations);

        menu = {
          "",
          "Please select the id of TSP algorithms:",
          "1 - Brute Force",
          "2 - 2-opt Heuristic (default)",
          "",
        };
        for (int j = 0; j < menu.size(); j++) {
          mvprintw(i++, col / 3, "%s", menu[j].c_str());
        }

        getstr(temp);
        std::string xcinput(temp);
        num = std::stoi(input);
        line =  "Calculating ...";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());

        auto start = std::chrono::high_resolution_clock::now();
        std::pair<double, std::vector<std::vector<std::string>>> results;
        if (input == "1") {
          results = map.TravellingTrojan(locations);
        } else {
          results = map.TravellingTrojan_2opt(locations);
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        map.CreateAnimation(results.second);

        clear();
        i = 0;
        line = "*************************Results******************************";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());
    
        if (results.second.size() != 0) {
          for (auto x : results.second[results.second.size() - 1]) {
            mvprintw(i++, (col - x.length()) / 2, "%s", x.c_str());
          }

          line = "**************************************************************";
          mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());

          line = "The distance of the path is:" + std::to_string(results.first) + " miles";
          mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());

          map.PlotPath(results.second[results.second.size() - 1]);
        } else {
          line =  "The size of the path is 0";
          mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());
        }

        menu = {
          "**************************************************************",
          "     You could find your animation at src/lib/output.avi.     ",
        };
        for (int j = 0; j < menu.size(); j++) {
          mvprintw(i++, (col - menu[j].length()) / 2, "%s", menu[j].c_str());
        }
        
        line = "Time taken by function: " + std::to_string(duration.count()) + " microseconds";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());

        line = "Press any key to continue.";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());
        getch();
        break;
      };
      case '5': {
        menu = {
          "**************************************************************",
          "* 5. Cycle Detection                                          ",
          "**************************************************************",
        };
        i = 0;
        for (i = 0; i < menu.size(); i++) {
          mvprintw(i, (col - menu[i].length()) / 2, "%s", menu[i].c_str());
        }

        std::vector<double> square;
    
        line = "Please input the left bound longitude(between -118.299 and -118.264): ";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());
        char temp[100];
        getstr(temp);
        std::string left(temp);
        square.push_back(std::atof(left.c_str()));

        line = "Please input the right bound longitude(between -118.299 and -118.264): ";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());
        getstr(temp);
        std::string right(temp);
        square.push_back(atof(right.c_str()));

        line = "Please input the upper bound latitude(between 34.011 and 34.032): ";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());
        getstr(temp);
        std::string upper(temp);
        square.push_back(atof(upper.c_str()));
 
        line = "Please input the lower bound latitude(between 34.011 and 34.032): ";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());
        getstr(temp);
        std::string lower(temp);
        square.push_back(atof(lower.c_str()));

        auto start = std::chrono::high_resolution_clock::now();
        auto results = map.CycleDetection(square);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        clear();
        i = 0;
        line = "*************************Results******************************";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());
    
        if (results == true) {
          line = "there exists cycle in the subgraph";
          mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());
        } else {
          line = "there exist no cycle in the subgraph ";
          mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());
        }
        line = "**************************************************************";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());

        line = "Time taken by function: " + std::to_string(duration.count()) + " microseconds";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());

        line = "Press any key to continue.";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());
        getch();
        break;
      };
      case '6': {
        menu = {
          "**************************************************************",
          "* 6. Topological Sort                                         ",
          "**************************************************************",
        };
        i = 0;
        for (i = 0; i < menu.size(); i++) {
          mvprintw(i, (col - menu[i].length()) / 2, "%s", menu[i].c_str());
        }

        line = "Please input the locations filename: ";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());
        char temp[100];
        getstr(temp);
        std::string locations_filename(temp);

        line = "Please input the dependencies filename: ";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());
        getstr(temp);
        std::string dependencies_filename(temp);

        // Read location names from CSV file
        std::vector<std::string> location_names;
        if (locations_filename == "") 
          location_names = {"Cardinal Gardens", "Coffee Bean1","CVS"};
        else
          location_names = map.ReadLocationsFromCSVFile(locations_filename);
    
        // Read dependencies from CSV file
        std::vector<std::vector<std::string>> dependencies;
        if (dependencies_filename == "")
          dependencies = {{"Cardinal Gardens", "Coffee Bean1"}, {"Cardinal Gardens", "CVS"}, {"Coffee Bean1", "CVS"}};
        else
          dependencies = map.ReadDependenciesFromCSVFile(dependencies_filename);

        auto start = std::chrono::high_resolution_clock::now();
        auto result = map.DeliveringTrojan(location_names, dependencies);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        clear();
        i = 0;
        line = "*************************Results******************************";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());

        line = "Topological Sorting Reults: ";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());

        for (auto x : result) {
          mvprintw(i++, (col - x.length()) / 2, "%s", x.c_str());
        }

        std::vector<std::string> node_ids;
        for (auto x: result) {
          Node node = map.GetNode(x);
          node_ids.push_back(node.id);
        }
        map.PlotPointsOrder(node_ids);

        line = "**************************************************************";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());

        line = "Time taken by function: " + std::to_string(duration.count()) + " microseconds";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());

        line = "Press any key to continue.";
        mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());
        getch();
        break;
      }
      case '7':
        return 0;
      default: {
        // line = "              Please select 1 - 7: ";
        // mvprintw(i++, (col - line.length()) / 2, "%s", line.c_str());
        // break;
      }
    }
  }

  endwin();            // End curses mode
  return EXIT_SUCCESS;
}