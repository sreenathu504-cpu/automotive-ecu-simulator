#include <iostream>
#include <fstream>
using namespace std;

class ECU
{
private:
    bool engineOn;
    int speed;
    int fuel;
    int temperature;
    int gear;          // 0 = Neutral, 1-5 = Gears
    bool headlightOn;
    bool seatBeltOn;
    bool doorOpen;

public:
    ECU()
    {
        engineOn = false;
        speed = 0;
        fuel = 100;
        temperature = 30;
        gear = 0;
        headlightOn = false;
        seatBeltOn = false;
        doorOpen = true;
    }

    // 1. Engine ON/OFF
    void startEngine()
    {
        if (engineOn)
        {
            cout << "Engine is Already ON!" << endl;
            return;
        }
        if (doorOpen)
        {
            cout << "Cannot start engine. Door is Open!" << endl;
            return;
        }
        if (!seatBeltOn)
        {
            cout << "Cannot start engine. Seat Belt not fastened!" << endl;
            return;
        }
        engineOn = true;
        cout << "Engine Started Successfully!" << endl;
    }

    void stopEngine()
    {
        if (engineOn)
        {
            engineOn = false;
            speed = 0;
            gear = 0;
            cout << "Engine Stopped Successfully!" << endl;
        }
        else
        {
            cout << "Engine is Already OFF!" << endl;
        }
    }

    // 2. Speed Control
    void increaseSpeed()
    {
        if (!engineOn)
        {
            cout << "Cannot increase speed. Engine is OFF!" << endl;
            return;
        }
        if (gear == 0)
        {
            cout << "Cannot increase speed. Gear is in Neutral!" << endl;
            return;
        }
        if (fuel <= 0)
        {
            cout << "Cannot increase speed. Fuel is Empty!" << endl;
            return;
        }
        speed += 10;
        temperature += 2;
        fuel -= 5;
        if (fuel < 0) fuel = 0;
        cout << "Speed increased to " << speed << " km/h" << endl;
        checkWarnings();
    }

    void decreaseSpeed()
    {
        if (speed <= 0)
        {
            cout << "Vehicle is already stationary!" << endl;
            return;
        }
        speed -= 10;
        if (speed < 0) speed = 0;
        cout << "Speed decreased to " << speed << " km/h" << endl;
    }

    // 3. Change Gear
    void changeGear()
    {
        if (!engineOn)
        {
            cout << "Cannot change gear. Engine is OFF!" << endl;
            return;
        }
        int g;
        cout << "Enter Gear (0 = Neutral, 1-5): ";
        cin >> g;
        if (g < 0 || g > 5)
        {
            cout << "Invalid Gear!" << endl;
            return;
        }
        gear = g;
        cout << "Gear changed to " << (gear == 0 ? "Neutral" : to_string(gear)) << endl;
    }

    // 4. Fuel Monitoring
    void refuel()
    {
        fuel = 100;
        cout << "Fuel Tank Refilled to 100%!" << endl;
    }

    // 5. Headlight
    void toggleHeadlight()
    {
        headlightOn = !headlightOn;
        cout << "Headlight turned " << (headlightOn ? "ON" : "OFF") << endl;
    }

    // 6. Seat Belt
    void toggleSeatBelt()
    {
        seatBeltOn = !seatBeltOn;
        cout << "Seat Belt " << (seatBeltOn ? "Fastened" : "Unfastened") << endl;
    }

    // 7. Door
    void toggleDoor()
    {
        doorOpen = !doorOpen;
        cout << "Door is now " << (doorOpen ? "Open" : "Closed") << endl;
        if (doorOpen && engineOn)
        {
            cout << "WARNING: Door opened while engine is running!" << endl;
        }
    }

    // 8. Warnings
    void checkWarnings()
    {
        if (fuel <= 10)
        {
            cout << "WARNING: Low Fuel! (" << fuel << "%)" << endl;
        }
        if (temperature >= 100)
        {
            cout << "WARNING: Engine Overheating! (" << temperature << " C)" << endl;
        }
    }

    // 9. Dashboard
    void showDashboard()
    {
        cout << "\n---------- DASHBOARD ----------" << endl;
        cout << "Engine      : " << (engineOn ? "ON" : "OFF") << endl;
        cout << "Speed       : " << speed << " km/h" << endl;
        cout << "Gear        : " << (gear == 0 ? "Neutral" : to_string(gear)) << endl;
        cout << "Fuel        : " << fuel << " %" << endl;
        cout << "Temperature : " << temperature << " C" << endl;
        cout << "Headlight   : " << (headlightOn ? "ON" : "OFF") << endl;
        cout << "Seat Belt   : " << (seatBeltOn ? "Fastened" : "Unfastened") << endl;
        cout << "Door        : " << (doorOpen ? "Open" : "Closed") << endl;
        cout << "--------------------------------" << endl;
    }

    // 10. Save Data to File
    void saveToFile()
    {
        ofstream outFile("ecu_data.txt");
        if (outFile.is_open())
        {
            outFile << engineOn << endl;
            outFile << speed << endl;
            outFile << fuel << endl;
            outFile << temperature << endl;
            outFile << gear << endl;
            outFile << headlightOn << endl;
            outFile << seatBeltOn << endl;
            outFile << doorOpen << endl;
            outFile.close();
            cout << "Data saved successfully to ecu_data.txt!" << endl;
        }
        else
        {
            cout << "Error: Unable to open file for saving!" << endl;
        }
    }

    // 11. Load Data from File
    void loadFromFile()
    {
        ifstream inFile("ecu_data.txt");
        if (inFile.is_open())
        {
            inFile >> engineOn;
            inFile >> speed;
            inFile >> fuel;
            inFile >> temperature;
            inFile >> gear;
            inFile >> headlightOn;
            inFile >> seatBeltOn;
            inFile >> doorOpen;
            inFile.close();
            cout << "Data loaded successfully from ecu_data.txt!" << endl;
        }
        else
        {
            cout << "Error: No saved data found!" << endl;
        }
    }
};

int main()
{
    ECU car;
    int choice;

    do
    {
        cout << "\n==================================" << endl;
        cout << "   AUTOMOTIVE ECU SIMULATOR" << endl;
        cout << "==================================" << endl;
        cout << "1. Start Engine" << endl;
        cout << "2. Stop Engine" << endl;
        cout << "3. Increase Speed" << endl;
        cout << "4. Decrease Speed" << endl;
        cout << "5. Change Gear" << endl;
        cout << "6. Refuel" << endl;
        cout << "7. Toggle Headlight" << endl;
        cout << "8. Toggle Seat Belt" << endl;
        cout << "9. Toggle Door" << endl;
        cout << "10. Show Dashboard" << endl;
        cout << "11. Save Data" << endl;
        cout << "12. Load Data" << endl;
        cout << "13. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                car.startEngine();
                break;

            case 2:
                car.stopEngine();
                break;

            case 3:
                car.increaseSpeed();
                break;

            case 4:
                car.decreaseSpeed();
                break;

            case 5:
                car.changeGear();
                break;

            case 6:
                car.refuel();
                break;

            case 7:
                car.toggleHeadlight();
                break;

            case 8:
                car.toggleSeatBelt();
                break;

            case 9:
                car.toggleDoor();
                break;

            case 10:
                car.showDashboard();
                break;

            case 11:
                car.saveToFile();
                break;

            case 12:
                car.loadFromFile();
                break;

            case 13:
                cout << "Exiting Program..." << endl;
                break;

            default:
                cout << "Invalid Choice!" << endl;
        }

    } while (choice != 13);

    return 0;
}