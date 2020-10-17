#include <iostream>  // Gives us access to std::cin and std::cout
#include <string>  // Gives us access to std::string and std::getline()

struct LightOutputs {
	bool red_ns;
	bool yellow_ns;
	bool green_ns;
	bool red_ew;
	bool yellow_ew;
	bool green_ew;
};

struct LightInputs {
	int time;
	bool car_sensor_n;
	bool car_sensor_s;
};

// TODO Define your light controller state machine class here

class LightController {
private:
	enum State {
		ALL_RED,
		HOR_GREEN,
		HOR_YELLOW,
		VER_GREEN,
		VER_YELLOW,
	};
	State current_state = ALL_RED;
	int transition_time;
public:
	void transition(LightInputs &inputs) {
		// std::cout << transition_time << ", " << inputs.time << std::endl;
		switch (current_state) {
			case ALL_RED:
				if (inputs.car_sensor_n || inputs.car_sensor_s) {
					current_state = VER_GREEN;
				} else {
					current_state = HOR_GREEN;
				}
				transition_time = inputs.time + 5;
				break;
			case VER_GREEN:
				if (transition_time == inputs.time) {
					current_state = VER_YELLOW;
					transition_time = inputs.time + 2;
				}
				break;
			case VER_YELLOW:
				if (transition_time == inputs.time) {
					current_state = ALL_RED;
				}
				break;
			case HOR_GREEN:
				if (transition_time == inputs.time) {
					current_state = HOR_YELLOW;
					transition_time = inputs.time + 2;
				}
				break;
			case HOR_YELLOW:
				if (transition_time == inputs.time) {
					current_state = ALL_RED;
				}
				break;
		}
	}

	LightOutputs output() {
		switch (current_state) {
			case ALL_RED:
				return (struct LightOutputs){true, false, false, true, false, false};
			case VER_GREEN:
				return (struct LightOutputs){false, false, true, true, false, false};
			case VER_YELLOW:
				return (struct LightOutputs){false, true, false, true, false, false};
			case HOR_GREEN:
				return (struct LightOutputs){true, false, false, false, false, true};
			case HOR_YELLOW:
				return (struct LightOutputs){true, false, false, false, true, false};
		}
	}
};

int main()
{
    // TODO Initialize your state machine class here
    int time = 0;
    LightController controller;
    while(true)
    {
        std::string input;
        std::getline(std::cin, input);
        if(input.size() != 2)
            break;

        // TODO Parse the input digits
        LightInputs inputs {
        	time,
        	input[0] == '1',
        	input[1] == '1',
        };
        // TODO Update your state machine based on input
        controller.transition(inputs);
        // TODO Output your state machine's light controls to std::cout
        LightOutputs output = controller.output();
		// bool red_ns;
		// bool yellow_ns;
		// bool green_ns;
		// bool red_ew;
		// bool yellow_ew;
		// bool green_ew;
        std::cout << output.red_ns << output.yellow_ns << output.green_ns
        	<< output.red_ew << output.yellow_ew << output.green_ew << std::endl;
        time += 1;

    }
    return 0;
}
