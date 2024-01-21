#include <iostream>
#include <string>

int main() {
    std::string date;

    std::cin >> date;
    // month.day.year
    std::string monthName;
    std::string rest = date.substr(date.find('.')+1);
    //std::string month = rest.substr(0,rest.find('.'))
    switch (auto month(std::stoi(rest.substr(0,rest.find('.')))); month){
        case 1:
            monthName = "stycznia";
            break;
        case 2:
            monthName = "lutego";
            break;
        case 3:
            monthName = "marca";
            break;
        case 4:
            monthName = "kwietnia";
            break;
        case 5:
            monthName = "maja";
            break;
        case 6:
            monthName = "czerwca";
            break;
        case 7:
            monthName = "lipca";
            break;
        case 8:
            monthName = "sierpnia";
            break;
        case 9:
            monthName = "wrzesnia";
            break;
        case 10:
            monthName = "pazdziernika";
            break;
        case 11:
            monthName = "listopada";
            break;
        case 12:
            monthName = "grudnia";
            break;
        default:
            return 0;
    }


    std::cout << date.substr(0,date.find('.')) << " " << monthName << " " << rest.substr(date.find('.')+1) << std::endl;

    return 0;
}
