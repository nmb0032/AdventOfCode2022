#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>

static const std::string PATH = "../data/calories.txt";

std::vector<std::vector<int>> read_file(const std::string path)
{
    std::ifstream file(path);

    std::vector<std::vector<int>> result{};
    std::vector<int> elf{};
    std::string line;
    while (std::getline(file, line))
    {
        if (line == "")
        {
            if (elf.size())
            {
                result.push_back(elf);
                elf.clear();
            }
            continue;
        }
        elf.push_back(std::stoi(line));
    }
    return result;
}

int get_max(const std::vector<std::vector<int>> &data)
{
    int max = 0;
    for (auto &elf : data)
    {
        int tmp = std::accumulate(elf.begin(), elf.end(), 0);
        if (tmp > max)
            max = tmp;
    }
    return max;
}

std::vector<int> get_nth_max(const std::vector<std::vector<int>> &data, int n)
{
    std::vector<int> tmp{};
    for (auto &elf : data)
    {
        tmp.push_back(std::accumulate(elf.begin(), elf.end(), 0));
    }
    std::nth_element(tmp.begin(), tmp.begin() + n, tmp.end(), std::greater{});
    std::vector<int> result{};
    for (int i = 0; i < n; i++)
    {
        result.push_back(tmp[i]);
    }
    return result;
}

std::string to_string(const std::vector<std::vector<int>> &data)
{
    std::string tmp{""};
    for (auto &elf : data)
    {
        tmp.append("An Elf: ");
        for (int i = 0; i < elf.size(); i++)
        {
            tmp.append(std::to_string(elf[i]) + " ");
        }
        tmp.append("\n");
    }
    return tmp;
}

int main(int, char **)
{
    std::cout << "Calorie Counting" << std::endl;
    std::vector<std::vector<int>> data = read_file(PATH);
    std::cout << "Data as String: " << to_string(data) << std::endl;
    std::cout << "Max Calories: " << get_max(data) << std::endl;
    std::cout << "Top 3 calories: ";
    std::vector<int> tmp = get_nth_max(data, 3);
    for (int a : tmp)
    {
        std::cout << " " + std::to_string(a);
    }
    std::cout << std::endl;
    std::cout << "Carrying in total: " << std::accumulate(tmp.begin(), tmp.end(), 0) << std::endl;
}
