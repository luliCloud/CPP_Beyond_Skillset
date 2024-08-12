/** hotel apt is 100 price more expensive thant the hotel room  with the same bedrooms
 * and bathroom num. Price of hotel room is calculated as :
 * 50 * bednum + 100 * bathnum;
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class HotelRoom {
private:
    int bedroom_, bathroom_;
public:
    HotelRoom (int bed, int bath) : bedroom_(bed), bathroom_(bath) {}

    /** must use virtual, otherwise the polymorphism will not auto find child's same name
     * function, but still run the parent same name function, if we store the parent pointer
     */
    virtual int getPrice() {
        return 50 * bedroom_ + 100 * bathroom_;
    }
};

class AptRoom : public HotelRoom {
public:
    /** child cannot inherited private member from parent, but it can initiailze these
     * member via the parent constructor. or using get, set func in parent class to get/set value
     */
    AptRoom(int bed, int bath) : HotelRoom(bed, bath) {}

    virtual int getPrice() { // noting don't type wrong of the name, otherwise will auto
    // go back to use the parent getPrice func!!!
        return HotelRoom::getPrice() + 100;  // noting how to get price from Parent class without instance
    }
};

int main() {
    // first we must use pointer or reference to realize polymorphism
    // second we must use parent class to initialize the vector if both class may exist
    // reason is that parent can auto find function if fit child. and the pointer store
    // parent add may have less initial space. even if points to a child and exceeded the 
    // range, it is valid. but if we store the child and point back to parent, may invalid
    // exceed the range to unkown memory place
    vector<HotelRoom*> rooms;
    int n;
    cin >> n;
    while (n--) {
        string type;
        int bed, bath;
        cin >> type >> bed >> bath;
        if (type == "HotelRoom") {
            rooms.push_back(new HotelRoom(bed, bath));
        } else {
            rooms.push_back(new AptRoom(bed, bath));
        }
    }

    int price = 0;
    for (auto room : rooms) {
        price += room->getPrice(); // we define virtual, so the system auto find correpond
        // type stored in the vector
    }
    cout << price << endl;

    // detele all space. as we stored different type. may need to delete one by one
    for (auto room : rooms) {
        delete room;
    }
    rooms.clear();

    return 0;
}