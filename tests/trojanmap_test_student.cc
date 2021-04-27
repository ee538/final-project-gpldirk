#include <map>
#include <vector>

#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"

// Test Autocomplete function
TEST(TrojanMapTest, Autocomplete) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test the empty string
  auto names = m.Autocomplete("");
  std::vector<std::string> gt1 = {}; // groundtruth for "Ch"
  EXPECT_EQ(names, gt1);

  // Test the uper case
  names = m.Autocomplete("ST");
  std::vector<std::string> gt2 = {"St Agnes Church", "St John39s CathedralHope Net", "Starbucks", "Student Union STU", "Starbucks Coffee"}; // groundtruth for "ch"
  EXPECT_EQ(names, gt2);

  // Test the lower case 
  names = m.Autocomplete("st "); 
  std::vector<std::string> gt3 = {"St Agnes Church", "St John39s CathedralHope Net"}; // groundtruth for "cH"
  EXPECT_EQ(names, gt3);
}

// Test FindPosition function
TEST(TrojanMapTest, FindPosition) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();

  // Test Crosswalk1
  auto position = m.GetPosition("Crosswalk1");
  std::pair<double, double> gt1(34.0302951, -118.2857237); // groundtruth for "ChickfilA"
  EXPECT_EQ(position, gt1);

  // Test Trojan Grounds Starbucks
  position = m.GetPosition("Trojan Grounds Starbucks");
  std::pair<double, double> gt2(34.0212898, -118.2824417); // groundtruth for "Ralphs"
  EXPECT_EQ(position, gt2);

  // Test Target
  position = m.GetPosition("Subway");
  std::pair<double, double> gt3(34.0118217, -118.2823019); // groundtruth for "Target"
  EXPECT_EQ(position, gt3);
}


// Test CalculateShortestPath_Dijkstra function 1
TEST(TrojanMapTest, CalculateShortestPath_Dijkstra) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();

  // Test from Subway to Expo ParkUSC
  auto path = m.CalculateShortestPath_Dijkstra("Subway", "Expo ParkUSC");
  std::vector<std::string> gt{
      "1759017530", "1855150081", "1870795259", "1870795261", "1870795272", "1870787389", "1870795282", "4020099348", "1870795287", "4060015480", "6814990128", "1870795293", "6814990112", "932378219", "6226313827", "7867091030", "7867091027", "6814990127", "4020099358", "4060015481", "1836105028", "122436252", "6820972451", "1732243549", "6820972450", "4020099365", "4060015482", "932416162", "6820935911", "1837212101", "1837212103", "6813411589", "216155217", "6813411590", "1472141024", "6813405280", "348121864", "348121996", "4059993475", "4399693649", "4399693648", "4015405549", "1781230450", "6820935898", "7023424980", "4399693644"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Expo ParkUSC to Subway
  path = m.CalculateShortestPath_Dijkstra("Expo ParkUSC", "Subway");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test CalculateShortestPath_Dijkstra function 2
TEST(TrojanMapTest, CalculateShortestPath_Dijkstra2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test from Department of Motor Vehicles to Subway
  auto path = m.CalculateShortestPath_Dijkstra("Department of Motor Vehicles", "Subway");
  std::vector<std::string> gt{
    "4732965439", "1932939400", "269633046", "6820972473", "5541778221", "1377766078", "269633572", "269633045", "6820972453", "2052181227", "6820972452", "6788057222", "6820972445", "6820935941", "6820972448", "1732243549", "6820972451", "122436252", "1836105028", "4060015481", "4020099358", "6814990127", "7867091027", "7867091030", "6226313827", "932378219", "6814990112", "1870795293", "6814990128", "4060015480", "1870795287", "4020099348", "1870795282", "1870787389", "1870795272", "1870795261", "1870795259", "1855150081", "1759017530"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Subway to Department of Motor Vehicles
  path = m.CalculateShortestPath_Dijkstra("Subway", "Department of Motor Vehicles");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test CalculateShortestPath_Dijkstra function 3
TEST(TrojanMapTest, CalculateShortestPath_Dijkstra3) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test from Student Union STU to Amazon Pick up Center
  auto path = m.CalculateShortestPath_Dijkstra("Student Union STU", "Amazon Pick up Center");
  std::vector<std::string> gt{}; // Expected path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Student Union STU to Amazon Pick up Center
  path = m.CalculateShortestPath_Dijkstra("Amazon Pick up Center", "Student Union STU");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}


// Test CalculateShortestPath_Bellman_Ford function 1
TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();

  // Test from Subway to Expo ParkUSC
  auto path = m.CalculateShortestPath_Bellman_Ford("Subway", "Expo ParkUSC");
  std::vector<std::string> gt{
      "1759017530", "1855150081", "1870795259", "1870795261", "1870795272", "1870787389", "1870795282", "4020099348", "1870795287", "4060015480", "6814990128", "1870795293", "6814990112", "932378219", "6226313827", "7867091030", "7867091027", "6814990127", "4020099358", "4060015481", "1836105028", "122436252", "6820972451", "1732243549", "6820972450", "4020099365", "4060015482", "932416162", "6820935911", "1837212101", "1837212103", "6813411589", "216155217", "6813411590", "1472141024", "6813405280", "348121864", "348121996", "4059993475", "4399693649", "4399693648", "4015405549", "1781230450", "6820935898", "7023424980", "4399693644"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Subway to Expo ParkUSC
  path = m.CalculateShortestPath_Bellman_Ford("Expo ParkUSC", "Subway");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test CalculateShortestPath_Bellman_Ford function 2
TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test from Department of Motor Vehicles to Subway
  auto path = m.CalculateShortestPath_Bellman_Ford("Department of Motor Vehicles", "Subway");
  std::vector<std::string> gt{
    "4732965439", "1932939400", "269633046", "6820972473", "5541778221", "1377766078", "269633572", "269633045", "6820972453", "2052181227", "6820972452", "6788057222", "6820972445", "6820935941", "6820972448", "1732243549", "6820972451", "122436252", "1836105028", "4060015481", "4020099358", "6814990127", "7867091027", "7867091030", "6226313827", "932378219", "6814990112", "1870795293", "6814990128", "4060015480", "1870795287", "4020099348", "1870795282", "1870787389", "1870795272", "1870795261", "1870795259", "1855150081", "1759017530"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Department of Motor Vehicles to Subway
  path = m.CalculateShortestPath_Bellman_Ford("Subway", "Department of Motor Vehicles");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test CalculateShortestPath_Bellman_Ford function 3
TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford3) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test from Student Union STU to Amazon Pick up Center
  auto path = m.CalculateShortestPath_Bellman_Ford("Student Union STU", "Amazon Pick up Center");
  std::vector<std::string> gt{}; // Expected path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Student Union STU to Amazon Pick up Center
  path = m.CalculateShortestPath_Bellman_Ford("Amazon Pick up Center", "Student Union STU");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}


// Test TSP function
TEST(TrojanMapTest, TSP) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"1873056015", "6905329551", "1931345270"}; // Input location ids 
  auto result = m.TravellingTrojan(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"1873056015", "1931345270", "6905329551", "1873056015"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) 
    flag = true;
  
  EXPECT_EQ(flag, true);
}

// Test TSP function 2
TEST(TrojanMapTest, TSP2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"1862312636", "67666219", "4015203110", "6807439002"}; // Input location ids 
  auto result = m.TravellingTrojan(input);
  std::cout << "My path length: " << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"1862312636", "4015203110", "6807439002", "67666219", "1862312636"}; // Expected order
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the groundtruth path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) // counterclockwise
    flag = true;
  EXPECT_EQ(flag, true);
}


// Test TSP function 3
TEST(TrojanMapTest, TSP3) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"123120189", "214470792", "63068532", "6807909279"}; // Input location ids 

  auto result = m.TravellingTrojan(input);
  std::cout << "My path length: " << result.first << "miles" << std::endl; // Print the result path lengths
  
  std::vector<std::string> gt{"123120189", "214470792", "6807909279", "63068532", "123120189"}; // Expected order
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the groundtruth path lengths

  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) // counterclockwise
    flag = true;
  
  EXPECT_EQ(flag, true);
}

// Test cycle detection function
TEST(TrojanMapTest, CycleDetection) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test case 1
  std::vector<double> square1 = {-118.294, -118.299, 34.022, 34.032};
  bool result1 = m.CycleDetection(square1);
  EXPECT_EQ(result1, false);

  // Test case 2
  std::vector<double> square2 = {-118.299, -118.294, 34.032, 334.022};
  bool result2 = m.CycleDetection(square2);
  EXPECT_EQ(result2, false);

  // Test case 3
  std::vector<double> square3 = {-118.298, -118.270, 34.030, 34.021};
  bool result3 = m.CycleDetection(square3);
  EXPECT_EQ(result3, true);
}

// Test topSort function
TEST(TrojanMapTest, TopologicalSort) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> location_names = {"Subway", "Coffee Bean1","CVS"};
  std::vector<std::vector<std::string>> dependencies = {{"Subway","Coffee Bean1"}, {"Subway","CVS"}, {"Coffee Bean1","CVS"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={"Subway", "Coffee Bean1","CVS"};
  EXPECT_EQ(result, gt);
}

// Test topSort function
TEST(TrojanMapTest, TopologicalSort2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> location_names = {"Target", "CVS", "Subway", "Raphs"};
  std::vector<std::vector<std::string>> dependencies = {{"Target","Raphs"}, {"Raphs","Subway"}, {"Subway", "CVS"}, {"CVS", "Target"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={};
  EXPECT_EQ(result, gt);
}

// Test topSort function
TEST(TrojanMapTest, TopologicalSort3) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> location_names = {"Target", "CVS", "Subway", "Raphs"};
  std::vector<std::vector<std::string>> dependencies = {{"Target","Raphs"}, {"Raphs","Subway"}, {"Subway", "CVS"}, {"CVS", "Raphs"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={};
  EXPECT_EQ(result, gt);
}
